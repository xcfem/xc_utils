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
//Pos2d.cc

#include "Pos2d.h"
#include <iostream>
#include <plotter.h>
#include "Vector2d.h"



#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/d1/Ray2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"

//! @brief Default constructor.
Pos2d::Pos2d(void)
  : ProtoGeom(), cgpt(CGAL::ORIGIN) {}

//! @brief Constructor.
Pos2d::Pos2d(const CGPoint_2 &p)
  : ProtoGeom(), cgpt(p) {}

//! @brief Constructor a partir de coordenadas cartesianas.
Pos2d::Pos2d(const GEOM_FT &Ax,const GEOM_FT &Ay)
  : ProtoGeom(), cgpt(Ax,Ay) {}

//! @brief Constructor a partir de coordenadas homogéneas.
Pos2d::Pos2d(const GEOM_RT &x,const GEOM_RT &y,const GEOM_RT &h)
  : ProtoGeom(), cgpt(x,y,h) {}

//! @brief Copy constructor
Pos2d::Pos2d(const Pos2d &other)
  : ProtoGeom(other), cgpt(other.cgpt) {}

//! @brief Assignment operator.
Pos2d &Pos2d::operator=(const Pos2d &other)
  {
    ProtoGeom::operator=(other);
    cgpt= other.cgpt;
    return *this;
  }

//! @brief Suma de un vector.
Pos2d &Pos2d::operator+=(const Vector2d &v)
  {
    operator=((*this)+v);
    return *this;
  }

//! @brie Resta de un vector.
Pos2d &Pos2d::operator-=(const Vector2d &v)
  {
    operator=((*this)-v);
    return *this;
  }

//! @brief Vector between points.
Vector2d Pos2d::operator-(const Pos2d &p) const
  {
    Vector2d retval(ToCGAL()-p.ToCGAL());
    return retval;
  }

//! @brief Return the point obtained by subtracting the vector.
Pos2d Pos2d::operator-(const Vector2d &v) const
  {
    Pos2d retval(ToCGAL()-v.ToCGAL());
    return retval;
  }

//! @brief Return the point obtained by adding the vector.
Pos2d Pos2d::operator+(const Vector2d &v) const
  {
    Pos2d retval(ToCGAL()+v.ToCGAL());
    return retval;
  }

//! @brief Return the position vector of the point.
Vector2d Pos2d::VectorPos(void) const
  { return (*this)-Origen2d; }

void Pos2d::SetX(const GEOM_FT &vx)
  { cgpt= CGPoint_2(vx,y()); }
void Pos2d::SetY(const GEOM_FT &vy)
  { cgpt= CGPoint_2(x(),vy); }
void Pos2d::Set(unsigned short int i,const GEOM_FT &v)
  {
    switch(i)
      {
      case 1:
        SetX(v);
        break;
      case 2:
        SetY(v);
        break;
      default:
	std::cerr << "Se esperaba que el índice fuera 1, 2 ó 3." << std::endl;
        break;
      }
  }

bool Pos2d::domina_a(const Pos2d &b) const
  {
    for(register size_t i= 1;i<=dimension();i++)
      if ((*this)(i)<b(i)) return false;
    return true;
  }

bool colineales(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3)
  { return collinear(p1.cgpt,p2.cgpt,p3.cgpt); } 

void Pos2d::Print(std::ostream &stream) const
  {
    stream << "x= " << x() << ','
           << "y= " << y();
  }

//! @brief Return the distance to the point.
GEOM_FT Pos2d::dist(const Pos2d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Return the squared distance to the point.
GEOM_FT Pos2d::dist2(const Pos2d &p) const
  { return squared_distance(cgpt,p.cgpt); }

//! @brief Return the squared distance to the line.
GEOM_FT Pos2d::dist2(const Line2d &r) const
  { return r.dist2(*this); }
  
//! @brief Return the distance to the line.
GEOM_FT Pos2d::dist(const Line2d &r) const
  { return r.dist(*this); }

//! @brief Return the squared distance to the ray.
GEOM_FT Pos2d::dist2(const Ray2d &sr) const
  { return sr.dist2(*this); }

//! @brief Return the distance to the ray.
GEOM_FT Pos2d::dist(const Ray2d &sr) const
  { return sr.dist(*this); }

//! @brief Return the squared distance to the segment.
GEOM_FT Pos2d::dist2(const Segment2d &sg) const
  { return sg.dist2(*this); }

//! @brief Return the distance to the segment.
GEOM_FT Pos2d::dist(const Segment2d &sg) const
  { return sg.dist(*this); }

void Pos2d::Plot(Plotter &plotter) const
  {
    plotter.fmarker(x(),y(),5,4.0); //Dibuja una cruz (5).
  }

std::ostream &operator<<(std::ostream &stream,const Pos2d &n)
  {
    n.Print(stream);
    return stream;
  }




