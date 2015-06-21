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
//Pos3d.cc

#include "Pos3d.h"
#include "Pos2d.h"
#include "../d2/Plano3d.h"
#include "Vector3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/SemiRecta3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/geom/d3/Solido3d.h"

//! @brief Suma de un vector.
Pos3d &Pos3d::operator+=(const Vector3d &v)
  {
    operator=((*this)+v);
    return *this;
  }

//! @brief Resta de un vector.
Pos3d &Pos3d::operator-=(const Vector3d &v)
  {
    operator=((*this)-v);
    return *this;
  }

//! @brief Vector diferencia entre puntos.
Vector3d Pos3d::operator-(const Pos3d &p) const
  {
    Vector3d retval(ToCGAL()-p.ToCGAL());
    return retval;
  }

//! @brief Punto que resulta al restar el vector.
Pos3d Pos3d::operator-(const Vector3d &v) const
  {
    Pos3d retval(ToCGAL()-v.ToCGAL());
    return retval;
  }

//! @brief Punto que resulta al sumar el vector.
Pos3d Pos3d::operator+(const Vector3d &v) const
  {
    Pos3d retval(ToCGAL()+v.ToCGAL());
    return retval;
  }

//! @brief Interpreta comandos del objeto.
bool Pos3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    static GEOM_FT x=0,y=0,z=0;
    x= cgpt.x(); y= cgpt.y(); z= cgpt.z();
    if(verborrea>2)
      std::clog << "(Pos3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "x")
      {
        x= interpretaDouble(status.GetString());
        cgpt= CGPoint_3(x,y,z);
        return true;
      }
    else if(cmd == "y")
      {
        y= interpretaDouble(status.GetString());
        cgpt= CGPoint_3(x,y,z);
        return true;
      }
    else if(cmd == "z")
      {
        z= interpretaDouble(status.GetString());
        cgpt= CGPoint_3(x,y,z);
        return true;
      }
    else if(cmd == "pos") //Posición del punto.
      {
        (*this)= interpretaPos3d(status.GetString());
        return true;
      }
    else if(cmd == "coo")
      {
        const std::vector<double> &crds= crea_vector_double(status.GetBloque());
        const size_t sz= crds.size();
        if(sz>=3)
          cgpt= CGPoint_3(crds[0],crds[1],crds[2]);
        else if(sz>1)
          cgpt= CGPoint_3(crds[0],crds[1],0.0);
        else if(sz>0)
          cgpt= CGPoint_3(crds[0],0.0,0.0);
        return true;
      }
    else
      return ProtoGeom::procesa_comando(status);
  }

//! @brief Devuelve el vector de posición del punto.
Vector3d Pos3d::VectorPos(void) const
  { return (*this)-Origen3d; }

GEOM_FT Pos3d::at0(const size_t &i) const
  { return cgpt.cartesian(i); }

GEOM_FT Pos3d::operator()(const size_t &i) const
  { return cgpt.cartesian(i-1); }

void Pos3d::SetX(const GEOM_FT &vx)
  { cgpt= CGPoint_3(vx,y(),z()); }
void Pos3d::SetY(const GEOM_FT &vy)
  { cgpt= CGPoint_3(x(),vy,z()); }
void Pos3d::SetZ(const GEOM_FT &vz)
  { cgpt= CGPoint_3(x(),y(),vz); }
void Pos3d::Set(unsigned short int i,const GEOM_FT &v)
  {
    switch(i)
      {
      case 1:
        SetX(v);
        break;
      case 2:
        SetY(v);
        break;
      case 3:
        SetZ(v);
        break;
      default:
	std::cerr << "Se esperaba que el índice fuera 1, 2 ó 3." << std::endl;
        break;
      }
  }

int Pos3d::Cuadrante(void) const
  {
    const bool x_no_neg= (x()>=0);
    const bool y_no_neg= (y()>=0);
    const bool z_no_neg= (z()>=0);
    if(x_no_neg) //(1,2,3 ó 4)
      if(y_no_neg) //1 o 4
        if(z_no_neg)
          return 1;
        else
          return 4;
      else //2 o 3
        if(z_no_neg)
          return 2;
        else
          return 3;
    else //(5,6,7 u 8)
      if(y_no_neg) //5 u 8
        if(z_no_neg)
          return 5;
        else
          return 8;
      else //6 o 7
        if(z_no_neg)
          return 6;
        else
          return 7;
  }

Pos3d Pos3d::ProyeccionXY3d(void) const
//Devuelve la proyeccion sobre el plano XY.
  { return PlanoXY3d.Proyeccion(*this); }
Pos3d Pos3d::ProyeccionXZ3d(void) const
//Devuelve la proyeccion sobre el plano XZ.
  { return PlanoXZ3d.Proyeccion(*this); }
Pos3d Pos3d::ProyeccionYZ3d(void) const
//Devuelve la proyeccion sobre el plano YZ.
  { return PlanoYZ3d.Proyeccion(*this); }

Pos2d Pos3d::ProyeccionXY2d(void) const
//Devuelve la proyeccion sobre el plano XY.
  {
    Pos3d p3d= ProyeccionXY3d();
    return Pos2d(p3d.x(),p3d.y());
  }
Pos2d Pos3d::ProyeccionXZ2d(void) const
//Devuelve la proyeccion sobre el plano XZ.
  {
    Pos3d p3d= ProyeccionXZ3d();
    return Pos2d(p3d.x(),p3d.z());
  }

