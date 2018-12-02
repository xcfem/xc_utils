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
//Array3dRange.cc

#include "Array3dRange.h"

//! @brief Return verdadero si el rango no contiene ningún índice.
bool Array3dRange::Vacio(void) const
  { return (layer_range.Vacio() || row_range.Vacio() || column_range.Vacio()); }

//! @brief Return la dimensión del rango 80,1,2 ó 3).
size_t Array3dRange::Dimension(void) const
  {
    size_t retval= 0;
    if(layer_range.Size()>1) retval++;
    if(row_range.Size()>1) retval++;
    if(column_range.Size()> 1) retval++;
    return retval;
  }

//! @brief Return verdadero si el único índice que varía es el I.
bool Array3dRange::isIRow(void) const
  {
    if((row_range.Size()>1) || (column_range.Size()>1)) return false;
    return true;
  }

//! @brief Return verdadero si el único índice que varía es el J.
bool Array3dRange::isJRow(void) const
  {
    if((layer_range.Size()>1) || (column_range.Size()>1)) return false;
    return true;
  }

//! @brief Return verdadero si el único índice que varía es el K.
bool Array3dRange::isKRow(void) const
  {
    if((layer_range.Size()>1) || (row_range.Size()>1)) return false;
    return true;
  }

//! @brief Return verdadero si los indices que varían son los J y K.
bool Array3dRange::isConstantILayer(void) const
  { return (layer_range.Size()==1); }

//! @brief Return verdadero si los indices que varían son los I y K.
bool Array3dRange::isConstantJLayer(void) const
  { return (row_range.Size()==1); }

//! @brief Return verdadero si los indices que varían son los I y J.
bool Array3dRange::isConstantKLayer(void) const
  { return (column_range.Size()==1); }

//! @brief Imprime el rango.
void Array3dRange::Print(std::ostream &os) const
  { os << layer_range << ',' << row_range << ',' << column_range; }

//! @brief Reduce los valores del rango de manera que ambos sean menores que
//! los que se pasan como parámetro.
void Array3dRange::Clip(const size_t &cpmax,const size_t &fmax,const size_t &cmax)
  {
    layer_range.Clip(cpmax);
    row_range.Clip(fmax);
    column_range.Clip(cmax);
  }

//! @brief Assigns to this one the intersection of both ranges.
void Array3dRange::Intersec(const Array3dRange &other)
  {
    layer_range.Intersec(other.layer_range);
    row_range.Intersec(other.row_range);
    column_range.Intersec(other.column_range);
  }

//! @brief Return the intersection of both ranges.
Array3dRange Array3dRange::Intersec(const Array3dRange &other) const
  {
    Array3dRange retval(*this);
    retval.Intersec(other);
    return retval;
  }

std::ostream &operator<<(std::ostream &os,const Array3dRange &rango)
  {
    rango.Print(os);
    return os;
  }

Array3dRange clip(const Array3dRange &r,const size_t &cpmax,const size_t &fmax,const size_t &cmax)
  {
    Array3dRange retval(r);
    retval.Clip(cpmax,fmax,cmax);
    return retval;
  }

//! @brief Return the intersection of both ranges.
Array3dRange intersec(const Array3dRange &r1,const Array3dRange &r2)
  { return r1.Intersec(r2); }
