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
      std::vector<int> m_Gtop_index; 
      std::vector<int> m_GtopFromRes; 
      std::vector<int> m_topsPreFSR_status; 

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
      std::vector<int> m_top_index; 
      
      std::vector<std::vector<int>> m_jet_map_Ghost;
      std::vector<std::vector<int>> m_jet_map_tops;

      ClassDefOverride(top::EventSaver, 0); 
      
      void ClearVector()
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
        m_jet_map_Ghost.clear();  
        m_jet_map_tops.clear();

      }

      void FillBranches()
      {

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

          systematicTree -> makeOutputVariable(m_jet_map_Ghost, "jet_map_Ghost");  
          systematicTree -> makeOutputVariable(m_jet_map_tops, "jet_map_Gtops");  
        }
      }
  }; 
}

#endif
