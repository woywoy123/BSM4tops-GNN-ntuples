#include <FourTopsGNNSampleProduction/ParticleID.h>

bool IsFinalTop(const xAOD::TruthParticle* Particle)
{
  if (!ParticleID::isTop(Particle -> pdgId())){ return false; }
  
  for (unsigned int i(0); i < Particle -> nChildren(); i++)
  {
    const xAOD::TruthParticle* tc = Particle -> child(i); 
    if (abs(tc -> pdgId()) < 6){ return true; }
  }
  return false;
}

bool IsFinalBSMZ(const xAOD::TruthParticle* Particle)
{
  for (unsigned int i(0); i < Particle -> nParents(); i++)
  {
    if (ParticleID::isBSMZ( Particle -> parent(i) -> pdgId())){return true;}
    else{return IsFinalBSMZ(Particle -> parent(i));}
  }
  return false;
}


