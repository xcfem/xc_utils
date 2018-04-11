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
                  << nmb << "' se devuelve nullptr." << std::endl;
        return nullptr;
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
                  << nmb << "' se devuelve nullptr." << std::endl;
        return nullptr;
      }
  }

//! @brief Constructor por defecto.
cmb_acc::PsiCoeffsMap::PsiCoeffsMap(void)
  : EntCmd(), coefs() {}

//! @brief Crea coeficientes con el nombre que se le pasa como parámetro.
cmb_acc::PsiCoeffs *cmb_acc::PsiCoeffsMap::crea_coefs(const std::string &nmb)
  {
    PsiCoeffs *retval= nullptr;
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

//! @brief Inserts the coefficients.
void cmb_acc::PsiCoeffsMap::insert(const std::string &nmb,const PsiCoeffs &c)
  { coefs[nmb]= c; }

//! @brief Devuelve el número de coeficientes definidos.
size_t cmb_acc::PsiCoeffsMap::size(void) const
 { return coefs.size(); }

