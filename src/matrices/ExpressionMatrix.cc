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
//ExpressionMatrix.cc

#include "ExpressionMatrix.h"

ExpressionMatrix::ExpressionMatrix(const m_double &m)
  : expression_matrix(m.getNumberOfRows(),m.getNumberOfColumns())
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        (*this)(i,j)= ExprAlgebra(m(i,j));
  }
void ExpressionMatrix::eval(void)
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        (*this)(i,j).eval();
  }
void ExpressionMatrix::eval(const char *palabra,const ExprAlgebra &a)
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        (*this)(i,j).eval(palabra,a);
  }
void ExpressionMatrix::eval(const char *palabra,const double &d)
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        (*this)(i,j).eval(palabra,d);
  }
ExpressionMatrix ExpressionMatrix::Eval(void) const
  {
    ExpressionMatrix retval(*this);
    retval.eval();
    return retval;
  }
ExpressionMatrix ExpressionMatrix::Eval(const char *palabra,const ExprAlgebra &a)
  {
    ExpressionMatrix retval(*this);
    retval.eval(palabra,a);
    return retval;
  }
ExpressionMatrix ExpressionMatrix::Eval(const char *palabra,const double &d)
  {
    ExpressionMatrix retval(*this);
    retval.eval(palabra,d);
    return retval;
  }
bool ExpressionMatrix::Evaluable(void) const
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        if(!(*this)(i,j).Evaluable())
          return false;
    return true;
  }
m_double ExpressionMatrix::ToNum(void) const
  {
    m_double retval(n_rows,n_columns,0.0);
    if(!Evaluable())
      std::cerr << "ExpressionMatrix::" << __FUNCTION__
	        << " can't eval the matrix expression." << std::endl;
    else
      for(size_type i=1;i<=n_rows;i++)
        for(size_type j=1;j<=n_columns;j++)
          retval(i,j)= (*this)(i,j).ToNum();
    return retval;  
  }
m_double ExpressionMatrix::ToNum(const char *palabra,const double &d) const
  {
    m_double retval(n_rows,n_columns,0.0);
    if(!Evaluable())
      std::cerr << "ExpressionMatrix::" << __FUNCTION__
	        << " can't eval the matrix expression." << std::endl;
    else
      for(size_type i=1;i<=n_rows;i++)
        for(size_type j=1;j<=n_columns;j++)
          retval(i,j)= (*this)(i,j).ToNum(palabra,d);
    return retval;  
  }
ExpressionMatrix &ExpressionMatrix::Trn(void)
  {
    expression_matrix::Trn();
    return *this;
  }
ExpressionMatrix ExpressionMatrix::GetTrn(void) const
  {
    ExpressionMatrix m= *this;
    m.Trn();
    return m;
  }
ExpressionMatrix &ExpressionMatrix::operator*=(const double &d)
  {
    size_type i,sz= size();      
    for(i= 0;i<sz;i++)
      (*this)[i]*= ExprAlgebra(d);
    return *this;
  }
ExpressionMatrix &ExpressionMatrix::operator*=(const ExpressionMatrix &m)
  {
    *this= (*this)*m;
    return *this;
  }
ExpressionMatrix operator*(const ExpressionMatrix &m1,const ExpressionMatrix &m2)
  {
    ExpressionMatrix producto(m1.n_rows,m2.n_columns);
    if (m1.n_columns != m2.n_rows)
      {
        std::cerr << "Matrices de dimensiones incompatibles en producto." << std::endl;
        std::cerr << "  m1= " << m1 << std::endl;
        std::cerr << "  m2= " << m2 << std::endl;
        return producto;
      }
    ExpressionMatrix::size_type i=1,j=1;
    for (i= 1;i<=m1.n_rows;i++)
      for (j= 1;j<=m2.n_columns;j++)
        producto(i,j)= dot(m1.getRow(i),m2.getColumn(j));
    return producto;
  }




//! @brief Converts a string (i.e.: [[1.0+x^2,0.0][0.0,1.0-x]]) into
//! a matrix.
ExpressionMatrix string_to_expression_matrix(const std::string &str)
  {
    ExpressionMatrix retval(1,1);
    retval.Input(str);
    return retval;
  }

