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
//FactorsMap.h
//Contenedor de coeficientes de simultaneidad de acciones.

#ifndef FACTORSMAP_H
#define FACTORSMAP_H

#include "xc_utils/src/nucleo/EntCmd.h"
#include <map>


namespace cmb_acc {

class LoadCombinationVector;

//! @ingroup CMBACC
//
//! @brief Contenedor de coeficientes de simultaneidad de acciones.
template <class Factors>
class FactorsMap: public EntCmd, public std::map<std::string,Factors>
  {
  private:
    static Factors default_factors; //!< Default values (all =1.0).
    bool exists(const std::string &nmb) const;
    Factors *getPtrCoefs(const std::string &nmb);
    Factors *crea_coefs(const std::string &nmb);
  public:
    FactorsMap(void);
    static inline const Factors &getCoefsPorDefecto(void)
      { return default_factors; }
    const Factors *getPtrCoefs(const std::string &nmb) const;
    const Factors &BuscaCoefs(const std::string &nmb) const;
    void insert(const std::string &,const Factors &);
  };

template <class Factors>
Factors FactorsMap<Factors>::default_factors;

//! @brief Return verdadero si la familia existe.
template <class Factors>
bool FactorsMap<Factors>::exists(const std::string &nmb) const
  { return (this->find(nmb)!=this->end()); }
 
//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
template <class Factors>
Factors *FactorsMap<Factors>::getPtrCoefs(const std::string &nmb)
  {
    if(this->exists(nmb))
      return &((*this)[nmb]);
    else
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
	          << "; factors with name: '"
                  << nmb << "' not found." << std::endl;
        return nullptr;
      }
  }

//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
template <class Factors>
const Factors &FactorsMap<Factors>::BuscaCoefs(const std::string &nmb) const
  {
    if(this->exists(nmb))
      return this->find(nmb)->second;
    else
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; factors with name: '"
                  << nmb << "' not found." << std::endl;
        return default_factors;
      }
  }

//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
template <class Factors>
const Factors *FactorsMap<Factors>::getPtrCoefs(const std::string &nmb) const
  {
    if(this->exists(nmb))
      return &(this->find(nmb)->second);
    else
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; factors with name: '"
                  << nmb << "' not found." << std::endl;
        return nullptr;
      }
  }

//! @brief Constructor por defecto.
template <class Factors>
FactorsMap<Factors>::FactorsMap(void)
  : EntCmd() {}

//! @brief Crea coeficientes con el nombre que se le pasa como parámetro.
template <class Factors>
Factors *FactorsMap<Factors>::crea_coefs(const std::string &nmb)
  {
    Factors *retval= nullptr;
    if(this->exists(nmb))
      retval= &(this->find(nmb)->second);
    else //los coeficientes son nuevos.
      {
        Factors tmp;
        (*this)[nmb]= tmp;
        retval= getPtrCoefs(nmb);
      }
    return retval;
  }

//! @brief Inserts the coefficients.
template <class Factors>
void FactorsMap<Factors>::insert(const std::string &nmb,const Factors &c)
  { (*this)[nmb]= c; }

} // fin namespace cmb_acc

#endif
