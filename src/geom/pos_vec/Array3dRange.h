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
//Array3dRange.h

#ifndef RANGOARRAY3D_H
#define RANGOARRAY3D_H

#include "xc_basic/src/matrices/RangoIndice.h"


//! @ingroup GEOM
//
//! @brief Rangos de variación de tres índices, se emplea en BoxConstRef.
class Array3dRange
  {
    RangoIndice layer_range; //!< layers range.
    RangoIndice row_range; //!< row range.
    RangoIndice column_range; //!< columns range.
  public:
    Array3dRange(const RangoIndice &rcp= RangoIndice(),const RangoIndice &rf= RangoIndice(),const RangoIndice &rc= RangoIndice())
      : layer_range(rcp), row_range(rf),column_range(rc) {}
    Array3dRange(const size_t &iLayer,const RangoIndice &rf,const RangoIndice &rc)
      : layer_range(iLayer,iLayer), row_range(rf),column_range(rc) {}
    Array3dRange(const RangoIndice &rcp,const size_t &iRow,const RangoIndice &rc)
      : layer_range(rcp), row_range(iRow, iRow),column_range(rc) {}
    Array3dRange(const RangoIndice &rcp,const RangoIndice &rf,const size_t &col)
      : layer_range(rcp), row_range(rf),column_range(col,col) {}
    template <class TTZ>
    Array3dRange(const TTZ &);

    size_t getNumberOfLayers(void) const
      { return row_range.Size(); }
    size_t getNumberOfRows(void) const
      { return row_range.Size(); }
    size_t getNumberOfColumns(void) const
      { return column_range.Size(); }
    size_t Size(void) const
    { return getNumberOfLayers()*getNumberOfRows()*getNumberOfColumns(); }
    bool Vacio(void) const;
    const RangoIndice &getLayerRange(void) const
      { return layer_range; }
    RangoIndice &getLayerRange(void)
      { return layer_range; }
    const RangoIndice &getRowRange(void) const
      { return row_range; }
    RangoIndice &getRowRange(void)
      { return row_range; }
    const RangoIndice &getColumnRange(void) const
      { return column_range; }
    RangoIndice &getColumnRange(void)
      { return column_range; }

    size_t Dimension(void) const;
    bool isIRow(void) const;
    bool isJRow(void) const;
    bool isKRow(void) const;
    bool isConstantILayer(void) const;
    bool isConstantJLayer(void) const;
    bool isConstantKLayer(void) const;

    inline static const char &Separador(void)
      { return RangoIndice::Separador(); }
    void Clip(const size_t &cpmax,const size_t &fmax,const size_t &cmax);
    void Intersec(const Array3dRange &);
    Array3dRange Intersec(const Array3dRange &other) const;
    void Print(std::ostream &os) const;
  };

Array3dRange clip(const Array3dRange &r,const size_t &cpmax,const size_t &fmax,const size_t &cmax);
Array3dRange intersec(const Array3dRange &,const Array3dRange &);
std::ostream &operator<<(std::ostream &os,const Array3dRange &rango);

//! @brief Constructor from an array.
template <class TTZ>
Array3dRange::Array3dRange(const TTZ &ttz)
  : layer_range(1,ttz.getNumberOfLayers()), row_range(1,ttz.getNumberOfRows()),column_range(1,ttz.getNumberOfColumns()) {}

//! @brief Clip the range intervals from the array argument.
template <class TTZ>
Array3dRange clip(const Array3dRange &rttz,const TTZ &ttz)
  { return rttz.Intersec(Array3dRange(ttz)); }

#endif
