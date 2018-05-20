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
//ActionsFamiliesMap.h
//Contenedor de familias de acciones.

#ifndef MAPFAMILIASACC_H
#define MAPFAMILIASACC_H

#include "xc_utils/src/nucleo/EntConNmb.h"
#include <map>
#include "xc_utils/src/loadCombinations/factors/PartialSafetyFactors.h"


namespace cmb_acc {

class ActionsFamily;
class LoadCombinationVector;
class CombinationFactorsMap;
class Action;
class ActionRValue;
class ActionsAndFactors;
class LeadingActionInfo;

//! @ingroup CMBACC
//
//! @brief Contenedor de familias de acciones.
class ActionsFamiliesMap: public EntConNmb
  {
  public:
    typedef std::map<std::string,ActionsFamily *> map_familias;
    typedef map_familias::iterator iterator;
    typedef map_familias::const_iterator const_iterator;

  private:
    map_familias familias; //!< Conjunto de familias.

    bool exists(const std::string &) const;
    void clear(void);
    ActionsFamiliesMap(const ActionsFamiliesMap &otro);
    ActionsFamiliesMap &operator=(const ActionsFamiliesMap &otro);
  protected:
    friend class ActionContainer;
  public:
    ActionsFamiliesMap(const std::string &,const PartialSafetyFactors &defaultGF= PartialSafetyFactors());
    ActionRValue &insert(const std::string &,const Action &,const std::string &combination_factors_name="");
    
    ActionsFamily *getActionsFamily(const std::string &);
    const ActionsFamily *getActionsFamily(const std::string &)const;
    ActionsFamily *newActionsFamily(const std::string &, const PartialSafetyFactors &defaultGF= PartialSafetyFactors());
    boost::python::list getKeys(void) const;    

    LoadCombinationVector getLoadCombinations(const bool &uls,const bool &sit_accidental) const;
    LoadCombinationVector getLoadCombinations(const bool &uls,const bool &sit_accidental,const LeadingActionInfo &) const;
    size_t getNumActions(void) const;
    const CombinationFactorsMap *getPtrCombinationFactors(void) const;
    
    const_iterator begin(void) const
      { return familias.begin(); }
    const_iterator end(void) const
      { return familias.end(); }
    iterator begin(void)
      { return familias.begin(); }
    iterator end(void)
      { return familias.end(); }
    size_t size(void) const
      { return familias.size(); }
    bool empty(void) const;
    
    virtual ~ActionsFamiliesMap(void);
  };
} // fin namespace cmb_acc

#endif
