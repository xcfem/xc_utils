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
//MallaTriang3d.cc

#include "MallaTriang3d.h"
#include "xc_utils/src/geom/d2/Triangulo3d.h"
#include "Triedro3d.h"
#include "xc_utils/src/gnu_gts/GTSSurface.h"
#include "xc_utils/src/gnu_gts/GTSEdge.h"
#include "xc_utils/src/gnu_gts/TriangleMap.h"


template <class HDS>
class Build_poliedro: public CGAL::Modifier_base<HDS>
  {
    const GTSSurface &sf;
  public:
    Build_poliedro(const GTSSurface &gts_surf)
      : sf(gts_surf) {}
    void operator()( HDS& hds)
      {
        const size_t num_facetas= sf.GetNumCaras();
        const size_t num_aristas= sf.GetNumAristas();
        const size_t num_vertices= sf.GetNumVertices();
        TriangleMap mt= sf.GetTriangleMap();
        // Postcondition: `hds' is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
        B.begin_surface(num_vertices,num_facetas,num_aristas);
        const VerticesMap &vertices= mt.getVertices();
        for(VerticesMap::const_iterator i= vertices.begin();
            i!= vertices.end();i++)
          {
            const Pos3d coo_vertice= (*i).second;
            B.add_vertex(coo_vertice.ToCGAL());        
          }
        const TriangleFaces &triangles= mt.getFaces();
        for(TriangleFaces::const_iterator j= triangles.begin();
            j!=triangles.end();j++)
          {
            B.begin_facet();
            B.add_vertex_to_facet((*j).V1()-1);
            B.add_vertex_to_facet((*j).V2()-1);
            B.add_vertex_to_facet((*j).V3()-1);
            B.end_facet();
          }
        B.end_surface();
      }
  };

MallaTriang3d::MallaTriang3d(const GTSSurface &gts_surf)
  {
    typedef CGPoliedro_3::HalfedgeDS HalfedgeDS;
    Build_poliedro<HalfedgeDS> bpoli(gts_surf);
    cgpoliedro.delegate(bpoli);
    //CGAL_assertion( P.is_triangle( P.halfedges_begin()));
  }

MallaTriang3d GTSSurface2MallaTriang3d(const GTSSurface &gts_surf)
  { return MallaTriang3d(gts_surf); }
GTSSurface MallaTriang3d::get_gts_surface(void) const
  {
     GTSSurface retval;
//     MallaTriang3d tmp= Triangula();
//     typedef MapPoligonos<CGMallaTriang_3> map_poligonos;
//     map_poligonos map= GetMapPoligonos();
//     deque<GTSVertex> vertices;
//     for(map_poligonos::vertices_const_iterator i= map.VerticesBegin();
//         i!= map.VerticesEnd(); i++)
//       {
//         Pos3d pos= (*i).second;
//         GTSVertex v(pos.x(),pos.y(),pos.z());
//         vertices.push_back(v);
//       }
//     typedef pair<size_t,size_t> verts_arista;
//     typedef set<verts_arista > set_aristas;
//     set_aristas s_aristas;
//     deque<GTSEdge> aristas;
//     for(map_poligonos::caras_const_iterator i= map.CarasBegin();
//         i!= map.CarasEnd(); i++)
//       {
//         const size_t v1= (*i).Vertice(1);
//         const size_t v2= (*i).Vertice(2);
//         const size_t v3= (*i).Vertice(3);
//         const verts_arista lado1(v1,v2);
//         if(s_aristas.find(lado1)== s_aristas.end()) //Arista nueva.
//           {
// 	    s_aristas.insert(lado1);
//             aristas.push_back(GTSEdge(vertices[lado1.first],vertices[lado1.second]));
//           }
//         const verts_arista lado2(v2,v3);
//         if(s_aristas.find(lado2)== s_aristas.end()) //Arista nueva.
//           {
// 	    s_aristas.insert(lado2);
//             aristas.push_back(GTSEdge(vertices[lado2.first],vertices[lado2.second]));
//           }
//         const verts_arista lado3(v3,v1);
//         if(s_aristas.find(lado3)== s_aristas.end()) //Arista nueva.
//           {
// 	    s_aristas.insert(lado3);
//             aristas.push_back(GTSEdge(vertices[lado3.first],vertices[lado3.second]));
//           }
//         GTSEdge l1= XXX
//       }
    
    std::cerr << "MallaTriang3d::get_gts_surface no implementada." << std::endl;
    return retval;
  }

Triangulo3d MallaTriang3d::GetTrianguloCara(const Facet_const_iterator &f) const
  {
    Facet::Halfedge_const_handle h = f->halfedge();
    return Triangulo3d(Pos3d(h->vertex()->point()),
                       Pos3d(h->next()->vertex()->point()),
                       Pos3d(h->next()->next()->vertex()->point()));
  }
MallaTriang3d::Facet_const_iterator MallaTriang3d::busca_triedro(const Pos3d &org,const Pos3d &p,const double &tol) const
  //Busca el triedro formado por el punto org y una de las facetas
  //que contiene al punto p que se pasa como parámetro.
  {
    const size_t nf= GetNumCaras();
    Facet_const_iterator retval= facets_end();
    if(nf<4) return retval;
    for(Facet_const_iterator i= facets_begin();i!=facets_end();i++)
      {
        Triangulo3d tf(GetTrianguloCara(i));
        Triedro3d triedro(org,tf.Vertice(1),tf.Vertice(2),tf.Vertice(3));
        if(triedro.In(p,tol))
          {
            retval= i;
            break;
          }
      }
    return retval;
  }
MallaTriang3d::Facet_const_iterator MallaTriang3d::BuscaTriedro(const Pos3d &org,const Pos3d &p,const double &tol) const
   { return busca_triedro(org,p,tol); }
