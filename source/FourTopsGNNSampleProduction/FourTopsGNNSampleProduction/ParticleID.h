#ifndef PARTICLEID_H
#define PARTICLEID_H

#include <xAODTruth/TruthParticle.h>
class ParticleID
{
  public:

    static bool isdq(int pdgId){ return abs(pdgId) == 1; }
    static bool isuq(int pdgId){ return abs(pdgId) == 2; }
    static bool issq(int pdgId){ return abs(pdgId) == 3; }
    static bool iscq(int pdgId){ return abs(pdgId) == 4; }
    static bool isbq(int pdgId){ return abs(pdgId) == 5; }
    static bool isTop(int pdgId){ return abs(pdgId) == 6; }

    static bool isPhoton(int pdgId){ return abs(pdgId) == 22; }
    static bool isGluon(int pdgId){ return abs(pdgId) == 21; }

    static bool isW(int pdgId){ return abs(pdgId) == 24; }
    static bool isZ(int pdgId){ return abs(pdgId) == 23; }
    static bool isH(int pdgId){ return abs(pdgId) == 25; }
    static bool isChargedH(int pdgId){ return abs(pdgId) == 37; }
    static bool isBSMH(int pdgId){ return abs(pdgId) == 35; }
    static bool isBSMZ(int pdgId){ return abs(pdgId) == 6000055; }

    static bool isTau(int pdgId){ return abs(pdgId) == 15; }
    static bool isMu(int pdgId){ return abs(pdgId) == 13; }
    static bool isEl(int pdgId){ return abs(pdgId) == 11; }
    static bool isNu(int pdgId){ return abs(pdgId) == 12 || abs(pdgId) == 14 || abs(pdgId) == 16; }
    static bool isQuark(int pdgId){ return abs(pdgId) < 7 && abs(pdgId) > 0; }
    static bool isLep(int pdgId){ return abs(pdgId) == 11 || abs(pdgId) == 13 || abs(pdgId) == 15; }

    static bool isGEANT(int barcode){ return barcode >= 200000; }

};

bool IsFinalTop(const xAOD::TruthParticle* particle); 
bool IsFinalBSMZ(const xAOD::TruthParticle* particle); 
bool IsFinalBSMH(const xAOD::TruthParticle* particle); 

#endif 
