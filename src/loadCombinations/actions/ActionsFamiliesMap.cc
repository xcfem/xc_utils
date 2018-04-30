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
#include "ActionContainer.h"


//! @brief Return verdadero si la familia existe.
bool cmb_acc::ActionsFamiliesMap::existe(const std::string &nmb) const
  { return (familias.find(nmb)!=familias.end()); }

//! @brief Return un puntero a la familia cuyo nombre se pasa como parámetro.
cmb_acc::ActionsFamily *cmb_acc::ActionsFamiliesMap::busca_familia_acc(const std::string &nmb)
  {
    if(existe(nmb))
      return familias[nmb];
    else
      return nullptr;
  }

//! @brief Return un puntero a la familia cuyo nombre se pasa como parámetro.
const cmb_acc::ActionsFamily *cmb_acc::ActionsFamiliesMap::busca_familia_acc(const std::string &nmb) const
  {
    const_iterator i= familias.find(nmb);
    if(i!= familias.end())
      return (*i).second;
    else
      return nullptr;
  }

//! @brief Insert the action in the family.
cmb_acc::ActionRValue &cmb_acc::ActionsFamiliesMap::insert(const std::string &familia,const Action &acc,const std::string &nmb_coefs_psi)
  {
    ActionsFamily *familia_ptr= busca_familia_acc(familia);
    if(!familia_ptr)
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; family: '"
                  << familia << "' not found.\n";
        const_iterator i= familias.begin();
        familia_ptr= (*i).second;
      }
    return familia_ptr->insert(acc,nmb_coefs_psi);
  }

//! @brief Crea una nueva familia con el nombre que se le pasa como parámetro.
cmb_acc::ActionsFamily *cmb_acc::ActionsFamiliesMap::crea_familia_acc(const std::string &nmb)
  {
    ActionsFamily *tmp =nullptr;
    if(!existe(nmb)) //la familia es nuevo.
      {
        tmp= new ActionsFamily(nmb,GammaF(GammaFELU(1.0,1.6,1.0,1.0),GammaFELS(0.9,1.1)));//Partial safety factors por defecto 
                                                                                            //para acciones permanentes de valor no constante.
        familias[nmb]= tmp;
      }
    else //la familia existe
      tmp= busca_familia_acc(nmb);
    return tmp;
  }

//! @brief Constructor por defecto.
cmb_acc::ActionsFamiliesMap::ActionsFamiliesMap(const std::string &nmb)
  : EntConNmb(nmb) {}

//! @brief Constructor de copia (NO COPIA LAS FAMILIAS).
cmb_acc::ActionsFamiliesMap::ActionsFamiliesMap(const ActionsFamiliesMap &otro)
  : EntConNmb(otro){}

//! @brief Operador asignación (NO COPIA LAS FAMILIAS).
cmb_acc::ActionsFamiliesMap &cmb_acc::ActionsFamiliesMap::operator=(const ActionsFamiliesMap &otro)
  {
    EntConNmb::operator=(otro);
    return *this;
  }

//! @brief Return un puntero a la tabla de coeficientes de simultaneidad.
const cmb_acc::PsiCoeffsMap *cmb_acc::ActionsFamiliesMap::getPtrPsiCoeffs(void) const
  {
    const ActionContainer *tmp= dynamic_cast<const ActionContainer *>(Owner());
    if(tmp)
      return tmp->getPtrPsiCoeffs();
    else
      {
	std::cerr << "ActionsFamiliesMap::getPtrPsiCoeffs; no se encontró el objeto propietario de éste." << std::endl;
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
bool cmb_acc::ActionsFamiliesMap::Vacia(void) const
  {
    bool retval= true;
    if(!familias.empty())
      for(const_iterator i= familias.begin();i!=familias.end();i++)
        {
          ActionsFamily *familia= (*i).second;
          if(familia)
            {
              if(!familia->Vacia()) //La familia contiene acciones.
                {
                  retval= false;
                  break;
                }
            }
	}
    return retval;
  }


//! @brief Return las combinaciones correspondientes a acciones permanentes de valor no constante.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::LoadCombinationVector cmb_acc::ActionsFamiliesMap::GetLoadCombinations(const bool &elu,const bool &sit_accidental) const
  {
    LoadCombinationVector retval;
    for(const_iterator i= familias.begin();i!=familias.end();i++)
      {
        ActionsFamily *familia= (*i).second;
        assert(familia);
        if(!familia->Vacia()) //La familia contiene acciones.
          {
            LoadCombinationVector SG_aster= familia->GetLoadCombinations(elu,sit_accidental,-1);//Las permanentes siempre con characteristic value.
            retval= LoadCombinationVector::ProdCartesiano(retval,SG_aster,Action::zero);
          }
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles.
    return retval;
  }
