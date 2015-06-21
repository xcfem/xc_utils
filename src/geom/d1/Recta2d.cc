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
//Recta2d.cc

#include "Recta2d.h"
#include "xc_basic/src/util/matem.h"
#include <plotter.h>
#include "xc_utils/src/base/CmdStatus.h"
#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos3d.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "Segmento2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/nucleo/aux_any.h"

//! @brief Devuelve el parámetro que corresponde al punto
//! sobre la recta.
//!
//! Devuelve el parámetro que corresponde al punto
//! sobre la recta. Se supone que el punto esta sobre la recta.
GEOM_FT RectaParametricas2d::Parametro(const Pos2d &p) const
  {
    Vector2d v= p-org;
    return dot(v,dir)/Abs(dir);
  }

//! @brief Constructor por defecto.
Recta2d::Recta2d(void): Linea2d(),cgr(CGPoint_2(0,0),CGPoint_2(1,0))
  {}
Recta2d::Recta2d(const Pos2d &p1,const Pos2d &p2)
  : Linea2d(), cgr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        clog << "Recta2d::Recta2d: La recta es degenerada, los puntos: "
             << p1 << " y " << p2 << " coinciden." << endl;
      }
    if(p1.dist(p2)<mchne_eps_dbl)
      std::cerr << "Recta2d::Recta2d: La recta está mal definida, los puntos: "
             << p1 << " y " << p2 << " están muy próximos." << endl;
  }
Recta2d::Recta2d(const Pos2d &p,const Dir2d &dir)
  : Linea2d(), cgr(p.ToCGAL(),dir.ToCGAL()) {}
Recta2d::Recta2d(const Pos2d &p,const Vector2d &vdir)
  : Linea2d(), cgr(p.ToCGAL(),vdir.ToCGAL()) {}

Recta2d::Recta2d(const CGRecta_2 &r)
  : Linea2d(), cgr(r) {}

Recta2d::Recta2d(const Recta2d &r)
  : Linea2d(),cgr(r.cgr) {}

//! @brief Constructor de la recta a partir de su ecuacion en paramétricas.
Recta2d::Recta2d(const RectaParametricas2d &param): Linea2d(),cgr(CGPoint_2(0,0),CGPoint_2(1,0))
      { Parametricas(param); }

//! @brief Operador asignación.
Recta2d &Recta2d::operator=(const Recta2d &r)
  {
    Linea2d::operator=(r);
    cgr= r.cgr;
    return *this;
  }

const CGRecta_2 &Recta2d::ToCGAL(void) const
  { return cgr; }

//! @brief Constructor virtual.
GeomObj *Recta2d::clon(void) const
  { return new Recta2d(*this); }

//! @brief Cambia la orientación de la recta.
void Recta2d::Swap(void)
  { cgr= cgr.opposite(); }

void Recta2d::DosPuntos(const Pos2d &p1,const Pos2d &p2)
  { (*this)= Recta2d(p1,p2); }
void Recta2d::salva_miembros(std::ostream &os,const std::string &indent) const
  {
/*         salva_org(os,indent); */
/*         os << indent << "\\dest{"; */
/*         PtoParametricas(100.0).salva_miembros(os,""); */
/*         os << '}' << endl; */
  }
void Recta2d::salva_cmd(std::ostream &os,const std::string &indent,const std::string &obj) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << '\\' << obj << endl
       << str_indent << '{' << endl;
    salva_miembros(os,str_indent+ "  ");
    os << str_indent  << '}' << endl;
  }

