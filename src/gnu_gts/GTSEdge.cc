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
//GTSEdge.cc

#include "GTSEdge.h"
#include "GTSVertex.h"
#include <iostream>

using namespace std;

void GTSEdge::crea(GTSVertex &v1,GTSVertex &v2)
  {
    if(edg) borra();
    edg = gts_edge_new(gts_edge_class(),v1.vt,v2.vt);
    v1.borrar= false; //Al parecer, desde aqui ESTE objeto se encarga
    v2.borrar= false; //de borrar los vértices.
    borrar= true;
  }
void GTSEdge::borra(void)
  {
    if(!borrar) return;
    if(edg) gts_object_destroy(GTS_OBJECT(edg));
    edg= NULL;
    borrar= false;
  }
GTSEdge::GTSEdge(GTSVertex &v1,GTSVertex &v2)
  : edg(NULL), borrar(false)
{ crea(v1,v2); }
GTSEdge::GTSEdge(const GTSEdge &otro)
  : edg(otro.edg), borrar(false)
  {}
GTSEdge &GTSEdge::operator=(const GTSEdge &otra)
  {
    borra();
    edg= otra.edg;
    borrar= false;
    return *this;
  }
GTSEdge::~GTSEdge(void)
  { borra(); }

GTSVertex GTSEdge::V1(void) const
  { return GTSVertex(GTS_SEGMENT(edg)->v1); }
GTSVertex GTSEdge::V2(void) const
  { return GTSVertex(GTS_SEGMENT(edg)->v2); }


bool GTSEdge::CollapseIsValid(void) const
//TRUE if e can be collapsed without violation of the topological constraints, FALSE otherwise.
  { return gts_edge_collapse_is_valid(edg); }
GTSVertex GTSEdge::VolumeOptimizedVertex(GtsVolumeOptimizedParams &params) const
//TRUE if e can be collapsed without violation of the topological constraints, FALSE otherwise.
  { return GTSVertex(gts_volume_optimized_vertex(edg, gts_vertex_class (), &params)); }
