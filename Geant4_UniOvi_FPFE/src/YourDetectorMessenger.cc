
#include "YourDetectorMessenger.hh"

#include "YourDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4String.hh"

YourDetectorMessenger::YourDetectorMessenger(YourDetectorConstruction* det)
:	G4UImessenger(),
	fYourDetector(det),
	fDirCMD(nullptr),
	fTargetThicknessCMD(nullptr),
	fTargetMaterialCMD(nullptr) {
	
	fDirCMD = new G4UIdirectory("/yourApp/det/");
	fDirCMD->SetGuidance("UI commands specific to the detector construction of this application");
	
	fTargetThicknessCMD = new G4UIcmdWithADoubleAndUnit("/yourApp/det/setTargetThickness", this);
	fTargetThicknessCMD->SetGuidance("Sets the Thickness of the Target.");
	fTargetThicknessCMD->SetParameterName("TagetSizeX",false);  
	fTargetThicknessCMD->SetRange("TagetSizeX>0.");
	fTargetThicknessCMD->SetUnitCategory("Length"); 
	fTargetThicknessCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTargetThicknessCMD->SetToBeBroadcasted(false);
	
	fTargetMaterialCMD  = new G4UIcmdWithAString("/yourApp/det/setTargetMaterial",this);
	fTargetMaterialCMD->SetGuidance("Sets the Material of the Target.");
	fTargetMaterialCMD->SetParameterName("TagetMaterial",false);  
	fTargetMaterialCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
	}
	
YourDetectorMessenger::~YourDetectorMessenger() {
	delete fTargetThicknessCMD;
	delete fTargetMaterialCMD;
	delete fDirCMD;
}
		
void YourDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
	if (command == fTargetThicknessCMD) {
		G4double thickness = fTargetThicknessCMD->GetNewDoubleValue(newValue);
		fYourDetector->SetTargetThickness(thickness);
	}
	if (command == fTargetMaterialCMD) {
		fYourDetector->SetTargetMaterial(newValue);
	}
}
