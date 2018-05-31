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
//Poliedro3d.cc

#include "Poliedro3d.h"
#include "../../d2/Triang3dMesh.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d2/Poligono3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/IO/Polyhedron_geomview_ostream.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include "quad-triangle.h"
#include "bool_op_poliedro3d.h"
#include "VertexMap.h"
#include <set>
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"





//! @brief Constructor por defecto.
Poliedro3d::Poliedro3d(void): cgpoliedro() {}

//! @brief Constructor.
Poliedro3d::Poliedro3d(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3)
  : cgpoliedro()
  { make_tetrahedron(p0,p1,p2,p3); }

//! @brief Constructor.
Poliedro3d::Poliedro3d(const std::deque<SemiEspacio3d> &se)
  : cgpoliedro()
  { make_polyhedron(se); }


//! @brief Constructor.
Poliedro3d::Poliedro3d(const SemiEspacio3d &se1, const SemiEspacio3d &se2,const SemiEspacio3d &se3, const SemiEspacio3d &se4)
  { make_tetrahedron(se1,se2,se3,se4); }

//! @brief Constructor.
Poliedro3d::Poliedro3d(const EPoliedro &e)
  : cgpoliedro(empobrece(e)) {}

//! @brief Constructor de copia.
Poliedro3d::Poliedro3d(const Poliedro3d &otro) 
  : PolyhedronBase(otro), cgpoliedro(otro.cgpoliedro) {}

//! @brief Operador asignación.
Poliedro3d &Poliedro3d::operator=(const Poliedro3d &otro)
  {
    PolyhedronBase::operator=(otro);
    cgpoliedro= otro.cgpoliedro;
    return *this;
  }

//! @brief Constructor virtual.
GeomObj *Poliedro3d::clon(void) const
  { return new Poliedro3d(*this); }

void Poliedro3d::make_tetrahedron(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3)
  { cgpoliedro.make_tetrahedron(p0.ToCGAL(),p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL()); }

void Poliedro3d::make_polyhedron(const std::deque<SemiEspacio3d> &se)
  {
    TripletMap<Pos3d> vertices= vertices_poliedro(se);
    BuildFromVertexMap build(vertices);
    cgpoliedro.delegate(build);
  }

void Poliedro3d::make_tetrahedron(const SemiEspacio3d &se1, const SemiEspacio3d &se2,const SemiEspacio3d &se3, const SemiEspacio3d &se4)
  {
    std::deque<SemiEspacio3d> se;
    se.push_back(se1);
    se.push_back(se2);
    se.push_back(se3);
    se.push_back(se4);
    make_polyhedron(se);
  }

// //! @brief Interpreta los semiespacios que definen el poliedro.
// //! @param cle Si es verdadero borra los vértices, caras y aristas
// //! que se hubieran definido previamente.
// void Poliedro3d::semiespacios(const std::string &str,const bool &cle)
//   {
//     const std::deque<SemiEspacio3d> se= interpretaSemiEspacios3d(str);
//     const size_t sz= se.size();
//     if(sz>=4)
//       {
//         if(cle)
//           clear();
//         make_polyhedron(se);
//       }
//     else
//       std::cerr << "Poliedro3d::semiespacios; "
//                 << "se esperaban al menos cuatro semiespacios." << std::endl;
//   }

//! @brief Return the sum of the areas of the faces.
GEOM_FT Poliedro3d::getArea(void) const
  {
    GEOM_FT retval= 0.0;
    for(Poliedro3d::Facet_const_iterator i= facets_begin();i!=facets_end();i++)
      retval+= GetCara(i).getArea();
    return retval;
  }

GEOM_FT Poliedro3d::GetMax(unsigned short int i) const
  {
    CGPoliedro_3::Vertex_const_iterator vi= cgpoliedro.vertices_begin();
    GEOM_FT retval= vi->point().cartesian(i-1);
    for(;vi!=cgpoliedro.vertices_end();vi++)
      retval= std::max(retval,vi->point().cartesian(i-1));
    return retval;
  }
GEOM_FT Poliedro3d::GetMin(unsigned short int i) const
  {
    CGPoliedro_3::Vertex_const_iterator vi= cgpoliedro.vertices_begin();
    GEOM_FT retval= vi->point().cartesian(i-1);
    for(;vi!=cgpoliedro.vertices_end();vi++)
      retval= std::min(retval,vi->point().cartesian(i-1));
    return retval;
  }

GeomObj::list_Pos3d Poliedro3d::GetVerticesCara(const Facet_const_iterator &f) const
  {
    Facet::Halfedge_const_handle h = f->halfedge();
    GeomObj::list_Pos3d retval;
    retval.push_back(Pos3d(h->vertex()->point()));
    retval.push_back(Pos3d(h->next()->vertex()->point()));
    retval.push_back(Pos3d(h->next()->next()->vertex()->point()));
    return retval;
  }

