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
//PilaLlamadas.cc

#include "PilaLlamadas.h"
#include "../nucleo/EntCmd.h"
#include "BloqueSub.h"
#include "Record.h"
#include "any_const_ptr.h"
#include "../nucleo/aux_any.h"
#include <iostream>
#include "CmdStatus.h"

std::string PilaLlamadas::last_cod= "";

PilaLlamadas::PilaLlamadas(void)
  : stk_llamadas() {}


void PilaLlamadas::imprime_ruta(std::ostream &os) const
  {
    os << "ruta: ";
    const EntCmd *ptr= GetObjetoActual();
    os << "(PilaLlamadas) Llamado desde: ";
    const_ptr_print(os,ptr->GetProp("tipo"));
    os << " (" << ptr << ")" << std::endl;
  }

//! @brief Devuelve una cadena de caracteres con los objetos
//! de la pila.
std::string PilaLlamadas::getRuta(void) const
  {
    std::string retval("");
    if(!empty())
      {
        const_iterator i= begin();
        retval= (*i)->nombre_clase();
        i++; //Elemento anterior al que llama.
        for(;i!=end();i++)
          retval+= "," + (*i)->nombre_clase();
      }
    return retval;
  }

//! @brief Coloca el objeto en lo alto de la pila, si es distinto al anterior y no nulo.
bool PilaLlamadas::SetObjetoActual(EntCmd *ptr)
  {
    bool retval= false;
    if(ptr)
      {
        if(ptr!=GetObjetoActual())
          { 
            push_front(ptr);
            last_cod= ""; //Inicializa last_cod.
            retval= true;
          }
      }
    else
      std::cerr << "Se intentó insertar un puntero nulo en la pila de llamadas." << std::endl;
    return retval;
  }

//! @brief Devuelve el objeto de lo alto de la pila.
bool PilaLlamadas::PopObjetoActual(void)
  {
    bool retval= false;
    if(!empty())
      {
        stk_llamadas::pop_front();
        last_cod= ""; //Inicializa last_cod.
        retval= true;
      }
    else
      std::cerr << "PilaLlamadas::PopObjetoActual; se intentó retirar un objeto de la pila vacía." << std::endl;
    return retval;
  }


//! @brief Procesa un comando del elemento que está
//! en cabeza de la pila y, si no la encuentra, se la pide
//! al anterior...
bool PilaLlamadas::procesa_comando(CmdStatus &status,EntCmd *caller)
  {
    const std::string cmd= status.Cmd(); //Desreferencia comando.
    if(EntProp::GetNivelVerborrea()>2)
      std::clog << "(PilaLlamadas) Procesando comando: " << cmd << std::endl;
    iterator i= begin();
    i++; //Elemento anterior al que llama.
    bool retval= false;
    for(;i!=end();i++)
      {
        retval= (*i)->procesa_comando(status);
        if(retval) break; //Encontró el comando, hemos terminado.
      }
    return retval;
  }

//! @brief Devuelve un iterador apuntando al primer objeto que 
//! posee el parámetro definido por el usuario, cuyo nombre (del parámetro)se
//! pasa como parámetro.
PilaLlamadas::const_iterator PilaLlamadas::has_user_param(const std::string &cod) const
  {
    const_iterator i= begin();
    i++; //Elemento anterior al que llama.
    for(;i!=end();i++)
      if((*i)->params.ExisteUserParam(cod)) break; //Encontró el parámetro, hemos terminado.
    return i;
  }

//! @brief Devuelve verdadero si encuentra en la pila un parámetro definido por el usuario.
bool PilaLlamadas::existe_user_param(const std::string &cod) const
  { return (has_user_param(cod)!=end()); }

//! @brief Busca la propiedad o variable cuyo código se pasa como parámetro
//! entre los objetos de que se están ejecutando actualmente
any_const_ptr PilaLlamadas::GetProp(const std::string &cod) const
  {
    any_const_ptr retval;
    if(cod != last_cod) //Se busca una propiedad nueva (o vieja con éxito).
      {
        last_cod= cod;
        if(EntProp::GetNivelVerborrea()>4)
          std::clog << "(PilaLlamadas) Buscando propiedad: " << cod << std::endl;
        for(const_iterator i= begin();i!=end();i++)
          {
            const EntProp *ptr_record= (*i);
            if(ptr_record)
              {
                const BloqueSub *ptr_sub= dynamic_cast<const BloqueSub *>(ptr_record);
                if(ptr_sub)
                  retval= ptr_sub->GetValorArg(cod);
                if(!retval.empty()) //Encontró la propiedad, hemos terminado.
                  {
                    last_cod= ""; //En caso de éxito, no interesa que conserve el último código.
                    break;
                  }
                if(!EntProp::visitado(ptr_record))
                  {
                    retval= ptr_record->GetProp(cod);
                    if(retval.empty())
                      EntProp::visita(ptr_record); //Si devuelve nada, no le volvemos a preguntar.
                  }
                if(!retval.empty()) //Encontró la propiedad, hemos terminado.
                  {
                    last_cod= ""; //En caso de éxito, no interesa que conserve el último código.
                    break;
                  }
              }
            else
	      std::cerr << "Se encontró un puntero nulo en la pila de llamadas"
                        << ", cuando se estaba buscando la propiedad: '" << cod << "'\n";
          }
      }
    return retval;
  }
