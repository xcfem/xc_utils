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
class Poligono2d;

//Funciones auxiliares para la manipulación de listas 
//de posiciones en 2d.

//! @ingroup GEOM
//
//! @brief Suma a las posiciones de la lista el vector que
//! se pasa como parámetro.
void mueve(GeomObj::list_Pos2d &l,const Vector2d &);
//! @brief Aplica a los puntos de la lista la transformación
//! que se pasa como parámetro.
void transforma(GeomObj::list_Pos2d &l,const Trf2d &);
void plot(Plotter &,const GeomObj::list_Pos2d &l);
//! @brief Devuelve los máximos de las coordenadas X e Y
//! de los puntos que se pasan como parámetro.
Pos2d getPMax(const GeomObj::list_Pos2d &l);
//! @brief Devuelve los mínimos de las coordenadas X e Y
//! de los puntos que se pasan como parámetro.
Pos2d getPMin(const GeomObj::list_Pos2d &l);
//! @brief Devuelve el «boundary» de 
//! los puntos que se pasan como parámetro.
BND2d getBnd(const GeomObj::list_Pos2d &l);
std::deque<GEOM_FT> &getRecubrimientos(const GeomObj::list_Pos2d &l,const Poligono2d &);
#endif

