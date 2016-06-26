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
//GTSGraph.h
//C++ wrapper para la clase GtsGraph de la biblioteca GTS.

#ifndef GTS_GRAPH_H
#define GTS_GRAPH_H

#include "gts.h"

class GTSSurface;

class GTSGraph
  {
    GtsGraph *gph;

    bool borrar;

    void crea(const GTSSurface &s);
    void borra(void);

  public:

    GTSGraph(const GTSSurface &s);
    GTSGraph(const GTSGraph &otro);
    GTSGraph &operator=(const GTSGraph &otro);

    void PrintStats(FILE* fp) const;

    void Write(FILE *fp);

    ~GTSGraph(void);
  };


#endif
