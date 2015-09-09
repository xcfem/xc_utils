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
//Punto2d.cc

#include "Punto2d.h"
#include <plotter.h>
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

bool Punto2d::procesa_comando(CmdStatus &status)
  {
    const string &cmd= deref_cmd(status.Cmd());
    //cerr << "(Punto2d) Procesando comando: " << cmd << endl;
    if(cmd == "pos_2d")
      {
        org.LeeCmd(status);
        return true;
      }
    else
      return GeomObj::procesa_comando(status);
  }
void Punto2d::Print(std::ostream &os) const
  { os << org; }
void Punto2d::Plot(Plotter &plotter) const
  {
    org.Plot(plotter);
  }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Punto2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d pA= trf2d.Transforma(org);
    (*this)= Punto2d(pA);
  }

void Punto2d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << "\\Punto2d" << std::endl
       << str_indent << '{' << std::endl;
    org.SalvaCmd(os,str_indent+ "  ");
    os << str_indent  << '}' << std::endl;
  }
