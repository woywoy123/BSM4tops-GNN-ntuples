#include <FourTopsGNNSampleProduction/TruthAnalysis.h>
#include <FourTopsGNNSampleProduction/ParticleID.h>
#include <thread>
#include <chrono>
#include <algorithm>


const xAOD::TruthParticle* GetParent(const xAOD::TruthParticle* particle)
{
  //if (ParticleID::isTop(particle -> pdgId())) return particle; 
  for (unsigned int i(0); i < particle -> nParents(); i++)
  {
    const xAOD::TruthParticle* parent = particle -> parent(i);
    if (!parent){continue;}
    return GetParent(parent);
  }
  return particle; 
}

std::vector<const xAOD::TruthParticle*> MergeParents(std::vector<const xAOD::TruthParticle*> Particles)
{
  std::vector<const xAOD::TruthParticle*> Output; 
  
  for (const xAOD::TruthParticle* T_j : Particles)
  {
    const xAOD::TruthParticle* p = GetParent(T_j);
    // Check if the particle object is within the Output vector. 
    // Parents share the same memory address
    if (!(std::find(Output.begin(), Output.end(), p) != Output.end())){ Output.push_back(p); }
  }

  return Output;
}

std::vector<const xAOD::TruthParticle*> TopsPreFSR(std::vector<const xAOD::TruthParticle*> Particles)
{
  std::vector<const xAOD::TruthParticle*> Out_T;
  std::vector<const xAOD::TruthParticle*> Out_O; 
  for (const xAOD::TruthParticle* T : Particles)
  {
    for (unsigned int i(0); i < T -> nChildren(); i++)
    {
      const xAOD::TruthParticle* cand = T -> child(i); 
      if (ParticleID::isTop(cand -> pdgId())){ Out_T.push_back(cand); }
      else {Out_O.push_back(cand);}
    }
  }
  
  if (Out_T.size() != 0){ return Out_T; }
  else { return TopsPreFSR(Out_O); }
}


const xAOD::TruthParticle* TopsPostFSR(const xAOD::TruthParticle* Particles)
{
  for (unsigned int i(0); i < Particles -> nChildren(); i++)
  {
    const xAOD::TruthParticle* cand = Particles -> child(i); 
    if (ParticleID::isTop(cand -> pdgId())){ return TopsPostFSR(cand); }
  }
  return Particles; 
}








const xAOD::TruthParticle* GetPath(const xAOD::TruthParticle* particle, int k, std::vector<const xAOD::TruthParticle*>* PV, std::vector<int>* PM)
{

  (*PV).push_back(particle); 
  (*PM).push_back(k); 

  k++; 
  for (unsigned int i(0); i < particle -> nChildren(); i++)
  {
    const xAOD::TruthParticle* child = particle -> child(i); 
    if (!child){continue;}
    GetPath(child, k, PV, PM);
  }
  
  return particle; 
}

