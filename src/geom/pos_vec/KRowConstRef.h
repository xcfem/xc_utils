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
//KRowConstRef.h 

#ifndef KROWCONSTREF_H
#define KROWCONSTREF_H


//! @ingroup GEOM
//
//! @brief Reference to a layer row of the tritriz which points have
//! constant J and K indices.
template <class TRITRIZ>
class KRowConstRef: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit KRowConstRef(const TRITRIZ &m,const size_t &iLayer= 1,const size_t &f= 1);
    KRowConstRef(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    KRowConstRef(const TRITRIZ &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col);
    inline virtual ~KRowConstRef(void) {}
    inline virtual const_reference operator()(size_t c=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(1,1,c); }
    inline virtual const_reference operator()(size_t iLayer,size_t iRow,size_t col) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(iLayer,iRow,col); }
  };

//! @brief Default constructor.
template<class TRITRIZ>
KRowConstRef<TRITRIZ>::KRowConstRef(const TRITRIZ &t,const size_t &iLayer,const size_t &f)
  : ConstRefCajaTritriz<TRITRIZ>(t,iLayer,f,RangoIndice(1,t.getNumberOfColumns()))
  {}

template<class TRITRIZ>
KRowConstRef<TRITRIZ>::KRowConstRef(const TRITRIZ &t,const size_t &iLayer,const size_t &f,const size_t &c1,const size_t &c2)
  : ConstRefCajaTritriz<TRITRIZ>(t,iLayer,f,RangoIndice(c1,c2))
  {}

template<class TRITRIZ>
KRowConstRef<TRITRIZ>::KRowConstRef(const TRITRIZ &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col)
  : ConstRefCajaTritriz<TRITRIZ>(t,iLayer,f,rango_col)
  {}

#endif
