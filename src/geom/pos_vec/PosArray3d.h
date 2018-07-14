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
#include "ConstRefCajaArray3d.h"
#include "ConstantILayerConstRef.h"
#include "ConstantJLayerConstRef.h"
#include "ConstantKLayerConstRef.h"
#include "IRowConstRef.h"
#include "JRowConstRef.h"
#include "KRowConstRef.h"
#include "VarRefCajaArray3d.h"
#include "ConstantILayerVarRef.h"
#include "ConstantJLayerVarRef.h"
#include "ConstantKLayerVarRef.h"
#include "IRowVarRef.h"
#include "JRowVarRef.h"
#include "KRowVarRef.h"



//! @ingroup GEOM
//
//! @brief Base class for the position arrays.
template <class POS>
class PosArray3d: public std::vector<PosArray<POS> >
  {
  public:
    typedef PosArray<POS> m_pos;
    typedef typename m_pos::reference reference;
    typedef typename m_pos::const_reference const_reference;

    typedef ConstRefCajaArray3d<PosArray3d<POS> > const_ref_caja;
    typedef ConstantILayerConstRef<PosArray3d<POS> > constant_i_layer_const_ref;
    typedef ConstantJLayerConstRef<PosArray3d<POS> > constant_j_layer_const_ref;
    typedef ConstantKLayerConstRef<PosArray3d<POS> > constant_k_layer_const_ref;
    typedef IRowConstRef<PosArray3d<POS> > i_row_const_ref;
    typedef JRowConstRef<PosArray3d<POS> > j_row_const_ref;
    typedef KRowConstRef<PosArray3d<POS> > k_row_const_ref;

    typedef VarRefCajaArray3d<PosArray3d<POS> > var_ref_caja;
    typedef ConstantILayerVarRef<PosArray3d<POS> > constant_i_layer_variable_ref;
    typedef ConstantJLayerVarRef<PosArray3d<POS> > constant_j_layer_variable_ref;
    typedef ConstantKLayerVarRef<PosArray3d<POS> > constant_k_layer_variable_ref;
    typedef IRowVarRef<PosArray3d<POS> > i_row_var_ref;
    typedef JRowVarRef<PosArray3d<POS> > j_row_var_ref;
    typedef KRowVarRef<PosArray3d<POS> > k_row_var_ref;

  protected:
    inline m_pos &get_layer(const size_t &iLayer)
      { return (*this)[iLayer-1]; }
    inline const m_pos &get_layer(const size_t &iLayer) const
      { return (*this)[iLayer-1]; }
  public:
    PosArray3d(const size_t iLayers= 1): std::vector<m_pos>(iLayers) {}
    PosArray3d(const size_t iLayers,const m_pos &m): std::vector<m_pos>(iLayers,m) {}
    PosArray3d(const m_pos &,const m_pos &,const m_pos &,const m_pos &,const size_t &,const size_t &);
    inline size_t getNumberOfLayers(void) const
      { return this->size(); }
    size_t getNumberOfRows(void) const;
    size_t getNumberOfColumns(void) const;
    size_t NumPos(void) const;

    const_ref_caja GetConstRefCaja(size_t iLayer=1,size_t f=1, size_t c=1) const
      { return const_ref_caja(*this,iLayer,f,c); }
    const_ref_caja GetConstRefCaja(const Array3dRange &rango) const
      { return const_ref_caja(*this,rango); }

    constant_i_layer_const_ref ConstantILayerGetConstRef(size_t iLayer=1,size_t iRow=1, size_t iColumn=1) const
      { return constant_i_layer_const_ref(*this,iLayer,iRow,iColumn); }
    constant_i_layer_const_ref ConstantILayerGetConstRef(size_t iLayer,const RangoIndice &row_range,const RangoIndice &column_range) const
      { return constant_i_layer_const_ref(*this,iLayer,row_range,column_range); }
    constant_j_layer_const_ref ConstantJLayerGetConstRef(size_t f=1,size_t iLayer=1, size_t c=1) const
      { return constant_j_layer_const_ref(*this,iLayer,f,c); }
    constant_j_layer_const_ref ConstantJLayerGetConstRef(const RangoIndice &layer_range,size_t f,const RangoIndice &column_range) const
      { return constant_j_layer_const_ref(*this,layer_range,f,column_range); }
    constant_k_layer_const_ref ConstantKLayerGetConstRef(size_t c=1,size_t iLayer=1, size_t f=1) const
      { return constant_k_layer_const_ref(*this,c,iLayer,f); }
    constant_k_layer_const_ref ConstantKLayerGetConstRef(const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &c) const
      { return constant_k_layer_const_ref(*this,layer_range,row_range,c); }

    i_row_const_ref IRowGetConstRef(size_t f=1,size_t c=1) const
      { return i_row_const_ref(*this,f,c); }
    i_row_const_ref IRowGetConstRef(const RangoIndice &layer_range,size_t f,size_t c) const
      { return i_row_const_ref(*this,layer_range,f,c); }
    j_row_const_ref JRowGetConstRef(size_t iLayer=1,size_t c=1) const
      { return j_row_const_ref(*this,iLayer,c); }
    j_row_const_ref JRowGetConstRef(size_t iLayer,const RangoIndice &row_range,size_t c) const
      { return j_row_const_ref(*this,iLayer,row_range,c); }
    k_row_const_ref KRowGetConstRef(size_t iLayer=1,size_t f=1) const
      { return k_row_const_ref(*this,iLayer,f); }
    k_row_const_ref KRowGetConstRef(size_t iLayer,size_t f,const RangoIndice &column_range) const
      { return k_row_const_ref(*this,iLayer,f,column_range); }

    var_ref_caja GetVarRefCaja(size_t iLayer=1,size_t f=1, size_t c=1)
      { return var_ref_caja(*this,iLayer,f,c); }
    var_ref_caja GetVarRefCaja(const Array3dRange &rango)
      { return var_ref_caja(*this,rango); }

    constant_i_layer_variable_ref ConstantILayerGetVarRef(size_t iLayer=1,size_t f=1, size_t c=1)
      { return constant_i_layer_variable_ref(*this,iLayer,f,c); }
    constant_i_layer_variable_ref ConstantILayerGetVarRef(size_t iLayer,const RangoIndice &row_range,const RangoIndice &column_range)
      { return constant_i_layer_variable_ref(*this,iLayer,row_range,column_range); }
    constant_j_layer_variable_ref ConstantJLayerGetVarRef(size_t f=1,size_t iLayer=1, size_t c=1)
      { return constant_j_layer_variable_ref(*this,iLayer,f,c); }
    constant_j_layer_variable_ref ConstantJLayerGetVarRef(const RangoIndice &layer_range,size_t f,const RangoIndice &column_range)
      { return constant_j_layer_variable_ref(*this,layer_range,f,column_range); }
    constant_k_layer_variable_ref ConstantKLayerGetVarRef(size_t c=1,size_t iLayer=1, size_t f=1)
      { return constant_k_layer_variable_ref(*this,c,iLayer,f); }
    constant_k_layer_variable_ref ConstantKLayerGetVarRef(const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &c)
      { return constant_k_layer_variable_ref(*this,layer_range,row_range,c); }

    i_row_var_ref IRowGetVarRef(size_t f=1,size_t c=1)
      { return i_row_var_ref(*this,f,c); }
    i_row_var_ref IRowGetVarRef(const RangoIndice &layer_range,size_t f,size_t c)
      { return i_row_var_ref(*this,layer_range,f,c); }
    j_row_var_ref JRowGetVarRef(size_t f=1,size_t c=1)
      { return j_row_var_ref(*this,f,c); }
    j_row_var_ref JRowGetVarRef(size_t iLayer,const RangoIndice &row_range,size_t c)
      { return j_row_var_ref(*this,iLayer,row_range,c); }
    k_row_var_ref KRowGetVarRef(size_t f=1,size_t c=1)
      { return k_row_var_ref(*this,f,c); }
    k_row_var_ref KRowGetVarRef(size_t iLayer,size_t f,const RangoIndice &column_range)
      { return k_row_var_ref(*this,iLayer,f,column_range); }

    inline const m_pos &operator()(const size_t &iLayer) const
      { return get_layer(iLayer); }
    inline m_pos &operator()(const size_t &iLayer)
      { return get_layer(iLayer); }
    inline const POS &operator()(const size_t &i,const size_t &j,const size_t &k) const
      { return get_layer(i)(j,k); }
    inline POS &operator()(const size_t &i,const size_t &j,const size_t &k)
      { return get_layer(i)(j,k); }
    POS GetCentro(void) const;
  };

