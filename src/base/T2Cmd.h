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
//T2Cmd.h

#ifndef T2CMD_H
#define T2CMD_H

#include "TCmd.h"

//! @ingroup BASE
//
//! @brief Clase para leer dos objetos (ver T2Cmd,T3Cmd,...).
template <class T1,class T2>
class T2Cmd: public TCmd<T1>
  {
  public:
    typedef T2 tipo2;
  private:
    T2 &t2; //!< Segundo objeto a leer.
    const std::string id2; //!< Cadena de caracteres que dispara la lectura del objeto t2.
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    T2Cmd(T1 &,const std::string &,T2 &,const std::string &);
  };

//! @brief Constructor.
template <class T1,class T2>
  T2Cmd<T1,T2>::T2Cmd(T1 &obj1,const std::string &i1,T2 &obj2,const std::string &i2)
  : TCmd<T1>(obj1,i1), t2(obj2), id2(i2) {}

//! @brief Lectura de la Tuple desde archivo.
template <class T1,class T2>
bool T2Cmd<T1,T2>::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= this->deref_cmd(status.Cmd());
    if(this->verborrea>2)
      std::clog << "(T2Cmd) Procesando comando: " << cmd << std::endl;
    if(cmd==id2)
      {
        t2.LeeCmd(status);
        return true;
      }
    else
      return TCmd<T1>::procesa_comando(status);
  }

#endif
