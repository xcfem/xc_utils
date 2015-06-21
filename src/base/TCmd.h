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
//TCmd.h

#ifndef TCMD_H
#define TCMD_H

#include "../nucleo/EntCmd.h"

//! @ingroup BASE
//
//! @brief Clase para leer un objeto (ver T2Cmd,T3Cmd,...).
template <class T>
class TCmd: public EntCmd
  {
  public:
    typedef T tipo;
  private:
    T &t; //!< Objeto a leer.
    const std::string id; //!< Cadena de caracteres que dispara la lectura del objeto.
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    TCmd(T &,const std::string &);
  };

//! @brief Constructor.
template <class T>
TCmd<T>::TCmd(T &obj,const std::string &s)
  : t(obj), id(s) {}

//! @brief Lectura de la Tuple desde archivo.
template <class T>
bool TCmd<T>::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(TCmd) Procesando comando: " << cmd << std::endl;
    if(cmd==id)
      {
        t.LeeCmd(status);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

#endif