bool Recta2d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd=  status.Cmd();
    const std::string str_error= "(Recta2d) Procesando comando: " + cmd;
    if(verborrea>2)
      std::clog << str_error << std::endl;
    static Pos2d o,d;
    if(cmd == "org")
      {
        o.LeeCmd(status);
        (*this)= Recta2d(o,d);
        return true;
      }
    else if(cmd == "dest")
      {
        d.LeeCmd(status);
        (*this)= Recta2d(o,d);
        return true;
      }
    else if(cmd == "dosPuntos")
      {
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos argumentos de tipo vector, se obtuvieron: "
                    << nc << std::endl;
        else
          {
            Pos2d p1= convert_to_pos2d(param[0]);
            Pos2d p2= convert_to_pos2d(param[1]);
            (*this)= Recta2d(p1,p2);
          }
        return true;
      }
    else if(cmd == "puntoyVector")
      {
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos argumentos de tipo vector, se obtuvieron: "
                    << nc << std::endl;
        else
          {
            Pos2d p= convert_to_pos2d(param[0]);
            Vector2d v= convert_to_vector2d(param[1]);
            (*this)= Recta2d(p,v);
          }
        return true;
      }
    else
      return Linea2d::procesa_comando(status);
  }

//! @brief Devuelve la longitud de la recta.
GEOM_FT Recta2d::Longitud(void) const
  { return NAN; }

//! @brief Devuelve el centro de gravedad de la recta.
Pos2d Recta2d::Cdg(void) const
  { return Pos2d(NAN,NAN); }

Dir2d Recta2d::GetDir(void) const
  { return Dir2d(cgr.direction()); }
Vector2d Recta2d::VDir(void) const
  { return GetDir().GetVector(); }
Vector2d Recta2d::VersorDir(void) const
  { return VDir().Normalizado(); }

double Recta2d::getLambda(unsigned short int i,const double &d,const Vector2d &i_) const
  { return (d-Punto(0)(i))/i_(i);}

//! @brief Devuelve la proyección ortogonal de p sobre la recta.
Pos2d Recta2d::Proyeccion(const Pos2d &p) const
  { return Pos2d(cgr.projection(p.ToCGAL())); }

//! @brief Devuelve la proyección ortogonal de v sobre la recta.
Vector2d Recta2d::Proyeccion(const Vector2d &v) const
  {
    const Vector2d d= VDir().Normalizado();
    return dot(v,d)*d;
  }

//! @brief Devuelve el valor de a que corresponde a la ecuación de la recta: a*x + b*y + c= 0
GEOM_RT Recta2d::a(void) const
  { return cgr.a(); }

//! @brief Devuelve el valor de b que corresponde a la ecuación de la recta: a*x + b*y + c= 0
GEOM_RT Recta2d::b(void) const
  { return cgr.b(); }

//! @brief Devuelve el valor de c que corresponde a la ecuación de la recta: a*x + b*y + c= 0
GEOM_RT Recta2d::c(void) const
  { return cgr.c(); }

//! @brief Devuelve la pendiente de la recta.
GEOM_FT Recta2d::GetPendiente(void) const
  { return GetParamA(); }

//! @brief Devuelve el parámetro a (y=a*x+b) de la proyección horizontal de la recta.
GEOM_FT Recta2d::GetParamA(void) const
  {
    if(EsVertical())
      {
        clog << "Recta2d::GetParamA: La recta es vertical, la pendiente es infinita." << endl;
        return NAN;
      }
    else
      return -(cgr.a()/cgr.b());
  }

//! @brief Devuelve el parámetro b (y=a*x+b) de la recta.
GEOM_FT Recta2d::GetParamB(void) const
  {
    if(EsVertical())
      {
        clog << "Recta2d::GetParamB: La recta es vertical, corta al eje y en el infinito." << endl;
        return NAN;
      }
    else
      return -(cgr.c()/cgr.b());
  }

GEOM_FT Recta2d::GetY(const GEOM_FT &x) const
  { 
    if(EsVertical())
      {
        clog << "Recta2d::GetY: La recta es vertical." << endl;
        return NAN;
      }
    return cgr.y_at_x(x);
  }
//! @brief Devuelve el parámetro que corresponde al punto
//! sobre la recta.
//!
//! Devuelve el parámetro que corresponde al punto
//! sobre la recta. Si el punto no esta sobre la recta
//! se calcula el parámetro de su proyección sobre
//! la misma.
GEOM_FT Recta2d::Parametro(const Pos2d &p) const
  {
    Pos2d tmp(p);
    if(!In(tmp))
      tmp= Proyeccion(tmp);
    RectaParametricas2d r= GetParametricas();
    return r.Parametro(tmp);
  }

