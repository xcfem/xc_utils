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
#include "xc_utils/src/loadCombinations/actions/ActionsAndFactors.h"


#include "LoadCombinations.h"



//! @brief Return true if the object is found.
bool cmb_acc::ActionWeightingMap::exists(const std::string &nmb) const
  { return (actions_and_factors.find(nmb)!=actions_and_factors.end()); }

//! @brief Return a pointer to the object with argument name.
cmb_acc::ActionsAndFactors *cmb_acc::ActionWeightingMap::findByName(const std::string &name)
  {
    if(exists(name))
      return actions_and_factors[name];
    else
      return nullptr;
  }

//! @brief Return a pointer to the object with that name.
const cmb_acc::ActionsAndFactors *cmb_acc::ActionWeightingMap::findByName(const std::string &name) const
  {
    const_iterator i= actions_and_factors.find(name);
    if(i!= actions_and_factors.end())
      return (*i).second;
    else
      return nullptr;
  }

//! @brief Creates a new object with the argument name.
cmb_acc::ActionsAndFactors *cmb_acc::ActionWeightingMap::findOrCreate(const std::string &name,const Factors &factors)
  {
    ActionsAndFactors *tmp =nullptr;
    if(!exists(name)) //new object.
      {
        tmp= new ActionsAndFactors(factors);
        actions_and_factors[name]= tmp;
      }
    else //already exists
      tmp= findByName(name);
    return tmp;
  }

//! @brief Default constructor.
cmb_acc::ActionWeightingMap::ActionWeightingMap(void)
  : CommandEntity() {}

//! @brief Copy constructor(NO COPIA LAS ACTIONS_AND_FACTORS).
cmb_acc::ActionWeightingMap::ActionWeightingMap(const ActionWeightingMap &other)
  : CommandEntity(other)
  {
    copy(other.actions_and_factors);
  }

//! @brief Assignment operator (NO COPIA LAS ACTIONS_AND_FACTORS).
cmb_acc::ActionWeightingMap &cmb_acc::ActionWeightingMap::operator=(const ActionWeightingMap &other)
  {
    CommandEntity::operator=(other);
    copy(other.actions_and_factors);
    return *this;
  }

//! @brief Define una ponderación de acciones.
cmb_acc::ActionsAndFactors *cmb_acc::ActionWeightingMap::create(const std::string &nmb_ponderacion,const Factors &factors)
  {
    ActionsAndFactors *retval= findOrCreate(nmb_ponderacion,factors);
    if(retval) retval->set_owner(this);
    return retval;
  }

//! @brief Insert the action being passed as parameter.
cmb_acc::ActionRValue &cmb_acc::ActionWeightingMap::insert(const std::string &pond,const std::string &familia,const Action &acc,const std::string &combination_factors_name,const std::string &partial_safety_factors_name)
  {
    ActionsAndFactors *ponderacion_ptr= findByName(pond);
    if(!ponderacion_ptr)
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
	          << "; weighting: '"
                  << pond << "' not found.\n";
      }
    return ponderacion_ptr->insert(familia,acc,combination_factors_name,partial_safety_factors_name);
  }

//! @brief Borra todas las actions_and_factors definidos.
void cmb_acc::ActionWeightingMap::clear(void)
  {
    for(iterator i= actions_and_factors.begin();i!=actions_and_factors.end();i++)
      {
        delete (*i).second;
        (*i).second= nullptr;
      }
    actions_and_factors.clear();
  }

//! @brief Copy the objects from the argument.
void cmb_acc::ActionWeightingMap::copy(const map_actions_and_factors &a_and_f)
  {
    clear();
    for(const_iterator i= a_and_f.begin();i!=a_and_f.end();i++)
      {
        const std::string name= (*i).first;
        const ActionsAndFactors *a= (*i).second;
        assert(a);
        actions_and_factors[name]= new ActionsAndFactors(*a);
      }
  }

cmb_acc::ActionWeightingMap::~ActionWeightingMap(void)
  {
    //actions_and_factors.clear();
    clear();
  }

//! @brief Return el número de actions_and_factors de todas las actions_and_factors.
size_t cmb_acc::ActionWeightingMap::size(void) const
  { return actions_and_factors.size(); }

//! brief Return verdadero si las actions_and_factors estan vacías.
bool cmb_acc::ActionWeightingMap::empty(void) const
  { return actions_and_factors.empty(); }

cmb_acc::ActionWeightingMap::iterator cmb_acc::ActionWeightingMap::begin(void)
  { return actions_and_factors.begin(); }
cmb_acc::ActionWeightingMap::const_iterator cmb_acc::ActionWeightingMap::begin(void) const
  { return actions_and_factors.begin(); }
cmb_acc::ActionWeightingMap::iterator cmb_acc::ActionWeightingMap::end(void)
  { return actions_and_factors.end(); }
cmb_acc::ActionWeightingMap::const_iterator cmb_acc::ActionWeightingMap::end(void) const
  { return actions_and_factors.end(); }

//! @brief Return the names of the action weightings.
boost::python::list cmb_acc::ActionWeightingMap::getKeys(void) const
  {
    boost::python::list retval;
    for(const_iterator i=this->begin();i!=this->end();i++)
      retval.append((*i).first);
    return retval;    
  }
//! @bried Return the combinations that correspond to all actions_and_factors.
cmb_acc::LoadCombinations cmb_acc::ActionWeightingMap::getLoadCombinations(void)
  {
    LoadCombinations retval;
    for(const_iterator i= actions_and_factors.begin();i!=actions_and_factors.end();i++)
      retval.Concat(LoadCombinations(*(*i).second));
    return retval;
  }

