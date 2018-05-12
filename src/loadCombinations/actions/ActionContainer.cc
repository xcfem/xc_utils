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

//Default partial safety factors

//for permanent actions
cmb_acc::GammaF defaultG(cmb_acc::GammaFELU(1.0,1.5,1.0,1.0),cmb_acc::GammaFELS(1.0,1.0)); 
//for variable actions
cmb_acc::GammaF defaultQ(cmb_acc::GammaFELU(0.0,1.6,0.0,1.0),cmb_acc::GammaFELS(0.0,1.0));
//for accidental actions
cmb_acc::GammaF defaultA(cmb_acc::GammaFELU(0.0,0.0,1.0,1.0));
//for seismic actions
cmb_acc::GammaF defaultS(cmb_acc::GammaFELU(0.0,0.0,1.0,1.0));

//! \fn cmb_acc::ActionContainer::ActionContainer(void)
//! @brief Constructor por defecto.
cmb_acc::ActionContainer::ActionContainer(const PsiCoeffsMap &coefs)
  : G("Permanentes",defaultG), 
    G_aster("Permanentes val. no cte.",defaultG), 
    Q("Variables",defaultQ),
    A("Accidentales",defaultA),
    AS("Sísmicas",defaultS),
    coefs_psi(coefs)
  {
    G.set_owner(this);
    G_aster.set_owner(this);
    Q.set_owner(this);
    A.set_owner(this);
    AS.set_owner(this);
  }

//! @brief Insert the action into the family identified by the string.
cmb_acc::ActionRValue &cmb_acc::ActionContainer::insert(const std::string &familia,const Action &acc,const std::string &nmb_coefs_psi,const std::string &subfamilia)
  {
    if(familia=="permanentes")
      return G.insert(subfamilia,acc,nmb_coefs_psi);
    else if(familia=="permanentes_nc")
      return G_aster.insert(subfamilia,acc,nmb_coefs_psi);
    else if(familia=="variables")
      return Q.insert(subfamilia,acc,nmb_coefs_psi);
    else if(familia=="accidentales")
      return A.insert(acc,nmb_coefs_psi);
    else if(familia=="sismicas")
      return AS.insert(acc,nmb_coefs_psi);
    else
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
	          << "; load family: '"
                  << familia << "' not found. Added to variable loads.\n";
        return Q.insert(subfamilia,acc,nmb_coefs_psi);
      }
  }

//! @brief Return el conjunto de acciones permanentes.
const cmb_acc::ActionsFamiliesMap &cmb_acc::ActionContainer::getPermanentActions(void) const
  { return G; }

//! @brief Asigna el conjunto de acciones permanentes.
void cmb_acc::ActionContainer::setPermanentActions(const ActionsFamiliesMap &g)
  { G= g; }

//! @brief Return el conjunto de acciones permanentes de valor no constante.
const cmb_acc::ActionsFamiliesMap &cmb_acc::ActionContainer::getPermanentActionsNC(void) const
  { return G_aster; }

//! @brief Asigna el conjunto de acciones permanentes de valor no constante.
void cmb_acc::ActionContainer::setPermanentActionsNC(const ActionsFamiliesMap &mfa)
  { G_aster= mfa; }

//! @brief Return el conjunto de acciones variables.
const cmb_acc::ActionsFamiliesMap &cmb_acc::ActionContainer::getVariableActions(void) const
  { return Q; }

//! @brief Return el conjunto de acciones variables.
void cmb_acc::ActionContainer::setVariableActions(const ActionsFamiliesMap &fa)
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

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsG(const bool &elu,const bool &sit_accidental) const
//! @brief Return las combinaciones que se forman con las acciones permanentes.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsG(const bool &elu,const bool &sit_accidental) const
  { return G.GetLoadCombinations(elu,sit_accidental,-1); } //Las permanentes siempre con characteristic value.

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsG_aster(const bool &elu,const bool &sit_accidental) const
//! @brief Return las combinaciones que se forman con las acciones permanentes de valor no constante.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsG_aster(const bool &elu,const bool &sit_accidental) const
  { return G_aster.GetLoadCombinations(elu,sit_accidental); } 

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsQ(const bool &elu,const bool &sit_accidental,short int r,int d,short int rr) const
//! @brief Return las combinaciones que se forman con las acciones variables.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
//! @param r: Valor representativo a emplear para el caso general.
//! - r= -1 -> characteristic value.
//! - r= 0 -> valor de combinación.
//! - r= 1 -> valor frecuente.
//! - r= 2 -> valor cuasipermanente.
//! @param d: Índice de la acción determinante (si no hay acción determinante d=-1).
//! @param rr: Valor representativo a emplear para la acción determinante.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsQ(const bool &elu,const bool &sit_accidental,short int r,int d,short int rr) const
  { return Q.GetLoadCombinations(elu,sit_accidental,r,d,rr); }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsA(short int r,int d,short int rr) const
