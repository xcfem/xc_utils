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
//Recta2d.h

#ifndef RECTA2D_H
#define RECTA2D_H

#include "Linea2d.h"
#include "../pos_vec/Pos2d.h"
#include "../pos_vec/Vector2d.h"



//! @ingroup GEOM
//
//! @brief Recta 2d en paramétricas.
class RectaParametricas2d
  {
    Pos2d org; //Origen de la recta.
    Vector2d dir; //Vector dirección.
  public:
    RectaParametricas2d(const Pos2d &o,const Vector2d &d)
      : org(o), dir(d) {}
    inline const Pos2d &GetOrg(void) const
      { return org; }
    inline const Vector2d &GetDir(void) const
      { return dir; }
    inline Pos2d GetPunto(const GEOM_FT &lambda) const
    //Devuelve un punto de la recta a una "distancia"
    //lambda del origen.
      { return org+lambda*dir; }
    GEOM_FT Parametro(const Pos2d &p) const;
  };


class Dir2d;
class SemiRecta2d;
class Segmento2d;


//! @ingroup GEOM
//
//! @brief Recta en dos dimensiones.
class Recta2d : public Linea2d
  {
    CGRecta_2 cgr;

    friend class SemiRecta2d;
    friend class Segmento2d;
  public:
    Recta2d(void);
    explicit Recta2d(const CGRecta_2 &r);
    Recta2d(const Pos2d &p1,const Pos2d &p2);
    Recta2d(const Pos2d &p,const Dir2d &dir);
    Recta2d(const Pos2d &p,const Vector2d &vdir);
    Recta2d(const Recta2d &r);
    Recta2d(const RectaParametricas2d &param);
    Recta2d &operator=(const Recta2d &r);

    const CGRecta_2 &ToCGAL(void) const;
    virtual GeomObj *clon(void) const;
    void Swap(void);

    void DosPuntos(const Pos2d &p1,const Pos2d &p2);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }

    Pos2d Projection(const Pos2d &p) const;
    Vector2d Projection(const Vector2d &) const;
    GeomObj::list_Pos2d Project(const GeomObj::list_Pos2d &ptos) const;
    
    GEOM_RT a(void) const;
    GEOM_RT b(void) const;
    GEOM_RT c(void) const;
    GEOM_FT GetPendiente(void) const;
    GEOM_FT GetParamA(void) const; //Devuelve el parámetro a (y=a*x+b) de la recta.
    GEOM_FT GetParamB(void) const; //Devuelve el parámetro b (y=a*x+b) de la recta.

    GEOM_FT GetY(const GEOM_FT &x) const;
    GEOM_FT Parametro(const Pos2d &p) const;
    GeomObj::list_Pos2d Ordena(const GeomObj::list_Pos2d &ptos) const;
    Pos2d Punto(const int &i=0) const;

    double getLambda(unsigned short int i,const double &d,const Vector2d &i_) const;

    RectaParametricas2d GetParametricas(void) const;
    Pos2d PtoParametricas(const GEOM_FT &lambda) const;
    void Parametricas(const RectaParametricas2d &param);
    bool EsVertical(void) const;
    bool EsDegenerada(void) const;
    bool In(const Pos2d &p, const double &tol= 0.0) const;
    bool LadoDerecho(const Pos2d &p) const;
    bool LadoIzquierdo(const Pos2d &p) const;

    GEOM_FT dist2(const Pos2d &p) const;
    virtual GEOM_FT dist(const Pos2d &p) const;

    Recta2d Perpendicular(const Pos2d &p) const;
    Recta2d Paralela(const Pos2d &v) const;
    Recta2d Offset(const Vector2d &v) const;
    Recta2d Offset(const GEOM_FT &d) const;
    void Put(const Pos2d &p1,const Pos2d &p2);

    bool Interseca(const Recta2d &r2) const;
    GeomObj2d::list_Pos2d Interseccion(unsigned short int i, const double &d) const;
    GeomObj2d::list_Pos2d Interseccion(const Recta2d &r2) const;

    bool Paralela(const Recta2d &r) const;

    virtual GEOM_FT Longitud(void) const;
    virtual Pos2d Cdg(void) const;
    Dir2d GetDir(void) const;
    Vector2d VDir(void) const;
    Vector2d VersorDir(void) const;
    Recta2d Bisectriz(const Recta2d &r) const;
    Recta2d getNormalizada(void) const;

    double Angulo(const Vector2d &v) const;
    double Azimuth(void) const;
    friend double angulo(const Recta2d &r,const Vector2d &v);
    friend double angulo(const Recta2d &r1,const Recta2d &r2);

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;

    void Transforma(const Trf2d &trf2d);

    friend bool operator==(const Recta2d &r1,const Recta2d &r2);

    void Print(std::ostream &os) const;
    void Plot(Plotter &psos) const;
    
  };

double angulo(const Recta2d &r,const Vector2d &v);
double angulo(const Recta2d &r1,const Recta2d &r2);

bool operator==(const Recta2d &r1,const Recta2d &r2);

inline GEOM_FT dist2(const Pos2d &p,const Recta2d &r)
  { return r.dist2(p); }
inline GEOM_FT dist(const Pos2d &p,const Recta2d &r)
  { return r.dist(p); }
inline GEOM_FT dist2(const Recta2d &r,const Pos2d &p)
  { return dist2(p,r); }
inline GEOM_FT dist(const Recta2d &r,const Pos2d &p)
  { return dist(p,r); }
GEOM_FT dist2(const Recta2d &r1,const Recta2d &r2);
GEOM_FT dist(const Recta2d &r1,const Recta2d &r2);

inline bool paralelas(const Recta2d &r1,const Recta2d &r2)
  { return r1.Paralela(r2); }

bool intersecan(const Recta2d &r1,const Recta2d &r2);
GeomObj2d::list_Pos2d interseccion(const Recta2d &r1,const Recta2d &r2);
Pos2d punto_interseccion(const Recta2d &, const Recta2d &);

bool colineales(const Recta2d &r1,const Recta2d &r2);

inline bool operator!=(const Recta2d &r1,const Recta2d &r2)
  { return !(r1==r2); }

inline Recta2d bisectriz(const Recta2d &r1,const Recta2d &r2)
  { return r1.Bisectriz(r2); }
Recta2d mediatriz(const Pos2d &p1,const Pos2d &p2);
 
#endif




