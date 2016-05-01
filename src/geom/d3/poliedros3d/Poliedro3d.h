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
//POLIEDRO3D.h

#ifndef POLIEDRO3D_H
#define POLIEDRO3D_H

#include <iostream>
#include "PolyhedronBase.h"
#include "../../tipos_cgal.h"
#include "MapPoligonos.h"
#include "enriched_polyhedron.h"

class Plano3d;
class SemiEspacio3d;
class MallaTriang3d;
class Poligono3d;


//! @ingroup GEOM
//
//! @brief Clase base para los poliedros.
class Poliedro3d: public PolyhedronBase
  {
  protected:
    CGPoliedro_3 cgpoliedro;

    Poliedro3d(const CGPoliedro_3 &cgp) 
      : PolyhedronBase(), cgpoliedro(cgp) {}
    void make_tetrahedron(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3);
    void make_tetrahedron(const SemiEspacio3d &, const SemiEspacio3d &,const SemiEspacio3d &, const SemiEspacio3d &);
    void make_polyhedron(const std::deque<SemiEspacio3d> &);
    //void semiespacios(const std::string &,const bool &clear= true);

  public:
    typedef CGPoliedro_3::Vertex Vertex;
    typedef CGPoliedro_3::Facet Facet;

    typedef CGPoliedro_3::Point_iterator Point_iterator;
    typedef CGPoliedro_3::Point_const_iterator Point_const_iterator;
    typedef CGPoliedro_3::Vertex_iterator Vertex_iterator;
    typedef CGPoliedro_3::Vertex_const_iterator Vertex_const_iterator;
    typedef CGPoliedro_3::Facet_iterator Facet_iterator;
    typedef CGPoliedro_3::Facet_const_iterator Facet_const_iterator;
    typedef CGPoliedro_3::Edge_iterator Edge_iterator;
    typedef CGPoliedro_3::Halfedge_iterator Halfedge_iterator;
    typedef CGPoliedro_3::Halfedge_around_facet_circulator Halfedge_around_facet_circulator;
    typedef CGPoliedro_3::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator;
    typedef CGPoliedro_3::Vertex_handle Vertex_handle;
    typedef CGPoliedro_3::Facet_handle Facet_handle;
    typedef CGPoliedro_3::Halfedge_handle Halfedge_handle;
    typedef CGPoliedro_3::HalfedgeDS HalfedgeDS;

    Poliedro3d(void);
    Poliedro3d(const Pos3d &, const Pos3d &,const Pos3d &, const Pos3d &);
    Poliedro3d(const SemiEspacio3d &, const SemiEspacio3d &,const SemiEspacio3d &, const SemiEspacio3d &);
    Poliedro3d(const std::deque<SemiEspacio3d> &);
    Poliedro3d(const Poliedro3d &);
    Poliedro3d(const EPoliedro &e);
    Poliedro3d &operator=(const Poliedro3d &otro);
    virtual GeomObj *clon(void) const;

    Point_iterator points_begin(void)
      { return cgpoliedro.points_begin(); }
    Point_iterator points_end(void)
      { return cgpoliedro.points_end(); }
    Vertex_iterator vertices_begin(void)
      { return cgpoliedro.vertices_begin(); }
    Vertex_iterator vertices_end(void)
      { return cgpoliedro.vertices_end(); }
    Facet_iterator facets_begin(void)
      { return cgpoliedro.facets_begin(); }
    Facet_iterator facets_end(void)
      { return cgpoliedro.facets_end(); }
    Point_const_iterator points_begin(void) const
      { return cgpoliedro.points_begin(); }
    Point_const_iterator points_end(void) const
      { return cgpoliedro.points_end(); }
    Vertex_const_iterator vertices_begin(void) const
      { return cgpoliedro.vertices_begin(); }
    Vertex_const_iterator vertices_end(void) const
      { return cgpoliedro.vertices_end(); }
    Facet_const_iterator facets_begin(void) const
      { return cgpoliedro.facets_begin(); }
    Facet_const_iterator facets_end(void) const
      { return cgpoliedro.facets_end(); }

    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    size_t GetNumVertices(void) const
      { return cgpoliedro.size_of_vertices(); }
    size_t GetNumAristas(void) const
      { return cgpoliedro.size_of_halfedges(); }
    size_t GetNumCaras(void) const
      { return cgpoliedro.size_of_facets(); }

    void clear(void)
      { cgpoliedro.clear(); }

    GeomObj::list_Pos3d GetVerticesCara(const Facet_const_iterator &f) const;
    Plano3d GetPlanoCara(const Facet_const_iterator &fi) const;
    Poligono3d GetCara(const Facet_const_iterator &f) const;
    std::deque<Poligono3d> GetCaras(void) const;

    GeomObj::list_Pos3d getVertices(void) const;

    virtual GEOM_FT Area(void) const;

    bool TocaCuadrante(const int &) const;

    MapPoligonos<CGPoliedro_3> GetMapPoligonos(void) const
      { return getMapPoligonos(cgpoliedro); }
    EPoliedro GetEnriquecido(void) const;
    MallaTriang3d Triangula(void) const;

    GEOM_FT PseudoDist(const Pos3d &p) const;
    inline virtual GEOM_FT dist(const Pos3d &p) const
      //Puesto que es un sólido consideramos que
      //tienen sentido las distancias negativas.
      { return PseudoDist(p); }

    friend Poliedro3d Union(const Poliedro3d &a,const Poliedro3d &b);
    friend Poliedro3d Interseccion(const Poliedro3d &a,const Poliedro3d &b);
    friend Poliedro3d Diferencia(const Poliedro3d &a,const Poliedro3d &b);
    friend Poliedro3d subdivide_quad_triangle(const Poliedro3d &pol,bool smooth_boundary);
    template <class InputIterator>
    friend Poliedro3d get_convex_hull(InputIterator first,InputIterator last);

    void Print(std::ostream &os) const;
    void Print(CGview_stream &v) const;
    void ReadOFF(std::istream &is);
  };

CGview_stream &operator<<(CGview_stream &v,const Poliedro3d &p);

inline MapPoligonos<CGPoliedro_3> getMapPoligonos(const Poliedro3d &p)
  { return p.GetMapPoligonos(); }
inline EPoliedro enriquece(const Poliedro3d &p)
  { return p.GetEnriquecido(); }

Poliedro3d subdivide_quad_triangle(const Poliedro3d &pol,bool smooth_boundary= false);

#endif
