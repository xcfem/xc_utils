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
//Trf2d.h
//Transformación afín (abstracto).

#ifndef TRF2D_H
#define TRF2D_H

#include "Trf.h"
#include "../cgal_types.h"
#include "xc_utils/src/geom/d2/GeomObj2d.h"

class Pos2d;
class Vector2d;
class Line2d;



//! @ingroup GEOM
//
//! @brief Clase base para las transformaciones en dos dimensiones.
class Trf2d: public Trf
  {
  private:
    CGTrfAfin_2 cgtrf;
    Trf2d(const CGTrfAfin_2 &t)
      : Trf(), cgtrf(t) {}
  protected:
    Trf2d(const CGAL::Translation &tr,const Vector2d &v);
    Trf2d(const CGAL::Rotation &rot,const GEOM_RT &seno,const GEOM_RT &coseno);
/*     //Trf2d(const CGAL::Reflection &ref,const Line2d &r); */
    Trf2d(const CGAL::Scaling &sc,const GEOM_FT &factor_escala);
    explicit Trf2d(const CGAL::Identity_transformation &i);

    CGPoint_2 Transforma(const CGPoint_2 &cgpt2) const;
  public:
    Trf2d(void)
      : Trf(), cgtrf(CGAL::Identity_transformation()) {}
/*     Trf2d( const GEOM_RT & m00,const GEOM_RT & m01,const GEOM_RT & m02, */
/*            const GEOM_RT & m10,const GEOM_RT & m11,const GEOM_RT & m12, */
/*            const GEOM_RT & hw = GEOM_RT(1.0)); */
    Trf2d( const GEOM_FT & m00,const GEOM_FT & m01,const GEOM_FT & m02,
           const GEOM_FT & m10,const GEOM_FT & m11,const GEOM_FT & m12);
    Trf2d(const Trf2d &otra)
      : Trf(otra), cgtrf(otra.cgtrf) {}
    Trf2d &operator=(const Trf2d &otra)
      {
	Trf::operator=(otra);
        cgtrf= otra.cgtrf;
        return *this;
      }
    //Return la transformación inversa.
    //Trf2d Inversa(void) const;

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
    virtual FT_matrix Cartesianas(void) const;
    virtual FT_matrix Homogeneas(void) const;
    Pos2d Transforma(const Pos2d &p) const;
    Vector2d Transforma(const Vector2d &v) const;
    template <class InputIterator>
    void Transforma(InputIterator first,InputIterator last) const;
    GeomObj::list_Pos2d Transforma(const GeomObj::list_Pos2d &lp2d) const;
    Pos2d operator()(const Pos2d &p) const;
    Vector2d operator()(const Vector2d &v) const;
    GeomObj::list_Pos2d operator()(const GeomObj::list_Pos2d &lp2d) const;
    friend Trf2d operator*(const Trf2d &a,const Trf2d &b);
    virtual ~Trf2d(void) {}
  };

template <class InputIterator>
void Trf2d::Transforma(InputIterator first,InputIterator last) const
  {
    for(InputIterator i= first;i!=last;i++)
      (*i)= Transforma(*i);
  }

#endif
