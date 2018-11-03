//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//m_double.cc

#include "m_double.h"

//! @brief Return the identity matrix.
m_double identidad(const m_double &m)
  {
    m_double retval(m);
    retval.Idn();
    return retval;
  }

//! @brief Return the identity matrix.
m_double identidad(const size_t &n_rows,const size_t &n_columns)
  {
    m_double retval(n_rows,n_columns);
    retval.Idn();
    return retval;
  }

//! @brief Convert a string (i. e.: [[1.0,0.0][0.0,1.0]]) into a matrix.
m_double string_to_m_double(const std::string &str)
  {
    m_double retval(1,1);
    retval.Input(str);
    return retval;
  }

