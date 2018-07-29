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
//SVD3d.h
//Sliding vectors system.

#ifndef SVD3D_H
#define SVD3D_H

#include "../ProtoGeom.h"
#include "VDesliz3d.h"
#include "Pos3d.h"

class Line3d;
class Plane;
class Ref3d3d;


//! @ingroup GEOM
//
//! @brief Sliding vectors system en un espacio tridimensional.
class SVD3d: public VDesliz3d
  {
    Vector3d mom; //!< Moment with respect to org;
  public:
    SVD3d(const Pos3d &O= Pos3d(),const Vector3d &R= Vector3d(),const Vector3d &Mo= Vector3d());
    explicit SVD3d(const VDesliz3d &v);
    const Vector3d &getResultant(void) const
      { return getVector(); }
    Vector3d getResultant(const Ref3d3d &ref) const;
    const Vector3d &getMoment(void) const
      { return mom; }
    VDesliz3d getMoment(const Pos3d &P) const;
    GEOM_FT getMoment(const Line3d &e) const;
    Vector3d getMoment(const Ref3d3d &ref) const;
    bool Nulo(void) const;
    void Neg(void);
    Line3d centralAxis(void) const;
    bool existsZeroMomentLine(const double &tol= sqrt_mchne_eps_dbl) const;
    Line3d getZeroMomentLine(const double &tol= sqrt_mchne_eps_dbl) const;
    Pos3d PointOfApplication(const Plane &p) const;

    SVD3d ReduceA(const Pos3d &Q) const;

    SVD3d &operator+=(const VDesliz3d &v);
    SVD3d &operator-=(const VDesliz3d &v);
    SVD3d &operator+=(const SVD3d &s);
    SVD3d &operator-=(const SVD3d &s);
    SVD3d &operator*=(const GEOM_FT &d);
    friend SVD3d operator+(const SVD3d &s1,const SVD3d &s2);
    friend SVD3d operator-(const SVD3d &s1,const SVD3d &s2);
    friend SVD3d operator*(const GEOM_FT &d, const SVD3d &s);
    friend SVD3d operator*(const SVD3d &s,const GEOM_FT &d);
    void Print(std::ostream &os) const;
    void PrintLtx(std::ostream &os,const std::string &ud_long= " m",const GEOM_FT &f_long=1.0, const std::string &ud_f= " N",const GEOM_FT &f_f=1.0) const;
    friend std::ostream &operator<<(std::ostream &os, const SVD3d &svd3d);
  };

SVD3d operator+(const SVD3d &s1,const SVD3d &s2);
SVD3d operator-(const SVD3d &s1,const SVD3d &s2);
SVD3d operator*(const GEOM_FT &d, const SVD3d &s);
SVD3d operator*(const SVD3d &s,const GEOM_FT &d);
SVD3d operator+(const VDesliz3d &v1,const VDesliz3d &v2);
SVD3d operator+(const SVD3d &s,const VDesliz3d &v);
SVD3d operator+(const VDesliz3d &v,const SVD3d &s);
SVD3d operator-(const SVD3d &svd3d);
std::ostream &operator<<(std::ostream &os, const SVD3d &svd3d);

#endif
