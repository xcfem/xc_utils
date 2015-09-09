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
//CmdTimer.h
//Clase para leer cronometradores.

#ifndef CMDTIMER_H
#define CMDTIMER_H

#include "../nucleo/EntCmd.h"
#include "xc_basic/src/tiempo/timer.h"

//! @ingroup BASE
//
//!  @brief Clase para leer cronometradores.
class CmdTimer: public EntCmd
  {
    Timer t; //!< Timer a leer.
    static TimeElapsed elapsed;
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    CmdTimer(const bool &prec);
    const Timer &GetTimer(void) const;
    any_const_ptr GetProp(const std::string &) const;
  };
#endif
