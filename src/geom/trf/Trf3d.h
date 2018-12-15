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
//Trf3d.h
//Three dimensional transformation.

#ifndef TRF3D_H
#define TRF3D_H

#include "Trf.h"
#include "../cgal_types.h"

class Pos3d;
class Vector3d;
class Pos3dArray;
class Pos3dArray3d;


//! @ingroup GEOM
//
//! @brief Three-dimensional transformation.
class Trf3d: public Trf
  {
  private:
    CGTrfAfin_3 cgtrf;
    Trf3d(const CGTrfAfin_3 &t)
      : Trf(), cgtrf(t) {}
  protected:
    Trf3d(const CGAL::Translation &tr,const Vector3d &v);
    //Trf3d(const CGAL::Rotation &rot,const GEOM_FT &seno,const GEOM_FT &coseno);
    Trf3d(const CGAL::Scaling &sc,const GEOM_FT &factor_escala);
    explicit Trf3d(const CGAL::Identity_transformation &i);
  public:
    Trf3d(void)
      : Trf(), cgtrf(CGAL::Identity_transformation()) {}
    Trf3d( const GEOM_FT & m00,const GEOM_FT & m01,const GEOM_FT & m02,const GEOM_FT & m03,
           const GEOM_FT & m10,const GEOM_FT & m11,const GEOM_FT & m12,const GEOM_FT & m13,
           const GEOM_FT & m20,const GEOM_FT & m21,const GEOM_FT & m22,const GEOM_FT & m23);
    //Trf3d Inversa(void) const;
      //Return the inverse transformation.
    //@brief Return the (i,j) componet of the transformation matrix expressed in
    // cartesian coordinates.
    //       -              -
    //       | m11  m12 m13 |
    //       | m21  m22 m23 |
    //       |   0    0  1  |
    //       -              -
    virtual GEOM_FT Cartesianas(const size_t &i,const size_t &j) const
      { return cgtrf.m(i-1,j-1); }
    
    //@brief Return the (i,j) componet of the transformation matrix expressed in
    // homogeneous coordinates.
    //       -              -
    //       | m11  m12 m13 |
    //       | m21  m22 m23 |
    //       |   0    0  hw |
    //       -              -
    virtual GEOM_FT Homogeneas(const size_t &i,const size_t &j) const
      { return cgtrf.hm(i-1,j-1); }
    void putHomogenousMatrix(const FT_matrix &mh);
    virtual FT_matrix Cartesianas(void) const;
    virtual FT_matrix Homogeneas(void) const;
    Pos3d Transform(const Pos3d &p) const;
    Vector3d Transform(const Vector3d &v) const;
    template <class InputIterator>
    void Transform(InputIterator first,InputIterator last) const;
    void Transform(Pos3dArray &m) const;
    const Pos3dArray &Transform(const Pos3dArray &m) const;
    void Transform(Pos3dArray3d &m) const;
    const Pos3dArray3d &Transform(const Pos3dArray3d &m) const;
    Pos3d operator()(const Pos3d &p) const;
    Vector3d operator()(const Vector3d &v) const;
    Pos3dArray operator()(const Pos3dArray &m) const;
    friend Trf3d operator*(const Trf3d &a,const Trf3d &b);
    friend Trf3d giroX3d(const double &ang_rad);
    friend Trf3d giroY3d(const double &ang_rad);
    friend Trf3d giroZ3d(const double &ang_rad);
    virtual ~Trf3d(void) {}
  };

Trf3d giroX3d(const double &ang_rad);
Trf3d giroY3d(const double &ang_rad);
Trf3d giroZ3d(const double &ang_rad);

inline Trf3d giroXYZ3d(const double &rx,const double &ry,const double &rz)
  { return giroZ3d(rz) * giroY3d(ry) * giroX3d(rx); }

template <class InputIterator>
void Trf3d::Transform(InputIterator first,InputIterator last) const
  {
    for(InputIterator i= first;i!=last;i++)
      (*i)= Transform(*i);
  }

#endif
