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
//utils_list_pos3d.h

#ifndef UTILS_LIST_POS3D_H
#define UTILS_LIST_POS3D_H

#include "xc_utils/src/geom/GeomObj.h"

class BND3d;
class Trf3d;
class Vector3d;

//Auxiliary functions for manipulation of position lists.


//! @ingroup GEOM
//
void mueve(GeomObj::list_Pos3d &l,const Vector3d &);
void transform(GeomObj::list_Pos3d &l,const Trf3d &);
Pos3d getPMax(const GeomObj::list_Pos3d &l);
Pos3d getPMin(const GeomObj::list_Pos3d &l);
BND3d getBnd(const GeomObj::list_Pos3d &l);

#endif

