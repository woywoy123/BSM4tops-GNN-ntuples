#include <FourTopsGNNSampleProduction/TruthAnalysis.h>
#include <FourTopsGNNSampleProduction/ParticleID.h>
#include <thread>
#include <chrono>
#include <algorithm>

// ====================================================== //
std::vector<Truth_> MergeParents(std::vector<Truth_> Particles)
{
  std::vector<Truth_> Output; 
  
  for (Truth_ T_j : Particles)
  {
    Truth_ p = GetParent(T_j);
    // Check if the particle object is within the Output vector. 
    // Parents share the same memory address
    if (!(std::find(Output.begin(), Output.end(), p) != Output.end())){ Output.push_back(p); }
  }

  return Output;
}

// ====================================================== //
std::vector<Truth_> TopsPreFSR(std::vector<Truth_> Particles)
{
  std::vector<Truth_> TMP_T;
  std::vector<Truth_> TMP_O; 
  for (const xAOD::TruthParticle* T : Particles)
  {
    if (!T){continue;}
    if (ParticleID::isTop(T -> pdgId())){ TMP_T.push_back(T); continue;}
    for (unsigned int i(0); i < T -> nChildren(); i++)
    {
      Truth_ cand = T -> child(i); 
      if (!cand){continue;}
      if (ParticleID::isBSMZ(cand -> pdgId()))
      {
        std::vector<Truth_> bsmZ = TopsPreFSR({cand}); 
        TMP_T.insert(TMP_T.end(), bsmZ.begin(), bsmZ.end());
      }
      if (ParticleID::isTop(cand -> pdgId())){ TMP_T.push_back(cand); continue;}
      TMP_O.push_back(cand);
    }
  }

  // Make sure they are unique objects 
  std::vector<Truth_> Out_T = UniqueObject(TMP_T);
  std::vector<Truth_> Out_O = UniqueObject(TMP_O); 

  if (Out_O.size() != 0)
  {
    Out_O.insert( Out_O.end(), Out_T.begin(), Out_T.end() ); 
    return TopsPreFSR(Out_O);
  }
  return Out_T;
}

Truth_ GetParent(Truth_ particle)
{
  //if (ParticleID::isTop(particle -> pdgId())) return particle; 
  for (unsigned int i(0); i < particle -> nParents(); i++)
  {
    Truth_ parent = particle -> parent(i);
    if (!parent){continue;}
    return GetParent(parent);
  }
  return particle; 
}

// ====================================================== //
Truth_ TopsPostFSR(Truth_ Particles)
{
  for (unsigned int i(0); i < Particles -> nChildren(); i++)
  {
    Truth_ cand = Particles -> child(i); 
    if (ParticleID::isTop(cand -> pdgId())){ return TopsPostFSR(cand); }
  }
  return Particles; 
}

// ====================================================== //
Truth_ GetPath(
    Truth_ particle, 
    int k, std::vector<Truth_>* PV, 
    std::vector<int>* PM)
{
  (*PV).push_back(particle); 
  (*PM).push_back(k); 

  k++; 
  for (unsigned int i(0); i < particle -> nChildren(); i++)
  {
    Truth_ child = particle -> child(i); 
    if (!child){continue;}
    GetPath(child, k, PV, PM);
  }
  
  return particle; 
}

// ====================================================== //
Truth_ AssureWDecay(Truth_ particle)
{
  for (unsigned int i(0); i < particle -> nChildren(); i++)
  {
    Truth_ cand = particle -> child(i); 
    if (!cand){continue;}
    if (cand -> pdgId() == particle -> pdgId() && ParticleID::isW(cand -> pdgId())){ return AssureWDecay(cand); }
  }
  return particle; 
}

// ====================================================== //
std::vector<Truth_> UniqueObject(std::vector<Truth_> Particles)
{
  std::vector<Truth_> Out;
  for (Truth_ T : Particles)
  {
    if (!(std::find(Out.begin(), Out.end(), T) != Out.end())){ Out.push_back(T); }
  }
  return Out; 
}


