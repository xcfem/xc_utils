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
//MapFamiliasAcc.cc

#include "MapFamiliasAcc.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "FamiliaAcciones.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"
#include "AccionesClasificadas.h"


//! @brief Devuelve verdadero si la familia existe.
bool cmb_acc::MapFamiliasAcc::existe(const std::string &nmb) const
  { return (familias.find(nmb)!=familias.end()); }

//! @brief Devuelve un puntero a la familia cuyo nombre se pasa como parámetro.
cmb_acc::FamiliaAcciones *cmb_acc::MapFamiliasAcc::busca_familia_acc(const std::string &nmb)
  {
    if(existe(nmb))
      return familias[nmb];
    else
      return NULL;
  }

//! @brief Devuelve un puntero a la familia cuyo nombre se pasa como parámetro.
const cmb_acc::FamiliaAcciones *cmb_acc::MapFamiliasAcc::busca_familia_acc(const std::string &nmb) const
  {
    const_iterator i= familias.find(nmb);
    if(i!= familias.end())
      return (*i).second;
    else
      return NULL;
  }

//! @brief Inserta la acción en la familia que se pasa como parámetro.
cmb_acc::VRAccion &cmb_acc::MapFamiliasAcc::inserta(const std::string &familia,const Accion &acc,const std::string &nmb_coefs_psi)
  {
    FamiliaAcciones *familia_ptr= busca_familia_acc(familia);
    if(!familia_ptr)
      {
        std::cerr << "MapFamiliasAcc::inserta no se encontró la familia: '"
                  << familia << "'\n";
        const_iterator i= familias.begin();
        familia_ptr= (*i).second;
      }
    return familia_ptr->inserta(acc,nmb_coefs_psi);
  }

//! @brief Crea una nueva familia con el nombre que se le pasa como parámetro.
cmb_acc::FamiliaAcciones *cmb_acc::MapFamiliasAcc::crea_familia_acc(const std::string &nmb)
  {
    FamiliaAcciones *tmp =NULL;
    if(!existe(nmb)) //la familia es nuevo.
      {
        tmp= new FamiliaAcciones(nmb,GammaF(GammaFELU(1.0,1.6,1.0,1.0),GammaFELS(0.9,1.1)));//Coeficientes de ponderación por defecto 
                                                                                            //para acciones permanentes de valor no constante.
        familias[nmb]= tmp;
      }
    else //la familia existe
      tmp= busca_familia_acc(nmb);
    return tmp;
  }

//! @brief Constructor por defecto.
cmb_acc::MapFamiliasAcc::MapFamiliasAcc(const std::string &nmb)
  : EntConNmb(nmb) {}

//! @brief Constructor de copia (NO COPIA LAS FAMILIAS).
cmb_acc::MapFamiliasAcc::MapFamiliasAcc(const MapFamiliasAcc &otro)
  : EntConNmb(otro){}

//! @brief Operador asignación (NO COPIA LAS FAMILIAS).
cmb_acc::MapFamiliasAcc &cmb_acc::MapFamiliasAcc::operator=(const MapFamiliasAcc &otro)
  {
    EntConNmb::operator=(otro);
    return *this;
  }

//! @brief Devuelve un puntero a la tabla de coeficientes de simultaneidad.
const cmb_acc::PsiCoeffsMap *cmb_acc::MapFamiliasAcc::getPtrPsiCoeffs(void) const
  {
    const AccionesClasificadas *tmp= dynamic_cast<const AccionesClasificadas *>(Owner());
    if(tmp)
      return tmp->getPtrPsiCoeffs();
    else
      {
	std::cerr << "MapFamiliasAcc::getPtrPsiCoeffs; no se encontró el objeto propietario de éste." << std::endl;
        return NULL;
      }
  }

//! @brief Lanza la ejecución del bloque de código que se pasa
//! como parámetro para cada una de las acciones del contenedor.
void cmb_acc::MapFamiliasAcc::for_each_accion(CmdStatus &status,const std::string &bloque)
  {
    for(iterator i= familias.begin();i!=familias.end();i++)
      {
        (*i).second->set_owner(this);
        (*i).second->for_each_accion(status,bloque);
      }
  }


