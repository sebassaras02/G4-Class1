#include "action.hh"
#include "generator.hh"
// contructor
actioninitialization::actioninitialization(){}
// destructor
actioninitialization::~actioninitialization(){}

void actioninitialization::Build() const{
    primarygenerator* generator= new primarygenerator();
    SetUserAction(generator);
}

