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

  	void EventSaver::initialize(
				std::shared_ptr<top::TopConfig> config, 
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
    		if (event.m_info -> isAvailable<float>("GenFilHT"))
		{
			m_genFilHT = event.m_info -> auxdataConst<float>("GenFilHT");
		}
 
    		// ============================= (Truth) Jet Stuff =======================================//
    		// Collect all the truth jets in this event.
    		const xAOD::JetContainer* m_truthjets{nullptr}; 
    		if (!evtStore() -> retrieve(m_truthjets, "AntiKt4TruthWZJets").isSuccess()){return;}
    		if (!m_truthjets){return;}
  
    		for (unsigned int tj(0); tj < m_truthjets -> size(); ++tj)
    		{
      			const xAOD::Jet_v1* trujet = m_truthjets -> at(tj); 
      			m_truthjets_index.push_back(tj);  
      			m_truthjets_pt.push_back(trujet -> pt());  
      			m_truthjets_eta.push_back(trujet -> eta()); 
      			m_truthjets_phi.push_back(trujet -> phi()); 
      			m_truthjets_e.push_back(trujet -> e());

      			int count = -99; 
      			if (trujet -> isAvailable<int>("HadronConeExclTruthLabelID"))
      			{
        			trujet -> getAttribute("HadronConeExclTruthLabelID", count); 
      			}
      			m_truthjets_btagged.push_back(count);
      			m_truthjets_topquarkcount.push_back(trujet -> auxdata<int>("GhostTQuarksFinalCount")); 
      			m_truthjets_wbosoncount.push_back(trujet -> auxdata<int>("GhostWBosonsCount"));
      			m_truthjets_TopIndex.push_back({-1}); 
    		}

		// Collect all the jets in this event.
	    	// The remaining kinematics are automatically added by AnalysisTop...
    		int _ji = 0; 
    		for (unsigned int j(0); j < event.m_jets.size(); ++j)
    		{
    			m_jets_index.push_back(_ji); 
    			m_jets_TopIndex.push_back({-1});
    			++_ji; 
    		}
    		const xAOD::JetContainer m_jets = event.m_jets; 
    		// ============================= End (Truth) Jet Stuff =======================================//
    		
    		
    		// ============================= Truth Top Stuff ===============================//  
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
    		std::vector<const xAOD::TruthParticle*> FinalTops; 
    		int _ti = 0;
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
    		  	m_top_status.push_back(top -> status()); 
    		  	m_top_FromRes.push_back(ParticleID::isResonance(top)); 
    		  	FinalTops.push_back(top); 

    		  	++_ti; 
    		}
    		// ============================= End Truth Top Stuff ===============================//
   
    		// ============================= Children Stuff ===============================//
    		// Iterate over all found tops and find the ones which are the final state tops, i.e. where the children are non-tops
    		int _ci = 0; 
    		std::vector<int> Children_Index; 
    		std::vector<const xAOD::TruthParticle*> Children_Vector; 
    		for (unsigned int ti(0); ti < FinalTops.size(); ++ti)
    		{
    		  	const xAOD::TruthParticle* top = FinalTops[ti]; 
    		  	std::vector<const xAOD::TruthParticle*> Children = ParticleID::FindChildren(top);  
    		  	std::vector<float> __pt, __e, __eta, __phi, __ch; 
    		  	std::vector<int> __pdg, __ti, __ci; 
    		  	
    		  	for (const xAOD::TruthParticle* c : Children)
    		  	{
    		  	  	__pt.push_back(c -> pt()); 
    		  	  	__e.push_back(c -> e()); 
    		  	  	__eta.push_back(c -> eta()); 
    		  	  	__phi.push_back(c -> phi()); 
    		  	  	
    		  	  	__ch.push_back(c -> charge());
    		  	  	__pdg.push_back(c -> pdgId()); 
    		  	 
    		  	  	__ti.push_back(m_top_index[ti]); 
    		  	  	__ci.push_back(_ci); 
    		  	  	Children_Vector.push_back(c);
    		  	  	Children_Index.push_back(_ci); 

    		  	  	++_ci;  
    		  	} 
    		  	
    		  	m_children_pt.push_back(__pt); 
    		  	m_children_e.push_back(__e); 
    		  	m_children_eta.push_back(__eta); 
    		  	m_children_phi.push_back(__phi); 
    		  	m_children_charge.push_back(__ch); 
    		  	
    		  	m_children_pdgid.push_back(__pdg); 
    		  	m_children_index.push_back(__ci); 
    		  	m_children_TopIndex.push_back(__ti); 
    		} 
    		// ============================= End Children Stuff =============================== //


    		MatchingJetsToTops(
    		    		FinalTops, m_truthjets, 
    		    		&m_truthjets_TopIndex, &m_top_index
    		); 

    		MatchingJetsToTops(
    		    		FinalTops, &m_jets, 
    		    		&m_jets_TopIndex, &m_top_index
    		); 

    		if (!LargeFiles && !DecayChainFiles)
    		{
    			top::EventSaverFlatNtuple::saveEvent(event); 
    			return; 
    		}
    		
    		if (LargeFiles){ 
	        	MatchingJets(
    		    		Children_Vector, m_truthjets, 
    		    		Children_Index, m_truthjets_index, 
    		    		&m_TJparton_ChildIndex, &m_TJparton_index, &m_TJparton_TruthJetIndex, 
    		    		&m_TJparton_pt, &m_TJparton_eta, &m_TJparton_phi, &m_TJparton_e, 
    		    		&m_TJparton_charge, &m_TJparton_pdgid
                        ); 

    		   	MatchingJets(
    		    		Children_Vector, &m_jets, 
    		    		Children_Index, m_jets_index, 
    		    		&m_Jparton_ChildIndex, &m_Jparton_index, &m_Jparton_JetIndex, 
    		    		&m_Jparton_pt, &m_Jparton_eta, &m_Jparton_phi, &m_Jparton_e, 
    		    		&m_Jparton_charge, &m_Jparton_pdgid
    		        );
    		}

    		if (DecayChainFiles){
    			for (unsigned int i(0); i < FinalTops.size(); ++i){
    		       		const xAOD::TruthParticle* _top = FinalTops[i];
    		       		std::vector<const xAOD::TruthParticle*> ParticleVector;  
    		       		std::vector<int> ParticleDecayIndex; 
    		       		ParticleID::GetPath(_top, 0, &ParticleVector, &ParticleDecayIndex); 
				for (unsigned int j(0); j < ParticleVector.size(); ++j){
					// Here we want to capture the top index!
					m_DCTopIndex.push_back(i); 
					m_DCDecayIndex.push_back(ParticleDecayIndex[j]); 
					m_DC_pt.push_back(ParticleVector[j] -> pt()); 
					m_DC_eta.push_back(ParticleVector[j] -> eta()); 
					m_DC_phi.push_back(ParticleVector[j] -> phi()); 
					m_DC_e.push_back(ParticleVector[j] -> e()); 

					m_DC_charge.push_back(ParticleVector[j] -> charge()); 
					m_DC_pdgid.push_back(ParticleVector[j] -> pdgId()); 
				}
    			}
    		}
    		top::EventSaverFlatNtuple::saveEvent(event); 
	}
}