GeomObj::list_Pos3d Poliedro3d::getVertices(void) const
  {
    GeomObj::list_Pos3d retval;
    for(CGPoliedro_3::Vertex_const_iterator vi= cgpoliedro.vertices_begin();vi!=cgpoliedro.vertices_end();vi++)
      retval.push_back(vi->point());
    return retval;
  }

Plane Poliedro3d::GetPlanoCara(const Facet_const_iterator &f) const
  {
    Facet::Halfedge_const_handle h= f->halfedge();
    Plane retval(h->vertex()->point(),h->next()->vertex()->point(),h->next()->next()->vertex()->point());
    return retval;
  }

//! @brief Return la cara correspondiente al iterador.
Poligono3d Poliedro3d::GetCara(const Facet_const_iterator &f) const
  {
    const GeomObj::list_Pos3d vertices= getVertices();
    Poligono3d retval(vertices.begin(),vertices.end());
    return retval;
  }

//! @brief Return las caras del poliedro.
std::deque<Poligono3d> Poliedro3d::GetCaras(void) const
  {
    std::deque<Poligono3d> retval;
    for(Poliedro3d::Facet_const_iterator i= facets_begin();i!=facets_end();i++)
      retval.push_back(GetCara(i));
    return retval;
  }

void Poliedro3d::Print(std::ostream &os) const
  {
    CGAL::set_ascii_mode(os);
    CGAL::set_pretty_mode(os);
    os << cgpoliedro << std::endl;
  }

void Poliedro3d::Print(CGview_stream &v) const
  {
    v << cgpoliedro;
  }

void Poliedro3d::ReadOFF(std::istream &is)
//Lee el poliedro desde un archivo de tipo Object File Format.
  { is >> cgpoliedro; }

CGview_stream &operator<<(CGview_stream &v,const Poliedro3d &p)
  {
    p.Print(v);
    return v;
  }

EPoliedro Poliedro3d::GetEnriquecido(void) const
  { return enriquece(cgpoliedro); }


Poliedro3d subdivide_quad_triangle(const Poliedro3d &pol,bool smooth_boundary)
  {
    CSubdivider_quad_triangle<EPoliedro,GEOMKernel> subdivider;
    EPoliedro retval, tmp(pol.GetEnriquecido());
    subdivider.subdivide(tmp,retval);
    return Poliedro3d(retval);
  }

Triang3dMesh Poliedro3d::Triangula(void) const
  {
    EPoliedro retval(GetEnriquecido());
    EPoliedro::Facet_iterator pFacet;
    for(pFacet = retval.facets_begin();
        pFacet != retval.facets_end();
        pFacet++)
      {
        const unsigned int degree = EPoliedro::degree(pFacet);
        CGAL_assertion(degree >= 3);

        const EPoliedro::Halfedge_handle pHalfedge1 = pFacet->halfedge();
        if(degree==4)
          {
            const EPoliedro::Halfedge_handle pHalfedge2 = pHalfedge1->next()->next();
            retval.split_facet(pHalfedge1,pHalfedge2);
          }
        else
          if(degree>4)
            {
              if(pHalfedge1->is_border())
                std::cerr << "Se intentó subdividir una cara hueca." << std::endl;
              else
                retval.create_center_vertex(pHalfedge1);
            }

      }
    return Triang3dMesh(Poliedro3d(retval));
  }

//! @brief Return the SIGNED distance from the point to the tetrahedron.
//! The distance is computed as the maximum of the distances from the point
//! to each of the planes that limit the tetrahedron.
GEOM_FT Poliedro3d::PseudoDist(const Pos3d &p) const
  {
    const size_t nv= GetNumVertices();
    assert(nv>0);
    Poliedro3d::Vertex_const_iterator pVertex0= vertices_begin();
    if(nv==1) return p.dist(pVertex0->point());
    Poliedro3d::Vertex_const_iterator pVertex1= pVertex0; pVertex1++;
    if(nv==2) return p.dist(Segmento3d(pVertex0->point(),pVertex1->point()));
    Poliedro3d::Facet_const_iterator i= facets_begin();
    const Plane pl(GetPlanoCara(i));
    GEOM_FT retval= pl.PseudoDist(p);
    for(;i!=facets_end();i++)
      {
        const Plane plano(GetPlanoCara(i));
        const GEOM_FT d1= plano.PseudoDist(p);
        retval= std::max(retval,d1);
      }
    return retval;
  }

//! @brief Return verdadero si alguno de los vertices toca el cuadrante
//! que se pasa como parámetro.
bool Poliedro3d::TocaCuadrante(const int &cuadrante) const
  {
    for(CGPoliedro_3::Vertex_const_iterator vi= cgpoliedro.vertices_begin();vi!=cgpoliedro.vertices_end();vi++)
      if(Pos3d((*vi).point()).Cuadrante() == cuadrante)
        return true;
    return false;
  }

