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
//FunctionFromPointsR2_R.h

#ifndef FUNCTIONFROMPOINTSR2_R_H
#define FUNCTIONFROMPOINTSR2_R_H

#include "FunctionFromPointsR2_T.h"
#include <deque>

typedef std::deque<double> dq_double;

//! @brief función de R2 en R defined on a set of points.
//!
//! Function that assigns a real to the points of its domain.
class FunctionFromPointsR2_R: public FunctionFromPointsR2_T<double>
  {
  public:
    typedef FunctionFromPointsR2_T<double> fR2_R;
    typedef std::pair<int,int> row_column;
    //! Constructor.
    FunctionFromPointsR2_R(const size_t &n_rows=1,const size_t &n_columns=1)
      : fR2_R(n_rows,n_columns) {}
    //! Constructor.
    FunctionFromPointsR2_R(const MatrizPos2d &dom,const double &vdef)
      : fR2_R(dom,vdef) {}
    FunctionFromPointsR2_R(const MatrizPos2d &dom,const m_values &v)
      : fR2_R(dom,v) {}
    row_column PosMax(void) const;
    double Max(void) const;
    Pos2d getMaxPoint(void) const;
    row_column PosMin(void) const;
    double Min(void) const;
    Pos2d getMinPoint(void) const;
  };


#endif
