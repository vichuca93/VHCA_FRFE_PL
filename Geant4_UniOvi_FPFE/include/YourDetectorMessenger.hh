
#ifndef YOURDETECTORMESSENGER_HH
#define YOURDETECTORMESSENGER_HH

#include "G4UImessenger.hh"

class YourDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4String;

class YourDetectorMessenger: public G4UImessenger {
	public:
		YourDetectorMessenger(YourDetectorConstruction* det);
		~YourDetectorMessenger();
		
		virtual void SetNewValue(G4UIcommand*, G4String);
		
	private:
		YourDetectorConstruction* fYourDetector;
		
		G4UIdirectory*				fDirCMD;
		G4UIcmdWithADoubleAndUnit*	fTargetThicknessCMD;
		G4UIcmdWithAString*			fTargetMaterialCMD;
		
		G4UImessenger* 				fDetMessenger;
		
};

#endif	
