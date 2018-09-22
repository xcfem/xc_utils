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

#include "xc_utils/src/kernel/CommandEntity.h"
#include <map>


namespace cmb_acc {

class LoadCombinationVector;

//! @ingroup CMBACC
//
//! @brief Contenedor de coeficientes de simultaneidad de acciones.
template <class Factors>
class FactorsMap: public CommandEntity, public std::map<std::string,Factors>
  {
  public:
    typedef typename std::map<std::string,Factors>::const_iterator const_iterator;
    typedef typename std::map<std::string,Factors>::iterator iterator;
  private:
    static Factors default_factors; //!< Default values (all =1.0).
    bool exists(const std::string &) const;
    Factors *getPtrCoefs(const std::string &);
    Factors *crea_coefs(const std::string &);
    void print_err_not_found(const std::string &, const std::string &) const;
  public:
    FactorsMap(void);
    const Factors *getPtrCoefs(const std::string &) const;
    const Factors &BuscaCoefs(const std::string &) const;
    void insert(const std::string &,const Factors &);
    std::deque<std::string> getNames(void) const;
  };

template <class Factors>
Factors FactorsMap<Factors>::default_factors;

//! @brief Return true if the name exists.
template <class Factors>
bool FactorsMap<Factors>::exists(const std::string &name) const
  { return (this->find(name)!=this->end()); }

//! @brief Error message when name not found.
template <class Factors>
void FactorsMap<Factors>::print_err_not_found(const std::string &functionName, const std::string &name) const
   {
      std::cerr << getClassName() << "::" << functionName
		<< "; factors with name: '"
		<< name << "' not found." << std::endl
		<< " candidates are: ";
      const std::deque<std::string> candidates= this->getNames();
      if(!candidates.empty())
	{
	  std::deque<std::string>::const_iterator i= candidates.begin();
	  std::cerr << *i;
	  i++;
          for(;i!=candidates.end();i++)
	    std::cerr << ", " << *i;
	  std::cerr << std::endl;
	}
   }
   
//! @brief Return the names of the factor families.
template <class Factors>
std::deque<std::string> FactorsMap<Factors>::getNames(void) const
  {
    std::deque<std::string> retval;
    for(const_iterator i= this->begin();i!= this->end();i++)
      retval.push_back(i->first);
    return retval;
  }

 
//! @brief Return a pointer to the factors named with the string
//! argument.
template <class Factors>
Factors *FactorsMap<Factors>::getPtrCoefs(const std::string &name)
  {
    Factors *retval= nullptr;
    if(this->exists(name))
      retval= &((*this)[name]);
    else
      this->print_err_not_found(__FUNCTION__,name);
    return retval;
  }

//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
template <class Factors>
const Factors &FactorsMap<Factors>::BuscaCoefs(const std::string &name) const
  {
    if(this->exists(name))
      return this->find(name)->second;
    else
      {
        this->print_err_not_found(__FUNCTION__,name);
	return default_factors;
      }
  }

//! @brief Return un apuntador a los coeficientes cuyo nombre se pasa como parámetro.
template <class Factors>
const Factors *FactorsMap<Factors>::getPtrCoefs(const std::string &name) const
  {
    const Factors *retval= nullptr;
    if(this->exists(name))
      retval= &(this->find(name)->second);
    else
      this->print_err_not_found(__FUNCTION__,name);
    return retval;
  }

//! @brief Default constructor.
template <class Factors>
FactorsMap<Factors>::FactorsMap(void)
  : CommandEntity() {}

//! @brief Crea coeficientes con el nombre que se le pasa como parámetro.
template <class Factors>
Factors *FactorsMap<Factors>::crea_coefs(const std::string &name)
  {
    Factors *retval= nullptr;
    if(this->exists(name))
      retval= &(this->find(name)->second);
    else //los coeficientes son nuevos.
      {
        Factors tmp;
        (*this)[name]= tmp;
        retval= getPtrCoefs(name);
      }
    return retval;
  }

//! @brief Inserts the coefficients.
template <class Factors>
void FactorsMap<Factors>::insert(const std::string &name,const Factors &c)
  { (*this)[name]= c; }

} // fin namespace cmb_acc

#endif
