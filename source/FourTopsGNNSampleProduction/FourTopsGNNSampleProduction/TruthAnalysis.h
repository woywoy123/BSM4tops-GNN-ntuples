#ifndef FOURTOPSGNNSAMPLEPRODUCTION_H
#define FOURTOPSGNNSAMPLEPRODUCTION_H

#include <iostream>
#include <xAODTruth/TruthParticle.h>

const xAOD::TruthParticle* GetParent(const xAOD::TruthParticle* particle); 
std::vector<const xAOD::TruthParticle*> MergeParents(std::vector<const xAOD::TruthParticle*> Particles); 

std::vector<const xAOD::TruthParticle*> TopsPreFSR(std::vector<const xAOD::TruthParticle*> Particles);
const xAOD::TruthParticle* TopsPostFSR(const xAOD::TruthParticle* Particles);

const xAOD::TruthParticle* GetPath(const xAOD::TruthParticle* particle, int k, std::vector<const xAOD::TruthParticle*>* PV, std::vector<int>* PM);

const xAOD::TruthParticle* AssureWDecay(const xAOD::TruthParticle* particle); 




#endif
