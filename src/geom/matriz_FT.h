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
//matriz_FT.h

#ifndef MATRIZ_FT_H
#define MATRIZ_FT_H

#include "xc_basic/src/matrices/matrizZ.h"
#include "tipos_cgal.h"



//Elementos neutros para la suma y el producto.
GEOM_FT neutro_suma(const GEOM_FT &);
GEOM_FT neutro_producto(const GEOM_FT &);


//! @ingroup GEOM
//
//! @brief Matriz.
class matriz_FT: public matrizZ<GEOM_FT>
  {
    matriz_FT(const matriz_FT &orig,size_t f1, size_t c1, size_t f2, size_t c2);
  public:
    matriz_FT(void);
    matriz_FT(size_type rows,size_type cols);
    matriz_FT(size_type rows,size_type cols,GEOM_FT val);
    matriz_FT GetCaja(size_t f1, size_t c1, size_t f2, size_t c2) const;
    matriz_FT getRow(size_t iRow) const;
    matriz_FT getColumn(size_t col) const;
    matriz_FT GetTrn(void) const;
    friend matriz_FT operator+(const matriz_FT &a,const matriz_FT &b);
    friend matriz_FT operator-(const matriz_FT &a,const matriz_FT &b);
    friend matriz_FT operator*(const matriz_FT &a,const matriz_FT &b);
    friend matriz_FT operator*(const GEOM_FT &d,const matriz_FT &a);
    friend matriz_FT operator*(const matriz_FT &a,const GEOM_FT &d);
    friend matriz_FT operator^(const matriz_FT &,const matriz_FT &v2);
  };

matriz_FT identidad(const size_t &f);
matriz_FT identidad(const matriz_FT &m);
matriz_FT traspuesta(const matriz_FT &m);


//Producto tensorial de dos tensores de primer orden.
matriz_FT prod_tensor(const matriz_FT &u,const matriz_FT &v);

//Operador producto tensorial.
inline matriz_FT operator&(const matriz_FT &u,const matriz_FT &v)
  { return prod_tensor(u,v); }

void Normaliza(matriz_FT &m);
void NormalizeRows(matriz_FT &m);
matriz_FT Normaliza(const matriz_FT &m);

matriz_FT operator-(const matriz_FT &m);

matrizZ<double> to_double(const matriz_FT &m);
matriz_FT from_double(const matrizZ<double> &m);

namespace boost
  {
    class any;
  }

#endif
