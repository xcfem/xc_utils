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
//FuncPorPuntosR2_R.cc

#include "FuncPorPuntosR2_R.h"

//! @brief Devuelve la fila y columna del máximo.
FuncPorPuntosR2_R::filacol FuncPorPuntosR2_R::PosMax(void) const
  {
    filacol retval;
    retval.first= 1;
    retval.second= 1;
    const size_t fls= GetNumFilas();
    const size_t cls= GetNumCols();
    register double max= Valor(1,1);
    for(register size_t i=1;i<=fls;i++)
      for(register size_t j=1;j<=cls;j++)
        {
          const double tmp= Valor(i,j);
          if(max < tmp)
            {
              max= tmp;
              retval.first= i;
              retval.second= j;
            }
        }
    return retval;
  }
//! @brief Devuelve el valor máximo de los valores definidos.
double FuncPorPuntosR2_R::Max(void) const
  {
    const filacol fc= PosMax();
    return Valor(fc.first,fc.second);
  }
//! @brief Devuelve la posición del valor máximo de los valores definidos.
Pos2d FuncPorPuntosR2_R::PuntoMax(void) const
  {
    const filacol fc= PosMax();
    return Posicion(fc.first,fc.second);
  }
//! @brief Devuelve la fila y columna del mínimo.
FuncPorPuntosR2_R::filacol FuncPorPuntosR2_R::PosMin(void) const
  {
    filacol retval;
    retval.first= 1;
    retval.second= 1;
    const size_t fls= GetNumFilas();
    const size_t cls= GetNumCols();
    register double min= Valor(1,1);
    for(register size_t i=1;i<=fls;i++)
      for(register size_t j=1;j<=cls;j++)
        {
          const double tmp= Valor(i,j);
          if(min > tmp)
            {
              min= tmp;
              retval.first= i;
              retval.second= j;
            }
        }
    return retval;
  }
//! @brief Devuelve el valor mínimo de los valores definidos.
double FuncPorPuntosR2_R::Min(void) const
  {
    const filacol fc= PosMin();
    return Valor(fc.first,fc.second);
  }
//! @brief Devuelve la posición del valor mínimo de los valores definidos.
Pos2d FuncPorPuntosR2_R::PuntoMin(void) const
  {
    const filacol fc= PosMin();
    return Posicion(fc.first,fc.second);
  }
