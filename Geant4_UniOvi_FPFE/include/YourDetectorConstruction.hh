

#ifndef YOURDETECTORCONSTRUCTION_HH
#define YOURDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class G4Material;
class G4String;
class G4LogicalVolume;
class YourDetectorMessenger;

class YourDetectorConstruction : public G4VUserDetectorConstruction {
	public:
		YourDetectorConstruction();
		virtual ~YourDetectorConstruction();
	   
		virtual G4VPhysicalVolume* Construct();
	   
		void SetTargetMaterial(const G4String& matName);
		const G4Material* GetTargetMaterial() const {return fTargetMaterial;}
	   
		void SetTargetThickness(const G4double thick) {fTargetThickness = thick;}
		G4double GetTargetThickness() const {return fTargetThickness;}
	   
		G4double GetGunXPosition() {return fGunXPosition;}
		
		const G4VPhysicalVolume* GetTargetPhysicalVolume() const { 
        return fTargetPhysicalVolume; 
		} 
	   
	private:
		G4Material* 		fTargetMaterial;
		G4double			fTargetThickness;
		G4VPhysicalVolume*	fTargetPhysicalVolume;
		G4double			fGunXPosition;
		YourDetectorMessenger* fDetMessenger;

};

#endif  
