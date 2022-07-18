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

template <class X>
void FillVector(
    X T, 
    std::vector<float>* pt, 
    std::vector<float>* e, 
    std::vector<float>* phi, 
    std::vector<float>* eta, 
    std::vector<float>* charge, 
    std::vector<float>* pdgid)
{
  pt -> push_back(T -> pt()); 
  e -> push_back(T -> e()); 
  phi -> push_back(T -> phi()); 
  eta -> push_back(T -> eta()); 
  charge -> push_back(T -> charge());
  pdgid -> push_back(T -> pdgId());
}

std::vector<Truth_> Intersection(std::vector<Truth_> V1, std::vector<Truth_> V2);




#endif
