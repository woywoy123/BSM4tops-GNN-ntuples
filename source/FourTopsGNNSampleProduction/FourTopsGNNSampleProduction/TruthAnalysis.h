#ifndef FOURTOPSGNNSAMPLEPRODUCTION_H
#define FOURTOPSGNNSAMPLEPRODUCTION_H

#include <iostream>
#include <xAODTruth/TruthParticle.h>
#include "TopEvent/Event.h"

typedef const xAOD::Jet* Jet_; 
typedef const xAOD::TruthParticle* Truth_; 
typedef std::map<Jet_, std::vector<Truth_>>::iterator it; 

std::vector<Truth_> MergeParents(std::vector<Truth_> Particles); 
std::vector<Truth_> TopsPreFSR(std::vector<Truth_> Particles);

Truth_ GetParent(Truth_ particle); 
Truth_ TopsPostFSR(Truth_ Particles);
Truth_ GetPath(Truth_ particle, int k, std::vector<Truth_>* PV, std::vector<int>* PM);
Truth_ AssureWDecay(Truth_ particle); 
std::vector<Truth_> UniqueObject(std::vector<Truth_> Particles);

void NormalizeList(std::map<Jet_, std::vector<Truth_>> Input, std::map<Jet_, std::vector<float>> Coeff, std::map<Jet_, std::vector<float>> dR, std::map<Jet_, std::vector<Truth_>>* Output);


template <class X>
void FillVector(
    X T, 
    std::vector<float>* pt, 
    std::vector<float>* e, 
    std::vector<float>* phi, 
    std::vector<float>* eta)
{
  pt -> push_back(T -> pt()); 
  e -> push_back(T -> e()); 
  phi -> push_back(T -> phi()); 
  eta -> push_back(T -> eta()); 
}

template <class Y, class U>
float deltaR(Y p1, U p2)
{
  return std::pow( std::pow(p1 -> eta() - p2 -> eta(), 2) + std::pow(p1 -> phi() - p2 -> phi(), 2), 0.5 );
}




#endif
