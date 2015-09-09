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
//VarRefFilaK.h 

#ifndef VARREFFILAK_H
#define VARREFFILAK_H


//! @ingroup GEOM
//
//! @brief Referencia a una capa fila de la tritriz cuyos puntos tienen los índices J y K constantes.
template <class TRITRIZ>
class VarRefFilaK: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit VarRefFilaK(TRITRIZ &m,const size_t &capa= 1,const size_t &f= 1);
    VarRefFilaK(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    VarRefFilaK(TRITRIZ &t,const size_t &capa,const size_t &f,const RangoIndice &rango_col);
    inline virtual ~VarRefFilaK(void) {}
    size_t IndiceCapa(void) const
      { return this->offset_cp+1; }
    size_t IndiceFila(void) const
      { return this->offset_f+1; }
    inline virtual const_reference operator()(size_t c=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,1,c); }
    inline virtual reference operator()(size_t c=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,1,c); }
    inline virtual const_reference operator()(size_t capa,size_t fila,size_t col) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
    inline virtual reference operator()(size_t capa,size_t fila,size_t col)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
  };

//! @brief Constructor por defecto.
template<class TRITRIZ>
VarRefFilaK<TRITRIZ>::VarRefFilaK(TRITRIZ &t,const size_t &capa,const size_t &f)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,f,RangoIndice(1,t.getNumCols())) {}

template<class TRITRIZ>
VarRefFilaK<TRITRIZ>::VarRefFilaK(TRITRIZ &t,const size_t &capa,const size_t &f,const size_t &c1,const size_t &c2)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,f,RangoIndice(c1,c2)) {}

template<class TRITRIZ>
VarRefFilaK<TRITRIZ>::VarRefFilaK(TRITRIZ &t,const size_t &capa,const size_t &f,const RangoIndice &rango_col)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,f,rango_col) {}

#endif
