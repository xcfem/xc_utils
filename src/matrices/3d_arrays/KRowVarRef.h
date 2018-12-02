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
//! @brief Reference to a row of the array which points have constant
//! K indexes.
template <class ARRAY_3D>
class KRowVarRef: public Array3dBoxVarRef<ARRAY_3D>
  {
  public:
    typedef typename Array3dBoxVarRef<ARRAY_3D>::const_reference const_reference;
    typedef typename Array3dBoxVarRef<ARRAY_3D>::reference reference;

    explicit KRowVarRef(ARRAY_3D &m,const size_t &iLayer= 1,const size_t &f= 1);
    KRowVarRef(ARRAY_3D &m,const size_t &,const size_t &,const size_t &,const size_t &);
    KRowVarRef(ARRAY_3D &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col);
    inline virtual ~KRowVarRef(void) {}
    size_t getLayerIndex(void) const
      { return this->offset_cp+1; }
    size_t getRowIndex(void) const
      { return this->offset_f+1; }
    inline virtual const_reference operator()(size_t c=1) const
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(1,1,c); }
    inline virtual reference operator()(size_t c=1)
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(1,1,c); }
    inline virtual const_reference operator()(size_t iLayer,size_t iRow,size_t col) const
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(iLayer,iRow,col); }
    inline virtual reference operator()(size_t iLayer,size_t iRow,size_t col)
      { return Array3dBoxVarRef<ARRAY_3D>::operator()(iLayer,iRow,col); }
  };

//! @brief Default constructor.
template<class ARRAY_3D>
KRowVarRef<ARRAY_3D>::KRowVarRef(ARRAY_3D &t,const size_t &iLayer,const size_t &f)
  : Array3dBoxVarRef<ARRAY_3D>(t,iLayer,f,RangoIndice(1,t.getNumberOfColumns())) {}

template<class ARRAY_3D>
KRowVarRef<ARRAY_3D>::KRowVarRef(ARRAY_3D &t,const size_t &iLayer,const size_t &f,const size_t &c1,const size_t &c2)
  : Array3dBoxVarRef<ARRAY_3D>(t,iLayer,f,RangoIndice(c1,c2)) {}

template<class ARRAY_3D>
KRowVarRef<ARRAY_3D>::KRowVarRef(ARRAY_3D &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col)
  : Array3dBoxVarRef<ARRAY_3D>(t,iLayer,f,rango_col) {}

#endif
