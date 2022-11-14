#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include <xAODTruth/TruthParticle.h>

typedef const xAOD::TruthParticle* Truth_; 

std::vector<Truth_> UniqueObject(std::vector<Truth_> Particles);
std::vector<Truth_> Intersection(std::vector<Truth_> V1, std::vector<Truth_> V2); 
int FindObject(Truth_ obj, std::vector<Truth_> V1); 

#endif 
