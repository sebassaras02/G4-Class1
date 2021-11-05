#include "physicslist.hh"

physicslist::physicslist(){
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4EmStandardPhysics());
}

physicslist::~physicslist(){}
