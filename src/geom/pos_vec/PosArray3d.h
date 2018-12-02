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
//PosArray3d.h
//Array of point matrices.

#ifndef POSARRAY3D_H
#define POSARRAY3D_H

#include "PosArray.h"
#include "xc_utils/src/matrices/3d_arrays/Array3dBase.h"


//! @ingroup GEOM
//
//! @brief Base class for grids of positions in 3D.
template <class POS>
class PosArray3d: public Array3dBase<PosArray<POS> >
  {
  public:
    typedef PosArray<POS> m_pos;
    PosArray3d(const size_t iLayers= 1): Array3dBase<m_pos >(iLayers) {}
    PosArray3d(const size_t iLayers,const m_pos &m): Array3dBase<m_pos >(iLayers,m) {}
    PosArray3d(const m_pos &,const m_pos &,const m_pos &,const m_pos &,const size_t &,const size_t &);
    size_t NumPos(void) const;

    POS getCenter(void) const;
  };

//! @brief Generate the point array from the arguments.
template <class POS>
PosArray3d<POS>::PosArray3d( const m_pos &l1_points,const m_pos &l2_points,
                             const m_pos &l3_points,const m_pos &l4_points,
                             const size_t &ndiv_12,const size_t &ndiv_14)
  : Array3dBase<PosArray<POS> >(l1_points.size())
  {
    const size_t n_layers= this->size();
    for(size_t i=1;i<=n_layers;i++) //Iteration on the point "layers".
      {
        const POS &p1= l1_points(i); //1st. point of the quadrangle. 
        const POS &p2= l2_points(i); //2nd. point of the quadrangle. 
        const POS &p3= l3_points(i); //3rd. point of the quadrangle. 
        const POS &p4= l4_points(i); //4th. point of the quadrangle. 
        const m_pos lado1= m_pos(p1,p2,ndiv_12);
        const m_pos lado2= m_pos(p2,p3,ndiv_14);
        const m_pos lado3= m_pos(p4,p3,ndiv_12);
        const m_pos lado4= m_pos(p1,p4,ndiv_14);
        m_pos i_layer(lado1,lado2,lado3,lado4);
        (*this)(i)= i_layer;
      }
  }

//! @brief Return the number of points in the container.
template <class POS>
size_t PosArray3d<POS>::NumPos(void) const
  { return this->getNumberOfComponents(); }

template <class POS,class SEG>
POS get_centro(const PosArray3d<POS> t,const SEG &sg)
  {
    POS retval;
    const typename PosArray3d<POS>::m_pos &base= t(1);
    const typename PosArray3d<POS>::m_pos &tapa= t(t.getNumberOfLayers());
    SEG s(get_centro(base,SEG()),get_centro(tapa,SEG()));
    retval= s.getCenterOfMass();
    return retval;
  }

#endif
