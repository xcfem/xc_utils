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
//MExpressionMatrix.h
//Matrix of matrices of expressions (or by boxes)
#ifndef MEXPRESSIONMATRIX_H
#define MEXPRESSIONMATRIX_H

#include "ExpressionMatrix.h"
#include "matrix_by_boxes.h"

class MMatrix;
class ExprAlgebra;

typedef MatrixByBoxes<ExpressionMatrix> m_expression_matrix;

class MExpressionMatrix: public m_expression_matrix
  {
    void eval(void);
    void eval(const char *palabra,const ExprAlgebra &a);
    void eval(const char *palabra,const double &d);
  public:
    MExpressionMatrix(void) : m_expression_matrix(1,1) {}
    MExpressionMatrix(size_type n_rows,size_type cols) : m_expression_matrix(n_rows,cols) {}
    MExpressionMatrix(size_type n_rows,size_type cols,const ExpressionMatrix &val)
      : m_expression_matrix(n_rows,cols,val) {}
    MExpressionMatrix(const MExpressionMatrix &otra) : m_expression_matrix(otra) {}
    MExpressionMatrix& operator=(const MExpressionMatrix &m)
      {
	m_expression_matrix::operator=(m);
        return *this;
      }
    bool Evaluable(void) const;
    MExpressionMatrix Eval(void) const;
    MExpressionMatrix Eval(const char *palabra,const ExprAlgebra &a);
    MExpressionMatrix Eval(const char *palabra,const double &d);
    MMatrix ToNum(void) const;
    MMatrix ToNum(const char *palabra,const double &d) const;
    MExpressionMatrix &operator*=(const ExpressionMatrix &m);
    MExpressionMatrix &operator*=(const double &d);
    MExpressionMatrix &operator*=(const MExpressionMatrix &m);

    friend MExpressionMatrix operator+(const MExpressionMatrix &m1,const MExpressionMatrix &m2);
    friend MExpressionMatrix operator-(const MExpressionMatrix &m1,const MExpressionMatrix &m2);
    friend MExpressionMatrix operator*(const MExpressionMatrix &m,const double &d)
;
    friend MExpressionMatrix operator*(const double &d,const MExpressionMatrix &m)
      { return m*d; }
    friend MExpressionMatrix operator*(const MExpressionMatrix &m1,const MExpressionMatrix &m2);
    friend MExpressionMatrix operator*(const ExpressionMatrix &m,const MExpressionMatrix &mM);
    friend MExpressionMatrix operator*(const MExpressionMatrix &mM, const ExpressionMatrix &m)
      { return m*mM; }
  };


#endif
