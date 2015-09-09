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
//matriz_FT.cc

#include "xc_basic/src/util/matem.h"
#include "matriz_FT.h"
#include "xc_basic/src/matrices/m_double.h"
#include "tipos_cgal.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/base/any_const_ptr.h"

// GEOM_FT neutro_suma(const GEOM_FT &)
//   { return double_to_FT(0.0); }
// GEOM_FT neutro_producto(const GEOM_FT &)
//   { return double_to_FT(1.0); }
GEOM_FT Abs(const matriz_FT &m)
  { return m.Abs(); }

matriz_FT::matriz_FT(void)
  : matrizZ<GEOM_FT>(1,1) {}
matriz_FT::matriz_FT(size_type filas,size_type cols)
  : matrizZ<GEOM_FT>(filas,cols) {}
matriz_FT::matriz_FT(size_type filas,size_type cols,GEOM_FT val)
  : matrizZ<GEOM_FT>(filas,cols,val) {}
matriz_FT::matriz_FT(const matriz_FT &orig,size_t f1, size_t c1, size_t f2, size_t c2)
  : matrizZ<GEOM_FT>(f2-f1+1,c2-c1+1)
  {
    orig.check_get_caja(f1,c1,f2,c2);
    for(register size_t i=1;i<=fls;i++)
      for(register size_t j=1;j<=cls;j++)
        (*this)(i,j)= orig(i+f1-1,j+c1-1);
  }

matriz_FT matriz_FT::GetCaja(size_t f1, size_t c1, size_t f2, size_t c2) const
  { return matriz_FT(*this,f1,c1,f2,c2); }
matriz_FT matriz_FT::GetFila(size_t fila) const
  { return GetCaja(fila,1,fila,cls); }
matriz_FT matriz_FT::GetCol(size_t col) const
  { return GetCaja(1,col,fls,col); }

matriz_FT matriz_FT::GetTrn(void) const
  { return traspuesta(*this); }

//! @brief Devuelve la matriz recíproca de la que se pasa como parámetro.
matriz_FT operator-(const matriz_FT &m)
  {
    matriz_FT neg(m);
    neg.Neg();
    return neg;
  }

matriz_FT operator+(const matriz_FT &a,const matriz_FT &b)
  {
    matriz_FT retval(a);
    retval+=b;
    return retval;
  }

matriz_FT operator-(const matriz_FT &a,const matriz_FT &b)
  {
    matriz_FT retval(a);
    retval-=b;
    return retval;
  }

//!  @brief Producto de matrices.
matriz_FT operator*(const matriz_FT &a,const matriz_FT &b)
  {
    matriz_FT retval(a);
    retval*=b;
    return retval;
  }

//!  @brief Producto por un escalar.
matriz_FT operator*(const GEOM_FT &d,const matriz_FT &a)
  {
    matriz_FT retval(a);
    retval*=d;
    return retval;
  }

//!  @brief Producto por un escalar.
matriz_FT operator*(const matriz_FT &a,const GEOM_FT &d)
  { return d*a; }

//!  @brief Producto vectorial. ¡Ojo! está escrito para vectores de dimensión 3 xxx.
matriz_FT operator^(const matriz_FT &v1,const matriz_FT &v2)
  { return prod_vectorial(v1,v2); }


//! @brief Devuelve la matriz identidad de f filas y f columnas.
matriz_FT identidad(const size_t &f)
  {
    matriz_FT retval(f,f);
    retval.Idn();
    return retval;
  }

matriz_FT identidad(const matriz_FT &m)
  {
    matriz_FT retval(m);
    retval.Idn();
    return retval;
  }

//! @brief Devuelve la traspuesta de la que se pasa como parámetro.
matriz_FT traspuesta(const matriz_FT &m)
  { 
    matriz_FT retval(m);
    retval.Trn();
    return retval;
  }

//! @brief Producto tensorial de dos tensores de primer orden.
//! -u: vector fila.
//! -v: vector columna.
matriz_FT prod_tensor(const matriz_FT &u,const matriz_FT &v)
  {
    const size_t sz_u= u.size();
    const size_t sz_v= v.size();
    matriz_FT retval(sz_u,sz_v);
    for(size_t i=1;i<=sz_u;i++)
      for(size_t j=1;j<=sz_v;j++)
        retval(i,j)= u[i-1]*v[j-1];
    return retval;
  }

//! @brief Divide los elementos de la matriz por su modulo.
void Normaliza(matriz_FT &m)
  {
    const GEOM_FT vabs= ::Abs(m);
    if(vabs>0) m*= 1/vabs;
  }

//! @brief Divide los elementos cada fila de la matriz por el modulo de dicha fila.
void NormalizaFilas(matriz_FT &m)
  {
    const size_t fls= m.getNumFilas(),cls= m.getNumCols();
    for(size_t i=1;i<=fls;i++)
      {
        const GEOM_FT mod_fila= ::Abs(m.GetFila(i));
        if(mod_fila>0)
          for(size_t j=1;j<=cls;j++)
	    m(i,j)/= mod_fila;
        else
	  std::cerr << "NormalizaFilas; la fila: " << i << " tiene módulo nulo." << std::endl;
      }
  }

//! @brief Devuelve la matriz normalizada de la que se pasa como parámetro.
matriz_FT Normaliza(const matriz_FT &m)
  {
    matriz_FT retval(m);
    Normaliza(retval);
    return retval;
  }

//! @brief Devuelve la matriz normalizada por filas de la que se pasa como parámetro.
matriz_FT NormalizaFilas(const matriz_FT &m)
  {
    matriz_FT retval(m);
    NormalizaFilas(retval);
    return retval;
  }

matrizZ<double> to_double(const matriz_FT &m)
  {
    const size_t fls= m.getNumFilas(),cls= m.getNumCols();
    m_double retval(fls,cls);
    for(register size_t i= 1;i<=fls;i++)
      for(register size_t j= 1;j<=cls;j++)
	retval(i,j)= m(i,j);
    return retval;
  }

matriz_FT from_double(const matrizZ<double> &m)
  {
    const size_t fls= m.getNumFilas(),cls= m.getNumCols();
    matriz_FT retval(fls,cls);
    for(register size_t i= 1;i<=fls;i++)
      for(register size_t j= 1;j<=cls;j++)
	retval(i,j)= double_to_FT(m(i,j));
    return retval;
  }


