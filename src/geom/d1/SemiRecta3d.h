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
//SemiRecta3d.h

#ifndef SEMIRECTA3D_H
#define SEMIRECTA3D_H

#include "Linea3d.h"
#include "Recta3d.h"
#include "../pos_vec/Pos3d.h"

class Dir3d;


//! @ingroup GEOM
//
//! @brief Semirrecta en tres dimensiones.
class SemiRecta3d : public Linea3d
  {
    CGSemiRecta_3 cgsr;
  public:
    SemiRecta3d(void): Linea3d(),cgsr(CGPoint_3(0,0,0),CGPoint_3(1,0,0)) {}
    SemiRecta3d(const CGSemiRecta_3 &r)
      : Linea3d(), cgsr(r) {}
    SemiRecta3d(const Pos3d &p1,const Pos3d &p2);
    SemiRecta3d(const SemiRecta3d &r)
      : Linea3d(),cgsr(r.cgsr) {}
    SemiRecta3d &operator=(const SemiRecta3d &r)
      {
	Linea3d::operator=(r);
        cgsr= r.cgsr;
        return *this;
      }

    virtual GeomObj *clon(void) const
      { return new SemiRecta3d(*this); }
    const CGSemiRecta_3 &ToCGAL(void) const
      { return cgsr; }
    void DosPuntos(const Pos3d &p1,const Pos3d &p2);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }
    Recta3d RectaSoporte(void) const
      { return Recta3d(cgsr.supporting_line()); }
    Pos3d Origen(void) const
      { return Pos3d(cgsr.source()); }
    inline GEOM_FT GetPendiente(void) const
      { return RectaSoporte().GetPendiente(); }
    const Pos3d Punto(const int &i) const
      { return Pos3d(cgsr.point(i)); }
    //! @brief Devuelve un punto de la recta a una "distancia" lambda del origen.
    Pos3d PtoParametricas(const GEOM_FT &lambda) const
      { return Punto(0)+lambda*VDir(); }
    inline bool EsDegenerada(void) const
      { return cgsr.is_degenerate(); }
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const
    //Devuelve verdadero si el punto está sobre la semirrecta.
      { return cgsr.has_on(p.ToCGAL()); }
    virtual GEOM_FT dist2(const Pos3d &p) const;
    GEOM_FT dist(const Pos3d &p) const;
    void Put(const Pos3d &p1,const Pos3d &p2)
    //Asigna valores a los puntos que definen la recta.
      { DosPuntos(p1,p2); }

    bool Paralela(const SemiRecta3d &r) const;
    bool Paralela(const Recta3d &r) const;

    GeomObj3d::list_Pos3d Interseccion(unsigned short int, const double &) const;
    GeomObj3d::list_Pos3d Interseccion(const Recta3d &r) const;
    GeomObj3d::list_Pos3d Interseccion(const SemiRecta3d &sr) const;

    //Devuelve el punto intersección de ambas rectas, si no existe la
    //intersección devuelve la lista vacía.
    inline virtual GEOM_FT Longitud(void) const
      { return NAN; }
    inline virtual Pos3d Cdg(void) const
      { return Pos3d(NAN,NAN,NAN); }
    Dir3d GetDir(void) const;
    Vector3d VDir(void) const;
    inline double Angulo(const Vector3d &v) const
      { return angulo(VDir(),v); }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }
    inline friend bool operator==(const SemiRecta3d &r1,const SemiRecta3d &r2)
      { return (r1.cgsr==r2.cgsr); }
    inline void Print(std::ostream &os) const
      { os << PtoParametricas(0.0) << " " << PtoParametricas(100.0); }
  };

inline GEOM_FT angulo(const SemiRecta3d &r,const Vector3d &v)
  { return r.Angulo(v); }
inline GEOM_FT angulo(const SemiRecta3d &sr,const Recta3d &r)
  { return r.Angulo(sr.VDir()); }
inline GEOM_FT angulo(const Recta3d &r,const SemiRecta3d &sr)
  { return r.Angulo(sr.VDir()); }

inline GEOM_FT dist2(const Pos3d &p,const SemiRecta3d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const SemiRecta3d &r,const Pos3d &p)
  { return r.dist2(p); }
inline GEOM_FT dist(const Pos3d &p,const SemiRecta3d &r)
  { return r.dist(p); }
inline GEOM_FT dist(const SemiRecta3d &r,const Pos3d &p)
  { return r.dist(p); }

inline bool paralelas(const SemiRecta3d &r1,const Recta3d &r2)
  { return r1.Paralela(r2); }
inline bool paralelas(const Recta3d &r1,const SemiRecta3d &r2)
  { return paralelas(r2,r1); }
inline bool paralelas(const SemiRecta3d &r1,const SemiRecta3d &r2)
  { return r1.Paralela(r2); }

inline GeomObj3d::list_Pos3d interseccion(const Recta3d &r1,const SemiRecta3d &r2)
  { return r2.Interseccion(r1); }
inline GeomObj3d::list_Pos3d interseccion(const SemiRecta3d &r1,const Recta3d &r2)
  { return r1.Interseccion(r2); }
inline GeomObj3d::list_Pos3d interseccion(const SemiRecta3d &r1,const SemiRecta3d &r2)
  { return r1.Interseccion(r2); }


inline bool colineales(const SemiRecta3d &sr,const Recta3d &r)
  { return colineales(sr.RectaSoporte(),r); }
inline bool colineales(const Recta3d &r,const SemiRecta3d &sr)
  { return colineales(sr,r); }
inline bool colineales(const SemiRecta3d &sr1,const SemiRecta3d &sr2)
  { return colineales(sr1,sr2.RectaSoporte()); }



#endif
