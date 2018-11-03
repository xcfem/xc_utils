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
//BoxConstRef.cc

#include "BoxConstRef.h"

//! @brief Constructor por defecto.
BoxBaseRef::BoxBaseRef(const ProtoMatrix &mat,const size_t &f1,const size_t &c1)
  : ProtoMatrix(std::max(mat.getNumberOfRows()-f1+1,size_t(0)),std::max(mat.getNumberOfColumns()-c1+1,size_t(0))), offset_f(f1-1),offset_c(c1-1)
  {}

//! @brief Constructor.
BoxBaseRef::BoxBaseRef(const ProtoMatrix &mat,const size_t &f1,const size_t &c1,const size_t &f2,const size_t &c2)
  : ProtoMatrix(std::max(f2-f1+1,size_t(0)),std::max(c2-c1+1,size_t(0))), offset_f(f1-1),offset_c(c1-1)
  {}

//! @brief Constructor.
BoxBaseRef::BoxBaseRef(const ProtoMatrix &mat,const RangoIndice &row_range,const RangoIndice &column_range)
  : ProtoMatrix(row_range.Size(),column_range.Size()), offset_f(row_range.Offset()),offset_c(column_range.Offset())
  {}

//! @brief Column alone constructor.
BoxBaseRef::BoxBaseRef(const ProtoMatrix &mat,const RangoIndice &row_range,const size_t &col)
  : ProtoMatrix(row_range.Size(),1), offset_f(row_range.Offset()),offset_c(col-1)
  {}

//! @brief Row alone constructor.
BoxBaseRef::BoxBaseRef(const ProtoMatrix &mat,const size_t &iRow,const RangoIndice &column_range)
  : ProtoMatrix(1,column_range.Size()), offset_f(iRow-1),offset_c(column_range.Offset())
  {}

//! @brief Return the row range.
RangoIndice BoxBaseRef::getRowRange(void) const
  { return RangoIndice(offset_f+1,offset_f+getNumberOfRows()); }

//! @brief Return the column range.
RangoIndice BoxBaseRef::getColumnRange(void) const
  { return RangoIndice(offset_c+1,offset_c+getNumberOfColumns()); }

