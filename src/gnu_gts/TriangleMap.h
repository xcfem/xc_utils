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
//TriangleMap.h

#ifndef TRIANGLE_MAP_H
#define TRIANGLE_MAP_H


#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <unistd.h>
#include "gts.h"
#include "xc_utils/src/gnu_gts/GTSVertex.h"
#include "xc_utils/src/gnu_gts/GTSFace.h"
#include "xc_utils/src/gnu_gts/GTSSurface.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/pos_vec/KDTreePos.h"
#include "xc_basic/src/kdtree++/kdtree.hpp"
#include <iostream>
#include <map>

Pos3d Vertex2Pos3d(const GtsVertex &v);

//! \ingroup Nod
//
//! @brief Vertex position wrapper for KDTree.
class VertexPos: public KDTreePos
  {
  private:
    int index;
  public:
    VertexPos(const int &i, const Pos3d &);
    explicit VertexPos(const Pos3d &p);
    inline const int &getIndex(void) const
      { return index; }
    static inline double tac( VertexPos p, size_t k ) { return p[k]; }
  };

inline bool operator==(const VertexPos &A,const VertexPos &B)
  { return ((A.getIndex()== B.getIndex()) && (A[0] == B[0]) && (A[1] == B[1]) && (A[2] == B[2])); }

class VerticesKDTree: protected kd_tree::KDTree<3, VertexPos, std::pointer_to_binary_function<VertexPos,size_t,double> >
  {
    size_t pend_optimizar;
  public:
    typedef kd_tree::KDTree<3, VertexPos, std::pointer_to_binary_function<VertexPos,size_t,double> > tree_type;
    VerticesKDTree(void);

    void insert(const int &,const Pos3d &);
    //void erase(const VertexPos &);
    void clear(void);

    int getNearest(const Pos3d &pos) const;
    int getNearestBallPoint(const Pos3d &pos, const double &r) const;
  };

class VerticesMap: public std::map<size_t,Pos3d>
  {

    static bool chequea_vertice(GtsVertex *v);

    friend class TriangleMap;

  public:
    void Inserta(GtsVertex *v);
    void Inserta(const size_t &i,const Pos3d &p);
    void Print(std::ostream &os) const;
    void Borra(void);
  };

std::ostream &operator<<(std::ostream &os, const VerticesMap &mv);

class TriangleVerticesIndexes
//Almacena tres indices que resultan de convertir
//los punteros a los vértices en enteros
  {
    size_t v1,v2,v3;

    bool chequea_edges(GtsTriangle *t);

  public:
    TriangleVerticesIndexes(void);
    TriangleVerticesIndexes(const size_t &,const size_t &,const size_t &);
    TriangleVerticesIndexes(GtsTriangle *t);
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
    inline bool operator==(const TriangleVerticesIndexes &otro) const
      { return (v1==otro.v1) && (v2==otro.v2) && (v3==otro.v3); }
    void Print(std::ostream &os) const;
  };


std::ostream &operator<<(std::ostream &os, const TriangleVerticesIndexes &ivc);

class TriangleFaces: public std::deque<TriangleVerticesIndexes>
  {
  public:
    void Append(const size_t &,const size_t &,const size_t &);
    void Print(std::ostream &os) const;
  };

class TriangleMap
  {
    VerticesMap mv;
    TriangleFaces faces;
  public:
    inline const VerticesMap &getVertices(void) const
      { return mv; }
    inline VerticesMap &getVertices(void)
      { return mv; }
    inline const TriangleFaces &getFaces(void) const
      { return faces; }
    inline TriangleFaces &getFaces(void)
      { return faces; }

    void InsertaVertice(GtsVertex *v);
    void AppendFace(GtsTriangle *t);
    void Renumera(void);
    void Print(std::ostream &os) const;
  };


std::ostream &operator<<(std::ostream &os, const TriangleMap &mt);

TriangleMap getTriangleMap(const GTSSurface &sf);

#endif
