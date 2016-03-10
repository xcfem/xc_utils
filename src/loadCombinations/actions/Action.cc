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
//Action.cxx

#include "Action.h"
#include "boost/lexical_cast.hpp"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_basic/src/texto/en_letra.h"
#include "xc_basic/src/texto/latex.h"
#include "xc_utils/src/base/Record.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "ActionRValueList.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"

const double cmb_acc::Action::zero= 1e-6;

//! @brief Constructor por defecto.
cmb_acc::Action::Action(const std::string &n, const std::string &descrip)
  : EntConNmb(n), descripcion(descrip),relaciones(), f_pond(1.0) {}

//! \fn cmb_acc::Action::NULA(void)
//! @brief Devuelve una acción nula.
cmb_acc::Action cmb_acc::Action::NULA(void)
  {
    Action retval;
    retval.f_pond= 0.0;
    return retval;
  }

//! @brief Devuelve verdadero si la acción no es combinación de otras.
bool cmb_acc::Action::Simple(void) const
  { return (GetNombre().find('+')==std::string::npos); }

//! @brief Devuelve el nombre expandido aplicando la propiedad distributiva
//! del producto es decir si la combinación se llama '1.5*G1+1.35*(G2+F2)'
//! devuelve '1.5*G1+1.35*G2+1.35*F2'.
const std::string cmb_acc::Action::GetNombreExpandido(void) const
  {
    std::string retval= GetNombre();
    if(has_char(retval,'('))
      {
        const ExprAlgebra tmp(retval);
        retval= expand(tmp).GetString();
      }
    return retval;
  }

//! @brief Devuelve la descomposición cuando la acción es una combinación.
cmb_acc::Action::map_descomp cmb_acc::Action::getDescomp(void) const
  {
    map_descomp descomp;
    typedef std::deque<std::string> dq_string;
    dq_string str_sumandos= ActionRelationships::get_sumandos_combinacion(GetNombre());
    for(dq_string::iterator i= str_sumandos.begin();i!=str_sumandos.end();i++)
      {
        const std::string &str_sum_i= *i;
        dq_string str_prod= separa_cadena(str_sum_i,"*");
        const size_t sz2= str_prod.size();
        if(sz2!=2)
	  std::cerr << "El sumando: " << str_sum_i << " está mal expresado." << std::endl;
        else
          {
            const float factor= boost::lexical_cast<float>(q_blancos(str_prod[0]));
            const std::string nmb_acc= q_blancos(str_prod[1]);
            descomp[nmb_acc]= factor;
          } 
      }
    return descomp;
  }

//! @brief Cuando se trata de una combinación, devuelve los coeficientes que
//! multiplican a cada una de las acciones que se pasa como parámetro.
std::vector<double> cmb_acc::Action::getCoeficientes(const std::vector<std::string> &base) const
  {
    const size_t sz= base.size();
    std::vector<double> retval(sz,0.0);
    const map_descomp descomp= getDescomp();
    for(size_t i= 0;i<sz;i++)
      {
        const std::string &nmb_accion= base[i];
	map_descomp::const_iterator j= descomp.find(nmb_accion);
        if(j!=descomp.end())
          retval[i]= j->second;
      }
    return retval;
  }

//! \fn cmb_acc::Action::limpia_nombres(void)
//! @brief ??
void cmb_acc::Action::limpia_nombres(void)
  {
    EntConNmb::Nombre()= ActionRelationships::limpia(GetNombre());
    descripcion= ActionRelationships::limpia(descripcion);
  }

//! \fn cmb_acc::Action::multiplica(const double &d)
//! @brief Multiplica la acción por el escalar que se pasa como parámetro.
void cmb_acc::Action::multiplica(const double &d)
  {
    f_pond*= d;
    limpia_nombres();
    const std::string strnum= num2str(f_pond,2);
    EntConNmb::Nombre()= strnum + "*" + GetNombre();
    descripcion= strnum + "*" + descripcion;
  }

//! \fn cmb_acc::Action::suma(const Action &f)
//! @brief Suma a ésta la acción que se pasa como parámetro (sólo en el caso de que sean compatibles).
void cmb_acc::Action::suma(const Action &f)
  {
    if(f.Nula(zero)) return;

    //Marcamos las combinaciones incompatibles.
    if((Incompatible(f))) 
      relaciones.setContieneIncomp(true);
    if(f.relaciones.contieneIncomp())
      relaciones.setContieneIncomp(true);

    if(GetNombre().size()>0)
      {
        EntConNmb::Nombre()+= " + " + f.GetNombre();
        descripcion+= " + " + f.descripcion;
      }
    else
      {
	EntConNmb::Nombre()= f.GetNombre();
        descripcion= f.descripcion;
      }
    relaciones.concat(f.relaciones);
    relaciones.updateMaestras(GetNombre());
    if(Nula(zero) && f.Nula(zero)) //Si ambas son nulas la suma es nula.
      f_pond= 0.0;
    else //En otro caso no lo sabemos.
      f_pond= 1.0;
    if(!Owner())
      set_owner(const_cast<EntCmd *>(f.Owner()));
  }

