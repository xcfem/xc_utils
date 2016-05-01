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
//ActionWeightingMap.cc

#include "ActionWeightingMap.h"
#include "xc_utils/src/loadCombinations/actions/ActionContainer.h"


#include "LoadCombinations.h"



//! @brief Devuelve verdadero si la ponderacion existe.
bool cmb_acc::ActionWeightingMap::existe(const std::string &nmb) const
  { return (ponderaciones.find(nmb)!=ponderaciones.end()); }

//! @brief Devuelve un puntero a la ponderacion cuyo nombre se pasa como parámetro.
cmb_acc::ActionContainer *cmb_acc::ActionWeightingMap::busca_ponderacion(const std::string &nmb)
  {
    if(existe(nmb))
      return ponderaciones[nmb];
    else
      return nullptr;
  }

//! @brief Devuelve un puntero a la ponderacion cuyo nombre se pasa como parámetro.
const cmb_acc::ActionContainer *cmb_acc::ActionWeightingMap::busca_ponderacion(const std::string &nmb) const
  {
    const_iterator i= ponderaciones.find(nmb);
    if(i!= ponderaciones.end())
      return (*i).second;
    else
      return nullptr;
  }

//! @brief Crea una nueva ponderacion con el nombre que se le pasa como parámetro.
cmb_acc::ActionContainer *cmb_acc::ActionWeightingMap::crea_ponderacion(const std::string &nmb,const PsiCoeffsMap &coefs)
  {
    ActionContainer *tmp =nullptr;
    if(!existe(nmb)) //la ponderacion es nuevo.
      {
        tmp= new ActionContainer(coefs);
        ponderaciones[nmb]= tmp;
      }
    else //la ponderacion existe
      tmp= busca_ponderacion(nmb);
    return tmp;
  }

//! @brief Constructor por defecto.
cmb_acc::ActionWeightingMap::ActionWeightingMap(void)
  : EntCmd() {}

//! @brief Constructor de copia (NO COPIA LAS PONDERACIONES).
cmb_acc::ActionWeightingMap::ActionWeightingMap(const ActionWeightingMap &otro)
  : EntCmd(otro)
  {
    copia(otro.ponderaciones);
  }

//! @brief Operador asignación (NO COPIA LAS PONDERACIONES).
cmb_acc::ActionWeightingMap &cmb_acc::ActionWeightingMap::operator=(const ActionWeightingMap &otro)
  {
    EntCmd::operator=(otro);
    copia(otro.ponderaciones);
    return *this;
  }

//! @brief Define una poderación de acciones.
cmb_acc::ActionContainer *cmb_acc::ActionWeightingMap::defPonderacion(const std::string &nmb_ponderacion,const PsiCoeffsMap &coefs)
  {
    ActionContainer *retval= crea_ponderacion(nmb_ponderacion,coefs);
    if(retval) retval->set_owner(this);
    return retval;
  }

//! @brief Inserta la acción que se pasa como parámetro.
cmb_acc::ActionRValue &cmb_acc::ActionWeightingMap::inserta(const std::string &pond,const std::string &familia,const Action &acc,const std::string &nmb_coefs_psi,const std::string &subfamilia)
  {
    ActionContainer *ponderacion_ptr= busca_ponderacion(pond);
    if(!ponderacion_ptr)
      {
        std::cerr << "ActionWeightingMap::inserta; no se encontró la ponderación: '"
                  << pond << "'\n";
      }
    return ponderacion_ptr->inserta(familia,acc,nmb_coefs_psi,subfamilia);
  }

//! @brief Borra todas las ponderaciones definidos.
void cmb_acc::ActionWeightingMap::clear(void)
  {
    for(iterator i= ponderaciones.begin();i!=ponderaciones.end();i++)
      {
        delete (*i).second;
        (*i).second= nullptr;
      }
    ponderaciones.clear();
  }

//! @brief Copia las ponderaciones que se pasan comp parámetro.
void cmb_acc::ActionWeightingMap::copia(const map_ponderaciones &pond)
  {
    clear();
    for(const_iterator i= pond.begin();i!=pond.end();i++)
      {
        const std::string nmb= (*i).first;
        const ActionContainer *a= (*i).second;
        assert(a);
        ponderaciones[nmb]= new ActionContainer(*a);
      }
  }

cmb_acc::ActionWeightingMap::~ActionWeightingMap(void)
  {
    //ponderaciones.clear();
    clear();
  }

//! @brief Devuelve el número de ponderaciones de todas las ponderaciones.
size_t cmb_acc::ActionWeightingMap::size(void) const
  { return ponderaciones.size(); }

//! brief Devuelve verdadero si las ponderaciones estan vacías.
bool cmb_acc::ActionWeightingMap::Vacia(void) const
  { return ponderaciones.empty(); }

cmb_acc::ActionWeightingMap::iterator cmb_acc::ActionWeightingMap::begin(void)
  { return ponderaciones.begin(); }
cmb_acc::ActionWeightingMap::const_iterator cmb_acc::ActionWeightingMap::begin(void) const
  { return ponderaciones.begin(); }
cmb_acc::ActionWeightingMap::iterator cmb_acc::ActionWeightingMap::end(void)
  { return ponderaciones.end(); }
cmb_acc::ActionWeightingMap::const_iterator cmb_acc::ActionWeightingMap::end(void) const
  { return ponderaciones.end(); }

//! @bried Devuelve las combinaciones correspondientes a todas las ponderaciones.
cmb_acc::LoadCombinations cmb_acc::ActionWeightingMap::getLoadCombinations(void)
  {
    LoadCombinations retval;
    for(const_iterator i= ponderaciones.begin();i!=ponderaciones.end();i++)
      retval.Concat(LoadCombinations(*(*i).second));
    return retval;
  }

