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
//ActionWeightingMap.h
//Container for actions and corresponding factors.

#ifndef ACTIONWEIGHTINGMAP_H
#define ACTIONWEIGHTINGMAP_H

#include "xc_utils/src/nucleo/EntCmd.h"
#include "xc_utils/src/loadCombinations/factors/Factors.h"
#include <map>


namespace cmb_acc {

class Action;
class ActionRValue;
class ActionsAndFactors;
class LoadCombinations;

//! @ingroup CMBACC
//
//! @brief Container for ActionAndFactors objects.
class ActionWeightingMap: public EntCmd
  {
  public:
    typedef std::map<std::string,ActionsAndFactors *> map_actions_and_factors;
    typedef map_actions_and_factors::iterator iterator;
    typedef map_actions_and_factors::const_iterator const_iterator;

  private:
    map_actions_and_factors actions_and_factors; //!< actions with its factors.

    bool exists(const std::string &nmb) const;
    ActionsAndFactors *findOrCreate(const std::string &nmb,const Factors &coefs= Factors());
    void clear(void);
    void copy(const map_actions_and_factors &pond);
  protected:
    friend class ActionsAndFactors;
  public:
    ActionWeightingMap(void);
    ActionWeightingMap(const ActionWeightingMap &otro);
    ActionWeightingMap &operator=(const ActionWeightingMap &otro);
    virtual ~ActionWeightingMap(void);
    cmb_acc::ActionsAndFactors *create(const std::string &,const Factors &coefs= Factors());

    ActionRValue &insert(const std::string &pond,const std::string &,const Action &,const std::string &combination_factors_name="",const std::string &partial_safety_factors_name="");

    size_t size(void) const;
    bool empty(void) const;
    iterator begin(void);
    const_iterator begin(void) const;
    iterator end(void);
    const_iterator end(void) const;
    boost::python::list getKeys(void) const;    
    ActionsAndFactors *findByName(const std::string &nmb);
    const ActionsAndFactors *findByName(const std::string &nmb) const;

    LoadCombinations getLoadCombinations(void);
  };

} // fin namespace cmb_acc

#endif
