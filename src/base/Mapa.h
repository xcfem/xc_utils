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
//Mapa.h

#ifndef MAPA_H
#define MAPA_H

#include "EntWOwner.h"
#include <map>
#include "boost/any.hpp"

class ExprAlgebra;
class Vector2d;

//XXX Quizá fuera bueno que esta clase compartiera con Lista
//un ancestro "contenedor" común.

//! @ingroup BASE
//
//! @brief Mapa de objetos.
class Mapa: public EntWOwner
  {
  public:
    typedef std::map<std::string,boost::any> map_objetos; //!< Tipo contenedor de objetos.
    typedef map_objetos::iterator iterator;
    typedef map_objetos::const_iterator const_iterator;
  private:
    map_objetos mapa;
    any_const_ptr get_prop_miembro(const std::string &,const boost::any &) const;
  protected:
    virtual bool procesa_comando(CmdStatus &status);
    template <class T>
    map_objetos &castMembers(void);
    boost::any &operator[](const std::string &);
  public:
    Mapa(EntCmd *owr);
    void clear(void);
    void clearAll(void);

    size_t size(void) const;
    iterator begin(void);
    iterator end(void);
    const_iterator begin(void) const;
    const_iterator end(void) const;
    bool empty(void) const;

    void Print(std::ostream &os) const;
    any_const_ptr GetProp(const std::string &cod) const;
    const boost::any &operator[](const std::string &) const;
  };

std::ostream &operator<<(std::ostream &os,const Mapa &l);

//! @brief Devuelve un mapa con los objetos de clase T que contenga éste.
template <class T>
Mapa::map_objetos &Mapa::castMembers(void)
  {
    static map_objetos retval;
    retval.clear();
    for(iterator i= begin();i!= end();i++)
      {
        EntCmd *ptr= entcmd_cast((*i).second);
        if(ptr)
          {
            T *plg= dynamic_cast<T *>(ptr);
            if(plg)
              retval.insert((*i).first,*plg);
            else
	      std::cerr << "Mapa::castMembers; el mapa es heterogéneo, se borrarán algunos objetos." << std::endl;
          }
        else
	  std::cerr << "Mapa::castMembers; el mapa es heterogéneo, se borrarán algunos objetos." << std::endl;
      }
    return retval;
  }

#endif
