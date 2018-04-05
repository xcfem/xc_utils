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
//Segmento2d.h

#ifndef SEGMENTO2D_H
#define SEGMENTO2D_H

#include "Linea2d.h"
#include "Recta2d.h"
#include "SemiRecta2d.h"
#include "../pos_vec/Pos2d.h"

class Dir2d;
class VectorPos2d;

//! @ingroup GEOM
//
//! @brief Segmento en dos dimensiones.
class Segmento2d : public Linea2d
  {
    CGSegmento_2 cgseg;
  public:
    Segmento2d(void): Linea2d(),cgseg(CGPoint_2(0,0),CGPoint_2(1,0)) {}
    Segmento2d(const CGSegmento_2 &r)
      : Linea2d(), cgseg(r) {}
    Segmento2d(const Pos2d &p1,const Pos2d &p2);
    Segmento2d(const Segmento2d &r)
      : Linea2d(),cgseg(r.cgseg) {}
    Segmento2d &operator=(const Segmento2d &r)
      {
	Linea2d::operator=(r);
        cgseg= r.cgseg;
        return *this;
      }
    const CGSegmento_2 &ToCGAL(void) const
      { return cgseg; }
    virtual GeomObj *clon(void) const;
    void TwoPoints(const Pos2d &p1,const Pos2d &p2);
    virtual GEOM_FT GetMax(unsigned short int i) const
      { return std::max(Origen()(i),Destino()(i)); }
    virtual GEOM_FT GetMin(unsigned short int i) const
      { return std::min(Origen()(i),Destino()(i)); }
    Recta2d RectaSoporte(void) const
      { return Recta2d(cgseg.supporting_line()); }
    Pos2d Origen(void) const
      { return Pos2d(cgseg.source()); }
    Pos2d Destino(void) const
      { return Pos2d(cgseg.target()); }
    inline GEOM_FT getSlope(void) const
      { return RectaSoporte().getSlope(); }
    const Pos2d Point(const int &i) const
      { return Pos2d(cgseg.point(i)); }
    Pos2d PtoParametricas(const GEOM_FT &) const;
    double getParamCooNatural(const GEOM_FT &) const;
    Pos2d PtoCooNatural(const GEOM_FT &) const;
    inline bool EsVertical(void) const
      { return cgseg.is_vertical(); }
    inline bool EsDegenerada(void) const
      { return cgseg.is_degenerate(); }
    virtual bool In(const Pos2d &, const double &tol= 0.0) const;
    virtual GEOM_FT dist2(const Pos2d &p) const;
    GEOM_FT dist(const Pos2d &p) const;
    //! @brief Set the points that define the segment.
    void Put(const Pos2d &p1,const Pos2d &p2)
      { TwoPoints(p1,p2); }

    //! @brief Returns the points ordered by the value of the 
    //! parameter of its projection onto the line from lowest
    //! to highest. Origin is at Recta2d::Point(0).
    GeomObj::list_Pos2d Ordena(const GeomObj::list_Pos2d &ptos) const
      { return RectaSoporte().Ordena(ptos); }

    Segmento2d Offset(const Vector2d &v) const;
    Segmento2d Offset(const GEOM_FT &d) const;

    inline bool Interseca(const Segmento2d &r2) const
      { return do_intersect(cgseg,r2.cgseg); }
    bool Interseca(const Recta2d &r) const;
    bool Interseca(const SemiRecta2d &sr) const;
    GeomObj2d::list_Pos2d Interseccion(unsigned short int, const double &) const;
    GeomObj2d::list_Pos2d Interseccion(const Recta2d &r) const;
    GeomObj2d::list_Pos2d Interseccion(const SemiRecta2d &sr) const;
    GeomObj2d::list_Pos2d Interseccion(const Segmento2d &sg2) const;

    Recta2d Perpendicular(const Pos2d &p) const;
    Recta2d Paralela(const Pos2d &v) const;
    Recta2d Mediatriz(void) const;

    bool Paralelo(const Recta2d &r) const
      { return paralelas(RectaSoporte(),r); }
    bool Paralelo(const SemiRecta2d &sr) const
      { return paralelas(RectaSoporte(),sr); }
    bool Paralelo(const Segmento2d &r) const
      { return paralelas(RectaSoporte(),r.RectaSoporte()); }

    virtual GEOM_FT Longitud(void) const;
    virtual Pos2d Cdg(void) const;
    Dir2d GetDir(void) const;
    Vector2d VDir(void) const;
    Vector2d Normal(void) const;
    Vector2d GetVector(void) const;
    GEOM_FT Angulo(const Vector2d &v) const;
    GEOM_FT AnguloSigno(const Vector2d &v) const;
    GEOM_FT Angulo(const Segmento2d &v) const;
    GEOM_FT AnguloSigno(const Segmento2d &v) const;
    GEOM_FT AnguloEjeX(void) const;
    GEOM_FT AnguloEjeY(void) const;
    inline GEOM_FT Azimuth(void) const
      { return RectaSoporte().Azimuth(); }

    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //Producto de inercia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }
    VectorPos2d Divide(int num_partes) const;

    void Transforma(const Trf2d &trf2d);

    inline friend bool operator==(const Segmento2d &r1,const Segmento2d &r2)
      { return (r1.cgseg==r2.cgseg); }
    void Print(std::ostream &os) const;
    void Plot(Plotter &) const;
  };

