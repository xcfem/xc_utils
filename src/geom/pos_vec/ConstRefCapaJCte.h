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
//ConstRefCapaJCte.h 

#ifndef CONSTREFCAPAJCTE_H
#define CONSTREFCAPAJCTE_H

#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Reference to a layer of the tritriz which points have
//! constant J index.
template <class TRITRIZ>
class ConstRefCapaJCte: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit ConstRefCapaJCte(const TRITRIZ &m,const size_t &capa=1,const size_t &f= 1,const size_t &c= 1);
    ConstRefCapaJCte(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstRefCapaJCte(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &f,const RangoIndice &rango_cols);
    inline virtual ~ConstRefCapaJCte(void) {}
    virtual const_reference operator()(size_t capa=1,size_t col=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(capa,1,col); }
  };

template<class TRITRIZ>
ConstRefCapaJCte<TRITRIZ>::ConstRefCapaJCte(const TRITRIZ &t,const size_t &capa,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(capa,t.GetCapas()),f,RangoIndice(c,t.getNumCols()))) {}

template<class TRITRIZ>
ConstRefCapaJCte<TRITRIZ>::ConstRefCapaJCte(const TRITRIZ &t,const size_t &f,const size_t &capa1,const size_t &c1,const size_t &capa2,const size_t &c2)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(capa1,capa2),f,RangoIndice(c1,c2))) {}

template<class TRITRIZ>
ConstRefCapaJCte<TRITRIZ>::ConstRefCapaJCte(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &f,const RangoIndice &rango_cols)
  : ConstRefCajaTritriz<TRITRIZ>(t,layer_range,f,rango_cols) {}

#endif
