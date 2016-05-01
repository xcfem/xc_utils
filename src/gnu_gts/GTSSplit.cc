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
//GTSSplit.cc

#include "GTSSplit.h"
#include "GTSVertex.h"
#include <iostream>

using namespace std;

void GTSSplit::crea(const GTSVertex &v,const GTSVertex &v1,const GTSVertex &v2)
  {
    if(spt) borra();
    spt = gts_split_new(gts_split_class(),v.vt,GTS_OBJECT(v1.vt),GTS_OBJECT(v2.vt));
    borrar= true;
  }
void GTSSplit::borra(void)
  {
    if(!borrar) return;
    if(spt) gts_object_destroy(GTS_OBJECT(spt));
    spt= nullptr;
    borrar= false;
  }
GTSSplit::GTSSplit(const GTSVertex &v,const GTSVertex &v1,const GTSVertex &v2)
  : spt(nullptr), borrar(false)
  { crea(v,v1,v2); }
GTSSplit::GTSSplit(const GTSSplit &otro)
  : spt(otro.spt), borrar(false)
  {}
GTSSplit &GTSSplit::operator=(const GTSSplit &otra)
  {
    borra();
    spt= otra.spt;
    borrar= false;
    return *this;
  }

void GTSSplit::Collapse(void)
//Collapses the vertex split vs. Any new edge created during the process will be of class klass. If heap is not nullptr, the new edges will be inserted into it and the destroyed edges will be removed from it.
  {
    gts_split_collapse(spt,gts_edge_class (),nullptr);
  }

  
GTSSplit::~GTSSplit(void)
  { borra(); }
