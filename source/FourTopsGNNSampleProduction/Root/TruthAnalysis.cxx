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

std::vector<const xAOD::TruthParticle*> UniqueObject(std::vector<const xAOD::TruthParticle*> Particles)
{
  std::vector<const xAOD::TruthParticle*> Out;
  for (const xAOD::TruthParticle* T : Particles)
  {
    if (!(std::find(Out.begin(), Out.end(), T) != Out.end())){ Out.push_back(T); }
  }
  return Out; 
}

std::vector<const xAOD::TruthParticle*> TopsPreFSR(std::vector<const xAOD::TruthParticle*> Particles)
{
  std::vector<const xAOD::TruthParticle*> TMP_T;
  std::vector<const xAOD::TruthParticle*> TMP_O; 
  for (const xAOD::TruthParticle* T : Particles)
  {
    for (unsigned int i(0); i < T -> nChildren(); i++)
    {
      const xAOD::TruthParticle* cand = T -> child(i); 
      if (!cand){continue;}
      if (ParticleID::isBSMZ(cand -> pdgId()))
      {
        std::vector<const xAOD::TruthParticle*> bsmZ = TopsPreFSR({cand}); 
        TMP_T.insert(TMP_T.end(), bsmZ.begin(), bsmZ.end());
      }
      if (ParticleID::isTop(cand -> pdgId())){ TMP_T.push_back(cand); }
      else {TMP_O.push_back(cand);}
    }
  }

  // Make sure they are unique objects 
  std::vector<const xAOD::TruthParticle*> Out_T = UniqueObject(TMP_T);
  std::vector<const xAOD::TruthParticle*> Out_O = UniqueObject(TMP_O); 
  
  if (Out_T.size() != 0){ return Out_T; }
  else if (Out_O.size() != 0){ return TopsPreFSR(Out_O); }
  else { return Out_O; }
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

const xAOD::TruthParticle* AssureWDecay(const xAOD::TruthParticle* particle)
{
  for (unsigned int i(0); i < particle -> nChildren(); i++)
  {
    const xAOD::TruthParticle* cand = particle -> child(i); 
    if (!cand){continue;}
    if (cand -> pdgId() == particle -> pdgId() && ParticleID::isW(cand -> pdgId())){ return AssureWDecay(cand); }
  }
  return particle; 
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




