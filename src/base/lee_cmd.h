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
//lee_cmd.h

#ifndef LEE_CMD_HXX
#define LEE_CMD_HXX

#include "CmdStatus.h"

template <typename T>
inline void lee_cmd(T &t,CmdStatus &status)
  {
    t.LeeCmd(status);
  }
template <>
inline void lee_cmd<std::string>(std::string &s,CmdStatus &status)
  {
    s= status.GetString();
  }
template <>
inline void lee_cmd<float>(float &f,CmdStatus &status)
  {
    f= status.GetFloat();
  }
template <>
inline void lee_cmd<double>(double &f,CmdStatus &status)
  {
    f= status.GetFloat();
  }
template <>
inline void lee_cmd<size_t>(size_t &i,CmdStatus &status)
  {
    i= size_t(status.GetFloat());
  }


#endif
