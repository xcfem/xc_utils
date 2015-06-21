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
//ConstRefFilaI.h 

#ifndef CONSTREFFILAI_H
#define CONSTREFFILAI_H


//! @ingroup GEOM
//
//! @brief Referencia a una capa fila de la tritriz cuyos puntos tienen los índices J y K constantes.
template <class TRITRIZ>
class ConstRefFilaI: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit ConstRefFilaI(const TRITRIZ &m,const size_t &f= 1,const size_t &c= 1);
    ConstRefFilaI(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstRefFilaI(const TRITRIZ &t,const RangoIndice &rango_capas,const size_t &f,const size_t &c);
    inline virtual ~ConstRefFilaI(void) {}
    virtual const_reference operator()(size_t capa=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(capa,1,1); }
    inline virtual const_reference operator()(size_t capa,size_t fila,size_t col) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
  };

//! @brief Constructor por defecto.
template<class TRITRIZ>
ConstRefFilaI<TRITRIZ>::ConstRefFilaI(const TRITRIZ &t,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoIndice(1,t.GetCapas()),f,c)
  {}

//! @brief Constructor.
template<class TRITRIZ>
ConstRefFilaI<TRITRIZ>::ConstRefFilaI(const TRITRIZ &t,const size_t &capa1,const size_t &capa2,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,RangoIndice(capa1,capa2),f,c)
  {}

//! @brief Constructor.
template<class TRITRIZ>
ConstRefFilaI<TRITRIZ>::ConstRefFilaI(const TRITRIZ &t,const RangoIndice &rango_capas,const size_t &f,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,rango_capas,f,c)
  {}

#endif
