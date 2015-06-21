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
//GTSSurfaceIntersection.h
//C++ wraper para la clase GtsFace de la biblioteca GTS.

#ifndef GTS_SURFACEINTERSECTION_H
#define GTS_SURFACEINTERSECTION_H

#include "gts.h"
#include <string>

class GTSSurface;

class GTSSurfaceIntersection
  {
    GtsSurfaceInter *si;

    bool borrar;

    void borra(void);

  protected:
    GtsSurfaceInter const *get_const_ptr(void) const
      { return si; }
    GtsSurfaceInter *get_ptr(void)
      { return si; }
    GTSSurface bool_op(const std::string &operation,GTSSurface &s2) const;

  public:

    GTSSurfaceIntersection(GtsSurfaceInter *f= NULL);
    GTSSurfaceIntersection(GtsSurfaceInterClass *klass,
                           GTSSurface &s1, GTSSurface &s2);
    GTSSurfaceIntersection(const GTSSurfaceIntersection &otra);
    GTSSurfaceIntersection &operator=(const GTSSurfaceIntersection &otra);

    void Write(FILE *fp);

    bool Check(bool &closed) const;

    void InterBoolean(GTSSurface &surface,GtsBooleanOperation op) const;

    ~GTSSurfaceIntersection(void);

    friend GTSSurface BoolOp(const GTSSurfaceIntersection &si,GTSSurface &s1, GTSSurface &s2,const std::string &str_op,bool check_self_intersection,bool verbose=false);
  };


#endif
