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
//KRowConstRef.h 

#ifndef KROWCONSTREF_H
#define KROWCONSTREF_H


//! @ingroup arrays3d
//
//! @brief Reference to a layer row of the array which points have
//! constant J and K indices.
template <class ARRAY_3D>
class KRowConstRef: public Array3dBoxConstRef<ARRAY_3D>
  {
  public:
    typedef typename Array3dBoxConstRef<ARRAY_3D>::const_reference const_reference;

    explicit KRowConstRef(const ARRAY_3D &m,const size_t &iLayer= 1,const size_t &f= 1);
    KRowConstRef(const ARRAY_3D &m,const size_t &,const size_t &,const size_t &,const size_t &);
    KRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col);
    inline virtual ~KRowConstRef(void) {}
    inline virtual const_reference operator()(size_t c=1) const
      { return Array3dBoxConstRef<ARRAY_3D>::operator()(1,1,c); }
    inline virtual const_reference operator()(size_t iLayer,size_t iRow,size_t col) const
      { return Array3dBoxConstRef<ARRAY_3D>::operator()(iLayer,iRow,col); }
  };

//! @brief Default constructor.
template<class ARRAY_3D>
KRowConstRef<ARRAY_3D>::KRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f)
  : Array3dBoxConstRef<ARRAY_3D>(t,iLayer,f,RangoIndice(1,t.getNumberOfColumns()))
  {}

template<class ARRAY_3D>
KRowConstRef<ARRAY_3D>::KRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f,const size_t &c1,const size_t &c2)
  : Array3dBoxConstRef<ARRAY_3D>(t,iLayer,f,RangoIndice(c1,c2))
  {}

template<class ARRAY_3D>
KRowConstRef<ARRAY_3D>::KRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f,const RangoIndice &rango_col)
  : Array3dBoxConstRef<ARRAY_3D>(t,iLayer,f,rango_col)
  {}

#endif
