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
#include "../../cgal_types.h"

//Aux functions for computing moments of arbitrary order  
//(0,1,2,3,...) of a polygon according to the algorithm
//según el algoritmo described by Carsten Steger
//in the document

// On the calculation of arbitrary moments of polygons
// Carsten Steger
// Technical Report FGBV-96-05
// October 1996

class PolygonalSurface2d;

GEOM_FT p_q_moment(const PolygonalSurface2d &sp,const int &p, const int &q);


#endif







