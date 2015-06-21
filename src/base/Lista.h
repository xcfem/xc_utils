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
//Lista.h

#ifndef LISTA_H
#define LISTA_H

#include "EntWOwner.h"

class ExprAlgebra;
class Vector2d;

//XXX Quizá fuera bueno que esta clase compartiera con Mapa
//un ancestro "contenedor" común.

//! @ingroup BASE
//
//! @brief Lista de objetos.
class Lista: public EntWOwner
  {
  public:
    typedef std::deque<boost::any> dq_objetos; //!< Tipo contenedor de objetos.
    typedef dq_objetos::iterator iterator;
    typedef dq_objetos::const_iterator const_iterator;
  private:
    dq_objetos lista;
    any_const_ptr get_prop_miembro(const std::string &,const boost::any &) const;
  protected:
    virtual bool procesa_comando(CmdStatus &status);
    void inserta_valores(const std::string &valor,bool asigna);
    void to_num(void);
    template <class T>
    std::list<T> &castMembers(void);
    void particiona(void);
    void recorta(const Poligono2d &plg);
    boost::any &operator[](const size_t &i);
  public:
    Lista(EntCmd *owr,const std::string &str= "");
    void clear(void);
    void clearAll(void);

    size_t size(void) const;
    iterator begin(void);
    iterator end(void);
    const_iterator begin(void) const;
    const_iterator end(void) const;
    bool empty(void) const;

    boost::any &sumatorio(void) const;
    boost::any &max(void) const;
    boost::any &min(void) const;

    void fromString(const std::string &);
    void Inserta(const int &);
    void Inserta(const long int &);
    void Inserta(const double &);
    void Inserta(const std::string &);
    void Inserta(const ExprAlgebra &);
    void Inserta(const Vector2d &);
    void GenListaEnteros(const int &primero= 1,const int &ultimo= 10,const int &step= 1);
    template <class InputIterator>
    void Inserta(InputIterator begin,InputIterator end);
    std::string sqlValues(void) const;
    void Print(std::ostream &os) const;
    any_const_ptr GetProp(const std::string &cod) const;
    const boost::any &operator[](const size_t &i) const;
  };

std::ostream &operator<<(std::ostream &os,const Lista &l);

template <class InputIterator>
void Lista::Inserta(InputIterator begin,InputIterator end)
  {
    for(InputIterator i= begin;i!=end;i++)
      Inserta(*i);
  }

//! @brief Devuelve una lista con los polígonos que contenga ésta.
template <class T>
std::list<T> &Lista::castMembers(void)
  {
    static std::list<T> retval;
    retval.clear();
    for(dq_objetos::iterator i= lista.begin();i!= lista.end();i++)
      {
        EntCmd *ptr= entcmd_cast(*i);
        if(ptr)
          {
            T *plg= dynamic_cast<T *>(ptr);
            if(plg)
              retval.push_back(*plg);
            else
	      std::cerr << "Lista::castMembers; la lista es heterogénea, se borrarán algunos objetos." << std::endl;
          }
        else
	  std::cerr << "Lista::castMembers; la lista es heterogénea, se borrarán algunos objetos." << std::endl;
      }
    return retval;
  }

#endif
