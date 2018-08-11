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
//VERTEXMAP.h

#ifndef VERTEXMAP_H
#define VERTEXMAP_H

#include <vector>
#include "xc_basic/src/stl/TripletMap.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "Poliedro3d.h"

//Convenience classes to generate polyhedrons from
//half-space intersections.

class Pos3dList;


//! @ingroup GEOM
//
//! @brief Vértices de la arista de un poliedro.
class VerticesArista
  {
    size_t v0;
    size_t v1;
  public:
    VerticesArista(const size_t &i,const size_t &j);
    void Swap(void);
    const size_t &getVI(void) const
      { return v0; }
    const size_t &getVJ(void) const
      { return v1; }
    bool comparteVertices(const VerticesArista &otra) const;
    friend bool operator==(const VerticesArista &,const VerticesArista &);
  };

bool operator==(const VerticesArista &,const VerticesArista &);

//! @ingroup GEOM
//
//! @brief Vértices de la cara de un poliedro.
class VerticesCara: public std::list<size_t>
  {
    bool visitada;
  public:
    typedef std::list<size_t> base;
    typedef base::iterator iterator;
    typedef base::const_iterator const_iterator;
    VerticesCara(void);
    void setVisitada(const bool &);
    const bool &yaVisitada(void) const;
    void Swap(void);
    Pos3dList getPosVertices(const std::vector<Pos3d> &) const;
    Pos3d getCentroide(const std::vector<Pos3d> &) const;
    std::list<VerticesArista> getEdges(void) const;
    bool tieneArista(const VerticesArista &) const;
    bool tieneAristaOrientada(const VerticesArista &) const;
    std::deque<VerticesCara> compartenArista(const std::deque<VerticesCara> &) const;
    void Print(std::ostream &os) const;
  };

std::ostream &operator<<(std::ostream &, const VerticesCara &);

//! @ingroup GEOM
//
//! @brief Mapa de vértices de un poliedro.
class VertexMap
  {
    std::vector<Pos3d> vertices;
    std::deque<VerticesCara > caras;
  public:
    VertexMap(const TripletMap<Pos3d> &);
    const std::vector<Pos3d> &getVertices(void) const;
    Pos3d getCentroide(void) const;
    size_t getNumVertices(void) const;
    size_t getNumCaras(void) const;
    const std::deque<VerticesCara> &getCaras(void) const;
    const VerticesCara &getCara(const size_t &) const;
    std::deque<VerticesCara *> tienenArista(const VerticesArista &);
    void makeConsistent(void);
    void Print(std::ostream &os) const;
  };

std::ostream &operator<<(std::ostream &, const VertexMap &);

// Crea un poliedro a partir de un mapa de vértices.
class BuildFromVertexMap: public CGAL::Modifier_base<Poliedro3d::HalfedgeDS>
  {
    const VertexMap vertex_map;
  public:
    BuildFromVertexMap(const TripletMap<Pos3d> &);
    void operator()(Poliedro3d::HalfedgeDS &);
  };
#endif
