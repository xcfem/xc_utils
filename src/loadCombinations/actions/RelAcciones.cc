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
//RelAcciones.cxx

#include "RelAcciones.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/utils_any.h"
#include "boost/regex.hpp"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"

//! @brief Elimina el factor que multiplica a la acción en la cadena de
//! la forma "1.35*A" que se pasa como parámetro.
std::string cmb_acc::RelAcciones::limpia(const std::string &str)
  {
    std::string retval= str;
    if(str.find('*')!=std::string::npos)
      retval=copia_desde(str,'*');
    return retval;
  }

//! @brief Devuelve los sumandos de la cadena de caracteres que se pasa como parámetro.
std::deque<std::string> cmb_acc::RelAcciones::get_sumandos_combinacion(const std::string &str)
  {
    std::deque<std::string> retval;
    if((has_char(str,'(')) || (has_char(str,')'))) //Tiene paréntesis
      {
        const ExprAlgebra e(str);
        const std::string s(expand(e).GetString());
        retval= separa_sumandos(s);
      }
    else
      return separa_sumandos(str);
    return retval;
  }

//! @brief Devuelve los nombres de las acciones que participan en la combinación.
std::deque<std::string> cmb_acc::RelAcciones::get_nmb_acciones_combinacion(const std::string &str)
  {
    std::deque<std::string> retval= get_sumandos_combinacion(str);
    for(std::deque<std::string>::iterator i= retval.begin();i!=retval.end();i++)
      (*i)= q_blancos(limpia(*i)); 
    return retval;
  }

//! @brief Constructor por defecto.
cmb_acc::RelAcciones::RelAcciones(void)
  : EntCmd(), incompatibles(0), maestras(0), nodet(false), contiene_incomp(false) {}

//! @brief Devuelve una cadena de caracteres con los nombres de la lista que se pasa como parámetro separados por comas.
std::string cmb_acc::RelAcciones::nombres(const dq_string &l) const
  {
    std::string retval;
    if(!l.empty())
      {
        const_iterator i=l.begin();
        retval= (*i); i++;
        for(;i!=l.end();i++)
          retval+= "," + (*i);
      }
    return retval;
  }

//! @brief Añade a las acciones incompatibles la lista de expresiones regulares que se pasa como parámetro.
void cmb_acc::RelAcciones::concat_incompatibles(const dq_string &otra)
  {
    for(const_iterator i= otra.begin();i!=otra.end();i++)
      AgregaIncompatible(*i);
  }

//! @brief Añade a las acciones maestras la lista de expresiones regulares que se pasa como parámetro.
void cmb_acc::RelAcciones::concat_maestras(const dq_string &otra)
  {
    for(const_iterator i= otra.begin();i!=otra.end();i++)
      AgregaMaestra(*i);
  }

