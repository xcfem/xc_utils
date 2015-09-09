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
//MEFSisCoo1DRect.cc

#include "SisCooRect1d3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Pos3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

bool SisCooRect1d3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SisCooRect1d3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "vdir")
      {
        Vector3d tmp;
        tmp.LeeCmd(status);
        SisCooRect1d3d::operator=(SisCooRect1d3d(tmp));
        return true;
      }
    else
      return SisCooXd3d::procesa_comando(status);
  }
SisCooRect1d3d::SisCooRect1d3d(const VGlobal &vX)
  : SisCooXd3d(1,vX)  //Eje 1 paralelo a Vx.
  {}
SisCooRect1d3d::SisCooRect1d3d(const PGlobal &o,const PGlobal &p)
  : SisCooXd3d(1,o,p) {}

SisCooRect1d3d::VGlobal SisCooRect1d3d::GetI(void) const
//Devuelve el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
SisCooRect1d3d::VGlobal SisCooRect1d3d::GetCooGlobales(const VLocal &v) const
{ return SisCooXd3d::GetCooGlobales(matriz_FT(1,1,v)); }
SisCooRect1d3d::VLocal SisCooRect1d3d::GetCooLocales(const SisCooRect1d3d::VGlobal &v) const
//Devuelve las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const matriz_FT tmp= SisCooXd3d::GetCooLocales(v);
    return VLocal(tmp(1));
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! i: Devuelve el vector unitario i.
any_const_ptr SisCooRect1d3d::GetProp(const std::string &cod) const
  {
    static VGlobal tmp_vg;
    if(cod=="i")
      {
        tmp_vg= GetI();
        return any_const_ptr(tmp_vg);
      }
    else
      return SisCooXd3d::GetProp(cod);
  }