inline GEOM_FT dist2(const Pos2d &p,const Segmento2d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const Segmento2d &r,const Pos2d &p)
  { return dist2(p,r); }
GEOM_FT dist(const Pos2d &p,const Segmento2d &r);
inline GEOM_FT dist(const Segmento2d &r,const Pos2d &p)
  { return dist(p,r); }

GEOM_FT angulo(const Segmento2d &,const Vector2d &);
GEOM_FT angulo(const Vector2d &,const Segmento2d &);

inline bool paralelas(const Segmento2d &sg,const Recta2d &r)
  { return sg.Paralelo(r); }
inline bool paralelas(const Recta2d &r, const Segmento2d &sg)
  { return paralelas(sg,r); }
inline bool paralelas(const Segmento2d &sg,const SemiRecta2d &sr)
  { return sg.Paralelo(sr); }
inline bool paralelas(const SemiRecta2d &sr, const Segmento2d &sg)
  { return paralelas(sg,sr); }
inline bool paralelas(const Segmento2d &r1,const Segmento2d &r2)
  { return r1.Paralelo(r2); }

inline bool intersecan(const Segmento2d &sg,const Recta2d &r)
  { return sg.Interseca(r); }
inline bool intersecan(const Recta2d &r,const Segmento2d &sg)
  { return sg.Interseca(r); }
inline bool intersecan(const Segmento2d &sg,const SemiRecta2d &sr)
  { return sg.Interseca(sr); }
inline bool intersecan(const SemiRecta2d &sr,const Segmento2d &sg)
  { return sg.Interseca(sr); }
inline bool intersecan(const Segmento2d &r1,const Segmento2d &r2)
  { return r1.Interseca(r2); }
inline GeomObj2d::list_Pos2d interseccion(const Segmento2d &sg,const Recta2d &r)
  { return sg.Interseccion(r); }
inline GeomObj2d::list_Pos2d interseccion(const Recta2d &r,const Segmento2d &sg)
  { return sg.Interseccion(r); }
inline GeomObj2d::list_Pos2d interseccion(const Segmento2d &sg,const SemiRecta2d &sr)
  { return sg.Interseccion(sr); }
inline GeomObj2d::list_Pos2d interseccion(const SemiRecta2d &sr,const Segmento2d &sg)
  { return sg.Interseccion(sr); }
inline GeomObj2d::list_Pos2d interseccion(const Segmento2d &sg1,const Segmento2d &sg2)
  { return sg1.Interseccion(sg2); }

inline bool colineales(const Segmento2d &sg,const Recta2d &r)
  { return colineales(sg.RectaSoporte(),r); }
inline bool colineales(const Recta2d &r,const Segmento2d &sg)
  { return colineales(sg,r); }
inline bool colineales(const Segmento2d &sg,const SemiRecta2d &sr)
  { return colineales(sg.RectaSoporte(),sr); }
inline bool colineales(const SemiRecta2d &sr,const Segmento2d &sg)
  { return colineales(sg,sr); }
inline bool colineales(const Segmento2d &sg1,const Segmento2d &sg2)
  { return colineales(sg1,sg2.RectaSoporte()); }

Pos2d intersection_point(const Segmento2d &, const Recta2d &);
Pos2d intersection_point(const Recta2d &, const Segmento2d &);
Pos2d intersection_point(const Segmento2d &, const Segmento2d &);

inline Recta2d mediatriz(const Segmento2d &sg)
  { return sg.Mediatriz(); }

std::list<Segmento2d> sin_degenerados(const std::list<Segmento2d> &);


#endif
