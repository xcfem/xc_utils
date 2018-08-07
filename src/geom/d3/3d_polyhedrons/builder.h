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
/***************************************************************************
builder.h
----------------------------------------------------------------------------
begin                : june 2003
copyright            : (C) 2003 by Pierre Alliez - INRIA
email                : pierre.alliez@sophia.inria.fr
Enriched incremental builder for CGAL Polyhedral Surfaces.
***************************************************************************/

#ifndef Enriched_polyhedron_incremental_builder_3_H
#define Enriched_polyhedron_incremental_builder_3_H 1

#include <CGAL/basic.h>
// MS Visual C++ 6.0 does not work with the new design.
#if defined( _MSC_VER) && (_MSC_VER <= 1200)
#ifndef CGAL_USE_POLYHEDRON_DESIGN_TWO
#define CGAL_USE_POLYHEDRON_DESIGN_ONE 1
#endif
#endif

#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
#include <CGAL/Polyhedron_old/Polyhedron_incremental_builder_3.h>
#else // CGAL_USE_POLYHEDRON_DESIGN_ONE //
#define CGAL_USE_POLYHEDRON_DESIGN_TWO 1

#include <CGAL/Random_access_adaptor.h>
#include <CGAL/HalfedgeDS_decorator.h>
#include <CGAL/Unique_hash_map.h>
#include <CGAL/IO/Verbose_ostream.h>
#include <vector>
#include <cstddef>

CGAL_BEGIN_NAMESPACE

template < class HalfedgeDS_>
class Enriched_polyhedron_incremental_builder_3 {
public:
    typedef HalfedgeDS_                     HDS; // internal
    typedef HalfedgeDS_                     HalfedgeDS;
    typedef typename HDS::Vertex            Vertex;
    typedef typename HDS::Halfedge          Halfedge;
    typedef typename HDS::Face              Face;
    typedef typename HDS::Vertex_handle     Vertex_handle;
    typedef typename HDS::Halfedge_handle   Halfedge_handle;
    typedef typename HDS::Face_handle       Face_handle;
    typedef typename HDS::Face_handle       Facet_handle;
    typedef typename Vertex::Base           VBase;
    typedef typename Halfedge::Base         HBase;
    typedef typename Vertex::Point          Point_3;
    typedef typename HDS::size_type         size_type;

protected:
    typedef typename HDS::Supports_vertex_halfedge  Supports_vertex_halfedge;
    typedef typename HDS::Supports_removal          Supports_removal;
    typedef typename HDS::Vertex_iterator           Vertex_iterator;
    typedef typename HDS::Halfedge_iterator         Halfedge_iterator;
    typedef Random_access_adaptor<Vertex_iterator>  Random_access_index;

    bool                      m_error;
    bool                      m_verbose;
    HDS&                      hds;
    size_type                 rollback_v;
    size_type                 rollback_f;
    size_type                 rollback_h;
    size_type                 new_vertices;
    size_type                 new_faces;
    size_type                 new_halfedges;
    Face_handle               current_face;
    Random_access_index       index_to_vertex_map;
    std::vector< Halfedge_handle>  vertex_to_edge_map;

    Halfedge_handle           g1;      // first halfedge, 0 denotes none.
    Halfedge_handle           gprime;
    Halfedge_handle           h1;      // current halfedge
    size_type                 w1;      // first vertex.
    size_type                 w2;      // second vertex.
    size_type                 v1;      // current vertex
    bool                      first_vertex;
    bool                      last_vertex;

    CGAL_assertion_code( int check_protocoll;)  // use to check protocoll.
    // states for checking: 0 = created, 1 = constructing, 2 = make face.

