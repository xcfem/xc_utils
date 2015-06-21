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
//Plano3d.cc

#include "Plano3d.h"
#include "../listas/TresPuntos3d.h"
#include "EcuacionGeneralPlano3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/SemiRecta3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d1/Polilinea3d.h"
#include "xc_utils/src/geom/d2/Poligono3d.h"
#include "xc_utils/src/geom/d2/Triangulo3d.h"
#include "xc_utils/src/geom/d3/GmGrupo3d.h"
#include "xc_basic/src/util/mchne_eps.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "CGAL/linear_least_squares_fitting_3.h"

Plano3d::Plano3d(void)
  : Superficie3d(), cgp(CGPoint_3(0,0,0), CGPoint_3(1,0,0), CGPoint_3(0,1,0)) {}

Plano3d::Plano3d(const CGPlane_3 &cgp)
  : Superficie3d(), cgp(cgp) {}

//! @brief Constructor: plano que pasa por tres puntos.
Plano3d::Plano3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : Superficie3d(), cgp(p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL()) {}


//! @brief Constructor: plano que pasa por el punto y es normal al vector.
Plano3d::Plano3d(const Pos3d &o,const Vector3d &v)
  : Superficie3d(), cgp(o.ToCGAL(),v.ToCGAL()) {}

//! @brief Convierte la clasificación del punto en la correspondiente de polígono.
Plano3d::clasif_poligono Plano3d::clfpnt2clfpol(const CGAL::Oriented_side os)
  {
    clasif_poligono retval= DETRAS;
    switch(os)
      {
        case CGAL::ON_NEGATIVE_SIDE:
          retval= DETRAS;
          break;
        case CGAL::ON_POSITIVE_SIDE:
          retval= DELANTE;
          break;
        case CGAL::ON_ORIENTED_BOUNDARY:
          retval= DENTRO;
          break;
      }
    return retval;
  }

Plano3d::Plano3d(const Recta3d &r,const Pos3d &p)
  : Superficie3d(), cgp(r.ToCGAL(),p.ToCGAL()) {}
Plano3d::Plano3d(const Segmento3d &s,const Vector3d &v)
  : Superficie3d(), cgp(s.RectaSoporte().ToCGAL(),(s.Origen()+v).ToCGAL()) {}
Plano3d::Plano3d(const Pos3d &p,const Vector3d &v1,const Vector3d &v2)
  : Superficie3d(), cgp(p.ToCGAL(),(p+v1).ToCGAL(),(p+v2).ToCGAL()) {}
Plano3d::Plano3d(const GeomObj3d::list_Pos3d &lp): Superficie3d(), cgp()
  {
    if(lp.size()<3)
      {
        std::cerr << "Plano3d(list_Pos3d): La lista ha de contener al menos tres puntos." 
             << std::endl;
      }
    GeomObj3d::list_Pos3d::const_iterator i= lp.begin();
    TresPuntos(*i,*i++,*i++);
  }
Plano3d::Plano3d(const Poligono3d &pg3d)
  : Superficie3d(), cgp()
  { *this= pg3d.GetPlano(); }
Plano3d::Plano3d(const EcuacionGeneralPlano3d &eg)
  : Superficie3d(), cgp(eg.a(),eg.b(),eg.c(),eg.d()) {}

Plano3d::Plano3d(const Plano3d &otro)
  : Superficie3d(), cgp(otro.cgp) {}

Plano3d &Plano3d::operator=(const Plano3d &otro)
  {
    cgp=(otro.cgp);
    Superficie3d::operator=(otro);
    return *this;
  }

GeomObj *Plano3d::clon(void) const
  { return new Plano3d(*this); }

