/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 Header:       FGPropagate.h
 Author:       Jon S. Berndt
 Date started: 1/5/99

 ------------- Copyright (C) 1999  Jon S. Berndt (jsb@hal-pc.org) -------------

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public License along with
 this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 Place - Suite 330, Boston, MA  02111-1307, USA.

 Further information about the GNU General Public License can also be found on
 the world wide web at http://www.gnu.org.

HISTORY
--------------------------------------------------------------------------------
01/05/99   JSB   Created

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
SENTRY
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef FGPOSITION_H
#define FGPOSITION_H

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
INCLUDES
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "FGModel.h"
#include "FGColumnVector3.h"
#include "FGQuaternion.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
DEFINITIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define ID_POSITION "$Id: FGPropagate.h,v 1.2 2004/04/17 12:18:50 jberndt Exp $"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
FORWARD DECLARATIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

namespace JSBSim {

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
CLASS DOCUMENTATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/** Models the lateral and longitudinal translational EOM.
    @author Jon S. Berndt
    @version $Id: FGPropagate.h,v 1.2 2004/04/17 12:18:50 jberndt Exp $
  */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
CLASS DECLARATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

class FGPropagate : public FGModel {
public:
  /** Constructor
      @param Executive a pointer to the parent executive object */
  FGPropagate(FGFDMExec* Executive);

  /// Destructor
  ~FGPropagate();

  bool InitModel(void);

  /** Runs the Propagate model; called by the Executive
      @see JSBSim.cpp documentation
      @return false if no error */
  bool Run(void);

  inline FGColumnVector3& GetVel(void) { return vVel; }
  inline double GetVn(void)  const { return vVel(eX); }
  inline double GetVe(void)  const { return vVel(eY); }
  inline double GetVd(void)  const { return vVel(eZ); }
  inline double Geth(void)  const { return h; }
  inline double GethVRP(void)  const { return hVRP; }
  inline double Gethdot(void) const { return RadiusDot; }
  inline double GetLatitude(void) const { return Latitude; }
  inline double GetLatitudeVRP(void) const { return LatitudeVRP; }
  inline double GetLatitudeDot(void) const { return LatitudeDot; }
  inline double GetLongitude(void) const { return Longitude; }
  inline double GetLongitudeVRP(void) const { return LongitudeVRP; }
  inline double GetLongitudeDot(void) const { return LongitudeDot; }
  inline double GetRunwayRadius(void) const { return RunwayRadius; }
  inline double GetDistanceAGL(void)  const { return DistanceAGL; }
  inline double GetRadius(void) const { return Radius; }
  inline FGColumnVector3& GetRunwayNormal(void) { return vRunwayNormal; }

  inline double GetHOverBCG(void) const { return hoverbcg; }
  inline double GetHOverBMAC(void) const { return hoverbmac; }
  void SetvVel(const FGColumnVector3& v) { vVel = v; }
  void SetLatitude(double tt) { Latitude = tt; }
  void SetLongitude(double tt) { Longitude = tt; }
  void Seth(double tt);
  void SetRunwayRadius(double tt) { RunwayRadius = tt; }
  void SetSeaLevelRadius(double tt) { SeaLevelRadius = tt;}
  void SetDistanceAGL(double tt);
  inline void SetRunwayNormal(double fgx, double fgy, double fgz ) {
      vRunwayNormal << fgx << fgy << fgz;
  }
  void SetVRP(FGColumnVector3& vrp) {vVRP = vrp;}

  void bind(void);
  void unbind(void);

private:
  FGColumnVector3 vVel;
  FGColumnVector3 vRunwayNormal;
  FGColumnVector3 vVRP;
  FGColumnVector3 vVRPoffset;
  FGColumnVector3 vMac;
  FGColumnVector3 vLocation;
  FGColumnVector3 vLocationDot;
  FGColumnVector3 vLocationDot_prev[4];
  FGColumnVector3 vPQR;
  FGColumnVector3 vPQRdot;
  FGColumnVector3 vPQRdot_prev[4];
  FGColumnVector3 vUVW;
  FGColumnVector3 vUVWdot;
  FGColumnVector3 vUVWdot_prev[4];
  FGQuaternion vQtrn;
  FGQuaternion vQtrndot_prev[4];

  double Radius, h, hVRP;
  double LatitudeDot, LongitudeDot, RadiusDot;
  double LatitudeDot_prev[4], LongitudeDot_prev[4], RadiusDot_prev[4];
  double Longitude, Latitude;
  double LongitudeVRP, LatitudeVRP;
  double dt;
  double RunwayRadius;
  double DistanceAGL;
  double SeaLevelRadius;
  double hoverbcg,hoverbmac,b;

  FGColumnVector3& toGlobe(FGColumnVector3&);
  void Debug(int from);
};
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif
