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



// GEOM_FT neutro_suma(const GEOM_FT &)
//   { return double_to_FT(0.0); }
// GEOM_FT neutro_producto(const GEOM_FT &)
//   { return double_to_FT(1.0); }
GEOM_FT Abs(const matriz_FT &m)
  { return m.Abs(); }

matriz_FT::matriz_FT(void)
  : matrizZ<GEOM_FT>(1,1) {}
matriz_FT::matriz_FT(size_type rows,size_type cols)
  : matrizZ<GEOM_FT>(rows,cols) {}
matriz_FT::matriz_FT(size_type rows,size_type cols,GEOM_FT val)
  : matrizZ<GEOM_FT>(rows,cols,val) {}
matriz_FT::matriz_FT(const matriz_FT &orig,size_t f1, size_t c1, size_t f2, size_t c2)
  : matrizZ<GEOM_FT>(f2-f1+1,c2-c1+1)
  {
    orig.check_get_caja(f1,c1,f2,c2);
    for(register size_t i=1;i<=n_rows;i++)
      for(register size_t j=1;j<=n_columns;j++)
        (*this)(i,j)= orig(i+f1-1,j+c1-1);
  }

matriz_FT matriz_FT::GetCaja(size_t f1, size_t c1, size_t f2, size_t c2) const
  { return matriz_FT(*this,f1,c1,f2,c2); }
matriz_FT matriz_FT::getRow(size_t iRow) const
  { return GetCaja(iRow,1,iRow,n_columns); }
matriz_FT matriz_FT::getColumn(size_t col) const
  { return GetCaja(1,col,n_rows,col); }

matriz_FT matriz_FT::GetTrn(void) const
  { return traspuesta(*this); }

//! @brief Return the matrix recíproca de la being passed as parameter.
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


//! @brief Return the matrix identidad de f rows y f columns.
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

//! @brief Return la traspuesta de la being passed as parameter.
matriz_FT traspuesta(const matriz_FT &m)
  { 
    matriz_FT retval(m);
    retval.Trn();
    return retval;
  }

//! @brief Producto tensorial de dos tensores de primer orden.
//! -u: row vector.
//! -v: column vector.
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

//! @brief Divides the components of each row of the matrix by the norm
//! of such row.
void NormalizeRows(matriz_FT &m)
  {
    const size_t n_rows= m.getNumberOfRows(),n_columns= m.getNumberOfColumns();
    for(size_t i=1;i<=n_rows;i++)
      {
        const GEOM_FT row_norm= ::Abs(m.getRow(i));
        if(row_norm>0)
          for(size_t j=1;j<=n_columns;j++)
	    m(i,j)/= row_norm;
        else
	  std::cerr << "NormalizeRows; the row: " << i
		    << " has zero norm." << std::endl;
      }
  }

//! @brief Return the matrix normalizada de la being passed as parameter.
matriz_FT Normaliza(const matriz_FT &m)
  {
    matriz_FT retval(m);
    Normaliza(retval);
    return retval;
  }

//! @brief Return the row-normalized matrix de la being passed as parameter.
matriz_FT NormalizeRows(const matriz_FT &m)
  {
    matriz_FT retval(m);
    NormalizeRows(retval);
    return retval;
  }

matrizZ<double> to_double(const matriz_FT &m)
  {
    const size_t n_rows= m.getNumberOfRows(),n_columns= m.getNumberOfColumns();
    m_double retval(n_rows,n_columns);
    for(register size_t i= 1;i<=n_rows;i++)
      for(register size_t j= 1;j<=n_columns;j++)
	retval(i,j)= m(i,j);
    return retval;
  }

matriz_FT from_double(const matrizZ<double> &m)
  {
    const size_t n_rows= m.getNumberOfRows(),n_columns= m.getNumberOfColumns();
    matriz_FT retval(n_rows,n_columns);
    for(register size_t i= 1;i<=n_rows;i++)
      for(register size_t j= 1;j<=n_columns;j++)
	retval(i,j)= double_to_FT(m(i,j));
    return retval;
  }


