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
//Polygon2d.h

#ifndef POLYGON2D_H
#define POLYGON2D_H

#include "xc_utils/src/geom/d2/2d_polygons/PolygonalSurface2d.h"

class Trf2d;
class HalfPlane2d;
class Line2d;
class Segment2d;
class Pos2dList;


//! @ingroup GEOM
//
//! @brief Polígono en dos dimensiones.
class Polygon2d: public PolygonalSurface2d
  {
    CGPolygon_2 cgpol; //CGAL polygon.
    template <class inputIterator>
    bool Overlap(inputIterator begin, inputIterator end) const;
  public:

    typedef CGPolygon_2::Vertex_iterator vertex_iterator; 
    typedef CGPolygon_2::Vertex_circulator vertex_circulator; 
    typedef CGPolygon_2::Edge_const_iterator edge_const_iterator; 
    typedef CGPolygon_2::Edge_const_circulator edge_const_circulator; 

    Polygon2d(void);
    Polygon2d(const GeomObj::list_Pos2d &lv);
    explicit Polygon2d(const CGPolygon_2 &);
    explicit Polygon2d(const std::list<Polygon2d> &lp);
    explicit Polygon2d(const Polyline2d &);
    explicit Polygon2d(const boost::python::list &);
    virtual GeomObj *clon(void) const;
    const CGPolygon_2 &ToCGAL(void) const
      { return cgpol; }

    inline virtual unsigned int GetNumVertices(void) const
      { return cgpol.size(); }
    inline void push_back(const Pos2d &p)
      { cgpol.push_back(p.ToCGAL()); }
    //! @brief Insert vertex q before the vertex pointed by i.
    inline vertex_iterator insert(vertex_iterator i,const Pos2d &q)
      { return cgpol.insert(i,q.ToCGAL()); }
    //! @brief Insert the vertices between [first,last) before
    //! the vertex pointed by i.
    template <class InputIterator>
    inline void insert(vertex_iterator i,
                       InputIterator first,
                       InputIterator last)
      { cgpol.insert(i,first,last); }
    //! @brief Modifies the position of the i-th vertex
    //! making it equal to the argument.
    void set(vertex_iterator i,const Pos2d &p)
      { cgpol.set(i,p.ToCGAL()); }
    void erase(vertex_iterator i)
    //Elimina el vértice al que se refiere i.
      { cgpol.erase(i); }
    //! @brief Elimina el vértice los vértices del rango [first,last).
    void erase(vertex_iterator first,vertex_iterator last)
      { cgpol.erase(first,last); }
    //! @brief Elimina el vértice los vértices del rango [first,last).
    void erase(void)
      { cgpol.erase(cgpol.vertices_begin(),cgpol.vertices_end()); }

    vertex_iterator vertices_begin(void) const
    //Returns a constant iterator that allows to traverse 
    //the vertices of the polygon p.
      { return cgpol.vertices_begin(); }
    vertex_iterator vertices_end(void) const
    //Returns the corresponding past-the-end iterator.
      { return cgpol.vertices_end(); }
    vertex_circulator vertices_circulator(void)
    //Returns a mutable circulator that allows to 
    //traverse the vertices of the polygon p.
      { return cgpol.vertices_circulator(); }
    edge_const_iterator edges_begin(void) const
    //Returns a non-mutable iterator that allows to 
    //traverse the edges of the polygon p.
      { return cgpol.edges_begin(); }
    edge_const_iterator edges_end(void)
    //Returns the corresponding past-the-end iterator.
      { return cgpol.edges_end(); }
    edge_const_circulator edges_circulator(void) const
    //Returns a non-mutable circulator that allows to 
    //traverse the edges of the polygon p.
      { return cgpol.edges_circulator(); }

    Polygon2d GetSwap(void) const
      {
        Polygon2d retval(*this);
        retval.Swap();
        return retval;
      }
    inline bool Horario(void) const
      { return (cgpol.is_clockwise_oriented());}
    inline bool Antihorario(void) const
      { return (cgpol.is_counterclockwise_oriented()); }
    inline void Swap(void)
      { cgpol.reverse_orientation(); }

    Polygon2d Offset(const GEOM_FT &d) const;

    inline GEOM_FT AreaSigno(void) const
      { return cgpol.area(); }
    virtual GEOM_FT getArea(void) const;
    std::vector<Polygon2d> getTributaryPolygons(void) const;
    std::vector<double> getTributaryAreas(void) const;
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    template <class inputIterator>
    bool In(inputIterator begin, inputIterator end) const;
    bool In(const Polyline2d &) const;
    bool In(const Polygon2d &) const;
    bool Overlap(const Pos2d &) const;
    bool Overlap(const Line2d &r) const;
    bool Overlap(const Ray2d &sr) const;
    bool Overlap(const Segment2d &sg) const;
    bool Overlap(const BND2d &) const;
    bool Overlap(const Polyline2d &) const;
    bool Overlap(const Polygon2d &) const;
    bool Overlap(const std::list<Polygon2d> &) const;
    //! @brief Return the position of the i-th vertex.
    inline Pos2d Vertice(unsigned int i) const
      { return Vertice0(i-1); }
    //! @brief Return the position of the i-th vertex
    //! (0 based: j=0..GetNumVertices()-1).
    inline Pos2d Vertice0(unsigned int j) const
      { return cgpol.vertex(j); }
    GeomObj::list_Pos2d getVertexList(void) const;

    void Transforma(const Trf2d &trf2d);

    std::deque<GEOM_FT> &GetRecubrimientos(const Pos2dList &) const;

    Polygon2d getUnion(const Polygon2d &other) const;
    void une(const Polygon2d &);
    void une(const std::list<Polygon2d> &l);
    void clipBy(const Polygon2d &);
    Segment2d Clip(const Line2d &) const;
    Segment2d Clip(const Ray2d &) const;
    Segment2d Clip(const Segment2d &) const;
    std::list<Polygon2d> Clip(const BND2d &bnd) const;
    std::list<Polygon2d> Clip(const Polygon2d &) const;

    std::list<Polygon2d> getIntersection(const HalfPlane2d &sp) const;

    //std::list<Polygon2d> create_polygon2d_list(const std::string &str) const;
  };

inline Polygon2d transforma(const Trf2d &trf2d,const Polygon2d &pol2d)
  { return getTransformado(pol2d,trf2d); }

Polygon2d append_mid_points(const Polygon2d &);

std::list<Polygon2d> intersection(const Polygon2d &p1,const Polygon2d &p2);
std::list<Polygon2d> intersection(const Polygon2d &p,const HalfPlane2d &r);
std::list<Polygon2d> corta(const Polygon2d &p,const Line2d &r);

Pos2d center_of_mass(const std::list<Polygon2d> &);

//!@brief Return verdadero si todos los objetos de la secuencia
//! están contenidos en el polígono.
template <class inputIterator>
bool Polygon2d::In(inputIterator begin, inputIterator end) const
  {
    bool retval= true;
    for(inputIterator i= begin;i!=end;i++)
      if(!In(*i))
        {
          retval= false;
          break;
        }
    return retval;
  }

//!@brief Return verdadero si alguno de los objetos de la secuencia
//! está contenido total o parcialmente en el polígono.
template <class inputIterator>
bool Polygon2d::Overlap(inputIterator begin, inputIterator end) const
  {
    bool retval= false;
    for(inputIterator i= begin;i!=end;i++)
      if(Overlap(*i))
        {
          retval= true;
          break;
        }
    return retval;
  }

#endif

