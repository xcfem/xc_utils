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
//Cilindro.cc

#include "Cilindro.h"

//! @brief Constructor.
Cilindro::Cilindro(void) {}

//! @brief Constructor.
Cilindro::Cilindro(const Circulo3d &secc,const GEOM_FT &lng)
  : SolidExtru3d<Circulo3d>(secc,lng) {}

//! @brief Operador asignación.
Cilindro &Cilindro::operator=(const Cilindro &se)
  {
    solid_extru_cil::operator=(se);
    return *this;
  }

//! @brief Constructor virtual.
GeomObj *Cilindro::clon(void) const
  { return new Cilindro(*this); }

//! @Devuelve la extension del objeto.
BND3d Cilindro::Bnd(void) const
  { return solid_extru_cil::Bnd(); }

matriz_FT Cilindro::I(void) const
  { return solid_extru_cil::I(); }

Pos3d Cilindro::Cdg(void) const
  { return solid_extru_cil::Cdg(); }
