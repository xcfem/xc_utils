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
//VarRefCajaTritriz.h 

#ifndef VARREFCAJATRITRIZ_H
#define VARREFCAJATRITRIZ_H

#include "BaseRefCajaTritriz.h"


//! @ingroup GEOM
//
//! @brief Referencia a una "subtritriz".
template <class TRITRIZ>
class VarRefCajaTritriz: public BaseRefCajaTritriz
  {
    TRITRIZ &ttz;
  public:
    typedef typename TRITRIZ::const_reference const_reference;
    typedef typename TRITRIZ::reference reference;

    explicit VarRefCajaTritriz(TRITRIZ &m,const size_t &iLayer=1,const size_t &f= 1,const size_t &c= 1);
    VarRefCajaTritriz(TRITRIZ &m,const RangoTritriz &rango);
    VarRefCajaTritriz(TRITRIZ &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range);
    VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range);
    VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &col);
    VarRefCajaTritriz(TRITRIZ &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range);
    VarRefCajaTritriz(TRITRIZ &t,const size_t iLayer,const RangoIndice &row_range,const size_t &col);
    VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &col);
    inline virtual ~VarRefCajaTritriz(void) {}
    inline virtual const_reference operator()(size_t iLayer=1,size_t iRow=1,size_t col=1) const
      { return ttz(iLayer+offset_cp, iRow+offset_f,col+offset_c); }
    inline virtual reference operator()(size_t iLayer=1,size_t iRow=1,size_t col=1)
      { return ttz(iLayer+offset_cp, iRow+offset_f,col+offset_c); }
  };

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t &iLayer,const size_t &f,const size_t &c)
  : BaseRefCajaTritriz(iLayer,f,c,t.getNumberOfLayers(),t.getNumberOfRows(),t.getNumberOfColumns()),ttz(t) {}

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoTritriz &rango)
  : BaseRefCajaTritriz(recorta(rango,t)),ttz(t) {}

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range)
  : BaseRefCajaTritriz(iLayer,recorta(row_range,t.getNumberOfRows()),recorta(column_range,t.getNumberOfColumns())),ttz(t) 
  {
    if(iLayer>ttz.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer << " out of range en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range)
  : BaseRefCajaTritriz(recorta(layer_range,t.getNumberOfLayers()),iRow,recorta(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iRow>ttz.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &col)
  : BaseRefCajaTritriz(recorta(layer_range,t.getNumberOfLayers()),recorta(row_range,t.getNumberOfRows()),col),ttz(t)
  {
    if(col>ttz.getNumberOfColumns())
      std::clog << "Aviso; column index: " << col
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range)
  : BaseRefCajaTritriz(iLayer,iRow,recorta(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iLayer>ttz.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
    if(iRow>ttz.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t iLayer,const RangoIndice &row_range,const size_t &col)
  : BaseRefCajaTritriz(iLayer,recorta(row_range,t.getNumberOfRows()),col),ttz(t)
  {
    if(iLayer>ttz.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
    if(col>ttz.getNumberOfColumns())
      std::clog << "Aviso; column index: " << col
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &col)
  : BaseRefCajaTritriz(recorta(layer_range,t.getNumberOfLayers()),iRow,col),ttz(t)
  {
    if(iRow>ttz.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
    if(col>ttz.getNumberOfColumns())
      std::clog << "Aviso; column index: " << col
		<< " out of range en tritriz de rangos: "
		<< RangoTritriz(ttz) << std::endl;
  }

template <class TRITRIZ>
inline std::ostream &operator<<(std::ostream &os,const VarRefCajaTritriz<TRITRIZ> &c)
  {
    PrintTritriz(c,os);
    return os;
  }

template <class TRITRIZ, class TRF>
const VarRefCajaTritriz<TRITRIZ> &transforma(const VarRefCajaTritriz<TRITRIZ> &caja,const TRF &trf)
  {
    static VarRefCajaTritriz<TRITRIZ> retval;
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
