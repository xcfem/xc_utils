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
//Carsten_Steger.h

#ifndef CARSTEN_STEGER_H
#define CARSTEN_STEGER_H

#include "xc_basic/src/util/matem.h"
#include "../../tipos_cgal.h"

//Funciones auxiliares para la obtención de los 
//momentos arbitrarios (orden 0,1,2,3,...) de un polígono
//según el algoritmo descrito por Carsten Steger
//en el documento

// On the calculation of arbitrary moments of polygons
// Carsten Steger
// Technical Report FGBV-96-05
// October 1996

class SupPoligonal2d;

GEOM_FT momento_p_q(const SupPoligonal2d &sp,const int &p, const int &q);


#endif







