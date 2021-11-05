#ifndef action_hh

#define action_hh

//call mandatory class
#include "G4VUserActionInitialization.hh"

class actioninitialization: public G4VUserActionInitialization{
    public:
    actioninitialization();
    ~actioninitialization();
    
    virtual void Build() const;
    
};
#endif
