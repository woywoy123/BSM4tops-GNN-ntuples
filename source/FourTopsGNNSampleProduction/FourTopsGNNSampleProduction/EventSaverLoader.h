#ifndef FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVERLOADER_H
#define FOURTOPSGNNSAMPLEPRODUCTION_EVENTSAVERLOADER_H

#include "TopEventSelectionTools/ToolLoaderBase.h"

namespace top
{
  class FourTopsGNNSampleProductionLoader : public ToolLoaderBase
  {
    public:
      top::EventSelectorBase* initTool(const std::string& name, 
                                       const std::string& line, 
                                       TFile* outputFile, 
                                       std::shared_ptr<top::TopConfig> config, 
                                       EL::Worker* wk = nullptr); 
      ClassDef(top::FourTopsGNNSampleProductionLoader, 0); 
  }; 

}


#endif
