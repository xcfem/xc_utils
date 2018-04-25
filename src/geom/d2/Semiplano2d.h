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
//Semiplano2d.h

#ifndef SEMIPLANO2D_H
#define SEMIPLANO2D_H


#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d2/Superficie2d.h"

class GmGrupo2d;
class SemiRecta2d;
class Segmento2d;


//! @ingroup GEOM
//
//! @brief Semiplano en dos dimensiones.
class Semiplano2d : public Superficie2d
  {
    Recta2d lim; //The points of the half-plane are those we lie to the right of the line.
  public:
    Semiplano2d(void);
    explicit Semiplano2d(const Recta2d &r);
    Semiplano2d(const Recta2d &r, const Pos2d &p);
    Semiplano2d(const Pos2d &p1,const Pos2d &p2);
    Semiplano2d(const Semiplano2d &sp);
    Semiplano2d &operator=(const Semiplano2d &sp);
    virtual GeomObj *clon(void) const;
    inline void Swap(void);
    Semiplano2d GetSwap(void) const;

    //! @brief Return el valor de a que corresponde a la ecuación de la recta: a*x + b*y + c= 0
    inline GEOM_RT a(void) const
      { return lim.a(); }
    inline GEOM_RT b(void) const
    //Return el valor de a que corresponde a la 
    //ecuación de la recta: a*x + b*y + c= 0
      { return lim.b(); }
    inline GEOM_RT c(void) const
    //Return el valor de a que corresponde a la 
    //ecuación de la recta: a*x + b*y + c= 0
      { return lim.c(); } 
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }
    inline bool EsDegenerado(void) const
      { return lim.EsDegenerada(); }
    inline const Recta2d &getBorde(void) const
      { return lim; }
    //! @brief Return true if the point is inside the half-plane.
    //! The points of the edge line belong to the half-plane.
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const
      { 
        if(lim.In(p,tol)) return true;
        if(lim.LadoDerecho(p)) return true;
        return false;
      }
    //! @brief Return the signed distance from the point to the half-plane.
    GEOM_FT DistSigno(const Pos2d &p) const
      {
        GEOM_FT retval= lim.dist(p);
        if(In(p)) retval= -retval;
        return retval;
      }
    //! @brief Return the distance from the point to the half-plane.
    inline virtual GEOM_FT Dist(const Pos2d &p) const
      { return fabs(DistSigno(p)); }

    Semiplano2d getNormalizado(void) const;

    inline bool Interseca(const Semiplano2d &r2) const
      { return lim.Interseca(r2.lim); }
    inline bool Interseca(const Recta2d &r) const
      { return lim.Interseca(r); }
    bool Interseca(const SemiRecta2d &sr) const;
    bool Interseca(const Segmento2d &sg) const;
    GmGrupo2d Interseccion(const Recta2d &r) const;
    GmGrupo2d Interseccion(const SemiRecta2d &sr) const;
    GmGrupo2d Interseccion(const Segmento2d &sg) const;

    inline virtual GEOM_FT Longitud(void) const
      { return NAN; }
    inline virtual Pos2d Cdg(void) const
      { return lim.Cdg(); }
    //Moment of inertia with respect to CDG in local coordinates.
    inline virtual GEOM_FT Ix(void) const
      { return NAN; }
    //Moment of inertia with respect to CDG in local coordinates.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //product of inertia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //Moment of inertia with respect to CDG in local coordinates.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }

    void Transforma(const Trf2d &trf2d);

    inline friend bool operator==(const Semiplano2d &r1,const Semiplano2d &r2)
      {
        if(&r1.lim==&r2.lim) return true;
        else
          return (r1.lim==r2.lim); 
      }
    inline void Print(std::ostream &os) const
      { os << lim; }
  };

inline GEOM_FT dist(const Pos2d &p,const Semiplano2d &r)
  { return r.Dist(p); }
inline GEOM_FT dist(const Semiplano2d &r,const Pos2d &p)
  { return dist(p,r); }
inline bool operator!=(const Semiplano2d &r1,const Semiplano2d &r2)
  { return !(r1==r2); }

inline bool intersecan(const Semiplano2d &sp1,const Semiplano2d &sp2)
  { return sp1.Interseca(sp2); }
inline bool intersecan(const Semiplano2d &sp,const Recta2d &r)
  { return sp.Interseca(r); }
inline bool intersecan(const Semiplano2d &sp,const SemiRecta2d &sr)
  { return sp.Interseca(sr); }
inline bool intersecan(const Semiplano2d &sp,const Segmento2d &sg)
  { return sp.Interseca(sg); }
inline bool intersecan(const Recta2d &r,const Semiplano2d &sp)
  { return sp.Interseca(r); }
inline bool intersecan(const SemiRecta2d &sr,const Semiplano2d &sp)
  { return sp.Interseca(sr); }
inline bool intersecan(const Segmento2d &sg,const Semiplano2d &sp)
  { return sp.Interseca(sg); }

GmGrupo2d interseccion(const Semiplano2d &sp,const Recta2d &r);
GmGrupo2d interseccion(const Semiplano2d &sp,const SemiRecta2d &sr);
GmGrupo2d interseccion(const Semiplano2d &sp,const Segmento2d &sg);
GmGrupo2d interseccion(const Recta2d &r,const Semiplano2d &sp);
GmGrupo2d interseccion(const SemiRecta2d &sr,const Semiplano2d &sp);
GmGrupo2d interseccion(const Segmento2d &sg,const Semiplano2d &sp);

#endif
