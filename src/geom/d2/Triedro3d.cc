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
//Triedro3d.cc

#include "Triedro3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d3/poliedros3d/Poliedro3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"

Triedro3d::Triedro3d(void)
  : GeomObj3d(), p0(Pos3d(0,0,0)), tr(Pos3d(1,0,0),Pos3d(0,1,0),Pos3d(0,0,1)) {}
Triedro3d::Triedro3d( const Pos3d &P0, const Pos3d &p1, const Pos3d &p2, const Pos3d &p3)
  : GeomObj3d(), p0(P0), tr(p1,p2,p3) {}
Triedro3d::Triedro3d(const Pos3d &P0, const Triangulo3d &TR)
  : GeomObj3d(), p0(P0), tr(TR){}

Poliedro3d Triedro3d::GetPoliedro3d(void) const
  {
    Poliedro3d retval(Vertice(0),Vertice(1),Vertice(2),Vertice(3));
    return retval;
  }

Plano3d Triedro3d::get_plano(const size_t &i) const
  {
    Poliedro3d tmp(GetPoliedro3d());
    Poliedro3d::Facet_const_iterator j= tmp.facets_begin();
    for(size_t k=0;k<i;k++)
      j++;
    return tmp.GetPlanoCara(j);
  }

//! @brief Devuelve el triángulo que sirve de base al triedro.
const Triangulo3d &Triedro3d::Base(void) const
  { return tr; }

//! @brief Devuelve la cúspide del triedro.
const Pos3d &Triedro3d::Cuspide(void) const
  { return p0; }


//! @brief Devuelve la recta que pasa por la cúspide del triedro
//! y por el CDG de su base.
Recta3d Triedro3d::Eje(void) const
  { return Recta3d(p0,tr.Cdg()); }

//! @brief Devuelve el ángulo del cono que, con vértice en la cúspide,
//! contiene al triedro.
GEOM_FT Triedro3d::GetAnguloConico(void) const
  {
    const Recta3d eje= Eje();
    GEOM_FT angConico= angulo(eje,Recta3d(p0,Vertice(1)));
    angConico= std::max(angConico, angulo(eje,Recta3d(p0,Vertice(2))));
    angConico= std::max(angConico, angulo(eje,Recta3d(p0,Vertice(3))));
    return angConico;
  }

Pos3d Triedro3d::Vertice(const size_t &i) const
  {
    if(i==0)
      return p0;
    else
      return tr.Vertice(i);
  }

//! @brief Devuelve la distancia CON SIGNO desde el punto al tetraedro.
//! La distancia se calcula como el máximo de la distancia del punto a cada uno de los planos
//! que limitan el triedro.
GEOM_FT Triedro3d::PseudoDist(const Pos3d &p) const
  {
    Poliedro3d tmp= GetPoliedro3d();
    Poliedro3d::Facet_const_iterator j= tmp.facets_begin();
    Plano3d plano= tmp.GetPlanoCara(j);
    GEOM_FT dmax= -plano.PseudoDist(p);
    j++;
    for(;j!=tmp.facets_end();j++)
      {
        plano= tmp.GetPlanoCara(j);
        dmax= std::max(dmax,-plano.PseudoDist(p));
      }
    return dmax;
  }

//! @brief Devuelve verdadero si el punto esta contenido en el triedro.
bool Triedro3d::In(const Pos3d &p,const double &tol) const
  {
    const Recta3d eje= Eje();
    GEOM_FT d= eje.dist(p);
    GEOM_FT radioCilindro= eje.dist(Vertice(1));
    radioCilindro= std::max(radioCilindro,eje.dist(Vertice(2)));
    radioCilindro= std::max(radioCilindro,eje.dist(Vertice(3)));
    bool retval= true;
    if((d-radioCilindro)>tol)
      return false;
    else
      {
        const GEOM_FT angConico= fabs(GetAnguloConico());
        const GEOM_FT ang= fabs(angulo(eje,Recta3d(p0,p)));
        if(ang<1.1*angConico)
          {
            Poliedro3d tmp= GetPoliedro3d();
            Plano3d plano;
            for(Poliedro3d::Facet_const_iterator j= tmp.facets_begin();j!=tmp.facets_end();j++)
              {
                plano= tmp.GetPlanoCara(j);
                d= -plano.PseudoDist(p);
                if(d>=tol)
                  {
                    retval= false;
                    break;
                  }
              }
          }
        else
          return false;
      }
    return retval;
  }

void Triedro3d::Put( const Pos3d &P0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3)
  { Put(P0,Triangulo3d(p1,p2,p3)); }

void Triedro3d::Put(const Pos3d &P0,const Triangulo3d &TR)
  {
    p0= P0;
    tr= TR;
  }

GEOM_FT Triedro3d::GetMax(short unsigned int i) const
  { return GetPoliedro3d().GetMax(i); }
GEOM_FT Triedro3d::GetMin(short unsigned int i) const
  { return GetPoliedro3d().GetMin(i); }
Pos3d Triedro3d::Cdg() const
  { return GetPoliedro3d().Cdg(); }

//! @brief Devuelve verdadero si alguno de los vertices del triángulo toca el cuadrante
//! que se pasa como parámetro.
bool Triedro3d::TocaCuadrante(const int &cuadrante) const
  {
    return tr.TocaCuadrante(cuadrante); 
  }

void Triedro3d::Print(std::ostream &os) const
  {
    Poliedro3d tmp= GetPoliedro3d();
    Poliedro3d::Vertex_const_iterator i= tmp.vertices_begin();
    for(;i!=tmp.vertices_end();i++)
      os << i->point() << ", ";
  }
