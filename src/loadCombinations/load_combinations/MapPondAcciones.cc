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
//MapPondAcciones.cc

#include "MapPondAcciones.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/loadCombinations/actions/AccionesClasificadas.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "LoadCombinations.h"



//! @brief Devuelve verdadero si la ponderacion existe.
bool cmb_acc::MapPondAcciones::existe(const std::string &nmb) const
  { return (ponderaciones.find(nmb)!=ponderaciones.end()); }

//! @brief Devuelve un puntero a la ponderacion cuyo nombre se pasa como parámetro.
cmb_acc::AccionesClasificadas *cmb_acc::MapPondAcciones::busca_ponderacion(const std::string &nmb)
  {
    if(existe(nmb))
      return ponderaciones[nmb];
    else
      return NULL;
  }

//! @brief Devuelve un puntero a la ponderacion cuyo nombre se pasa como parámetro.
const cmb_acc::AccionesClasificadas *cmb_acc::MapPondAcciones::busca_ponderacion(const std::string &nmb) const
  {
    const_iterator i= ponderaciones.find(nmb);
    if(i!= ponderaciones.end())
      return (*i).second;
    else
      return NULL;
  }

//! @brief Crea una nueva ponderacion con el nombre que se le pasa como parámetro.
cmb_acc::AccionesClasificadas *cmb_acc::MapPondAcciones::crea_ponderacion(const std::string &nmb,const MapCoefsPsi &coefs)
  {
    AccionesClasificadas *tmp =NULL;
    if(!existe(nmb)) //la ponderacion es nuevo.
      {
        tmp= new AccionesClasificadas(coefs);
        ponderaciones[nmb]= tmp;
      }
    else //la ponderacion existe
      tmp= busca_ponderacion(nmb);
    return tmp;
  }

//! @brief Constructor por defecto.
cmb_acc::MapPondAcciones::MapPondAcciones(void)
  : EntCmd() {}

//! @brief Constructor de copia (NO COPIA LAS PONDERACIONES).
cmb_acc::MapPondAcciones::MapPondAcciones(const MapPondAcciones &otro)
  : EntCmd(otro)
  {
    copia(otro.ponderaciones);
  }

//! @brief Operador asignación (NO COPIA LAS PONDERACIONES).
cmb_acc::MapPondAcciones &cmb_acc::MapPondAcciones::operator=(const MapPondAcciones &otro)
  {
    EntCmd::operator=(otro);
    copia(otro.ponderaciones);
    return *this;
  }

//! @brief Lanza la ejecución del bloque de código que se pasa
//! como parámetro para cada una de las ponderaciones del contenedor.
void cmb_acc::MapPondAcciones::for_each(CmdStatus &status,const std::string &bloque)
  {
    for(iterator i= ponderaciones.begin();i!=ponderaciones.end();i++)
      {
        (*i).second->set_owner(this);
        (*i).second->EjecutaBloque(status,bloque,"MapPondAcciones:for_each");
      }
  }

//! @brief Lanza la ejecución del bloque de código que se pasa
//! como parámetro para cada una de las acciones del contenedor.
void cmb_acc::MapPondAcciones::for_each_accion(CmdStatus &status,const std::string &bloque)
  {
    for(iterator i= ponderaciones.begin();i!=ponderaciones.end();i++)
      (*i).second->for_each_accion(status,bloque);
  }

//! @brief Define una poderación de acciones.
cmb_acc::AccionesClasificadas *cmb_acc::MapPondAcciones::defPonderacion(const std::string &nmb_ponderacion,const MapCoefsPsi &coefs)
  {
    AccionesClasificadas *retval= crea_ponderacion(nmb_ponderacion,coefs);
    if(retval) retval->set_owner(this);
    return retval;
  }

//! @brief Inserta la acción que se pasa como parámetro.
cmb_acc::VRAccion &cmb_acc::MapPondAcciones::inserta(const std::string &pond,const std::string &familia,const Accion &acc,const std::string &nmb_coefs_psi,const std::string &subfamilia)
  {
    AccionesClasificadas *ponderacion_ptr= busca_ponderacion(pond);
    if(!ponderacion_ptr)
      {
        std::cerr << "MapPondAcciones::inserta; no se encontró la ponderación: '"
                  << pond << "'\n";
      }
    return ponderacion_ptr->inserta(familia,acc,nmb_coefs_psi,subfamilia);
  }

