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

namespace top {
  EventSaver::EventSaver(){} 

  void EventSaver::initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches) 
  {
    top::EventSaverFlatNtuple::initialize(config, file, extraBranches); 

    for (auto systematicTree : treeManagers()) {}
    F = file; 
  }

  void EventSaver::saveEvent(const top::Event& event)
  {
   
    std::cout << " \n------ Event ------ " << std::endl;
    m_genFilHT = -99; 
    if (!event.m_info -> eventType(xAOD::EventInfo::IS_SIMULATION)){return;}
    if (event.m_info -> isAvailable<float>("GenFiltHT"))
    {
      m_genFilHT = event.m_info -> auxdataConst<float>("GenFiltHT"); 
    }
    const xAOD::JetContainer* m_truthjets{nullptr}; 
    if (!evtStore() -> retrieve(m_truthjets, "AntiKt4TruthWZJets").isSuccess()){return;}
    if (m_truthjets)
    {
      int k = 1;
      std::vector<const xAOD::TruthParticle*> AllParents; 
      for (const auto &jet : *m_truthjets)
      {
        //if ( jet -> pt() < PT_Cut || fabs(jet -> eta()) > ETA_Cut){continue;}
        int truth_flavour = jet -> auxdata<int>("PartonTruthLabelID");
        std::cout << k << ". ++> "  << truth_flavour << std::endl;
        
        std::vector<const xAOD::TruthParticle*> ghost_P = jet -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
        AllParents.insert(AllParents.end(), ghost_P.begin(), ghost_P.end());  
        k++; 
      }
      
      // Merge all the ghost particles and get a common parent i.e. go to origin particles
      std::vector<const xAOD::TruthParticle*> Out = MergeParents(AllParents);

      // Now go down the decay chain and parents which produce tops
      std::vector<const xAOD::TruthParticle*> TopsPreFSR_ = TopsPreFSR(Out); 
      for (const xAOD::TruthParticle* T : TopsPreFSR_)
      {
        std::cout << "++++> " << T -> pdgId() << std::endl;
      }

      // Find tops before full decay, i.e. they have gone through FSR
      std::vector<const xAOD::TruthParticle*> TopsPostFSR_; 
      for (const xAOD::TruthParticle* T : TopsPreFSR_)
      {
        const xAOD::TruthParticle* P = TopsPostFSR(T);
        TopsPostFSR_.push_back(P); 
        std::cout << "++---> " << P -> pdgId() << " " << P -> nChildren() << std::endl;
        for (unsigned int i(0); i < P -> nChildren(); i++)
        {
          std::cout << "==> " << P -> child(i) -> pdgId() << std::endl; 
        }
      }
      
      // Now match the tops by following the decay chain and match them to truth jets.
       



      




      std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 

    }

    //std::vector<const xAOD::TruthParticle*> ParticleVector; 
    //std::vector<int> ParticleMap; 
    //const xAOD::TruthParticleContainer* TPC = event.m_truth; 
    //for (const xAOD::TruthParticle* T : *TPC)
    //{

    //  if (ParticleID::isGEANT(T -> barcode())){break;}
    //  if (!IsFinalTop(T)){continue;} // Check that the given top decays into quarks etc.

    //  GetPath(T, 0, &ParticleVector, &ParticleMap); 
    //  std::cout << " ||||> " << T -> pdgId() << std::endl;
    //}
    //
    //int k = 1; 
    //for (unsigned int i(0); i < ParticleVector.size(); i++)
    //{

    //  if (ParticleMap[i] > 5){continue;}
    //  std::string p = ""; p+=(std::to_string(k)); p += ("."); 
    //  for (int l(0); l < ParticleMap[i]; l++){p+=("-"); }
    //  p += "> ";  
    //  if (ParticleMap[i] != 0 && ParticleMap[i] < 5 )
    //  {
    //    k++; 
    //    std::cout << p << ParticleVector[i] -> pdgId() << " " << ParticleVector[i] -> status()<< std::endl;
    //  }
    //  else if (ParticleMap[i] == 0) {std::cout << ParticleVector[i] -> pdgId() << " " << ParticleVector[i] -> status()<< std::endl;}




    //}




    top::EventSaverFlatNtuple::saveEvent(event); 
  }


}

