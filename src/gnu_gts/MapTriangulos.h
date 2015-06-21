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
//MapTriangulos.h

#ifndef MAP_TRIANGULOS_H
#define MAP_TRIANGULOS_H


#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <unistd.h>
#include "gts.h"
#include "xc_utils/src/gnu_gts/GTSVertex.h"
#include "xc_utils/src/gnu_gts/GTSFace.h"
#include "xc_utils/src/gnu_gts/GTSSurface.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include <iostream>
#include <map>

Pos3d Vertex2Pos3d(const GtsVertex &v);


class MapVertices: protected std::map<size_t,Pos3d>
  {

    static bool chequea_vertice(GtsVertex *v);

    friend class MapTriangulos;

  public:
    typedef std::map<size_t,Pos3d> map_p3d;
    typedef map_p3d::iterator iterator;
    typedef map_p3d::const_iterator const_iterator;

    inline const_iterator begin(void) const
      { return map_p3d::begin(); }
    inline const_iterator end(void) const
      { return map_p3d::end(); }
    inline iterator begin(void)
      { return map_p3d::begin(); }
    inline iterator end(void)
      { return map_p3d::end(); }
    void Inserta(GtsVertex *v);
    void Inserta(const size_t &i,const Pos3d &p);
    void Print(std::ostream &os) const;
    void Borra(void);
  };

std::ostream &operator<<(std::ostream &os, const MapVertices &mv);

class IndVerticesTriangulo
//Almacena tres indices que resultan de convertir
//los punteros a los vértices en enteros
  {
    size_t v1,v2,v3;

    bool chequea_edges(GtsTriangle *t);

  public:
    IndVerticesTriangulo(GtsTriangle *t);
    inline const size_t &V1(void) const
      { return v1; }
    inline const size_t &V2(void) const
      { return v2; }
    inline const size_t &V3(void) const
      { return v3; }
    inline size_t &V1(void)
      { return v1; }
    inline size_t &V2(void)
      { return v2; }
    inline size_t &V3(void)
      { return v3; }
    void Print(std::ostream &os) const;
  };


std::ostream &operator<<(std::ostream &os, const IndVerticesTriangulo &ivc);

class MapTriangulos
  {
    MapVertices mv;
    std::deque<IndVerticesTriangulo> caras;
  public:
    typedef MapVertices::iterator vertices_iterator;
    typedef MapVertices::const_iterator vertices_const_iterator;
    typedef std::deque<IndVerticesTriangulo>::const_iterator caras_const_iterator;

    vertices_const_iterator VerticesBegin(void) const
      { return mv.begin(); }
    vertices_const_iterator VerticesEnd(void) const
      { return mv.end(); }
    vertices_iterator VerticesBegin(void)
      { return mv.begin(); }
    vertices_iterator VerticesEnd(void)
      { return mv.end(); }
    caras_const_iterator CarasBegin(void) const
      { return caras.begin(); }
    caras_const_iterator CarasEnd(void) const
      { return caras.end(); }

    void InsertaVertice(GtsVertex *v);
    void InsertaCara(GtsTriangle *t);
    void Renumera(void);
    void Print(std::ostream &os) const;
  };


std::ostream &operator<<(std::ostream &os, const MapTriangulos &mt);

MapTriangulos getMapTriangulos(const GTSSurface &sf);

#endif