void Plano3d::TresPuntos(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  { operator=(Plano3d(p1,p2,p3)); }

bool Plano3d::procesa_comando(CmdStatus &status)
  {
    const std::string &cmd= deref_cmd(status.Cmd());
    const std::string str_error= "(Plano3d) Procesando comando: " + cmd;
    if(verborrea>2)
      std::clog << str_error << cmd << std::endl;
    if(cmd == "tres_puntos")
      {
        TresPuntos3d tp;
        tp.LeeCmd(status);
        TresPuntos(tp.Org(),tp.P1(),tp.P2());
        return true;
      }
    else if(cmd == "3puntos")
      {
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        if(nc<3)
	  std::cerr << str_error
                    << "Se esperaban tres argumentos de tipo punto, se obtuvieron: "
                    << nc << std::endl;
        else
          {
            Pos3d o= convert_to_pos3d(param[0]);
            Pos3d p1= convert_to_pos3d(param[1]);
            Pos3d p2= convert_to_pos3d(param[2]);
            TresPuntos(o,p1,p2);
          }
        return true;
      }
    else if(cmd == "pto_y_vector")
      {
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos argumentos, un punto y un vector, se obtuvieron: "
                    << nc << std::endl;
        else
          {
            Pos3d o= convert_to_pos3d(param[0]);
            Vector3d v= convert_to_vector3d(param[1]);
            operator=(Plano3d(o,v));
          }
        return true;
      }
    else if(cmd == "ecuacion_general")
      {
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        if(nc<4)
	  std::cerr << str_error
                    << "Se esperaban cuatro argumentos reales, se obtuvieron: "
                    << nc << std::endl;
        else
          {
            const double a= convert_to_double(param[0]);
            const double b= convert_to_double(param[1]);
            const double c= convert_to_double(param[2]);
            const double d= convert_to_double(param[3]);
            EcuacionGeneralPlano3d eq(a,b,c,d);
            operator=(Plano3d(eq));
          }
        return true;
      }
    else if(cmd == "swap")
      {
        status.GetString(); //Ignoramos argumentos.
        Swap();
        return true;
      }
    else
      return Superficie3d::procesa_comando(status);
  }
// void Plano3d::SalvaCmd(std::ostream &os,const std::string &indent= "  ") const
//   {
//     const std::string str_indent= indent + "  ";
//     os << indent << "\\plano" << std::endl
//        << str_indent << '{' << std::endl;
//     salva_miembros(os,str_indent+ "  ");
//     os << str_indent  << '}' << std::endl;
//   }

//! @brief Devuelve el vector normal al plano con sentido hacia el lado "positivo".
Vector3d Plano3d::Normal(void) const
  { return Vector3d(cgp.orthogonal_vector()); }
//! @brief Devuelve un vector ortogonal al devuelto por Normal().
Vector3d Plano3d::Base1(void) const
  { return Vector3d(cgp.base1()); }
//! @brief Devuelve un vector ortogonal al devuelto por Normal() y al devuelto por Base1().
Vector3d Plano3d::Base2(void) const
  { return Vector3d(cgp.base2()); }

//! @brief Devuelve un sistema de coordenadas cuyo plano XY
//! coincide con éste.
SisCooRect2d3d Plano3d::getSisCoo(void) const
  { return SisCooRect2d3d(Base1(),Base2()); }

//! @brief Devuelve un sistema de referencia cuyo plano XY
//! coincide con éste.
Ref2d3d Plano3d::getRef(const Pos3d &org) const
  { return Ref2d3d(org,Base1(),Base2()); }

void Plano3d::Swap(void)
  { operator=(GetSwap()); }
Plano3d Plano3d::GetSwap(void) const
  { return Plano3d(cgp.opposite()); }

//! @brief Devuelve la proyección del punto sobre el plano.
Pos3d Plano3d::Proyeccion(const Pos3d &p) const
  { return Pos3d(cgp.projection(p.ToCGAL())); }

//! @brief Devuelve la proyección del vector sobre el plano.
Vector3d Plano3d::Proyeccion(const Vector3d &v) const
  {
    const Vector3d n= Normal().Normalizado();
    return cross(cross(n,v),n);
  }

//! @brief Devuelve la proyección de la recta sobre el plano.
Recta3d Plano3d::Proyeccion(const Recta3d &r) const
  {
    Recta3d retval;
    const Pos3d p0= Proyeccion(r.Punto(0));
    const Pos3d p1= Proyeccion(r.Punto(100));
    const double d= p0.dist(p1);
    if(d>mchne_eps_dbl)
      retval= Recta3d(p0,p1);
    else
      retval.setExists(false);
    return retval;
  }

GeomObj3d::list_Pos3d Plano3d::Proyeccion(const GeomObj3d::list_Pos3d &ptos) const
  {
    GeomObj3d::list_Pos3d retval;
    for(GeomObj3d::list_Pos3d::const_iterator i=ptos.begin();i!=ptos.end();i++)
      retval.push_back(Proyeccion(*i));
    return retval;
  }
// Poligono Plano3d::Proyeccion(const Poligono &pg) const
//   { return pg.Proyeccion(*this); }

//! @brief Devuelve un punto arbitrario del plano.
Pos3d Plano3d::Punto(void) const
  { return Pos3d(cgp.point()); }

bool Plano3d::LadoPositivo(const Pos3d &p) const
  { return cgp.has_on_positive_side(p.ToCGAL()); }
bool Plano3d::LadoNegativo(const Pos3d &p) const
  { return cgp.has_on_negative_side(p.ToCGAL()); }

//Devuelve verdadero si el punto está sobre el Plano.
bool Plano3d::In(const Pos3d &p, const GEOM_FT &tol) const
  { 
    bool retval= false;
    if(cgp.has_on(p.ToCGAL()))
      retval= true;
    else if(dist(p)<=tol)
      retval= true;
    return retval;
  }

CGAL::Oriented_side Plano3d::ClasificaPunto(const Pos3d &p) const
  { return cgp.oriented_side(p.ToCGAL()); }

GEOM_FT Plano3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Devuelve la distancia con signo desde el punto al Plano.
GEOM_FT Plano3d::PseudoDist(const Pos3d &p) const
  {
    GEOM_FT retval= dist(p);
    if(LadoNegativo(p))
      return -retval;
    else
      return retval;
  }
//! @brief Devuelve la distancia con signo desde el punto al Plano.
GEOM_FT Plano3d::PseudoDist2(const Pos3d &p) const
  {
    GEOM_FT retval= dist2(p);
    if(LadoNegativo(p))
      return -retval;
    else
      return retval;
  }

//Devuelve la distancia l cuadrado desde el punto al plano.
GEOM_FT Plano3d::dist2(const Pos3d &p) const
  { return p.dist2(Proyeccion(p)); }

//! @brief Devuelve la ecuacion general del plano ax + by + cz + d = 0
EcuacionGeneralPlano3d Plano3d::GetEcuacionGeneral(void) const
  { return EcuacionGeneralPlano3d(cgp.a(),cgp.b(),cgp.c(),cgp.d()); }

//! @brief Devuelve la posición del centro de gravedad del plano.
//! Como el plano es infinito cualquier punto del mismo
//! es su centro de gravedad.
Pos3d Plano3d::Cdg(void) const
  { return Punto(); }

Plano3d::clasif_poligono Plano3d::ClasificaPoligono(const Poligono3d &pol) const
  {
    GeomObj::list_Pos3d lv= pol.ListaVertices();
    return ClasificaPuntos(lv.begin(),lv.end());
  }

Plano3d FromCGAL(const CGPlane_3 &p)
  { return Plano3d(p); }

bool operator==(const Plano3d &p1,const Plano3d &p2)
  { return (p1.cgp == p2.cgp); }

void Plano3d::Print(std::ostream &os) const
  { os << Normal() << std::endl; }

//! @brief Devuelve la coordenada x del punto del plano */
//! tal que:
//! y = p.x()
//! z = p.y()
GEOM_FT Plano3d::x(const Pos2d &p) const
  { return GetEcuacionGeneral().x(p); }

//! @brief Devuelve la coordenada y del punto del plano */
//! tal que:
//! x = p.x()
//! z = p.y()
GEOM_FT Plano3d::y(const Pos2d &p) const
  { return GetEcuacionGeneral().y(p); }

//! @brief Devuelve la coordenada z del punto del plano */
//! tal que:
//! x = p.x()
//! y = p.y()
GEOM_FT Plano3d::z(const Pos2d &p) const
  { return GetEcuacionGeneral().z(p); }

//! @brief Calcula el plano de ecuacion general ax + by + cz + d = 0
void Plano3d::EcuacionGeneral(const EcuacionGeneralPlano3d &eq)
  { operator=(Plano3d(eq)); }

//! @brief Returns true if intesection exists.
bool Plano3d::Interseca(const Plano3d &p) const
  { return do_intersect(ToCGAL(),p.ToCGAL()); }

//! @brief Returns (if exists) la intersección con el plano que se pasa como parámetro.
Recta3d Plano3d::Interseccion(const Plano3d &p) const
  { return recta_interseccion(*this,p); }

// //! @brief Devuelve (if exists) la intersección con el plano que se pasa como parámetro.
// Recta3d Plano3d::Interseccion(const Plano3d &p) const
//   {
//     const Recta3d retval= Interseccion(p);
//     if(!retval.exists())
//       std::cerr << "Intersection with plane doesn't exists: "
//                 << p << std::endl;
//     return retval;
//   }

//! @brief Devuelve verdadero if exists la intersección con la recta que se pasa como parámetro.
bool Plano3d::Interseca(const Recta3d &r) const
  { return do_intersect(ToCGAL(),r.ToCGAL()); }

//! @brief Devuelve (if exists) la intersección con la recta que se pasa como parámetro.
Pos3d Plano3d::Interseccion(const Recta3d &r) const
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(*this,r);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

// //! @brief Devuelve (if exists) la intersección con la recta que se pasa como parámetro.
// Pos3d Plano3d::Interseccion(const Recta3d &r) const
//   {
//     const Pos3d retval= Interseccion(r);
//     if(!retval.exists())
//       std::cerr << "Intersection with line "
//                 << r << "doesn't exists." << std::endl;
//     return retval;
//   }

//! @brief Devuelve verdadero if exists la intersección con la recta que se pasa como parámetro.
bool Plano3d::Interseca(const SemiRecta3d &sr) const
  { return do_intersect(ToCGAL(),sr.ToCGAL()); }

//! @brief Devuelve (if exists) la intersección con la semirrecta que se pasa como parámetro.
Pos3d Plano3d::Interseccion(const SemiRecta3d &sr) const
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(*this,sr);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

//! @brief Devuelve verdadero if exists la intersección con el segmento que se pasa como parámetro.
bool Plano3d::Interseca(const Segmento3d &sg) const
  { return do_intersect(ToCGAL(),sg.ToCGAL()); }

//! @brief Devuelve (if exists) la intersección con la semirrecta que se pasa como parámetro.
Pos3d Plano3d::Interseccion(const Segmento3d &sg) const
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(*this,sg);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

// //! @brief Devuelve (if exists) la intersección con la recta que se pasa como parámetro.
// Pos3d Plano3d::Interseccion(const SemiRecta3d &sr) const
//   {
//     const Pos3d retval= Interseccion(sr);
//     if(!retval.exists())
//       std::cerr << "Intersection with ray doesn't exists: "
//                 << sr << std::endl;
//     return retval;
//   }

//! @brief Devuelve la intersección del plano con el XY.
Recta3d Plano3d::TrazaXY(void) const
  { return Interseccion(PlanoXY3d); }

//! @brief Devuelve la intersección del plano con el XZ.
Recta3d Plano3d::TrazaXZ(void) const
  { return Interseccion(PlanoXZ3d); }

//! @brief Devuelve la intersección del plano con el YZ.
Recta3d Plano3d::TrazaYZ(void) const
  { return Interseccion(PlanoYZ3d); }

//! @brief Devuelve la recta de máxima pendiente del plano respecto al XY.
Recta3d Plano3d::RectaMaximaPendienteXY(void) const
  {
    Recta3d retval;
    Recta3d traza= TrazaXY();
    if(traza.exists())
      {
        Pos3d punto(Punto());
        Plano3d p(perpendicular(traza,punto));
        retval= recta_interseccion(p,*this);
      }
    return retval;
  }

//! @brief Devuelve la recta de máxima pendiente del plano respecto al XZ.
Recta3d Plano3d::RectaMaximaPendienteXZ(void) const
  {
    Recta3d retval;
    Recta3d traza= TrazaXZ();
    if(traza.exists())
      {
        Pos3d punto(Punto());
        Plano3d p(perpendicular(traza,punto));
        retval= recta_interseccion(p,*this);
      }
    return retval;
  }

//! @brief Devuelve la recta de máxima pendiente del plano respecto al YZ.
Recta3d Plano3d::RectaMaximaPendienteYZ(void) const
  {
    Recta3d retval;
    Recta3d traza= TrazaYZ();
    if(traza.exists())
      {
        Pos3d punto(Punto());
        Plano3d p(perpendicular(traza,punto));
        retval= recta_interseccion(p,*this);
      }
    return retval;
  }

//! @brief Devuelve el ángulo que forma con el plano que se pasa como parámetro.
GEOM_FT Plano3d::Angulo(const Plano3d &p) const
  { return angulo(*this,p); }

//! @brief Devuelve el ángulo que forma con el vector que se pasa como parámetro.
GEOM_FT Plano3d::Angulo(const Vector3d &v) const
  { return angulo(*this,v); }

//! @brief Devuelve la pendiente respecto al plano XY
GEOM_FT Plano3d::AnguloPendienteXY(void) const
  { return angulo(*this,PlanoXY3d); }

//! @brief Devuelve la pendiente respecto al plano XZ
GEOM_FT Plano3d::AnguloPendienteXZ(void) const
  { return angulo(*this,PlanoXZ3d); }

//! @brief Devuelve la pendiente respecto al plano YZ
GEOM_FT Plano3d::AnguloPendienteYZ(void) const
  { return angulo(*this,PlanoYZ3d); }

//! @brief Calcula el plano que mejor se ajusta a la nube de puntos.
GEOM_FT Plano3d::AjusteMinimosCuadrados(const GeomObj3d::list_Pos3d &lp)
  {
    std::list<CGPoint_3> puntos;
    for(GeomObj3d::list_Pos3d::const_iterator i=lp.begin(); i!=lp.end();i++)
      puntos.push_back((*i).ToCGAL()); 
    GEOM_FT quality= linear_least_squares_fitting_3(puntos.begin(),puntos.end(),cgp,CGAL::Dimension_tag<0>());
    return quality;
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
any_const_ptr Plano3d::GetProp(const std::string &cod) const
  {
    static GEOM_FT tmp_ft= 0.0;
    if(cod=="getNormal")
      {
        tmp_gp_vector3d= Normal();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getBase1")
      {
        tmp_gp_vector3d= Base1();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getBase2")
      {
        tmp_gp_vector3d= Base2();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getProyVector")
      {
        const Vector3d v= popVector3d(cod);
        tmp_gp_vector3d= Proyeccion(v);
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getProyPunto")
      {
        const Pos3d p= popPos3d(cod);
        tmp_gp_pos3d= Proyeccion(p);
        return any_const_ptr(tmp_gp_pos3d);
      }
    else if(cod=="getProyRecta")
      {
        const Recta3d r= popRecta3d(cod);
        tmp_gp_recta3d= Proyeccion(r);
        if(!tmp_gp_recta3d.exists())
	  std::cerr << "getProyRecta: se produjo un error al calcular la proyección." << std::endl;
        return any_const_ptr(tmp_gp_recta3d);
      }
    else if(cod=="getPseudoDist")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_ft= PseudoDist(tmp);
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getDist")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_ft= dist(tmp);
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getInterseccionConRecta")
      {
        const Recta3d tmp= popRecta3d(cod);
        GeomObj3d::list_Pos3d lista= interseccion(*this,tmp);
        if(!lista.empty())
          tmp_gp_pos3d= lista[0];
	else
	  std::cerr << "getInterseccionConRecta: la recta no corta al plano." << std::endl;
        return any_const_ptr(tmp_gp_pos3d);
      }
    else
      return Superficie3d::GetProp(cod);
  }

//! @brief Devuelve el plano perpendicular a la recta r
//! que pasa por el punto p.
Plano3d perpendicular(const Recta3d &r, const Pos3d &p)
  { return r.Perpendicular(p); }

//! @brief Recta intersección de dos planos.
Recta3d recta_interseccion(const Plano3d &p1, const Plano3d &p2)
  {
    Recta3d retval;
    GmGrupo3d tmp= interseccion(p1,p2);
    if(!tmp.empty())
      {
        const Recta3d *ptr_recta= dynamic_cast<const Recta3d *>(tmp.begin()->get_const_ptr());
        if(ptr_recta)
          retval= *ptr_recta;
      }
    else
      retval.setExists(false);
    return retval;
  }

//! @brief Intersección de tres planos.
Pos3d punto_interseccion(const Plano3d &p1, const Plano3d &p2, const Plano3d &p3)
  {
    Pos3d retval;
    GmGrupo3d tmp= interseccion(p1,p2);
    if(!tmp.empty())
      {
        const Recta3d *ptr_recta= dynamic_cast<const Recta3d *>(tmp.begin()->get_const_ptr());
        if(ptr_recta)
          retval= punto_interseccion(p3,*ptr_recta);
      }
    else
      retval.setExists(false);
    return retval;
  }

//! @brief Intersección de dos planos.
GmGrupo3d interseccion(const Plano3d &p1, const Plano3d &p2)
  {
    GmGrupo3d retval;
    if(do_intersect(p1.ToCGAL(),p2.ToCGAL()))
      {
        const CGAL::Object result = CGAL::intersection(p1.ToCGAL(),p2.ToCGAL());
        if(const CGRecta_3 *ri= CGAL::object_cast<CGRecta_3 >(&result)) //(CGAL::assign(ri, result))
          retval.push_back(Recta3d(*ri));
        else
          {
            CGPlane_3 planoi;
            if(CGAL::assign(planoi, result))
              {
                std::cerr << "interseccion(Plano3d,Plano3d): Los planos coinciden." 
                          << std::endl;
              }
            else
              {
                std::cerr << "interseccion(Plano3d,Plano3d): Error desconocido." 
                          << std::endl;
              }
	  }
      }
    return retval;
  }

//! @brief Devuelve la intersección de la recta con el plano.
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Recta3d &r)
  {
    GeomObj3d::list_Pos3d retval;
    if(do_intersect(p.ToCGAL(),r.ToCGAL()))
      {
        CGAL::Object result;
        CGPoint_3 ptoi;
        CGRecta_3 ri;
        result = CGAL::intersection(p.ToCGAL(),r.ToCGAL());
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos3d(ptoi));
        else
          if(CGAL::assign(ri, result))
            {
              std::cerr << "interseccion(Plano3d,Recta3d): El plano contiene a la recta." 
                   << std::endl;
            }
          else
            {
              std::cerr << "interseccion(Plano3d,Recta3d): Error desconocido." 
                   << std::endl;
            }
      }
    return retval;
  }

//! @brief Devuelve la intersección de la recta con el plano.
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const SemiRecta3d &sr)
  {
    GeomObj3d::list_Pos3d retval;
    if(do_intersect(p.ToCGAL(),sr.ToCGAL()))
      {
        CGAL::Object result;
        CGPoint_3 ptoi;
        CGRecta_3 ri;
        result = CGAL::intersection(p.ToCGAL(),sr.ToCGAL());
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos3d(ptoi));
        else
          if(CGAL::assign(ri, result))
            {
              std::cerr << "interseccion(Plano3d,SemiRecta3d): El plano contiene a la recta." 
                   << std::endl;
            }
          else
            {
              std::cerr << "interseccion(Plano3d,SemiRecta3d): Error desconocido." 
                   << std::endl;
            }
      }
    // else
    //   std::cerr << "No intersecan." << std::endl;
    return retval;    
  }

//! @brief Devuelve la intersección de la semirrecta con el plano.
GeomObj3d::list_Pos3d interseccion(const SemiRecta3d &sr, const Plano3d &p)
  { return interseccion(p,sr); }

//! @brief Devuelve la intersección del segmento con el plano.
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Segmento3d &sg)
  {
    GeomObj3d::list_Pos3d retval;
    if(do_intersect(p.ToCGAL(),sg.ToCGAL()))
      {
        CGAL::Object result;
        CGPoint_3 ptoi;
        CGRecta_3 ri;
        result = CGAL::intersection(p.ToCGAL(),sg.ToCGAL());
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos3d(ptoi));
        else
          if(CGAL::assign(ri, result))
            {
              std::cerr << "interseccion(Plano3d,Segmento3d): El plano contiene a la recta." 
                   << std::endl;
            }
          else
            {
              std::cerr << "interseccion(Plano3d,Segmentoed): Error desconocido." 
                   << std::endl;
            }
      }
    // else
    //   std::cerr << "No intersecan." << std::endl;
    return retval;    
  }