//! @brief Lee un objeto MapFamiliasAcc desde archivo
bool cmb_acc::MapFamiliasAcc::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string msg_proc_cmd= "(MapFamiliasAcc) Procesando comando: " + cmd;
    if(verborrea>2)
      std::clog << msg_proc_cmd << std::endl;
    if(cmd == "defFamiliaAcciones") //Definición de una familia.
      {
	std::string nmb_familia_acc= "";
        std::deque<boost::any> fnc_indices= status.Parser().SeparaIndices(this);
        if(fnc_indices.size()>0)
          nmb_familia_acc= convert_to_string(fnc_indices[0]); //Nombre del set.
        FamiliaAcciones *s= crea_familia_acc(nmb_familia_acc);
        if(s)
          {
            s->set_owner(this);
            s->LeeCmd(status);
          }
        return true;
      }
    else if(cmd == "for_each")
      {
        const std::string bloque= status.GetBloque();
        for(iterator i= familias.begin();i!=familias.end();i++)
          {
            (*i).second->set_owner(this);
            (*i).second->EjecutaBloque(status,bloque,GetNombre()+":for_each");
          }
        return true;
      }
    else if(cmd == "for_each_accion")
      {
        const std::string bloque= status.GetBloque();
        for_each_accion(status,bloque);
        return true;
      }
    FamiliaAcciones *familia_ptr= busca_familia_acc(cmd);
    if(familia_ptr)
      {
        familia_ptr->set_owner(this);
        familia_ptr->LeeCmd(status);
        return true;
      }
    else
      return EntConNmb::procesa_comando(status);
  }

//! @brief Borra todas las familias definidos.
void cmb_acc::MapFamiliasAcc::clear(void)
  {
    for(iterator i= familias.begin();i!=familias.end();i++)
      {
        delete (*i).second;
        (*i).second= NULL;
      }
    familias.clear();
  }

cmb_acc::MapFamiliasAcc::~MapFamiliasAcc(void)
  {
    familias.clear();
    clear();
  }

//! @brief Devuelve el número de acciones de todas las familias.
size_t cmb_acc::MapFamiliasAcc::getNumAcciones(void) const
  { 
    size_t retval= 0;
    if(!familias.empty())
      for(const_iterator i= familias.begin();i!=familias.end();i++)
        {          
          FamiliaAcciones *familia= (*i).second;
          if(familia)
            retval+= familia->getNumAcciones();
	}
    return retval;
  }

//! brief Devuelve verdadero si las familias estan vacías.
bool cmb_acc::MapFamiliasAcc::Vacia(void) const
  {
    bool retval= true;
    if(!familias.empty())
      for(const_iterator i= familias.begin();i!=familias.end();i++)
        {
          FamiliaAcciones *familia= (*i).second;
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


//! @brief Devuelve las combinaciones correspondientes a acciones permanentes de valor no constante.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::LoadCombinationVector cmb_acc::MapFamiliasAcc::GetLoadCombinations(const bool &elu,const bool &sit_accidental) const
  {
    LoadCombinationVector retval;
    for(const_iterator i= familias.begin();i!=familias.end();i++)
      {
        FamiliaAcciones *familia= (*i).second;
        assert(familia);
        if(!familia->Vacia()) //La familia contiene acciones.
          {
            LoadCombinationVector SG_aster= familia->GetLoadCombinations(elu,sit_accidental,-1);//Las permanentes siempre con valor característico.
            retval= LoadCombinationVector::ProdCartesiano(retval,SG_aster,Accion::zero);
          }
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles.
    return retval;
  }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
//!
//! Soporta los códigos:
any_const_ptr cmb_acc::MapFamiliasAcc::GetProp(const std::string &cod) const
  {
    const FamiliaAcciones *familia_ptr= busca_familia_acc(cod);
    if(cod == "num_familias")
      {
        tmp_gp_szt= familias.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "num_acciones")
      {
        tmp_gp_szt= getNumAcciones();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(familia_ptr)
      return any_const_ptr(familia_ptr);
    else
      return EntConNmb::GetProp(cod);
  }
