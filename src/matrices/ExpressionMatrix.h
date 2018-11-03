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
//ExpressionMatrix.h
//Matrix of expressions

#ifndef EXPRESSIONMATRIX_H
#define EXPRESSIONMATRIX_H

#include "ZMatrix.h"
#include "xc_utils/src/functions/algebra/ExprAlgebra.h"
#include "m_double.h"

typedef ZMatrix<ExprAlgebra> expression_matrix;

class ExpressionMatrix: public expression_matrix
  {
    friend class MExpressionMatrix;

    void eval(void);
    void eval(const char *palabra,const ExprAlgebra &a);
    void eval(const char *palabra,const double &d);
  public:
    ExpressionMatrix(size_type n_rows=1,size_type cols=1,const ExprAlgebra &val=ExprAlgebra())
      : expression_matrix(n_rows,cols,val) {}
    ExpressionMatrix(const ExpressionMatrix &otra) : expression_matrix(otra) {}
    ExpressionMatrix &operator=(const ExpressionMatrix &m)
      {
	expression_matrix::operator=(m);
        return *this;
      }
    explicit ExpressionMatrix(const m_double &m);
    static LexAlgebra &LexA(void)
      { return ExprAlgebra::LexA(); }
    ExpressionMatrix &Trn(void);
    ExpressionMatrix GetTrn(void) const;
    bool Evaluable(void) const;
    ExpressionMatrix Eval(void) const;
    ExpressionMatrix Eval(const char *palabra,const ExprAlgebra &a);
    ExpressionMatrix Eval(const char *palabra,const double &d);
    m_double ToNum(void) const;
    m_double ToNum(const char *palabra,const double &d) const;
    ExpressionMatrix &operator*=(const double &d);
    ExpressionMatrix &operator*=(const ExpressionMatrix &m);
    friend ExpressionMatrix operator*(const ExpressionMatrix &m1,const ExpressionMatrix &m2);
    friend ExpressionMatrix operator*(const m_double &m,const ExpressionMatrix &mE)
      {
        ExpressionMatrix retval= mE*ExpressionMatrix(m);
        return retval;
      }
    friend ExpressionMatrix operator*(const ExpressionMatrix &mE, const m_double &m)
      { return m*mE; }
  };


ExpressionMatrix string_to_expression_matrix(const std::string &str);

#endif
