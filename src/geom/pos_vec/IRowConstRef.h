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
//IRowConstRef.h 

#ifndef IROWCONSTREF_H
#define IROWCONSTREF_H


//! @ingroup GEOM
//
//! @brief Reference to a layer row from the tritriz which points have
//! constant J and K indices.
template <class TRITRIZ>
class IRowConstRef: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit IRowConstRef(const TRITRIZ &m,const size_t &f= 1,const size_t &c= 1);
    IRowConstRef(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    IRowConstRef(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &f,const size_t &c);
    inline virtual ~IRowConstRef(void) {}
    virtual const_reference operator()(size_t iLayer=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(iLayer,1,1); }
    inline virtual const_reference operator()(size_t iLayer,size_t iRow,size_t col) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(iLayer,iRow,col); }
  };

//! @brief Default constructor.
template<class TRITRIZ>
IRowConstRef<TRITRIZ>::IRowConstRef(const TRITRIZ &t,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoIndice(1,t.getNumberOfLayers()),f,c)
  {}

//! @brief Constructor.
template<class TRITRIZ>
IRowConstRef<TRITRIZ>::IRowConstRef(const TRITRIZ &t,const size_t &iLayer1,const size_t &iLayer2,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoIndice(iLayer1,iLayer2),f,c)
  {}

//! @brief Constructor.
template<class TRITRIZ>
IRowConstRef<TRITRIZ>::IRowConstRef(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,layer_range,f,c)
  {}

#endif
