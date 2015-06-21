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
//GTSFace.h
//C++ wraper para la clase GtsFace de la biblioteca GTS.

#ifndef GTS_FACE_H
#define GTS_FACE_H

#include "gts.h"

class GTSEdge;

class GTSFace
  {
    GtsFace *fc;

    bool borrar;
    void crea(GTSEdge &e1,GTSEdge &e2,GTSEdge &e3);
    void borra(void);
  protected:
    GtsFace const *get_const_ptr(void) const
      { return fc; }
    GtsFace *get_ptr(void)
      { return fc; }

  public:
    friend class GTSSurface;
    friend class GTSSurfaceTraverse;

    GTSFace(GtsFace *f= NULL);
    GTSFace(GTSEdge &e1,GTSEdge &e2,GTSEdge &e3);
    GTSFace(const GTSFace &otra);
    GTSFace &operator=(const GTSFace &otra);
    bool Null(void) const;
    ~GTSFace(void);
  };


#endif
