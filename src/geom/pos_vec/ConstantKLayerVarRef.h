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
//ConstantKLayerVarRef.h 

#ifndef CONSTANTKLAYERVARREF_H
#define CONSTANTKLAYERVARREF_H


//! @ingroup GEOM
//
//! @brief Reference to a layer of the array which points
//! have constant K index.
template <class ARRAY_3D>
class ConstantKLayerVarRef: public Array3dBoxVarRef<ARRAY_3D>
  {
  public:
    typedef typename Array3dBoxVarRef<ARRAY_3D>::const_reference const_reference;
    typedef typename Array3dBoxVarRef<ARRAY_3D>::reference reference;

    explicit ConstantKLayerVarRef(ARRAY_3D &m,const size_t &c=1,const size_t &iLayer= 1,const size_t &f= 1);
    ConstantKLayerVarRef(ARRAY_3D &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstantKLayerVarRef(ARRAY_3D &t,const RangoIndice &column_range,const RangoIndice &row_range,const size_t &c);
    inline virtual ~ConstantKLayerVarRef(void) {}
    size_t IndiceCol(void) const
      { return this->offset_c+1; }
    virtual const_reference operator()(size_t iLayer=1,size_t iRow=1) const
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(iLayer,iRow,1); }
    virtual reference operator()(size_t iLayer=1,size_t iRow=1)
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(iLayer,iRow,1); }
  };

template<class ARRAY_3D>
ConstantKLayerVarRef<ARRAY_3D>::ConstantKLayerVarRef(ARRAY_3D &t,const size_t &c,const size_t &iLayer,const size_t &f)
  : Array3dBoxVarRef<ARRAY_3D>(t,Array3dRange(RangoIndice(iLayer,t.getNumberOfLayers()),RangoIndice(f,t.getNumberOfRows()),c)) {}

template<class ARRAY_3D>
ConstantKLayerVarRef<ARRAY_3D>::ConstantKLayerVarRef(ARRAY_3D &t,const size_t &c,const size_t &iLayer1,const size_t &f1,const size_t &iLayer2,const size_t &f2)
  : Array3dBoxVarRef<ARRAY_3D>(t,Array3dRange(RangoIndice(iLayer1,iLayer2),RangoIndice(f1,f2),c)) {}

template<class ARRAY_3D>
ConstantKLayerVarRef<ARRAY_3D>::ConstantKLayerVarRef(ARRAY_3D &t,const RangoIndice &column_range,const RangoIndice &row_range,const size_t &c)
  : Array3dBoxVarRef<ARRAY_3D>(t,column_range,row_range,c) {}

#endif
