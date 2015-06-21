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
//SisCooRect3d3d.cc

#include "SisCooRect3d3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/T3Cmd.h"
#include "xc_utils/src/base/any_const_ptr.h"

SisCooRect3d3d::SisCooRect3d3d(const VGlobal &v1,const VGlobal &v2)
  : SisCooXd3d(3,v1,v2) {}
SisCooRect3d3d::SisCooRect3d3d(const PGlobal &o,const PGlobal &p)
  : SisCooXd3d(3,o,p) {}
SisCooRect3d3d::SisCooRect3d3d(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : SisCooXd3d(3,p1,p2,p3) {}
SisCooRect3d3d::SisCooRect3d3d(const VGlobal &v1,const VGlobal &v2,const VGlobal &v3)
  : SisCooXd3d(3,v1,v2,v3) {}

bool SisCooRect3d3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd=  status.Cmd();
    if(verborrea>2)
      std::clog << "(SisCooRect3d3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "vectores")
      {
        VGlobal i,j;
        T2Cmd<VGlobal,VGlobal> tmp(i,"i",j,"j");
        tmp.LeeCmd(status);
        (*this)= SisCooRect3d3d(i,j);
        return true;
      }
    else if(cmd == "3puntos")
      {
        PGlobal p1,p2,p3;
        T3Cmd<PGlobal,PGlobal,PGlobal> tmp(p1,"p1",p2,"p2",p3,"p3");
        tmp.LeeCmd(status);
        (*this)= SisCooRect3d3d(p1,p2,p3);
        return true;
      }
    else
      return SisCooXd3d::procesa_comando(status);
  }
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetI(void) const
//Devuelve el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetJ(void) const
//Devuelve el vector unitario J en el sistema global.
  { return GetVDirEje(2); }
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetK(void) const
//Devuelve el vector unitario K en el sistema global.
  { return GetVDirEje(3); }
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetCooGlobales(const VLocal &v) const
//Devuelve las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  { return SisCooXd3d::GetCooGlobales(v.GetMatriz()); }
SisCooRect3d3d::VLocal SisCooRect3d3d::GetCooLocales(const VGlobal &v) const
//Devuelve las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const matriz_FT tmp= SisCooXd3d::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2),tmp(3));
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! i: Devuelve el vector unitario i.
//! j: Devuelve el vector unitario j.
//! k: Devuelve el vector unitario k.
any_const_ptr SisCooRect3d3d::GetProp(const std::string &cod) const
  {
    static VGlobal tmp_vg;
    if(cod=="i")
      {
        tmp_vg= GetI();
        return any_const_ptr(tmp_vg);
      }
    else if(cod=="j")
      {
        tmp_vg= GetJ();
        return any_const_ptr(tmp_vg);
      }
    else if(cod=="k")
      {
        tmp_vg= GetK();
        return any_const_ptr(tmp_vg);
      }
    else
      return SisCooXd3d::GetProp(cod);
  }
