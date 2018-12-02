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
//ConstantILayerConstRef.h 

#ifndef CONSTANTILAYERCONSTREF_H
#define CONSTANTILAYERCONSTREF_H

#include "Array3dRange.h"


//! @ingroup arrays3d
//
//! @brief Reference to a layer of the array which points have
//! constant I index.
template <class ARRAY_3D>
class ConstantILayerConstRef: public Array3dBoxConstRef<ARRAY_3D>
  {
  public:
    typedef typename Array3dBoxConstRef<ARRAY_3D>::const_reference const_reference;

    explicit ConstantILayerConstRef(const ARRAY_3D &m,const size_t &iLayer=1,const size_t &f= 1,const size_t &c= 1);
    ConstantILayerConstRef(const ARRAY_3D &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstantILayerConstRef(const ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range);
    inline virtual ~ConstantILayerConstRef(void) {}
    virtual const_reference operator()(size_t iRow=1,size_t col=1) const
      { return Array3dBoxConstRef<ARRAY_3D>::operator()(1,iRow,col); }
  };

template<class ARRAY_3D>
ConstantILayerConstRef<ARRAY_3D>::ConstantILayerConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f,const size_t &c)
  : Array3dBoxConstRef<ARRAY_3D>(t,Array3dRange(iLayer,RangoIndice(f,t.getNumberOfRows()),RangoIndice(c,t.getNumberOfColumns()))) {}

template<class ARRAY_3D>
ConstantILayerConstRef<ARRAY_3D>::ConstantILayerConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f1,const size_t &c1,const size_t &f2,const size_t &c2)
  : Array3dBoxConstRef<ARRAY_3D>(t,Array3dRange(iLayer,RangoIndice(f1,f2),RangoIndice(c1,c2))) {}

template<class ARRAY_3D>
ConstantILayerConstRef<ARRAY_3D>::ConstantILayerConstRef(const ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range)
  : Array3dBoxConstRef<ARRAY_3D>(t,iLayer,row_range,column_range) {}

#endif