    // Implement the vertex_to_edge_map either with an array or
    // the halfedge pointer in the vertices (if supported).
    // ----------------------------------------------------
    void initialize_vertex_to_edge_map( size_type  , bool, Tag_true) {}
    void initialize_vertex_to_edge_map( size_type n, bool mode, Tag_false){
        vertex_to_edge_map = std::vector< Halfedge_handle>();
        vertex_to_edge_map.reserve(n);
        if ( mode) {
            // go through all halfedges and keep a halfedge for each
            // vertex found in a hashmap.
            typedef Unique_hash_map< Vertex_iterator, Halfedge_handle> V_map;
            Halfedge_handle hh;
            V_map v_map( hh, hds.size_of_vertices());
            for ( Halfedge_iterator hi = hds.halfedges_begin();
                  hi != hds.halfedges_end();
                  ++hi) {
                v_map[ hi->vertex()] = hi;
            }
            size_type i = 0;
            for ( Vertex_iterator vi = hds.vertices_begin();
                  vi != hds.vertices_end();
                  ++vi) {
                set_vertex_to_edge_map( i, v_map[ index_to_vertex_map[i]]);
                ++i;
            }
        }
    }
    void initialize_vertex_to_edge_map( size_type n, bool mode) {
        initialize_vertex_to_edge_map(n, mode, Supports_vertex_halfedge());
    }
    void push_back_vertex_to_edge_map( Halfedge_handle  , Tag_true) {}
    void push_back_vertex_to_edge_map( Halfedge_handle h, Tag_false) {
        vertex_to_edge_map.push_back(h);
    }
    void push_back_vertex_to_edge_map( Halfedge_handle h) {
        push_back_vertex_to_edge_map( h, Supports_vertex_halfedge());
    }
    Halfedge_handle get_vertex_to_edge_map( int i, Tag_true) {
        // Use the halfedge pointer within the vertex.
        return index_to_vertex_map[i]->halfedge();
    }
    Halfedge_handle get_vertex_to_edge_map( int i, Tag_false) {
        // Use the self-managed array vertex_to_edge_map.
        return vertex_to_edge_map[i];
    }
    Halfedge_handle get_vertex_to_edge_map( int i) {
        return get_vertex_to_edge_map( i, Supports_vertex_halfedge());
    }
    void set_vertex_to_edge_map( int i, Halfedge_handle h, Tag_true) {
        // Use the halfedge pointer within the vertex.
        index_to_vertex_map[i]->VBase::set_halfedge(h);
    }
    void set_vertex_to_edge_map( int i, Halfedge_handle h, Tag_false) {
        // Use the self-managed array vertex_to_edge_map.
        vertex_to_edge_map[i] = h;
    }
    void set_vertex_to_edge_map( int i, Halfedge_handle h) {
        set_vertex_to_edge_map( i, h, Supports_vertex_halfedge());
    }

// An Incremental Builder for Polyhedral Surfaces
// ----------------------------------------------
// DEFINITION
//
// Enriched_polyhedron_incremental_builder_3<HDS> is an auxiliary class that
// supports the incremental construction of polyhedral surfaces. This is
// for example convinient when constructing polyhedral surfaces from
// files. The incremental construction starts with a list of all point
// coordinates and concludes with a list of all facet polygons. Edges are
// not explicitly specified. They are derived from the incidence
// information provided from the facet polygons. These are given as a
// sequence of vertex indices. The correct protocol of method calls to
// build a polyhedral surface can be stated as regular expression:
//
// `begin_surface (add_vertex | (begin_facet add_vertex_to_facet*
//  end_facet))* end_surface '
//
// PARAMETERS
//
// `HDS' is the halfedge data structure used to represent the
// polyhedral surface that is to be constructed.
//
// CREATION
public:
    bool error() const { return m_error; }

    Enriched_polyhedron_incremental_builder_3( HDS& h, bool verbose = false)
        // stores a reference to the halfedge data structure `h' in the
        // internal state. The previous polyhedral surface in `h'
        // remains unchanged. The incremental builder adds the new
        // polyhedral surface to the old one.
      : m_error( false), m_verbose( verbose), hds(h) {
        CGAL_assertion_code(check_protocoll = 0;)
    }

    ~Enriched_polyhedron_incremental_builder_3() {
        CGAL_assertion( check_protocoll == 0);
    }

// OPERATIONS
    enum { CGAL_RELATIVE = 0, CGAL_ABSOLUTE = 1};


