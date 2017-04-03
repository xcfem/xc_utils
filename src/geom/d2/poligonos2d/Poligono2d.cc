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
//Poligono2d.cc

#include "Poligono2d.h"
#include "bool_op_poligono2d.h"
#include<CGAL/create_offset_polygons_2.h>
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/d1/Polilinea2d.h"
#include "xc_utils/src/geom/d2/Semiplano2d.h"
#include "xc_utils/src/geom/d2/BND2d.h"

#include <CGAL/Boolean_set_operations_2.h>
#include <boost/any.hpp>

#include "xc_utils/src/geom/cdg.h"
#include "xc_utils/src/geom/trf/Translation2d.h"
#include "xc_utils/src/geom/listas/utils_list_pos2d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos2d.h"


//! @brief Constructor por defecto.
Poligono2d::Poligono2d(void)
  : SupPoligonal2d(), cgpol() {}

//! @brief Constructor.
Poligono2d::Poligono2d(const CGPoligono_2 &p)
  : SupPoligonal2d(), cgpol(p) {}

//! @brief Constructor.
Poligono2d::Poligono2d(const GeomObj::list_Pos2d &lv)
  {
    for(list_Pos2d::const_iterator i= lv.begin(); i!=lv.end(); i++)
      push_back(*i);
  }

//! @brief Constructor.
Poligono2d::Poligono2d(const Polilinea2d &p)
  {
    //XXX Falla si la linea se interseca a sí misma.
    for(Polilinea2d::const_iterator i= p.begin(); i!=p.begin(); i++)
      push_back(*i);
  }

//! @brief Constructor.
Poligono2d::Poligono2d(const std::list<Poligono2d> &lp)
  {
    if(!lp.empty())
      {
        (*this)= *lp.begin();
        if(lp.size()>1)
	  std::cerr << "Poligono2d::Poligono2d; la lista contiene más de un polígono." << std::endl;
      }
    else
      std::cerr << "Poligono2d::Poligono2d; la lista está vacía." << std::endl;
  }

//! @brief Constructor virtual.
GeomObj *Poligono2d::clon(void) const
  { return new Poligono2d(*this); }

//! @brief Devuelve un polígono paralelo a éste a distancia
//! «d». Por el exterior si la distancia es positiva o por
//! el interior en otro caso.
Poligono2d Poligono2d::Offset(const GEOM_FT &d) const
  {
    Poligono2d retval;
    typedef boost::shared_ptr<CGPoligono_2> PolygonPtr;
    typedef std::vector<PolygonPtr> PolygonPtrVector;
    PolygonPtrVector offset_polygons;
    if(d<0)
      offset_polygons= CGAL::create_interior_skeleton_and_offset_polygons_2(-d,cgpol);
    else
      offset_polygons= CGAL::create_exterior_skeleton_and_offset_polygons_2(d,cgpol);
    if(!offset_polygons.empty())
      {
        if(offset_polygons.size()!=1)
          std::cerr << "Poligono2d::Offset; se obtuvo más de un polígono" << std::endl;
        retval.cgpol= *offset_polygons[0];
      }
    return retval;
  }

//! @brief Devuelve verdadero si el punto está contenido en el polígono.
bool Poligono2d::In(const Pos2d &p, const double &tol) const
  {
    if(cgpol.has_on_boundary(p.ToCGAL())) return true;
    if(cgpol.has_on_bounded_side(p.ToCGAL())) return true;
    return false;
  }

//! @brief Devuelve verdadero si la polilinea está contenida en el polígono.
bool Poligono2d::In(const Polilinea2d &p) const
  { return In(p.begin(),p.end()); }

//! @brief Devuelve verdadero si el polígono está contenido en éste.
bool Poligono2d::In(const Poligono2d &p) const
  { return In(p.vertices_begin(),p.vertices_end()); }

//! @brief Devuelve verdadero si el polígono contiene al punto.
bool Poligono2d::Overlap(const Pos2d &p) const
  { return In(p); }


//! @brief Devuelve verdadero si la recta y el Poligono
//! tienen algun punto en común.
bool Poligono2d::Overlap(const Recta2d &r) const
  { return SupPoligonal2d::Overlap(r); }

  
//! @brief Devuelve verdadero si la semirrecta y el Poligono
//! tienen algun punto en común.
bool Poligono2d::Overlap(const SemiRecta2d &sr) const
  { return SupPoligonal2d::Overlap(sr); }

//! @brief Devuelve verdadero si el segmento y el Poligono
//! tienen algun punto en común.
bool Poligono2d::Overlap(const Segmento2d &sg) const
  {
    bool retval= false;
    if(In(sg.Origen()))
      retval= true;
    else if(In(sg.Destino()))
      retval= true;
    else
      {
        GeomObj::list_Pos2d tmp= GetPolilinea().Interseccion(sg);
        retval= !tmp.empty();
      }
    return retval;
  }

