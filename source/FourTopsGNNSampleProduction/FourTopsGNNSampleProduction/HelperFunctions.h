#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include <xAODTruth/TruthParticle.h>
#include "FourTopsGNNSampleProduction/ParticleID.h"
#include "TopEvent/Event.h"

typedef const xAOD::TruthParticle* Truth_; 
typedef const xAOD::JetContainer* JetC_; 
typedef const xAOD::Jet_v1* Jet_; 

typedef std::vector<float> _fvec; 
typedef std::vector<int> _ivec;
typedef std::vector<_ivec> __ivec; 

std::vector<Truth_> UniqueObject(std::vector<Truth_> Particles);
std::vector<Truth_> Intersection(std::vector<Truth_> V1, std::vector<Truth_> V2); 
int FindObject(Truth_ obj, std::vector<Truth_> V1); 

void MatchingJets(
	std::vector<Truth_> Children, JetC_ JContainer, 
	_ivec c_index, _ivec j_index, // External index mapping
	__ivec* jpc_index, _ivec* jp_index, _ivec* jp_jindex, 
	_fvec* pt, _fvec* eta, _fvec* phi, _fvec* e, _fvec* charge, _fvec* pdgid
); 
void MatchingJetsToTops(
	std::vector<Truth_> Tops, JetC_ JContainer, 
	__ivec* j_tindex, _ivec* t_index
); 	




#endif 
