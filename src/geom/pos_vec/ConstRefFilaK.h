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
//ConstRefFilaK.h 

#ifndef CONSTREFFILAK_H
#define CONSTREFFILAK_H


//! @ingroup GEOM
//
//! @brief Referencia a una capa fila de la tritriz cuyos puntos tienen los índices J y K constantes.
template <class TRITRIZ>
class ConstRefFilaK: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit ConstRefFilaK(const TRITRIZ &m,const size_t &capa= 1,const size_t &f= 1);
    ConstRefFilaK(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstRefFilaK(const TRITRIZ &t,const size_t &capa,const size_t &f,const RangoIndice &rango_col);
    inline virtual ~ConstRefFilaK(void) {}
    inline virtual const_reference operator()(size_t c=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(1,1,c); }
    inline virtual const_reference operator()(size_t capa,size_t fila,size_t col) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
  };

//! @brief Constructor por defecto.
template<class TRITRIZ>
ConstRefFilaK<TRITRIZ>::ConstRefFilaK(const TRITRIZ &t,const size_t &capa,const size_t &f)
  : ConstRefCajaTritriz<TRITRIZ>(t,capa,f,RangoIndice(1,t.getNumCols()))
  {}

template<class TRITRIZ>
ConstRefFilaK<TRITRIZ>::ConstRefFilaK(const TRITRIZ &t,const size_t &capa,const size_t &f,const size_t &c1,const size_t &c2)
  : ConstRefCajaTritriz<TRITRIZ>(t,capa,f,RangoIndice(c1,c2))
  {}

template<class TRITRIZ>
ConstRefFilaK<TRITRIZ>::ConstRefFilaK(const TRITRIZ &t,const size_t &capa,const size_t &f,const RangoIndice &rango_col)
  : ConstRefCajaTritriz<TRITRIZ>(t,capa,f,rango_col)
  {}

#endif
