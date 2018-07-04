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
//JRowVarRef.h 

#ifndef JROWVARREF_H
#define JROWVARREF_H


//! @ingroup GEOM
//
//! @brief Reference to a row de la tritriz which points
//! have constant J and K indices.
template <class TRITRIZ>
class JRowVarRef: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit JRowVarRef(TRITRIZ &m,const size_t &iLayer= 1,const size_t &c= 1);
    JRowVarRef(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    JRowVarRef(TRITRIZ &t,const size_t &iLayer,const RangoIndice &row_range,const size_t &c);
    inline virtual ~JRowVarRef(void) {}
    size_t getLayerIndex(void) const
      { return this->offset_cp+1; }
    size_t IndiceCol(void) const
      { return this->offset_c+1; }
    inline virtual const_reference operator()(size_t f=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,f,1); }
    inline virtual reference operator()(size_t f=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,f,1); }
    inline virtual const_reference operator()(size_t iLayer,size_t iRow,size_t col) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(iLayer,iRow,col); }
    inline virtual reference operator()(size_t iLayer,size_t iRow,size_t col)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(iLayer,iRow,col); }
  };

//! @brief Default constructor.
template<class TRITRIZ>
JRowVarRef<TRITRIZ>::JRowVarRef(TRITRIZ &t,const size_t &iLayer,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,iLayer,RangoIndice(1,t.getNumberOfRows()),c) {}

template<class TRITRIZ>
JRowVarRef<TRITRIZ>::JRowVarRef(TRITRIZ &t,const size_t &iLayer,const size_t &f1,const size_t &f2,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,iLayer,RangoIndice(f1,f2),c) {}

template<class TRITRIZ>
JRowVarRef<TRITRIZ>::JRowVarRef(TRITRIZ &t,const size_t &iLayer,const RangoIndice &row_range,const size_t &c)
  : VarRefCajaTritriz<TRITRIZ>(t,iLayer,row_range,c) {}

#endif
