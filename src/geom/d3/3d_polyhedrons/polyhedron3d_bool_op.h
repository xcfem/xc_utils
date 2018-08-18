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
//polyhedron3d_bool_op.h
//Boolean operations between polyhedrons.

#ifndef POLYHEDRON3D_BOOL_OP_H
#define POLYHEDRON3D_BOOL_OP_H

class Polyhedron3d;


//! @ingroup GEOM
//
//! @brief Union of the polyhedron arguments.
Polyhedron3d Union(const Polyhedron3d &a,const Polyhedron3d &b);
//! @brief Intersection of the polyhedrons.
Polyhedron3d intersection(const Polyhedron3d &a,const Polyhedron3d &b);
//! @brief Difference of the polyhedrons.
Polyhedron3d Diferencia(const Polyhedron3d &a,const Polyhedron3d &b);

#endif
