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
//FuncPorPuntosR2_R.h

#ifndef FUNCPORPUNTOSR2_R_H
#define FUNCPORPUNTOSR2_R_H

#include "FuncPorPuntosR2_T.h"
#include <deque>

typedef std::deque<double> dq_double;

//! @brief función de R2 en R definida por puntos.
//!
//! Función que a los puntos del dominio le asigna un
//! real.
class FuncPorPuntosR2_R: public FuncPorPuntosR2_T<double>
  {
  public:
    typedef FuncPorPuntosR2_T<double> fR2_R;
    typedef std::pair<int,int> filacol;
    //! Constructor.
    FuncPorPuntosR2_R(const size_t &fls=1,const size_t &cls=1)
      : fR2_R(fls,cls) {}
    //! Constructor.
    FuncPorPuntosR2_R(const MatrizPos2d &dom,const double &vdef)
      : fR2_R(dom,vdef) {}
    FuncPorPuntosR2_R(const MatrizPos2d &dom,const m_valores &v)
      : fR2_R(dom,v) {}
    filacol PosMax(void) const;
    double Max(void) const;
    Pos2d PuntoMax(void) const;
    filacol PosMin(void) const;
    double Min(void) const;
    Pos2d PuntoMin(void) const;
  };


#endif