//! @brief Devuelve las ecuaciones parametricas de la recta de la siguiente forma:
//!   v[0]: coordenadas del origen.
//!   v[1]: vector direcci'on de la recta.
RectaParametricas2d Recta2d::GetParametricas(void) const
  { return RectaParametricas2d(Punto(0),VDir()); }

//! @brief Devuelve un punto de la recta a una "distancia"
//! lambda del origen.
Pos2d Recta2d::PtoParametricas(const GEOM_FT &lambda) const
  { return Punto(0)+lambda*VDir(); }

//! @brief Definición de la recta a partir de su ecuacion en
//! parametricas.
void Recta2d::Parametricas(const RectaParametricas2d &param)
  { DosPuntos(param.GetPunto(0.0),param.GetPunto(100.0)); }

//! @brief SOLO SE USA EN Ordena.
bool menor_param(const Pos3d &p1, const Pos3d &p2)
  { return (p1.z()<p2.z()); }

//! @brief Devuelve los puntos que se pasan como parámetro
//! en una lista ordenada por el valor de su proyección sobre la
//! recta de menor a mayor. El origen es Recta2d::Punto(0).
GeomObj::list_Pos2d Recta2d::Ordena(const GeomObj::list_Pos2d &ptos) const
  {
    GeomObj::list_Pos2d retval;
    if(ptos.empty()) return retval;

    RectaParametricas2d rp= GetParametricas();
    GeomObj::list_Pos3d tmp;
    for(GeomObj::list_Pos2d::const_iterator i= ptos.begin();i!=ptos.end();i++)
      tmp.push_back(Pos3d((*i).x(),(*i).y(),rp.Parametro(*i)));

    sort(tmp.begin(),tmp.end(),menor_param);

    for(GeomObj::list_Pos3d::const_iterator i= tmp.begin();i!=tmp.end();i++)
      retval.push_back(Pos2d((*i).x(),(*i).y()));
    return retval;
  }

//! @brief Devuelve los puntos que se pasan como parámetro
//! proyectados sobre la recta.
GeomObj::list_Pos2d Recta2d::Proyecta(const GeomObj::list_Pos2d &ptos) const
  {
    GeomObj::list_Pos2d retval;
    for(GeomObj::list_Pos2d::const_iterator i= ptos.begin();i!=ptos.end();i++)
      retval.push_back(Proyeccion(*i));
    return retval;
  }

//! @brief Devuelve la recta perpendicular a r que pasa por p.
Recta2d Recta2d::Perpendicular(const Pos2d &p) const
  { return Recta2d(cgr.perpendicular(p.ToCGAL())); }

//! @brief Devuelve la recta que resulta de aplicar a ésta el desplazamiento v.
Recta2d Recta2d::Offset(const Vector2d &v) const
  {
    const Pos2d p= Punto()+v;
    return Recta2d(p,VDir());
  }

//! @brief Devuelve la recta paralela a ésta que pasa por p.
Recta2d Recta2d::Paralela(const Pos2d &p) const
  {
    const Vector2d v= p-Punto();
    return Offset(v);
  }

//! @brief Devuelve una recta paralela a ésta a la distancia
//! que se pasa como parámetro. Si la distancia es positiva,
//! la nueva recta quedará a la derecha de la anterior.
Recta2d Recta2d::Offset(const GEOM_FT &d) const
  {
    const Vector2d v= d*VersorDir();
    const Vector2d n(v.y(),-v.x());
    return Offset(n);
  }

//! @brief Asigna valores a los puntos que definen la recta.
void Recta2d::Put(const Pos2d &p1,const Pos2d &p2)
  { DosPuntos(p1,p2); }



//! @brief Devuelve verdadero si la recta corta a la que se pasa como parámetro.
bool Recta2d::Interseca(const Recta2d &r2) const
  { return do_intersect(cgr,r2.cgr); }

//! @brief Devuelve la intersección de la Linea con un plano coord_i=cte.
GeomObj2d::list_Pos2d Recta2d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj::list_Pos2d lp;
    unsigned short int j=i;
    j++;
    if(j>2) j=1;
    Pos2d p;
    p.Set(i,d);
    const Vector2d i_= VDir();
    const Pos2d org(Punto(0));
    if (fabs(i_(i))<1.0E-12) return lp;
    const double l= getLambda(i,d,i_);
    p.Set(j,org(j)+l*i_(j));
    lp.push_back(p);
    return lp;
  }

