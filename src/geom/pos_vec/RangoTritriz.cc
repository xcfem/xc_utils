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
//RangoTritriz.cc

#include "RangoTritriz.h"

//! @brief Return verdadero si el rango no contiene ningún índice.
bool RangoTritriz::Vacio(void) const
  { return (layer_range.Vacio() || row_range.Vacio() || column_range.Vacio()); }

//! @brief Return la dimensión del rango 80,1,2 ó 3).
size_t RangoTritriz::Dimension(void) const
  {
    size_t retval= 0;
    if(layer_range.Size()>1) retval++;
    if(row_range.Size()>1) retval++;
    if(column_range.Size()> 1) retval++;
    return retval;
  }

//! @brief Return verdadero si el único índice que varía es el I.
bool RangoTritriz::isIRow(void) const
  {
    if((row_range.Size()>1) || (column_range.Size()>1)) return false;
    return true;
  }

//! @brief Return verdadero si el único índice que varía es el J.
bool RangoTritriz::isJRow(void) const
  {
    if((layer_range.Size()>1) || (column_range.Size()>1)) return false;
    return true;
  }

//! @brief Return verdadero si el único índice que varía es el K.
bool RangoTritriz::isKRow(void) const
  {
    if((layer_range.Size()>1) || (row_range.Size()>1)) return false;
    return true;
  }

//! @brief Return verdadero si los indices que varían son los J y K.
bool RangoTritriz::isConstantILayer(void) const
  { return (layer_range.Size()==1); }

//! @brief Return verdadero si los indices que varían son los I y K.
bool RangoTritriz::isConstantJLayer(void) const
  { return (row_range.Size()==1); }

//! @brief Return verdadero si los indices que varían son los I y J.
bool RangoTritriz::isConstantKLayer(void) const
  { return (column_range.Size()==1); }

//! @brief Imprime el rango.
void RangoTritriz::Print(std::ostream &os) const
  { os << layer_range << ',' << row_range << ',' << column_range; }

//! @brief Reduce los valores del rango de manera que ambos sean menores que
//! los que se pasan como parámetro.
void RangoTritriz::Clip(const size_t &cpmax,const size_t &fmax,const size_t &cmax)
  {
    layer_range.Clip(cpmax);
    row_range.Clip(fmax);
    column_range.Clip(cmax);
  }

//! @brief Assigns to this one the intersection of both ranges.
void RangoTritriz::Intersec(const RangoTritriz &otro)
  {
    layer_range.Intersec(otro.layer_range);
    row_range.Intersec(otro.row_range);
    column_range.Intersec(otro.column_range);
  }

//! @brief Return the intersection of both ranges.
RangoTritriz RangoTritriz::Intersec(const RangoTritriz &otro) const
  {
    RangoTritriz retval(*this);
    retval.Intersec(otro);
    return retval;
  }

std::ostream &operator<<(std::ostream &os,const RangoTritriz &rango)
  {
    rango.Print(os);
    return os;
  }

RangoTritriz clip(const RangoTritriz &r,const size_t &cpmax,const size_t &fmax,const size_t &cmax)
  {
    RangoTritriz retval(r);
    retval.Clip(cpmax,fmax,cmax);
    return retval;
  }

//! @brief Return the intersection of both ranges.
RangoTritriz intersec(const RangoTritriz &r1,const RangoTritriz &r2)
  { return r1.Intersec(r2); }
