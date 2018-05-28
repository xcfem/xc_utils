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
//ActionContainer.cxx

#include "ActionContainer.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"
#include "LeadingActionInfo.h"


//! @brief Constructor por defecto.
cmb_acc::ActionContainer::ActionContainer(void)
  : G("Permanentes"), 
    G_aster("Permanentes val. no cte."), 
    Q("Variables"),
    A("Accidentales"),
    AS("Sísmicas")
  {
    G.set_owner(this);
    G_aster.set_owner(this);
    Q.set_owner(this);
    A.set_owner(this);
    AS.set_owner(this);
  }

//! @brief Insert the action into the family identified by the string.
cmb_acc::ActionRValue &cmb_acc::ActionContainer::insert(const std::string &familia,const Action &acc,const std::string &combination_factors_name,const std::string &partial_safety_factors_name)
  {
    if(familia=="permanentes")
      return G.insert(acc,combination_factors_name,partial_safety_factors_name);
    else if(familia=="permanentes_nc")
      return G_aster.insert(acc,combination_factors_name,partial_safety_factors_name);
    else if(familia=="variables")
      return Q.insert(acc,combination_factors_name,partial_safety_factors_name);
    else if(familia=="accidentales")
      return A.insert(acc,combination_factors_name,partial_safety_factors_name);
    else if(familia=="sismicas")
      return AS.insert(acc,combination_factors_name,partial_safety_factors_name);
    else
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
	          << "; load family: '"
                  << familia << "' not found. Added to variable loads.\n";
        return Q.insert(acc,combination_factors_name,partial_safety_factors_name);
      }
  }

//! @brief Return el conjunto de acciones permanentes.
const cmb_acc::ActionsFamily &cmb_acc::ActionContainer::getPermanentActions(void) const
  { return G; }

//! @brief Asigna el conjunto de acciones permanentes.
void cmb_acc::ActionContainer::setPermanentActions(const ActionsFamily &g)
  { G= g; }

//! @brief Return the non-constant permanent actions.
const cmb_acc::ActionsFamily &cmb_acc::ActionContainer::getPermanentActionsNC(void) const
  { return G_aster; }

//! @brief Set the non-constant permanent actions.
void cmb_acc::ActionContainer::setPermanentActionsNC(const ActionsFamily &mfa)
  { G_aster= mfa; }

//! @brief Return el conjunto de acciones variables.
const cmb_acc::ActionsFamily &cmb_acc::ActionContainer::getVariableActions(void) const
  { return Q; }

//! @brief Return el conjunto de acciones variables.
void cmb_acc::ActionContainer::setVariableActions(const ActionsFamily &fa)
  { Q= fa; }

//! @brief Return el conjunto de acciones accidentales.
const cmb_acc::ActionsFamily &cmb_acc::ActionContainer::getAccidentalActions(void) const
  { return A; }

//! @brief Asigna el conjunto de acciones accidentales.
void cmb_acc::ActionContainer::setAccidentalActions(const ActionsFamily &fa)
  { A= fa; }

//! @brief Return el conjunto de acciones sísmicas.
const cmb_acc::ActionsFamily &cmb_acc::ActionContainer::getSeismicActions(void) const
  { return AS; }

//! @brief Asigna el conjunto de acciones sísmicas.
void cmb_acc::ActionContainer::setSeismicActions(const ActionsFamily &fa)
  { AS= fa; }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPermanentes(const bool &uls,const bool &sit_accidental) const
