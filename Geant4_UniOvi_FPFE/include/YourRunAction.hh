

#ifndef YOURRUNACTION_HH
#define YOURRUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4String.hh"

class YourPrimaryGeneratorAction;
class G4Run;

class YourRunAction : public G4UserRunAction {
	public:
		YourRunAction(YourPrimaryGeneratorAction* prim = nullptr);
		virtual ~YourRunAction();
		
		virtual void BeginOfRunAction(const G4Run*);
		virtual void EndOfRunAction(const G4Run*);
	private:
		YourPrimaryGeneratorAction* fYourPrimary;
};

#endif
