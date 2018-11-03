//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//MatrixRange.h

#ifndef MATRIXRANGE_H
#define MATRIXRANGE_H

#include "RangoIndice.h"

//! @brief Rango de variación de un índice, se emplea en BoxConstRef.
class MatrixRange
  {
    RangoIndice row_range; //!< row range.
    RangoIndice column_range; //!< column range.
  public:
    MatrixRange(const RangoIndice &rf,const RangoIndice &rc)
      :row_range(rf),column_range(rc) {}
    template <class M>
    MatrixRange(const M &);
    size_t getNumberOfRows(void) const
      { return row_range.Size(); }
    size_t getNumberOfColumns(void) const
      { return column_range.Size(); }
    size_t Size(void) const
      { return getNumberOfRows()*getNumberOfColumns(); }
    const RangoIndice &getRowRange(void) const
      { return row_range; }
    RangoIndice &getRowRange(void)
      { return row_range; }
    const RangoIndice &getColumnRange(void) const
      { return column_range; }
    RangoIndice &GetgetColumnRange(void)
      { return column_range; }
    bool isRow(void) const
      { return (row_range.Size()==1); }
    bool isColumn(void) const
      { return (column_range.Size()==1); }
    bool Vacio(void) const;
    inline static const char &Separador(void)
      { return RangoIndice::Separador(); }
    void Clip(const size_t &fmax,const size_t &cmax);
    void Intersec(const MatrixRange &otro);
    MatrixRange Intersec(const MatrixRange &otro) const;
    void Print(std::ostream &os) const;
  };

MatrixRange clip(const MatrixRange &r,const size_t &fmax,const size_t &cmax);
MatrixRange intersec(const MatrixRange &,const MatrixRange &);
template <class M>
MatrixRange clip(const MatrixRange &,const M &);
std::ostream &operator<<(std::ostream &os,const MatrixRange &rango);

//! @brief Constructor from a matrix.
template <class M>
MatrixRange::MatrixRange(const M &m)
  : row_range(1,m.getNumberOfRows()),column_range(1,m.getNumberOfColumns()) {}

//! @brief Clipping of the range intervals from a matrix.
template <class M>
MatrixRange clip(const MatrixRange &rm,const M &m)
  { return rm.Intersec(MatrixRange(m)); }
#endif