//! \fn cmb_acc::RelAcciones::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::RelAcciones::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(Accion) Procesando comando: " << cmd << std::endl;
    if(cmd == "incompatibles")
      {
        const std::string str= q_blancos(interpretaString(status.GetString()));
        if(str!="") AgregaIncompatible(str);
        return true;
      }
    else if(cmd == "maestras")
      {
        const std::string str= q_blancos(interpretaString(status.GetString()));
        if(str!="") AgregaMaestra(str);
        return true;
      }
    else if(cmd == "no_determinante")
      {
        status.GetString(); //Ignoramos argumentos.
        nodet= true;
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve verdadero si alguna de las cadenas de caracteres de nmbAccionesComb
//! verifican la expresión regular "exprReg".
bool cmb_acc::RelAcciones::match(const std::string &exprReg,const dq_string &nmbAccionesComb) const
  {
    bool retval= false;
    boost::regex expresion(exprReg); //Inicializamos la expresión regular.
    for(const_iterator j= nmbAccionesComb.begin();j!=nmbAccionesComb.end();j++)
      {
        const std::string &test= *j;
        retval= regex_match(test, expresion);
        if(retval) break; //No hace falta seguir.
      }
    return retval;
  }

//! @brief Devuelve verdadero si alguna de las cadenas de caracteres que se pasan como parámetro
//! verifica alguna de las expresiones del contenedor de expresiones regulares "exprReg".
bool cmb_acc::RelAcciones::match_any(const dq_string &exprReg,const dq_string &nmbAccionesComb) const
  {
    bool retval= false;
    for(const_iterator i= exprReg.begin();i!=exprReg.end();i++)
      {
        const std::string str= *i;
        retval= match(str,nmbAccionesComb);
        if(retval) break; //No hace falta seguir.
      }
    return retval;
  }

//! @brief Devuelve verdadero si para cada una de las expresiones regulares de "exprReg"
//! existe alguna cadena de caracteres de nmbAccionesComb que la verifica.
bool cmb_acc::RelAcciones::match_all(const dq_string &exprReg,const dq_string &nmbAccionesComb) const
  {
    bool retval= false;
    for(const_iterator i= exprReg.begin();i!=exprReg.end();i++)
      {
        const std::string str= *i;
        retval= match(str,nmbAccionesComb);
        if(!retval) break; //No hace falta seguir.
      }
    return retval;
  }

//! @brief Devuelve verdadero si la cadenas de caracteres que se pasan como parámetro
//! verifica alguna de las expresiones del contenedor "incompatibles".
bool cmb_acc::RelAcciones::matchIncompatibles(const dq_string &sumandos) const
  { return match_any(incompatibles,sumandos); }

//! @brief Devuelve verdadero si la acción cuyo nombre se pasa como parámetro es incompatible con esta,
//! es decir que ambas no pueden estar presentes en la misma hipótesis.
bool cmb_acc::RelAcciones::incompatible(const std::string &nmb) const
  {
    bool retval= false;
    const std::deque<std::string> sumandos= get_nmb_acciones_combinacion(nmb);
    retval= matchIncompatibles(sumandos);
    return retval;
  }

//! @brief Devuelve verdadero si la acción cuyo nombre se pasa como parámetro es maestra de esta,
//! es decir que ambas no pueden estar presentes en la misma hipótesis.
bool cmb_acc::RelAcciones::esclavaDe(const std::string &nmb) const
  { 
    bool retval= false;
    for(const_iterator i= maestras.begin();i!=maestras.end();i++)
      {
        boost::regex expresion(*i); //Inicializamos la expresión regular.
        retval= regex_match(nmb,expresion);
        if(!retval) break; //No hace falta seguir.
      }
    return retval;
  }

//! @brief Elimina de la lista de maestras aquellas que ya se encuentran en la lista de
//! nombres de acciones que se pasa como parámetro.
void cmb_acc::RelAcciones::updateMaestras(const std::string &nmb)
  {
    if(!maestras.empty())
      {
        const dq_string nmbAccionesComb= get_nmb_acciones_combinacion(nmb); //Nombres de las acciones de esta combinacion.
        dq_string nuevas;
        for(const_iterator i= maestras.begin();i!=maestras.end();i++)
          if(!match(*i,nmbAccionesComb)) //No se encontró la maestra.
            nuevas.push_back(*i);
        maestras= nuevas;
      }
  }

void cmb_acc::RelAcciones::concat(const RelAcciones &otra)
  {
    concat_incompatibles(otra.incompatibles);
    concat_maestras(otra.maestras);
  }

std::string cmb_acc::RelAcciones::nombresIncompatibles(void) const
  { return nombres(incompatibles); }
std::string cmb_acc::RelAcciones::nombresMaestras(void) const
  { return nombres(maestras); }

void cmb_acc::RelAcciones::Print(std::ostream &os) const
  {
    os << "incompatibles: {" << nombresIncompatibles() << "}; maestras: {"
       << nombresMaestras() << "}";
    if(contiene_incomp) os << " contiente incompatibles." << std::endl;
  }

//! @brief Devuelve la propiedad cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::RelAcciones::GetProp(const std::string &cod) const
  {
    if(cod == "contieneIncomp")
      return any_const_ptr(contiene_incomp);
    else if(cod == "getMaestras")
      {
        tmp_gp_str= nombresMaestras();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "getIncompatibles")
      {
        tmp_gp_str= nombresIncompatibles();
        return any_const_ptr(tmp_gp_str);
      }
    else
      return EntCmd::GetProp(cod);
  }

std::ostream &cmb_acc::operator<<(std::ostream &os,const RelAcciones &a)
  {
    a.Print(os);
    return os;
  }

//! @brief Devuelve las combinaciones filtrando las que contienen acciones incompatibles.
const cmb_acc::LoadCombinationVector &cmb_acc::getCompatibles(const LoadCombinationVector &comb)
  {
    static LoadCombinationVector retval;
    const size_t sz= comb.size();
    if(sz<1)
      {
        retval.resize(0);
        return retval;
      }
    LoadCombinationVector tmp(sz);
    size_t cont=0;
    for(size_t i=0;i<sz;i++)
      if(!(comb[i].getRelaciones().contieneIncomp())) //Si no contiene acciones incompatibles.
       {
         tmp[cont]= comb[i]; //La agregamos.
         cont++;
       }
    retval.resize(cont);
    for(size_t i=0;i<cont;i++)
      retval[i]= tmp[i];
    return retval;
  }

//! @brief Filtra las combinaciones casos en las que las acciones esclavas aparecen sin su maestra.
const cmb_acc::LoadCombinationVector &cmb_acc::filtraCombsEsclavasHuerfanas(const cmb_acc::LoadCombinationVector &comb)
  {
    static LoadCombinationVector retval;
    const size_t sz= comb.size();
    if(sz<1)
      {
        retval.resize(0);
        return retval;
      }
    LoadCombinationVector tmp(sz);
    size_t cont=0;
    for(size_t i=0;i<sz;i++)
      if(!(comb[i].getRelaciones().tieneHuerfanas())) //No contiene esclavas huerfanas.
        {
          tmp[cont]= comb[i]; //La agregamos.
          cont++;
        }
    retval.resize(cont);
    for(size_t i=0;i<cont;i++)
      retval[i]= tmp[i];
    return retval;
  }
