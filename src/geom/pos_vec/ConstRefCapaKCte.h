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
//ConstRefCapaKCte.h 

#ifndef CONSTREFCAPAKCTE_H
#define CONSTREFCAPAKCTE_H

#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Referencia a una capa de la tritriz cuyos puntos tienen el índice K constante.
template <class TRITRIZ>
class ConstRefCapaKCte: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit ConstRefCapaKCte(const TRITRIZ &m,const size_t &c=1,const size_t &capa= 1,const size_t &f= 1);
    ConstRefCapaKCte(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstRefCapaKCte(const TRITRIZ &t,const RangoIndice &rango_cols,const RangoIndice &rango_filas,const size_t &c);
    inline virtual ~ConstRefCapaKCte(void) {}
    virtual const_reference operator()(size_t capa=1,size_t fila=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(capa,fila,1); }
  };

template<class TRITRIZ>
ConstRefCapaKCte<TRITRIZ>::ConstRefCapaKCte(const TRITRIZ &t,const size_t &c,const size_t &capa,const size_t &f)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(capa,t.GetCapas()),RangoIndice(f,t.getNumFilas()),c)) {}

template<class TRITRIZ>
ConstRefCapaKCte<TRITRIZ>::ConstRefCapaKCte(const TRITRIZ &t,const size_t &c,const size_t &capa1,const size_t &f1,const size_t &capa2,const size_t &f2)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(capa1,capa2),RangoIndice(f1,f2),c)) {}

template<class TRITRIZ>
ConstRefCapaKCte<TRITRIZ>::ConstRefCapaKCte(const TRITRIZ &t,const RangoIndice &rango_cols,const RangoIndice &rango_filas,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,rango_cols,rango_filas,c)
  {}

#endif