//! @brief Devuelve la intersección de la recta con el plano.
GeomObj3d::list_Pos3d interseccion(const Segmento3d &sg, const Plano3d &p)
  { return interseccion(p,sg); }

GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Polilinea3d &pl)
  { return pl.getIntersection(p); }

GeomObj3d::list_Pos3d interseccion(const Polilinea3d &pl, const Plano3d &p)
  { return pl.getIntersection(p); }

Pos3d punto_interseccion(const Plano3d &p, const Recta3d &r)
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(p,r);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

Pos3d punto_interseccion(const Recta3d &r, const Plano3d &p)
  { return punto_interseccion(p,r); }

Pos3d punto_interseccion(const Plano3d &p, const SemiRecta3d &sr)
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(p,sr);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

Pos3d punto_interseccion(const SemiRecta3d &sr, const Plano3d &p)
  { return punto_interseccion(p,sr); }

Pos3d punto_interseccion(const Plano3d &p, const Segmento3d &sg)
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(p,sg);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }
Pos3d punto_interseccion(const Segmento3d &sg, const Plano3d &p)
  { return punto_interseccion(p,sg); }

GEOM_FT angulo(const Recta3d &r,const Plano3d &p)
  {
    GEOM_FT retval;
    const Recta3d rProj= p.Proyeccion(r);
    if(rProj.exists())
      retval= angulo(r,rProj);
    else
      {
        retval= NAN;
        std::cerr << "angulo(recta,plano): se produjo un error al calcular la proyección." << std::endl;
      }
    return retval;
  }

