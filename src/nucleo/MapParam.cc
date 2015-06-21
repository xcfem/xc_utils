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
//MapParam.cc

#include "MapParam.h"
#include <boost/any.hpp>
#include "xc_utils/src/nucleo/aux_any.h"
#include "xc_utils/src/base/utils_any.h"
#include <iostream>

//! @brief Libera la memoria reservada
void MapParam::libera(void)
  {
    if(params) delete params;
    params= NULL;
  }

//! @brief Copia el mapa de parámetros 
void MapParam::alloc(const map_params *p)
  {
    libera();
    if(p)
      params= new map_params(*p);
    else
      params= new map_params();
  }

//! @brief Constructor por defecto.
MapParam::MapParam(void)
  : params(NULL) {}

//! @brief Constructor de copia.
MapParam::MapParam(const MapParam &otro)
  : params(NULL)
  { alloc(otro.params); }

//! @brief Operador asignación.
MapParam &MapParam::operator=(const MapParam &otro)
  {
    alloc(otro.params);
    return *this;
  }

//! @brief Asigna el propietario a las parámetros del objeto.
void MapParam::SetOwner(EntProp *owr)
  {
    if(params)
      {
        for(param_iterator i= params->begin();i!= params->end();i++)
          {
            boost::any *data= &((*i).second);
	    set_owner(data,owr);
          }
      }
  }

MapParam::param_iterator MapParam::begin(void)
  { return params->begin(); }
MapParam::param_iterator MapParam::end(void)
  { return params->end(); }
MapParam::param_const_iterator MapParam::begin(void) const
  { return params->begin(); }
MapParam::param_const_iterator MapParam::end(void) const
  { return params->end(); }


//! @brief Devuelve verdadero si existe una propiedad definida por
//! el usuario que tenga por nombre el que se pasa como parámetro.
bool MapParam::ExisteUserParam(const std::string &nmb_prop) const
  {
    bool retval= false;
    if(params) //Existe el contenedor.
      {
        map_params::const_iterator i= params->find(nmb_prop);
        if(i!= params->end())
          retval= true;
      }
    return retval;
  }

//! @brief Devuelve un iterador que apunta a la propiedad cuyo nombre se pasa como parámetro.
MapParam::param_iterator MapParam::BuscaUserParam(const std::string &nmb_prop) const
  {
    param_iterator retval;
    if(params) //Existe el contenedor.
      retval= params->find(nmb_prop);
    else
      std::cerr << "MapParam::BuscaUserParam ("
                << nmb_prop << "); ¡error!, el objeto no tiene parámetros." << std::endl;
    return retval;
  }

//! @brief Borra la propiedad cuyo nombre se pasa como parámetro.
size_t MapParam::BorraUserParam(const std::string &nmb_prop)
  {
    size_t retval= 0;
    if(params) //Existe el contenedor.
      retval= params->erase(nmb_prop);
    return retval;
  }

//! @brief Da de alta una propiedad definida por el usuario.
MapParam::param_iterator MapParam::CreaUserParam(const std::string &nombre,const boost::any &operand)
  {
    if(!params)
      alloc();
    (*params)[nombre]= operand;
    param_iterator retval= params->find(nombre);
    if(retval== params->end())
      std::cerr << "Error en MapParam::CreaUserParam." << std::endl;
    return retval;
  }

//! @brief Asigna un valor a una propiedad definida por el usuario.
MapParam::param_iterator MapParam::AsignaUserParam(const param_iterator &iterParamDes,const boost::any &valorAny)
  {
    const boost::any &objAny= (*iterParamDes).second;
    const std::string tipo= boost_any_tipo_operando(objAny);
    if(!boost_any_same_type(objAny,valorAny))
      (*iterParamDes).second= convert_to_type(tipo,valorAny);
    else
      (*iterParamDes).second= valorAny;
    return iterParamDes;
  }

//! @brief Devuelve una cadena de caracteres que contiene los nombres
//! de las parámetros separadas por comas.
std::string MapParam::SqlUserParamNames(void) const
  {
    std::string retval;
    if(params)
      {
        if(!params->empty())
          {
            param_const_iterator i=params->begin();
            retval= '\'' + i->first + '\''; i++;
            for(;i!=params->end();i++)
              { retval+= ",'" + i->first + '\''; }
          }
      }
    return retval;
  }

//! @brief Devuelve una cadena de caracteres que sirve para insertar los
//! valores de las variables en una tabla mediante SQL.
std::string MapParam::SqlUserParamValues(void) const
  {
    std::string retval;
    if(params)
      {
        if(!params->empty())
          {
            param_const_iterator i=params->begin();
            retval= boost_any_to_sql_value(i->second); i++;
            for(;i!=params->end();i++)
              { retval+= ','+ boost_any_to_sql_value(i->second); }
          }
      }
    return retval;
  }



//! @brief Destructor
MapParam::~MapParam(void)
  { libera(); }

//! @brief Devuelve el número de parámetros.
size_t MapParam::size(void) const
  {
    if(params)
      return params->size();
    else
      return 0;
  }

//! @brief Devuelve verdadero si el contenedor está vacío.
bool MapParam::empty(void) const
  {
    if(params)
      return params->empty();
    else
      return true;
  }


//! @brief Borra las parámetros de usuario del objeto.
void MapParam::clear(void)
  { if(params) params->clear(); }

//! @brief Devuelve los nombres de las parámetros separados por comas.
std::string MapParam::ListaNmbParams(void) const
  {
    std::string retval;
    if(params)
      {
        if(!params->empty())
          {
            param_iterator i= params->begin();
            if(i!= params->end())
              retval+= (*i).first;
            i++;
            for(;i!= params->end();i++)
              retval+= "," + (*i).first;
          }
      }
    return retval;
  }

//! @brief Devuelve el conjunto de nombres de las parámetros.
std::set<std::string> MapParam::SetNombresParams(void) const
  {
    std::set<std::string> retval;
    if(params)
      {
        for(param_iterator i= params->begin();i!= params->end();i++)
          retval.insert((*i).first);
      }
    return retval;
  }

//! @brief Imprime la cadena que se pasa como parámetro.
void MapParam::Print(std::ostream &os) const
  {
    if(params)
      for(param_const_iterator i= params->begin();i!=params->end();i++)
        {
          os << (*i).first << "= ";
          boost_any_print(os,(*i).second);
          os << std::endl;
        }
  }

//! @brief Devuelve un puntero a una propiedad definida por el
//! usuario.
boost::any *MapParam::GetUserParamPtr(const std::string &cod) const
  {
    boost::any *retval= NULL;
    if(params)
      {
        const map_params::iterator i= params->find(cod);
        if(i!= params->end()) //La propiedad es de este objeto.
          retval= &((*i).second);
      }
    return retval;
  }
