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
//Poligono3d.cc

#include "Poligono3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d3/GmGrupo3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/geom/listas/auxiliares.h"


Poligono3d::Poligono3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : D2to3d(p1,p2,p3), plg2d()
  {
    push_back(p1);
    push_back(p2);
    push_back(p3);
  }

GeomObj::list_Pos3d Poligono3d::ListaVertices(void) const
  {
    GeomObj::list_Pos3d retval;
    register Poligono2d::vertex_iterator i= plg2d.vertices_begin();
    for(;i!=plg2d.vertices_end();i++)
      retval.push_back(to_3d(*i));
    return retval;
  }
Segmento3d Poligono3d::Lado(unsigned int i) const
  {
    Segmento2d sg2d= plg2d.Lado(i);
    return to_3d(sg2d);
  }

Segmento3d Poligono3d::Lado0(unsigned int i) const
  {
    Segmento2d sg2d= plg2d.Lado0(i);
    return to_3d(sg2d);
  }

Plano3d Poligono3d::GetPlanoLado(unsigned int i) const
  {
    Segmento3d lado= Lado(i);
    Vector3d v= GetPlano().Normal();
    return Plano3d(lado,v);
  }

Plano3d Poligono3d::GetPlanoLado0(unsigned int i) const
  { return GetPlanoLado(i+1); }

bool Poligono3d::In(const Pos3d &p,const double &tol)
  {
    if(!GetPlano().In(p,tol)) return false;
    const Pos2d p2d(to_2d(p));
    return plg2d.In(p2d,tol);
  }

//! @brief Devuelve el centro de gravedad del polígono.
Pos3d Poligono3d::Cdg(void) const
  { return to_3d(plg2d.Cdg()); }

std::vector<Poligono3d> Poligono3d::getPoligonosTributarios(void) const
  {
    const std::vector<Poligono2d> tmp= plg2d.getPoligonosTributarios();
    const size_t sz= tmp.size();
    std::vector<Poligono3d> retval(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= Poligono3d(get_ref(),tmp[i]);
    return retval;
  }

GEOM_FT Poligono3d::Ix(void) const
  {
    std::cerr << "Poligono3d::Ix() no implementada, se devuelve 0." << std::endl;
    return 0;
  }
GEOM_FT Poligono3d::Iy(void) const
  {
    std::cerr << "Poligono3d::Iy() no implementada, se devuelve 0." << std::endl;
    return 0;
  }
GEOM_FT Poligono3d::Iz(void) const
  {
    std::cerr << "Poligono3d::Iz() no implementada, se devuelve 0." << std::endl;
    return 0;
  }

GEOM_FT Poligono3d::GetMax(unsigned short int i) const
  {
    const GeomObj::list_Pos3d lv= ListaVertices();
    return get_max_i(i,lv.begin(),lv.end());
  }
GEOM_FT Poligono3d::GetMin(unsigned short int i) const
  {
    const GeomObj::list_Pos3d lv= ListaVertices();
    return get_min_i(i,lv.begin(),lv.end());
  }

void Poligono3d::Print(std::ostream &os) const
  {
    unsigned int nv= GetNumVertices();
    if(nv<1) return;
    os << Vertice(1);
    for(register unsigned int i= 2; i <= nv; i++)
      os << ", " << Vertice(i);
  }

//! @brief Devuelve el cuadrado de la distancia desde el punto al polígono
//! La distancia se calcula como el máximo de:
//!  -La distancia desde el punto al plano que contiene al polígono.
//! -Las distancias (con signo) del punto a cada uno de los semiespacios
//!  definidos por el plano que contiene a un lado y es normal al polígono.
//!
//! Si los vértices están dados en sentido horario, las distancias positivas
//! corresponden a puntos AL MISMO LADO DEL POLÍGONO respecto al segmento, en caso contrario
//! es necesario cambiar el signo de la distancia. 
GEOM_FT Poligono3d::distSigno2(const Pos3d &p,const bool &sentido_horario) const
  {
    const short int signo= (sentido_horario ? 1 : -1);
    const size_t nv= GetNumVertices();
    const size_t nl= GetNumLados();
    if(nv==0) return NAN;
    if(nv==1) return p.dist2(Vertice(1));
     
    //Distancia al plano que contiene al poligono
    register GEOM_FT d= GetPlano().dist2(p);
    //Distancia a los semiespacios definidos por los lados.
    for(register unsigned int i=1; i<=nl; i++)
      {
        SemiEspacio3d se3d(GetPlanoLado(i));
        const GEOM_FT d_i= signo*se3d.distSigno2(p);
        d= std::max(d,d_i);
      }
    return d;
  }
GEOM_FT Poligono3d::distSigno(const Pos3d &p,const bool &sentido_horario) const
  { return sqrt_FT(::Abs(distSigno2(p,sentido_horario))); }

//! @brief Devuelve la distancia desde el punto al polígono.
//! La distancia se calcula como el máximo de las 
//! distancias (con signo) del punto a cada uno de los planos
//!  que contienen a un lado y son perpendiculares al plano 
//!  que contiene al polígono.
//! Si el punto está dentro del polígono se devuelve 0.
GEOM_FT Poligono3d::dist2(const Pos3d &p) const
  {
    const GEOM_FT retval= distSigno2(p);
    return (retval >= 0 ? retval : 0);
  }


//! @brief Devuelve la distancia desde el punto al polígono.
//!La distancia se calcula como el máximo de:
//! -Las distancias (con signo) del punto a cada uno de los planos
//!  que contienen a un lado y son perpendiculares al plano 
//!  que contiene al polígono.
//! Si el punto está dentro del polígono se devuelve 0.
GEOM_FT Poligono3d::dist(const Pos3d &p) const
  {
    const GEOM_FT retval= distSigno(p);
    return (retval >= 0 ? retval : 0);
  }

std::list<Poligono3d> Poligono3d::Corta(const Plano3d &pl) const
//Devuelve los polígonos que resultan de cortar por el plano
//pl, el polígono p, que se pasa como parámetro.
  {
    std::list<Poligono3d> retval;
    const Plano3d pl_polig= GetPlano();
    if(pl_polig==pl) return retval;
    if(paralelos(pl_polig,pl)) return retval;

    GmGrupo3d gint= interseccion(pl_polig,pl);
    GeomObj3d *ptr=(*gint.begin());
    const Recta3d r= *((Recta3d *)ptr);

    const Pos2d p2dA= to_2d(r.Punto());
    const Pos2d p2dB= to_2d(r.Punto(100));
    const Recta2d r2d(p2dA,p2dB);

    std::list<Poligono2d> inter= corta(plg2d,r2d);
    for(std::list<Poligono2d>::const_iterator i= inter.begin(); i!=inter.end();i++)
      retval.push_back(Poligono3d(get_ref(),*i));

    return retval;
  }

//! @brief Devuelve verdadero si alguno de los vertices toca el cuadrante
//! que se pasa como parámetro.
bool Poligono3d::TocaCuadrante(const int &cuadrante) const
  {
    register Poligono2d::vertex_iterator i= plg2d.vertices_begin();
    for(;i!=plg2d.vertices_end();i++)
      if(to_3d(*i).Cuadrante() == cuadrante)
        return true;
    return false;
  }
