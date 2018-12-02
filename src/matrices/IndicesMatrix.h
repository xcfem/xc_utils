//----------------------------------------------------------------------------
//  biblioteca bibXCLcmd; bilioteca de comandos para el intérprete del lenguaje
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
//IndicesMatrix.h
//Matrix of indices

#ifndef INDICESMATRIX_H
#define INDICESMATRIX_H

#include "xc_utils/src/matrices/TMatrix.h"
#include "xc_utils/src/matrices/vectorZ.h"
#include "m_int.h"

typedef vectorZ<int> VIndices;

//! @ingroup Matrices
//
//! @brief Matrix of indices. I'ts used to express a
//! set of positions by its indices, i. e. :
//! [[1,2][2,2][3,2]
//!  [1,1][2,1][2,3]]
class IndicesMatrix: public TMatrix<VIndices,std::vector<VIndices > >
  {
  public:
    typedef TMatrix<VIndices,std::vector<VIndices > > m_indices;
  protected:
    IndicesMatrix(const IndicesMatrix &mp, size_t &f1, size_t &c1, size_t &f2, size_t &c2);
  public:
    IndicesMatrix(const size_t &f=1,const size_t &c=1,const VIndices &p= VIndices());
    IndicesMatrix(const m_int &,const std::vector<VIndices > &);

    IndicesMatrix getBox(size_t f1, size_t c1, size_t f2, size_t c2) const;
    IndicesMatrix getRow(size_t ) const;
    IndicesMatrix getColumn(size_t ) const;

    void Offset(const VIndices &);
  };


#endif
