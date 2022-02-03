#ifndef FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVER_H
#define FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVER_H

#include "TopAnalysis/EventSaverFlatNtuple.h"
#include "TopPartons/PartonHistory.h"

namespace top {
  class EventSaver : public top::EventSaverFlatNtuple {
    public:
      EventSaver(); 
      virtual ~EventSaver() {}
      virtual void initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches) override; 
      virtual StatusCode initialize() override { return StatusCode::SUCCESS; }
      virtual void saveEvent(const top::Event& event) override; 


    private:
      TFile* F; 
      float m_genFilHT; 
      float PT_Cut = 15000; 
      float ETA_Cut = 2.5; 

      // Reconstructed ghost tops before FSR
      std::vector<float> m_topsPreFSR_pt;
      std::vector<float> m_topsPreFSR_e;
      std::vector<float> m_topsPreFSR_eta;
      std::vector<float> m_topsPreFSR_phi;
      std::vector<int> m_topsPreFSR_charge; 

      // Reconstructed ghost tops post FSR
      std::vector<float> m_topsPostFSR_pt;
      std::vector<float> m_topsPostFSR_e;
      std::vector<float> m_topsPostFSR_eta;
      std::vector<float> m_topsPostFSR_phi;
      std::vector<int> m_topsPostFSR_charge; 


      // Children from Reconstucted gHost tops post FSR
      std::vector<std::vector<float>> m_topPostFSR_children_pt; 
      std::vector<std::vector<float>> m_topPostFSR_children_e; 
      std::vector<std::vector<float>> m_topPostFSR_children_eta; 
      std::vector<std::vector<float>> m_topPostFSR_children_phi; 
      std::vector<std::vector<int>> m_topPostFSR_children_charge; 
      std::vector<std::vector<int>> m_topPostFSR_children_pdgid; 

      // Truth jets
      std::vector<float> m_TruthJets_pt;
      std::vector<float> m_TruthJets_e;
      std::vector<float> m_TruthJets_eta;
      std::vector<float> m_TruthJets_phi;
      std::vector<float> m_TruthJets_pdgid; 
        
      // Truth jet to Ghost top mapping 
      std::vector<std::vector<int>> m_GhostTruthJetMap; 

      // Children from m_truth branch 
      std::vector<std::vector<float>> m_top_children_pt; 
      std::vector<std::vector<float>> m_top_children_e; 
      std::vector<std::vector<float>> m_top_children_eta; 
      std::vector<std::vector<float>> m_top_children_phi; 
      std::vector<std::vector<int>> m_top_children_charge; 
      std::vector<std::vector<int>> m_top_children_pdgid; 

      // tops from m_truth branch 
      std::vector<float> m_top_pt; 
      std::vector<float> m_top_e; 
      std::vector<float> m_top_eta; 
      std::vector<float> m_top_phi; 
      std::vector<int> m_top_charge; 
      std::vector<int> m_topFromRes; 


      ClassDefOverride(top::EventSaver, 0); 
  }; 
}

#endif
