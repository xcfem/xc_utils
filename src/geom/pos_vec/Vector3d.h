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
//Vector3d.h

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "xc_basic/src/util/mchne_eps.h"
#include "../ProtoGeom.h"
#include "../cgal_types.h"

class Pos3d;
class Dir3d;
class FT_matrix;
class SbVec3f;


//! @ingroup GEOM
//
//! @brief Vector en tres dimensiones.
class Vector3d: public ProtoGeom
  {
    CGVector_3 cgvct;
  public:
    Vector3d(void): cgvct(CGAL::NULL_VECTOR){}
    Vector3d(const CGVector_3 &v)
      : cgvct(v) {}
    Vector3d(const GEOM_FT &x,const GEOM_FT &y,const GEOM_FT &z);
    Vector3d(const FT_matrix &m);
    Vector3d(const Pos3d &p1,const Pos3d &p2);
    const CGVector_3 &ToCGAL(void) const
      { return cgvct; }
    void Neg(void)
      { cgvct= -cgvct; }
    bool Nulo(void) const;
    void SetX(const GEOM_FT &vx);
    void SetY(const GEOM_FT &vy);
    void SetZ(const GEOM_FT &vz);
    void Set(unsigned short int i,const GEOM_FT &v);
    inline const GEOM_FT operator()(const size_t &i) const
      { return cgvct.cartesian(i-1); }
    inline const GEOM_FT x(void) const
      { return cgvct.x(); }
    inline const GEOM_FT y(void) const
      { return cgvct.y(); }
    inline const GEOM_FT z(void) const
      { return cgvct.z(); }
    FT_matrix getMatrix(void) const;
    Dir3d Direccion(void) const;
    Vector3d &operator+=(const Vector3d &);
    Vector3d &operator-=(const Vector3d &);
    Vector3d operator+(const Vector3d &) const;
    Vector3d operator-(const Vector3d &) const;
    Vector3d operator*(const GEOM_FT &) const;
    Vector3d operator/(const GEOM_FT &) const;

    inline virtual GEOM_FT GetModulus2(void) const
      //Return el cuadrado del módulo del vector.
      { return (x()*x()+y()*y()+z()*z()); }
    virtual GEOM_FT GetModulus(void) const;
    bool EsUnitario(const double &tol= mchne_eps_dbl) const;
    Vector3d Normalizado(void) const;
    void Normaliza(void);
    Vector3d Perpendicular(const Vector3d &v) const;
    virtual GEOM_FT GetDot(const Vector3d &v) const;
    virtual GEOM_FT GetDot(const FT_matrix &m) const;
    Vector3d getCross(const Vector3d &v) const;
    GEOM_FT getAngle(const Vector3d &v) const;


    inline friend GEOM_FT dot(const Vector3d &v1, const Vector3d &v2)
      { return v1.GetDot(v2); }
    inline friend GEOM_FT dot(const Vector3d &v1, const FT_matrix &m)
      { return v1.GetDot(m); }
    inline friend GEOM_FT dot(const FT_matrix &m, const Vector3d &v1)
      { return v1.GetDot(m); }
    inline friend Vector3d cross(const Vector3d &v1, const Vector3d &v2)
      { return v1.getCross(v2); }
    inline friend Vector3d operator^(const Vector3d &v1, const Vector3d &v2)
      { return cross(v1,v2); }
    inline friend bool operator==(const Vector3d &v1, const Vector3d &v2)
      { return (v1.cgvct==v2.cgvct); }
    friend FT_matrix operator*(const FT_matrix &m,const Vector3d &v);
    friend std::ostream &operator<<(std::ostream &stream,const Vector3d &n);

    inline virtual ~Vector3d(void) {}
  };

inline Vector3d operator-(const Vector3d &d)
  {
    Vector3d retval(d);
    retval.Neg();
    return retval;
  }

const Vector3d I_3d(1,0,0);
const Vector3d J_3d(0,1,0);
const Vector3d K_3d(0,0,1);

//! @brief Return el cuadrado del módulo del vector.
inline GEOM_FT Abs2(const Vector3d &v)
  { return v.GetModulus2(); }

GEOM_FT Abs(const Vector3d &v); //Return el módulo del vector.

GEOM_FT angle(const Vector3d &v1,const Vector3d &v2);

//Producto tensorial.
FT_matrix prod_tensor(const Vector3d &u,const Vector3d &v);
FT_matrix operator&(const Vector3d &u,const Vector3d &v);

bool paralelos(const Vector3d &v1,const Vector3d &v2);
bool coplanarios(const Vector3d &v1,const Vector3d &v2,const Vector3d &v3);

inline Vector3d operator*(const GEOM_FT &d,const Vector3d &v)
  { return v*d; }

inline Vector3d Normaliza(const Vector3d &v)
  { return v.Normalizado(); } 
FT_matrix Traspuesta(const Vector3d &v);
FT_matrix skew_symm_matrix_post(const Vector3d &v);
FT_matrix skew_symm_matrix_pre(const Vector3d &v);

const Vector3d VectorNulo3d;

#endif
