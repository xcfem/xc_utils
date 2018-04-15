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
//  Consulte los detalles DE LA LICENCIA PÚBLICA GENERAL GNU PARA OBTENER 
//  UNA INFORMACIÓN MÁS DETALLADA. 
//
// DEBERÍA HABER RECIBIDO UNA COPIA DE LA LICENCIA PÚBLICA GENERAL GNU 
// JUNTO A ESTE PROGRAMA. 
// EN CASO CONTRARIO, CONSULTE <HTTP://WWW.GNU.ORG/LICENSES/>.
//----------------------------------------------------------------------------
//CONSTANTKLAYERCONSTREF.H 

#ifndef CONSTANTKLAYERCONSTREF_H
#define CONSTANTKLAYERCONSTREF_H

#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Reference to a layer de la tritriz which points
//! have constant K index.
template <class TRITRIZ>
class ConstantKLayerConstRef: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit ConstantKLayerConstRef(const TRITRIZ &m,const size_t &c=1,const size_t &iLayer= 1,const size_t &f= 1);
    ConstantKLayerConstRef(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstantKLayerConstRef(const TRITRIZ &t,const RangoIndice &column_range,const RangoIndice &row_range,const size_t &c);
    inline virtual ~ConstantKLayerConstRef(void) {}
    virtual const_reference operator()(size_t iLayer=1,size_t iRow=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(iLayer,iRow,1); }
  };

template<class TRITRIZ>
ConstantKLayerConstRef<TRITRIZ>::ConstantKLayerConstRef(const TRITRIZ &t,const size_t &c,const size_t &iLayer,const size_t &f)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(iLayer,t.getNumberOfLayers()),RangoIndice(f,t.getNumberOfRows()),c)) {}

template<class TRITRIZ>
ConstantKLayerConstRef<TRITRIZ>::ConstantKLayerConstRef(const TRITRIZ &t,const size_t &c,const size_t &iLayer1,const size_t &f1,const size_t &iLayer2,const size_t &f2)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(iLayer1,iLayer2),RangoIndice(f1,f2),c)) {}

template<class TRITRIZ>
ConstantKLayerConstRef<TRITRIZ>::ConstantKLayerConstRef(const TRITRIZ &t,const RangoIndice &column_range,const RangoIndice &row_range,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,column_range,row_range,c)
  {}

#endif
