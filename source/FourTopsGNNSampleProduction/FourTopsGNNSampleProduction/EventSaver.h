#ifndef FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVER_H
#define FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVER_H

#include "TopAnalysis/EventSaverFlatNtuple.h"
#include "TopPartons/PartonHistory.h"
#include "xAODTruth/TruthParticle.h"

typedef std::vector<float> _fvec; 
typedef std::vector<int> _ivec;
typedef std::vector<_fvec> __fvec; 
typedef std::vector<_ivec> __ivec; 

namespace top
{
  class EventSaver : public top::EventSaverFlatNtuple
  {
    public:
      EventSaver(); 
      virtual ~EventSaver() {}
      virtual void initialize(std::shared_ptr<top::TopConfig> config,
                              TFile* file, 
                              const std::vector<std::string>& extraBranches)
                              override; 

      virtual StatusCode initialize() override { return StatusCode::SUCCESS; }
      virtual void saveEvent(const top::Event& event) override; 

    private:
      TFile* F;
      ClassDefOverride(top::EventSaver, 0); 
      
      float m_genFilHT; 
      bool LargeFiles = true; 

      // Collect truth jets
      _ivec m_truthjets_index; 
      _fvec m_truthjets_pt; 
      _fvec m_truthjets_eta; 
      _fvec m_truthjets_phi; 
      _fvec m_truthjets_e; 
      _ivec m_truthjets_btagged; 
      _ivec m_truthjets_topquarkcount; 
      _ivec m_truthjets_wbosoncount; 
      __ivec m_truthjets_TopIndex; 

      // Collect jets 
      _ivec m_jets_index; 
      __ivec m_jets_TopIndex; 

      // Truth Tops in Sample 
      _fvec m_top_pt; 
      _fvec m_top_e; 
      _fvec m_top_eta; 
      _fvec m_top_phi; 
      _fvec m_top_charge; 
      
      _ivec m_top_pdgid; 
      _ivec m_top_index; 
      _ivec m_top_status; 
      _ivec m_top_FromRes; 
      
      // Truth Children in sample
      __fvec m_children_pt; 
      __fvec m_children_e; 
      __fvec m_children_eta; 
      __fvec m_children_phi; 
      __fvec m_children_charge; 
      
      __ivec m_children_pdgid; 
      __ivec m_children_index; 
      __ivec m_children_TopIndex;

      // Truth Jet Partons
      _ivec m_TJparton_index; 
      _ivec m_TJparton_TruthJetIndex; 
      __ivec m_TJparton_ChildIndex; 
      _fvec m_TJparton_pt; 
      _fvec m_TJparton_eta; 
      _fvec m_TJparton_phi; 
      _fvec m_TJparton_e; 

      _fvec m_TJparton_charge; 
      _fvec m_TJparton_pdgid; 

      // Jet Partons
      _ivec m_Jparton_index; 
      _ivec m_Jparton_JetIndex; 
      __ivec m_Jparton_ChildIndex; 
      _fvec m_Jparton_pt; 
      _fvec m_Jparton_eta; 
      _fvec m_Jparton_phi; 
      _fvec m_Jparton_e; 

      _fvec m_Jparton_charge; 
      _fvec m_Jparton_pdgid; 

      void ClearVectors()
      {
        m_genFilHT = -99; 

        // Collect truth jets
        m_truthjets_index.clear(); 
        m_truthjets_pt.clear(); 
        m_truthjets_eta.clear(); 
        m_truthjets_phi.clear(); 
        m_truthjets_e.clear(); 
        m_truthjets_btagged.clear(); 
        m_truthjets_topquarkcount.clear(); 
        m_truthjets_wbosoncount.clear(); 
        m_truthjets_TopIndex.clear(); 

        // Collect jets 
        m_jets_index.clear(); 
        m_jets_TopIndex.clear(); 

        // Truth Tops in Sample 
        m_top_pt.clear(); 
        m_top_e.clear(); 
        m_top_eta.clear(); 
        m_top_phi.clear(); 
        m_top_charge.clear(); 
        
        m_top_pdgid.clear(); 
        m_top_index.clear(); 
        m_top_FromRes.clear(); 
        m_top_status.clear(); 
        
        // Truth Children in sample
        m_children_pt.clear(); 
        m_children_e.clear(); 
        m_children_eta.clear(); 
        m_children_phi.clear(); 
        m_children_charge.clear(); 
        
        m_children_pdgid.clear(); 
        m_children_index.clear(); 
        m_children_TopIndex.clear();

        // Truth Jet Partons
        m_TJparton_index.clear(); 
        m_TJparton_TruthJetIndex.clear(); 
        m_TJparton_ChildIndex.clear(); 
        m_TJparton_pt.clear(); 
        m_TJparton_eta.clear(); 
        m_TJparton_phi.clear(); 
        m_TJparton_e.clear(); 

        m_TJparton_charge.clear(); 
        m_TJparton_pdgid.clear(); 

        // Jet Partons
        m_Jparton_index.clear(); 
        m_Jparton_JetIndex.clear(); 
        m_Jparton_ChildIndex.clear(); 
        m_Jparton_pt.clear(); 
        m_Jparton_eta.clear(); 
        m_Jparton_phi.clear(); 
        m_Jparton_e.clear(); 

        m_Jparton_charge.clear(); 
        m_Jparton_pdgid.clear(); 

      }

