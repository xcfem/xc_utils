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
//Rectangulo2d.cc

#include "Rectangulo2d.h"
#include "xc_utils/src/base/CmdStatus.h"

bool Rectangulo2d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(Rectangulo2d) Procesando comando: " << cmd << endl;
    static double base=1.0,altura=1.0;
    if(status.Cmd() == "altura")
      {
        altura= status.GetFloat();
        return true;
      }
    else if(status.Cmd() == "base")
      {
        base= status.GetFloat();
        return true;
      }
    (*this)= Rectangulo2d(base,altura);
    return Cuadrilatero2d::procesa_comando(status);
  }
// void Rectangulo2d::salva_miembros(std::ostream &os,const string &indent) const
//   {
//     os << indent + "\\base{" << lado << '}' << endl;
//     os << indent + "\\altura{" << altura << '}' << endl;
//   }

