#ifndef FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVER_H
#define FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVER_H

#include "TopAnalysis/EventSaverFlatNtuple.h"
#include "TopPartons/PartonHistory.h"
#include "xAODTruth/TruthParticle.h"
#include "fstream"

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

      typedef std::vector<float> vec_f; 
      typedef std::vector<int> vec_i; 

      // Truth Tops in Sample
      std::vector<float> m_top_pt; 
      std::vector<float> m_top_e; 
      std::vector<float> m_top_eta; 
      std::vector<float> m_top_phi; 
      std::vector<float> m_top_charge; 
      std::vector<float> m_top_pdgid; 
      std::vector<int> m_top_index; 
      std::vector<int> m_top_FromRes; 

      // Children from Tops - Entire decay chain 
      std::vector<float> m_top_children_pt; 
      std::vector<float> m_top_children_e; 
      std::vector<float> m_top_children_eta; 
      std::vector<float> m_top_children_phi; 
      std::vector<float> m_top_children_charge; 
      std::vector<float> m_top_children_pdgid; 
      std::vector<int> m_top_children_index; 
      std::vector<int> m_top_children_TopIndex; 
      std::vector<std::vector<int>> m_top_children_JetIndex; 
      std::vector<std::vector<int>> m_top_children_TruthJetIndex; 
      
      // Tops contributing to Jets
      std::vector<std::vector<int>> m_jet_topIndex; 
      std::vector<std::vector<int>> m_truthjet_topIndex; 

      // Collecting the jet's constituents 
      std::vector<float> m_jet_children_pt; 
      std::vector<float> m_jet_children_e; 
      std::vector<float> m_jet_children_eta; 
      std::vector<float> m_jet_children_phi; 
      std::vector<float> m_jet_children_charge; 
      std::vector<float> m_jet_children_pdgid; 
      std::vector<int> m_jet_children_index; 
 
      // Collecting the Truth jet's constituents 
      std::vector<float> m_truthjet_children_pt; 
      std::vector<float> m_truthjet_children_e; 
      std::vector<float> m_truthjet_children_eta; 
      std::vector<float> m_truthjet_children_phi; 
      std::vector<float> m_truthjet_children_charge; 
      std::vector<float> m_truthjet_children_pdgid; 
      std::vector<int> m_truthjet_children_index; 

      // Collecting the Truth jet properties
      std::vector<float> m_truthjet_pt; 
      std::vector<float> m_truthjet_e; 
      std::vector<float> m_truthjet_eta; 
      std::vector<float> m_truthjet_phi; 
      std::vector<float> m_truthjet_pdgid; 


      ClassDefOverride(top::EventSaver, 0); 
      
      void ClearVector()
      {
        m_genFilHT = -99; 

        // Truth Tops in Sample
        m_top_pt.clear();  
        m_top_e.clear();  
        m_top_eta.clear();  
        m_top_phi.clear();  
        m_top_charge.clear();  
        m_top_pdgid.clear();  
        m_top_index.clear();  
        m_top_FromRes.clear();  

        // Children from Tops - Entire decay chain 
        m_top_children_pt.clear();  
        m_top_children_e.clear();  
        m_top_children_eta.clear();  
        m_top_children_phi.clear();  
        m_top_children_charge.clear();  
        m_top_children_pdgid.clear();  
        m_top_children_index.clear();  
        m_top_children_TopIndex.clear();  
        m_top_children_JetIndex.clear();  
        m_top_children_TruthJetIndex.clear();  
        
        // Tops contributing to Jets
        m_jet_topIndex.clear();  
        m_truthjet_topIndex.clear();  

        // Collecting the jet's constituents 
        m_jet_children_pt.clear();  
        m_jet_children_e.clear();  
        m_jet_children_eta.clear();  
        m_jet_children_phi.clear();  
        m_jet_children_charge.clear();  
        m_jet_children_pdgid.clear();  
        m_jet_children_index.clear();  
 
        // Collecting the Truth jet's constituents 
        m_truthjet_children_pt.clear();  
        m_truthjet_children_e.clear();  
        m_truthjet_children_eta.clear();  
        m_truthjet_children_phi.clear();  
        m_truthjet_children_charge.clear();  
        m_truthjet_children_pdgid.clear();  
        m_truthjet_children_index.clear();  

        // Collecting the Truth jet properties
        m_truthjet_pt.clear();
        m_truthjet_e.clear();
        m_truthjet_eta.clear();
        m_truthjet_phi.clear();
        m_truthjet_pdgid.clear();
      }

      void FillBranches()
      {

        for (auto systematicTree : treeManagers())
        {


          // Truth Tops in Sample
          systematicTree -> makeOutputVariable(m_top_pt, "top_pt");  
          systematicTree -> makeOutputVariable(m_top_e, "top_e"); 
          systematicTree -> makeOutputVariable(m_top_eta, "top_eta"); 
          systematicTree -> makeOutputVariable(m_top_phi, "top_phi"); 
          systematicTree -> makeOutputVariable(m_top_charge, "top_charge"); 
          systematicTree -> makeOutputVariable(m_top_pdgid, "top_pdgid"); 
          systematicTree -> makeOutputVariable(m_top_index, "top_index"); 
          systematicTree -> makeOutputVariable(m_top_FromRes, "top_FromRes"); 

          // Children from Tops - Entire decay chain 
          systematicTree -> makeOutputVariable(m_top_children_pt, "children_pt");  
          systematicTree -> makeOutputVariable(m_top_children_e,  "children_e"); 
          systematicTree -> makeOutputVariable(m_top_children_eta,  "children_eta"); 
          systematicTree -> makeOutputVariable(m_top_children_phi,  "children_phi"); 
          systematicTree -> makeOutputVariable(m_top_children_charge,  "children_charge"); 
          systematicTree -> makeOutputVariable(m_top_children_pdgid,  "children_pdgid"); 
          systematicTree -> makeOutputVariable(m_top_children_index, "children_index"); 

          systematicTree -> makeOutputVariable(m_top_children_TopIndex,  "children_TopIndex"); 
          systematicTree -> makeOutputVariable(m_top_children_JetIndex,  "children_JetIndex"); 
          systematicTree -> makeOutputVariable(m_top_children_TruthJetIndex,  "children_TruthJetIndex"); 
          
          // Tops contributing to Jets
          systematicTree -> makeOutputVariable(m_jet_topIndex, "jet_TopIndex"); 
          systematicTree -> makeOutputVariable(m_truthjet_topIndex, "truthjet_TopIndex"); 

          // Collecting the jet's constituents 
          systematicTree -> makeOutputVariable(m_jet_children_pt, "jetChildren_pt");
          systematicTree -> makeOutputVariable(m_jet_children_e, "jetChildren_e"); 
          systematicTree -> makeOutputVariable(m_jet_children_eta, "jetChildren_eta");
          systematicTree -> makeOutputVariable(m_jet_children_phi, "jetChildren_phi");
          systematicTree -> makeOutputVariable(m_jet_children_charge, "jetChildren_charge");  
          systematicTree -> makeOutputVariable(m_jet_children_pdgid, "jetChildren_pdgid");
          systematicTree -> makeOutputVariable(m_jet_children_index, "jetChildren_index");
 
          // Collecting the Truth jet's constituents 
          systematicTree -> makeOutputVariable(m_truthjet_children_pt, "truthjetChildren_pt");
          systematicTree -> makeOutputVariable(m_truthjet_children_e, "truthjetChildren_e"); 
          systematicTree -> makeOutputVariable(m_truthjet_children_eta, "truthjetChildren_eta");
          systematicTree -> makeOutputVariable(m_truthjet_children_phi, "truthjetChildren_phi");
          systematicTree -> makeOutputVariable(m_truthjet_children_charge, "truthjetChildren_charge");  
          systematicTree -> makeOutputVariable(m_truthjet_children_pdgid, "truthjetChildren_pdgid");
          systematicTree -> makeOutputVariable(m_truthjet_children_index, "truthjetChildren_index");


          // Collecting the Truth jet properties
          systematicTree -> makeOutputVariable(m_truthjet_pt, "truthjet_pt");
          systematicTree -> makeOutputVariable(m_truthjet_e, "truthjet_e");
          systematicTree -> makeOutputVariable(m_truthjet_eta, "truthjet_eta");
          systematicTree -> makeOutputVariable(m_truthjet_phi, "truthjet_phi");
          systematicTree -> makeOutputVariable(m_truthjet_pdgid, "truthjet_pdgid");
        }
      }


      //void DumpLog(TString text)
      //{
      //  std::ofstream print;
      //  print.open("log.txt", std::ios_base::app); 
      //  print << text + "\n";
      //}
  }; 
}

#endif
