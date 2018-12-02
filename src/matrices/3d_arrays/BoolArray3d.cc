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
//BoolArray3d.cc

#include "BoolArray3d.h"

//! @brief Generate the bool arrays from the arguments.
//!
//! @param n_layers: number of layers.
//! @param n_rows: number of rows for each layer.
//! @param n_columns: number of columns for each layer.
//! @param def_value: default value.
BoolArray3d::BoolArray3d(const size_t &n_layers, const size_t &n_rows, const size_t &n_columns, const bool &def_value)
: Array3dBase<m_bool>(n_layers,n_rows,n_columns,def_value)
  {}
