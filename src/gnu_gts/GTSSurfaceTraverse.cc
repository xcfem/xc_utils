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
//GTSSurfaceTraverse.cc

#include "GTSSurfaceTraverse.h"
#include "GTSSurface.h"
#include "GTSFace.h"
#include <iostream>

using namespace std;

void GTSSurfaceTraverse::crea(const GTSSurface &s,const GTSFace &f)
  {
    if(sft) borra();
    sft = gts_surface_traverse_new(s.s,f.fc);
    borrar= true;
  }
void GTSSurfaceTraverse::borra(void)
  {
    if(!borrar) return;
    if(sft) gts_surface_traverse_destroy(sft);
    sft= NULL;
    borrar= false;
  }
GTSSurfaceTraverse::GTSSurfaceTraverse(const GTSSurface &s,const GTSFace &f)
  : sft(NULL), borrar(false)
  { crea(s,f); }
GTSSurfaceTraverse::GTSSurfaceTraverse(const GTSSurfaceTraverse &otra)
  : sft(otra.sft), borrar(false)
  {}
GTSSurfaceTraverse &GTSSurfaceTraverse::operator=(const GTSSurfaceTraverse &otra)
  {
    sft= otra.sft;
    borrar= false;
    return *this;
  }  
GTSSurfaceTraverse::~GTSSurfaceTraverse(void)
  { borra(); }
GTSFace GTSSurfaceTraverse::Next(guint *level) const
  { return GTSFace(gts_surface_traverse_next(sft,level)); }
