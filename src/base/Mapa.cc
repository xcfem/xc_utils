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
//Mapa.cc

#include "Mapa.h"
#include "CmdStatus.h"
#include "any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "../nucleo/aux_any.h"
#include "../nucleo/InterpreteRPN.h"

//! @brief Constructor por defecto.
Mapa::Mapa(EntCmd *owr)
  : EntWOwner(owr), mapa() {}


//! @brief Borra los elementos del mapa.
void Mapa::clear(void)
  { mapa.clear(); }

//! @brief Borra las propiedades de usuario del objeto y los elementos del mapa.
void Mapa::clearAll(void)
  {
    EntWOwner::clearProps();
    mapa.clear();
  }

size_t Mapa::size(void) const
  { return mapa.size(); }
Mapa::iterator Mapa::begin(void)
  { return mapa.begin(); }
Mapa::iterator Mapa::end(void)
  { return mapa.end(); }
Mapa::const_iterator Mapa::begin(void) const
  { return mapa.begin(); }
Mapa::const_iterator Mapa::end(void) const
  { return mapa.end(); }
bool Mapa::empty(void) const
  { return mapa.empty(); }


//! @brief Lee un objeto Record desde archivo
//! Soporta los comandos:
bool Mapa::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string msg_error= "(Mapa) Procesando comando: "+ cmd;
    if(verborrea>2)
      std::clog << msg_error << std::endl;
    if(cmd == "inserta")
      {
        const CmdParser &parser= status.Parser();
        const std::string bloque= status.GetBloque();
        if(!parser.TieneIndices())
	  std::cerr << msg_error << "; uso: " << cmd << "[s]{valor}" << std::endl;
        else
          {
	    std::deque<boost::any> indices= crea_deque_boost_any(parser.GetIndices());
            const std::string s= boost_any_to_string(indices[0]);
	    boost::any valor;
            if(interpretaUno(bloque))
              valor= InterpreteRPN::Pila().Pop();
            else
	      std::cerr << msg_error << "; no se pudo evaluar la expresión: '"
                        << bloque << "'." << std::endl;
            mapa[s]= valor;
          }
        return true;
      }
    else if(cmd == "clear") //Borra todo.
      {
        status.GetString(); //Ignoramos entrada.
        mapa.clear();
        return true;
      }
    else if(cmd == "elem")
      {
        const CmdParser &parser= status.Parser();
        if(!parser.TieneIndices())
	  std::cerr << msg_error << "; uso: " << cmd << "[i]{comandos...}" << std::endl;
        else
          {
            const std::string bloque= status.GetBloque();
	    std::deque<boost::any> indices= crea_deque_boost_any(parser.GetIndices());
            const std::string s= boost_any_to_string(indices[0]);
            EntCmd *ptr= entcmd_cast((*this)[s]);
            if(ptr)
              ptr->EjecutaBloque(status,bloque,"mapa:elem");
            else
              {
	        std::clog << msg_error
                          << "; el objeto de tipo: " << boost_any_tipo_operando((*this)[s])
                          << ", no lee comandos, se ignora la entrada." << std::endl;
                status.GetBloque();
              }
          }
        return true;
      }
    else if(cmd == "for_each")
      {
        const std::string bloque= status.GetBloque();
	iterator i= begin();
	for(;i!= end();i++)
          {
            EntCmd *ptr= entcmd_cast((*i).second);
            if(ptr)
              ptr->EjecutaBloque(status,bloque,"mapa:for_each");
            else
              {
	        std::clog << msg_error 
                          << "; el objeto de tipo: " << boost_any_tipo_operando(*i)
                          << ", no lee comandos, se ignora la entrada." << std::endl;
                status.GetBloque();
              }
          }
        return true;
      }
    else
      return EntWOwner::procesa_comando(status);
  }

void Mapa::Print(std::ostream &os) const
  {
    if(mapa.empty()) return;
    const_iterator i= begin();
    boost_any_print(os,*i); i++;
    for(;i!=mapa.end();i++)
      {
        os << ',';
        boost_any_print(os,*i);
      }
  }

//! @brief Devuelve una propiedad de un elemento del mapa (si es posible);
any_const_ptr Mapa::get_prop_miembro(const std::string &nmb_miembro,const boost::any &elem_mapa) const
  {
    if(boost_any_is_mapa(elem_mapa))
      return boost_any_to_mapa(elem_mapa).GetProp(nmb_miembro);
    else
      {
	std::cerr << "Mapa::GetProp; No se pudo obtener la propiedad: '"
                  << nmb_miembro << "' porque ";
        boost_any_print(std::cerr,elem_mapa);
        std::cerr << " no es una mapa." << std::endl;
        return any_const_ptr();
      }
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr Mapa::GetProp(const std::string &cod) const 
  {
    if(verborrea>4)
      std::clog << "(Mapa::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod == "size")
      {
        tmp_gp_szt= mapa.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "get")
      {
        const std::string s= popString(cod);
        static boost::any retval;
        retval= operator[](s);
        return any_const_ptr(retval); 
      }
    else
      return EntWOwner::GetProp(cod);
  }

boost::any &Mapa::operator[](const std::string &s)
  {
    static boost::any retval;
    const_iterator i= mapa.find(s);
    if(i!=end())
      retval= (*i).second;
    else
      {
        const std::string posLectura= get_ptr_status()->getPosicionLecturaActual();
        std::cerr << "Mapa; no se encontró el elemento: '" << s << "'. "
                  << posLectura << std::endl;
      }
    return retval;
  }

const boost::any &Mapa::operator[](const std::string &s) const
  {
    static boost::any retval;
    const_iterator i= mapa.find(s);
    if(i!=end())
      retval= (*i).second;
    else
      {
        const std::string posLectura= get_ptr_status()->getPosicionLecturaActual();
        std::cerr << "Mapa; no se encontró el elemento: '" << s << "'. "
                  << posLectura << std::endl;
      }
    return retval;
  }


std::ostream &operator<<(std::ostream &os,const Mapa &l)
  {
    l.Print(os);
    return os;
  }