//! @brief Generate the point arra from the arguments.
template <class POS>
PosArray3d<POS>::PosArray3d( const m_pos &l1_points,const m_pos &l2_points,
                             const m_pos &l3_points,const m_pos &l4_points,
                             const size_t &ndiv_12,const size_t &ndiv_14)
  : std::vector<m_pos>(l1_points.size())
  {
    const size_t n_layers= this->size();
    for(size_t i=1;i<=n_layers;i++) //Iteration of the point "layers".
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

//! @brief Return el número de elementos of the array.
template <class POS>
size_t PosArray3d<POS>::NumPos(void) const
  {
    const size_t sz= this->size();
    if(sz<1)
      return 0;
    else
      {
        const m_pos &layer= (*this)(1); 
        return sz*layer.getNumberOfRows()*layer.getNumberOfColumns();
      }
  }

template <class POS>
size_t PosArray3d<POS>::getNumberOfRows(void) const
  {
    size_t retval= 0;
    if(this->size())
      retval= (*this)[0].getNumberOfRows();
    return retval;
  }

template <class POS>
size_t PosArray3d<POS>::getNumberOfColumns(void) const
  {
    size_t retval= 0;
    if(this->size())
      retval= (*this)[0].getNumberOfColumns();
    return retval;
  }

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

template <class POS>
inline std::ostream &operator<<(std::ostream &os,const PosArray3d<POS> &t)
  {
    const size_t n_layers= t.getNumberOfLayers();
    for(size_t i=1;i<=n_layers;i++)
      os << t(i);
    return os;
  }

#endif
