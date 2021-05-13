
#ifndef YOURPRIMARYGENERATORACTION_HH
#define YOURPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4Types.hh"
#include "G4String.hh"

class YourDetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4String;

class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
	public:
		YourPrimaryGeneratorAction(YourDetectorConstruction* det);
		virtual ~YourPrimaryGeneratorAction();
		
		virtual void GeneratePrimaries(G4Event* anEvent);
		
		G4ParticleGun*  GetParticleGun() { return fParticleGun; } 
		
		void SetDefaultKinematic();
		void UpdatePosition();
		const G4String& GetParticleName() const;
		G4double GetParticleEnergy() const;
		
	private:
		YourDetectorConstruction* fYourDetector;
		G4ParticleGun* fParticleGun;
	};
	
#endif
