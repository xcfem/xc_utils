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
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"

//! @brief Constructor por defecto.
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

//! @brief Constructor de copia.
Pos2d::Pos2d(const Pos2d &otro)
  : ProtoGeom(otro), cgpt(otro.cgpt) {}

//! @brief Operador asignación.
Pos2d &Pos2d::operator=(const Pos2d &otro)
  {
    ProtoGeom::operator=(otro);
    cgpt= otro.cgpt;
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

//! @brief Vector diferencia entre puntos.
Vector2d Pos2d::operator-(const Pos2d &p) const
  {
    Vector2d retval(ToCGAL()-p.ToCGAL());
    return retval;
  }

//! @brief Punto que resulta al restar el vector.
Pos2d Pos2d::operator-(const Vector2d &v) const
  {
    Pos2d retval(ToCGAL()-v.ToCGAL());
    return retval;
  }

//! @brief Punto que resulta al sumar el vector.
Pos2d Pos2d::operator+(const Vector2d &v) const
  {
    Pos2d retval(ToCGAL()+v.ToCGAL());
    return retval;
  }

//! @brief Lee un objeto Pos2d desde archivo
bool Pos2d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Pos2d) Procesando comando: " << cmd << std::endl;
    if(cmd == "x")
      {
        const double tmp= interpretaDouble(status.GetString());
        cgpt= CGPoint_2(double_to_FT(tmp),cgpt.y());
        return true;
      }
    else if(cmd == "y")
      {
        const double tmp= interpretaDouble(status.GetString());
        cgpt= CGPoint_2(cgpt.x(),double_to_FT(tmp));
        return true;
      }
    else if(cmd == "coo")
      {
        const std::vector<double> &crds= crea_vector_double(status.GetBloque());
        const size_t sz= crds.size();
        if(sz>=2)
          cgpt= CGPoint_2(crds[0],crds[1]);
        else if(sz>0)
          cgpt= CGPoint_2(crds[0],0.0);
        return true;
      }
    else
      return ProtoGeom::procesa_comando(status);
  }
void Pos2d::salva_miembros(std::ostream &os,const std::string &indent) const
  {
    os << indent << "\\x{" << x()
                 << "} \\y{" << y() 
                 << "} }";
  }
Vector2d Pos2d::VectorPos(void) const
  //Devuelve el vector de posición del punto.
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

void Pos2d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << "\\Pos2d{";
    salva_miembros(os,"");
    os << '}' << endl;
  }

void Pos2d::Print(std::ostream &stream) const
  {
    stream << "x= " << x() << ','
           << "y= " << y();
  }

//! @brief Devuelve la distancia al punto.
GEOM_FT Pos2d::dist(const Pos2d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Devuelve el cuadrado de la distancia al punto.
GEOM_FT Pos2d::dist2(const Pos2d &p) const
  { return squared_distance(cgpt,p.cgpt); }

//! @brief Devuelve el cuadrado de la distancia a la recta.
GEOM_FT Pos2d::dist2(const Recta2d &r) const
  { return r.dist2(*this); }
  
//! @brief Devuelve la distancia a la recta.
GEOM_FT Pos2d::dist(const Recta2d &r) const
  { return r.dist(*this); }

//! @brief Devuelve el cuadrado de la distancia a la semirrecta.
GEOM_FT Pos2d::dist2(const SemiRecta2d &sr) const
  { return sr.dist2(*this); }

//! @brief Devuelve la distancia a la semirrecta.
GEOM_FT Pos2d::dist(const SemiRecta2d &sr) const
  { return sr.dist(*this); }

//! @brief Devuelve el cuadrado de la distancia al segmento.
GEOM_FT Pos2d::dist2(const Segmento2d &sg) const
  { return sg.dist2(*this); }

//! @brief Devuelve la distancia al segmento.
GEOM_FT Pos2d::dist(const Segmento2d &sg) const
  { return sg.dist(*this); }

void Pos2d::Plot(Plotter &plotter) const
  {
    plotter.fmarker(x(),y(),5,4.0); //Dibuja una cruz (5).
  }
//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! x: Devuelve la coordenada x del punto.
//! y: Devuelve la coordenada y del punto.
any_const_ptr Pos2d::GetProp(const std::string &cod) const
  {
    static GEOM_FT tmp_ft= 0.0;
    if(cod=="x")
      {
        tmp_ft= x();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="y")
      {
        tmp_ft= y();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getVectorPos")
      {
        tmp_gp_vector2d= VectorPos();
        return any_const_ptr(tmp_gp_vector2d);
      }
    else
      return ProtoGeom::GetProp(cod);
  }

std::ostream &operator<<(std::ostream &stream,const Pos2d &n)
  {
    n.Print(stream);
    return stream;
  }




