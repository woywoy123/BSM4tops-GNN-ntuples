#include "FourTopsGNNSampleProduction/EventSaver.h"
#include "FourTopsGNNSampleProduction/ParticleID.h"
#include "FourTopsGNNSampleProduction/HelperFunctions.h"

// Boilerplate Event Info
#include "TopEvent/Event.h"
#include "TopEvent/EventTools.h"

// File stuff
#include "TopEventSelectionTools/TreeManager.h"
#include "TopConfiguration/TopConfig.h"

// Particle Stuff
#include "xAODTruth/TruthParticle.h"

namespace top
{
  EventSaver::EventSaver(){}

  void EventSaver::initialize(std::shared_ptr<top::TopConfig> config, 
                              TFile* file, 
                              const std::vector<std::string>& extraBranches)
  {
    top::EventSaverFlatNtuple::initialize(config, file, extraBranches); 
    FillBranches(); 
    F = file; 
  }
  
  void EventSaver::saveEvent(const top::Event& event)
  {

    ClearVectors();
    if (!event.m_info -> eventType(xAOD::EventInfo::IS_SIMULATION)){return;}
    if (event.m_info -> isAvailable<float>("GenFilHT")){m_genFilHT = event.m_info -> auxdataConst<float>("GenFilHT");}

    const xAOD::JetContainer* m_truthjets{nullptr}; 
    if (!evtStore() -> retrieve(m_truthjets, "AntiKt4TruthWZJets").isSuccess()){return;}
    if (!m_truthjets){return;}
    
    // Get the Generator Particles (usually the proton)
    const xAOD::TruthParticleContainer* TruParticle = event.m_truth; 

    // Search through the Generator Particles and find the tops just before they decay 
    std::vector<const xAOD::TruthParticle*> _Tops;
    for (const xAOD::TruthParticle* top : *TruParticle)
    {
      if (ParticleID::isGEANT(top)){break;}
      
      // Find all tops, even the ones that are still emitting Gluons
      ParticleID::FindTops(top, &_Tops);  
    }
    
    // Remove duplicate Objects
    _Tops = UniqueObject(_Tops);
    
    // Iterate over all found tops and find the ones which are the final state tops, i.e. where the children are non-tops
    int _ti = 0;
    int _citj = 0; 
    int _cij = 0; 
    for (const xAOD::TruthParticle* top : _Tops)
    {
      if (!ParticleID::isFinalStateTop(top)){continue;}
      m_top_pt.push_back(top -> pt()); 
      m_top_e.push_back(top -> e()); 
      m_top_eta.push_back(top -> eta()); 
      m_top_phi.push_back(top -> phi()); 

      m_top_charge.push_back(top -> charge()); 
      m_top_index.push_back(_ti); 
      m_top_pdgid.push_back(top -> pdgId()); 
      m_top_FromRes.push_back(ParticleID::isResonance(top)); 
    
      std::vector<const xAOD::TruthParticle*> Children = ParticleID::FindChildren(top); 
      
      std::vector<float> _pt, _e, _eta, _phi, _ch; 
      std::vector<int> _pdg, __ti;
      for (const xAOD::TruthParticle* c : Children)
      {

        _pt.push_back(c -> pt()); 
        _e.push_back(c -> e()); 
        _eta.push_back(c -> eta()); 
        _phi.push_back(c -> phi()); 
        _ch.push_back(c -> charge()); 
        
        _pdg.push_back(c -> pdgId());
        __ti.push_back( _ti ); 

      }

      m_children_pt.push_back(_pt); 
      m_children_e.push_back(_e); 
      m_children_eta.push_back(_eta); 
      m_children_phi.push_back(_phi); 

      m_children_charge.push_back(_ch); 
      m_children_pdgid.push_back(_pdg); 
      m_children_TopIndex.push_back(__ti); 
   
      // Get entire decay path of the top
      std::vector<const xAOD::TruthParticle*> _TMP; 
      ParticleID::GetDecayPath(top, &_TMP); 
      
      // Match the decay chain to the truth jets 
      std::vector<const xAOD::TruthParticle*> all_partons; 
      for (unsigned int j(0); j < m_truthjets -> size(); j++)
      {
        if (m_truthjets_TopIndex.size() < j+1){ m_truthjets_TopIndex.push_back({-1}); }

        if (m_truthjets_pt.size() < j+1)
        {
          m_truthjets_pt.push_back((*m_truthjets)[j] -> pt()); 
          m_truthjets_e.push_back((*m_truthjets)[j] -> e()); 
          m_truthjets_eta.push_back((*m_truthjets)[j] -> eta()); 
          m_truthjets_phi.push_back((*m_truthjets)[j] -> phi()); 
        }

        // Check whether any of the decay children addresses are found within the truth jets
        std::vector<const xAOD::TruthParticle*> trujetparton = (*m_truthjets)[j] -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons");
        std::vector<const xAOD::TruthParticle*> sim = Intersection(_TMP, trujetparton); 
        all_partons.insert(all_partons.end(), trujetparton.begin(), trujetparton.end()); 

        if (sim.size() != 0)
        {
          if (m_truthjets_TopIndex[j][0] == -1){ m_truthjets_TopIndex[j][0] = _ti; }
          else { m_truthjets_TopIndex[j].push_back(_ti); }
        }
      }
      
      // This is for Debugging the matching of the above. Here the truth jet partons are matched to the CHILDREN of the tops
      for (const xAOD::TruthParticle* c : Children)
      {
        if (!LargeFiles){continue;}

        std::vector<const xAOD::TruthParticle*> __TMP; 
        ParticleID::GetDecayPath(c, &__TMP); 
        __TMP = Intersection(__TMP, all_partons); 
        
        std::vector<float> __pt, __e, __eta, __phi, __ch; 
        std::vector<int> __pdg, __idx;
        for (const xAOD::TruthParticle* _c : __TMP)
        {
          __pt.push_back(_c -> pt()); 
          __e.push_back(_c -> e()); 
          __eta.push_back(_c -> eta()); 
          __phi.push_back(_c -> phi()); 
          __ch.push_back(_c -> charge()); 
          
          __pdg.push_back(_c -> pdgId()); 
          __idx.push_back( _citj ); 
        }
        m_truJparton_pt.push_back(__pt); 
        m_truJparton_e.push_back(__e); 
        m_truJparton_eta.push_back(__eta); 
        m_truJparton_phi.push_back(__phi); 

        m_truJparton_charge.push_back(__ch); 
        m_truJparton_pdgid.push_back(__pdg); 
        m_truJparton_ChildIndex.push_back(__idx); 
        
        _citj++; 
      }

      // Check whether any of the decay children addresses are found within the jets
      all_partons.clear(); 
      for (unsigned int j(0); j < event.m_jets.size(); j++)
      {
        if (m_jets_TopIndex.size() < j+1){ m_jets_TopIndex.push_back({-1}); }

        std::vector<const xAOD::TruthParticle*> jetparton = event.m_jets.at(j) -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons");
        std::vector<const xAOD::TruthParticle*> sim = Intersection(_TMP, jetparton); 
        all_partons.insert(all_partons.end(), jetparton.begin(), jetparton.end()); 
        
        if (sim.size() != 0)
        {
          if (m_jets_TopIndex[j][0] == -1){ m_jets_TopIndex[j][0] = _ti; }
          else { m_jets_TopIndex[j].push_back(_ti); }
        }
      }

      // This is for Debugging the matching of the above. Here the jet partons are matched to the CHILDREN of the tops
      for (const xAOD::TruthParticle* c : Children)
      {
        if (!LargeFiles){continue;}

        std::vector<const xAOD::TruthParticle*> __TMP; 
        ParticleID::GetDecayPath(c, &__TMP); 
        __TMP = Intersection(__TMP, all_partons); 

        std::vector<float> __pt, __e, __eta, __phi, __ch; 
        std::vector<int> __pdg, __idx;
        for (const xAOD::TruthParticle* _c : __TMP)
        {
          __pt.push_back(_c -> pt()); 
          __e.push_back(_c -> e()); 
          __eta.push_back(_c -> eta()); 
          __phi.push_back(_c -> phi()); 
          __ch.push_back(_c -> charge()); 
          
          __pdg.push_back(_c -> pdgId()); 
          __idx.push_back( _cij ); 
        }
        m_Jparton_pt.push_back(__pt); 
        m_Jparton_e.push_back(__e); 
        m_Jparton_eta.push_back(__eta); 
        m_Jparton_phi.push_back(__phi); 
        m_Jparton_charge.push_back(__ch); 
        
        m_Jparton_pdgid.push_back(__pdg); 
        m_Jparton_ChildIndex.push_back(__idx); 
        
        _cij++; 
      }

      _ti++; 
    }
    top::EventSaverFlatNtuple::saveEvent(event); 
  }
}
