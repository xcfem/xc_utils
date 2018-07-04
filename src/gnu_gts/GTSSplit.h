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
//GTSSplit.h
//C++ wrapper para la clase GtsSplit de la biblioteca GTS.

#ifndef GTS_SPLIT_H
#define GTS_SPLIT_H

#include "gts.h"

class GTSVertex;

class GTSSplit
  {
    GtsSplit *spt;

    bool borrar;

    void crea(const GTSVertex &v,const GTSVertex &v1,const GTSVertex &v2);
    void borra(void);

  public:

    friend class GTSEdge;

    GTSSplit(const GTSVertex &v,const GTSVertex &v1,const GTSVertex &v2);
    GTSSplit(const GtsSplit *pspt);
    GTSSplit(const GTSSplit &);
    GTSSplit &operator=(const GTSSplit &otra);

    void Collapse(void);

    ~GTSSplit(void);
  };


#endif
