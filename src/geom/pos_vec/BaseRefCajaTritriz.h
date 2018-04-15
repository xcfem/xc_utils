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
//BaseRefCajaTritriz.h 

#ifndef BASEREFCAJATRITRIZ_H
#define BASEREFCAJATRITRIZ_H

#include <ostream>

class RangoIndice;
class RangoTritriz;

//! @ingroup GEOM
//
//! @brief Indices que definen una caja de una tritriz.
class BaseRefCajaTritriz
  {
  protected:
    size_t n_layers; //!< number of layers.
    size_t n_rows; //!< number of rows.
    size_t n_columns; //!< number of columns.
    size_t offset_cp; //!< Offset layer.
    size_t offset_f; //!< Offset row.
    size_t offset_c; //!< Offset column.
  public:
    BaseRefCajaTritriz(const size_t &,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    BaseRefCajaTritriz(const RangoTritriz &rango);
    BaseRefCajaTritriz(const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range);
    BaseRefCajaTritriz(const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range);
    BaseRefCajaTritriz(const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &col);
    BaseRefCajaTritriz(const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range);
    BaseRefCajaTritriz(const size_t iLayer,const RangoIndice &row_range,const size_t &col);
    BaseRefCajaTritriz(const RangoIndice &layer_range,const size_t &iRow,const size_t &col);
    inline const size_t &getNumberOfLayers(void) const
      { return n_layers; }
    inline const size_t &getNumberOfRows(void) const
      { return n_rows; }
    inline const size_t &getNumberOfColumns(void) const
      { return n_columns; }
    inline const size_t Size(void) const
      { return n_layers*n_rows*n_columns; }
    bool Empty(void) const;
    RangoIndice LayerRange(void) const;
    RangoIndice RowRange(void) const;
    RangoIndice RangoCols(void) const;
  };

template <class TRITRIZ>
inline void PrintTritriz(const TRITRIZ &t,std::ostream &os)
  {
    os << '[';
    const size_t n_layers= t.getNumberOfLayers();
    for(size_t i=1;i<=n_layers;i++)
      {
        os << '[';
        const size_t n_rows= t.getNumberOfRows();
        for(register size_t j= 1;j<=n_rows;j++)
          {
            os << '[';
            const size_t n_columns= t.getNumberOfColumns();
            if(n_columns > 0) os << t(i,j,1);
	    for(register size_t k= 2;k<=n_columns;k++)
	      os << ',' << t(i,j,k);
            os << ']';
          }
        os << ']';
      }
    os << ']';
  }

#endif
