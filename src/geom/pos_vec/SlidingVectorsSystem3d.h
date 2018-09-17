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
//SlidingVectorsSystem3d.h
//Sliding vectors system.

#ifndef SLIDINGVECTORSSYSTEM3D_H
#define SLIDINGVECTORSSYSTEM3D_H

#include "../ProtoGeom.h"
#include "SlidingVector3d.h"
#include "Pos3d.h"

class Line3d;
class Plane;
class Ref3d3d;


//! @ingroup GEOM
//
//! @brief Sliding vectors system en un espacio tridimensional.
class SlidingVectorsSystem3d: public SlidingVector3d
  {
    Vector3d mom; //!< Moment with respect to org;
  public:
    SlidingVectorsSystem3d(const Pos3d &O= Pos3d(),const Vector3d &R= Vector3d(),const Vector3d &Mo= Vector3d());
    explicit SlidingVectorsSystem3d(const SlidingVector3d &v);
    const Vector3d &getResultant(void) const
      { return getVector(); }
    Vector3d getResultant(const Ref3d3d &ref) const;
    const Vector3d &getMoment(void) const
      { return mom; }
    SlidingVector3d getMoment(const Pos3d &P) const;
    GEOM_FT getMoment(const Line3d &e) const;
    Vector3d getMoment(const Ref3d3d &ref) const;
    bool Nulo(void) const;
    void Neg(void);
    Line3d centralAxis(void) const;
    bool existsZeroMomentLine(const double &tol= sqrt_mchne_eps_dbl) const;
    Line3d getZeroMomentLine(const double &tol= sqrt_mchne_eps_dbl) const;
    Pos3d PointOfApplication(const Plane &p) const;

    SlidingVectorsSystem3d ReduceA(const Pos3d &Q) const;

    SlidingVectorsSystem3d &operator+=(const SlidingVector3d &v);
    SlidingVectorsSystem3d &operator-=(const SlidingVector3d &v);
    SlidingVectorsSystem3d &operator+=(const SlidingVectorsSystem3d &s);
    SlidingVectorsSystem3d &operator-=(const SlidingVectorsSystem3d &s);
    SlidingVectorsSystem3d &operator*=(const GEOM_FT &d);
    friend SlidingVectorsSystem3d operator+(const SlidingVectorsSystem3d &s1,const SlidingVectorsSystem3d &s2);
    friend SlidingVectorsSystem3d operator-(const SlidingVectorsSystem3d &s1,const SlidingVectorsSystem3d &s2);
    friend SlidingVectorsSystem3d operator*(const GEOM_FT &d, const SlidingVectorsSystem3d &s);
    friend SlidingVectorsSystem3d operator*(const SlidingVectorsSystem3d &s,const GEOM_FT &d);
    void Print(std::ostream &os) const;
    void PrintLtx(std::ostream &os,const std::string &ud_long= " m",const GEOM_FT &f_long=1.0, const std::string &ud_f= " N",const GEOM_FT &f_f=1.0) const;
    friend std::ostream &operator<<(std::ostream &os, const SlidingVectorsSystem3d &svd3d);
  };

SlidingVectorsSystem3d operator+(const SlidingVectorsSystem3d &s1,const SlidingVectorsSystem3d &s2);
SlidingVectorsSystem3d operator-(const SlidingVectorsSystem3d &s1,const SlidingVectorsSystem3d &s2);
SlidingVectorsSystem3d operator*(const GEOM_FT &d, const SlidingVectorsSystem3d &s);
SlidingVectorsSystem3d operator*(const SlidingVectorsSystem3d &s,const GEOM_FT &d);
SlidingVectorsSystem3d operator+(const SlidingVector3d &v1,const SlidingVector3d &v2);
SlidingVectorsSystem3d operator+(const SlidingVectorsSystem3d &s,const SlidingVector3d &v);
SlidingVectorsSystem3d operator+(const SlidingVector3d &v,const SlidingVectorsSystem3d &s);
SlidingVectorsSystem3d operator-(const SlidingVectorsSystem3d &svd3d);
std::ostream &operator<<(std::ostream &os, const SlidingVectorsSystem3d &svd3d);

#endif
