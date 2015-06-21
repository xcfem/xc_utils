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
//Transformación afín (abstracto).

#ifndef TRF3D_H
#define TRF3D_H

#include "Trf.h"
#include "../tipos_cgal.h"

class Pos3d;
class Vector3d;
class MatrizPos3d;
class TritrizPos3d;


//! @ingroup GEOM
//
//! @brief Transformación de coordenadas en 3d.
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
      //Devuelve la transformación inversa.
    virtual GEOM_FT Cartesianas(const size_t &i,const size_t &j) const
    //Devuelve el elemento (i,j) de la matriz de transformación en cartesianas.
    //       -              -
    //       | m11  m12 m13 |
    //       | m21  m22 m23 |
    //       |   0    0  1  |
    //       -              -
      { return cgtrf.m(i-1,j-1); }
    virtual GEOM_FT Homogeneas(const size_t &i,const size_t &j) const
    //Devuelve el elemento (i,j) de la matriz de transformación en homogéneas.
    //       -              -
    //       | m11  m12 m13 |
    //       | m21  m22 m23 |
    //       |   0    0  hw |
    //       -              -
      { return cgtrf.hm(i-1,j-1); }
    void PutMatrizHomogeneas(const matriz_FT &mh);
    virtual matriz_FT Cartesianas(void) const;
    virtual matriz_FT Homogeneas(void) const;
    Pos3d Transforma(const Pos3d &p) const;
    Vector3d Transforma(const Vector3d &v) const;
    template <class InputIterator>
    void Transforma(InputIterator first,InputIterator last) const;
    void Transforma(MatrizPos3d &m) const;
    const MatrizPos3d &Transforma(const MatrizPos3d &m) const;
    void Transforma(TritrizPos3d &m) const;
    const TritrizPos3d &Transforma(const TritrizPos3d &m) const;
    Pos3d operator()(const Pos3d &p) const;
    Vector3d operator()(const Vector3d &v) const;
    MatrizPos3d operator()(const MatrizPos3d &m) const;
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
void Trf3d::Transforma(InputIterator first,InputIterator last) const
  {
    for(InputIterator i= first;i!=last;i++)
      (*i)= Transforma(*i);
  }

#endif
