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
//ColumnConstRef.h 

#ifndef COLUMNCONSTREF_H
#define COLUMNCONSTREF_H

#include "BoxConstRef.h"

//! @brief Constant reference to a column of a matrix.
template <class MAT>
class ColumnConstRef: public BoxConstRef<MAT>
  {
  public:
    typedef typename BoxConstRef<MAT>::const_reference const_reference;

    ColumnConstRef(const MAT &m,const size_t &c= 1,const size_t &f= 1);
    ColumnConstRef(const MAT &m,const size_t &,const size_t &,const size_t &);
    ColumnConstRef(const MAT &mat,const RangoIndice &,const size_t &);
    virtual const_reference operator()(size_t iRow) const
      { return BoxConstRef<MAT>::operator()(iRow,1); }
  };

template<class MAT>
ColumnConstRef<MAT>::ColumnConstRef(const MAT &mat,const size_t &c,const size_t &f)
  : BoxConstRef<MAT>(mat,f,c,mat.getNumberOfRows(),c)
  {}

template<class MAT>
ColumnConstRef<MAT>::ColumnConstRef(const MAT &mat,const size_t &c,const size_t &f1,const size_t &f2)
  : BoxConstRef<MAT>(mat,f1,c,f2,c)
  {}

template<class MAT>
ColumnConstRef<MAT>::ColumnConstRef(const MAT &mat,const RangoIndice &row_range,const size_t &col)
  : BoxConstRef<MAT>(mat,row_range,col)
  {}

#endif
