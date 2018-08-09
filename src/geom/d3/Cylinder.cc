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
//Cylinder.cc

#include "Cylinder.h"

//! @brief Constructor.
Cylinder::Cylinder(void) {}

//! @brief Constructor.
Cylinder::Cylinder(const Circle3d &secc,const GEOM_FT &lng)
  : SolidExtru3d<Circle3d>(secc,lng) {}

//! @brief Operador asignación.
Cylinder &Cylinder::operator=(const Cylinder &se)
  {
    solid_extru_cil::operator=(se);
    return *this;
  }

//! @brief Constructor virtual.
GeomObj *Cylinder::clon(void) const
  { return new Cylinder(*this); }

//! @Return la extension del objeto.
BND3d Cylinder::Bnd(void) const
  { return solid_extru_cil::Bnd(); }

FT_matrix Cylinder::I(void) const
  { return solid_extru_cil::I(); }

Pos3d Cylinder::getCenterOfMass(void) const
  { return solid_extru_cil::getCenterOfMass(); }
