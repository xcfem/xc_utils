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
//CmdTimer

#include "CmdTimer.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "any_const_ptr.h"

TimeElapsed CmdTimer::elapsed;

//! @brief Constructor.
CmdTimer::CmdTimer(const bool &prec)
  : t(prec) {}

//! @brief Lectura de la Timer desde archivo.
bool CmdTimer::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(CmdTimer) Procesando comando: " << cmd << std::endl;
    if(cmd == "start") //Arranca el cronometrador.
      {
        status.GetBloque(); //Ignora entrada.
        t.start();
        return true;
      }
    else if(cmd == "stop") //Para el cronometrador.
      {
        status.GetBloque(); //Ignora entrada.
        elapsed= t.stop();
        return true;
      }
    else if(cmd == "reset") //Resetea el cronometrador.
      {
        status.GetBloque(); //Ignora entrada.
        t.reset();
        return true;
      }
    else if(cmd == "get_time") //Resetea el cronometrador.
      {
        status.GetBloque(); //Ignora entrada.
        elapsed= t.getTime();
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve una referencia a la Timer.
const Timer &CmdTimer::GetTimer(void) const
  { return t; }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr CmdTimer::GetProp(const std::string &cod) const 
  {
    if(cod == "userTime")
      return any_const_ptr(elapsed.getUserTime());
    else if(cod == "systemTime")
      return any_const_ptr(elapsed.getSystemTime());
    else if(cod == "realTime")
      return any_const_ptr(elapsed.getRealTime());
    else
      return EntCmd::GetProp(cod);
  }
