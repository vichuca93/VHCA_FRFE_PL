
#ifndef YOURSTEPPINGACTION_HH
#define YOURSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class YourDetectorConstruction;
class YourEventAction;
class G4PhysicalVolume;

class YourSteppingAction : public G4UserSteppingAction {
	public:
		YourSteppingAction(YourDetectorConstruction* det, YourEventAction* evtAction);
		virtual ~YourSteppingAction();
		virtual void UserSteppingAction(const G4Step* step);
	private:
		YourDetectorConstruction* fYourDetector;
		YourEventAction* fYourEventAction;
};

#endif
