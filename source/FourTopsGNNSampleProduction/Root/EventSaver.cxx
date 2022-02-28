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

    for (auto systematicTree : treeManagers())
    {
      systematicTree -> makeOutputVariable(m_topsPreFSR_pt, "topPreFSR_pt"); 
      systematicTree -> makeOutputVariable(m_topsPreFSR_e, "topPreFSR_e"); 
      systematicTree -> makeOutputVariable(m_topsPreFSR_eta, "topPreFSR_eta"); 
      systematicTree -> makeOutputVariable(m_topsPreFSR_phi, "topPreFSR_phi"); 
      systematicTree -> makeOutputVariable(m_topsPreFSR_charge, "topPreFSR_charge"); 
      systematicTree -> makeOutputVariable(m_topsPreFSR_status, "topPreFSR_status");

      systematicTree -> makeOutputVariable(m_topsPostFSR_pt, "topPostFSR_pt"); 
      systematicTree -> makeOutputVariable(m_topsPostFSR_e, "topPostFSR_e"); 
      systematicTree -> makeOutputVariable(m_topsPostFSR_eta, "topPostFSR_eta"); 
      systematicTree -> makeOutputVariable(m_topsPostFSR_phi, "topPostFSR_phi"); 
      systematicTree -> makeOutputVariable(m_topsPostFSR_charge, "topPostFSR_charge"); 

      systematicTree -> makeOutputVariable(m_topPostFSR_children_pt, "topPostFSRchildren_pt"); 
      systematicTree -> makeOutputVariable(m_topPostFSR_children_e, "topPostFSRchildren_e"); 
      systematicTree -> makeOutputVariable(m_topPostFSR_children_eta, "topPostFSRchildren_eta"); 
      systematicTree -> makeOutputVariable(m_topPostFSR_children_phi, "topPostFSRchildren_phi"); 
      systematicTree -> makeOutputVariable(m_topPostFSR_children_charge, "topPostFSRchildren_charge"); 
      systematicTree -> makeOutputVariable(m_topPostFSR_children_pdgid, "topPostFSRchildren_pdgid"); 
      systematicTree -> makeOutputVariable(m_Gtop_index, "Gtop_index"); 
      systematicTree -> makeOutputVariable(m_GtopFromRes, "Gtop_FromRes"); 

      systematicTree -> makeOutputVariable(m_TruthJets_pt, "truthjet_pt"); 
      systematicTree -> makeOutputVariable(m_TruthJets_e, "truthjet_e"); 
      systematicTree -> makeOutputVariable(m_TruthJets_eta, "truthjet_eta"); 
      systematicTree -> makeOutputVariable(m_TruthJets_phi, "truthjet_phi"); 
      systematicTree -> makeOutputVariable(m_TruthJets_pdgid, "truthjet_pdgid"); 

      systematicTree -> makeOutputVariable(m_GhostTruthJetMap, "GhostTruthJetMap"); 

      systematicTree -> makeOutputVariable(m_top_children_pt, "truth_top_child_pt"); 
      systematicTree -> makeOutputVariable(m_top_children_e, "truth_top_child_e"); 
      systematicTree -> makeOutputVariable(m_top_children_eta, "truth_top_child_eta"); 
      systematicTree -> makeOutputVariable(m_top_children_phi, "truth_top_child_phi"); 
      systematicTree -> makeOutputVariable(m_top_children_charge, "truth_top_child_charge"); 
      systematicTree -> makeOutputVariable(m_top_children_pdgid, "truth_top_child_pdgid"); 

      systematicTree -> makeOutputVariable(m_top_pt, "truth_top_pt"); 
      systematicTree -> makeOutputVariable(m_top_e, "truth_top_e"); 
      systematicTree -> makeOutputVariable(m_top_eta, "truth_top_eta"); 
      systematicTree -> makeOutputVariable(m_top_phi, "truth_top_phi"); 
      systematicTree -> makeOutputVariable(m_top_charge, "truth_top_charge"); 
      systematicTree -> makeOutputVariable(m_topFromRes, "truth_top_FromRes"); 
      systematicTree -> makeOutputVariable(m_top_index, "truth_top_index"); 

      systematicTree -> makeOutputVariable(m_top_debug, "truth_top_debug");
      systematicTree -> makeOutputVariable(m_jet_map_top, "jet_map_top");
      systematicTree -> makeOutputVariable(m_jet_map_Ghost, "jet_map_Ghost");  

    }
    F = file; 
  }

  void EventSaver::saveEvent(const top::Event& event)
  {
   
    m_genFilHT = -99; 

    // Reconstructed ghost tops before FSR
    m_topsPreFSR_pt.clear();
    m_topsPreFSR_e.clear();
    m_topsPreFSR_eta.clear();
    m_topsPreFSR_phi.clear();
    m_topsPreFSR_charge.clear(); 
    m_topsPreFSR_status.clear();

    // Reconstructed ghost tops post FSR
    m_topsPostFSR_pt.clear();
    m_topsPostFSR_e.clear();
    m_topsPostFSR_eta.clear();
    m_topsPostFSR_phi.clear();
    m_topsPostFSR_charge.clear(); 

    // Children from Reconstucted gHost tops post FSR
    m_topPostFSR_children_pt.clear(); 
    m_topPostFSR_children_e.clear(); 
    m_topPostFSR_children_eta.clear(); 
    m_topPostFSR_children_phi.clear(); 
    m_topPostFSR_children_charge.clear(); 
    m_topPostFSR_children_pdgid.clear(); 

    // Truth jets
    m_TruthJets_pt.clear();
    m_TruthJets_e.clear();
    m_TruthJets_eta.clear();
    m_TruthJets_phi.clear();
    m_TruthJets_pdgid.clear(); 
      
    // Truth jet to Ghost top mapping 
    m_GhostTruthJetMap.clear(); 
    m_Gtop_index.clear(); 

    // Children from m_truth branch 
    m_top_children_pt.clear(); 
    m_top_children_e.clear(); 
    m_top_children_eta.clear(); 
    m_top_children_phi.clear(); 
    m_top_children_charge.clear(); 
    m_top_children_pdgid.clear(); 

    // tops from m_truth branch 
    m_top_pt.clear(); 
    m_top_e.clear(); 
    m_top_eta.clear(); 
    m_top_phi.clear(); 
    m_top_charge.clear(); 
    m_topFromRes.clear(); 
    m_GtopFromRes.clear(); 

    m_top_index.clear(); 
    m_top_debug.clear(); 
    m_jet_map_top.clear();
    m_jet_map_Ghost.clear();   


    if (!event.m_info -> eventType(xAOD::EventInfo::IS_SIMULATION)){return;}
    if (event.m_info -> isAvailable<float>("GenFiltHT")){m_genFilHT = event.m_info -> auxdataConst<float>("GenFiltHT"); }
    const xAOD::JetContainer* m_truthjets{nullptr}; 
    if (!evtStore() -> retrieve(m_truthjets, "AntiKt4TruthWZJets").isSuccess()){return;}
    if (!m_truthjets){return;}


    std::vector<const xAOD::TruthParticle*> AllParents;
    std::vector<int> AllParents_Map;
    int p = 0; 
    for (const auto &jet : *m_truthjets)
    {
      p++; 
      std::vector<const xAOD::TruthParticle*> ghost_P = jet -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
      AllParents.insert(AllParents.end(), ghost_P.begin(), ghost_P.end());  
       
      std::vector<int> tmp(ghost_P.size(), p); 
      AllParents_Map.insert(AllParents_Map.end(), tmp.begin(), tmp.end()); 
      
      //if ( jet -> pt() < PT_Cut || fabs(jet -> eta()) > ETA_Cut){continue;}
      m_GhostTruthJetMap.push_back({0}); 
      m_TruthJets_pt.push_back( jet -> pt() ); 
      m_TruthJets_e.push_back( jet -> e() ); 
      m_TruthJets_eta.push_back( jet -> eta() ); 
      m_TruthJets_phi.push_back( jet -> phi() ); 
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
      m_GtopFromRes.push_back(res); 

      m_topsPreFSR_pt.push_back(T -> pt()); 
      m_topsPreFSR_e.push_back(T -> e()); 
      m_topsPreFSR_eta.push_back(T -> eta()); 
      m_topsPreFSR_phi.push_back(T -> phi()); 
      m_topsPreFSR_charge.push_back(T -> charge()); 
      m_topsPreFSR_status.push_back(T -> status());
    }
     

    // Find tops before full decay, i.e. before FSR
    std::vector<const xAOD::TruthParticle*> TopsPostFSR_; 
    for (const xAOD::TruthParticle* T : TopsPreFSR_)
    {
      const xAOD::TruthParticle* P = TopsPostFSR(T);
      TopsPostFSR_.push_back(P); 

      m_topsPostFSR_pt.push_back(P -> pt()); 
      m_topsPostFSR_e.push_back(P -> e()); 
      m_topsPostFSR_eta.push_back(P -> eta()); 
      m_topsPostFSR_phi.push_back(P -> phi()); 
      m_topsPostFSR_charge.push_back(P -> charge()); 

      std::vector<float> pt; 
      std::vector<float> e; 
      std::vector<float> eta; 
      std::vector<float> phi; 
      std::vector<int> charge; 
      std::vector<int> pdgid; 
      
      for (unsigned int i(0); i < P -> nChildren(); i++)
      {
        const xAOD::TruthParticle* ch = AssureWDecay(P -> child(i));
        if (ParticleID::isW(ch -> pdgId()))
        {
          for (unsigned int k(0); k < ch -> nChildren(); k++)
          {
            pt.push_back(ch -> child(k) -> pt());        
            e.push_back(ch -> child(k) -> e()); 
            eta.push_back(ch -> child(k) -> eta()); 
            phi.push_back(ch -> child(k) -> phi()); 
            charge.push_back(ch -> child(k) -> charge()); 
            pdgid.push_back(ch -> child(k) -> pdgId()); 
          }
        }
        else if ( ParticleID::isNu(ch -> pdgId()) || ParticleID::isQuark( ch -> pdgId()) || ParticleID::isLep( ch -> pdgId()))
        {

          pt.push_back(ch -> pt());        
          e.push_back(ch -> e()); 
          eta.push_back(ch -> eta()); 
          phi.push_back(ch -> phi()); 
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
    p = 0; 
    std::vector<int> AllParticleMap; 
    std::vector<int> TopMap; 
    std::vector<const xAOD::TruthParticle*> AllParticleVector; 
    for (const xAOD::TruthParticle* T : TopsPostFSR_)
    {
      p++; 
      m_Gtop_index.push_back(p); 

      std::vector<const xAOD::TruthParticle*> ParticleVector; 
      std::vector<int> ParticleMap; 
      GetPath(T, 0, &ParticleVector, &ParticleMap); 
      
      AllParticleMap.insert(AllParticleMap.end(), ParticleMap.begin(), ParticleMap.end()); 
      AllParticleVector.insert(AllParticleVector.end(), ParticleVector.begin(), ParticleVector.end());
      std::vector<int> tmp(ParticleVector.size(), p); 
      TopMap.insert(TopMap.end(), tmp.begin(), tmp.end()); 
      
      int index = 0; 
      for (const xAOD::Jet* j : *m_truthjets)
      {
        
        //if ( j -> pt() < PT_Cut || fabs(j -> eta()) > ETA_Cut){continue;}
        
        std::vector<const xAOD::TruthParticle*> ghost = j -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
        std::vector<const xAOD::TruthParticle*> TMP; 
        for (const xAOD::TruthParticle* t_c : ParticleVector)
        {
          for (const xAOD::TruthParticle* g : ghost)
          {
            if (t_c == g){ TMP.push_back(t_c); }
          }
        }
        
        if (TMP.size() > 0)
        { 
          if (m_GhostTruthJetMap[index][0] == 0){m_GhostTruthJetMap[index] = {};}
          m_GhostTruthJetMap[index].push_back(p); 
        }
        index++;
      }
    }
   
    std::map<const xAOD::Jet*, std::vector<const xAOD::TruthParticle*>> Output_E;
    std::map<const xAOD::Jet*, std::vector<const xAOD::TruthParticle*>> Output_PT;
    std::map<const xAOD::Jet*, std::vector<const xAOD::TruthParticle*>> Paired;
    std::map<const xAOD::Jet*, std::vector<float>> Paired_E;
    std::map<const xAOD::Jet*, std::vector<float>> Paired_PT;
    std::map<const xAOD::Jet*, std::vector<float>> Paired_dR;
    int o = 0;
    
    for (const xAOD::Jet* j_i : event.m_jets)
    {
      Paired.insert({j_i, {}});
      Paired_E.insert({j_i, {}}); 
      Paired_PT.insert({j_i, {}}); 
      Paired_dR.insert({j_i, {}}); 
    }


    //std::cout << "_____ New Event _____ " << std::endl;
    // ============================== WARNING!!!!!! =========================================== //
    // Careful!!! This particle map was created using ONLY TOPS!!!!!! Might need to resort to using all partons from truthjets
    for (unsigned int k(0); k < AllParticleMap.size(); k++)
    {
      std::vector<float> je_dr; 
      for (const xAOD::Jet* j_i : event.m_jets)
      {
        const xAOD::TruthParticle* depth_p = AllParticleVector[k]; 
        je_dr.push_back(std::pow( std::pow(depth_p -> eta() - j_i -> eta(), 2) + std::pow(depth_p -> phi() - j_i -> phi(), 2), 0.5 )); 
      }
    
      int v_ind = std::min_element(je_dr.begin(), je_dr.end()) - je_dr.begin(); 
      const xAOD::Jet* je = event.m_jets.at(v_ind);
      
      Paired[je].push_back(AllParticleVector[k]);
      Paired_E[je].push_back(AllParticleVector[k] -> e() / je -> e());
      Paired_PT[je].push_back(AllParticleVector[k] -> pt() / je -> pt());
      Paired_dR[je].push_back(je_dr[v_ind]);
    }
    NormalizeList(Paired, Paired_E, Paired_dR, &Output_E); 
    NormalizeList(Paired, Paired_PT, Paired_dR, &Output_PT); 

    for (it j = Output_E.begin(); j != Output_E.end(); j++)
    {
      m_jet_map_top.push_back({0});
      const xAOD::Jet* J = j -> first; 
      std::vector<const xAOD::TruthParticle*> VE = j -> second; 
      std::vector<const xAOD::TruthParticle*> VPT = Output_PT[J]; 
      std::vector<const xAOD::TruthParticle*> Out_V; 

      std::set_intersection(VE.begin(), VE.end(), VPT.begin(), VPT.end(), back_inserter(Out_V));
      
      for (int i(0); i < AllParticleVector.size(); i++)
      {
        const xAOD::TruthParticle* thisParticle = AllParticleVector[i]; 
        int thisIndex = TopMap[i];
        for (const xAOD::TruthParticle* JE : Out_V)
        {
          if ( thisParticle == JE )
          {
            if (m_jet_map_top[o][0] == 0){ m_jet_map_top[o] = {}; }
            m_jet_map_top[o].push_back(thisIndex);
            break;
          }
        }
      }
      o++;
    }

    // ============================== Using Ghost Partons of Truth Jets =========================================== //
    std::vector<const xAOD::TruthParticle*> AllParents_Unique;
    std::vector<int> AllParents_Map_Unique;
    for (int i(0); i < AllParents.size(); i++)
    {
      if (!(std::find(AllParents_Unique.begin(), AllParents_Unique.end(), AllParents[i]) != AllParents_Unique.end()))
      {
        AllParents_Unique.push_back(AllParents[i]); 
        AllParents_Map_Unique.push_back(AllParents_Map[i]); 
      }
    }

    Paired.clear();
    Paired_E.clear();
    Paired_PT.clear();
    Paired_dR.clear();
    Output_E.clear();
    Output_PT.clear();
    o = 0;

    for (const xAOD::Jet* j_i : event.m_jets)
    {
      Paired.insert({j_i, {}});
      Paired_E.insert({j_i, {}}); 
      Paired_PT.insert({j_i, {}}); 
      Paired_dR.insert({j_i, {}}); 
    }
    
    for (unsigned int k(0); k < AllParents_Unique.size(); k++)
    {
      std::vector<float> je_dr; 
      for (const xAOD::Jet* j_i : event.m_jets)
      {
        const xAOD::TruthParticle* depth_p = AllParents_Unique[k]; 
        je_dr.push_back(std::pow( std::pow(depth_p -> eta() - j_i -> eta(), 2) + std::pow(depth_p -> phi() - j_i -> phi(), 2), 0.5 )); 
      }
    
      int v_ind = std::min_element(je_dr.begin(), je_dr.end()) - je_dr.begin(); 
      const xAOD::Jet* je = event.m_jets.at(v_ind);
      
      Paired[je].push_back(AllParents_Unique[k]);
      Paired_E[je].push_back(AllParents_Unique[k] -> e() / je -> e());
      Paired_PT[je].push_back(AllParents_Unique[k] -> pt() / je -> pt());
      Paired_dR[je].push_back(je_dr[v_ind]);
    }

    NormalizeList(Paired, Paired_E, Paired_dR, &Output_E); 
    NormalizeList(Paired, Paired_PT, Paired_dR, &Output_PT); 
    
    for (it j = Output_E.begin(); j != Output_E.end(); j++)
    {
      m_jet_map_Ghost.push_back({0});
      const xAOD::Jet* J = j -> first; 
      std::vector<const xAOD::TruthParticle*> VE = j -> second; 
      std::vector<const xAOD::TruthParticle*> VPT = Output_PT[J]; 
      std::vector<const xAOD::TruthParticle*> Out_V; 
      
      std::set_intersection(VE.begin(), VE.end(), VPT.begin(), VPT.end(), back_inserter(Out_V));

      for (int i(0); i < AllParents_Unique.size(); i++)
      {
        const xAOD::TruthParticle* thisParticle = AllParents_Unique[i]; 
        int thisIndex = AllParents_Map_Unique[i];
        for (const xAOD::TruthParticle* JE : Out_V)
        {
          if ( thisParticle == JE )
          {
            if (m_jet_map_Ghost[o][0] == 0){ m_jet_map_Ghost[o] = {}; }
            m_jet_map_Ghost[o].push_back(thisIndex);
            break;
          }
        }
      }
      o++;
    }
    




    //std::this_thread::sleep_for(std::chrono::milliseconds(100000));

      //if (p < -1)
      //{

      //  std::vector<int> tmp_ParticleMap; 
      //  std::vector<const xAOD::TruthParticle*> tmp_ParticleVector; 

      //  std::cout << "------- WARNING!!!! MORE THAN 4 TOPS FOUND! " << p << std::endl;
      //  for (const xAOD::TruthParticle* K : TopsPostFSR_)
      //  {
      //    GetPath(K, 0, &tmp_ParticleVector, &tmp_ParticleMap); 
      //    std::cout << "TOP ADDRESS: " << K << " nParents: " << K -> nParents() << " PT: " << K -> pt() << " E: " << K -> e() << " Phi: " << K -> phi() << " Eta: " << K -> eta() << " S: " << K -> status() << " nChildren:" << K -> nChildren()<< std::endl;

      //    if (K -> nParents() > 0)
      //    {
      //      std::vector<const xAOD::TruthParticle*> Out = MergeParents({K});

      //      for (const xAOD::TruthParticle* L : Out)
      //      {
      //        std::cout << "Final parent of Top: " << L -> pdgId() << " A: " << L << " nParents: " << L -> nParents() << " " << L -> pdgId()  << std::endl;
      //      }
      //    } 
      //  }

      //  std::cout << "====== DECAY CHAIN =========" << std::endl;

      //  for (int i(0); i < tmp_ParticleVector.size(); i++)
      //  {
      //    
      //    if (tmp_ParticleMap[i] > 5){continue;}
      //    TString ar = ""; 

      //    for (int k(0); k < tmp_ParticleMap[i]; k++){ar += "-"; }
      //    ar += "> "; 
      //    
      //    if (abs(tmp_ParticleVector[i] -> pdgId()) == 6)
      //    {
      //      std::cout << " NEW TOP: " << std::endl;
      //      std::cout << ar << " P: " << tmp_ParticleVector[i] -> pdgId() << " S: " << tmp_ParticleVector[i] -> status() << " MA: " << tmp_ParticleVector[i] <<  std::endl;
      //      continue; 
      //    }

      //    std::cout << ar << " P: " << tmp_ParticleVector[i] -> pdgId() << " S: " << tmp_ParticleVector[i] -> status() << " MA: " << tmp_ParticleVector[i] <<  std::endl;
      //  }
      //  std::this_thread::sleep_for(std::chrono::milliseconds(100000)); 
      //}


    const xAOD::TruthParticleContainer* TPC = event.m_truth; 
    p = 0;
    int y = 0; 
    for (const xAOD::TruthParticle* T : *TPC)
    {

      if (ParticleID::isGEANT(T -> barcode())){break;}
      if (!IsFinalTop(T)){continue;} // Check that the given top decays into quarks etc.

      int res = 0; 
      if (IsFinalBSMZ(T)){res=1;}
      m_topFromRes.push_back(res); 
      p++; 

      m_top_pt.push_back(T -> pt()); 
      m_top_e.push_back(T -> e()); 
      m_top_eta.push_back(T -> eta()); 
      m_top_phi.push_back(T -> phi()); 
      m_top_charge.push_back(T -> charge()); 
      m_top_index.push_back(p); 
      
      std::vector<float> tmp_pt; 
      std::vector<float> tmp_e; 
      std::vector<float> tmp_eta; 
      std::vector<float> tmp_phi; 
      std::vector<int> tmp_charge; 
      std::vector<int> tmp_pdgid; 
      for (unsigned int k(0); k < T -> nChildren(); k++)
      {
        const xAOD::TruthParticle* ch = AssureWDecay(T -> child(k));
        if (!ch) continue;

        if (ParticleID::isTop(ch -> pdgId())) { m_top_debug.push_back(1); }
     
        if (ParticleID::isW(ch -> pdgId()))
        {
          for (unsigned int c(0); c < ch -> nChildren(); c++)
          {
            tmp_pt.push_back( ch -> child(c) -> pt()); 
            tmp_e.push_back( ch -> child(c) -> e()); 
            tmp_eta.push_back( ch -> child(c) -> eta()); 
            tmp_phi.push_back( ch -> child(c) -> phi()); 
            tmp_charge.push_back( ch -> child(c) -> charge());
            tmp_pdgid.push_back( ch -> child(c) -> pdgId()); 
            y++; 
          }
        }
        else if ( ParticleID::isNu(ch -> pdgId()) || ParticleID::isQuark( ch -> pdgId()) || ParticleID::isLep( ch -> pdgId()))
        {
          tmp_pt.push_back( ch -> pt()); 
          tmp_e.push_back( ch -> e()); 
          tmp_eta.push_back( ch -> eta()); 
          tmp_phi.push_back( ch -> phi()); 
          tmp_charge.push_back( ch -> charge());
          tmp_pdgid.push_back( ch -> pdgId()); 
          y++; 
        }
      }

      m_top_children_pt.push_back(tmp_pt); 
      m_top_children_e.push_back(tmp_e); 
      m_top_children_eta.push_back(tmp_eta); 
      m_top_children_phi.push_back(tmp_phi); 
      m_top_children_charge.push_back(tmp_charge); 
      m_top_children_pdgid.push_back(tmp_pdgid);  
    }
    

    
    top::EventSaverFlatNtuple::saveEvent(event); 
  }


}