GEOM_FT angulo(const Plano3d &p,const Recta3d &r)
  { return angulo(r,p); }

GEOM_FT angulo(const Vector3d &v,const Plano3d &p)
  { return M_PI/2 - angulo(p.Normal(),v); }

GEOM_FT angulo(const Plano3d &p,const Vector3d &v)
  { return angulo(v,p); }

GEOM_FT angulo(const Plano3d &p1,const Plano3d &p2)
  {
    GEOM_FT retval= angulo(p1.Normal(),p2.Normal());
    return retval;
  }


GeomObj3d::list_Pos3d interseccion(const Recta3d &r, const Plano3d &p)
  { return interseccion(p,r); }

//! @brief Devuelve los puntos de intersección entre los planos.
GeomObj3d::list_Pos3d puntos_interseccion(const std::deque<Plano3d> &planos)
  {
    GeomObj3d::list_Pos3d retval;
    const size_t sz= planos.size();
    for(size_t i=0;i<sz;i++)
      for(size_t j=i+1;j<sz;j++)
        for(size_t k=j+1;k<sz;k++)
	  {
            const Pos3d p= punto_interseccion(planos[i],planos[j],planos[k]);
            if(p.exists())
              retval.push_back(p);
          }
    return retval;
  }

//! @brief Devuelve verdadero si la recta es paralela al plano.
bool paralelos(const Plano3d &p, const Recta3d &r)
  { return(!do_intersect(p.ToCGAL(),r.ToCGAL())); }

//! @brief Devuelve verdadero si los planos son paralelos.
bool paralelos(const Plano3d &p1, const Plano3d &p2)
  { return(!do_intersect(p1.ToCGAL(),p2.ToCGAL())); }

