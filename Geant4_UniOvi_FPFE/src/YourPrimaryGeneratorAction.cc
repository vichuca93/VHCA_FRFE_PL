
#include "YourPrimaryGeneratorAction.hh"
#include "YourDetectorConstruction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

YourPrimaryGeneratorAction::YourPrimaryGeneratorAction(YourDetectorConstruction* det)
:	G4VUserPrimaryGeneratorAction(),
	fYourDetector(det),
	fParticleGun(nullptr) {
		G4int nParticle =1;
		fParticleGun = new G4ParticleGun(nParticle);
		SetDefaultKinematic();
}

YourPrimaryGeneratorAction::~YourPrimaryGeneratorAction() {
	delete fParticleGun;
}
	
void YourPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

void YourPrimaryGeneratorAction::SetDefaultKinematic() {
// Creo la pistola de particulas y configuro las propiedades por defecto
	fParticleGun = new G4ParticleGun(1);
// Para electornes
	//G4ParticleDefinition* part = G4Electron::Definition();
	G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle("e-");
	//G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle("proton");
	fParticleGun->SetParticleDefinition(part);
// La direccion de la particula
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0, 0.0, 0.0));
// Energia cinetica
	fParticleGun->SetParticleEnergy(30.0*CLHEP::MeV);
	//fParticleGun->SetParticleEnergy(12.0*CLHEP::GeV);
	UpdatePosition();
}

// Posicion
void YourPrimaryGeneratorAction::UpdatePosition() {
	fParticleGun->SetParticlePosition(G4ThreeVector(fYourDetector->GetGunXPosition(), 0.0, 0.0));
}

const G4String& YourPrimaryGeneratorAction::GetParticleName() const{
	return fParticleGun->GetParticleDefinition()->GetParticleName();
}

G4double YourPrimaryGeneratorAction::GetParticleEnergy() const{
	return fParticleGun->GetParticleEnergy();
}

