#include "FourTopsGNNSampleProduction/HelperFunctions.h"

std::vector<Truth_> UniqueObject(std::vector<Truth_> Particles)
{
  std::vector<Truth_> Out;
  for (Truth_ T : Particles)
  {
    if (!(std::find(Out.begin(), Out.end(), T) != Out.end())){ Out.push_back(T); }
  }
  return Out; 
}

Truth_ GetDecayTip(Truth_ part, std::vector<Truth_> inpt)
{
  for (unsigned int i(0); i < part -> nChildren(); i++)
  {
    Truth_ c = part -> child(i); 
    
    if (!c){ continue; }
    if (std::find(inpt.begin(), inpt.end(), c) != inpt.end()){ return GetDecayTip(c, inpt); }
  }
  return part;
}


std::vector<Truth_> Intersection(std::vector<Truth_> V1, std::vector<Truth_> V2)
{
  std::vector<Truth_> TMP; 
  for (Truth_ t_c : V1)
  {
    for (Truth_ t_p : V2)
    {
      if (t_c == t_p){TMP.push_back(t_c); break;}
    }
  }
  TMP = UniqueObject(TMP); 
  
  // Check that the decay chain is unique and aim to get the tip of the decay
  std::vector<Truth_> output; 
  for (Truth_ c : TMP)
  { 
    Truth_ c1 = GetDecayTip(c, TMP); 
    if (c1 == c){ output.push_back(c1); }
  }
  return output;
}

int FindObject(Truth_ obj, std::vector<Truth_> V1)
{
  int index = -1; 
  for (unsigned int i(0); i < V1.size(); i++)
  {
    if (V1.at(i) == obj){ index = i; break; }
  }
  return index; 
}
