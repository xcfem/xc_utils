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

//! @brief Devuelve verdadero si el rango no contiene ningún índice.
bool RangoTritriz::Vacio(void) const
  { return (rango_capas.Vacio() || rango_filas.Vacio() || rango_cols.Vacio()); }

//! @brief Devuelve la dimensión del rango 80,1,2 ó 3).
size_t RangoTritriz::Dimension(void) const
  {
    size_t retval= 0;
    if(rango_capas.Size()>1) retval++;
    if(rango_filas.Size()>1) retval++;
    if(rango_cols.Size()> 1) retval++;
    return retval;
  }

//! @brief Devuelve verdadero si el único índice que varía es el I.
bool RangoTritriz::EsFilaI(void) const
  {
    if((rango_filas.Size()>1) || (rango_cols.Size()>1)) return false;
    return true;
  }

//! @brief Devuelve verdadero si el único índice que varía es el J.
bool RangoTritriz::EsFilaJ(void) const
  {
    if((rango_capas.Size()>1) || (rango_cols.Size()>1)) return false;
    return true;
  }

//! @brief Devuelve verdadero si el único índice que varía es el K.
bool RangoTritriz::EsFilaK(void) const
  {
    if((rango_capas.Size()>1) || (rango_filas.Size()>1)) return false;
    return true;
  }

//! @brief Devuelve verdadero si los indices que varían son los J y K.
bool RangoTritriz::EsCapaICte(void) const
  { return (rango_capas.Size()==1); }

//! @brief Devuelve verdadero si los indices que varían son los I y K.
bool RangoTritriz::EsCapaJCte(void) const
  { return (rango_filas.Size()==1); }

//! @brief Devuelve verdadero si los indices que varían son los I y J.
bool RangoTritriz::EsCapaKCte(void) const
  { return (rango_cols.Size()==1); }

//! @brief Imprime el rango.
void RangoTritriz::Print(std::ostream &os) const
  { os << rango_capas << ',' << rango_filas << ',' << rango_cols; }

//! @brief Reduce los valores del rango de manera que ambos sean menores que
//! los que se pasan como parámetro.
void RangoTritriz::Recorta(const size_t &cpmax,const size_t &fmax,const size_t &cmax)
  {
    rango_capas.Recorta(cpmax);
    rango_filas.Recorta(fmax);
    rango_cols.Recorta(cmax);
  }

//! @brief Asigna a ESTE la intersección de ambos rangos.
void RangoTritriz::Intersec(const RangoTritriz &otro)
  {
    rango_capas.Intersec(otro.rango_capas);
    rango_filas.Intersec(otro.rango_filas);
    rango_cols.Intersec(otro.rango_cols);
  }

//! @brief Devuelve la intersección de ambos rangos.
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

RangoTritriz recorta(const RangoTritriz &r,const size_t &cpmax,const size_t &fmax,const size_t &cmax)
  {
    RangoTritriz retval(r);
    retval.Recorta(cpmax,fmax,cmax);
    return retval;
  }

//! @brief Devuelve la intersección de ambos rangos.
RangoTritriz intersec(const RangoTritriz &r1,const RangoTritriz &r2)
  { return r1.Intersec(r2); }
