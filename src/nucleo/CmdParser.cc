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
//CmdParser.cc

#include "CmdParser.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"
#include "boost/any.hpp"
#include "xc_utils/src/base/utils_any.h"
#include "EntProp.h"

//! @brief Quita los paréntesis de la cadena que se le pasa como parámetro.
std::string CmdParser::quita_parentesis(const std::string &str,const char &abre,const char &cierra)
  {
    size_t inicio= 0,sz=str.size();
    if(str[0]==abre) inicio= 1;
    if(str[sz-1]==cierra) sz=sz-2;
    return str.substr(inicio,sz);
  }

//! @brief Devuelve la subcadena de str limitada por los caracteres 'abre' y 'cierra.
std::string CmdParser::get_substr(const std::string &str,const char &abre,const char &cierra)
  {
    std::string retval("");
    const size_t sz= str.size();
    if(sz<2) return retval; //Al menos debería tener un caracter abre y otro cierra.
    if(str[0]!= abre) return retval; //Debería comenzar con el carácter abre.
    size_t i= 1,cuenta_llaves= 1; retval+= str[0]; //Incializamos.
    while(cuenta_llaves && (i<sz))
      {
        const char c= str[i++];
        if(c == abre) cuenta_llaves++;
        if(c == cierra) cuenta_llaves--;
        retval+= c;
      }
    return retval;
  }

//! @brief Devuelve verdadero si no hay problemas con comillas,
//! corchetes o paréntesis.
bool CmdParser::check_cmd_str(const std::string &str_cmd) const
  {
    bool retval= true;
    if(str_cmd.empty())
      retval= false;
    if(!check_comillas(str_cmd))
      retval= false;
    if(!check_parentesis(str_cmd))
      retval= false;
    if(!check_corchetes(str_cmd))
      retval= false;
    return retval;
  }

//! @brief Asigna valores a los miembros a partir de la cadena de caracteres
//! que se pasa como parámetro.
//! La cadena de caracteres devuelta está formada por los caracteres que siguen al
//! carácter punto '.' y se utiliza en PropParser como nombre de la propiedad
//! ver PropParser::PropParser(const std::string &str_prop).
void CmdParser::parse(const std::string &str_cmd)
  {
    if(check_cmd_str(str_cmd))
      {
        const size_t sz= str_cmd.size();
        int stop= -1;
        for(size_t i=0;i<sz;i++)
          {
            const char c= str_cmd[i];
            if( (c=='(') || (c=='[') || (c=='.') )
              {
                stop= i;
                break;
              }
          }
        std::string resto= "";
        if(stop<0) //No ha encontrado ( ni [ ni .
          nmb_cmd= str_cmd;
        else
          {
            if(stop>0)
              nmb_cmd= str_cmd.substr(0,stop);
            resto= str_cmd.substr(stop,sz);

            while(resto.size())
              {
                const size_t sz_resto= resto.size();
                if(resto[0]=='(')
                  {
                    args= get_substr(resto,'(',')'); //Obtenemos los argumentos.
                    resto= resto.substr(args.size(),sz_resto);
                    args= quita_parentesis(args,'(',')');
                  }
                else
                  if(resto[0]=='[')
                    {
                      const std::string tmp= get_substr(resto,'[',']'); //Obtenemos los indices.
                      resto= resto.substr(tmp.size(),sz_resto);
                      if(indices.size()) //Si ya se habían leído índices.
                        indices+= ',' + quita_parentesis(tmp,'[',']');
                      else
                        indices= quita_parentesis(tmp,'[',']');
                    }
                  else
                    if(resto[0]=='.')
                      {
                        nmb_miembro= q_car_i(resto,'.');
                        resto= "";
                      }
                    else
                      {
                        std::cerr << "CmdParser; error en expresión: '" << str_cmd
                                  << "', se obtuvo la subexpresión: '" << resto << "'" << std::endl;
                        break;
                      }
              }
          }
      }
    cmd= nmb_cmd;
    if(!nmb_miembro.empty())
      cmd+= "."+nmb_miembro;
  }

//! @brief Constructor.
CmdParser::CmdParser(const std::string &str)
  : nmb_cmd(""), args(""), indices(""), nmb_miembro("")
  { parse(str); }

void CmdParser::ClearCmd(void)
  {
    nmb_cmd.clear();
    cmd.clear();
  }