    void begin_surface( std::size_t v, std::size_t f, std::size_t h = 0,
                        int mode = CGAL_RELATIVE);
        // starts the construction. v is the number of new
        // vertices to expect, f the number of new facets, and h the number of
        // new halfedges. If h is unspecified (`== 0') it is estimated using
        // Euler equations (plus 5% for the so far unkown holes and genus
        // of the object). These values are used to reserve space in the
        // polyhedron representation `HDS'. If the representation
        // supports insertion these values do not restrict the class of
        // readable polyhedrons. If the representation does not support
        // insertion the object must fit in the reserved sizes.
        //    If `mode' is set to CGAL_ABSOLUTE the incremental builder uses
        // CGAL_ABSOLUTE indexing and the vertices of the old polyhedral surface
        // can be used in new facets. Otherwise CGAL_RELATIVE indexing is used
        // starting with new indices for the new construction.


    Vertex_handle add_vertex( const Point_3& p) {
        // adds p to the vertex list.
        CGAL_assertion( check_protocoll == 1);
        if ( hds.size_of_vertices() >= hds.capacity_of_vertices()) {
            Verbose_ostream verr( m_verbose);
            verr << " " << std::endl;
            verr << "CGAL::Enriched_polyhedron_incremental_builder_3<HDS>::"
                 << std::endl;
            verr << "add_vertex(): capacity error: more than " << new_vertices
                 << " vertices added." << std::endl;
            m_error = true;
            return Vertex_handle();
        }
        HalfedgeDS_decorator<HDS> decorator(hds);
        Vertex_handle v = decorator.vertices_push_back( Vertex(p));
        index_to_vertex_map.push_back( v);
        decorator.set_vertex_halfedge( v, Halfedge_handle());
        push_back_vertex_to_edge_map( Halfedge_handle());
        ++new_vertices;
        return v;
    }

    // returns handle for the vertex of index i
    Vertex_handle vertex( std::size_t i) {
        if ( i < new_vertices)
            return index_to_vertex_map[i];
        return Vertex_handle();
    }

    Facet_handle begin_facet() {
        // starts a facet.
        if ( m_error)
            return Facet_handle();
        CGAL_assertion( check_protocoll == 1);
        CGAL_assertion_code( check_protocoll = 2;)
        if ( hds.size_of_faces() >= hds.capacity_of_faces()) {
            Verbose_ostream verr( m_verbose);
            verr << " " << std::endl;
            verr << "CGAL::Enriched_polyhedron_incremental_builder_3<HDS>::"
                 << std::endl;
            verr << "begin_facet(): capacity error: more than " << new_vertices
                 << " facets added." << std::endl;
            m_error = true;
            return Facet_handle();
        }
        // initialize all status variables.
        first_vertex = true;  // denotes 'no vertex yet'
        g1 =  Halfedge_handle();  // denotes 'no halfedge yet'
        last_vertex = false;

        HalfedgeDS_decorator<HDS> decorator(hds);
        current_face = decorator.faces_push_back( Face());
        return current_face;
    }

    void add_vertex_to_facet( std::size_t i);
        // adds a vertex with index i to the current facet. The first
        // point added with `add_vertex()' has the index 0.

    Halfedge_handle end_facet() {
        // ends a facet.
        if ( m_error)
            return Halfedge_handle();
        CGAL_assertion( check_protocoll == 2);
        CGAL_assertion( ! first_vertex);
        // cleanup all static status variables
        add_vertex_to_facet( w1);
        if ( m_error)
            return Halfedge_handle();
        last_vertex = true;
        add_vertex_to_facet( w2);
        if ( m_error)
            return Halfedge_handle();
        CGAL_assertion( check_protocoll == 2);
        CGAL_assertion_code( check_protocoll = 1;)
        HalfedgeDS_items_decorator<HDS> decorator;
        Halfedge_handle h = get_vertex_to_edge_map(w1);
        decorator.set_face_halfedge( current_face, h);
        ++new_faces;
        return h;
    }

