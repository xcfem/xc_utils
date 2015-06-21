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
//MapTriangulos.cc

#include "MapTriangulos.h"

Pos3d Vertex2Pos3d(const GtsVertex &v)
  { return Pos3d(v.p.x,v.p.y,v.p.z); }

static gboolean vertex_add(GtsVertex *v,MapTriangulos *mt)
  {
    mt->InsertaVertice(v);
    return TRUE;
  }
static gboolean triangle_add(GtsTriangle *t,MapTriangulos *mt)
  {
    mt->InsertaCara(t);
    return TRUE;
  }

bool MapVertices::chequea_vertice(GtsVertex *v)
  {
    g_return_val_if_fail (v != NULL, FALSE);
    g_return_val_if_fail (GTS_OBJECT (v)->reserved == NULL, FALSE);
    g_assert (GTS_OBJECT (v)->reserved == NULL);
    return true;
  }

void MapVertices::Inserta(GtsVertex *v)
  {
    if(!chequea_vertice(v))
      std::cerr << "MapVertices: se intentó insertar un vértice erróneo." << std::endl;
    Inserta(size_t(v),Vertex2Pos3d(*v));
  }
void MapVertices::Inserta(const size_t &i,const Pos3d &p)
  { (*this)[i]= p; }
void MapVertices::Print(std::ostream &os) const
  {
    for(const_iterator i= begin();i!=end();i++)
      os << "Vertice: " << (*i).first << ": " << (*i).second << std::endl;
  }
void MapVertices::Borra(void)
  { erase(begin(),end()); }

std::ostream &operator<<(std::ostream &os, const MapVertices &mv)
  {
    mv.Print(os);
    return os;
  }

IndVerticesTriangulo::IndVerticesTriangulo(GtsTriangle *t)
  : v1(size_t(gts_triangle_vertex_opposite(t,t->e1))),
    v2(size_t(gts_triangle_vertex_opposite(t,t->e2))),
    v3(size_t(gts_triangle_vertex_opposite(t,t->e3)))
  {
    if(!chequea_edges(t))
      std::cerr << "IndVerticesTriangulo: Error al crear la cara." << std::endl;
  }
bool IndVerticesTriangulo::chequea_edges(GtsTriangle *t)
  {
    g_return_val_if_fail(t != NULL, false);
    g_return_val_if_fail(t->e1 != NULL, false);
    g_return_val_if_fail(t->e2 != NULL, false);
    g_return_val_if_fail(t->e3 != NULL, false);
    g_return_val_if_fail(t->e1 != t->e2 && t->e1 != t->e3 && t->e2 != t->e3, false);
    g_assert(gts_segments_touch (GTS_SEGMENT (t->e1), GTS_SEGMENT (t->e2)));
    g_return_val_if_fail (gts_segments_touch (GTS_SEGMENT (t->e1), GTS_SEGMENT (t->e3)), FALSE);
    g_return_val_if_fail (gts_segments_touch (GTS_SEGMENT (t->e2), GTS_SEGMENT (t->e3)), FALSE);
    g_return_val_if_fail (GTS_SEGMENT (t->e1)->v1 != GTS_SEGMENT (t->e1)->v2, FALSE);
    g_return_val_if_fail (GTS_SEGMENT (t->e2)->v1 != GTS_SEGMENT (t->e2)->v2, FALSE);
    g_return_val_if_fail (GTS_SEGMENT (t->e3)->v1 != GTS_SEGMENT (t->e3)->v2, FALSE);
    g_return_val_if_fail (GTS_OBJECT (t)->reserved == NULL, FALSE);
    return true;
  }
void IndVerticesTriangulo::Print(std::ostream &os) const
  {
    os << "Cara: " << v1 << ", " << v2 << ", " << v3;
  }
std::ostream &operator<<(std::ostream &os, const IndVerticesTriangulo &ivc)
  {
    ivc.Print(os);
    return os;
  }

void MapTriangulos::InsertaVertice(GtsVertex *v)
  { mv.Inserta(v); }
void MapTriangulos::InsertaCara(GtsTriangle *t)
  { caras.push_back(IndVerticesTriangulo(t)); }
void MapTriangulos::Renumera(void)
  {
    MapVertices mv_renum; //Vertices renumerados.
    size_t contador= 1;
    for(vertices_iterator i= VerticesBegin();i!=VerticesEnd();i++)
      {
        const size_t ind_vertice= (*i).first;
        const Pos3d coo_vertice= (*i).second;
        for(std::deque<IndVerticesTriangulo>::iterator j= caras.begin();j!=caras.end();j++)
          {
            IndVerticesTriangulo &cara_j= *j;
            if(cara_j.V1() == ind_vertice) cara_j.V1()= contador;
            if(cara_j.V2() == ind_vertice) cara_j.V2()= contador;
            if(cara_j.V3() == ind_vertice) cara_j.V3()= contador;
          }
        mv_renum[contador]= coo_vertice;
        contador++;
      }
    mv.Borra();
    mv= mv_renum;
  }
void MapTriangulos::Print(std::ostream &os) const
  {
    os << "Lista de vértices: " << std::endl;
    mv.Print(os);
    os << "Lista de caras: " << std::endl;
    for(caras_const_iterator i= caras.begin();i!=caras.end();i++)
      os << *i << std::endl;
  }
std::ostream &operator<<(std::ostream &os, const MapTriangulos &mt)
  {
    mt.Print(os);
    return os;
  }

MapTriangulos getMapTriangulos(const GTSSurface &sf)
  {
    MapTriangulos retval;
    sf.ForEachVertex((GtsFunc)vertex_add,&retval);
    sf.ForEachFace((GtsFunc)triangle_add,&retval);
    retval.Renumera();
    return retval;
  }


