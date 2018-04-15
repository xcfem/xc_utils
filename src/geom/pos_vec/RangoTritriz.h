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
//RangoTritriz.h

#ifndef RANGOTRITRIZ_H
#define RANGOTRITRIZ_H

#include "xc_basic/src/matrices/RangoIndice.h"


//! @ingroup GEOM
//
//! @brief Rangos de variación de tres índices, se emplea en ConstRefCaja.
class RangoTritriz
  {
    RangoIndice layer_range; //!< layers range.
    RangoIndice row_range; //!< row range.
    RangoIndice column_range; //!< columns range.
  public:
    RangoTritriz(const RangoIndice &rcp= RangoIndice(),const RangoIndice &rf= RangoIndice(),const RangoIndice &rc= RangoIndice())
      : layer_range(rcp), row_range(rf),column_range(rc) {}
    RangoTritriz(const size_t &iLayer,const RangoIndice &rf,const RangoIndice &rc)
      : layer_range(iLayer,iLayer), row_range(rf),column_range(rc) {}
    RangoTritriz(const RangoIndice &rcp,const size_t &iRow,const RangoIndice &rc)
      : layer_range(rcp), row_range(iRow, iRow),column_range(rc) {}
    RangoTritriz(const RangoIndice &rcp,const RangoIndice &rf,const size_t &col)
      : layer_range(rcp), row_range(rf),column_range(col,col) {}
    template <class TTZ>
    RangoTritriz(const TTZ &);

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
    void Recorta(const size_t &cpmax,const size_t &fmax,const size_t &cmax);
    void Intersec(const RangoTritriz &otro);
    RangoTritriz Intersec(const RangoTritriz &otro) const;
    void Print(std::ostream &os) const;
  };

RangoTritriz recorta(const RangoTritriz &r,const size_t &cpmax,const size_t &fmax,const size_t &cmax);
RangoTritriz intersec(const RangoTritriz &,const RangoTritriz &);
std::ostream &operator<<(std::ostream &os,const RangoTritriz &rango);

//! @brief Constructor a partir de una tritriz.
template <class TTZ>
RangoTritriz::RangoTritriz(const TTZ &ttz)
  : layer_range(1,ttz.getNumberOfLayers()), row_range(1,ttz.getNumberOfRows()),column_range(1,ttz.getNumberOfColumns()) {}

//! @brief Recorte de los intervalos del rango a partir de una tritriz.
template <class TTZ>
RangoTritriz recorta(const RangoTritriz &rttz,const TTZ &ttz)
  { return rttz.Intersec(RangoTritriz(ttz)); }

#endif