    template <class InputIterator>
    Halfedge_handle add_facet( InputIterator first, InputIterator beyond) {
        // synonym for begin_facet(), a call to add_facet() for each iterator
        // value type, and end_facet().
        begin_facet();
        for ( ; ! m_error && first != beyond; ++first)
            add_vertex_to_facet( *first);
        if ( m_error)
            return Halfedge_handle();
        return end_facet();
    }

    template <class InputIterator>
    bool test_facet( InputIterator first, InputIterator beyond) {
        // tests if the facet described by the vertex indices in the
        // range [first,beyond) can be inserted without creating a
        // a non-manifold (and therefore invalid) situation.
        // First, create a copy of the indices and close it cyclically
        std::vector< std::size_t> indices( first, beyond);
        if ( indices.size() < 3)
            return false;
        indices.push_back( indices[0]);
        return test_facet_indices( indices);
    }

    bool test_facet_indices( std::vector< std::size_t> indices);

    void end_surface();
        // ends the construction.

    bool check_unconnected_vertices();
        // returns `true' if unconnected vertices are detected. If `verb'
        // is set to `true' debug information about the unconnected
        // vertices is printed.

    bool remove_unconnected_vertices( Tag_true);
    bool remove_unconnected_vertices( Tag_false) {
        return ! check_unconnected_vertices();
    }
    bool remove_unconnected_vertices() {
        // returns `true' if all unconnected vertices could be removed
        // succesfully.
        return remove_unconnected_vertices( Supports_removal());
    }

    void rollback();

protected:
    Halfedge_handle lookup_hole( std::size_t w) {
        CGAL_assertion( w < new_vertices);
        return lookup_hole( get_vertex_to_edge_map( w));
    }

    size_type find_vertex( Vertex_handle v) {
        // Returns 0 if v == nullptr.
        if ( v == Vertex_handle() )
            return 0;
        size_type n = 0;
        typename HDS::Vertex_iterator it = hds.vertices_begin();
        while ( it != v) {
            CGAL_assertion( it != hds.vertices_end());
            ++n;
            ++it;
        }
        n = n - rollback_v;
        return n;
    }

    size_type find_facet( Face_handle f) {
        // Returns 0 if f == nullptr.
        if ( f == Face_handle())
            return 0;
        size_type n = 0;
        typename HDS::Face_iterator it = hds.faces_begin();
        while ( it != f) {
            CGAL_assertion( it != hds.faces_end());
            ++n;
            ++it;
        }
        n = n - rollback_f;
        return n;
    }

