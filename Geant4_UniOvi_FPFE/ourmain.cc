
#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"
#include "YourDetectorConstruction.hh"
#include "YourPrimaryGeneratorAction.hh"
#include "YourActionInitialization.hh"

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

int main(int argc, char** argv) {

G4UIExecutive* ui=0;
  if (argc ==1 ){
    ui = new G4UIExecutive(argc,argv, "qt");
  }
  
// Declaro primero el RunManager
G4RunManager* runManager = new G4RunManager();

// Declaro el G4UserDetectorConstructor
YourDetectorConstruction* detector = new YourDetectorConstruction(); 
runManager->SetUserInitialization(detector);

// Declaro el G4PhysicsList
// -> Para saber qué partícula usaremos
G4PhysListFactory physListFactory; 
const G4String plName = "FTFP_BERT"; 
G4VModularPhysicsList* pl = physListFactory.GetReferencePhysList(plName); 
runManager->SetUserInitialization(pl); 

// Declaro mi ActionInitialization
runManager->SetUserInitialization(new YourActionInitialization(detector));

// Inicializo el run
//runManager->Initialize();

// anadimos verbosity
//G4EventManager::GetEventManager()->GetTrackingManageer()->SetVerboseLevel(1);
// corremos 10 eventos
//runManager->BeamOn(10);
// borramos el RunManager


//Anadimos visualizacion
G4VisManager* visManager = new G4VisExecutive;
visManager->Initialize();
//delete visManager;

G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if (!ui) {
    G4String cmd = "/control/execute ";
    G4String scmd = argv[1];
    UImanager->ApplyCommand(cmd + scmd);
  } else {
    UImanager->ApplyCommand("/run/initialize");
    UImanager->ApplyCommand("/control/execute ../vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  delete runManager;
  
  return 0;

}


