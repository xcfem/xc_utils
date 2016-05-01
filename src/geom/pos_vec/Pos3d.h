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
//Pos3d.h

#ifndef POS3D_H
#define POS3D_H


#include <iostream>
#include <string>
#include "../tipos_cgal.h"
#include "../ProtoGeom.h"

class Vector3d;
class Pos2d;
class Recta3d;
class SemiRecta3d;
class Segmento3d;
class Plano3d;
class SemiEspacio3d;
class Solido3d;

//! @ingroup GEOM
//
//! @brief Posición en tres dimensiones.
class Pos3d : public ProtoGeom
  {
    CGPoint_3 cgpt;
  public:
    typedef Vector3d vector;
    typedef CGPoint_3::Cartesian_const_iterator Cartesian_const_iterator;

    Pos3d(void)
      : ProtoGeom(), cgpt(CGAL::ORIGIN) {}
    Pos3d(const CGPoint_3 &p)
      : ProtoGeom(), cgpt(p) {}
    Pos3d(const GEOM_FT &Ax,const GEOM_FT &Ay,const GEOM_FT &Az)
      : ProtoGeom(), cgpt(Ax,Ay,Az) {}
/*     Pos3d(const double &Ax,const double &Ay,const double &Az) */
/*       : ProtoGeom(), cgpt(Point_3_from_doubles(Ax,Ay,Az)) {} */
    Pos3d(const Pos3d &otro): ProtoGeom(otro), cgpt(otro.cgpt){}
    Pos3d &operator=(const Pos3d &otro)
      {
	ProtoGeom::operator=(otro);
        cgpt=(otro.cgpt);
        return *this;
      }
    Pos3d &operator+=(const Vector3d &);
    Pos3d &operator-=(const Vector3d &);
    Vector3d operator-(const Pos3d &) const;
    Pos3d operator-(const Vector3d &) const;
    Pos3d operator+(const Vector3d &) const;
    const CGPoint_3 &ToCGAL(void) const
      { return cgpt; }
    GEOM_FT at0(const size_t &i) const;
    GEOM_FT operator()(const size_t &i) const;
    inline const GEOM_FT x() const
      { return Pos3d::operator()(1); }
    inline const GEOM_FT y() const
      { return Pos3d::operator()(2); }
    inline const GEOM_FT z() const
      { return Pos3d::operator()(3); }
    inline const GEOM_RT hx() const
      { return cgpt.hx(); }
    inline const GEOM_RT hy() const
      { return cgpt.hy(); }
    inline const GEOM_RT hz() const
      { return cgpt.hz(); }
    inline const GEOM_RT hw() const
      { return cgpt.hw(); }

    void SetX(const GEOM_FT &vx);
    void SetY(const GEOM_FT &vy);
    void SetZ(const GEOM_FT &vz);
    void Set(unsigned short int i,const GEOM_FT &v);

    inline Cartesian_const_iterator cartesian_begin(void) const
      { return ToCGAL().cartesian_begin(); }
    inline Cartesian_const_iterator cartesian_end(void) const
      { return ToCGAL().cartesian_end(); }
    size_t dimension(void) const
      { return cgpt.dimension(); }
    Vector3d VectorPos(void) const; //Devuelve el vector de posición del punto.
    bool domina_a(const Pos3d &b) const;

    GEOM_FT dist(const Pos3d &) const;
    GEOM_FT dist2(const Pos3d &) const;
    GEOM_FT dist2(const Recta3d &) const;
    GEOM_FT dist(const Recta3d &) const;
    GEOM_FT dist2(const SemiRecta3d &) const;
    GEOM_FT dist(const SemiRecta3d &) const;
    GEOM_FT dist2(const Segmento3d &) const;
    GEOM_FT dist(const Segmento3d &) const;
    GEOM_FT dist2(const Plano3d &) const;
    GEOM_FT dist(const Plano3d &) const;
    GEOM_FT dist2(const SemiEspacio3d &) const;
    GEOM_FT dist(const SemiEspacio3d &) const;
    GEOM_FT dist(const Solido3d &) const;

    int Cuadrante(void) const; //Devuelve el cuadrante en el que se encuentra el punto.

    Pos3d ProyeccionXY3d(void) const; //Devuelve la proyección sobre el plano XY.
    Pos3d ProyeccionXZ3d(void) const; //Devuelve la proyección sobre el plano XZ.
    Pos3d ProyeccionYZ3d(void) const; //Devuelve la proyección sobre el plano YZ.

    Pos2d ProyeccionXY2d(void) const; //Devuelve la proyección sobre el plano XY.
    Pos2d ProyeccionXZ2d(void) const; //Devuelve la proyección sobre el plano XZ.
    Pos2d ProyeccionYZ2d(void) const; //Devuelve la proyección sobre el plano YZ.

    Pos3d getModArgX(const GEOM_FT &mod,const GEOM_FT &giroX) const;
    Pos3d getModArgY(const GEOM_FT &mod,const GEOM_FT &giroY) const;
    Pos3d getModArgZ(const GEOM_FT &mod,const GEOM_FT &giroZ) const;

    friend bool colineales(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    friend bool coplanarios(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4);
    friend std::ostream &operator<<(std::ostream &stream,const Pos3d &n);
    inline friend bool operator==(const Pos3d &a,const Pos3d &b)
      { return (a.cgpt==b.cgpt); }
    inline friend bool operator!=(const Pos3d &a,const Pos3d &b)
      { return !(a==b); }
  };

Pos3d To3dXY2d(const Pos2d &p,const GEOM_FT &z= 0);
Pos3d To3dXZ2d(const Pos2d &p,const GEOM_FT &y= 0);
Pos3d To3dYZ2d(const Pos2d &p,const GEOM_FT &x= 0);
Pos3d To3d(const Pos2d &p,const size_t &coo,const GEOM_FT &u=0);


inline GEOM_FT dist2(const Pos3d &p1,const Pos3d &p2)
  { return p1.dist2(p2); }

inline GEOM_FT dist(const Pos3d &p1,const Pos3d &p2)
  { return p1.dist(p2); }

inline Pos3d pos_max(const Pos3d &a,const Pos3d &b)
  { return Pos3d(std::max(a.x(),b.x()),std::max(a.y(),b.y()),std::max(a.z(),b.z())); }
inline Pos3d pos_min(const Pos3d &a,const Pos3d &b)
  { return Pos3d(std::min(a.x(),b.x()),std::min(a.y(),b.y()),std::min(a.z(),b.z())); }

const Pos3d Origen3d;

#endif