//! \fn cmb_acc::Action::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::Action::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(Action) Procesando comando: " << cmd << std::endl;
    if(cmd == "nombre")
      {
	SetNombre(interpretaString(status.GetString()));
        return true;
      }
    else if(cmd == "descripcion")
      {
        descripcion= interpretaString(status.GetString());
        return true;
      }
    else if(cmd == "relaciones")
      {
        relaciones.LeeCmd(status);
        return true;
      }
    else
      return EntConNmb::procesa_comando(status);
  }

//! @brief Devuelve verdadero si la acción que se pasa como parámetro es incompatible con esta,
//! es decir que ambas no pueden estar presentes en la misma hipótesis.
//!
//! La acción será incompatible cuando su nombre verifique alguna de las expresiones
//! regulares contenidas en el miembro incompatibles.
//! La acción no podrá ser incompatible consigo misma.
bool cmb_acc::Action::incompatible(const Action &f) const
  {
    bool retval= false;
    if(this != &f) //La carga no puede ser incompatible consigo misma.
      retval= relaciones.incompatible(f.GetNombre());
    return retval;
  }

//! \fn cmb_acc::Action::Incompatible(const Action &f) const
//! @brief Devuelve verdadero si la acción que se pasa como parámetro es incompatible con esta,
//! es decir que ambas no pueden estar presentes en la misma hipótesis.
//!
//! @param f: Action cuya incompatibilidad con ésta se comprueba.
//! La acción será incompatible cuando su nombre verifique alguna de las expresiones
//! regulares contenidas en el miembro incompatibles.
//! La acción no podrá ser incompatible consigo misma.
bool cmb_acc::Action::Incompatible(const Action &f) const
  {
    bool retval= false;
    if(this != &f) //La carga no puede ser incompatible consigo misma.
      {
        retval= relaciones.incompatible(f.GetNombre());
        if(!retval) retval= f.relaciones.incompatible(GetNombre());
      }
    return retval;
  }

std::string cmb_acc::Action::ListaStrIncompatibles(ActionRValueList *af) const
  {
    std::string retval;
    if(af)
      {
        std::deque<const cmb_acc::Action *> incomp= listaIncompatibles(this,af->begin(),af->end());
        if(!incomp.empty())
          retval= nombresPtrAcciones(incomp.begin(),incomp.end());
      }
    else
      std::cerr << "El puntero a la familia de acciones es nulo." << std::endl;
    return retval; 
  }


void cmb_acc::Action::Print(std::ostream &os) const
  {
    os << GetNombre();
    relaciones.Print(os);
  }

//! @brief Devuelve la propiedad cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::Action::GetProp(const std::string &cod) const
  {
    if(cod == "getNombre")
      {
        tmp_gp_str= GetNombre();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "getNombreExpandido")
      {
        tmp_gp_str= ascii2latex(GetNombreExpandido());
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "getDescripcion")
      {
        tmp_gp_str= GetDescripcion();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "getDescomp")
      {
        const map_descomp tmp= getDescomp();
        tmp_gp_record.clearProps();
        for(map_descomp::const_iterator i= tmp.begin();i!=tmp.end();i++)
          tmp_gp_record.crea_user_prop(i->first,i->second);
        return any_const_ptr(tmp_gp_record);
      }
    else if(cod == "getRelaciones")
      { return any_const_ptr(&relaciones); }
    else if(cod == "getCoeficientes")
      {
        const std::vector<std::string> base= popVectorString(cod);
        const std::vector<double> tmp= getCoeficientes(base);
        tmp_gp_mdbl= m_double(1,tmp.size(),tmp.begin(),tmp.end());
        return any_const_ptr(tmp_gp_mdbl);
      }
    else
      return EntConNmb::GetProp(cod);
  }

//! @brief Devuelve verdadero si las acciones de índices i y j son incompatibles.
bool cmb_acc::incompatibles(const Action &acc_i,const Action &acc_j)
  {
    bool retval= false;
    if(&acc_i!=&acc_j) //Una acción nunca es incompatible consigo misma.
      {
        if(acc_i.Incompatible(acc_j))
          retval= true;
        else
          if(acc_j.Incompatible(acc_i)) retval= true;
      }
    return retval;
  }

std::ostream &cmb_acc::operator<<(std::ostream &os,const Action &a)
  {
    a.Print(os);
    return os;
  }
