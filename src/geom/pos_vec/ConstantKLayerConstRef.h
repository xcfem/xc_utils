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

#include "Array3dRange.h"


//! @ingroup GEOM
//
//! @brief Reference to a layer of the array which points
//! have constant K index.
template <class ARRAY_3D>
class ConstantKLayerConstRef: public ConstRefCajaArray3d<ARRAY_3D>
  {
  public:
    typedef typename ConstRefCajaArray3d<ARRAY_3D>::const_reference const_reference;

    explicit ConstantKLayerConstRef(const ARRAY_3D &m,const size_t &c=1,const size_t &iLayer= 1,const size_t &f= 1);
    ConstantKLayerConstRef(const ARRAY_3D &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstantKLayerConstRef(const ARRAY_3D &t,const RangoIndice &column_range,const RangoIndice &row_range,const size_t &c);
    inline virtual ~ConstantKLayerConstRef(void) {}
    virtual const_reference operator()(size_t iLayer=1,size_t iRow=1) const
      { return ConstRefCajaArray3d<ARRAY_3D>::operator()(iLayer,iRow,1); }
  };

template<class ARRAY_3D>
ConstantKLayerConstRef<ARRAY_3D>::ConstantKLayerConstRef(const ARRAY_3D &t,const size_t &c,const size_t &iLayer,const size_t &f)
  : ConstRefCajaArray3d<ARRAY_3D>(t,Array3dRange(RangoIndice(iLayer,t.getNumberOfLayers()),RangoIndice(f,t.getNumberOfRows()),c)) {}

template<class ARRAY_3D>
ConstantKLayerConstRef<ARRAY_3D>::ConstantKLayerConstRef(const ARRAY_3D &t,const size_t &c,const size_t &iLayer1,const size_t &f1,const size_t &iLayer2,const size_t &f2)
  : ConstRefCajaArray3d<ARRAY_3D>(t,Array3dRange(RangoIndice(iLayer1,iLayer2),RangoIndice(f1,f2),c)) {}

template<class ARRAY_3D>
ConstantKLayerConstRef<ARRAY_3D>::ConstantKLayerConstRef(const ARRAY_3D &t,const RangoIndice &column_range,const RangoIndice &row_range,const size_t &c)
  : ConstRefCajaArray3d<ARRAY_3D>(t,column_range,row_range,c)
  {}

#endif
