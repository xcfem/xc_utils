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
//VarRefCapaJCte.h 

#ifndef VARREFCAPAJCTE_H
#define VARREFCAPAJCTE_H

#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Referencia a una capa de la tritriz cuyos puntos tienen el índice J constante.
template <class TRITRIZ>
class VarRefCapaJCte: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit VarRefCapaJCte(TRITRIZ &m,const size_t &capa=1,const size_t &f= 1,const size_t &c= 1);
    VarRefCapaJCte(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    VarRefCapaJCte(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &f,const RangoIndice &rango_cols);
    inline virtual ~VarRefCapaJCte(void) {}
    size_t IndiceFila(void) const
      { return this->offset_f+1; }
    virtual const_reference operator()(size_t capa=1,size_t col=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,1,col); }
    virtual reference operator()(size_t capa=1,size_t col=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,1,col); }
  };

template<class TRITRIZ>
VarRefCapaJCte<TRITRIZ>::VarRefCapaJCte(TRITRIZ &t,const size_t &capa,const size_t &f,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,RangoTritriz(RangoIndice(capa,t.GetCapas()),f,RangoIndice(c,t.getNumCols()))) {}

template<class TRITRIZ>
VarRefCapaJCte<TRITRIZ>::VarRefCapaJCte(TRITRIZ &t,const size_t &f,const size_t &capa1,const size_t &c1,const size_t &capa2,const size_t &c2)
  : VarRefCajaTritriz<TRITRIZ>(t,RangoIndice(capa1,capa2),f,RangoIndice(c1,c2)) {}

template<class TRITRIZ>
VarRefCapaJCte<TRITRIZ>::VarRefCapaJCte(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &f,const RangoIndice &rango_cols)
  : VarRefCajaTritriz<TRITRIZ>(t,rango_capas,f,rango_cols) {}

#endif
