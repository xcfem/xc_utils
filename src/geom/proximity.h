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
//proximity.h

#ifndef PROXIMITY_H
#define PROXIMITY_H

template<class InputIter, class Pt>
const InputIter nearest(InputIter first, InputIter last,const Pt &p)
  {
    InputIter i=first;
    InputIter retval= i;
    double dist_min= dist(*retval,p);
    for(;i!=last; i++)
      {
        const double d= dist(*i,p);
        if(d<dist_min)
          {
            dist_min= d;
            retval= i;
          }
      }
    return retval;
  }


#endif
