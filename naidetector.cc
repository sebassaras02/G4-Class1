#include <iostream>
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
/*create principal function
 create autoshell of Geant4*/
#include "detectorconstruction.hh"
#include "physicslist.hh"
#include "action.hh"
int main (int argc, char** argv)
{
    /* always use G4RunManager which is the top of execution of Geant4*/
    G4RunManager* runmanager= new G4RunManager();
    // tell geant4 to inizilitation of detector construction
    runmanager->SetUserInitialization(new detectorconstruction());
    runmanager->SetUserInitialization(new physicslist());
    runmanager->SetUserInitialization(new actioninitialization());
    // only initialize runmanger just in case you have all mandatory classes
    runmanager->Initialize();
    // need user interfase
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    G4UImanager* UIManager=  G4UImanager::GetUIpointer();
    // need a visualization, it has to be first to have a view and after that have the volumes
    G4VisManager *vis= new G4VisExecutive();
    vis->Initialize();
    // Open the example with OPENGL
    UIManager->ApplyCommand("/vis/open OGL");
    // draw the volumes
    UIManager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UIManager->ApplyCommand("/vis/drawVolume");
    // to refresh each event
    UIManager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    // to see the trajectories of particles
    UIManager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UIManager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    
    ui->SessionStart();



    return 0;
}
