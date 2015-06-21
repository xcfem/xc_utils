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
//PrismaTriang3d.cc

#include "PrismaTriang3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

bool PrismaTriang3d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(PrismaTriang3d) Procesando comando: " << cmd << endl;
    if(status.Cmd() == "lado")
      {
//         const double lado= status.GetFloat();
//         Seccion()= Cuadrado(lado);
        return true;
      }
    else
      return prisma_triang::procesa_comando(status);
  }
PrismaTriang3d::PrismaTriang3d(const Triangulo3d &tr,const double &h)
  : prisma_triang(Triangulo3d(tr),h) {}
PrismaTriang3d::PrismaTriang3d(const PrismaTriang3d &c)
  : prisma_triang(c) {}
PrismaTriang3d &PrismaTriang3d::operator=(const PrismaTriang3d &c)
  {
    prisma_triang::operator=(c);
    return *this;
  }
GeomObj *PrismaTriang3d::clon(void) const
  { return new PrismaTriang3d(*this); }

void PrismaTriang3d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << "\\PrismaTriang3d" << std::endl;
    os << str_indent << '{' << std::endl;
	//prisma_PrismaTriang3d::salva_miembros(os,str_indent+"  ");
    os << str_indent << '}' << std::endl;
  }