void CmdParser::Clear(void)
  {
    ClearCmd();
    args.clear();
    indices.clear();
    nmb_miembro.clear();
  }

//! @brief Devuelve el nombre de la propiedad.
const std::string &CmdParser::GetCmd(void) const
  { return cmd; }

//! @brief Devuelve el nombre de la propiedad.
const std::string &CmdParser::GetNmbCmd(void) const
  { return nmb_cmd; }

//! @brief Devuelve los argumentos.
const std::string &CmdParser::GetArgs(void) const
  { return args; }

//! @brief Devuelve los indices.
const std::string &CmdParser::GetIndices(void) const
  { return indices; }

//! @brief Devuelve el miembro.
const std::string &CmdParser::GetMiembro(void) const
  { return nmb_miembro; }

//! @brief Devuelve verdadero si el comando tiene índices.
bool CmdParser::TieneIndices(void) const
  { return indices.size()>0; }

//! @brief Devuelve verdadero si el comando tiene argumentos.
bool CmdParser::TieneArgs(void) const
  { return args.size()>0; }

//! @brief Devuelve verdadero si el comando tiene miembros.
bool CmdParser::TieneMiembro(void) const
  { return !nmb_miembro.empty(); }

//! @brief Devuelve verdadero si el comando no tiene ni miembros ni índices ni argumentos.
bool CmdParser::Simple(void) const
  {
    if(TieneMiembro()) return false;
    if(TieneIndices()) return false;
    if(TieneArgs()) return false;
    return true;
  }



//! @brief Devuelve los argumentos separados por comas.
std::deque<boost::any> CmdParser::SeparaArgs(const EntProp *ptr_ent) const
  {
    std::deque<boost::any> retval;
    if(TieneArgs())
      retval= ptr_ent->crea_deque_boost_any(args);
    return retval;
  }

//! @brief Devuelve los índices.
std::deque<boost::any> CmdParser::SeparaIndices(const EntProp *ptr_ent) const
  {
    std::deque<boost::any> retval;
    if(TieneIndices())
      retval= ptr_ent->crea_deque_boost_any(indices);
    if(retval.size()==1) //Quizá estan en forma de vector.
      {
        if(boost_any_is_vector_any(retval[0]))
          {
            const std::vector<boost::any> tmp= boost_any_to_vector_any(retval[0]);
            retval.clear();
            retval.insert(retval.begin(),tmp.begin(),tmp.end());
          }
      }
    return retval;
  }

//! @brief Devuelve los índices como vector de cadenas de caracteres.
std::vector<std::string> CmdParser::getIndicesAsStrings(const EntProp *ptr_ent) const
  {
    std::vector<std::string> retval;
    const std::deque<boost::any> fnc_indices= SeparaIndices(ptr_ent);
    const size_t sz= fnc_indices.size();
    if(sz>0)
      {
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_string(fnc_indices[i]);
      }
    return retval;
  }

//! @brief Devuelve los índices como vector de enteros.
std::vector<int> CmdParser::getIndicesAsInts(const EntProp *ptr_ent) const
  {
    std::vector<int> retval;
    const std::deque<boost::any> fnc_indices= SeparaIndices(ptr_ent);
    const size_t sz= fnc_indices.size();
    if(sz>0)
      {
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_int(fnc_indices[i]);
      }
    return retval;
  }

//! @brief Devuelve los índices como vector de doubles.
std::vector<double> CmdParser::getIndicesAsDoubles(const EntProp *ptr_ent) const
  {
    std::vector<double> retval;
    const std::deque<boost::any> fnc_indices= SeparaIndices(ptr_ent);
    const size_t sz= fnc_indices.size();
    if(sz>0)
      {
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_double(fnc_indices[i]);
      }
    return retval;
  }

//! @brief Devuelve los índices como vector de size_t.
std::vector<size_t> CmdParser::getIndicesAsSzts(const EntProp *ptr_ent) const
  {
    std::vector<size_t> retval;
    const std::deque<boost::any> fnc_indices= SeparaIndices(ptr_ent);
    const size_t sz= fnc_indices.size();
    if(sz>0)
      {
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_size_t(fnc_indices[i]);
      }
    return retval;
  }

//! @brief Imprime los miembros.
void CmdParser::Print(std::ostream &os) const
  {
    os << "nombre comando: '" << nmb_cmd << "'" << std::endl
       << "argumentos: '" << args << "'" << std::endl
       << "indices: '" << indices << "'" << std::endl;
  }
