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

#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Reference to a layer de la tritriz which points have
//! constant J index.
template <class TRITRIZ>
class ConstantJLayerVarRef: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit ConstantJLayerVarRef(TRITRIZ &m,const size_t &iLayer=1,const size_t &f= 1,const size_t &c= 1);
    ConstantJLayerVarRef(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstantJLayerVarRef(TRITRIZ &t,const RangoIndice &layer_range,const size_t &f,const RangoIndice &column_range);
    inline virtual ~ConstantJLayerVarRef(void) {}
    size_t getRowIndex(void) const
      { return this->offset_f+1; }
    virtual const_reference operator()(size_t iLayer=1,size_t col=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(iLayer,1,col); }
    virtual reference operator()(size_t iLayer=1,size_t col=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(iLayer,1,col); }
  };

template<class TRITRIZ>
ConstantJLayerVarRef<TRITRIZ>::ConstantJLayerVarRef(TRITRIZ &t,const size_t &iLayer,const size_t &f,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(iLayer,t.getNumberOfLayers()),f,RangoIndice(c,t.getNumberOfColumns()))) {}

template<class TRITRIZ>
ConstantJLayerVarRef<TRITRIZ>::ConstantJLayerVarRef(TRITRIZ &t,const size_t &f,const size_t &iLayer1,const size_t &c1,const size_t &iLayer2,const size_t &c2)
  : VarRefCajaTritriz<TRITRIZ>(t,RangoIndice(iLayer1,iLayer2),f,RangoIndice(c1,c2)) {}

template<class TRITRIZ>
ConstantJLayerVarRef<TRITRIZ>::ConstantJLayerVarRef(TRITRIZ &t,const RangoIndice &layer_range,const size_t &f,const RangoIndice &column_range)
  : VarRefCajaTritriz<TRITRIZ>(t,layer_range,f,column_range) {}

#endif
