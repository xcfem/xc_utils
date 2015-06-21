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
//ConstRefFilaJ.h 

#ifndef CONSTREFFILAJ_H
#define CONSTREFFILAJ_H


//! @ingroup GEOM
//
//! @brief Referencia a una capa fila de la tritriz cuyos puntos tienen los índices J y K constantes.
template <class TRITRIZ>
class ConstRefFilaJ: public ConstRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename ConstRefCajaTritriz<TRITRIZ>::const_reference const_reference;

    explicit ConstRefFilaJ(const TRITRIZ &m,const size_t &capa= 1,const size_t &c= 1);
    ConstRefFilaJ(const TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    ConstRefFilaJ(const TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const size_t &c);
    inline virtual ~ConstRefFilaJ(void) {}
    inline virtual const_reference operator()(size_t f=1) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(1,f,1); }
    inline virtual const_reference operator()(size_t capa,size_t fila,size_t col) const
      { return ConstRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
  };

//! @brief Constructor por defecto.
template<class TRITRIZ>
ConstRefFilaJ<TRITRIZ>::ConstRefFilaJ(const TRITRIZ &t,const size_t &capa,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,capa,RangoIndice(1,t.getNumFilas()),c)
  {}

template<class TRITRIZ>
ConstRefFilaJ<TRITRIZ>::ConstRefFilaJ(const TRITRIZ &t,const size_t &capa,const size_t &f1,const size_t &f2,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,capa,RangoIndice(f1,f2),c) {}

template<class TRITRIZ>
ConstRefFilaJ<TRITRIZ>::ConstRefFilaJ(const TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const size_t &c)
  : ConstRefCajaTritriz<TRITRIZ>(t,capa,rango_filas,c) {}

#endif
