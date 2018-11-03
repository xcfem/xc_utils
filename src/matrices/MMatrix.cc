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
//MMatrix.cc

#include "MMatrix.h"
#include "vcolM.h"

//! @brief Constructor.
//!
//! @param dim: Dimensiones de rows and columns (square matrix).
MMatrix::MMatrix(const std::vector<size_t> &dim)
  :  m_matrix(dim) {}

//! @brief Constructor.
//!
//! @param dim_rows: row dimension.
//! @param dim_columns: column dimension.
MMatrix::MMatrix(const std::vector<size_t> &dim_rows,const std::vector<size_t> &dim_columns)
  :  m_matrix(dim_rows,dim_columns) {}

//! @brief Operador *=
MMatrix &MMatrix::operator*=(const m_double &m)
  {
    m_matrix::operator*=(m);
    return *this;
  }

//! @brief Operador *=
MMatrix &MMatrix::operator*=(const double &d)
  {
    m_matrix::operator*=(d);
    return *this;
  }
//! @brief Operador *=
MMatrix &MMatrix::operator*=(const MMatrix &m)
  {
    m_matrix::operator*=(m);
    return *this;
  }

//! @brief Operador *=
MMatrix &MMatrix::operator*=(const vcolM &v)
  {
    m_matrix::operator*=((const MMatrix &)v);
    return *this;
  }

MMatrix operator*(const MMatrix &m1,const MMatrix &m2)
  {
    MMatrix producto(m1);
    producto*=m2;
    return producto;
  }

//! @brief Return the transposed matrix.
MMatrix MMatrix::GetTrn(void) const
  {
    MMatrix m= *this;
    m.Trn();
    return m;
  }

//! @brief Convert the argument matrix in a block matrix.
//!
//! @param dim_rows: row dimension.
//! @param dim_columns: column dimension.
//! @param a: matrix that will be converted.
MMatrix to_boxes(const std::vector<size_t> dim_rows,const std::vector<size_t> dim_columns,const m_double &a)
  {
    MMatrix retval(dim_rows,dim_columns);
    //Comprobamos dimensiones.
    assert(retval.getTotalNumberOfRows()==a.getNumberOfRows()); 
    assert(retval.getTotalNumberOfColumns()==a.getNumberOfColumns());

    const size_t n_rows= retval.getNumberOfRows();
    const size_t n_columns= retval.getNumberOfColumns();

    size_t row_box= 1; //Row where the box starts.
    size_t col_box= 1; //Column where the box starts.
    for(size_t i=1;i<=n_rows;i++)
      {
        col_box= 1;
        const size_t fbloque= dim_rows[i-1]; //Rows of i-th row.
        for(size_t j=1;j<=n_columns;j++)
          {
            const size_t cbloque= dim_columns[j-1]; //Columns of j-th column.
            retval(i,j)= a.getBox(row_box,col_box,row_box+fbloque-1,col_box+cbloque-1);
            col_box+=cbloque; //Next column.
          }
        row_box+=fbloque; //Next row.
      }
    return retval;
  }

//! @brief Convert the argument matrix in a block matrix.
//!
//! @param muestra: template matrix which blocks dimensions will be used
//! to define the blocks of the new matrix.
//! @param a: matrix that will be converted.
MMatrix to_boxes(const MMatrix &muestra,const m_double &a)
  {
    const std::vector<size_t> dim_rows= muestra.get_dim_rows();
    const std::vector<size_t> dim_columns= muestra.get_dim_columns();
    return to_boxes(dim_rows,dim_columns,a);
  }




