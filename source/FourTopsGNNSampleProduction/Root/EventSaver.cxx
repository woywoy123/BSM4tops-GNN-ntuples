#include "FourTopsGNNSampleProduction/EventSaver.h"

// Boilerplate Event Info 
#include "TopEvent/Event.h"
#include "TopEvent/EventTools.h"

// File stuff 
#include "TopEventSelectionTools/TreeManager.h"
#include "TopConfiguration/TopConfig.h"

// Particle stuff
#include "xAODTruth/TruthParticle.h"

// Debugging stuff 
#include <FourTopsGNNSampleProduction/TruthAnalysis.h>
#include <FourTopsGNNSampleProduction/ParticleID.h>
#include <thread>
#include <chrono>
#include <algorithm>

namespace top {
  EventSaver::EventSaver(){} 

  void EventSaver::initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches) 
  {
    top::EventSaverFlatNtuple::initialize(config, file, extraBranches); 
    FillBranches();
    F = file; 
  }

  void EventSaver::saveEvent(const top::Event& event)
  {
    ClearVector();
    if (!event.m_info -> eventType(xAOD::EventInfo::IS_SIMULATION)){return;}
    if (event.m_info -> isAvailable<float>("GenFiltHT")){m_genFilHT = event.m_info -> auxdataConst<float>("GenFiltHT"); }
    
    const xAOD::JetContainer* m_truthjets{nullptr}; 
    if (!evtStore() -> retrieve(m_truthjets, "AntiKt4TruthWZJets").isSuccess()){return;}
    if (!m_truthjets){return;}


    std::vector<const xAOD::TruthParticle*> AllParents;
    for (const auto &jet : *m_truthjets)
    {
      std::vector<const xAOD::TruthParticle*> ghost_P = jet -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
      AllParents.insert(AllParents.end(), ghost_P.begin(), ghost_P.end());  
       
      //if ( jet -> pt() < PT_Cut || fabs(jet -> eta()) > ETA_Cut){continue;}
      FillVector(jet, &m_TruthJets_pt, &m_TruthJets_e, &m_TruthJets_phi, &m_TruthJets_eta); 
      m_GhostTruthJetMap.push_back({0}); 
      m_TruthJets_pdgid.push_back(jet -> auxdata<int>("PartonTruthLabelID")); 
    }
    
    // Merge all the ghost particles and get a common parent i.e. go to origin particles
    std::vector<const xAOD::TruthParticle*> Out = MergeParents(AllParents);

    // Now go down the decay chain and parents which produce tops
    std::vector<const xAOD::TruthParticle*> TopsPreFSR_ = TopsPreFSR(Out);
    for (const xAOD::TruthParticle* T : TopsPreFSR_)
    {
      int res = 0; 
      if (IsFinalBSMZ(T)){res=1;}
      FillVector(T, &m_topsPreFSR_pt, &m_topsPreFSR_e, &m_topsPreFSR_phi, &m_topsPreFSR_eta); 

      m_topsPreFSR_charge.push_back(T -> charge()); 
      m_topsPreFSR_status.push_back(T -> status());
      m_GtopFromRes.push_back(res); 
    }
    
    
    // Find tops before full decay, i.e. before FSR
    std::vector<const xAOD::TruthParticle*> TopsPostFSR_; 
    for (const xAOD::TruthParticle* T : TopsPreFSR_)
    {
      const xAOD::TruthParticle* P = TopsPostFSR(T);

      FillVector(T, &m_topsPostFSR_pt, &m_topsPostFSR_e, &m_topsPostFSR_phi, &m_topsPostFSR_eta); 
      m_topsPostFSR_charge.push_back(P -> charge()); 
      TopsPostFSR_.push_back(P); 
      
      std::vector<float> pt, e, eta, phi; 
      std::vector<int> charge, pdgid; 
      for (unsigned int i(0); i < P -> nChildren(); i++)
      {
        const xAOD::TruthParticle* ch = AssureWDecay(P -> child(i));
        if (ParticleID::isW(ch -> pdgId()))
        {
          for (unsigned int k(0); k < ch -> nChildren(); k++)
          {
            FillVector(ch -> child(k), &pt, &e, &phi, &eta);
            charge.push_back(ch -> child(k) -> charge()); 
            pdgid.push_back(ch -> child(k) -> pdgId()); 
          }
        }
        else if ( ParticleID::isNu(ch -> pdgId()) || ParticleID::isQuark( ch -> pdgId()) || ParticleID::isLep( ch -> pdgId()))
        {
          FillVector(ch, &pt, &e, &phi, &eta);
          charge.push_back(ch -> charge()); 
          pdgid.push_back(ch -> pdgId()); 
        }

      }

      m_topPostFSR_children_pt.push_back(pt); 
      m_topPostFSR_children_e.push_back(e); 
      m_topPostFSR_children_eta.push_back(eta); 
      m_topPostFSR_children_phi.push_back(phi); 
      m_topPostFSR_children_charge.push_back(charge); 
      m_topPostFSR_children_pdgid.push_back(pdgid); 
    }

    // Now match the tops by following the decay chain and match them to truth jets.
    int p = 0; 
    for (const xAOD::TruthParticle* T : TopsPostFSR_)
    {
      p++; 
      m_Gtop_index.push_back(p); 

      std::vector<const xAOD::TruthParticle*> ParticleVector; 
      std::vector<int> ParticleMap; 
      GetPath(T, 0, &ParticleVector, &ParticleMap); 
      
      int index = 0; 
      for (const xAOD::Jet* j : *m_truthjets)
      {
        
        //if ( j -> pt() < PT_Cut || fabs(j -> eta()) > ETA_Cut){continue;}
        
        std::vector<const xAOD::TruthParticle*> ghost = j -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
        std::vector<const xAOD::TruthParticle*> Similar; 
        
        std::set_intersection(ParticleVector.begin(), ParticleVector.end(), ghost.begin(), ghost.end(), back_inserter(Similar)); 
        if (Similar.size() > 0)
        { 
          if (m_GhostTruthJetMap[index][0] == 0){m_GhostTruthJetMap[index] = {};}
          m_GhostTruthJetMap[index].push_back(p); 
        }
        index++;
      }
    }
   
    p = 0;
    const xAOD::TruthParticleContainer* TPC = event.m_truth; 
    for (const xAOD::TruthParticle* T : *TPC)
    {

      if (ParticleID::isGEANT(T -> barcode())){break;}
      if (!IsFinalTop(T)){continue;} // Check that the given top decays into quarks etc.

      int res = 0; 
      if (IsFinalBSMZ(T)){res=1;}
      m_topFromRes.push_back(res); 
      p++; 

      FillVector(T, &m_top_pt, &m_top_e, &m_top_phi, &m_top_eta);
      m_top_charge.push_back(T -> charge()); 
      m_top_index.push_back(p); 
      
      std::vector<float> tmp_pt, tmp_e, tmp_eta, tmp_phi; 
      std::vector<int> tmp_charge, tmp_pdgid; 
      for (unsigned int k(0); k < T -> nChildren(); k++)
      {
        const xAOD::TruthParticle* ch = AssureWDecay(T -> child(k));
        if (!ch) continue;
        if (ParticleID::isW(ch -> pdgId()))
        {
          for (unsigned int c(0); c < ch -> nChildren(); c++)
          {
            FillVector(ch -> child(c), &tmp_pt, &tmp_e, &tmp_phi, &tmp_eta);
            tmp_charge.push_back( ch -> child(c) -> charge());
            tmp_pdgid.push_back( ch -> child(c) -> pdgId()); 
          }
        }
        else if ( ParticleID::isNu(ch -> pdgId()) || ParticleID::isQuark( ch -> pdgId()) || ParticleID::isLep( ch -> pdgId()))
        {
          FillVector(ch, &tmp_pt, &tmp_e, &tmp_phi, &tmp_eta);
          tmp_charge.push_back( ch -> charge());
          tmp_pdgid.push_back( ch -> pdgId()); 
        }
      }
      m_top_children_pt.push_back(tmp_pt); 
      m_top_children_e.push_back(tmp_e); 
      m_top_children_eta.push_back(tmp_eta); 
      m_top_children_phi.push_back(tmp_phi); 
      m_top_children_charge.push_back(tmp_charge); 
      m_top_children_pdgid.push_back(tmp_pdgid);  
    }

    std::map<int, std::vector<int>> TruthJet_JetMap;
    for (unsigned int k(0); k < event.m_jets.size(); k++)
    {
      std::vector<const xAOD::TruthParticle*> g_J = event.m_jets.at(k) -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
      TruthJet_JetMap.insert({k, {-1}}); 

      for (unsigned int l(0); l < m_truthjets -> size(); l++)
      {
        std::vector<const xAOD::TruthParticle*> g_truJ = (*m_truthjets)[l] -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
        
        std::vector<const xAOD::TruthParticle*> Similar; 
        std::set_intersection(g_J.begin(), g_J.end(), g_truJ.begin(), g_truJ.end(), back_inserter(Similar));
        if (Similar.size() != 0)
        { 
          if (TruthJet_JetMap[k][0] == -1){ TruthJet_JetMap[k] = {}; }
          TruthJet_JetMap[k].push_back(l); 
        }
      }
      m_jet_map_Ghost.push_back(TruthJet_JetMap[k]); 
    }
    top::EventSaverFlatNtuple::saveEvent(event); 
  }


}

