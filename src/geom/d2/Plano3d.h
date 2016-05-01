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
//Plano3d.h

#ifndef PLANO3D_H
#define PLANO3D_H

#include <cstdlib>
#include <cmath>
#include "xc_basic/src/util/matem.h"
#include "Superficie3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "../tipos_cgal.h"
#include <list>

class Recta3d;
class SemiRecta3d;
class Segmento3d;
class Polilinea3d;
class Poligono3d;
class GmGrupo3d;
class EcuacionGeneralPlano3d;
class SisCooRect2d3d;
class Ref2d3d;


//! @ingroup GEOM
//
//! @brief Plano en tres dimensiones. Se define como el
//! plano xy del triedro definido por el miembro "ref".
class Plano3d : public Superficie3d
  {
    CGPlane_3 cgp;
  public:

    typedef enum{DELANTE,DETRAS,DENTRO,CRUZA} clasif_poligono;

  protected:
    static clasif_poligono clfpnt2clfpol(const CGAL::Oriented_side os);
  public:
    Plano3d(void);
    explicit Plano3d(const CGPlane_3 &cgp);
    Plano3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Plano3d(const Pos3d &o,const Vector3d &v);
    Plano3d(const Pos3d &p,const Vector3d &v1,const Vector3d &v2);
    Plano3d(const Recta3d &r,const Pos3d &p);
    Plano3d(const Segmento3d &s,const Vector3d &v);
    Plano3d(const Poligono3d &trg);
    Plano3d(const Plano3d &otro);
    Plano3d(const EcuacionGeneralPlano3d &eg);
    Plano3d(const GeomObj3d::list_Pos3d &lp);
    Plano3d &operator=(const Plano3d &otro);

    virtual GeomObj *clon(void) const;
    const CGPlane_3 &ToCGAL(void) const
      { return cgp; }
    void TresPuntos(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int i) const
      { return NAN; }
    Pos3d Proyeccion(const Pos3d &) const;
    Vector3d Proyeccion(const Vector3d &) const;
    Recta3d Proyeccion(const Recta3d &) const;
    GeomObj3d::list_Pos3d Proyeccion(const GeomObj3d::list_Pos3d &) const;
    //Poligono3d Proyeccion(const Poligono3d &) const;

    virtual Vector3d Normal(void) const;
    Vector3d Base1(void) const;
    Vector3d Base2(void) const;
    SisCooRect2d3d getSisCoo(void) const;
    Ref2d3d getRef(const Pos3d &) const;

    void Swap(void);
    Plano3d GetSwap(void) const;

    bool LadoPositivo(const Pos3d &p) const;
    bool LadoNegativo(const Pos3d &p) const;
    virtual bool In(const Pos3d &p, const GEOM_FT &tol= 0.0) const;

    CGAL::Oriented_side ClasificaPunto(const Pos3d &p) const;

    template <typename InputIterator>
    clasif_poligono ClasificaPuntos(InputIterator first,InputIterator last) const;
    clasif_poligono ClasificaPoligono(const Poligono3d &pol) const;

    GEOM_FT PseudoDist(const Pos3d &p) const;
    GEOM_FT PseudoDist2(const Pos3d &p) const;
    virtual GEOM_FT dist2(const Pos3d &p) const;
    virtual GEOM_FT dist(const Pos3d &p) const;
    //! @brief Asigna valores a los puntos que definen el Plano.
    void Put(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
      { TresPuntos(p1,p2,p3); }

    EcuacionGeneralPlano3d GetEcuacionGeneral(void) const;
    void EcuacionGeneral(const EcuacionGeneralPlano3d &eq);
    GEOM_FT x(const Pos2d &p) const;
    GEOM_FT y(const Pos2d &p) const;
    GEOM_FT z(const Pos2d &p) const;

    virtual Pos3d Cdg(void) const;
    Pos3d Punto(void) const;
    //! @brief Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Ix(void) const
      { return NAN; }
    //! @brief Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //! @brief Momento de inercia respecto al CDG en ejes locales.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }

    Recta3d TrazaXY(void) const;
    Recta3d TrazaXZ(void) const;
    Recta3d TrazaYZ(void) const;
    Recta3d RectaMaximaPendienteXY(void) const;
    Recta3d RectaMaximaPendienteXZ(void) const;
    Recta3d RectaMaximaPendienteYZ(void) const;

    bool Interseca(const Plano3d &p) const;
    Recta3d Interseccion(const Plano3d &p) const;
    bool Interseca(const Recta3d &p) const;
    Pos3d Interseccion(const Recta3d &p) const;
    bool Interseca(const SemiRecta3d &p) const;
    Pos3d Interseccion(const SemiRecta3d &p) const;
    bool Interseca(const Segmento3d &p) const;
    Pos3d Interseccion(const Segmento3d &p) const;

    GEOM_FT Angulo(const Plano3d &p) const;
    GEOM_FT Angulo(const Vector3d &) const;
    GEOM_FT AnguloPendienteXY(void) const;
    GEOM_FT AnguloPendienteXZ(void) const;
    GEOM_FT AnguloPendienteYZ(void) const;

    GEOM_FT AjusteMinimosCuadrados(const GeomObj3d::list_Pos3d &lp);

    friend Plano3d FromCGAL(const CGPlane_3 &p);
    friend bool operator==(const Plano3d &p1,const Plano3d &p2);
    void Print(std::ostream &os) const;
  };

Plano3d FromCGAL(const CGPlane_3 &p);
bool operator==(const Plano3d &p1,const Plano3d &p2);

const Plano3d PlanoXY3d(Pos3d(0,0,0),Pos3d(1,0,0),Pos3d(0,1,0));
const Plano3d PlanoXZ3d(Pos3d(0,0,0),Pos3d(1,0,0),Pos3d(0,0,1));
const Plano3d PlanoYZ3d(Pos3d(0,0,0),Pos3d(0,1,0),Pos3d(0,0,1));

GEOM_FT angulo(const Recta3d &r,const Plano3d &p);
GEOM_FT angulo(const Plano3d &p,const Recta3d &r);
GEOM_FT angulo(const Vector3d &,const Plano3d &);
GEOM_FT angulo(const Plano3d &,const Vector3d &);
GEOM_FT angulo(const Plano3d &,const Plano3d &);


Plano3d perpendicular(const Recta3d &r, const Pos3d &p);
//Devuelve el plano perpendicular a la recta r
//que pasa por el punto p.

bool paralelos(const Plano3d &p, const Recta3d &r);
bool paralelos(const Plano3d &p1, const Plano3d &p2);


Recta3d recta_interseccion(const Plano3d &, const Plano3d &);
Pos3d punto_interseccion(const Plano3d &, const Plano3d &,const Plano3d &);
GmGrupo3d interseccion(const Plano3d &p1, const Plano3d &p2);
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Recta3d &r);
GeomObj3d::list_Pos3d interseccion(const Recta3d &r, const Plano3d &p);
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const SemiRecta3d &r);
GeomObj3d::list_Pos3d interseccion(const SemiRecta3d &r, const Plano3d &p);
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Segmento3d &);
GeomObj3d::list_Pos3d interseccion(const Segmento3d &, const Plano3d &p);
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Polilinea3d &r);
GeomObj3d::list_Pos3d interseccion(const Polilinea3d &r, const Plano3d &p);
Pos3d punto_interseccion(const Plano3d &p, const Recta3d &r);
Pos3d punto_interseccion(const Recta3d &r, const Plano3d &p);
Pos3d punto_interseccion(const Plano3d &p, const SemiRecta3d &r);
Pos3d punto_interseccion(const SemiRecta3d &r, const Plano3d &p);
Pos3d punto_interseccion(const Plano3d &p, const Segmento3d &r);
Pos3d punto_interseccion(const Segmento3d &r, const Plano3d &p);

