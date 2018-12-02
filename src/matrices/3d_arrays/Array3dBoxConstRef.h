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
//Array3dBoxConstRef.h 

#ifndef ARRAY3DBOXCONSTREF_H
#define ARRAY3DBOXCONSTREF_H

#include "Array3dBoxRefBase.h"
#include "Array3dRange.h"


//! @ingroup arrays3d
//
//! @brief Referencia a una "sub array 3D".
template <class ARRAY_3D>
class Array3dBoxConstRef: public Array3dBoxRefBase
  {
    const ARRAY_3D &ttz;
  public:
    typedef typename ARRAY_3D::const_reference const_reference;

    explicit Array3dBoxConstRef(const ARRAY_3D &t,const size_t &iLayer=1,const size_t &f= 1,const size_t &c= 1);
    Array3dBoxConstRef(const ARRAY_3D &t,const Array3dRange &rango);
    Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const RangoIndice &row_range,const RangoIndice &column_range);
    Array3dBoxConstRef(const ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range);
    Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range);
    Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &iCol);
    Array3dBoxConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range);
    Array3dBoxConstRef(const ARRAY_3D &t,const size_t iLayer,const RangoIndice &row_range,const size_t &iCol);
    Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &iCol);
    inline virtual ~Array3dBoxConstRef(void) {}
    inline virtual const_reference operator()(size_t iLayer=1,size_t iRow=1,size_t iCol=1) const
      { return ttz(iLayer+offset_cp,iRow+offset_f,iCol+offset_c); }
  };

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &f,const size_t &c)
  : Array3dBoxRefBase(iLayer,f,c,t.getNumberOfLayers(),t.getNumberOfRows(),t.getNumberOfColumns()),ttz(t) {}

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const Array3dRange &rango)
  : Array3dBoxRefBase(clip(rango,t)),ttz(t) {}

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const RangoIndice &row_range,const RangoIndice &column_range)
  : Array3dBoxRefBase(clip(layer_range,t.getNumberOfLayers()),clip(row_range,t.getNumberOfRows()),clip(column_range,t.getNumberOfColumns())),ttz(t) {}

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range)
  : Array3dBoxRefBase(iLayer,clip(row_range,t.getNumberOfRows()),clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iLayer>t.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range)
  : Array3dBoxRefBase(clip(layer_range,t.getNumberOfLayers()),iRow,clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iRow>t.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &iCol)
  : Array3dBoxRefBase(clip(layer_range,t.getNumberOfLayers()),clip(row_range,t.getNumberOfRows()),iCol),ttz(t)
  {
    if(iCol>t.getNumberOfColumns())
      std::clog << "Aviso; column index: " << iCol
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range)
  : Array3dBoxRefBase(iLayer,iRow,clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iLayer>t.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
    if(iRow>t.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const size_t iLayer,const RangoIndice &row_range,const size_t &iCol)
  : Array3dBoxRefBase(iLayer,clip(row_range,t.getNumberOfRows()),iCol),ttz(t)
  {
    if(iLayer>t.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
    if(iCol>t.getNumberOfColumns())
      std::clog << "Aviso; column index: " << iCol
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
Array3dBoxConstRef<ARRAY_3D>::Array3dBoxConstRef(const ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &iCol)
  : Array3dBoxRefBase(clip(layer_range,t.getNumberOfLayers()),iRow,iCol),ttz(t)
  {
    if(iRow>t.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
    if(iCol>t.getNumberOfColumns())
      std::clog << "Aviso; column index: " << iCol
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template <class ARRAY_3D>
inline std::ostream &operator<<(std::ostream &os,const Array3dBoxConstRef<ARRAY_3D> &c)
  {
    PrintArray3d(c,os);
    return os;
  }

template <class ARRAY_3D, class TRF>
const Array3dBoxConstRef<ARRAY_3D> &transforma(const Array3dBoxConstRef<ARRAY_3D> &box,const TRF &trf)
  {
    static Array3dBoxConstRef<ARRAY_3D> retval;
    retval= box;
    const size_t n_layers= box.getNumberOfLayers();
    const size_t n_rows= box.getNumberOfRows();
    const size_t n_columns= box.getNumberOfColumns();
    for(size_t k=1;k<=n_layers;k++) //For each layer.
      for(size_t i=1;i<=n_rows;i++) //For each row.
        for(size_t j=1;j<=n_columns;j++) //For each column.
          retval(i,j,k)= Transforma(box(i,j,k));
    return retval;
  }


#endif
