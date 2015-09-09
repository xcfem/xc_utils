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
//VDesliz2d.cc

#include "VDesliz2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

//! @brief Constructor.
VDesliz2d::VDesliz2d(const Pos2d &o,const Pos2d &p)
  : Vector2d(p-o), org(o) {}

bool VDesliz2d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(VDesliz2d) Procesando comando: " << status.Cmd() << endl;
    if(status.Cmd() == "vector")
      {
        Vector2d::LeeCmd(status);
        return true;
      }
    else if(status.Cmd() == "pto_aplic")
      {
        org.LeeCmd(status);
        return true;
      }
    else
      return Vector2d::procesa_comando(status);
  }

GEOM_FT VDesliz2d::Momento(const Pos2d &o) const
//Momento de un vector deslizante respecto a un punto.
  {
    GEOM_FT retval(0.0);
    if(!this->Nulo()) //Si ESTE vector no es nulo.
      {
        Vector2d r= org - o;
        if(!r.Nulo()) //Si r no es nulo.
          if(!paralelos(r,*this)) //Si r y ESTE no son paralelos
            retval= r.x()*this->y()-this->x()*r.y();
      }
    return retval;
  }

GEOM_FT inverso(const GEOM_FT &p)
  { return GEOM_FT(1.0/p); }

VDesliz2d operator/(const VDesliz2d &m,const GEOM_FT &p)
  { return m*inverso(p); }

VDesliz2d operator-(const VDesliz2d &v)
  {
    VDesliz2d neg(v);
    neg.Neg();
    return neg;
  }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
any_const_ptr VDesliz2d::GetProp(const std::string &cod) const
  {
    if(cod=="org")
      {
        return any_const_ptr(&org);
      }
    else if(cod=="modulo")
      {
        tmp_gp_dbl= GetModulus();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="momento") //Momento respecto al punto cuyas coordenadas se pasan como parámetro.
      {
        double x0= 0.0;
        double y0= 0.0;
        if(InterpreteRPN::Pila().size()>1)
          {
            x0= convert_to_double(InterpreteRPN::Pila().Pop());
            y0= convert_to_double(InterpreteRPN::Pila().Pop());
          }
        else if(InterpreteRPN::Pila().size()>0)
          {
            x0= convert_to_double(InterpreteRPN::Pila().Pop());
          }
        tmp_gp_dbl= Momento(Pos2d(x0,y0));
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="brazo") //Brazo respecto al punto cuyas coordenadas se pasan como parámetro.
      {
        double x0= 0.0;
        double y0= 0.0;
        if(InterpreteRPN::Pila().size()>1)
          {
            x0= convert_to_double(InterpreteRPN::Pila().Pop());
            y0= convert_to_double(InterpreteRPN::Pila().Pop());
          }
        else if(InterpreteRPN::Pila().size()>0)
          {
            x0= convert_to_double(InterpreteRPN::Pila().Pop());
          }
        tmp_gp_dbl= Momento(Pos2d(x0,y0))/GetModulus();
        return any_const_ptr(tmp_gp_dbl);
      }
    else
      return Vector2d::GetProp(cod);
  }
