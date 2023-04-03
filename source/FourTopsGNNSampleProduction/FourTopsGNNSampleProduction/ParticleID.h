#ifndef PARTICLEID_H
#define PARTICLEID_H

#include <xAODTruth/TruthParticle.h>

class ParticleID
{
	public:
    		static bool isGEANT(const xAOD::TruthParticle* p){ return p -> barcode() >= 200000; }
    		static bool isTop(const xAOD::TruthParticle* p){ return abs(p -> pdgId()) == 6; }
    		static bool isW(const xAOD::TruthParticle* p){ return abs(p -> pdgId()) == 24; }
    		static bool isBSMZ(const xAOD::TruthParticle* p){ return abs(p -> pdgId()) == 6000055; }
    		static bool isBSMH(const xAOD::TruthParticle* p){ return abs(p -> pdgId()) == 35; }

    		static bool isFinalStateTop(const xAOD::TruthParticle* p);
    		static int isResonance(const xAOD::TruthParticle* p); 
    		static void FindTops(const xAOD::TruthParticle* p, std::vector<const xAOD::TruthParticle*>* _Tops); 
    		static std::vector<const xAOD::TruthParticle*> FindChildren(const xAOD::TruthParticle* p);
    		static void GetDecayPath(const xAOD::TruthParticle* p, std::vector<const xAOD::TruthParticle*>* inpt); 
		
		static const xAOD::TruthParticle* GetPath(
						const xAOD::TruthParticle* particle, int index, 
						std::vector<const xAOD::TruthParticle*>* Decay, 
						std::vector<int>* Path); 
};

#endif
