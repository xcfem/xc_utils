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
//SemiRecta2d.cc

#include "SemiRecta2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include <plotter.h>
#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

SemiRecta2d::SemiRecta2d(const Pos2d &p1,const Pos2d &p2)
  : Linea2d(), cgsr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        clog << "SemiRecta2d::SemiRecta2d: La recta es degenerada, los puntos: "
             << p1 << " y " << p2 << " coinciden." << endl;
      }
  }
SemiRecta2d::SemiRecta2d(const Pos2d &p1,const Vector2d &vdir)
  : Linea2d(), cgsr(p1.ToCGAL(),vdir.ToCGAL()) {}
void SemiRecta2d::DosPuntos(const Pos2d &p1,const Pos2d &p2)
  { (*this)= SemiRecta2d(p1,p2); }
void SemiRecta2d::salva_miembros(std::ostream &os,const  std::string &indent) const
  {
/*         salva_org(os,indent); */
/*         os << indent << "\\dest{"; */
/*         PtoParametricas(100.0).salva_miembros(os,""); */
/*         os << '}' << endl; */
  }
void SemiRecta2d::salva_cmd(std::ostream &os,const  std::string &indent,const  std::string &obj) const
  {
    const  std::string str_indent= indent + "  ";
    os << indent << '\\' << obj << endl
       << str_indent << '{' << endl;
    salva_miembros(os,str_indent+ "  ");
    os << str_indent  << '}' << endl;
  }

bool SemiRecta2d::procesa_comando(CmdStatus &status)
  {
    Pos2d o,d;
    if(status.Cmd() == "org")
      {
        o.LeeCmd(status);
        (*this)= SemiRecta2d(o,d);
        return true;
      }
    else if(status.Cmd() == "dest")
      {
        d.LeeCmd(status);
        (*this)= SemiRecta2d(o,d);
        return true;
      }
    else
      return Linea2d::procesa_comando(status);
  }

Dir2d SemiRecta2d::GetDir(void) const
  { return Dir2d(cgsr.direction()); }
Vector2d SemiRecta2d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Devuelve el cuadrado de la distancia 
//! desde el punto a la semirrecta.
GEOM_FT SemiRecta2d::dist2(const Pos2d &p) const
  {
    Recta2d r= RectaSoporte();
    Pos2d proy= r.Proyeccion(p);
    GEOM_FT retval= p.dist2(proy); //Válido si el punto proyectado está en la semirrecta.
    if(!In(proy)) //El punto está fuera de la semirrecta.
      retval= p.dist2(Origen());
    return retval;
  }

//! @brief Devuelve la distancia 
//! desde el punto a la semirrecta.
GEOM_FT SemiRecta2d::dist(const Pos2d &p) const
  { return sqrt_FT(dist2(p)); }

bool SemiRecta2d::Interseca(const Recta2d &r) const
  { return do_intersect(r.cgr,cgsr); }

//! @brief Devuelve la intersección de la semirrecta con un plano coord_i=cte.
GeomObj2d::list_Pos2d SemiRecta2d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj2d::list_Pos2d lp;
    lp= RectaSoporte().Interseccion(i,d);
    if(!lp.empty())
      {
        const Vector2d i_= VDir();
        const double l= RectaSoporte().getLambda(i,d,i_);
        if(l<0.0)
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Devuelve el punto intersección de recta y semirrecta, si doesn't exists la
//! intersección devuelve la lista vacía.
GeomObj2d::list_Pos2d SemiRecta2d::Interseccion(const Recta2d &r) const
  {
    GeomObj2d::list_Pos2d retval;
    if(Interseca(r))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgsr,r.cgr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << "SemiRecta2d::Interseccion(Recta2d): Error desconocido." << endl
                 << "sg: " << *this << endl
                 << "r: " << r << endl;
          }
      }
    return retval;
  }

//Devuelve el punto intersección de ambas rectas, if doesn't exists la
//intersección devuelve la lista vacía.
GeomObj2d::list_Pos2d SemiRecta2d::Interseccion(const SemiRecta2d &r2) const
  {
    GeomObj2d::list_Pos2d retval;
    if(*this == r2)
      {
        cerr << "SemiRecta2d::interseccion(SemiRecta2d): Las semirectas coinciden, todos sus puntos pertenecen a la intersección." 
             << endl;
        return retval;
      }
    if(Interseca(r2))
      {
        CGAL::Object result;
        Pos2d ptoi;
        result = CGAL::intersection(this->cgsr,r2.cgsr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << "interseccion(SemiRecta2d,SemiRecta2d): Error desconocido." 
                 << endl;
          }
      }
    return retval;
  }


//! @brief Aplica a la semirrecta la transformación que se
//! pasa como parámetro.
void SemiRecta2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d p1= trf2d.Transforma(Origen());
    const Pos2d p2= trf2d.Transforma(Punto(100));
    (*this)= SemiRecta2d(p1,p2);
  }

void SemiRecta2d::Print(std::ostream &os) const
  { os << PtoParametricas(0.0) << " " << PtoParametricas(100.0); }
void SemiRecta2d::Plot(Plotter &psos) const
//La semirecta no se dibuja, primero hay que recortarla.
  {}