    Halfedge_handle lookup_halfedge( size_type w, size_type v) {
        // Pre: 0 <= w,v < new_vertices
        // Case a: It exists an halfedge g from w to v:
        //     g must be a border halfedge and the facet of g->opposite()
        //     must be set and different from the current facet.
        //     Set the facet of g to the current facet. Return the
        //     halfedge pointing to g.
        // Case b: It exists no halfedge from w to v:
        //     Create a new pair of halfedges g and g->opposite().
        //     Set the facet of g to the current facet and g->opposite()
        //     to a border halfedge. Assign the vertex references.
        //     Set g->opposite()->next() to g. Return g->opposite().
        typedef typename HDS::Supports_halfedge_vertex
            Supports_halfedge_vertex;
        Assert_compile_time_tag( Supports_halfedge_vertex(), Tag_true());
        CGAL_assertion( w < new_vertices);
        CGAL_assertion( v < new_vertices);
        CGAL_assertion( ! last_vertex);
        HalfedgeDS_items_decorator<HDS> decorator;
        Halfedge_handle e = get_vertex_to_edge_map( w);
        if ( e != Halfedge_handle()) {
            CGAL_assertion( e->vertex() == index_to_vertex_map[w]);
            // check that the facet has no self intersections
            if ( current_face != Face_handle()
                 && current_face == decorator.get_face(e)) {
                Verbose_ostream verr( m_verbose);
                verr << " " << std::endl;
                verr << "CGAL::Enriched_polyhedron_incremental_builder_3<HDS>::"
                     << std::endl;
                verr << "lookup_halfedge(): input error: facet "
                     << new_faces << " has a self intersection at vertex "
                     << w << "." << std::endl;
                m_error = true;
                return Halfedge_handle();
            }
            Halfedge_handle start_edge( e);
            do {
                if ( e->next()->vertex() == index_to_vertex_map[v]) {
                    if ( ! e->next()->is_border()) {
                        Verbose_ostream verr( m_verbose);
                        verr << " " << std::endl;
                        verr << "CGAL::Enriched_polyhedron_incremental_builder_3"
                                "<HDS>::" << std::endl;
                        verr << "lookup_halfedge(): input error: facet "
                             << new_faces << " shares a halfedge from "
                                "vertex " <<  w << " to vertex " << v
                             << " with";
                        if (  m_verbose && current_face != Face_handle())
                            verr << " facet "
                                 << find_facet( decorator.get_face(e->next()))
                                 << '.' << std::endl;
                        else
                            verr << " another facet." << std::endl;
                        m_error = true;
                        return Halfedge_handle();
                    }
                    CGAL_assertion( ! e->next()->opposite()->is_border());
                    if ( current_face != Face_handle() && current_face ==
                         decorator.get_face( e->next()->opposite())) {
                        Verbose_ostream verr( m_verbose);
                        verr << " " << std::endl;
                        verr << "CGAL::Enriched_polyhedron_incremental_builder_3"
                                "<HDS>::" << std::endl;
                        verr << "lookup_halfedge(): input error: facet "
                             << new_faces << " has a self intersection "
                                "at the halfedge from vertex " << w
                             << " to vertex " << v << "." << std::endl;
                        m_error = true;
                        return Halfedge_handle();
                    }
                    decorator.set_face( e->next(), current_face);
                    return e;
                }
                e = e->next()->opposite();
            } while ( e != start_edge);
        }
        // create a new halfedge
        if ( hds.size_of_halfedges() >= hds.capacity_of_halfedges()) {
            Verbose_ostream verr( m_verbose);
            verr << " " << std::endl;
            verr << "CGAL::Enriched_polyhedron_incremental_builder_3<HDS>::"
                 << std::endl;
            verr << "lookup_halfedge(): capacity error: more than "
                 << new_halfedges << " halfedges added while creating facet"
                 << new_faces << '.' << std::endl;
            m_error = true;
            return Halfedge_handle();
        }
        e = hds.edges_push_back( Halfedge(), Halfedge());
        new_halfedges++;
        new_halfedges++;
        decorator.set_face( e, current_face);
        e->HBase::set_vertex( index_to_vertex_map[v]);
        e->HBase::set_next( Halfedge_handle());
        decorator.set_prev( e, e->opposite());
        e = e->opposite();
        e->HBase::set_vertex( index_to_vertex_map[w]);
        e->HBase::set_next( e->opposite());
        return e;
    }

    Halfedge_handle lookup_hole( Halfedge_handle e) {
        // Halfedge e points to a vertex w. Walk around w to find a hole
        // in the facet structure. Report an error if none exist. Return
        // the halfedge at this hole that points to the vertex w.
        CGAL_assertion( e != Halfedge_handle());
        HalfedgeDS_items_decorator<HDS> decorator;
        Halfedge_handle start_edge( e);
        do {
            if ( e->next()->is_border()) {
                return e;
            }
            e = e->next()->opposite();
        } while ( e != start_edge);

        Verbose_ostream verr( m_verbose);
        verr << " " << std::endl;
        verr << "CGAL::Enriched_polyhedron_incremental_builder_3<HDS>::" << std::endl;
        verr << "lookup_hole(): input error: at vertex "
             << find_vertex( e->vertex())
             << " a closed surface already exists and facet "
             << new_faces << " is nonetheless adjacent." << std::endl;
        if (  m_verbose && current_face != Face_handle()) {
            verr << "             The closed cycle of facets is:";
            do {
                if ( ! e->is_border())
                    verr << " " << find_facet( decorator.get_face(e));
                e = e->next()->opposite();
            } while ( e != start_edge);
            verr << '.' << std::endl;
        }
        m_error = true;
        return Halfedge_handle();
    }
};

