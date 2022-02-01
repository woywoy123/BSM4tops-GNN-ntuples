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

      ClassDefOverride(top::EventSaver, 0); 
  }; 
}

#endif