//! @brief Devuelve verdadero si ambos el BND y el poligono
//! tienen algun punto en común.
bool Poligono2d::Overlap(const BND2d &bnd) const
  { return bnd.Overlap(*this); }

//! @brief Devuelve verdadero si la el polígono se superpone
//! con la polilinea que se pasa como parámetro.
bool Poligono2d::Overlap(const Polilinea2d &p) const
  {
    bool retval= Overlap(p.begin(),p.end());
    if(!retval)
      for(Polilinea2d::const_iterator j=p.begin();j!=p.end();j++)
        if(Overlap(p.GetSegmento(j)))
          {
            retval= true;
            break;
          }
    return retval;
  }

//! @brief Devuelve verdadero si el polígono se superpone
//! con el que se pasa como parámetro.
bool Poligono2d::Overlap(const Poligono2d &p) const
  { 
    bool retval= Overlap(p.vertices_begin(),p.vertices_end());
    if(!retval)
      retval= p.Overlap(vertices_begin(),vertices_end());
    else if(!retval)
      {
        const unsigned int nl= p.GetNumLados();
        for(unsigned int i= 1; i<=nl;i++)
          if(Overlap(p.Lado(i)))
            {
              retval= true;
               break;
            }
      }
    else if(!retval)
      {
        const unsigned int nl= GetNumLados();
        for(unsigned int i= 1; i<=nl;i++)
          if(p.Overlap(Lado(i)))
            {
              retval= true;
              break;
            }
      }
    return retval;
  }

//! @brief Devuelve verdadero si el polígono se superpone
//! con alguno de los de la lista que se pasa como parámetro.
bool Poligono2d::Overlap(const std::list<Poligono2d> &l) const
  {
    bool retval= false;
    if(!l.empty())
      for(std::list<Poligono2d>::const_iterator i=l.begin();i!=l.end();i++)
        if(Overlap(*i))
          {
            retval= true;
            break;
          }
    return retval;
  }

//! @brief Devuelve el valor maximo de la coordenada i.
GEOM_FT Poligono2d::GetMax(unsigned short int i) const
  {
    if (GetNumVertices() < 1) return 0.0;
    GEOM_FT retval;
    const size_t j= (i-1)%2+1;
    if(j==1)
      retval=(*cgpol.right_vertex()).x();
    else
      retval=(*cgpol.top_vertex()).y(); //j==2
    return retval;
  }

//! @brief Devuelve el valor minimo de la coordenada i.
GEOM_FT Poligono2d::GetMin(unsigned short int i) const
  {
    if (GetNumVertices() < 1) return 0.0;
    GEOM_FT retval;
    const size_t j= (i-1)%2+1;
    if(j==1)
      retval= (*cgpol.left_vertex()).x();
    else
      retval= (*cgpol.bottom_vertex()).y(); //j==2
    return retval;
  }

GeomObj::list_Pos2d Poligono2d::ListaVertices(void) const
  {
    GeomObj::list_Pos2d lv;
    if(GetNumVertices() > 0)
      for(register CGPoligono_2::Vertex_iterator j=cgpol.vertices_begin(); j != cgpol.vertices_end();j++)
        lv.push_back(Pos2d(*j));
    return lv;
  }

//! @brief Aplica a los vértices la transformación que se pasa como parámetro.
void Poligono2d::Transforma(const Trf2d &trf2d)
  { trf2d.Transforma(cgpol.vertices_begin(),cgpol.vertices_end()); }

//! Devuelve los polígonos que resultan de cortar por la recta
//! r, el polígono p, que se pasa como parámetro.
std::list<Poligono2d> corta(const Poligono2d &p,const Recta2d &r)
  {
    std::list<Poligono2d> retval;
    if(!intersecan(p.Bnd(),r)) return retval;
    Semiplano2d sp1(r);
    Semiplano2d sp2= sp1.GetSwap();
    retval= interseccion(p,sp1);
    const std::list<Poligono2d> inter2= interseccion(p,sp2);
    retval.insert(retval.end(),inter2.begin(),inter2.end());
    return retval;
  }

//! @brief Devuelve el área del polígono.
GEOM_FT Poligono2d::Area(void) const
  { return ::Abs(AreaSigno()); }

//! @brief Devuelve los poligonos que forman el área tributaria
//! de cada vértice.
std::vector<Poligono2d> Poligono2d::getPoligonosTributarios(void) const
  {
    const size_t nv= GetNumVertices();
    const Pos2d cdg= Cdg();
    const Poligono2d pMed= agrega_puntos_medios(*this);
    const size_t nvPMed= pMed.GetNumVertices();
    std::vector<Poligono2d> retval(nv);
    for(size_t i=0;i<nv;i++)
      {
        const size_t j1= 2*i;
        const Pos2d v1= pMed.Vertice0(j1);
        size_t j2= j1+1;
        if(j2>=nvPMed) j2= 0;
        const Pos2d v2= pMed.Vertice0(j2);
        size_t j3= nvPMed-1;
        if(j1>=1) j3= j1-1;
        const Pos2d v3= pMed.Vertice0(j3);
        Poligono2d tmp;
        tmp.push_back(v1);
        tmp.push_back(v2);
        tmp.push_back(cdg);
        tmp.push_back(v3);
        retval[i]= tmp;
      }
    return retval;
  }

