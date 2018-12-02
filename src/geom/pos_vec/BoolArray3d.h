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
//BoolArray3d.h
//Array of point matrices.

#ifndef BOOLARRAY3D_H
#define BOOLARRAY3D_H

#include "xc_utils/src/matrices/m_bool.h"
#include "Array3dBoxConstRef.h"
#include "ConstantILayerConstRef.h"
#include "ConstantJLayerConstRef.h"
#include "ConstantKLayerConstRef.h"
#include "IRowConstRef.h"
#include "JRowConstRef.h"
#include "KRowConstRef.h"
#include "Array3dBoxVarRef.h"
#include "ConstantILayerVarRef.h"
#include "ConstantJLayerVarRef.h"
#include "ConstantKLayerVarRef.h"
#include "IRowVarRef.h"
#include "JRowVarRef.h"
#include "KRowVarRef.h"



//! @ingroup GEOM
//
//! @brief Base class for grids of bool in 3D (used to express if
//! something exists or not in a (layer,row,column).
class BoolArray3d: public std::vector<m_bool>
  {
  public:
    typedef typename m_bool::reference reference;
    typedef typename m_bool::const_reference const_reference;

    typedef Array3dBoxConstRef<BoolArray3d > box_const_ref;
    typedef ConstantILayerConstRef<BoolArray3d > constant_i_layer_const_ref;
    typedef ConstantJLayerConstRef<BoolArray3d > constant_j_layer_const_ref;
    typedef ConstantKLayerConstRef<BoolArray3d > constant_k_layer_const_ref;
    typedef IRowConstRef<BoolArray3d > i_row_const_ref;
    typedef JRowConstRef<BoolArray3d > j_row_const_ref;
    typedef KRowConstRef<BoolArray3d > k_row_const_ref;

  protected:
    inline m_bool &get_layer(const size_t &iLayer)
      { return (*this)[iLayer-1]; }
    inline const m_bool &get_layer(const size_t &iLayer) const
      { return (*this)[iLayer-1]; }
  public:
    BoolArray3d(const size_t &n_layers, const size_t &n_rows, const size_t &n_columns, const bool &def_value= true); 
    inline size_t getNumberOfLayers(void) const
      { return this->size(); }
    size_t getNumberOfRows(const size_t &layer= 1) const;
    size_t getNumberOfColumns(const size_t &layer= 1) const;
    size_t getNumBools(void) const;

    box_const_ref getBoxConstRef(size_t iLayer=1,size_t f=1, size_t c=1) const
      { return box_const_ref(*this,iLayer,f,c); }
    box_const_ref getBoxConstRef(const Array3dRange &rango) const
      { return box_const_ref(*this,rango); }

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

    inline const m_bool &operator()(const size_t &iLayer) const
      { return get_layer(iLayer); }
    inline m_bool &operator()(const size_t &iLayer)
      { return get_layer(iLayer); }
    inline bool operator()(const size_t &i,const size_t &j,const size_t &k) const
      { return get_layer(i)(j,k); }
    inline void assign(const size_t &i,const size_t &j,const size_t &k, const bool &value)
      { get_layer(i).assign(j,k,value); }
  };

//! @brief Generate the bool arrays from the arguments.
//!
//! @param n_layers: number of layers.
//! @param n_rows: number of rows for each layer.
//! @param n_columns: number of columns for each layer.
//! @param def_value: default value.
BoolArray3d::BoolArray3d(const size_t &n_layers, const size_t &n_rows, const size_t &n_columns, const bool &def_value)
  : std::vector<m_bool>(n_layers)
  {
    for(size_t i=1;i<=n_layers;i++) //Iteration of the point "layers".
      (*this)(i)= m_bool(n_rows,n_columns,def_value);
  }

//! @brief Return the number of bools in the container.
size_t BoolArray3d::getNumBools(void) const
  {
    const size_t sz= this->size();
    if(sz<1)
      return 0;
    else
      {
        const m_bool &layer= (*this)(1);
        return sz*layer.getNumberOfRows()*layer.getNumberOfColumns();
      }
  }


//! @brief Return the number of rows of the layer.
//!
//! @param layer: layer to retrieve the number rows of.
size_t BoolArray3d::getNumberOfRows(const size_t &layer) const
  {
    size_t retval= 0;
    if(this->size())
      retval= (*this)[layer-1].getNumberOfRows();
    return retval;
  }

//! @brief Return the number of columns of the layer.
//!
//! @param layer: layer to retrieve the number columns of.
size_t BoolArray3d::getNumberOfColumns(const size_t &layer) const
  {
    size_t retval= 0;
    if(this->size())
      retval= (*this)[layer-1].getNumberOfColumns();
    return retval;
  }


inline std::ostream &operator<<(std::ostream &os,const BoolArray3d &t)
  {
    const size_t n_layers= t.getNumberOfLayers();
    for(size_t i=1;i<=n_layers;i++)
      os << t(i);
    return os;
  }

#endif
