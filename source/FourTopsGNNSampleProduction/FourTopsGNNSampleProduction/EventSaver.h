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

      // Truth Tops in Sample 
      _fvec m_top_pt; 
      _fvec m_top_e; 
      _fvec m_top_eta; 
      _fvec m_top_phi; 

      _ivec m_top_charge; 
      _ivec m_top_pdgid; 
      _ivec m_top_index; 
      _ivec m_top_FromRes; 
      
      // Truth Children in sample
      __fvec m_children_pt; 
      __fvec m_children_e; 
      __fvec m_children_eta; 
      __fvec m_children_phi; 

      __ivec m_children_charge; 
      __ivec m_children_pdgid; 
      __ivec m_children_TopIndex; 
     
      // Truth Jets in Sample
      _fvec m_truthjets_pt; 
      _fvec m_truthjets_e; 
      _fvec m_truthjets_eta; 
      _fvec m_truthjets_phi; 
      __ivec m_truthjets_TopIndex;

      // Collect the partons matched to the children of the decay chain
      __fvec m_truJparton_pt; 
      __fvec m_truJparton_e; 
      __fvec m_truJparton_eta; 
      __fvec m_truJparton_phi;
      __ivec m_truJparton_charge; 
      __ivec m_truJparton_pdgid; 
      __ivec m_truJparton_ChildIndex; 

      // Jets in Sample
      __ivec m_jets_TopIndex;

      // Collect the partons matched to the children of the decay chain
      __fvec m_Jparton_pt; 
      __fvec m_Jparton_e; 
      __fvec m_Jparton_eta; 
      __fvec m_Jparton_phi;
      __ivec m_Jparton_charge; 
      __ivec m_Jparton_pdgid; 
      __ivec m_Jparton_ChildIndex; 

      void ClearVectors()
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
      
        // Truth Children in sample
        m_children_pt.clear(); 
        m_children_e.clear(); 
        m_children_eta.clear(); 
        m_children_phi.clear(); 
        m_children_charge.clear(); 
        m_children_pdgid.clear(); 
        m_children_TopIndex.clear(); 

        // Truth Jets in Sample
        m_truthjets_pt.clear(); 
        m_truthjets_e.clear(); 
        m_truthjets_eta.clear(); 
        m_truthjets_phi.clear(); 
        m_truthjets_TopIndex.clear();
  
        // Collect the partons matched to the children of the decay chain
        m_truJparton_pt.clear(); 
        m_truJparton_e.clear(); 
        m_truJparton_eta.clear(); 
        m_truJparton_phi.clear();
        m_truJparton_charge.clear(); 
        m_truJparton_pdgid.clear(); 
        m_truJparton_ChildIndex.clear(); 
  
        // Jets in Sample
        m_jets_TopIndex.clear();
  
        // Collect the partons matched to the children of the decay chain
        m_Jparton_pt.clear(); 
        m_Jparton_e.clear(); 
        m_Jparton_eta.clear(); 
        m_Jparton_phi.clear();
        m_Jparton_charge.clear(); 
        m_Jparton_pdgid.clear(); 
        m_Jparton_ChildIndex.clear(); 
      }

      void FillBranches()
      {
        for (auto systematicTree : treeManagers())
        {
          systematicTree -> makeOutputVariable(m_top_pt,  "top_pt"); 
          systematicTree -> makeOutputVariable(m_top_e,   "top_e"); 
          systematicTree -> makeOutputVariable(m_top_eta, "top_eta"); 
          systematicTree -> makeOutputVariable(m_top_phi, "top_phi"); 
          systematicTree -> makeOutputVariable(m_top_charge,  "top_charge"); 
          systematicTree -> makeOutputVariable(m_top_pdgid,   "top_pdgid"); 
          systematicTree -> makeOutputVariable(m_top_index,   "top_index"); 
          systematicTree -> makeOutputVariable(m_top_FromRes, "top_FromRes"); 

          systematicTree -> makeOutputVariable(m_children_pt,     "children_pt"); 
          systematicTree -> makeOutputVariable(m_children_e,      "children_e"); 
          systematicTree -> makeOutputVariable(m_children_eta,    "children_eta"); 
          systematicTree -> makeOutputVariable(m_children_phi,    "children_phi"); 
          systematicTree -> makeOutputVariable(m_children_charge, "children_charge"); 
          systematicTree -> makeOutputVariable(m_children_pdgid,  "children_pdgid"); 
          systematicTree -> makeOutputVariable(m_children_TopIndex, "children_TopIndex"); 

          systematicTree -> makeOutputVariable(m_truthjets_pt,       "truthjet_pt"); 
          systematicTree -> makeOutputVariable(m_truthjets_e,        "truthjet_e"); 
          systematicTree -> makeOutputVariable(m_truthjets_eta,      "truthjet_eta"); 
          systematicTree -> makeOutputVariable(m_truthjets_phi,      "truthjet_phi"); 
          systematicTree -> makeOutputVariable(m_truthjets_TopIndex, "truthjet_TopIndex"); 

          systematicTree -> makeOutputVariable(m_truJparton_pt,     "truJparton_pt"); 
          systematicTree -> makeOutputVariable(m_truJparton_e,      "truJparton_e"); 
          systematicTree -> makeOutputVariable(m_truJparton_eta,    "truJparton_eta"); 
          systematicTree -> makeOutputVariable(m_truJparton_phi,    "truJparton_phi"); 
          systematicTree -> makeOutputVariable(m_truJparton_charge, "truJparton_charge"); 
          systematicTree -> makeOutputVariable(m_truJparton_pdgid,  "truJparton_pdgid"); 
          systematicTree -> makeOutputVariable(m_truJparton_ChildIndex, "truJparton_ChildIndex"); 

          systematicTree -> makeOutputVariable(m_Jparton_pt,     "Jparton_pt"); 
          systematicTree -> makeOutputVariable(m_Jparton_e,      "Jparton_e"); 
          systematicTree -> makeOutputVariable(m_Jparton_eta,    "Jparton_eta"); 
          systematicTree -> makeOutputVariable(m_Jparton_phi,    "Jparton_phi"); 
          systematicTree -> makeOutputVariable(m_Jparton_charge, "Jparton_charge"); 
          systematicTree -> makeOutputVariable(m_Jparton_pdgid,  "Jparton_pdgid"); 
          systematicTree -> makeOutputVariable(m_Jparton_ChildIndex, "Jparton_ChildIndex"); 

          systematicTree -> makeOutputVariable(m_jets_TopIndex, "jet_TopIndex"); 
        }
      }
  }; 
}

#endif