//! @brief Devuelve el punto intersección de ambas rectas, if doesn't exists la
//! intersección devuelve la lista vacía.
GeomObj2d::list_Pos2d Recta2d::Interseccion(const Recta2d &r2) const
  {
    GeomObj2d::list_Pos2d retval;
    if(EsDegenerada())
      {
        std::cerr << "Recta2d::Interseccion(Recta2d): La recta: "
                  << *this << " es degenerada."  << std::endl;
        return retval;
      }
    if(r2.EsDegenerada())
      {
        std::cerr << "Recta2d::Interseccion(Recta2d): La recta: "
                  << r2 << " es degenerada."  << std::endl;
        return retval;
      }
    if(colineales(*this,r2))
      {
	std::cerr << "Recta2d::Interseccion(Recta2d): Las rectas coinciden, todos sus puntos pertenecen a la intersección." 
             << endl;
        return retval;
      }
    if(!paralelas(*this,r2))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgr,r2.cgr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << "recta2d::Interseccion(Recta2d): Error desconocido al intersecar las rectas:" << endl
                 << "  r: " << *this << endl
                 << "  r2: " << r2 << endl;
          }
      }
    return retval;
  }

//! @brief Devuelve un punto arbitrario de la recta.
//! Si i==j, se cumple que Punto(i) == Punto(j).
//! Además, l is directed from point(i)  to point(j), for all i < j.
Pos2d Recta2d::Punto(const int &i) const
  { return Pos2d(cgr.point(i)); }

//! @brief Devuelve la distancia al cuadrado entre las dos rectas.
GEOM_FT dist2(const Recta2d &r1,const Recta2d &r2)
  {
    GEOM_FT retval= 0.0;
    if(!intersecan(r1,r2)) //son paralelas
      if(r1 != r2) //NO son la misma recta.
        {
          const Pos2d p1= r1.Punto(0);
          const Pos2d p2= r2.Proyeccion(p1);
          retval= dist2(p1,p2);
	}
    return retval;
  }

//! @brief Devuelve el ángulo con el vector que se pasa como parámetro.
double Recta2d::Angulo(const Vector2d &v) const
  { return angulo(VDir(),v); }

//! @brief Devuelve el ángulo con el eje Y.
double Recta2d::Azimuth(void) const
  { return angulo(VDir(),Vector2d(0,1)); }

//! @brief Devuelve el ángulo de la recta con el vector.
double angulo(const Recta2d &r,const Vector2d &v)
  { return r.Angulo(v); }

//! @brief Devuelve el ángulo entre las rectas.
double angulo(const Recta2d &r1,const Recta2d &r2)
  { return r1.Angulo(r2.VDir()); }

bool Recta2d::Paralela(const Recta2d &r) const
  { return (paralelas(GetDir(),r.GetDir())); }

//! @brief Devuelve la recta bisectriz de ESTA
//! y la que se pasa como parámetro.
Recta2d Recta2d::Bisectriz(const Recta2d &r) const
  { return Recta2d(bisector(this->ToCGAL(),r.ToCGAL())); }

Recta2d Recta2d::getNormalizada(void) const
  { return Recta2d(Punto(),VersorDir()); }

//! @brief Devuelve verdadero si la recta es vertical.
bool Recta2d::EsVertical(void) const
  { return cgr.is_vertical(); }

//! @brief Devuelve verdadero si la recta es degenerada.
bool Recta2d::EsDegenerada(void) const
  { return cgr.is_degenerate(); }

//! @brief Devuelve verdadero si el punto está sobre la recta.
bool Recta2d::In(const Pos2d &p, const double &tol) const
  { return cgr.has_on(p.ToCGAL()); }

//! @brief Devuelve verdadero si el punto está al lado derecho de la recta.
bool Recta2d::LadoDerecho(const Pos2d &p) const
  { return cgr.has_on_negative_side(p.ToCGAL()); }