//! @brief Lee un objeto MapPondAcciones desde archivo
bool cmb_acc::MapPondAcciones::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string msg_proc_cmd= "(MapPondAcciones) Procesando comando: " + cmd;
    if(verborrea>2)
      std::clog << msg_proc_cmd << std::endl;
    if(cmd == "defPonderacion") //Definición de una ponderacion.
      {
	std::string nmb_ponderacion= "";
        std::deque<boost::any> fnc_indices= status.Parser().SeparaIndices(this);
        if(fnc_indices.size()>0)
          nmb_ponderacion= convert_to_string(fnc_indices[0]); //Nombre del set.
        AccionesClasificadas *s= defPonderacion(nmb_ponderacion);
        if(s)
          s->LeeCmd(status);
        return true;
      }
    else if(cmd == "for_each")
      {
        const std::string bloque= status.GetBloque();
        for_each(status,bloque);
        return true;
      }
    else if(cmd == "for_each_accion")
      {
        const std::string bloque= status.GetBloque();
        for_each_accion(status,bloque);
        return true;
      }
    AccionesClasificadas *ponderacion_ptr= busca_ponderacion(cmd);
    if(ponderacion_ptr)
      {
        ponderacion_ptr->set_owner(this);
        ponderacion_ptr->LeeCmd(status);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Borra todas las ponderaciones definidos.
void cmb_acc::MapPondAcciones::clear(void)
  {
    for(iterator i= ponderaciones.begin();i!=ponderaciones.end();i++)
      {
        delete (*i).second;
        (*i).second= NULL;
      }
    ponderaciones.clear();
  }

//! @brief Copia las ponderaciones que se pasan comp parámetro.
void cmb_acc::MapPondAcciones::copia(const map_ponderaciones &pond)
  {
    clear();
    for(const_iterator i= pond.begin();i!=pond.end();i++)
      {
        const std::string nmb= (*i).first;
        const AccionesClasificadas *a= (*i).second;
        assert(a);
        ponderaciones[nmb]= new AccionesClasificadas(*a);
      }
  }

cmb_acc::MapPondAcciones::~MapPondAcciones(void)
  {
    //ponderaciones.clear();
    clear();
  }

//! @brief Devuelve el número de ponderaciones de todas las ponderaciones.
size_t cmb_acc::MapPondAcciones::size(void) const
  { return ponderaciones.size(); }

//! brief Devuelve verdadero si las ponderaciones estan vacías.
bool cmb_acc::MapPondAcciones::Vacia(void) const
  { return ponderaciones.empty(); }

cmb_acc::MapPondAcciones::iterator cmb_acc::MapPondAcciones::begin(void)
  { return ponderaciones.begin(); }
cmb_acc::MapPondAcciones::const_iterator cmb_acc::MapPondAcciones::begin(void) const
  { return ponderaciones.begin(); }
cmb_acc::MapPondAcciones::iterator cmb_acc::MapPondAcciones::end(void)
  { return ponderaciones.end(); }
cmb_acc::MapPondAcciones::const_iterator cmb_acc::MapPondAcciones::end(void) const
  { return ponderaciones.end(); }

//! @bried Devuelve las combinaciones correspondientes a todas las ponderaciones.
cmb_acc::LoadCombinations cmb_acc::MapPondAcciones::getLoadCombinations(void)
  {
    LoadCombinations retval;
    for(const_iterator i= ponderaciones.begin();i!=ponderaciones.end();i++)
      retval.Concat(LoadCombinations(*(*i).second));
    return retval;
  }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
any_const_ptr cmb_acc::MapPondAcciones::GetProp(const std::string &cod) const
  {
    const AccionesClasificadas *ponderacion_ptr= busca_ponderacion(cod);
    if(cod == "getSize")
      {
        tmp_gp_szt= ponderaciones.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(ponderacion_ptr)
      return any_const_ptr(ponderacion_ptr);
    else
      return EntCmd::GetProp(cod);
  }


