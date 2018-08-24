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
//JRowConstRef.h 

#ifndef JROWCONSTREF_H
#define JROWCONSTREF_H


//! @ingroup GEOM
//
//! @brief Reference to a layer of the array which points have constant
//! J and K indexes.
template <class ARRAY_3D>
class JRowConstRef: public Array3dBoxConstRef<ARRAY_3D>
  {
  public:
    typedef typename Array3dBoxConstRef<ARRAY_3D>::const_reference const_reference;

    explicit JRowConstRef(const ARRAY_3D &m,const size_t &iLayer= 1,const size_t &c= 1);
    JRowConstRef(const ARRAY_3D &m,const size_t &,const size_t &,const size_t &,const size_t &);
    JRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const size_t &c);
    inline virtual ~JRowConstRef(void) {}
    inline virtual const_reference operator()(size_t f=1) const
      { return Array3dBoxConstRef<ARRAY_3D>::operator()(1,f,1); }
    inline virtual const_reference operator()(size_t iLayer,size_t iRow,size_t col) const
      { return Array3dBoxConstRef<ARRAY_3D>::operator()(iLayer,iRow,col); }
  };

//! @brief Default constructor.
template<class ARRAY_3D>
JRowConstRef<ARRAY_3D>::JRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &c)
  : Array3dBoxConstRef<ARRAY_3D>(t,iLayer,RangoIndice(1,t.getNumberOfRows()),c)
  {}

template<class ARRAY_3D>
JRowConstRef<ARRAY_3D>::JRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f1,const size_t &f2,const size_t &c)
  : Array3dBoxConstRef<ARRAY_3D>(t,iLayer,RangoIndice(f1,f2),c) {}

template<class ARRAY_3D>
JRowConstRef<ARRAY_3D>::JRowConstRef(const ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const size_t &c)
  : Array3dBoxConstRef<ARRAY_3D>(t,iLayer,row_range,c) {}

#endif
