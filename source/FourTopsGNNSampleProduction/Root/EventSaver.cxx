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
  
    // Collect for each top the decay chain and store in a flat vector - Also match each child to a specific jet/truthjet
    int p = 0; 
    const xAOD::TruthParticleContainer* TPC = event.m_truth; 
    std::vector<const xAOD::TruthParticle*> Tops_; 
    for (const xAOD::TruthParticle* T : *TPC)
    {
      if (ParticleID::isGEANT(T -> barcode())){break;}
      if (!IsFinalTop(T)){continue;} // Check that the given top decays into quarks etc.
     
      int res = 0; 
      if (IsFinalBSMZ(T)){res=1;}
      FillVector(T, &m_top_pt, &m_top_e, &m_top_phi, &m_top_eta, &m_top_charge, &m_top_pdgid);
      m_top_FromRes.push_back(res); 
      m_top_index.push_back(p);

      std::vector<const xAOD::TruthParticle*> Particle_Vector; 
      std::vector<int> Particle_DecayIndex;
      GetPath(T, 0, &Particle_Vector, &Particle_DecayIndex);

      // Record all the children decay chain
      for (unsigned int i=0; i<Particle_DecayIndex.size(); i++)
      {
        const xAOD::TruthParticle* C = Particle_Vector[i];
        int C_i = Particle_DecayIndex[i];

        m_top_children_index.push_back(C_i);
        m_top_children_TopIndex.push_back(p);
        FillVector(C, &m_top_children_pt, 
            &m_top_children_e, &m_top_children_phi, 
            &m_top_children_eta, &m_top_children_charge, 
            &m_top_children_pdgid);
        
        std::vector<int> tmp_JetIndex; 
        for (unsigned int j(0); j < event.m_jets.size(); j++)
        {
          std::vector<const xAOD::TruthParticle*> g_J = event.m_jets.at(j) -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons");
          std::vector<const xAOD::TruthParticle*> F = Intersection({C}, g_J); 
          if ( F.size() != 0 ){ tmp_JetIndex.push_back(j); }
        }
        if (tmp_JetIndex.size() == 0) {tmp_JetIndex = {-1};}
        m_top_children_JetIndex.push_back(tmp_JetIndex);

        std::vector<int> tmp_TruthJetIndex; 
        for (unsigned int j(0); j < m_truthjets -> size(); j++)
        {
          std::vector<const xAOD::TruthParticle*> g_J = (*m_truthjets)[j] -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons");
          std::vector<const xAOD::TruthParticle*> F = Intersection({C}, g_J); 
          if ( F.size() != 0 ){ tmp_TruthJetIndex.push_back(j); }
        }
        if (tmp_TruthJetIndex.size() == 0) {tmp_TruthJetIndex = {-1};}
        m_top_children_TruthJetIndex.push_back(tmp_TruthJetIndex);
      }
      p++; 
    }
    
    // Record the jet constituents and record any top contributions
    for (unsigned int j(0); j < event.m_jets.size(); j++)
    {
      std::vector<const xAOD::TruthParticle*> g_J = event.m_jets.at(j) -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons");
      
      std::vector<int> Tmp_Index; 
      for (unsigned int i(0); i < Tops_.size(); i++)
      {
        const xAOD::TruthParticle* T = Tops_[i]; 
        std::vector<const xAOD::TruthParticle*> t_map; 
        std::vector<int> t_index; 

        GetPath(T, 0, &t_map, &t_index);
        std::vector<const xAOD::TruthParticle*> F = Intersection(t_map, g_J); 
        if (F.size() != 0 ){ Tmp_Index.push_back(i); }
      }
      if (Tmp_Index.size() != 0 ){ Tmp_Index.push_back(-1); }
      m_jet_topIndex.push_back( Tmp_Index );

      for (const xAOD::TruthParticle* C : g_J)
      {
        FillVector(C, &m_jet_children_pt, 
            &m_jet_children_e, &m_jet_children_phi, 
            &m_jet_children_eta, &m_jet_children_charge, 
            &m_jet_children_pdgid);
        m_jet_children_index.push_back(j); 
      }
    }
  
    // Record the truthjet constituents and record any top contributions
    for (unsigned int j(0); j < m_truthjets -> size(); j++)
    {
      std::vector<const xAOD::TruthParticle*> g_J = (*m_truthjets)[j] -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons");
      
      std::vector<int> Tmp_Index; 
      for (unsigned int i(0); i < Tops_.size(); i++)
      {
        const xAOD::TruthParticle* T = Tops_[i]; 
        std::vector<const xAOD::TruthParticle*> t_map; 
        std::vector<int> t_index; 

        GetPath(T, 0, &t_map, &t_index);
        std::vector<const xAOD::TruthParticle*> F = Intersection(t_map, g_J); 
        if (F.size() != 0 ){ Tmp_Index.push_back(i); }
      }
      if (Tmp_Index.size() != 0 ){ Tmp_Index.push_back(-1); }
      m_truthjet_topIndex.push_back( Tmp_Index );
      
      for (const xAOD::TruthParticle* C : g_J)
      {
        FillVector(C, &m_truthjet_children_pt, 
            &m_truthjet_children_e, &m_truthjet_children_phi, 
            &m_truthjet_children_eta, &m_truthjet_children_charge, 
            &m_truthjet_children_pdgid);
        m_truthjet_children_index.push_back(j); 
      }
      
      m_truthjet_pt.push_back((*m_truthjets)[j] -> pt()); 
      m_truthjet_e.push_back((*m_truthjets)[j] -> e()); 
      m_truthjet_eta.push_back((*m_truthjets)[j] -> eta()); 
      m_truthjet_phi.push_back((*m_truthjets)[j] -> phi()); 
      m_truthjet_pdgid.push_back((float)(*m_truthjets)[j] -> auxdata<int>("PartonTruthLabelID")); 
    }


    top::EventSaverFlatNtuple::saveEvent(event); 
  }


}