//! @brief Devuelve la proyeccion sobre el plano YZ.
Pos2d Pos3d::ProyeccionYZ2d(void) const
  {
    Pos3d p3d= ProyeccionYZ3d();
    return Pos2d(p3d.y(),p3d.z());
  }

//! @brief Equivalente a la función de autocad @mod<arg con el giro en
//! torno al eje x.
Pos3d Pos3d::getModArgX(const GEOM_FT &mod,const GEOM_FT &giroX) const
  { return Pos3d(x(),y()+mod*cos(giroX),z()+mod*sin(giroX)); }

//! @brief Equivalente a la función de autocad @mod<arg con el giro en
//! torno al eje y.
Pos3d Pos3d::getModArgY(const GEOM_FT &mod,const GEOM_FT &giroY) const
  { return Pos3d(x()+mod*cos(giroY),y(),z()-mod*sin(giroY)); }


//! @brief Equivalente a la función de autocad @mod<arg con el giro en
//! torno al eje z.
Pos3d Pos3d::getModArgZ(const GEOM_FT &mod,const GEOM_FT &giroZ) const
  { return Pos3d(x()+mod*cos(giroZ),y()+mod*sin(giroZ),z()); }

bool Pos3d::domina_a(const Pos3d &b) const
  {
    for(register size_t i= 1;i<=dimension();i++)
      if ((*this)(i)<b(i)) return false;
    return true;
  }

//! @brief Devuelve la distancia
//! al punto que se pasa como parámetro.
GEOM_FT Pos3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Devuelve el cuadrado de la distancia
//! al punto que se pasa como parámetro.
GEOM_FT Pos3d::dist2(const Pos3d &p) const
  { return squared_distance(cgpt,p.cgpt); }

//! @brief Devuelve el cuadrado de la distancia a la recta.
GEOM_FT Pos3d::dist2(const Recta3d &r) const
  { return r.dist2(*this); }
  
//! @brief Devuelve la distancia a la recta.
GEOM_FT Pos3d::dist(const Recta3d &r) const
  { return r.dist(*this); }

//! @brief Devuelve el cuadrado de la distancia a la semirrecta.
GEOM_FT Pos3d::dist2(const SemiRecta3d &sr) const
  { return sr.dist2(*this); }

//! @brief Devuelve la distancia a la semirrecta.
GEOM_FT Pos3d::dist(const SemiRecta3d &sr) const
  { return sr.dist(*this); }

//! @brief Devuelve el cuadrado de la distancia al segmento.
GEOM_FT Pos3d::dist2(const Segmento3d &sg) const
  { return sg.dist2(*this); }

//! @brief Devuelve la distancia al segmento.
GEOM_FT Pos3d::dist(const Segmento3d &sg) const
  { return sg.dist(*this); }

//! @brief Devuelve el cuadrado de la distancia al plano.
GEOM_FT Pos3d::dist2(const Plano3d &p) const
  { return p.dist2(*this); }

//! @brief Devuelve la distancia al plano.
GEOM_FT Pos3d::dist(const Plano3d &p) const
  { return p.dist(*this); }

//! @brief Devuelve el cuadrado de la distancia al semiespacio.
GEOM_FT Pos3d::dist2(const SemiEspacio3d &se) const
  { return se.dist2(*this); }

//! @brief Devuelve la distancia al semiespacio.
GEOM_FT Pos3d::dist(const SemiEspacio3d &se) const
  { return se.dist(*this); }

//! @brief Devuelve la distancia al sólido.
GEOM_FT Pos3d::dist(const Solido3d &s) const
  { return s.dist(*this); }

void Pos3d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << "\\Pos3d{";
    salva_miembros(os,"");
    os << '}' << std::endl;
  }
std::ostream &operator<<(std::ostream &stream,const Pos3d &n)
  {
//     stream << "x= " << to_double(n.x()) << ','
//            << "y= " << to_double(n.y()) << ','
//            << "z= " << to_double(n.z());
    stream << "x= " << n.x() << ','
           << "y= " << n.y() << ','
           << "z= " << n.z();
    return stream;
  }


Pos3d To3dXY2d(const Pos2d &p,const GEOM_FT &z)
  { return Pos3d(p.x(),p.y(),z); }
Pos3d To3dXZ2d(const Pos2d &p,const GEOM_FT &y)
  { return Pos3d(p.x(),y,p.y()); }
Pos3d To3dYZ2d(const Pos2d &p,const GEOM_FT &x)
  { return Pos3d(x,p.x(),p.y()); }
Pos3d To3d(const Pos2d &p,const size_t &coo,const GEOM_FT &u)
  { 
    const size_t i= (coo-1)%3+1;
    if(i==3) return To3dXY2d(p,u);
    if(i==2) return To3dXZ2d(p,u);
    return To3dYZ2d(p,u);
  }

bool colineales(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  { return collinear(p1.cgpt,p2.cgpt,p3.cgpt); } 
bool coplanarios(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4)
  { return coplanar(p1.cgpt,p2.cgpt,p3.cgpt,p4.cgpt); } 


//! @brief Devuelve una propiedad del objeto.
any_const_ptr Pos3d::GetProp(const std::string &cod) const
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
    else if(cod=="z")
      {
        tmp_ft= z();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getVectorPos")
      {
        tmp_gp_vector3d= VectorPos();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else
      return ProtoGeom::GetProp(cod);
  }




