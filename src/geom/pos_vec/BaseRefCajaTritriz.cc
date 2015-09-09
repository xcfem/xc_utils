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
//BaseRefCajaTritriz.cc

#include "BaseRefCajaTritriz.h"
#include "xc_basic/src/matrices/RangoIndice.h"
#include "RangoTritriz.h"
#include <iostream>

BaseRefCajaTritriz::BaseRefCajaTritriz(const size_t &capa1,const size_t &f1,const size_t &c1,const size_t &capa2,const size_t &f2,const size_t &c2)
  : ncapas(std::max(capa2-capa1+1,size_t(0))), nfls(std::max(f2-f1+1,size_t(0))), ncls(std::max(c2-c1+1,size_t(0))),
    offset_cp(capa1-1),offset_f(f1-1),offset_c(c1-1) {}

BaseRefCajaTritriz::BaseRefCajaTritriz(const RangoTritriz &rango)
  : ncapas(rango.GetRangoCapas().Size()), nfls(rango.GetRangoFilas().Size()), ncls(rango.GetRangoCols().Size()),
    offset_cp(rango.GetRangoCapas().Offset()),offset_f(rango.GetRangoFilas().Offset()),offset_c(rango.GetRangoCols().Offset()) 
  {
    if(rango.Vacio())
      std::cerr << "Error!. El rango: '" << rango << "', está vacío." << std::endl;
  }

BaseRefCajaTritriz::BaseRefCajaTritriz(const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols)
  : ncapas(1), nfls(rango_filas.Size()), ncls(rango_cols.Size()),
    offset_cp(capa-1),offset_f(rango_filas.Offset()),offset_c(rango_cols.Offset()) 
  {
    if(rango_filas.Vacio())
      std::cerr << "Error!. El rango de las filas: '" << rango_filas << "', está vacío." << std::endl;
    if(rango_cols.Vacio())
      std::cerr << "Error!. El rango de las columnas: '" << rango_cols << "', está vacío." << std::endl;
  }

BaseRefCajaTritriz::BaseRefCajaTritriz(const RangoIndice &rango_capas,const size_t &fila,const RangoIndice &rango_cols)
  : ncapas(rango_capas.Size()), nfls(1), ncls(rango_cols.Size()),
    offset_cp(rango_capas.Offset()),offset_f(fila-1),offset_c(rango_cols.Offset())
  {
    if(rango_capas.Vacio())
      std::cerr << "Error!. El rango de las capas: '" << rango_capas << "', está vacío." << std::endl;
    if(rango_cols.Vacio())
      std::cerr << "Error!. El rango de las columnas: '" << rango_cols << "', está vacío." << std::endl;
  }

BaseRefCajaTritriz::BaseRefCajaTritriz(const RangoIndice &rango_capas,const RangoIndice &rango_filas,const size_t &col)
  : ncapas(rango_capas.Size()), nfls(rango_filas.Size()), ncls(1),
    offset_cp(rango_capas.Offset()),offset_f(rango_filas.Offset()),offset_c(col-1)
  {
    if(rango_capas.Vacio())
      std::cerr << "Error!. El rango de las capas: '" << rango_capas << "', está vacío." << std::endl;
    if(rango_filas.Vacio())
      std::cerr << "Error!. El rango de las filas: '" << rango_filas << "', está vacío." << std::endl;
  }

BaseRefCajaTritriz::BaseRefCajaTritriz(const size_t &capa,const size_t &fila,const RangoIndice &rango_cols)
  : ncapas(1), nfls(1), ncls(rango_cols.Size()),
    offset_cp(capa-1),offset_f(fila-1),offset_c(rango_cols.Offset()) {}

BaseRefCajaTritriz::BaseRefCajaTritriz(const size_t capa,const RangoIndice &rango_filas,const size_t &col)
  : ncapas(1), nfls(rango_filas.Size()), ncls(1),
    offset_cp(capa-1),offset_f(rango_filas.Offset()),offset_c(col-1) {}

BaseRefCajaTritriz::BaseRefCajaTritriz(const RangoIndice &rango_capas,const size_t &fila,const size_t &col)
  : ncapas(rango_capas.Size()), nfls(1), ncls(1),
    offset_cp(rango_capas.Offset()),offset_f(fila-1),offset_c(col-1) {}

//! @brief Devuelve el rango de capas.
RangoIndice BaseRefCajaTritriz::RangoCapas(void) const
  { return RangoIndice(offset_cp+1,offset_cp+GetCapas()); }

//! @brief Devuelve el rango de filas.
RangoIndice BaseRefCajaTritriz::RangoFilas(void) const
  { return RangoIndice(offset_f+1,offset_f+getNumFilas()); }

//! @brief Devuelve el rango de columnas.
RangoIndice BaseRefCajaTritriz::RangoCols(void) const
  { return RangoIndice(offset_c+1,offset_c+getNumCols()); }

//! @brief Devuelve verdadero si está vacía
bool  BaseRefCajaTritriz::Empty(void) const
  { return (Size() == 0); }
