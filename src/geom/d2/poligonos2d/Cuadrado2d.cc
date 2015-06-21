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
//Cuadrado2d.cc

#include "Cuadrado2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"


Cuadrado2d::Cuadrado2d(const Pos2d &o,const GEOM_FT &l)
  : Cuadrilatero2d(o,o+Vector2d(l,0),o+Vector2d(l,l),o+Vector2d(0,l)) {}

bool Cuadrado2d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(Cuadrado2d) Procesando comando: " << cmd << endl;
    if(status.Cmd() == "lado")
      {
        GEOM_FT lado= status.GetFloat();
        (*this)= Cuadrado2d(lado);
        return true;
      }
    else
      return Cuadrilatero2d::procesa_comando(status);
  }

void Cuadrado2d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    std::cerr << "Cuadrado2d::SalvaCmd no implementada." << std::endl;
    const std::string str_indent= indent + "  ";
    os << indent << "\\cuadrado" << std::endl
       << str_indent << '{' << std::endl;
    //salva_miembros(os,str_indent+ "  ");
    //os << str_indent + "  \\lado{" << lado << '}' << std::endl;
    os << str_indent  << '}' << std::endl;
  }
