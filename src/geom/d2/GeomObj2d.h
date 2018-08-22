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
//GeomObj.h

#ifndef GEOMOBJ2D_H
#define GEOMOBJ2D_H

#include "xc_utils/src/geom/GeomObj.h"
#include "xc_utils/src/geom/sis_ref/PrincipalAxesOfInertia2D.h"

class BND2d;
class Dir2d;
class Line2d;
class FT_matrix;

//! @ingroup GEOM
//
//! @brief Base class for the two-dimensional geometric objects.
class GeomObj2d: public GeomObj
  {
  public:
   typedef PolyPos<Pos2d> list_Pos2d;

    GeomObj2d(void) {}
    virtual ~GeomObj2d(void) {}
    virtual GEOM_FT GetMax(unsigned short int i) const= 0;
    //Return el valor maximo de la coordenada i.
    virtual GEOM_FT GetMin(unsigned short int i) const= 0;
    //Return el valor minimo de la coordenada i.
    GEOM_FT GetXMax(void) const { return GetMax(1); }
    GEOM_FT GetYMax(void) const { return GetMax(2); }
    GEOM_FT GetXMin(void) const { return GetMin(1); }
    GEOM_FT GetYMin(void) const { return GetMin(2); }
    Pos2d GetPMax(void) const;
    Pos2d GetPMin(void) const;
    BND2d Bnd(void) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    virtual bool Out(const Pos2d &p, const double &tol= 0.0) const;
    //! @brief Return the factor used for the computation
    //! of the center of mass (1.0 by default).
    virtual GEOM_FT getCenterOfMassFactor(void) const
      { return 1.0; }
    virtual Pos2d getCenterOfMass(void) const= 0;
    virtual GEOM_FT getLength(void) const= 0; //?? Por que se re-declara (está en GeomObj).
    virtual GEOM_FT getArea(void) const= 0; //?? Por que se re-declara (está en GeomObj).
    //! @brief Return the object volume
    inline virtual GEOM_FT getVolume(void) const
      { return 0.0; }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    virtual GEOM_FT Ix(void) const= 0;
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    virtual GEOM_FT Iy(void) const= 0;
    //! @brief Producto de inercia with respect to the center of mass en local axis.
    virtual GEOM_FT Pxy(void) const= 0;
    //! @brief Moment of inertia polar with respect to the center of mass en local axis.
    inline virtual GEOM_FT Iz(void) const
      { return Ix()+Iy(); }
    double Theta_p(void) const;
    Dir2d IAxisDir_a(void) const;
    Dir2d IAxisDir_b(void) const;
    Line2d IAxis_a(void) const;
    Line2d IAxis_b(void) const;
    Ref2d2d PrincipalAxesOfInertia(void) const;
    GEOM_FT I1(void) const;
    GEOM_FT I2(void) const;
    inline PrincipalAxesOfInertia2D Inercia(void)
      { return PrincipalAxesOfInertia2D(getCenterOfMass(),Ix(),Iy(),Pxy()); }
    GEOM_FT I( const unsigned short int &i,
              const unsigned short int &j) const;
    virtual inline GEOM_FT IArea(void) const
      { return getArea(); }
    GEOM_FT I(const Pos2d &O,const Vector2d &e) const;
    GEOM_FT I(const Line2d &r) const;
    GEOM_FT I( const unsigned short int i,
              const unsigned short int j,
              const Pos2d &o) const;
    GEOM_FT IO(const Pos2d &o) const;
    FT_matrix I(void) const;
    FT_matrix I(const Pos2d &o) const;

    virtual void Mueve(const Vector2d &);
    virtual void Transforma(const Trf2d &trf2d)= 0;    
  };

//! @brief Return the transformed object.
template <class T>
T getTransformado(const T &obj,const Trf2d &trf2d)
  {
    T retval(obj);
    retval.Transforma(trf2d);
    return retval;
  }

#endif




