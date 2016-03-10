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
//PsiCoeffsMap.cc

#include "PsiCoeffsMap.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

cmb_acc::PsiCoeffs cmb_acc::PsiCoeffsMap::coefs_por_defecto;

//! @brief Devuelve verdadero si la familia existe.
bool cmb_acc::PsiCoeffsMap::existe(const std::string &nmb) const
  { return (coefs.find(nmb)!=coefs.end()); }

//! @brief Devuelve un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
cmb_acc::PsiCoeffs *cmb_acc::PsiCoeffsMap::getPtrCoefs(const std::string &nmb)
  {
    if(existe(nmb))
      return &(coefs[nmb]);
    else
      {
	std::cerr << "cmb_acc::PsiCoeffsMap::getPtrCoefs; no se encontraron los coeficientes de nombre: '"
                  << nmb << "' se devuelve NULL." << std::endl;
        return NULL;
      }
  }

//! @brief Devuelve un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
const cmb_acc::PsiCoeffs &cmb_acc::PsiCoeffsMap::BuscaCoefs(const std::string &nmb) const
  {
    if(existe(nmb))
      return coefs.find(nmb)->second;
    else
      {
	std::cerr << "cmb_acc::PsiCoeffsMap::BuscaCoefs; no se encontraron los coeficientes de nombre: '"
                  << nmb << "' se devuelven los valores por defecto." << std::endl;
        return coefs_por_defecto;
      }
  }

//! @brief Devuelve un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
const cmb_acc::PsiCoeffs *cmb_acc::PsiCoeffsMap::getPtrCoefs(const std::string &nmb) const
  {
    if(existe(nmb))
      return &(coefs.find(nmb)->second);
    else
      {
	std::cerr << "cmb_acc::PsiCoeffsMap::getPtrCoefs; no se encontraron los coeficientes de nombre: '"
                  << nmb << "' se devuelve NULL." << std::endl;
        return NULL;
      }
  }

//! @brief Constructor por defecto.
cmb_acc::PsiCoeffsMap::PsiCoeffsMap(void)
  : EntCmd(), coefs() {}

//! @brief Lanza la ejecución del bloque de código que se pasa
//! como parámetro para cada una de las acciones del contenedor.
void cmb_acc::PsiCoeffsMap::for_each(CmdStatus &status,const std::string &bloque)
  {
    for(iterator i= coefs.begin();i!=coefs.end();i++)
      {
        (*i).second.set_owner(this);
        (*i).second.EjecutaBloque(status,bloque,"PsiCoeffsMap:for_each");
      }
  }

//! @brief Crea coeficientes con el nombre que se le pasa como parámetro.
cmb_acc::PsiCoeffs *cmb_acc::PsiCoeffsMap::crea_coefs(const std::string &nmb)
  {
    PsiCoeffs *retval= NULL;
    if(existe(nmb))
      retval= &(coefs.find(nmb)->second);
    else //los coeficientes son nuevos.
      {
        PsiCoeffs tmp;
        coefs[nmb]= tmp;
        retval= getPtrCoefs(nmb);
      }
    return retval;
  }

//! @brief Inserta los coeficientes que se pasan como parámetro
void cmb_acc::PsiCoeffsMap::insert(const std::string &nmb,const PsiCoeffs &c)
  { coefs[nmb]= c; }

//! @brief Lee un objeto PsiCoeffsMap desde archivo
bool cmb_acc::PsiCoeffsMap::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string msg_proc_cmd= "(PsiCoeffsMap) Procesando comando: " + cmd;
    if(verborrea>2)
      std::clog << msg_proc_cmd << std::endl;

    if(cmd == "defCoefs") //Definición de coeficientes.
      {
	std::string nmb_coefs= "";
        std::deque<boost::any> fnc_indices= status.Parser().SeparaIndices(this);
        if(fnc_indices.size()>0)
          nmb_coefs= convert_to_string(fnc_indices[0]); //Nombre del set.
        PsiCoeffs *s= crea_coefs(nmb_coefs);
        if(s) s->LeeCmd(status);
        return true;
      }
    else if(cmd == "for_each")
      {
        for_each(status,status.GetBloque());
        return true;
      }
    PsiCoeffs *coefs_ptr= getPtrCoefs(cmd);
    if(coefs_ptr)
      {
        coefs_ptr->set_owner(this);
        coefs_ptr->LeeCmd(status);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve el número de coeficientes definidos.
size_t cmb_acc::PsiCoeffsMap::size(void) const
 { return coefs.size(); }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
//!
//! Soporta los códigos:
any_const_ptr cmb_acc::PsiCoeffsMap::GetProp(const std::string &cod) const
  {
    if(cod == "size")
      {
        tmp_gp_szt= size();
        return any_const_ptr(tmp_gp_szt);
      }
    return EntCmd::GetProp(cod);
  }
