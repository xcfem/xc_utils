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
//SisCooRect1d2d.cc

#include "SisCooRect1d2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/pos_vec/Dir2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"
#include "xc_utils/src/base/any_const_ptr.h"

bool SisCooRect1d2d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SisCooRect1d2d) Procesando comando: " << cmd << std::endl;
    if(cmd == "cos_x")
      {
        put(1,1,double_to_FT(interpretaDouble(status.GetString())));
        return true;
      }
    else if(cmd == "cos_y")
      {
        put(1,2,double_to_FT(interpretaDouble(status.GetString())));
        return true;
      }
    else
      return SisCooXd2d::procesa_comando(status);
  }
SisCooRect1d2d::SisCooRect1d2d(const VGlobal &vX)
  : SisCooXd2d(1,vX) {} //Eje 1 paralelo a Vx.
SisCooRect1d2d::SisCooRect1d2d(const PGlobal &p1,const PGlobal &p2)
  : SisCooXd2d(1,p1,p2) {} //Eje 1 desde p1 a p2.

SisCooRect1d2d::VGlobal SisCooRect1d2d::GetI(void) const
//Devuelve el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
SisCooRect1d2d::VGlobal SisCooRect1d2d::GetCooGlobales(const VLocal &v) const
//Devuelve las componentes del vector v 
//que se pasa como parámetro expresado en locales
//expresadas en coordenadas globales.
  { return SisCooXd2d::GetCooGlobales(matriz_FT(1,1,v)); }
SisCooRect1d2d::VLocal SisCooRect1d2d::GetCooLocales(const SisCooRect1d2d::VGlobal &v) const
//Devuelve las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const matriz_FT tmp= SisCooXd2d::GetCooLocales(v);
    return tmp(1,1);
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! i: Devuelve el vector unitario i.
any_const_ptr SisCooRect1d2d::GetProp(const std::string &cod) const
  {
    static VGlobal tmp_vg;
    if(has_char(cod,'('))
      {
        std::deque<std::string> fnc_args= getargs(cod); //Averiguamos si es de la forma fnc(arg1,arg2,...)
        if(fnc_args.size()>1) //Parece que lo es.
          {
            if(fnc_args[0]=="en_globales")
              {
                const GEOM_FT x= double_to_FT(ExprAlgebra(fnc_args[1].c_str()).ToNum()); //Coordenada local.
                tmp_vg= GetCooGlobales(x);
                return any_const_ptr(tmp_vg);
              }
            else if(fnc_args[0]=="en_locales")
              {
                const GEOM_FT x= double_to_FT(ExprAlgebra(fnc_args[1].c_str()).ToNum()); //Coordenada x.
                const GEOM_FT y= double_to_FT(ExprAlgebra(fnc_args[2].c_str()).ToNum()); //Coordenada y.
                static VLocal tmp_vl= GetCooLocales(VGlobal(x,y));
                return any_const_ptr(tmp_vl);
              }
            else
              return any_const_ptr();
          }
        else
          return any_const_ptr();
      }
    else
      if(cod=="i")
        {
          tmp_vg= GetI(); 
          return any_const_ptr(tmp_vg);
        }
      else
        return SisCooXd2d::GetProp(cod);
  }
