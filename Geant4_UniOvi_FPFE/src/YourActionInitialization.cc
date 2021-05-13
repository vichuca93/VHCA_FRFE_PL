
#include "YourActionInitialization.hh"

#include "YourDetectorConstruction.hh"
#include "YourPrimaryGeneratorAction.hh"

#include "YourEventAction.hh"
#include "YourSteppingAction.hh"
#include "YourRunAction.hh"

YourActionInitialization::YourActionInitialization(YourDetectorConstruction* det)
: G4VUserActionInitialization() {
	fYourDetector = det;
}

YourActionInitialization::~YourActionInitialization() {}

void YourActionInitialization::Build() const {
  // Set UserPrimaryGeneratorAction
  YourPrimaryGeneratorAction* primaryAction = new YourPrimaryGeneratorAction(fYourDetector);
  SetUserAction(primaryAction);
  // Set UserRunAction
  YourRunAction* runAction = new YourRunAction(primaryAction);
  SetUserAction(runAction); 
  // Set UserEventAction
  YourEventAction* eventAction = new YourEventAction();
  SetUserAction(eventAction);
  // Set UserSteppingAction
  SetUserAction( new YourSteppingAction(fYourDetector, eventAction) );
} 
