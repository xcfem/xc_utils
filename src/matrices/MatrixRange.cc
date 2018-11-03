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
//MatrixRange.cc

#include "MatrixRange.h"

//! @brief Return verdadero si el rango no contiene ningún índice.
bool MatrixRange::Vacio(void) const
{ return (row_range.Vacio() || column_range.Vacio()); }

//! @brief Imprime el rango.
void MatrixRange::Print(std::ostream &os) const
  { os << row_range << ',' << column_range; }

//! @brief Reduce los valores del rango de manera que ambos sean menores que
//! los being passed as parameter.
void MatrixRange::Clip(const size_t &fmax,const size_t &cmax)
  {
    row_range.Clip(fmax);
    column_range.Clip(cmax);
  }

//! @brief Asigna a ESTE la intersección de ambos rangos.
void MatrixRange::Intersec(const MatrixRange &otro)
  {
    row_range.Intersec(otro.row_range);
    column_range.Intersec(otro.column_range);
  }

//! @brief Return la intersección de ambos rangos.
MatrixRange MatrixRange::Intersec(const MatrixRange &otro) const
  {
    MatrixRange retval(*this);
    retval.Intersec(otro);
    return retval;
  }

std::ostream &operator<<(std::ostream &os,const MatrixRange &rango)
  {
    rango.Print(os);
    return os;
  }

MatrixRange clip(const MatrixRange &r,const size_t &fmax,const size_t &cmax)
  {
    MatrixRange retval(r);
    retval.Clip(fmax,cmax);
    return retval;
  }

//! @brief Return la intersección de ambos rangos.
MatrixRange intersec(const MatrixRange &r1,const MatrixRange &r2)
  { return r1.Intersec(r2); }