//! @brief Devuelve las áreas de los polígonos tributarios (una por
//! vértice).
std::vector<double> Poligono2d::getAreasTributarias(void) const
  {
    const size_t nv= GetNumVertices();
    std::vector<double> retval(nv,0.0);
    std::vector<Poligono2d> plgs= getPoligonosTributarios();
    for(size_t i=0;i<nv;i++)
      retval[i]= plgs[i].Area();
    return retval;
  }

//! @brief Devuelve los recubrimientos de las fibras que se pasan como parámetro.
std::deque<GEOM_FT> &Poligono2d::GetRecubrimientos(const ListaPos2d &l) const
  { return l.GetRecubrimientos(*this); }

//! @brief Devuelve un polígono con un vértice en el punto medio
//! de cada lado del polígono primitivo (se usa en XC::GeomSection::getAnchoMecanico).
Poligono2d agrega_puntos_medios(const Poligono2d &plg)
  {
    Poligono2d retval;
    const size_t num_vertices= plg.GetNumVertices();
    if(num_vertices>1)
      {
        Pos2d p1= plg.Vertice(1);
        retval.push_back(p1);
        Pos2d pmed,p2;
        for(register size_t i=2;i<=num_vertices;i++)
          {
            p2= plg.Vertice(i);
            pmed= Segmento2d(p1,p2).Cdg();
            retval.push_back(pmed);
            retval.push_back(p2);
            p1= p2;
          }
        p2= plg.Vertice(1);
        retval.push_back(Segmento2d(p1,p2).Cdg());
      }
    return retval;
  }

//! @brief Devuelve la intesección del polígono con la recta.
Segmento2d Poligono2d::Clip(const Recta2d &r) const
  { return SupPoligonal2d::Clip(r); }

//! @brief Devuelve la intesección del polígono con la semirecta.
Segmento2d Poligono2d::Clip(const SemiRecta2d &sr) const
  { return SupPoligonal2d::Clip(sr); }

//! @brief Devuelve la intesección del polígono con el segmento.
Segmento2d Poligono2d::Clip(const Segmento2d &sg) const
  { return SupPoligonal2d::Clip(sg); }

//! @brief Devuelve los polígonos que resultan de recortar éste por
//! por el BND que se pasa como parámetro.
std::list<Poligono2d> Poligono2d::Clip(const BND2d &bnd) const
  { return Clip(bnd.GetPoligono()); }

//! @brief Devuelve los polígonos que resultan de recortar éste por
//! por el que se pasa como parámetro.
std::list<Poligono2d> Poligono2d::Clip(const Poligono2d &otro) const
  { return interseccion(*this,otro); }

//! @brief Recorta este polígono con el que se pasa como parámetro
void Poligono2d::clipBy(const Poligono2d &plg)
  { (*this)= Poligono2d(Clip(plg)); }

//! @brief Devuelve la intersección de este polígono con el que
//! se pasa como parámetro.
std::list<Poligono2d> Poligono2d::Interseccion(const Semiplano2d &sp) const
  { return interseccion(*this,sp); }

//! @brief Devuelve la unión de este polígono con el que
//! se pasa como parámetro.
Poligono2d Poligono2d::getUnion(const Poligono2d &otro) const
  {
    Poligono2d retval;
    std::list<Poligono2d> polUnion= join(*this,otro);
    if(!polUnion.empty())
      retval= Poligono2d(polUnion);
    else
      std::cerr << "Error en unión de polígonos." << std::endl;
    return retval;
  }

void Poligono2d::une(const Poligono2d &otro)
  { (*this)= getUnion(otro); }

void Poligono2d::une(const std::list<Poligono2d> &l)
  {
    const std::string str_error= "Poligono2d::une; error en unión de polígono con lista.";
    if(!l.empty())
      {
        const std::list<Poligono2d> tmp= join(l,*this);
        if(tmp.empty())
          std::cerr << str_error << " La unión está vacía." << std::endl;
        else
          (*this)= Poligono2d(tmp);
      }
  }

// //! @brief Devuelve la lista de polígonos que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
// std::list<Poligono2d> Poligono2d::crea_lista_poligono2d(const std::string &str) const
//   {
//     check_comillas(str);
//     const std::deque<boost::any> tmp= crea_deque_boost_any(str);
//     const size_t sz= tmp.size();
//     std::list<Poligono2d> retval;
//     for(size_t i= 0;i<sz;i++)
//       retval.push_back(convert_to_poligono2d(tmp[i]));
//     return retval;
//   }

Pos2d cdg(const std::list<Poligono2d> &l)
  { return cdg(l.begin(),l.end()); }


