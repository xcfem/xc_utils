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
//Triangulo2d.cc

#include "Triangulo2d.h"
#include "Poligono2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include <plotter.h>
#include "xc_utils/src/geom/trf/Trf2d.h"

//! @brief Devuelve la base opuesta al vértice i.
Segmento2d Triangulo2d::Base(const size_t &i) const
  { return Lado(i%3+1); }
//! @brief Devuelve la altura correspondiente al vértice i.
Segmento2d Triangulo2d::Altura(const size_t &i) const
  {
    if(Degenerado())
      {
        cerr << "¡Ojo!, se pide la altura de un triángulo degenerado." << endl;
      }
    const Recta2d rbase= Base(i).RectaSoporte();
    const Recta2d perp= rbase.Perpendicular(Vertice(i));
    const Pos2d pint= *interseccion(rbase,perp).begin();
    return Segmento2d(Vertice(i),pint);
  }
GEOM_FT Triangulo2d::Longitud(void) const
  {
    GEOM_FT retval= Lado(1).Longitud();
    retval+= Lado(2).Longitud();
    retval+= Lado(3).Longitud();
    return retval;
  }
Pos2d Triangulo2d::Cdg(void) const
  {
    Vector2d v= Vertice(1).VectorPos();
    v= v+Vertice(2).VectorPos();
    v= v+Vertice(3).VectorPos();
    return Origen2d+v/3.0;
  }

GEOM_FT Triangulo2d::GetMax(unsigned short int i) const
  {
    GEOM_FT retval= Vertice(1)(i);
    retval= max(retval,Vertice(2)(i));
    retval=max(retval,Vertice(3)(i));
    return retval;
  }
GEOM_FT Triangulo2d::GetMin(unsigned short int i) const
  {
    GEOM_FT retval= Vertice(1)(i);
    retval= min(retval,Vertice(2)(i));
    retval=min(retval,Vertice(3)(i));
    return retval;
  }

Poligono2d Triangulo2d::GetPoligono(void) const
  {
    Poligono2d retval;
    retval.push_back(Vertice(1));
    retval.push_back(Vertice(2));
    retval.push_back(Vertice(3));
    return retval;
  }

bool Triangulo2d::procesa_comando(CmdStatus &status)
  {
    const string &cmd= deref_cmd(status.Cmd());
    //cerr << "(Triangulo2d) Procesando comando: " << cmd << endl;
    static Pos2d p1,p2,p3;
    if(cmd == "p1")
      {
        p1.LeeCmd(status);
        return true;
      }
    else if(cmd == "p2")
      {
        p2.LeeCmd(status);
        return true;
      }
    else if(cmd == "p3")
      {
        p3.LeeCmd(status);
        return true;
      }
    (*this)= Triangulo2d(p1,p2,p3);
    return SupPoligonal2d::procesa_comando(status);
  }
void Triangulo2d::Print(std::ostream &os) const
  { os << cgtriang; }
void Triangulo2d::Plot(Plotter &plotter) const
  {
    const Pos2d p1= Vertice(1);
    const Pos2d p2= Vertice(2);
    const Pos2d p3= Vertice(3);
    plotter.fline(p1.x(),p1.y(),p2.x(),p2.y());
    plotter.fline(p2.x(),p2.y(),p3.x(),p3.y());
    plotter.fline(p3.x(),p3.y(),p1.x(),p1.y());
  }

//! @brief Aplica a la recta la transformación que se
//! pasa como parámetro.
void Triangulo2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d pA= trf2d.Transforma(Vertice(1));
    const Pos2d pB= trf2d.Transforma(Vertice(2));
    const Pos2d pC= trf2d.Transforma(Vertice(3));
    (*this)= Triangulo2d(pA,pB,pC);
  }

void Triangulo2d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    std::cerr << "Triangulo2d::SalvaCmd no implementada" << std::endl;
  }