template < class HDS>
void
Enriched_polyhedron_incremental_builder_3<HDS>::
rollback() {
    CGAL_assertion( rollback_v <= hds.size_of_vertices());
    CGAL_assertion( rollback_h <= hds.size_of_halfedges());
    CGAL_assertion( rollback_f <= hds.size_of_faces());
    if ( rollback_v == 0 && rollback_h == 0 && rollback_f == 0) {
        hds.clear();
    } else {
        while ( rollback_v != hds.size_of_vertices())
            hds.vertices_pop_back();
        CGAL_assertion((( hds.size_of_halfedges() - rollback_h) & 1) == 0);
        while ( rollback_h != hds.size_of_halfedges())
            hds.edges_pop_back();
        while ( rollback_f != hds.size_of_faces())
            hds.faces_pop_back();
    }
    m_error = false;
    CGAL_assertion_code( check_protocoll = 0;)
}

template < class HDS>  CGAL_MEDIUM_INLINE
void
Enriched_polyhedron_incremental_builder_3<HDS>::
begin_surface( std::size_t v, std::size_t f, std::size_t h, int mode) {
    CGAL_assertion( check_protocoll == 0);
    CGAL_assertion_code( check_protocoll = 1;)
    CGAL_assertion( ! m_error);
    if ( mode == CGAL_RELATIVE) {
        new_vertices  = 0;
        new_faces     = 0;
        new_halfedges = 0;
        rollback_v    = hds.size_of_vertices();
        rollback_f    = hds.size_of_faces();
        rollback_h    = hds.size_of_halfedges();
    } else {
        new_vertices  = hds.size_of_vertices();
        new_faces     = hds.size_of_faces();
        new_halfedges = hds.size_of_halfedges();
        rollback_v    = 0;
        rollback_f    = 0;
        rollback_h    = 0;
    }
    if ( h == 0) {
        // Use the Eulerian equation for connected planar graphs. We do
        // not know the number of facets that are holes and we do not
        // know the genus of the surface. So we add 12 and a factor of
        // 5 percent.
        h = int((v + f - 2 + 12) * 2.1);
    }
    hds.reserve( hds.size_of_vertices()  + v,
                 hds.size_of_halfedges() + h,
                 hds.size_of_faces()     + f);
    if ( mode == CGAL_RELATIVE) {
        index_to_vertex_map = Random_access_index( hds.vertices_end());
        index_to_vertex_map.reserve(v);
        initialize_vertex_to_edge_map( v, false);
    } else {
        index_to_vertex_map = Random_access_index( hds.vertices_begin(),
                                                   hds.vertices_end());
        index_to_vertex_map.reserve( hds.size_of_vertices() + v);
        initialize_vertex_to_edge_map( hds.size_of_vertices() + v, true);
    }
}

