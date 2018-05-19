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
//CombinationFactorsMap.cc

#include "CombinationFactorsMap.h"



cmb_acc::CombinationFactors cmb_acc::CombinationFactorsMap::coefs_por_defecto;

//! @brief Return verdadero si la familia existe.
bool cmb_acc::CombinationFactorsMap::existe(const std::string &nmb) const
  { return (coefs.find(nmb)!=coefs.end()); }

//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
cmb_acc::CombinationFactors *cmb_acc::CombinationFactorsMap::getPtrCoefs(const std::string &nmb)
  {
    if(existe(nmb))
      return &(coefs[nmb]);
    else
      {
	std::cerr << "cmb_acc::CombinationFactorsMap::getPtrCoefs; no se encontraron los coeficientes de nombre: '"
                  << nmb << "' se devuelve nullptr." << std::endl;
        return nullptr;
      }
  }

//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
const cmb_acc::CombinationFactors &cmb_acc::CombinationFactorsMap::BuscaCoefs(const std::string &nmb) const
  {
    if(existe(nmb))
      return coefs.find(nmb)->second;
    else
      {
	std::cerr << "cmb_acc::CombinationFactorsMap::BuscaCoefs; no se encontraron los coeficientes de nombre: '"
                  << nmb << "' se devuelven los valores por defecto." << std::endl;
        return coefs_por_defecto;
      }
  }

//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
const cmb_acc::CombinationFactors *cmb_acc::CombinationFactorsMap::getPtrCoefs(const std::string &nmb) const
  {
    if(existe(nmb))
      return &(coefs.find(nmb)->second);
    else
      {
	std::cerr << "cmb_acc::CombinationFactorsMap::getPtrCoefs; no se encontraron los coeficientes de nombre: '"
                  << nmb << "' se devuelve nullptr." << std::endl;
        return nullptr;
      }
  }

//! @brief Constructor por defecto.
cmb_acc::CombinationFactorsMap::CombinationFactorsMap(void)
  : EntCmd(), coefs() {}

//! @brief Crea coeficientes con el nombre que se le pasa como parámetro.
cmb_acc::CombinationFactors *cmb_acc::CombinationFactorsMap::crea_coefs(const std::string &nmb)
  {
    CombinationFactors *retval= nullptr;
    if(existe(nmb))
      retval= &(coefs.find(nmb)->second);
    else //los coeficientes son nuevos.
      {
        CombinationFactors tmp;
        coefs[nmb]= tmp;
        retval= getPtrCoefs(nmb);
      }
    return retval;
  }

//! @brief Inserts the coefficients.
void cmb_acc::CombinationFactorsMap::insert(const std::string &nmb,const CombinationFactors &c)
  { coefs[nmb]= c; }

//! @brief Return el número de coeficientes definidos.
size_t cmb_acc::CombinationFactorsMap::size(void) const
 { return coefs.size(); }

