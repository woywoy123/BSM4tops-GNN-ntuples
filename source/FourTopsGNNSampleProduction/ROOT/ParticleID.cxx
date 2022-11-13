#include "FourTopsGNNSampleProduction/ParticleID.h"

bool ParticleID::isFinalStateTop(const xAOD::TruthParticle* p)
{
  for (unsigned int i(0); i < p -> nChildren(); i++)
  {
    if (isTop(p -> child(i))){ return false; }
  }
  return true;
}

int ParticleID::isResonance(const xAOD::TruthParticle* p)
{
  for (unsigned int i(0); i < p -> nParents(); i++)
  {
    const xAOD::TruthParticle* par = p -> parent(i); 
    if (!par){ continue; }
    
    if (isBSMZ(par)){ return 1; }
    if (isBSMH(par)){ return 1; }
    
    return isResonance( par ); 
  }
  return 0;
}

void ParticleID::FindTops(const xAOD::TruthParticle* p, std::vector<const xAOD::TruthParticle*>* _Tops)
{
 
  if (isTop(p))
  { 
    (*_Tops).push_back(p); 
    return; 
  }

  for (unsigned int i(0); i < p -> nChildren(); i++)
  {
    const xAOD::TruthParticle* c = p -> child(i); 
    if (!c){ continue; }
    FindTops(c, _Tops); 
  }
}

std::vector<const xAOD::TruthParticle*> ParticleID::FindChildren(const xAOD::TruthParticle* p)
{

  std::vector<const xAOD::TruthParticle*> children; 
  for (unsigned int i(0); i < p -> nChildren(); i++)
  {
    const xAOD::TruthParticle* c = p -> child(i); 
    
    if (!isW(c))
    {
      children.push_back(c); 
      continue;
    }

    std::vector<const xAOD::TruthParticle*> tmp = FindChildren(c); 
    children.insert(children.end(), tmp.begin(), tmp.end()); 
  }
  
  return children; 

}

void ParticleID::GetDecayPath(const xAOD::TruthParticle* top, std::vector<const xAOD::TruthParticle*>* inpt)
{
  
  (*inpt).push_back(top); 
  for (unsigned int i(0); i < top -> nChildren(); i++)
  {
    const xAOD::TruthParticle* c = top -> child(i); 
    if (!c) {continue;}
    GetDecayPath(c, inpt); 
  }
  
  return; 
}