template < class HDS>
void
Enriched_polyhedron_incremental_builder_3<HDS>::
add_vertex_to_facet( std::size_t v2) {
    if ( m_error)
        return;
    CGAL_assertion( check_protocoll == 2);
    if ( v2 >= new_vertices) {
        Verbose_ostream verr( m_verbose);
        verr << " " << std::endl;
        verr << "CGAL::Enriched_polyhedron_incremental_builder_3<HDS>::"
             << std::endl;
        verr << "add_vertex_to_facet(): vertex index " << v2
             << " is out-of-range [0," << new_vertices-1 << "]."
             << std::endl;
        m_error = true;
        return;
    }
    HalfedgeDS_items_decorator<HDS> decorator;

    if ( first_vertex) {
        CGAL_assertion( ! last_vertex);
        w1 = v2;
        first_vertex = false;
        return;
    }
    if ( g1 == Halfedge_handle()) {
        CGAL_assertion( ! last_vertex);
        gprime  = lookup_halfedge( w1, v2);
        if ( m_error)
            return;
        h1 = g1 = gprime->next();
        v1 = w2 = v2;
        return;
    }
    // g1, h1, v1, w1, w2 are set. Insert halfedge.
    // Lookup v1-->v2
    Halfedge_handle hprime;
    if ( last_vertex)
        hprime = gprime;
    else {
        hprime = lookup_halfedge( v1, v2);
        if ( m_error)
            return;
    }
    Halfedge_handle h2 = hprime->next();
    CGAL_assertion( ! last_vertex || h2 == g1);
    Halfedge_handle prev = h1->next();
    h1->HBase::set_next( h2);
    decorator.set_prev( h2, h1);

    if ( get_vertex_to_edge_map( v1) == Halfedge_handle()) {  // case 1:
        h2->opposite()->HBase::set_next( h1->opposite());
        decorator.set_prev( h1->opposite(), h2->opposite());
    } else {                                                  // case 2:
        bool b1 = h1->opposite()->is_border();
        bool b2 = h2->opposite()->is_border();
        if ( b1 && b2) {
            Halfedge_handle hole = lookup_hole( v1);
            if ( m_error)
                return;
            CGAL_assertion( hole != Halfedge_handle());
            h2->opposite()->HBase::set_next( hole->next());
            decorator.set_prev( hole->next(), h2->opposite());
            hole->HBase::set_next( h1->opposite());
            decorator.set_prev( h1->opposite(), hole);
        } else if ( b2) {                                     // case 2.b:
            CGAL_assertion( prev->is_border());
            h2->opposite()->HBase::set_next( prev);
            decorator.set_prev( prev, h2->opposite());
        } else if ( b1) {                                     // case 2.c:
            CGAL_assertion( hprime->is_border());
            hprime->HBase::set_next( h1->opposite());
            decorator.set_prev( h1->opposite(), hprime);
        } else if ( h2->opposite()->next() == h1->opposite()) {// case 2.d:
            // f1 == f2
            CGAL_assertion( decorator.get_face( h1->opposite()) ==
                       decorator.get_face( h2->opposite()));
        } else {                                              // case 2.e:
            if ( prev == h2) {                                // case _i:
                // nothing to be done, hole is closed.
            } else {                                          // case _ii:
                CGAL_assertion( prev->is_border());
                CGAL_assertion( hprime->is_border());
                hprime->HBase::set_next( prev);
                decorator.set_prev( prev, hprime);
                // Check whether the halfedges around v1 are connected.
                // It is sufficient to check it for h1 to prev.
                // Assert loop termination:
                CGAL_assertion_code( std::size_t k = 0;)
                // Look for a hole in the facet complex starting at h1.
                Halfedge_handle hole;
                Halfedge_handle e = h1;
                do {
                    if ( e->is_border())
                        hole = e;
                    e = e->next()->opposite();
                    CGAL_assertion( k++ < hds.size_of_halfedges());
                } while ( e->next() != prev && e != h1);
                if ( e == h1) {
                    // disconnected facet complexes
                    if ( hole != Halfedge_handle()) {
                        // The complex can be connected with
                        // the hole at hprime.
                        hprime->HBase::set_next( hole->next());
                        decorator.set_prev( hole->next(), hprime);
                        hole->HBase::set_next( prev);
                        decorator.set_prev( prev, hole);
                    } else {
                        Verbose_ostream verr( m_verbose);
                        verr << " " << std::endl;
                        verr << "CGAL::Enriched_polyhedron_incremental_builder_3<"
                                "HDS>::" << std::endl;
                        verr << "add_vertex_to_facet(): input error: "
                                "disconnected facet complexes at vertex "
                             << v1 << ":" << std::endl;

                        if ( m_verbose && current_face != Face_handle()) {
                            verr << "           involved facets are:";
                            do {
                                if ( ! e->is_border())
                                    verr << " " << find_facet(
                                                decorator.get_face(e));
                                e = e->next()->opposite();
                            } while ( e != h1);
                            verr << " (closed cycle) and";
                            e = hprime;
                            do {
                                if ( ! e->is_border())
                                    verr << " " << find_facet(
                                                decorator.get_face(e));
                            } while ( e != hprime);
                            verr << "." << std::endl;
                        }
                        m_error = true;
                        return;
                    }
                }
            }
        }
    }
    if ( h1->vertex() == index_to_vertex_map[v1])
        set_vertex_to_edge_map( v1, h1);
    CGAL_assertion( h1->vertex() == index_to_vertex_map[v1]);
    h1 = h2;
    v1 = v2;
}