GeomObj3d::list_Pos3d puntos_interseccion(const std::deque<Plano3d> &);

template <typename InputIterator>
Plano3d::clasif_poligono Plano3d::ClasificaPuntos(InputIterator first,InputIterator last) const
  {
    InputIterator i= first;
    CGAL::Oriented_side cf_pinic= ClasificaPunto(*i); i++;
    for(;i!=last;i++)
      {
        const CGAL::Oriented_side cf_punto= ClasificaPunto(*i);
        if(cf_punto!=cf_pinic)
          {
            if(cf_pinic!=CGAL::ON_ORIENTED_BOUNDARY) //Punto inicial fuera de plano.
              if(cf_punto!=CGAL::ON_ORIENTED_BOUNDARY) //Punto *i fuera de plano.
                return CRUZA;
              else //Punto *i dentro de plano.
                continue;
            else //Punto inicial dentro de plano.
              if(cf_punto!=CGAL::ON_ORIENTED_BOUNDARY) //Punto *i fuera de plano.
                {
                  cf_pinic= cf_punto;
                  continue;
                }
              else //Punto *i dentro de plano.
                continue;
          }
      }
    //Si llegamos hasta aquí es que todos tienen la
    //misma clasificación.
    return clfpnt2clfpol(cf_pinic);
  }


/* class SemiRecta; */

/* GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const SemiRecta3d &sr); */
/* inline GeomObj3d::list_Pos3d interseccion(const SemiRecta3d &sr, const Plano3d &p) */
/*   { return interseccion(p,sr); }  */


#endif

