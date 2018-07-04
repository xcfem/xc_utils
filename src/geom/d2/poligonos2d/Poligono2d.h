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
//Poligono2d.h

#ifndef POLIGONO2D_H
#define POLIGONO2D_H

#include "xc_utils/src/geom/d2/poligonos2d/SupPoligonal2d.h"

class Trf2d;
class HalfPlane2d;
class Recta2d;
class Segment2d;
class ListaPos2d;


//! @ingroup GEOM
//
//! @brief Polígono en dos dimensiones.
class Poligono2d: public SupPoligonal2d
  {
    CGPoligono_2 cgpol; //Poligono de CGAL.
    template <class inputIterator>
    bool Overlap(inputIterator begin, inputIterator end) const;
  public:

    typedef CGPoligono_2::Vertex_iterator vertex_iterator; 
    typedef CGPoligono_2::Vertex_circulator vertex_circulator; 
    typedef CGPoligono_2::Edge_const_iterator edge_const_iterator; 
    typedef CGPoligono_2::Edge_const_circulator edge_const_circulator; 

    Poligono2d(void);
    Poligono2d(const GeomObj::list_Pos2d &lv);
    explicit Poligono2d(const CGPoligono_2 &);
    explicit Poligono2d(const std::list<Poligono2d> &lp);
    explicit Poligono2d(const Polilinea2d &);
    explicit Poligono2d(const boost::python::list &);
    virtual GeomObj *clon(void) const;
    const CGPoligono_2 &ToCGAL(void) const
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

    Poligono2d GetSwap(void) const
      {
        Poligono2d retval(*this);
        retval.Swap();
        return retval;
      }
    inline bool Horario(void) const
      { return (cgpol.is_clockwise_oriented());}
    inline bool Antihorario(void) const
      { return (cgpol.is_counterclockwise_oriented()); }
    inline void Swap(void)
      { cgpol.reverse_orientation(); }

    Poligono2d Offset(const GEOM_FT &d) const;

    inline GEOM_FT AreaSigno(void) const
      { return cgpol.area(); }
    virtual GEOM_FT getArea(void) const;
    std::vector<Poligono2d> getPoligonosTributarios(void) const;
    std::vector<double> getTributaryAreas(void) const;
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    template <class inputIterator>
    bool In(inputIterator begin, inputIterator end) const;
    bool In(const Polilinea2d &) const;
    bool In(const Poligono2d &) const;
    bool Overlap(const Pos2d &) const;
    bool Overlap(const Recta2d &r) const;
    bool Overlap(const SemiRecta2d &sr) const;
    bool Overlap(const Segment2d &sg) const;
    bool Overlap(const BND2d &) const;
    bool Overlap(const Polilinea2d &) const;
    bool Overlap(const Poligono2d &) const;
    bool Overlap(const std::list<Poligono2d> &) const;
    //! @brief Return the position of the i-th vertex.
    inline Pos2d Vertice(unsigned int i) const
      { return Vertice0(i-1); }
    //! @brief Return the position of the i-th vertex
    //! (0 based: j=0..GetNumVertices()-1).
    inline Pos2d Vertice0(unsigned int j) const
      { return cgpol.vertex(j); }
    GeomObj::list_Pos2d ListaVertices(void) const;

    void Transforma(const Trf2d &trf2d);

    std::deque<GEOM_FT> &GetRecubrimientos(const ListaPos2d &) const;

    Poligono2d getUnion(const Poligono2d &other) const;
    void une(const Poligono2d &);
    void une(const std::list<Poligono2d> &l);
    void clipBy(const Poligono2d &);
    Segment2d Clip(const Recta2d &) const;
    Segment2d Clip(const SemiRecta2d &) const;
    Segment2d Clip(const Segment2d &) const;
    std::list<Poligono2d> Clip(const BND2d &bnd) const;
    std::list<Poligono2d> Clip(const Poligono2d &) const;

    std::list<Poligono2d> getIntersection(const HalfPlane2d &sp) const;

    //std::list<Poligono2d> crea_lista_poligono2d(const std::string &str) const;
  };

inline Poligono2d transforma(const Trf2d &trf2d,const Poligono2d &pol2d)
  { return getTransformado(pol2d,trf2d); }

Poligono2d append_mid_points(const Poligono2d &);

std::list<Poligono2d> intersection(const Poligono2d &p1,const Poligono2d &p2);
std::list<Poligono2d> intersection(const Poligono2d &p,const HalfPlane2d &r);
std::list<Poligono2d> corta(const Poligono2d &p,const Recta2d &r);

Pos2d center_of_mass(const std::list<Poligono2d> &);

//!@brief Return verdadero si todos los objetos de la secuencia
//! están contenidos en el polígono.
template <class inputIterator>
bool Poligono2d::In(inputIterator begin, inputIterator end) const
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
bool Poligono2d::Overlap(inputIterator begin, inputIterator end) const
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

