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
//GTSGraph.cc

#include "GTSGraph.h"
#include "GTSSurface.h"
#include <iostream>

using namespace std;

void GTSGraph::crea(const GTSSurface &s)
  {
    if(gph) borra();
    gph = gts_surface_graph_new(gts_graph_class(),s.s);
    borrar= true;
  }
void GTSGraph::borra(void)
  {
    if(!borrar) return;
    if(gph) gts_object_destroy(GTS_OBJECT(gph));
    gph= nullptr;
    borrar= false;
  }
GTSGraph::GTSGraph(const GTSSurface &s)
  : gph(nullptr), borrar(false)
  { crea(s); }
GTSGraph::GTSGraph(const GTSGraph &other)
  : gph(other.gph), borrar(false)
  {}
GTSGraph &GTSGraph::operator=(const GTSGraph &otra)
  {
    borra();
    gph= otra.gph;
    borrar= false;
    return *this;
  }

void GTSGraph::PrintStats(FILE* fp) const
  { gts_graph_print_stats (gph, fp); }

void GTSGraph::Write(FILE *fp)
  { gts_graph_write(gph, fp); }

GTSGraph::~GTSGraph(void)
  { borra(); }



