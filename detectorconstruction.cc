#include "detectorconstruction.hh"
// contructor
detectorconstruction::detectorconstruction()
{}
// destructor
detectorconstruction::~detectorconstruction()
{}
// add properties and volumenes
G4VPhysicalVolume* detectorconstruction::Construct()
{
    // CREATE MATERIALS
    
    
    // define an Element from isotopes, by relative abundance
    G4Isotope* U5 = new G4Isotope("U235", 92, 235, 235.01*g/mole);
    G4Isotope* U8 = new G4Isotope("U238", 92, 238, 238.03*g/mole);
    // create the mixture
    G4Element* elU  = new G4Element("enriched Uranium", "U", 2);
    elU->AddIsotope(U5,  95.*perCent);
    elU->AddIsotope(U8,  5.*perCent);
    G4Element* elO  = new G4Element("Oxygen" , // its name
                                    "O" , // symbol
                                    8., // atomic number
                                    16.00*g/mole); // atomic weigth
    // define the material
    G4Material* uranium_mat = new G4Material("Uranium_enriched", 10.97*g/cm3, 2);
    uranium_mat->AddElement(elU, 1);
    uranium_mat->AddElement(elO, 2);
    // call Nist library to create the air
    G4NistManager* nist = G4NistManager::Instance();
    nist->SetVerbose(1);
    G4Material* Air  = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* helium = nist->ConstructNewGasMaterial("helium","G4_He",400.*kelvin,            10*atmosphere);
    G4Material* zicaloy  = nist->FindOrBuildMaterial("G4_Zn");
    
    
    // CREATE SOLIDS
    // world
    G4Box*world_solid= new G4Box("world_solid",
            1*m,
            1*m,
            1*m);
    // the other ones
    G4Tubs*zirc_solid= new G4Tubs("zirc_solid",
             0*cm,
             10*cm,
             10*cm,
             0*deg,
             360*deg);
    G4Tubs*hel_solid= new G4Tubs("hel_solid",
             0*cm,
             9.5*cm,
             10*cm,
             0*deg,
             360*deg);
    G4Tubs*ur_solid= new G4Tubs("ur_solid",
             0*cm,
             8*cm,
             10*cm,
             0*deg,
             360*deg);
    
    
    //CREATE LOGIC VOLUMES
    G4LogicalVolume* logicWorld = new G4LogicalVolume(
                        world_solid, //its solid
                        Air,         //its material
                        "world_logic");    //its name
    //CREATE PHYSICAL VOLUMES
    G4VPhysicalVolume*world_phys= new G4PVPlacement(0,// no rotation
                                G4ThreeVector(), // where is the center
                                logicWorld, // its logic volume
                                "world_phys",
                                0, // its mother volume, its the first mother 'cause it's cero
                                false, 
                                0, // if you insert several logical volumes there
                                true // to check overlaps
                                );
    G4LogicalVolume* logic_zirc = new G4LogicalVolume(
                        zirc_solid, //its solid
                        zicaloy,         //its material
                        "zircarloy_logic");    //its name
    G4LogicalVolume* logic_hel = new G4LogicalVolume(
                        hel_solid, //its solid
                        helium,         //its material
                        "helium_logic");    //its name
    G4LogicalVolume* logic_uranium = new G4LogicalVolume(
                        ur_solid, //its solid
                        uranium_mat,         //its material
                        "uranium_logic");    //its name
    

    new G4PVPlacement(0,// no rotation
                    G4ThreeVector(), // where is the center
                    logic_zirc, // its logic volume
                    "zircaloy_phys",
                    logicWorld, // its mother volume                    
                    false, 
                    0, // if you insert several logical volumes there
                    true); // to check overlaps
                    
    new G4PVPlacement(0,// no rotation
                    G4ThreeVector(), // where is the center
                    logic_hel, // its logic volume
                    "helium_phys",
                    logic_zirc, // its mother volume, its the first mother 'cause it's cero
                    false, 
                    0, // if you insert several logical volumes there
                    true); // to check overlaps
                    
    new G4PVPlacement(0,// no rotation
                    G4ThreeVector(), // where is the center
                    logic_uranium, // its logic volume
                    "uranium_phys",
                    logic_hel, // its mother volume, its the first mother 'cause it's cero
                    false, 
                    0, // if you insert several logical volumes there
                    true); // to check overlaps
                    
                    
    // always return to physworld
    return world_phys;
}