//! @brief Devuelve verdadero si el punto está al lado derecho de la recta.
bool Recta2d::LadoIzquierdo(const Pos2d &p) const
  { return cgr.has_on_positive_side(p.ToCGAL()); }

//! @brief Devuelve la distancia al cuadrado desde el punto a la recta.
GEOM_FT Recta2d::dist2(const Pos2d &p) const
  {
    const GEOM_FT A= a(),B= b(), C= c();
    return sqr(A*p.x()+B*p.y()+C)/(A*A+B*B);
  }

//! @brief Devuelve la distancia al cuadrado desde el punto a la recta.
GEOM_FT Recta2d::dist(const Pos2d &p) const
  { return sqrt(dist2(p)); }

//Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Recta2d::Ix(void) const
  { return 0.0; }

//Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Recta2d::Iy(void) const
  { return NAN; }

//Producto de inercia.
GEOM_FT Recta2d::Pxy(void) const
  { return NAN; }

//Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Recta2d::Iz(void) const
  { return NAN; }

bool operator==(const Recta2d &r1,const Recta2d &r2)
  {
    if(&r1==&r2)
      return true;
    else
      return (r1.cgr==r2.cgr); 
  }

//! @brief Devuelve la distancia entre las rectas.
GEOM_FT dist(const Recta2d &r1,const Recta2d &r2)
  { return sqrt_FT(dist2(r1,r2)); } 

bool colineales(const Recta2d &r1,const Recta2d &r2)
  {
    const Pos2d p1= r2.Punto(0);
    const Pos2d p2= r2.Punto(10);
    if( r1.In(p1) && r1.In(p2) )
      return true;
    else
      return false;
  }

//! @brief Returns true if intersection exists.
bool intersecan(const Recta2d &r1,const Recta2d &r2)
  { return r1.Interseca(r2); }

//! @brief Devuelve la intersección.
GeomObj2d::list_Pos2d interseccion(const Recta2d &r1,const Recta2d &r2)
  { return r1.Interseccion(r2); }

//! @brief Devuelve el punto de intersección (if exists).
Pos2d punto_interseccion(const Recta2d &r1, const Recta2d &r2)
  {
    Pos2d retval;
    GeomObj2d::list_Pos2d tmp= interseccion(r1,r2);
    if(tmp.empty())
      retval.setExists(false);
    else
      retval= *tmp.begin();
    return retval;
  }

//! @brief Aplica a la recta la transformación que se
//! pasa como parámetro.
void Recta2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d p1= trf2d.Transforma(Punto(0));
    const Pos2d p2= trf2d.Transforma(Punto(100));
    (*this)= Recta2d(p1,p2);
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
any_const_ptr Recta2d::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "(Recta2d::GetProp) Buscando propiedad: " << cod << std::endl;

    static GEOM_FT tmp_ft= 0.0;
    static Pos2d cdg;
    if(cod=="getParamA")
      {
        tmp_ft= GetParamA();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getParamB")
      {
        tmp_ft= GetParamB();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getDist")
      {
        const Pos2d tmp= popPos2d(cod);
        tmp_ft= dist(tmp);
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getVDir")
      {
        tmp_gp_vector2d= VDir();
        return any_const_ptr(tmp_gp_vector2d);
      }
    else if(cod=="offset")
      {
        const GEOM_FT d= popDouble(cod);
        tmp_gp_recta2d= Offset(d);
        return any_const_ptr(tmp_gp_recta2d);
      }
    else
      return Linea2d::GetProp(cod);
  }

void Recta2d::Print(std::ostream &os) const
  { os << PtoParametricas(0.0) << " " << PtoParametricas(100.0); }
void Recta2d::Plot(Plotter &psos) const
//La recta no se dibuja, primero hay que recortarla.
  {
  }


void Recta2d::SalvaCmd(std::ostream &os,const std::string &indent) const
  { salva_cmd(os,indent,"recta"); }

Recta2d mediatriz(const Pos2d &p1,const Pos2d &p2)
  { 
    const Segmento2d sg(p1,p2);
    return sg.Mediatriz();
  }
