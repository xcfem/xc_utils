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
//MapPropVar.cc

#include "MapPropVar.h"
#include <boost/any.hpp>
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/Lista.h"
#include "xc_utils/src/nucleo/aux_any.h"

//! @brief Constructor por defecto.
MapPropVar::MapPropVar(void)
  : props(), vars() {}

//! @brief Asigna el propietario a las propiedades del objeto.
void MapPropVar::SetOwner(EntProp *owr)
  {
    props.SetOwner(owr);
    vars.SetOwner(owr);
  }

const MapParam &MapPropVar::Vars(void) const
  { return vars; }
MapParam &MapPropVar::Vars(void)
  { return vars; }
const MapParam &MapPropVar::Props(void) const
  { return props; }
MapParam &MapPropVar::Props(void)
  { return props; }

//! @brief Devuelve verdadero si existe una propiedad o variable definida por
//! el usuario que tenga por nombre el que se pasa como parámetro.
bool MapPropVar::ExisteUserParam(const std::string &nmb_prop) const
  {
    bool retval= vars.ExisteUserParam(nmb_prop);
    if(!retval)
      retval= props.ExisteUserParam(nmb_prop);
    return retval;
  }

//! @brief Devuelve un iterador que apunta a la propiedad o variable cuyo nombre se pasa como parámetro.
MapParam::param_iterator MapPropVar::BuscaUserParam(const std::string &nmb_prop) const
  {
    MapParam::param_iterator retval;
    if(!vars.empty())
      {
        retval= vars.BuscaUserParam(nmb_prop);
        if(retval == vars.end())
          retval= props.BuscaUserParam(nmb_prop);
      }
    else
      retval= props.BuscaUserParam(nmb_prop);
    return retval;
  }

//! @brief Borra la propiedad cuyo nombre se pasa como parámetro.
size_t MapPropVar::BorraUserParam(const std::string &nmb_prop)
  {
    if(vars.ExisteUserParam(nmb_prop))
      return vars.BorraUserParam(nmb_prop);
    else
      return props.BorraUserParam(nmb_prop);
  }

//! @brief Asigna un valor a una propiedad definida por el usuario.
MapParam::param_iterator MapPropVar::AsignaUserParam(const MapParam::param_iterator &iterParamDes,const boost::any &valorAny)
  {
    const boost::any &objAny= (*iterParamDes).second;
    const std::string tipo= boost_any_tipo_operando(objAny);
    if(!boost_any_same_type(objAny,valorAny))
      (*iterParamDes).second= convert_to_type(tipo,valorAny);
    else
      (*iterParamDes).second= valorAny;
    return iterParamDes;
  }

//! @brief Asigna un valor a un elemento de una propiedad definida por el usuario.
void MapPropVar::AsignaElemUserParam(const MapParam::param_iterator &iterParamDes,const boost::any &indicesAny,const boost::any &valorAny)
  {
    boost::any &objAny= (*iterParamDes).second;
    if(boost_any_is_string(objAny))
      {
	std::string &str= *boost::any_cast<std::string>(&objAny);
        const size_t sz= convert_to_size_t(indicesAny);
        str[sz]= convert_to_char(valorAny);
      }
    else if(boost_any_is_vector_any(objAny))
      {
	std::vector<boost::any> &v= *boost::any_cast<std::vector<boost::any> >(&objAny);
        const size_t sz= convert_to_size_t(indicesAny);
        v[sz]= valorAny;
      }
//     else if(boost_any_is_lista(objAny))
//       {
// 	Lista &l= *boost::any_cast<Lista>(&objAny);
//         const size_t sz= convert_to_size_t(indicesAny);
//         l[sz]= valorAny;
//       }
//     else if(boost_any_is_m_double(a) && boost_any_is_vector_any(b))  //M_DOUBLE[INT]
//       retval= boost::any(boost_any_to_m_double(a)[convert_to_size_t(boost_any_to_vector_any(b)[0])]);
    else if(boost_any_is_m_double(objAny))
      {
	m_double &m= *boost::any_cast<m_double>(&objAny);
        const std::vector<size_t> idx= convert_to_vector_size_t(indicesAny);
        if(idx.size()>1)
          m(idx[0],idx[1])= convert_to_double(valorAny);
      }
    else
      {
        std::cerr << "No se pudo aplicar el operador [] al objeto de tipo: "
                  << boost_any_tipo_operando(objAny) << " para los índices de tipo "
                  << boost_any_tipo_operando(indicesAny) << std::endl;
      }
  }

//! @brief Devuelve el número de propiedades.
size_t MapPropVar::size(void) const
  { return vars.size()+props.size(); }

//! @brief Devuelve verdadero si el contenedor está vacío.
bool MapPropVar::empty(void) const
  { return (props.empty() && vars.empty()); }

//! @brief Borra las propiedades de usuario del objeto.
void MapPropVar::clearProps(void)
  {
    props.clear();
    vars.clear();
  }

void MapPropVar::clearVars(void)
  { vars.clear(); }

//! @brief Imprime la cadena que se pasa como parámetro.
void MapPropVar::Print(std::ostream &os) const
  {
    vars.Print(os);
    props.Print(os);
  }

//! @brief Devuelve un puntero a una propiedad definida por el
//! usuario.
boost::any *MapPropVar::GetUserParamPtr(const std::string &cod) const
  {
    boost::any *retval= vars.GetUserParamPtr(cod);
    if(!retval)
      retval= props.GetUserParamPtr(cod);
    return retval;
  }
