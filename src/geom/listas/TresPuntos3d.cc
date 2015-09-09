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
//TresPuntos3d.cc

#include "TresPuntos3d.h"
#include "xc_utils/src/base/CmdStatus.h"

bool TresPuntos3d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(TresPuntos3d) Procesando comando: " << cmd << endl;
    if(status.Cmd() == "org")
      {
        _org.LeeCmd(status);
        return true;
      }
    else if(status.Cmd() == "p1")
      {
        _p1.LeeCmd(status);
        return true;
      }
    else if(status.Cmd() == "p2")
      {
        _p2.LeeCmd(status);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }
// void TresPuntos3d::salva_miembros(std::ostream &os,const std::string &indent) const
//   {
//     os << indent << "\\org{";
//     _org.salva_miembros(os,"");
//     os << '}' << endl;        
//     os << indent << "\\p1{";
//     _p1.salva_miembros(os,"");
//     os << '}' << endl;
//     os << indent << "\\p2{";
//     _p2.salva_miembros(os,"");
//     os << '}' << endl;
//   }
// void TresPuntos3d::SalvaCmd(std::ostream &os,const std::string &indent= "  ") const
//   {
//     const string str_indent= indent + "  ";
//     os << indent << "\\tres_puntos" << endl
//        << str_indent << '{' << endl;
//     salva_miembros(os,str_indent+ "  ");
//     os << str_indent  << '}' << endl;
//   }
