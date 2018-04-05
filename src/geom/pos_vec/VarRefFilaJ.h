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
//VarRefFilaJ.h 

#ifndef VARREFFILAJ_H
#define VARREFFILAJ_H


//! @ingroup GEOM
//
//! @brief Reference to a row de la tritriz which points
//! have constant J and K indices.
template <class TRITRIZ>
class VarRefFilaJ: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit VarRefFilaJ(TRITRIZ &m,const size_t &capa= 1,const size_t &c= 1);
    VarRefFilaJ(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    VarRefFilaJ(TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const size_t &c);
    inline virtual ~VarRefFilaJ(void) {}
    size_t IndiceCapa(void) const
      { return this->offset_cp+1; }
    size_t IndiceCol(void) const
      { return this->offset_c+1; }
    inline virtual const_reference operator()(size_t f=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,f,1); }
    inline virtual reference operator()(size_t f=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,f,1); }
    inline virtual const_reference operator()(size_t capa,size_t fila,size_t col) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
    inline virtual reference operator()(size_t capa,size_t fila,size_t col)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(capa,fila,col); }
  };

//! @brief Constructor por defecto.
template<class TRITRIZ>
VarRefFilaJ<TRITRIZ>::VarRefFilaJ(TRITRIZ &t,const size_t &capa,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,RangoIndice(1,t.getNumFilas()),c) {}

template<class TRITRIZ>
VarRefFilaJ<TRITRIZ>::VarRefFilaJ(TRITRIZ &t,const size_t &capa,const size_t &f1,const size_t &f2,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,RangoIndice(f1,f2),c) {}

template<class TRITRIZ>
VarRefFilaJ<TRITRIZ>::VarRefFilaJ(TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,capa,rango_filas,c) {}

#endif
