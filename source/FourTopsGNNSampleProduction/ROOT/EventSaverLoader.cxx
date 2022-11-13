#include "FourTopsGNNSampleProduction/EventSaverLoader.h"
#include "TopConfiguration/TopConfig.h"
#include <iostream>
#include "TFile.h"

namespace top
{
  top::EventSelectorBase* FourTopsGNNSampleProductionLoader::initTool(const std::string& name,
                                                                         const std::string& line, 
                                                                         TFile* outputFile, 
                                                                         std::shared_ptr<top::TopConfig> config, 
                                                                         EL::Worker* wk) 
  {
    return nullptr; 
  }
}
