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
//bool_op_poliedro3d.h
//Operaciones booleanas entre poliedros.

#ifndef BOOL_OP_POLIEDRO3D_H
#define BOOL_OP_POLIEDRO3D_H

class Poliedro3d;


//! @ingroup GEOM
//
//! @brief Unión de los poliedros que se pasan como parámetro.
Poliedro3d Union(const Poliedro3d &a,const Poliedro3d &b);
//! @brief Intersección de los poliedros que se pasan como parámetro.
Poliedro3d Interseccion(const Poliedro3d &a,const Poliedro3d &b);
//! @brief Diferencia de los poliedros que se pasan como parámetro.
Poliedro3d Diferencia(const Poliedro3d &a,const Poliedro3d &b);

#endif
