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
//GmGrupo3d.cc

#include "GmGrupo3d.h"
#include "xc_utils/src/base/CmdStatus.h"

#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d0/Punto3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/SemiRecta3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"

GEOM_FT GmGrupo3d::inercia(const Recta3d &e) const
//Devuelve el momento de inercia respecto a la recta e
  {
    if(objetos.empty()) return 0.0;
    if(!igual_dimension())
      {
        std::cerr << "¡Ojo!, GmGrupo3d::inercia: los objetos del grupo tienen distintas dimensiones." << std::endl;
      }
    register pdeque_geom_obj::const_iterator i(objetos.begin());
    register GEOM_FT retval((*i)->I(e));
    i++;
    for(;i!=objetos.end();i++)
      retval+= (*i)->I(e);
    return retval;
  }

GEOM_FT GmGrupo3d::Ix(void) const
//Momento de inercia respecto al CDG en ejes locales.
{ return inercia(Recta3d(Cdg(),Dir3d(1.0,0.0,0.0))); }
GEOM_FT GmGrupo3d::Iy(void) const
//Momento de inercia respecto al CDG en ejes locales.
{ return inercia(Recta3d(Cdg(),Dir3d(0.0,1.0,0.0))); }
GEOM_FT GmGrupo3d::Iz(void) const
//Momento de inercia respecto al CDG en ejes locales.
{ return inercia(Recta3d(Cdg(),Dir3d(0.0,0.0,1.0))); }
GEOM_FT GmGrupo3d::Pxy(void) const
  {
    std::cerr << "GmGrupo3d::Pxy no implementada, se devuelve 0." << std::endl;
    return 0.0;
  }

bool GmGrupo3d::procesa_comando(CmdStatus &status)
  {
    //std::cerr << "(GmGrupo3d) Procesando comando: " << cmd << std::endl;
    if(status.Cmd() == "punto3d")
      {
        Punto3d p;
        p.LeeCmd(status);
        push_back(p);
        return true;
      }
    else if(status.Cmd() == "segmento3d")
      {
        Segmento3d s;
        s.LeeCmd(status);
        push_back(s);
        return true;
      }
    else if(status.Cmd() == "semirrecta3d")
      {
        SemiRecta3d sr;
        sr.LeeCmd(status);
        push_back(sr);
        return true;
      }
    else if(status.Cmd() == "recta3d")
      {
        Recta3d r;
        r.LeeCmd(status);
        push_back(r);
        return true;
      }
    else
      return GeomObj::procesa_comando(status);
  }

Pos3d GmGrupo3d::Cdg(void) const
  {
    if(objetos.empty()) return Pos3d();
    if(!igual_dimension())
      {
        std::cerr << "¡Ojo!, GmGrupo3d::Cdg: los objetos del grupo tienen distintas dimensiones." << std::endl;
      }    register pdeque_geom_obj::const_iterator i(objetos.begin());
    GEOM_FT area_i= (*i)->AreaCdg();
    Vector3d num= (*i)->Cdg().VectorPos()*area_i;
    GEOM_FT denom(area_i);
    i++;
    for(;i!=objetos.end();i++)
      {
        area_i= (*i)->AreaCdg();
        num= num + (*i)->Cdg().VectorPos()*area_i;
        denom+= area_i;
      }
    num= num*(1/denom);
    return Origen3d+num;
  }
void GmGrupo3d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << "\\lista_geom" << std::endl;
    os << str_indent << '{' << std::endl;
    for(register pdeque_geom_obj::const_iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->SalvaCmd(os,str_indent+"  ");
    os << str_indent << "}\\c{fin lista_geom}" << std::endl;
  }

