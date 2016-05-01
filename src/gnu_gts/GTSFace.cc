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
//GTSFace.cc

#include "GTSFace.h"
#include "GTSEdge.h"

void GTSFace::crea(GTSEdge &e1,GTSEdge &e2,GTSEdge &e3)
  {
    if(fc) borra();
    fc = gts_face_new(gts_face_class(),e1.edg,e2.edg,e3.edg);
    e1.borrar= false; //Al parecer, desde aqui ESTE objeto se encarga
    e2.borrar= false; //de borrar los edges.
    e3.borrar= false;
    borrar= true;
  }
void GTSFace::borra(void)
  {
    if(!borrar) return;
    if(fc) gts_object_destroy(GTS_OBJECT(fc));
    fc= nullptr;
    borrar= false;
  }
GTSFace::GTSFace(GtsFace *f)
  :fc(f), borrar(false) {}
GTSFace::GTSFace(GTSEdge &e1,GTSEdge &e2,GTSEdge &e3)
  : fc(nullptr), borrar(false)
  { crea(e1,e2,e3); }
GTSFace::GTSFace(const GTSFace &otra)
  :fc(otra.fc), borrar(false) {}
GTSFace &GTSFace::operator=(const GTSFace &otra)
  {
    borra();
    fc= otra.fc;
    borrar= false;
    return *this;
  }
bool GTSFace::Null(void) const
  { return (fc==nullptr); }

GTSFace::~GTSFace(void)
  { borra(); }