template < class HDS>
bool
Enriched_polyhedron_incremental_builder_3<HDS>::
test_facet_indices( std::vector< std::size_t> indices) {
    typedef typename HDS::Supports_halfedge_vertex Supports_halfedge_vertex;
    Assert_compile_time_tag( Supports_halfedge_vertex(), Tag_true());
    // tests if the facet described by the vertex indices can be inserted
    // without creating a a non-manifold (and therefore invalid) situation.
    // indices are cyclically closed once.
    std::size_t n = indices.size() - 1;
    // Test if a vertex is not twice in the indices
    for ( std::size_t i = 0; i < n; ++i) {
        CGAL_precondition( indices[i] < new_vertices);
        // check if vertex indices[i] is already in the sequence [0..i-1]
        for ( std::size_t k = 0; k+1 < i; ++k) {
            if ( indices[k] == indices[i])
                return false;
        }
    }
    // Test non-manifold edges
    for ( std::size_t i = 0; i < n; ++i) {
        // edge goes from vertex indices[i] to indices[i+1]
        // we know already that the edge is only once in the sequence
        // (otherwise the end-vertices would be twice in the sequence too)
        // check if edge is already in the HDS and is not border edge
        Halfedge_handle v = get_vertex_to_edge_map(indices[i]);
        Vertex_handle   w = index_to_vertex_map[indices[i+1]];
        if ( v != Halfedge_handle()
             && get_vertex_to_edge_map(indices[i+1]) != Halfedge_handle()) {
            // cycle through halfedge-loop and find edge to indices[i+1]
            Halfedge_handle vstart = v;
            do {
                v = v->next()->opposite();
            } while ( v->next()->vertex() != w && v != vstart);
            if ( v->next()->vertex() == w && ! v->next()->is_border())
                return false;
        }
    }
    // test non-manifold vertices
    for ( std::size_t i = 0; i < n; ++i) {
        // since we don't allow duplicates in indices[..] and we
        // tested for non-manifold edges already, we just need to check
        // if the vertex indices[i] is not a closed manifold yet.
        Halfedge_handle v = get_vertex_to_edge_map(indices[i]);
        if ( v != Halfedge_handle()) {
            Halfedge_handle vstart = v;
            do {
                v = v->next()->opposite();
            } while ( ! v->is_border() && v != vstart);
            if ( ! v->is_border())
                return false;
        }
    }
    return true;
}


template < class HDS>  CGAL_MEDIUM_INLINE
void
Enriched_polyhedron_incremental_builder_3<HDS>::
end_surface() {
    if ( m_error)
        return;
    CGAL_assertion( check_protocoll == 1);
    CGAL_assertion_code( check_protocoll = 0;)
}

template < class HDS>
bool
Enriched_polyhedron_incremental_builder_3<HDS>::
check_unconnected_vertices() {
    if ( m_error)
        return false;
    bool unconnected = false;
    Verbose_ostream verr( m_verbose);
    for ( std::size_t i = 0; i < new_vertices; i++) {
        if ( get_vertex_to_edge_map( i) == Halfedge_handle()) {
            verr << "CGAL::Enriched_polyhedron_incremental_builder_3<HDS>::\n"
                 << "check_unconnected_vertices( verb = true): "
                 << "vertex " << i << " is unconnected." << std::endl;
            unconnected = true;
        }
    }
    return unconnected;
}

template < class HDS>
bool
Enriched_polyhedron_incremental_builder_3<HDS>::
remove_unconnected_vertices( Tag_true) {
    if ( m_error)
        return true;
    for( std::size_t i = 0; i < new_vertices; i++) {
        if( get_vertex_to_edge_map( i) == Halfedge_handle()) {
            hds.vertices_erase( index_to_vertex_map[i]);
        }
    }
    return true;
}

CGAL_END_NAMESPACE

#endif // CGAL_USE_POLYHEDRON_DESIGN_ONE //
#endif // CGAL_Enriched_polyhedron_incremental_builder_3_H //
// EOF //