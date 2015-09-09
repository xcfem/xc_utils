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
//VarRefFilaI.h 

#ifndef VARREFFILAI_H
#define VARREFFILAI_H


//! @ingroup GEOM
//
//! @brief Referencia a una fila de la tritriz cuyos puntos tienen los índices J y K constantes.
template <class TRITRIZ>
class VarRefFilaI: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit VarRefFilaI(TRITRIZ &m,const size_t &f= 1,const size_t &c= 1);
    VarRefFilaI(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    VarRefFilaI(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &f,const size_t &c);
    inline virtual ~VarRefFilaI(void) {}
    size_t IndiceFila(void) const
      { return this->offset_f+1; }
    size_t IndiceCol(void) const
      { return this->offset_c+1; }
    virtual const_reference operator()(size_t capa=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,1,1); }
    virtual reference operator()(size_t capa=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,1,1); }
    inline virtual const_reference operator()(size_t capa,size_t fila,size_t col) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
    inline virtual reference operator()(size_t capa,size_t fila,size_t col)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
  };

//! @brief Constructor por defecto.
template<class TRITRIZ>
VarRefFilaI<TRITRIZ>::VarRefFilaI(TRITRIZ &t,const size_t &f,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,RangoIndice(1,t.GetCapas()),f,c)
  {}

//! @brief Constructor.
template<class TRITRIZ>
VarRefFilaI<TRITRIZ>::VarRefFilaI(TRITRIZ &t,const size_t &capa1,const size_t &capa2,const size_t &f,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,RangoIndice(capa1,capa2),f,c)
  {}

//! @brief Constructor.
template<class TRITRIZ>
VarRefFilaI<TRITRIZ>::VarRefFilaI(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &f,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,rango_capas,f,c)
  {}

#endif
