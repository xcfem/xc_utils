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
//MapPoligonos.h

#ifndef MAP_POLIGONOS_H
#define MAP_POLIGONOS_H

#include <deque>
#include <CGAL/iterator.h>
#include "../../tipos_cgal.h"
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <iostream>
#include <map>


//! @ingroup GEOM
//
//! @brief Almacena los indices de los vértices
//! de un polígono.
class StoVerticesPoligono
  {
  protected:
    std::deque<size_t> ind_vertices;

  public:
    StoVerticesPoligono(const size_t &sz,const size_t &V);
    inline size_t GetNumVertices(void) const
      { return ind_vertices.size(); }
    inline const size_t &Vertice(const size_t &i) const
      { return ind_vertices[(i-1)]; }
    inline size_t &Vertice(const size_t &i)
      { return ind_vertices[(i-1)]; }
    void Print(std::ostream &os) const;
  };

template <class TPOL>
class IndVerticesPoligono: public StoVerticesPoligono
  {
  public:
    typedef typename TPOL::Vertex_const_iterator VCI;
    typedef CGAL::Inverse_index<VCI> Index;
    typedef typename TPOL::Halfedge_around_facet_const_circulator HFCC;

  public:
    IndVerticesPoligono(const Index &index,const HFCC &f);
  };

template <class TPOL>
IndVerticesPoligono<TPOL>::IndVerticesPoligono(const IndVerticesPoligono<TPOL>::Index &index,const IndVerticesPoligono<TPOL>::HFCC &ihc)
  : StoVerticesPoligono(circulator_size(ihc),0)
  {
    HFCC hc= ihc;
    HFCC hc_end = hc;
    CGAL_assertion(circulator_size( hc) >= 3);
    size_t i= 0;
    do
      {
        ind_vertices[i]= index[VCI(hc->vertex())];
        ++hc; i++;
      }
    while(hc != hc_end);
  }

template <class TPOS>
class MapPosVertices: protected std::map<size_t,TPOS>
  {

  public:
    typedef std::map<size_t,TPOS> map_p3d;
    typedef typename map_p3d::iterator iterator;
    typedef typename map_p3d::const_iterator const_iterator;

    inline const_iterator begin(void) const
      { return map_p3d::begin(); }
    inline const_iterator end(void) const
      { return map_p3d::end(); }
    inline iterator begin(void)
      { return map_p3d::begin(); }
    inline iterator end(void)
      { return map_p3d::end(); }
    void insert(const size_t &i,const TPOS &p);
    void Print(std::ostream &os) const;
  };

template <class TPOS>
void MapPosVertices<TPOS>::insert(const size_t &i,const TPOS &p)
  { (*this)[i]= p; }
template <class TPOS>
void MapPosVertices<TPOS>::Print(std::ostream &os) const
  {
    for(const_iterator i= begin();i!=end();i++)
      os << "Vertice: " << (*i).first << ": " << (*i).second << std::endl;
  }

template <class TPOL>
class MapPoligonos
  {
  public:
    typedef IndVerticesPoligono<TPOL> IndVertices;
    typedef typename IndVertices::VCI VCI;
    typedef typename IndVertices::Index Index;
    typedef typename IndVertices::HFCC HFCC;
    typedef typename TPOL::Vertex::Point Point;
    typedef MapPosVertices<Point> map_pos_vertices;
    typedef typename map_pos_vertices::const_iterator vertices_const_iterator;
    typedef typename std::deque<IndVertices >::const_iterator caras_const_iterator;

  private:
    map_pos_vertices mv;
    std::deque<IndVertices> caras;
  public:

    MapPoligonos(const TPOL &pol);

    vertices_const_iterator VerticesBegin(void) const
      { return mv.begin(); }
    vertices_const_iterator VerticesEnd(void) const
      { return mv.end(); }
    caras_const_iterator CarasBegin(void) const
      { return caras.begin(); }
    caras_const_iterator CarasEnd(void) const
      { return caras.end(); }

    void Print(std::ostream &os) const;
  };

template <class TPOL>
MapPoligonos<TPOL>::MapPoligonos(const TPOL &pol)
  {
    typedef typename TPOL::Facet_const_iterator FCI;
    size_t cont= 0;
    for(VCI vi = pol.vertices_begin();
            vi != pol.vertices_end(); ++vi)
      {
        mv.insert(cont,vi->point());
        cont++;
      }
    const Index index(pol.vertices_begin(),pol.vertices_end());
    for(FCI fi = pol.facets_begin(); fi != pol.facets_end(); ++fi)
      {
        HFCC hc = fi->facet_begin();
        caras.push_back(IndVertices(index,hc));
      }
  }

template <class TPOL>
void MapPoligonos<TPOL>::Print(std::ostream &os) const
  {
    os << "Lista de vértices: " << std::endl;
    mv.Print(os);
    os << "Lista de caras: " << std::endl;
    for(caras_const_iterator i= caras.begin();i!=caras.end();i++)
      {
        (*i).Print(os);
        os << std::endl;
      }
  }


template <class TPOL>
std::ostream &operator<<(std::ostream &os, const MapPoligonos<TPOL> &mt)
  {
    mt.Print(os);
    return os;
  }

template <class TPOL>
MapPoligonos<TPOL> getMapPoligonos(const TPOL &pol)
  { return MapPoligonos<TPOL>(pol); }

template <class TPOLORG,class HDS,class CVPOS>
class Build_tdest_polyhedron: public CGAL::Modifier_base<HDS>
  {
    const TPOLORG &sf;

  public:
    typedef typename HDS::Vertex Vertex;
    typedef typename Vertex::Point Point;
    typedef typename MapPoligonos<TPOLORG>::vertices_const_iterator vconst_iter;
    typedef typename MapPoligonos<TPOLORG>::caras_const_iterator cconst_iter;

  public:
    Build_tdest_polyhedron(const TPOLORG &pol)
      : sf(pol) {}
    void operator()(HDS& hds);
  };

template <class TPOLORG,class HDS,class CVPOS>
  void Build_tdest_polyhedron<TPOLORG,HDS,CVPOS>::operator()(HDS& hds)
  {
    const size_t num_facetas= sf.size_of_facets();
    const size_t num_aristas= sf.size_of_halfedges();
    const size_t num_vertices= sf.size_of_vertices();
    MapPoligonos<TPOLORG> mt= getMapPoligonos(sf);
    // Postcondition: `hds' is a valid polyhedral surface.
    CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);

    B.begin_surface(num_vertices,num_facetas,num_aristas);
    for(vconst_iter i= mt.VerticesBegin();i!=mt.VerticesEnd();i++)
      {
        B.add_vertex(CVPOS()((*i).second));        
      }
    for(cconst_iter j= mt.CarasBegin();j!=mt.CarasEnd();j++)
      {
        B.begin_facet();
        const size_t nv= (*j).GetNumVertices();
        for(size_t i=0;i<nv;i++)
          B.add_vertex_to_facet((*j).Vertice(i+1));
        B.end_facet();
      }
    B.end_surface();
  }

#endif
