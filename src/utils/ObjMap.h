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
//ObjMap.h

#ifndef OBJMAP
#define OBJMAP

#include <map>
#include <string>
#include <iostream>

//! @ingroup UTILS
//
//! @brief Contenedor de objetos de la bibioteca vtk.
template <class T>
class ObjMap: private std::map<std::string,T *>
  {
  public:
    typedef std::map<std::string,T*> map_ptr;
    typedef typename map_ptr::iterator iterator;
    typedef typename map_ptr::const_iterator const_iterator;
  private:
    void clear(void);
    ObjMap(const ObjMap &);
    const ObjMap &operator=(const ObjMap &);
  protected:
    inline iterator find(const std::string &s)
      { return std::map<std::string,T *>::find(s); }
  public:

    ObjMap(void);
    void Borra(const std::string &);
    T *Inserta(const std::string &,const T &);
    T *Busca(const std::string &);
    const T *Busca(const std::string &) const;
    inline const_iterator find(const std::string &s) const
      { return std::map<std::string,T *>::find(s); }
    ~ObjMap(void);
  };

//! @brief Constructor.
template <class T>
ObjMap<T>::ObjMap(void)
  : map_ptr() {}

//! @brief Constructor de copia.
template <class T>
ObjMap<T>::ObjMap(const ObjMap &otro)
  : map_ptr()
  {
    for(const_iterator i=otro.begin();i!=otro.end();i++)
      Inserta(i->first,*(i->second));
  }

//! @brief Operador de asignación.
template <class T>
const ObjMap<T> &ObjMap<T>::operator=(const ObjMap &otro)
  {
    clear();
    for(const_iterator i=otro.begin();i!=otro.end();i++)
      Inserta(i->first,*(i->second));
    return *this;
  }

//! @brief Libera la memoria ocupada por elemento cuya clave se pasa como parámetro.
template <class T>
void ObjMap<T>::Borra(const std::string &clave)
  {
    T *previo= Busca(clave);
    if(previo) //Si existe un elemento con esta clave lo borramos.
      {
        delete previo;
        map_ptr::erase(clave);
      } 
  }

//! @brief Libera la memoria ocupada por todos los objetos del contenedor.
template <class T>
void ObjMap<T>::clear(void)
  {
    for(iterator i=ObjMap<T>::begin();i!=ObjMap<T>::end(); i++)
      {
        delete i->second;
        i->second=nullptr;
      }
    map_ptr::clear();
  }

//! @brief Devuelve un puntero al objeto cuya clave se pasa como parámetro.
template <class T>
T *ObjMap<T>::Busca(const std::string &clave)
  {
    iterator i= ObjMap<T>::find(clave);
    if(i!=ObjMap<T>::end())
      return i->second;
    else
      return nullptr;
  }

//! @brief Devuelve un puntero al objeto cuya clave se pasa como parámetro.
template <class T>
const T *ObjMap<T>::Busca(const std::string &clave) const
  {
    const_iterator i= ObjMap<T>::find(clave);
    if(i!=ObjMap<T>::end())
      return i->second;
    else
      return nullptr;
  }

//! @brief Inserta en el contenedor el objeto empleando la clave que se pasa como parámetro.
template <class T>
T *ObjMap<T>::Inserta(const std::string &clave,const T &c)
  {
    T *previo= Busca(clave);
    if(previo) //Si ya existe un elemento con esta clave lo borramos.
      {
	std::cerr << "ObjMap::Inserta; ya existía el objeto de clave: " << clave << std::endl;
        delete previo;
        map_ptr::erase(clave);
      } 
    T *retval= c.Copia();
    map_ptr::insert(make_pair(clave,retval));
    return retval;
  }

//! @brief Destructor.
template <class T>
ObjMap<T>::~ObjMap(void)
  { clear(); }

#endif
