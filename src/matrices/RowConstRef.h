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
//RowConstRef.h 

#ifndef ROWCONSTREF_H
#define ROWCONSTREF_H

#include "BoxConstRef.h"

//! @brief Reference to a matrix row.
template <class MAT>
class RowConstRef: public BoxConstRef<MAT>
  {
  public:
    typedef typename BoxConstRef<MAT>::const_reference const_reference;

    RowConstRef(const MAT &m,const size_t &f= 1,const size_t &c= 1);
    RowConstRef(const MAT &m,const size_t &,const size_t &,const size_t &);
    RowConstRef(const MAT &mat,const size_t &,const RangoIndice &);
    virtual const_reference operator()(size_t col) const
      { return BoxConstRef<MAT>::operator()(1,col); }
  };

template<class MAT>
RowConstRef<MAT>::RowConstRef(const MAT &mat,const size_t &f,const size_t &c)
  : BoxConstRef<MAT>(mat,f,c,f,mat.getNumberOfColumns())
  {}

template<class MAT>
RowConstRef<MAT>::RowConstRef(const MAT &mat,const size_t &f,const size_t &c1,const size_t &c2)
  : BoxConstRef<MAT>(mat,f,RangoIndice(c1,c2))
  {}

template<class MAT>
RowConstRef<MAT>::RowConstRef(const MAT &mat,const size_t &f,const RangoIndice &column_range)
  : BoxConstRef<MAT>(mat,f,column_range)
  {}

#endif
