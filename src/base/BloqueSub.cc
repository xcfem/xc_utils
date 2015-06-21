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
//BloqueSub.cc

#include "BloqueSub.h"
#include "Lista.h"
#include "Record.h"
#include "utils_any.h"
#include "any_const_ptr.h"
#include "../nucleo/aux_any.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/PilaLlamadas.h"
#include "boost/lexical_cast.hpp"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

//! @brief Constructor.
BloqueSub::BloqueSub(EntCmd *owner, const std::string &nmb)
  : BloqueBase(owner,nmb) {}

//! @brief Constructor.
BloqueSub::BloqueSub(EntCmd *owner, const std::string &nmb,const std::string &b,const std::string &def_args)
  : BloqueBase(owner,nmb,b)
  {
    procesa_def_parametros(def_args);
  }
//! @brief Constructor de copia.
BloqueSub::BloqueSub(const BloqueSub &otro)
  : BloqueBase(otro)
  { copia_orden_argumentos(otro.orden_argumentos); }

//! @brief Operador asignación.
BloqueSub &BloqueSub::operator=(const BloqueSub &otro)
  {
    BloqueBase::operator=(otro);
    copia_orden_argumentos(otro.orden_argumentos);
    return *this;
  }

//! @brief Copia el vector de orden de argumentos de otro BloqueSub en éste.
void BloqueSub::copia_orden_argumentos(const vector_orden_argumentos &otro)
  {
    const MapPropVar &params_este= params; //Parámetros de éste BloqueSub.
    if(params_este.empty()) return;
    const size_t num_param= otro.size();
    orden_argumentos= vector_orden_argumentos(num_param); //Inicializamos vector orden.
    size_t conta= 0; //Contador.
    for(vector_orden_argumentos::const_iterator i= otro.begin();i!=otro.end();i++,conta++)
      {
        const MapParam::param_iterator otro_param_iter= *i;
        const std::string &nmb_param= (*otro_param_iter).first;
        MapParam::param_iterator param_iter= params_este.BuscaUserParam(nmb_param);
        orden_argumentos[conta]= param_iter;
      }

  }

//! @brief Recibe una cadena de caracteres de la forma:
//! "string a, bloque b,string c" que define el número,
//! tipo y orden de los parámetros que recibe la función
//! y con esta definición crea las propiedades correspondientes
//! e inicializa el vector de orden.
void BloqueSub::procesa_def_parametros(const std::string &str)
  {
    if(str.empty()) return;
    const std::deque<std::string> tmp= separa_csv(str); //Separamos argumentos.
    const size_t num_param= tmp.size();
    if(num_param < 1) return;
    orden_argumentos= vector_orden_argumentos(num_param); //Inicializamos vector orden.
    size_t conta= 0;
    for(std::deque<std::string>::const_iterator i= tmp.begin();i!=tmp.end();i++, conta++)
      {
        const std::deque<std::string> tmp2= separa_cadena(*i," ");
        if(tmp2.size()!= 2)
	  std::cerr << "BloqueSub::procesa_parametros; error en la definición "
                    << "del parámetro: '" << *i << "'.\n" << std::endl;
        else
          {
            const std::string &nombre= tmp2[1];
            const std::string &tipo= tmp2[0];
            orden_argumentos[conta]= params.Props().CreaUserParam(nombre,string_to_boost_any(tipo,"",""));
          }
      }
  }

//! @brief Devuelve el número de argumentos que se le pasan a la subrutina.
size_t BloqueSub::NumParametros(void) const
  { return orden_argumentos.size(); }

//! @brief Actualiza los valores de las propiedades según
//! los valores de la cadena de caracteres que se pasa como parámetro:
//! "paramA,paramB,paramC,..."
void BloqueSub::valores_parametros(const size_t &argc) const
  {
    const std::string &nmb_subrutina= pila_nombres_cmd_usuario.top();
    const std::string &msg_subrutina= "subrutina: '" + nmb_subrutina + "'";
    if(argc != NumParametros())
      err_num_argumentos(std::cerr,NumParametros(),"valores_parametros",msg_subrutina);
    else
      for(orden_argumentos_const_reverse_iterator i= orden_argumentos.rbegin();i!= orden_argumentos.rend();i++)
        {
          const MapParam::param_iterator param_iter= *i;
          if(verborrea>4)
	    std::clog << "asignando parámetro: " << (*param_iter).first << std::endl;
	  boost::any &prp= (*param_iter).second;
          const boost::any &arg= InterpreteRPN::Pila().Pop();
          if(boost_any_is_empty(arg))
            {
              const std::string posLectura= ptr_status->getPosicionLecturaActual();
	      std::cerr << "BloqueSub::valores_parametros; el argumento para: '"
                        << (*param_iter).first << "' de la subrutina: '"
                        << nmb_subrutina << "' tiene valor nulo." 
                        << posLectura << std::endl;
            }
          else
            {
              if(verborrea>4)
	        std::clog << "valor: " << arg << std::endl;
              EntCmd *this_no_const= const_cast<BloqueSub *>(this);
              if(!convert_arg(prp,arg,this_no_const))
	        std::cerr << "BloqueSub::valores_parametros; error en "
			  << msg_subrutina << ", la conversión para el tipo: '"
                          << boost_any_tipo_operando(prp) << "', no está implementada." << std::endl;
            }
        }
  }