//! @brief Return the combinations obtained from permanent and non-constant permanent actions.
//! @param uls: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPermanentes(const bool &uls,const bool &sit_accidental) const
  {
    LoadCombinationVector retval;
    if(!G.empty()) //Hay acciones permanentes.
      {
        retval= G.getActions().getCombinations(uls,sit_accidental,-1);//Las permanentes siempre con characteristic value.
      }
    if(!G_aster.empty()) //There are non-constant permanent actions.
      {
        const LoadCombinationVector SG_aster= G_aster.getActions().getCombinations(uls,sit_accidental,-1);//Las permanentes siempre con characteristic value.
        retval= LoadCombinationVector::ProdCartesiano(retval,SG_aster,Action::zero);
      }
    retval= get_compatibles(retval); //Filtramos las que contienen acciones incompatibles
                                                                   // o esclavas huérfanas.
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetVariables(const LoadCombinationVector &permanentes,const bool &uls,const bool &sit_accidental,const short int &v) const
//! @brief Return las combinaciones que corresponden a acciones permanentes (incluso no constantes) y variables.
//! @param permanentes: LoadCombinations de las acciones permanentes obtenidas mediante cmb_acc::ActionContainer::GetPermanentes.
//! @param uls: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
//! @param v: representative value to consider for the leading action.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetVariables(const LoadCombinationVector &permanentes,const bool &uls,const bool &sit_accidental,const short int &v) const
  {
    LoadCombinationVector retval; //Inicializa con acciones permanentes.
    if(!Q.empty()) //Hay acciones variables.
      {
        LoadCombinationVector SQ= Q.getActions().getCombinationsWhenLeading(uls,sit_accidental,v);
        retval= LoadCombinationVector::ProdCartesiano(permanentes,SQ,Action::zero);
        if(uls) retval= LoadCombinationVector::Concat(permanentes,retval,Action::zero); //Si ULS consideramos también las cargas permanentes SOLAS.
      }
    else //No hay acciones variables.
      retval= permanentes;
    retval= get_compatibles(retval); //Filtramos las combinaciones que contienen acciones incompatibles
                                                                   // o esclavas huérfanas.
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetAccSis(const LoadCombinationVector &previas,const ActionsFamily &Acc) const
//! @brief Return las combinaciones correspondientes en situaciones accidentales o sísmicas.
//! @param previas: LoadCombinations de las acciones permanentes y variables obtenidas mediante cmb_acc::ActionContainer::GetVariables.
//! @param Acc: Familia de acciones accidentales o sísmicas.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetAccSis(const LoadCombinationVector &previas,const ActionsFamily &Acc) const
  {
    LoadCombinationVector retval(previas);
    if(!Acc.empty()) //Existen acciones accidentales o sísmicas.
      {
        const size_t na= Acc.getActions().size();
        LoadCombinationVector SA;
        for(size_t i=0;i<na;i++) //i: Índice de la acción accidental o sísmica.
          {
	    LeadingActionInfo lci(i,-1,0); //Leading action with characteristic value (-1)
                                           //rest of actions with combination value 0 (WHICH MUST BE ZERO).
            LoadCombinationVector temp= Acc.getActions().getCombinations(true,true,lci);
            SA= LoadCombinationVector::Concat(SA,temp,Action::zero);
          }
        retval= LoadCombinationVector::ProdCartesiano(retval,SA,Action::zero);
      }
    retval= get_compatibles(retval); //Filtramos las que contienen acciones incompatibles.
    return retval;
  }



//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPersistentesOTransit(void) const
//! @brief Return las combinaciones correspondientes a estados límite últimos en situaciones persistentes o transitorias.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPersistentesOTransit(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ULS en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(true,false); //ULS, situación no accidental.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,true,false,0);//ULS, leading action with characteristic value
                                              //rest of actions with combination value.
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    return retval;
  }

//! \fn cmb_acc::ActionContainer::GetAccidentales(void) const
//! @brief Return las combinaciones correspondientes a  estados límite últimos en situaciones accidentales.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetAccidentales(void) const
  {
    LoadCombinationVector retval;
    if(A.empty()) return retval; //No hay acciones accidentales.
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ULS en situaciones accidentales..." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    retval= GetPermanentes(true,true); //ULS, situación accidental.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,true,true,2); //ULS, leading action with characteristic value
                                              //rest of actions with cuasi-permanent value.
    if(verbosity>1) std::clog << "  done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones accidentales...";
    retval= GetAccSis(retval,A);
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    return retval;
  }


//! \fn cmb_acc::ActionContainer::GetSismicas(void) const
//! @brief Return las combinaciones correspondientes a  estados límite últimos en situaciones sísmicas.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetSismicas(void) const
  {
    LoadCombinationVector retval;
    if(AS.empty()) return retval; //No hay acciones sismicas.
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ULS en situaciones sísmicas..." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    retval= GetPermanentes(true,true); //ULS, situación accidental.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    if(!Q.empty()) //Hay acciones variables.
      {
        LoadCombinationVector SQ= Q.getActions().getCombinations(true,true,2); //ULS, all actions with quasi-permanent value.
        retval= LoadCombinationVector::ProdCartesiano(retval,SQ,Action::zero);
      }
    if(verbosity>1) std::clog << "  done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones sísmicas...";
    retval= GetAccSis(retval,AS);
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    return retval;
  }

//! \fn cmb_acc::ActionContainer::GetCombULS(void) const
//! @brief Return las combinaciones correspondientes a todas las situaciones de ESTADO LIMITE ÚLTIMO.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCombULS(void) const
  {
    LoadCombinationVector retval= GetPersistentesOTransit(); //Situaciones persistentes o transitorias.
    LoadCombinationVector accidentales= GetAccidentales();
    retval= LoadCombinationVector::Concat(retval,accidentales,0.0);
    LoadCombinationVector sismicas= GetSismicas();
    retval= LoadCombinationVector::Concat(retval,sismicas,0.0);
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "  Calculadas " << retval.size() << " combinaciones ULS." << std::endl;
    retval.Numera("H-ULS-");
    return retval;
  }

//serviceability limit states.


//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPocoFrecuentes(void) const
//! @brief Return las combinaciones correspondientes a situaciones poco frecuentes en ESTADO LIMITE DE SERVICIO.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPocoFrecuentes(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para SLS en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(false,false); //SLS, situación no accidental (obviamente).
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,0);//SLS, leading action with characteristic value
                                              //rest of actions with combination value.
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetFrecuentes(void) const
//! @brief Return las combinaciones correspondientes a situaciones persistentes o transitorias.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetFrecuentes(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para SLS en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(false,false); //SLS, situación no accidental (obviamente).
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,1);//SLS, leading action with characteristic value
                                              //rest of actions with quasi-permanent value.
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCuasiPermanentes(void) const
//! @brief Return las combinaciones correspondientes a situaciones persistentes o transitorias.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCuasiPermanentes(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para SLS en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(false,false); //SLS, situación no accidental.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,2);//SLS, all actions with quasi-permanent value.
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    if(verbosity>1) std::clog << "done." << std::endl;
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCombSLS(void) const
//! @brief Return las combinaciones correspondientes a todas las situaciones de ESTADO LIMITE DE SERVICIO.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCombSLS(void) const
  {
    LoadCombinationVector retval= GetPocoFrecuentes(); //LoadCombinations poco frecuentes.
    LoadCombinationVector frecuente= GetFrecuentes();
    retval= LoadCombinationVector::Concat(retval,frecuente,0.0);
    LoadCombinationVector cp= GetCuasiPermanentes();
    retval= LoadCombinationVector::Concat(retval,cp,0.0);
    retval= filtraCombsEsclavasHuerfanas(get_compatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "  Calculadas " << retval.size() << " combinaciones SLS." << std::endl;
    retval.Numera("H-SLS-");
    return retval;
  }
