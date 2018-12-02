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
//ConstantJLayerVarRef.h 

#ifndef CONSTANTJLAYERVARREF_H
#define CONSTANTJLAYERVARREF_H

#include "Array3dRange.h"


//! @ingroup arrays3d
//
//! @brief Reference to a layer of the array which points have
//! constant J index.
template <class ARRAY_3D>
class ConstantJLayerVarRef: public Array3dBoxVarRef<ARRAY_3D>
  {
  public:
    typedef typename Array3dBoxVarRef<ARRAY_3D>::const_reference const_reference;
    typedef typename Array3dBoxVarRef<ARRAY_3D>::reference reference;

    explicit ConstantJLayerVarRef(ARRAY_3D &m,const size_t &iLayer=1,const size_t &f= 1,const size_t &c= 1);
    ConstantJLayerVarRef(ARRAY_3D &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstantJLayerVarRef(ARRAY_3D &t,const RangoIndice &layer_range,const size_t &f,const RangoIndice &column_range);
    inline virtual ~ConstantJLayerVarRef(void) {}
    size_t getRowIndex(void) const
      { return this->offset_f+1; }
    virtual const_reference operator()(size_t iLayer=1,size_t col=1) const
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(iLayer,1,col); }
    virtual reference operator()(size_t iLayer=1,size_t col=1)
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(iLayer,1,col); }
  };

template<class ARRAY_3D>
ConstantJLayerVarRef<ARRAY_3D>::ConstantJLayerVarRef(ARRAY_3D &t,const size_t &iLayer,const size_t &f,const size_t &c)
  : Array3dBoxVarRef<ARRAY_3D>(t,Array3dRange(RangoIndice(iLayer,t.getNumberOfLayers()),f,RangoIndice(c,t.getNumberOfColumns()))) {}

template<class ARRAY_3D>
ConstantJLayerVarRef<ARRAY_3D>::ConstantJLayerVarRef(ARRAY_3D &t,const size_t &f,const size_t &iLayer1,const size_t &c1,const size_t &iLayer2,const size_t &c2)
  : Array3dBoxVarRef<ARRAY_3D>(t,RangoIndice(iLayer1,iLayer2),f,RangoIndice(c1,c2)) {}

template<class ARRAY_3D>
ConstantJLayerVarRef<ARRAY_3D>::ConstantJLayerVarRef(ARRAY_3D &t,const RangoIndice &layer_range,const size_t &f,const RangoIndice &column_range)
  : Array3dBoxVarRef<ARRAY_3D>(t,layer_range,f,column_range) {}

#endif
