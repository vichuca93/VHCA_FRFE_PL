#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

#include "YourDetectorConstruction.hh"
#include "YourDetectorMessenger.hh"

#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4Material.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

using namespace CLHEP;
	
// Declaro mi YorDetectorConstruction utilizando la clase G4VUserDetectorConstruction
YourDetectorConstruction::YourDetectorConstruction()
:	G4VUserDetectorConstruction(),
	fTargetMaterial(nullptr),
	fTargetPhysicalVolume(nullptr) {
	fDetMessenger = new YourDetectorMessenger(this);
	SetTargetMaterial("G4_Si");
	fTargetThickness = 1.0*cm;
	fGunXPosition = 0.0;
}

YourDetectorConstruction::~YourDetectorConstruction() {
	delete fDetMessenger;
}

void YourDetectorConstruction::SetTargetMaterial(const G4String& matName) {
// try to find the material in the NIST DB
fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial(matName);
	if (!fTargetMaterial) {
	  G4cerr<< "\n **** ERROR in YourDetectorConstruction::SetTargetMaterial() \n"
			<< "        Material with the given name of < " << matName << " >  \n"
			<< "        was not found in the G4 NIST material DB               \n"
			<< G4endl;
	  exit(-1);      
	}
}

// Mi detector es una pared en la dirección X

// I. 	Primero creo los materiales: tanto de mi entorno (hidrogeno de baja densidad)
//	  	y de mi target
//
// II. 	Tengo que crear la geometria del detector. Serán dos cajas (VBox) una representará 
//		el entorno, y la segunda debe de estar dentro de la caja del entorno con el material
//		que se quiera

G4VPhysicalVolume* YourDetectorConstruction::Construct() {
	
// I. Creo los materiales
	// Entorno
	G4double zet = 1.0;
	G4double amass = 1.01*g/mole;
	G4double density = universe_mean_density;
	G4double pressure = 3.0E-18*pascal;
	G4double temperature = 2.73*kelvin;
	
	G4Material* materialWorld = new G4Material("Galactic", zet, amass, density, kStateGas, temperature, pressure);
	
	// Target
	//G4Element* elO = new G4Element("Oxygen", "O", 8.00, 16*g/mole);
	//G4Element* elSi = new G4Element("Silice", "Si", 14.00, 28.085*g/mole);
	//G4Material* matSiO2 = new G4Material("SilOxide", 2.634*g/cm3, 2);
	//	matSiO2->AddElement(elSi, 1);
	//	matSiO2->AddElement(elO, 2);
	//G4Material* materialTarget = matSiO2;
	
	G4Material* materialTarget = fTargetMaterial;
	
	
// II. Creo la geometria
	// Definiendo los tamaños y posicion inicial del haz
	G4double targetXSize = fTargetThickness;
	G4double targetYSize = 1.25*targetXSize;
	G4double worldXSize = 1.1*targetXSize;
	G4double worldYSize = 1.1*targetYSize;
	fGunXPosition = -0.25*(worldXSize + targetXSize);
	
	// Creo las cajas que representan el entorno y el target
	//	-> Tenemos que crear 3 cajas -> G4Box, G4LogicalVolume y G4VPhysicalVolume
	
	// 1) Entorno
	G4Box* worldSolid = new G4Box("solid-World", 0.5*worldXSize, 0.5*worldYSize, 0.5*worldYSize);
	G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, materialWorld, "logic-World");
	G4VPhysicalVolume* worldPhysical = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), worldLogical, "World", nullptr, false, 0);
	// 2) Target
	G4Box* targetSolid = new G4Box("solid-target", 0.5*targetXSize, 0.5*targetYSize, 0.5*targetYSize);
	G4LogicalVolume* targetLogical = new G4LogicalVolume(targetSolid, materialTarget, "logic-target");
	G4VPhysicalVolume* targetPhysical = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), targetLogical, "Target", worldLogical, false, 0);
	 // -> El parametro worldLogical me define que mi target está dentro de mi entorno
	 
fTargetPhysicalVolume = targetPhysical;

// III.	Nos devuelce el volumen físico
return worldPhysical;	
}	


