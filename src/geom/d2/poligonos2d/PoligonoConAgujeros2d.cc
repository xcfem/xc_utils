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
//PoligonoConAgujeros2d.cc

#include "PoligonoConAgujeros2d.h"
#include "Poligono2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"



//! @brief Constructor por defecto.
PoligonoConAgujeros2d::PoligonoConAgujeros2d(void)
  : Superficie2d(){}

//! @brief Constructor por defecto.
PoligonoConAgujeros2d::PoligonoConAgujeros2d(const Poligono2d &p)
  : Superficie2d(), cgpol(p.ToCGAL()) {}

//! @brief Constructor virtual.
GeomObj *PoligonoConAgujeros2d::clon(void) const
  { return new PoligonoConAgujeros2d(*this); }

void PoligonoConAgujeros2d::contour(const Poligono2d &plg)
  { cgpol= CGPoligonoConAgujeros_2(plg.ToCGAL()); }

GEOM_FT PoligonoConAgujeros2d::Longitud(void) const
  {
    GEOM_FT temp = 0;
    for(Hole_const_iterator i= cgpol.holes_begin();i!=cgpol.holes_end();i++)
      {
        const Poligono2d p(*i);
        temp += p.Longitud();
      }
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp += p.Longitud();
      }      
    return temp;
  }

GEOM_FT PoligonoConAgujeros2d::Area(void) const
  {
    GEOM_FT temp = 0;
    for(Hole_const_iterator i= cgpol.holes_begin();i!=cgpol.holes_end();i++)
      {
        const Poligono2d p(*i);
        temp-= p.Area();
      }
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp+= p.Area();
      }
    else
      std::cerr << "PoligonoConAgujeros2d::Area; exterior contour doesn't exists." << std::endl;
    return temp;    
  }

//! @brief Devuelve el valor maximo de la coordenada i.
GEOM_FT PoligonoConAgujeros2d::GetMax(unsigned short int i) const
  { 
    GEOM_FT temp = 0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp= p.GetMax(i);
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMax; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        temp= std::max(temp,p.GetMax(i));
      }
    return temp;
  }

//! @brief Devuelve el valor minimo de la coordenada i.
GEOM_FT PoligonoConAgujeros2d::GetMin(unsigned short int i) const
  {
    GEOM_FT temp = 0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        temp= p.GetMin(i);
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        temp= std::min(temp,p.GetMin(i));
      }
    return temp;
  }

//! @brief Devuelve verdadero si el punto está contenido en el polígono.
bool PoligonoConAgujeros2d::In(const Pos2d &p, const double &tol) const
  {
    bool retval= false;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d pol(cgpol.outer_boundary());
        retval= pol.In(p,tol);
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    if(retval)
      for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
        {
          const Poligono2d pol(*j);
          if(pol.In(p,tol))
            {
              retval= false;
              break;
            }
        }
    return retval;

  }

//! @brief Devuelve el centro de gravedad.
Pos2d PoligonoConAgujeros2d::Cdg(void) const
  {
    GEOM_FT areaTotal= Area();
    Vector2d vPos;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        vPos= p.Cdg().VectorPos()*p.Area();
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        vPos= vPos-p.Cdg().VectorPos()*p.Area();
      }
    vPos= vPos*(1.0/areaTotal);
    return Pos2d(vPos.x(),vPos.y());
  }



//! @brief Calcula el momento de inercia respecto a un eje paralelo al
//! eje x que pasa por el CDG de la sección.
//! Ix = Integral y^2 dA
GEOM_FT PoligonoConAgujeros2d::Ix(void) const
  { 
    Pos2d cdg= Cdg();
    GEOM_FT retval= 0.0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        retval+= p.Ix()+p.Area()*sqr(p.Cdg().y()-cdg.y());
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        retval-= p.Ix()+p.Area()*sqr(p.Cdg().y()-cdg.y());
      }
    return retval;
  }

//! @brief Calcula el momento de inercia respecto a un eje paralelo al
//! eje y que pasa por el CDG del polígono.
//! Iy = Integral x^2 dA
GEOM_FT PoligonoConAgujeros2d::Iy(void) const
  { 
    Pos2d cdg= Cdg();
    GEOM_FT retval= 0.0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        retval+= p.Iy()+p.Area()*sqr(p.Cdg().x()-cdg.x());
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        retval-= p.Iy()+p.Area()*sqr(p.Cdg().x()-cdg.x());
      }
    return retval;
  }

//! @brief Calcula el producto de inercia respecto a los ejes paralelos
//! a los x e y que pasan por el CDG del polígono.
//! Pxy = Integral x*y dA
GEOM_FT PoligonoConAgujeros2d::Pxy(void) const
  {
    Pos2d cdg= Cdg();
    GEOM_FT retval= 0.0;
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
        const GEOM_FT dx= p.Cdg().x()-cdg.x();
        const GEOM_FT dy= p.Cdg().y()-cdg.y();
        retval+= p.Pxy()+p.Area()*dx*dy;
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
        const GEOM_FT dx= p.Cdg().x()-cdg.x();
        const GEOM_FT dy= p.Cdg().y()-cdg.y();
        retval-= p.Iy()+p.Area()*dx*dy;
      }
    return retval;
  }

//! @brief Hace un agujero en este polígono con
//! la forma del que se le pasa como parámetro.
void PoligonoConAgujeros2d::add_hole(const Poligono2d &p)
  { cgpol.add_hole(p.ToCGAL()); }

//! @brief Aplica la transformación que se pasa como parámetro
PoligonoConAgujeros2d PoligonoConAgujeros2d::getTransformado(const Trf2d &trf2d)
  {
    PoligonoConAgujeros2d retval;
    if(!cgpol.is_unbounded())
      {
        Poligono2d p(cgpol.outer_boundary());
        p.Transforma(trf2d);
        retval.cgpol= CGPoligonoConAgujeros_2(p.ToCGAL());
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        Poligono2d p(*j);
        p.Transforma(trf2d);
        retval.cgpol.add_hole(p.ToCGAL());
      }
    return retval;
  }

//! @brief Aplica la transformación que se pasa como parámetro
void PoligonoConAgujeros2d::Transforma(const Trf2d &trf2d)
  {
    PoligonoConAgujeros2d tmp= getTransformado(trf2d);
    PoligonoConAgujeros2d::operator=(tmp); 
  }

void PoligonoConAgujeros2d::Print(std::ostream &os) const
  {
    if(!cgpol.is_unbounded())
      {
        const Poligono2d p(cgpol.outer_boundary());
	os << "contorno: " << p << std::endl;
      }
    else
      std::cerr << "PoligonoConAgujeros2d::GetMin; exterior contour doesn't exists." << std::endl;

    for(Hole_const_iterator j= cgpol.holes_begin();j!=cgpol.holes_end();j++)
      {
        const Poligono2d p(*j);
	os << "hueco: " << p << std::endl;
      }
  }
