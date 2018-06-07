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
//ConstRefCajaTritriz.h 

#ifndef CONSTREFCAJATRITRIZ_H
#define CONSTREFCAJATRITRIZ_H

#include "BaseRefCajaTritriz.h"
#include "RangoTritriz.h"


//! @ingroup GEOM
//
//! @brief Referencia a una "subtritriz".
template <class TRITRIZ>
class ConstRefCajaTritriz: public BaseRefCajaTritriz
  {
    const TRITRIZ &ttz;
  public:
    typedef typename TRITRIZ::const_reference const_reference;

    explicit ConstRefCajaTritriz(const TRITRIZ &t,const size_t &iLayer=1,const size_t &f= 1,const size_t &c= 1);
    ConstRefCajaTritriz(const TRITRIZ &t,const RangoTritriz &rango);
    ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const RangoIndice &row_range,const RangoIndice &column_range);
    ConstRefCajaTritriz(const TRITRIZ &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range);
    ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range);
    ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &iCol);
    ConstRefCajaTritriz(const TRITRIZ &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range);
    ConstRefCajaTritriz(const TRITRIZ &t,const size_t iLayer,const RangoIndice &row_range,const size_t &iCol);
    ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &iCol);
    inline virtual ~ConstRefCajaTritriz(void) {}
    inline virtual const_reference operator()(size_t iLayer=1,size_t iRow=1,size_t iCol=1) const
      { return ttz(iLayer+offset_cp,iRow+offset_f,iCol+offset_c); }
  };

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const size_t &iLayer,const size_t &f,const size_t &c)
  : BaseRefCajaTritriz(iLayer,f,c,t.getNumberOfLayers(),t.getNumberOfRows(),t.getNumberOfColumns()),ttz(t) {}

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const RangoTritriz &rango)
  : BaseRefCajaTritriz(clip(rango,t)),ttz(t) {}

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const RangoIndice &row_range,const RangoIndice &column_range)
  : BaseRefCajaTritriz(clip(layer_range,t.getNumberOfLayers()),clip(row_range,t.getNumberOfRows()),clip(column_range,t.getNumberOfColumns())),ttz(t) {}

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range)
  : BaseRefCajaTritriz(iLayer,clip(row_range,t.getNumberOfRows()),clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iLayer>t.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range)
  : BaseRefCajaTritriz(clip(layer_range,t.getNumberOfLayers()),iRow,clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iRow>t.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &iCol)
  : BaseRefCajaTritriz(clip(layer_range,t.getNumberOfLayers()),clip(row_range,t.getNumberOfRows()),iCol),ttz(t)
  {
    if(iCol>t.getNumberOfColumns())
      std::clog << "Aviso; column index: " << iCol
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range)
  : BaseRefCajaTritriz(iLayer,iRow,clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iLayer>t.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
    if(iRow>t.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const size_t iLayer,const RangoIndice &row_range,const size_t &iCol)
  : BaseRefCajaTritriz(iLayer,clip(row_range,t.getNumberOfRows()),iCol),ttz(t)
  {
    if(iLayer>t.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
    if(iCol>t.getNumberOfColumns())
      std::clog << "Aviso; column index: " << iCol
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
ConstRefCajaTritriz<TRITRIZ>::ConstRefCajaTritriz(const TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &iCol)
  : BaseRefCajaTritriz(clip(layer_range,t.getNumberOfLayers()),iRow,iCol),ttz(t)
  {
    if(iRow>t.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
    if(iCol>t.getNumberOfColumns())
      std::clog << "Aviso; column index: " << iCol
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template <class TRITRIZ>
inline std::ostream &operator<<(std::ostream &os,const ConstRefCajaTritriz<TRITRIZ> &c)
  {
    PrintTritriz(c,os);
    return os;
  }

template <class TRITRIZ, class TRF>
const ConstRefCajaTritriz<TRITRIZ> &transforma(const ConstRefCajaTritriz<TRITRIZ> &caja,const TRF &trf)
  {
    static ConstRefCajaTritriz<TRITRIZ> retval;
    retval= caja;
    const size_t n_layers= caja.getNumberOfLayers();
    const size_t n_rows= caja.getNumberOfRows();
    const size_t n_columns= caja.getNumberOfColumns();
    for(size_t k=1;k<=n_layers;k++) //For each layer.
      for(size_t i=1;i<=n_rows;i++) //For each row.
        for(size_t j=1;j<=n_columns;j++) //For each column.
          retval(i,j,k)= Transforma(caja(i,j,k));
    return retval;
  }


#endif
