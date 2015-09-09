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
//ConstRefCapaICte.h 

#ifndef CONSTREFCAPAICTE_H
#define CONSTREFCAPAICTE_H

#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Referencia a una capa de la tritriz cuyos puntos tienen el índice I constante.
template <class TRITRIZ>
class ConstRefCapaICte: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit ConstRefCapaICte(const TRITRIZ &m,const size_t &capa=1,const size_t &f= 1,const size_t &c= 1);
    ConstRefCapaICte(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstRefCapaICte(const TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols);
    inline virtual ~ConstRefCapaICte(void) {}
    virtual const_reference operator()(size_t fila=1,size_t col=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(1,fila,col); }
  };

template<class TRITRIZ>
ConstRefCapaICte<TRITRIZ>::ConstRefCapaICte(const TRITRIZ &t,const size_t &capa,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(capa,RangoIndice(f,t.getNumFilas()),RangoIndice(c,t.getNumCols()))) {}

template<class TRITRIZ>
ConstRefCapaICte<TRITRIZ>::ConstRefCapaICte(const TRITRIZ &t,const size_t &capa,const size_t &f1,const size_t &c1,const size_t &f2,const size_t &c2)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoTritriz(capa,RangoIndice(f1,f2),RangoIndice(c1,c2))) {}

template<class TRITRIZ>
ConstRefCapaICte<TRITRIZ>::ConstRefCapaICte(const TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols)
  : ConstRefCajaTritriz<TRITRIZ>(t,capa,rango_filas,rango_cols) {}

#endif
