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
//utils_list_pos3d.cc

#include "utils_list_pos3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/trf/Trf3d.h"
#include "xc_utils/src/geom/d3/BND3d.h"


//! @brief Desplaza los puntos de la lista.
void mueve(GeomObj::list_Pos3d &l,const Vector3d &v)
  {
    for(register GeomObj::list_Pos3d::iterator j=l.begin();j != l.end();j++)
      (*j)= (*j) + v;
  }

//! @brief Aplica a los vértices la transformación que se pasa como parámetro.
void transforma(GeomObj::list_Pos3d &l,const Trf3d &t)
  { t.Transforma(l.begin(),l.end()); }

//! @brief Devuelve la esquina superior derecha del rectángulo envolvente. 
Pos3d getPMax(const GeomObj::list_Pos3d &l)
  { return Pos3d(l.GetMax(1),l.GetMax(2),l.GetMax(3)); }

//! @brief Devuelve la esquina inferior izquierda del rectángulo envolvente. 
Pos3d getPMin(const GeomObj::list_Pos3d &l)
  { return Pos3d(l.GetMin(1),l.GetMin(2),l.GetMin(3)); }

//! @brief Devuelve el rectángulo envolvente. 
BND3d getBnd(const GeomObj::list_Pos3d &l)
  { return BND3d(getPMin(l),getPMax(l)); }