//! Lee un objeto BloqueSub desde archivo
//! Soporta los comandos:
bool BloqueSub::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueSub; procesando comando: " << cmd << std::endl;
    if(cmd == "rutina")
      {
        bloque= status.GetBloque();
        return true;
      }
    else
      return BloqueBase::procesa_comando(status);
  }

//! @brief Ejecuta la subrutina.
void BloqueSub::Run(const EntCmd *cllr) const
  {
    assert(get_ptr_status());
    const size_t szPilaAntes= ptr_status->GetPilaLlamadas().size();
    assert(cllr);
    if(cllr == this)
      std::cerr << "!Ojo! la rutina se llama a sí misma." << std::endl;
    cllr->set_sub(this);
    BloqueSub *this_no_const= const_cast<BloqueSub *>(this);
    get_ptr_status()->GetPilaLlamadas().SetObjetoActual(this_no_const); //Colocamos el objeto BloqueSub en la pila de llamadas.
    EntCmd *caller_no_const= const_cast<EntCmd *>(cllr);
    typedef std::set<std::string> str_set;
    str_set vars_antes= cllr->params.Vars().SetNombresParams();
    caller_no_const->EjecutaBloque(Bloque(),getNombre());
    str_set nuevas= cllr->params.Vars().SetNombresParams();
    if(!vars_antes.empty())
      {
        for(str_set::const_iterator i= vars_antes.begin();i!=vars_antes.end();i++)
	  nuevas.erase(*i);
      }
    caller_no_const->params.Vars().BorraUserParams(nuevas.begin(),nuevas.end());
    get_ptr_status()->GetPilaLlamadas().PopObjetoActual(); //Devolvemos la pila al estado anterior.
    cllr->set_sub(NULL);
    const size_t szPilaDespues= ptr_status->GetPilaLlamadas().size();
    if(szPilaDespues!=szPilaAntes)
      {
        const std::string posLectura= get_ptr_status()->getPosicionLecturaActual();
        std::cerr << "ERROR en BloqueSub::Run; " << nombre_clase() << " llamado desde: " << cllr->nombre_clase()
                  << " la pila varía de tamaño (antes: " << szPilaAntes 
                 << " después: " << szPilaDespues << ")." << posLectura << std::endl;
      }
  }

//! @brief Devuelve verdadero si existe el argumento cuyo nombre se pasa como parámetro.
bool BloqueSub::ExisteNombreArgumento(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "BloqueSub::ExisteNombreArgumento, buscando parámetro: " << cod << std::endl;
    bool retval= false;
    for(vector_orden_argumentos::const_iterator i= orden_argumentos.begin();i!=orden_argumentos.end();i++)
      {
        const MapParam::param_iterator orden_argumentos_param_iter= *i;
        const std::string &nmb_param= (*orden_argumentos_param_iter).first;
        if(nmb_param==cod)
          {
            retval= true;
            break;
          }
      }
    return retval;
  }

//! @brief Devuelve un iterador que apunta al parámetro definido por el usuario cuyo nombre se pasa como parametro.
BloqueSub::orden_argumentos_const_iterator BloqueSub::get_iterator(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "BloqueSub::get_iterator, buscando parámetro: " << cod << std::endl;
    for(vector_orden_argumentos::const_iterator i= orden_argumentos.begin();i!=orden_argumentos.end();i++)
      {
        MapParam::param_iterator orden_argumentos_param_iter= *i;
        const std::string &nmb_param= (*orden_argumentos_param_iter).first;
        if(nmb_param==cod)
          return i;
      }
    return orden_argumentos.end();
  }

//! @brief Devuelve un iterador que apunta al parámetro definido por el usuario cuyo nombre se pasa como parametro.
MapParam::param_iterator BloqueSub::get_arg_iterator(const std::string &cod) const
  { return *get_iterator(cod); }

//! @brief Devuelve el valor del argumento cuyo nombre se pasa como parámetro.
any_const_ptr BloqueSub::GetValorArg(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "BloqueSub::GetValorArg, buscando parámetro: " << cod << std::endl;
    any_const_ptr retval;
    orden_argumentos_const_iterator i= get_iterator(cod);
    if(i!=orden_argumentos.end())
      {
        const MapParam::param_iterator orden_argumentos_param_iter= *i;
        retval= any_const_ptr(orden_argumentos_param_iter->second);
      }
    return retval;
  }


//! \brief Devuelve la propiedad LOCAL del objeto cuyo código (de la propiedad) se pasa
//! como parámetro. Se entiende por propiedad LOCAL la que está definida en el propio objeto
//! y, por tanto, no requiere consultar a ningún otro (su propietario,pila de llamadas,...).
any_const_ptr BloqueSub::GetPropLocal(const std::string &cod) const
  {
    if(params.ExisteUserParam(cod))
      {
        return get_user_param(cod);
      }
    else if(cod=="num_parametros")
      {
        tmp_gp_szt= NumParametros();
        return any_const_ptr(tmp_gp_szt);
      }
    else
      return BloqueBase::GetPropLocal(cod);
  }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
any_const_ptr BloqueSub::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "BloqueSub::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    any_const_ptr tmp= GetPropLocal(cod);
    if(!tmp.empty())
      retval= tmp;
    else
      retval= BloqueBase::GetProp(cod);
    return retval;
  }
