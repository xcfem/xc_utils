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
//utils_list_pos2d.h

#ifndef UTILS_LIST_POS2D_H
#define UTILS_LIST_POS2D_H

#include "xc_utils/src/geom/GeomObj.h"

class BND2d;
class Polygon2d;

//Auxiliary functions for manipulation of position lists.

//! @ingroup GEOM
//
void mueve(GeomObj::list_Pos2d &l,const Vector2d &);
void transforma(GeomObj::list_Pos2d &l,const Trf2d &);
void plot(Plotter &,const GeomObj::list_Pos2d &l);
Pos2d getPMax(const GeomObj::list_Pos2d &l);
Pos2d getPMin(const GeomObj::list_Pos2d &l);
BND2d getBnd(const GeomObj::list_Pos2d &l);
std::deque<GEOM_FT> &getRecubrimientos(const GeomObj::list_Pos2d &l,const Polygon2d &);
#endif

