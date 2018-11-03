//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//Muestra.cc

#include "Muestra.h"
#include "xc_utils/src/utils/misc_utils/matem.h"

double Muestra::Media(void) const
  {
    double retval= 0.0;
    for(const_iterator i=begin();i!=end();i++)
      retval+= *i;
    return retval/double(size());
  }
double Muestra::DesviacionTipica(void) const
  {
    double media= Media();
    double retval= 0.0;
    for(const_iterator i=begin();i!=end();i++)
      retval+= sqr(media-*i);
    return sqrt(retval/double(size()));
  }
