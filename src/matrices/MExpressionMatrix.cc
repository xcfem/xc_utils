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
//MExpressionMatrix.cc

#include "MExpressionMatrix.h"
#include "MMatrix.h"

void MExpressionMatrix::eval(void)
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        (*this)(i,j).eval();
  }
void MExpressionMatrix::eval(const char *palabra,const ExprAlgebra &a)
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        (*this)(i,j).eval(palabra,a);
  }
void MExpressionMatrix::eval(const char *palabra,const double &d)
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        (*this)(i,j).eval(palabra,d);
  }

MExpressionMatrix MExpressionMatrix::Eval(void) const
  {
    MExpressionMatrix retval(*this);
    retval.eval();
    return retval;
  }
MExpressionMatrix MExpressionMatrix::Eval(const char *palabra,const ExprAlgebra &a)
  {
    MExpressionMatrix retval(*this);
    retval.eval(palabra,a);
    return retval;
  }
MExpressionMatrix MExpressionMatrix::Eval(const char *palabra,const double &d)
  {
    MExpressionMatrix retval(*this);
    retval.eval(palabra,d);
    return retval;
  }
bool MExpressionMatrix::Evaluable(void) const
  {
    for(size_type i=1;i<=n_rows;i++)
      for(size_type j=1;j<=n_columns;j++)
        if(!(*this)(i,j).Evaluable())
          return false;
    return true;
  }
MMatrix MExpressionMatrix::ToNum(void) const
  {
    MMatrix retval(n_rows,n_columns);
    if(!Evaluable())
      std::cerr << "ExpressionMatrix::" << __FUNCTION__
	        << "cant evaluate the expression matrix" << std::endl;
    else
      for(size_type i=1;i<=n_rows;i++)
        for(size_type j=1;j<=n_columns;j++)
          retval(i,j)= (*this)(i,j).ToNum();
    return retval;
  }
MMatrix MExpressionMatrix::ToNum(const char *palabra,const double &d) const
  {
    MMatrix retval(n_rows,n_columns);
    if(!Evaluable())
      std::cerr << "ExpressionMatrix::" << __FUNCTION__
	        << "cant evaluate the expression matrix" << std::endl;
    else
      for(size_type i=1;i<=n_rows;i++)
        for(size_type j=1;j<=n_columns;j++)
          retval(i,j)= (*this)(i,j).ToNum(palabra,d);
    return retval;
  }
MExpressionMatrix &MExpressionMatrix::operator*=(const ExpressionMatrix &m)
  {
    m_expression_matrix::operator*=(m);
    return *this;
  }
MExpressionMatrix &MExpressionMatrix::operator*=(const double &d)
  {
    size_type i,sz= size();      
    for(i= 0;i<sz;i++)
      (*this)[i]*=d;
    return *this;
  }
MExpressionMatrix &MExpressionMatrix::operator*=(const MExpressionMatrix &m)
  {
    m_expression_matrix::operator*=(m);
    return *this;
  }
MExpressionMatrix operator*(const MExpressionMatrix &m1,const MExpressionMatrix &m2)
  {
    MExpressionMatrix producto(m1);
    producto*=(m2);
    return producto;
  }

MExpressionMatrix operator+(const MExpressionMatrix &m1,const MExpressionMatrix &m2)
  {
    MExpressionMatrix retval(m1);
    retval+=m2;
    return retval;
  }

MExpressionMatrix operator-(const MExpressionMatrix &m1,const MExpressionMatrix &m2)
  {
    MExpressionMatrix retval(m1);
    retval-=m2;
    return retval;
  }

MExpressionMatrix operator*(const MExpressionMatrix &m,const double &d)
  {
    MExpressionMatrix retval(m);
    retval*=d;
    return retval;
  }

MExpressionMatrix operator*(const ExpressionMatrix &m,const MExpressionMatrix &mM)
  {
    MExpressionMatrix retval(mM); retval*=m;
    return retval;
  }

