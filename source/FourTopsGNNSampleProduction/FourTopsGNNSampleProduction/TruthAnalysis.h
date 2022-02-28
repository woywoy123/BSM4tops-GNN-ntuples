#ifndef FOURTOPSGNNSAMPLEPRODUCTION_H
#define FOURTOPSGNNSAMPLEPRODUCTION_H

#include <iostream>
#include <xAODTruth/TruthParticle.h>
#include "TopEvent/Event.h"

typedef const xAOD::Jet* Jet_; 
typedef const xAOD::TruthParticle* Truth_; 
typedef std::map<Jet_, std::vector<Truth_>>::iterator it; 

Truth_ GetParent(Truth_ particle); 
std::vector<Truth_> MergeParents(std::vector<Truth_> Particles); 

std::vector<Truth_> TopsPreFSR(std::vector<Truth_> Particles);
Truth_ TopsPostFSR(Truth_ Particles);

Truth_ GetPath(Truth_ particle, int k, std::vector<Truth_>* PV, std::vector<int>* PM);

Truth_ AssureWDecay(Truth_ particle); 

void NormalizeList(std::map<Jet_, std::vector<Truth_>> Input, std::map<Jet_, std::vector<float>> Coeff, std::map<Jet_, std::vector<float>> dR, std::map<Jet_, std::vector<Truth_>>* Output);

#endif
