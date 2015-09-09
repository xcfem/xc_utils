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
    RangoIndice rango_capas; //!< Rango de capas.
    RangoIndice rango_filas; //!< Rango de filas.
    RangoIndice rango_cols; //!< Rango de columnas.
  public:
    RangoTritriz(const RangoIndice &rcp= RangoIndice(),const RangoIndice &rf= RangoIndice(),const RangoIndice &rc= RangoIndice())
      : rango_capas(rcp), rango_filas(rf),rango_cols(rc) {}
    RangoTritriz(const size_t &capa,const RangoIndice &rf,const RangoIndice &rc)
      : rango_capas(capa,capa), rango_filas(rf),rango_cols(rc) {}
    RangoTritriz(const RangoIndice &rcp,const size_t &fila,const RangoIndice &rc)
      : rango_capas(rcp), rango_filas(fila,fila),rango_cols(rc) {}
    RangoTritriz(const RangoIndice &rcp,const RangoIndice &rf,const size_t &col)
      : rango_capas(rcp), rango_filas(rf),rango_cols(col,col) {}
    template <class TTZ>
    RangoTritriz(const TTZ &);

    size_t NumCapas(void) const
      { return rango_filas.Size(); }
    size_t NumFilas(void) const
      { return rango_filas.Size(); }
    size_t NumCols(void) const
      { return rango_cols.Size(); }
    size_t Size(void) const
    { return NumCapas()*NumFilas()*NumCols(); }
    bool Vacio(void) const;
    const RangoIndice &GetRangoCapas(void) const
      { return rango_capas; }
    RangoIndice &GetRangoCapas(void)
      { return rango_capas; }
    const RangoIndice &GetRangoFilas(void) const
      { return rango_filas; }
    RangoIndice &GetRangoFilas(void)
      { return rango_filas; }
    const RangoIndice &GetRangoCols(void) const
      { return rango_cols; }
    RangoIndice &GetRangoCols(void)
      { return rango_cols; }

    size_t Dimension(void) const;
    bool EsFilaI(void) const;
    bool EsFilaJ(void) const;
    bool EsFilaK(void) const;
    bool EsCapaICte(void) const;
    bool EsCapaJCte(void) const;
    bool EsCapaKCte(void) const;

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
  : rango_capas(1,ttz.GetCapas()), rango_filas(1,ttz.getNumFilas()),rango_cols(1,ttz.getNumCols()) {}

//! @brief Recorte de los intervalos del rango a partir de una tritriz.
template <class TTZ>
RangoTritriz recorta(const RangoTritriz &rttz,const TTZ &ttz)
  { return rttz.Intersec(RangoTritriz(ttz)); }

#endif