      void FillBranches()
      {
        for (auto systematicTree : treeManagers())
        {


          // Collect truth jets
          systematicTree -> makeOutputVariable(m_truthjets_index, "truthjets_index"); 
          systematicTree -> makeOutputVariable(m_truthjets_pt, "truthjets_pt"); 
          systematicTree -> makeOutputVariable(m_truthjets_eta, "truthjets_eta"); 
          systematicTree -> makeOutputVariable(m_truthjets_phi, "truthjets_phi"); 
          systematicTree -> makeOutputVariable(m_truthjets_e, "truthjets_e"); 
          systematicTree -> makeOutputVariable(m_truthjets_btagged, "truthjets_btagged"); 
          systematicTree -> makeOutputVariable(m_truthjets_topquarkcount, "truthjets_topquarkcount"); 
          systematicTree -> makeOutputVariable(m_truthjets_wbosoncount, "truthjets_wbosoncount"); 
          systematicTree -> makeOutputVariable(m_truthjets_TopIndex, "truthjets_TopIndex"); 

          // Collect jets 
          systematicTree -> makeOutputVariable(m_jets_index, "jets_index"); 
          systematicTree -> makeOutputVariable(m_jets_TopIndex, "jets_TopIndex"); 

          // Truth Tops in Sample 
          systematicTree -> makeOutputVariable(m_top_index, "top_index"); 
          systematicTree -> makeOutputVariable(m_top_pt, "top_pt"); 
          systematicTree -> makeOutputVariable(m_top_e, "top_e"); 
          systematicTree -> makeOutputVariable(m_top_eta, "top_eta"); 
          systematicTree -> makeOutputVariable(m_top_phi, "top_phi"); 
          systematicTree -> makeOutputVariable(m_top_charge, "top_charge");
          
          systematicTree -> makeOutputVariable(m_top_pdgid, "top_pdgid"); 
          systematicTree -> makeOutputVariable(m_top_FromRes, "top_FromRes");
          systematicTree -> makeOutputVariable(m_top_status, "top_status");
          
          // Truth Children in sample
          systematicTree -> makeOutputVariable(m_children_index, "children_index"); 
          systematicTree -> makeOutputVariable(m_children_pt, "children_pt"); 
          systematicTree -> makeOutputVariable(m_children_e, "children_e"); 
          systematicTree -> makeOutputVariable(m_children_eta, "children_eta"); 
          systematicTree -> makeOutputVariable(m_children_phi, "children_phi"); 
          systematicTree -> makeOutputVariable(m_children_charge, "children_charge"); 
          
          systematicTree -> makeOutputVariable(m_children_pdgid, "children_pdgid"); 
          systematicTree -> makeOutputVariable(m_children_TopIndex, "children_TopIndex");

          // Truth Jet Partons
          systematicTree -> makeOutputVariable(m_TJparton_index, "TJparton_index"); 
          systematicTree -> makeOutputVariable(m_TJparton_TruthJetIndex, "TJparton_TruthJetIndex"); 
          systematicTree -> makeOutputVariable(m_TJparton_ChildIndex, "TJparton_ChildIndex"); 
          systematicTree -> makeOutputVariable(m_TJparton_pt, "TJparton_pt"); 
          systematicTree -> makeOutputVariable(m_TJparton_eta, "TJparton_eta"); 
          systematicTree -> makeOutputVariable(m_TJparton_phi, "TJparton_phi"); 
          systematicTree -> makeOutputVariable(m_TJparton_e, "TJparton_e"); 

          systematicTree -> makeOutputVariable(m_TJparton_charge, "TJparton_charge"); 
          systematicTree -> makeOutputVariable(m_TJparton_pdgid, "TJparton_pdgid"); 

          // Jet Partons
          systematicTree -> makeOutputVariable(m_Jparton_index, "Jparton_index"); 
          systematicTree -> makeOutputVariable(m_Jparton_JetIndex, "Jparton_JetIndex"); 
          systematicTree -> makeOutputVariable(m_Jparton_ChildIndex, "Jparton_ChildIndex"); 
          systematicTree -> makeOutputVariable(m_Jparton_pt, "Jparton_pt"); 
          systematicTree -> makeOutputVariable(m_Jparton_eta, "Jparton_eta"); 
          systematicTree -> makeOutputVariable(m_Jparton_phi, "Jparton_phi"); 
          systematicTree -> makeOutputVariable(m_Jparton_e, "Jparton_e"); 

          systematicTree -> makeOutputVariable(m_Jparton_charge, "Jparton_charge"); 
          systematicTree -> makeOutputVariable(m_Jparton_pdgid, "Jparton_pdgid"); 
        }
      }
  }; 
}

#endif
