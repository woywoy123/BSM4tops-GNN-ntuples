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


