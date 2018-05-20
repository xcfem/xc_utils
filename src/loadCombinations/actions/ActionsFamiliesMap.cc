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
//ActionsFamiliesMap.cc

#include "ActionsFamiliesMap.h"
#include "ActionsFamily.h"


#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"
#include "ActionsAndFactors.h"
#include "LeadingActionInfo.h"


//! @brief Return verdadero si la familia existe.
bool cmb_acc::ActionsFamiliesMap::exists(const std::string &actionsFamilyName) const
  { return (familias.find(actionsFamilyName)!=familias.end()); }

//! @brief Return un puntero a la familia cuyo nombre se pasa como parámetro.
cmb_acc::ActionsFamily *cmb_acc::ActionsFamiliesMap::getActionsFamily(const std::string &actionsFamilyName)
  {
    if(exists(actionsFamilyName))
      return familias[actionsFamilyName];
    else
      return nullptr;
  }

//! @brief Return un puntero a la familia cuyo nombre se pasa como parámetro.
const cmb_acc::ActionsFamily *cmb_acc::ActionsFamiliesMap::getActionsFamily(const std::string &actionsFamilyName) const
  {
    const_iterator i= familias.find(actionsFamilyName);
    if(i!= familias.end())
      return (*i).second;
    else
      return nullptr;
  }

//! @brief Insert the action in the family.
cmb_acc::ActionRValue &cmb_acc::ActionsFamiliesMap::insert(const std::string &familyName,const Action &acc,const std::string &combination_factors_name)
  {
    ActionsFamily *familia_ptr= getActionsFamily("default");
    if(!familyName.empty())
      familia_ptr= getActionsFamily(familyName);
    if(!familia_ptr)
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; family: '"
                  << familyName << "' not found.\n";
        const_iterator i= familias.begin();
        familia_ptr= (*i).second;
      }
    return familia_ptr->insert(acc,combination_factors_name);
  }

//! @brief Crea una nueva familia con el nombre que se le pasa como parámetro.
cmb_acc::ActionsFamily *cmb_acc::ActionsFamiliesMap::newActionsFamily(const std::string &actionsFamilyName,const PartialSafetyFactors &defaultGF)
  {
    ActionsFamily *tmp =nullptr;
    if(!exists(actionsFamilyName)) //new family.
      {
        tmp= new ActionsFamily(actionsFamilyName,defaultGF);//Default partial safety factors por defecto
	tmp->set_owner(this);
        familias[actionsFamilyName]= tmp;
      }
    else //la familia existe
      tmp= getActionsFamily(actionsFamilyName);
    return tmp;
  }

//! @brief Constructor por defecto.
cmb_acc::ActionsFamiliesMap::ActionsFamiliesMap(const std::string &name, const PartialSafetyFactors &defaultGF)
  : EntConNmb(name)
  {
    newActionsFamily("default");
  }

//! @brief Constructor de copia (NO COPIA LAS FAMILIAS).
cmb_acc::ActionsFamiliesMap::ActionsFamiliesMap(const ActionsFamiliesMap &otro)
  : EntConNmb(otro)
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; must not be called." << std::endl;
  }

//! @brief Operador asignación (NO COPIA LAS FAMILIAS).
cmb_acc::ActionsFamiliesMap &cmb_acc::ActionsFamiliesMap::operator=(const ActionsFamiliesMap &otro)
  {
    EntConNmb::operator=(otro);
    return *this;
  }

//! @brief Return un puntero a la tabla de coeficientes de simultaneidad.
const cmb_acc::CombinationFactorsMap *cmb_acc::ActionsFamiliesMap::getPtrCombinationFactors(void) const
  {
    const ActionsAndFactors *tmp= dynamic_cast<const ActionsAndFactors *>(Owner());
    if(tmp)
      return tmp->getFactors().getPtrCombinationFactors();
    else
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; owner not found." << std::endl;
        return nullptr;
      }
  }

//! @brief Borra todas las familias definidos.
void cmb_acc::ActionsFamiliesMap::clear(void)
  {
    for(iterator i= familias.begin();i!=familias.end();i++)
      {
        delete (*i).second;
        (*i).second= nullptr;
      }
    familias.clear();
  }

cmb_acc::ActionsFamiliesMap::~ActionsFamiliesMap(void)
  {
    familias.clear();
    clear();
  }

//! @brief Return the names of the action families.
boost::python::list cmb_acc::ActionsFamiliesMap::getKeys(void) const
  {
    boost::python::list retval;
    for(const_iterator i=this->begin();i!=this->end();i++)
      retval.append((*i).first);
    return retval;    
  }

//! @brief Return el número de acciones de todas las familias.
size_t cmb_acc::ActionsFamiliesMap::getNumActions(void) const
  { 
    size_t retval= 0;
    if(!familias.empty())
      for(const_iterator i= familias.begin();i!=familias.end();i++)
        {          
          ActionsFamily *familia= (*i).second;
          if(familia)
            retval+= familia->getNumActions();
	}
    return retval;
  }

//! brief Return verdadero si las familias estan vacías.
bool cmb_acc::ActionsFamiliesMap::empty(void) const
  {
    bool retval= true;
    if(!familias.empty())
      for(const_iterator i= familias.begin();i!=familias.end();i++)
        {
          ActionsFamily *familia= (*i).second;
          if(familia)
            {
              if(!familia->empty()) //La familia contiene acciones.
                {
                  retval= false;
                  break;
                }
            }
	}
    return retval;
  }


//! @brief Return the combinations for the non-constant permanent actions.
//! @param uls: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::LoadCombinationVector cmb_acc::ActionsFamiliesMap::getLoadCombinations(const bool &uls,const bool &sit_accidental) const
  {
    LoadCombinationVector retval;
    for(const_iterator i= familias.begin();i!=familias.end();i++)
      {
        ActionsFamily *familia= (*i).second;
        assert(familia);
        if(!familia->empty()) //La familia contiene acciones.
          {
            LoadCombinationVector SG_aster= familia->getLoadCombinations(uls,sit_accidental,-1);//Las permanentes siempre con characteristic value.
            retval= LoadCombinationVector::ProdCartesiano(retval,SG_aster,Action::zero);
          }
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles.
    return retval;
  }

//! @brief Return the combinations for the non permanent actions.
//! @param uls: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
//! @param leadingActionInfo: Information about the leading action.
cmb_acc::LoadCombinationVector cmb_acc::ActionsFamiliesMap::getLoadCombinations(const bool &uls,const bool &sit_accidental, const LeadingActionInfo &leadingActionInfo) const
  {
    LoadCombinationVector retval;
    for(const_iterator i= familias.begin();i!=familias.end();i++)
      {
        ActionsFamily *familia= (*i).second;
        assert(familia);
        if(!familia->empty()) //La familia contiene acciones.
          {
            LoadCombinationVector tmp= familia->getLoadCombinations(uls,sit_accidental,leadingActionInfo);
            retval= LoadCombinationVector::ProdCartesiano(retval,tmp,Action::zero);
          }
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles.
    return retval;
  }