//! @brief Return las combinaciones que se forman con las acciones accidentales.
//! @param r: Valor representativo a emplear para el caso general.
//! - r= -1 -> characteristic value.
//! - r= 0 -> valor de combinación.
//! - r= 1 -> valor frecuente.
//! - r= 2 -> valor cuasipermanente.
//! @param d: Índice de la acción determinante (si no hay acción determinante d=-1).
//! @param rr: Valor representativo a emplear para la acción determinante.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsA(short int r,int d,short int rr) const
  { return A.GetLoadCombinations(true,true,r,d,rr); }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsAS(short int r,int d,short int rr) const
//! @brief Return las combinaciones que se forman con las acciones sísmicas.
//! @param r: Valor representativo a emplear para el caso general.
//! - r= -1 -> characteristic value.
//! - r= 0 -> valor de combinación.
//! - r= 1 -> valor frecuente.
//! - r= 2 -> valor cuasipermanente.
//! @param d: Índice de la acción determinante (si no hay acción determinante d=-1).
//! @param rr: Valor representativo a emplear para la acción determinante.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetLoadCombinationsAS(short int r,int d,short int rr) const
  { return AS.GetLoadCombinations(true,true,r,d,rr); }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPermanentes(const bool &elu,const bool &sit_accidental) const
//! @brief Return las combinaciones correspondientes a acciones permanentes y permanentes de valor no constante.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPermanentes(const bool &elu,const bool &sit_accidental) const
  {
    LoadCombinationVector retval;
    if(!G.empty()) //Hay acciones permanentes.
      {
        retval= GetLoadCombinationsG(elu,sit_accidental);
      }
    if(!G_aster.empty()) //Hay acciones permanentes de valor no constante.
      {
        const LoadCombinationVector SG_aster= GetLoadCombinationsG_aster(elu,sit_accidental);
        retval= LoadCombinationVector::ProdCartesiano(retval,SG_aster,Action::zero);
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles
                                                                   // o esclavas huérfanas.
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetVariables(const LoadCombinationVector &permanentes,const bool &elu,const bool &sit_accidental,const short int &v) const
//! @brief Return las combinaciones que corresponden a acciones permanentes (incluso no constantes) y variables.
//! @param permanentes: LoadCombinations de las acciones permanentes obtenidas mediante cmb_acc::ActionContainer::GetPermanentes.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
//! @param v: Valor representativo a considerar para la acción determinante.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetVariables(const LoadCombinationVector &permanentes,const bool &elu,const bool &sit_accidental,const short int &v) const
  {
    LoadCombinationVector retval; //Inicializa con acciones permanentes.
    if(!Q.empty()) //Hay acciones variables.
      {
        const size_t nq= Q.getNumActions();
        LoadCombinationVector SQ;
        for(size_t i=0;i<nq;i++) //i: Índice de la acción determinante.
          {
            if(verbosity>1) std::clog << std::endl << "    Obteniendo combinaciones de acciones variables con acción determinante: " << i << " ...";
            LoadCombinationVector temp= GetLoadCombinationsQ(elu,sit_accidental,v,i,v-1); //Acción determinante con valor v
                                                                                     //resto con valor v-1.
            SQ= LoadCombinationVector::Concat(SQ,temp,Action::zero);
            if(verbosity>1) std::clog << "hecho." << std::endl;
          }
        retval= LoadCombinationVector::ProdCartesiano(permanentes,SQ,Action::zero);
        if(elu) retval= LoadCombinationVector::Concat(permanentes,retval,Action::zero); //Si ELU consideramos también las cargas permanentes SOLAS.
      }
    else //No hay acciones variables.
      retval= permanentes;
    retval= getCompatibles(retval); //Filtramos las combinaciones que contienen acciones incompatibles
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
        const size_t na= Acc.getNumActions();
        LoadCombinationVector SA;
        for(size_t i=0;i<na;i++) //i: Índice de la acción accidental o sísmica.
          {
            LoadCombinationVector temp= Acc.GetLoadCombinations(true,true,0,i,-1); //Acción accidental o sísmica i con characteristic value
                                                                              //resto con valor de combinación (QUE DEBE SER NULO).
            SA= LoadCombinationVector::Concat(SA,temp,Action::zero);
          }
        retval= LoadCombinationVector::ProdCartesiano(retval,SA,Action::zero);
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles.
    return retval;
  }



//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPersistentesOTransit(void) const
//! @brief Return las combinaciones correspondientes a estados límite últimos en situaciones persistentes o transitorias.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPersistentesOTransit(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ELU en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(true,false); //ELU, situación no accidental.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,true,false,0);//ELU, acción determinante con characteristic value
                                              //resto con valor de combinación.
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::ActionContainer::GetAccidentales(void) const
//! @brief Return las combinaciones correspondientes a  estados límite últimos en situaciones accidentales.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetAccidentales(void) const
  {
    LoadCombinationVector retval;
    if(A.empty()) return retval; //No hay acciones accidentales.
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ELU en situaciones accidentales..." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    retval= GetPermanentes(true,true); //ELU, situación accidental.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,true,true,2); //ELU, acción determinante con valor frecuente
                                              //resto con valor de cuasipermanente.
    if(verbosity>1) std::clog << "  hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones accidentales...";
    retval= GetAccSis(retval,A);
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    return retval;
  }


//! \fn cmb_acc::ActionContainer::GetSismicas(void) const
//! @brief Return las combinaciones correspondientes a  estados límite últimos en situaciones sísmicas.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetSismicas(void) const
  {
    LoadCombinationVector retval;
    if(AS.empty()) return retval; //No hay acciones sismicas.
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ELU en situaciones sísmicas..." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    retval= GetPermanentes(true,true); //ELU, situación accidental.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    if(!Q.empty()) //Hay acciones variables.
      {
        LoadCombinationVector SQ= GetLoadCombinationsQ(true,true,2); //ELU, todas con valor cuasipermanente.
        retval= LoadCombinationVector::ProdCartesiano(retval,SQ,Action::zero);
      }
    if(verbosity>1) std::clog << "  hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones sísmicas...";
    retval= GetAccSis(retval,AS);
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::ActionContainer::GetCombELU(void) const
//! @brief Return las combinaciones correspondientes a todas las situaciones de ESTADO LIMITE ÚLTIMO.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCombELU(void) const
  {
    LoadCombinationVector retval= GetPersistentesOTransit(); //Situaciones persistentes o transitorias.
    LoadCombinationVector accidentales= GetAccidentales();
    retval= LoadCombinationVector::Concat(retval,accidentales,0.0);
    LoadCombinationVector sismicas= GetSismicas();
    retval= LoadCombinationVector::Concat(retval,sismicas,0.0);
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "  Calculadas " << retval.size() << " combinaciones ELU." << std::endl;
    retval.Numera("H-ELU-");
    return retval;
  }

//serviceability limit states.


//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPocoFrecuentes(void) const
//! @brief Return las combinaciones correspondientes a situaciones poco frecuentes en ESTADO LIMITE DE SERVICIO.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetPocoFrecuentes(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ELS en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(false,false); //ELS, situación no accidental (obviamente).
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,0);//ELS, acción determinante con characteristic value
                                               //resto con valor de combinación.
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetFrecuentes(void) const
//! @brief Return las combinaciones correspondientes a situaciones persistentes o transitorias.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetFrecuentes(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ELS en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(false,false); //ELS, situación no accidental (obviamente).
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,1);//ELS, acción determinante con valor frecuente
                                               //resto con valor de cuasipermanente. 
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCuasiPermanentes(void) const
//! @brief Return las combinaciones correspondientes a situaciones persistentes o transitorias.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCuasiPermanentes(void) const
  {
    if(verbosity>1) std::clog << "Obteniendo combinaciones de acciones para ELS en situaciones persistentes o transitorias..." << std::endl; 
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    LoadCombinationVector retval= GetPermanentes(false,false); //ELS, situación no accidental.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,2);//ELS, todas con valor cuasipermanente.
    if(verbosity>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    if(verbosity>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCombELS(void) const
//! @brief Return las combinaciones correspondientes a todas las situaciones de ESTADO LIMITE DE SERVICIO.
cmb_acc::LoadCombinationVector cmb_acc::ActionContainer::GetCombELS(void) const
  {
    LoadCombinationVector retval= GetPocoFrecuentes(); //LoadCombinations poco frecuentes.
    LoadCombinationVector frecuente= GetFrecuentes();
    retval= LoadCombinationVector::Concat(retval,frecuente,0.0);
    LoadCombinationVector cp= GetCuasiPermanentes();
    retval= LoadCombinationVector::Concat(retval,cp,0.0);
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verbosity>1) std::clog << "  Calculadas " << retval.size() << " combinaciones ELS." << std::endl;
    retval.Numera("H-ELS-");
    return retval;
  }
