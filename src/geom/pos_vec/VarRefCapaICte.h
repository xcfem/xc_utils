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
//VarRefCapaICte.h 

#ifndef VARREFCAPAICTE_H
#define VARREFCAPAICTE_H

#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Reference to a layer de la tritriz which points have constant I index.
template <class TRITRIZ>
class VarRefCapaICte: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit VarRefCapaICte(TRITRIZ &m,const size_t &capa=1,const size_t &f= 1,const size_t &c= 1);
    VarRefCapaICte(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    VarRefCapaICte(TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols);
    inline virtual ~VarRefCapaICte(void) {}
    size_t IndiceCapa(void) const
      { return this->offset_cp+1; }
    virtual const_reference operator()(size_t fila=1,size_t col=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,fila,col); }
    virtual reference operator()(size_t fila=1,size_t col=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,fila,col); }
  };

template<class TRITRIZ>
VarRefCapaICte<TRITRIZ>::VarRefCapaICte(TRITRIZ &t,const size_t &capa,const size_t &f,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,RangoTritriz(capa,RangoIndice(f,t.getNumFilas()),RangoIndice(c,t.getNumCols()))) {}

template<class TRITRIZ>
VarRefCapaICte<TRITRIZ>::VarRefCapaICte(TRITRIZ &t,const size_t &capa,const size_t &f1,const size_t &c1,const size_t &f2,const size_t &c2)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,RangoIndice(f1,f2),RangoIndice(c1,c2)) {}

template<class TRITRIZ>
VarRefCapaICte<TRITRIZ>::VarRefCapaICte(TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,rango_filas,rango_cols)
  {}

#endif
