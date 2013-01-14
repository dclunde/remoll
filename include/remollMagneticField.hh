#ifndef __REMOLLMAGNETICFIELD_HH
#define __REMOLLMAGNETICFIELD_HH

#include <vector>

#define __NDIM 3

#include "G4String.hh"
#include "G4MagneticField.hh"

/*!
    \class remollMagneticField
    \brief Individual field map manager
*/

class remollMagneticField : public G4MagneticField {
    /*! 
     * Moller spectrometer magnetic field class
     *
     * Use trilinear interpolation in cylindrical coordinates
     * Might be nice to use some kind of spline someday?
     * Use vectors to store multidimensional arrays
     *
     * Units are meters, degrees, and Tesla
     * Coordinate ordering will be r, phi, z
     * We will only deal with phi interval [-pi,pi]
     *
     * Field maps are of the form
     *
     * #Rpoints		rmin	rmax
     * #Phipoints	phimin	phimax
     * #Zpoints		zmin	zmax
     * # xtants (7 for septant form, 1 for full geometry)
     * r   phi   z    br   bphi   bz
     * ......
     *
     */

    public:
	remollMagneticField( G4String );
	virtual ~remollMagneticField();

	void GetFieldValue( const   G4double Point[4], G4double *Bfield ) const;  

	void InitializeGrid();
	void ReadFieldMap();

	void SetFieldScale(G4double s){ fFieldScale = s; }
	void SetZoffset(G4double z){ fZoffset= z; }

	G4String GetName();

	enum Coord_t { kR, kPhi, kZ };

	G4bool IsInit(){ return fInit; }

    private:
	G4String fFilename;

	G4int fN[__NDIM];
	G4double fMin[__NDIM], fMax[__NDIM];

	G4int fNxtant; // Number of *tants (septants, or whatever)
	G4double fPhi0, fPhiLow;

	// Storage space for the table
	std::vector< std::vector< std::vector< G4double > > > fBFieldData[__NDIM];

	G4double fZoffset;

	G4double fFieldScale; // Scale overall field by this amount

	G4bool fInit;
};


#endif//__REMOLLMAGNETICFIELD_HH