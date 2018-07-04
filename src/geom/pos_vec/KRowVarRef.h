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
//KRowVarRef.h 

#ifndef KROWVARREF_H
#define KROWVARREF_H


//! @ingroup GEOM
//
//! @brief Reference to a row de la tritriz which points have constant
//! K indexes.
template <class TRITRIZ>
class KRowVarRef: public VarRefCajaTritriz<TRITRIZ>
  {
  public:
    typedef typename VarRefCajaTritriz<TRITRIZ>::const_reference const_reference;
    typedef typename VarRefCajaTritriz<TRITRIZ>::reference reference;

    explicit KRowVarRef(TRITRIZ &m,const size_t &iLayer= 1,const size_t &f= 1);
    KRowVarRef(TRITRIZ &m,const size_t &,const size_t &,const size_t &,const size_t &);
    KRowVarRef(TRITRIZ &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col);
    inline virtual ~KRowVarRef(void) {}
    size_t getLayerIndex(void) const
      { return this->offset_cp+1; }
    size_t getRowIndex(void) const
      { return this->offset_f+1; }
    inline virtual const_reference operator()(size_t c=1) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,1,c); }
    inline virtual reference operator()(size_t c=1)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(1,1,c); }
    inline virtual const_reference operator()(size_t iLayer,size_t iRow,size_t col) const
      { return VarRefCajaTritriz<TRITRIZ>::operator()(iLayer,iRow,col); }
    inline virtual reference operator()(size_t iLayer,size_t iRow,size_t col)
      { return VarRefCajaTritriz<TRITRIZ>::operator()(iLayer,iRow,col); }
  };

//! @brief Default constructor.
template<class TRITRIZ>
KRowVarRef<TRITRIZ>::KRowVarRef(TRITRIZ &t,const size_t &iLayer,const size_t &f)
  : VarRefCajaTritriz<TRITRIZ>(t,iLayer,f,RangoIndice(1,t.getNumberOfColumns())) {}

template<class TRITRIZ>
KRowVarRef<TRITRIZ>::KRowVarRef(TRITRIZ &t,const size_t &iLayer,const size_t &f,const size_t &c1,const size_t &c2)
  : VarRefCajaTritriz<TRITRIZ>(t,iLayer,f,RangoIndice(c1,c2)) {}

template<class TRITRIZ>
KRowVarRef<TRITRIZ>::KRowVarRef(TRITRIZ &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col)
  : VarRefCajaTritriz<TRITRIZ>(t,iLayer,f,rango_col) {}

#endif
