//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//Xd3dCooSys.h
//Coordinate system of dimension X defined in a three-dimensional space.

#ifndef XD3D_COO_SYS_H
#define XD3D_COO_SYS_H

#include "CooSys.h"

class Vector3d;
class Dir3d;
class Pos3d;

//! @ingroup CooSys
//! 
//! @brief Base class for coordinate systems
//! defined in a three-dimensional space.
class Xd3dCooSys: public CooSys
  {
  public:
    typedef Vector3d VGlobal; //!< Vector in the 3D space.
    typedef Pos3d PGlobal; //!< Point in the 3D space.
    typedef Dir3d DGlobal; //!< Direction in the 3D space.
  protected:
    void vectores_unitarios(const VGlobal &i_,const VGlobal &j_,const VGlobal &k_);
    Xd3dCooSys(const size_t &i)
      : CooSys(i,3) {}
    Xd3dCooSys(const size_t &i,const VGlobal &v1);
    Xd3dCooSys(const size_t &i,const VGlobal &v1,const VGlobal &v2);
    Xd3dCooSys(const size_t &i,const PGlobal &o,const PGlobal &p);
    Xd3dCooSys(const size_t &i,const PGlobal &p1,const PGlobal &p2, const PGlobal &p3);
    Xd3dCooSys(const size_t &i,const VGlobal &v1,const VGlobal &v2,const VGlobal &v3);


    void putRow(const size_t &axis,const VGlobal &v);
    void XAxisVector(const VGlobal &v);
    void TwoPoints(const PGlobal &o,const PGlobal &p);
    void ThreePoints(const PGlobal &o,const PGlobal &p1,const PGlobal &p2);

  public:
    //@ brief Constructor virtual.
    virtual Xd3dCooSys *CopiaXd3d(void) const= 0;
    virtual VGlobal getAxisVDir(const size_t &axis) const;
    //Return the direction vector of the axis.
    virtual DGlobal getAxisDir(const size_t &axis) const;

    VGlobal GetCooGlobales(const FT_matrix &v) const;
    FT_matrix GetCooLocales(const VGlobal &v) const;
  };

#endif
