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
//Vector2d.h

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "xc_basic/src/util/mchne_eps.h"
#include "xc_basic/src/matrices/op_tensor.h"
#include "../cgal_types.h"
#include "../ProtoGeom.h"

class Pos2d;
class Dir2d;
class Plotter;
class FT_matrix;


//! @ingroup GEOM
//
//! @brief Vector en dos dimensiones.
class Vector2d: public ProtoGeom
  {
    CGVector_2 cgvct;
  public:
    Vector2d(void): ProtoGeom(), cgvct(CGAL::NULL_VECTOR) {}
    Vector2d(const CGVector_2 &v)
      : ProtoGeom(), cgvct(v) {}
    Vector2d(const CGDirection_2 &dir)
      : ProtoGeom(), cgvct(dir.vector()) {}
    Vector2d(const GEOM_FT &x,const GEOM_FT &y);
/*     Vector2d(const double &x,const double &y); */
    Vector2d(const FT_matrix &m);
    Vector2d(const Pos2d &p1,const Pos2d &p2);
    Vector2d(const Vector2d &other): cgvct(other.cgvct){}
    Vector2d &operator=(const Vector2d &other)
      {
	ProtoGeom::operator=(other);
        cgvct=other.cgvct;
        return *this;
      }
    const CGVector_2 &ToCGAL(void) const
      { return cgvct; }
    void Neg(void)
      { cgvct= -cgvct; }
    bool Nulo(void) const;
    void SetX(const GEOM_FT &vx);
    void SetY(const GEOM_FT &vy);
    void Set(unsigned short int i,const GEOM_FT &v);

    inline const GEOM_FT operator()(const size_t &i) const //Base 1.
      { return cgvct.cartesian(i-1); }
    inline const GEOM_FT operator[](const size_t &j) const //Base 0.
      { return cgvct.cartesian(j); }
    inline const GEOM_FT x() const
      { return Vector2d::operator()(1); }
    inline const GEOM_FT y() const
      { return Vector2d::operator()(2); }
    FT_matrix getMatrix(void) const;
    Vector2d operator+(const Vector2d &) const;
    Vector2d operator-(const Vector2d &) const;
    Vector2d operator*(const GEOM_FT &) const;
    Vector2d operator/(const GEOM_FT &) const;

    inline virtual GEOM_FT GetModulus2(void) const
      { return (x()*x()+y()*y()); }
    virtual GEOM_FT GetModulus(void) const;
    bool EsUnitario(const double &tol= mchne_eps_dbl) const;

    //! @brief Return el versor (vector de módulo unidad) correspondiente a éste vector.
    inline Vector2d Normalizado(void) const
      { return (*this)/GetModulus(); }
    Vector2d Normal(void) const;
    Dir2d Direccion(void) const;
    GEOM_FT getSignedAngle(const Vector2d &v) const;
    GEOM_FT getAngle(const Vector2d &v) const;
    GEOM_FT XAxisAngle(void) const;
    GEOM_FT YAxisAngle(void) const;

    //Producto escalar.
    inline virtual GEOM_FT GetDot(const Vector2d &v) const
      { return (x()*v.x()+y()*v.y()); }
    virtual GEOM_FT GetDot(const FT_matrix &m) const;
    inline friend GEOM_FT dot(const Vector2d &v1, const Vector2d &v2)
      { return v1.GetDot(v2); }
    friend GEOM_FT dot(const Vector2d &v1, const FT_matrix &m);
    friend GEOM_FT dot(const FT_matrix &m, const Vector2d &v1);

    friend FT_matrix operator*(const FT_matrix &m,const Vector2d &v);

    inline friend bool operator==(const Vector2d &v1,const Vector2d &v2)
      { return (v1.cgvct==v2.cgvct); }

    //void Gira(const GEOM_FT &ang_rad);
    //Vector2d GetGirado(const double &ang_rad) const;
    Vector2d Perpendicular(const Orientacion &o) const;
    Vector2d Perpendicular(const Vector2d &v) const;
    void Print(std::ostream &stream) const;
    void Plot(Plotter &psos) const;
    friend std::ostream &operator<<(std::ostream &stream,const Vector2d &n);
    inline virtual ~Vector2d(void) {}
  };

inline Vector2d operator-(const Vector2d &d)
  {
    Vector2d retval(d);
    retval.Neg();
    return retval;
  }

inline GEOM_FT Abs2(const Vector2d &v)
  { return v.GetModulus2(); }
inline GEOM_FT Abs(const Vector2d &v)
  { return v.GetModulus(); }
double signedAngle(const Vector2d &v1,const Vector2d &v2);
double angle(const Vector2d &v1,const Vector2d &v2);

//! @breif Return el producto por un escalar.
inline Vector2d operator*(const GEOM_FT &d,const Vector2d &v)
  { return v*d; }
//! @brief Return el versor (vector de módulo unidad) correspondiente a éste vector.
inline Vector2d Normaliza(const Vector2d &v)
  { return v.Normalizado(); }

//Producto tensorial.
FT_matrix prod_tensor(const Vector2d &u,const Vector2d &v);
FT_matrix operator&(const Vector2d &u,const Vector2d &v);

bool colineales(const Vector2d &v1,const Vector2d &v2);
bool paralelos(const Vector2d &v1,const Vector2d &v2);

const Vector2d VectorNulo2d;

#endif
