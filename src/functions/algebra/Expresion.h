//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//Expresion.h

#ifndef EXPRESION_H
#define EXPRESION_H

#include "ExprBase.h"
#include <list>
#include "Segnal.h"
#include <iostream>

class Expresion: public ExprBase
  {
    typedef std::list<Segnal *> l_Expr;
    l_Expr lista; //!< Lista de señales.
  protected:

    void borra_lista(void);
    void update_nueva_lista(void);

    //! @brief Crea la expresión a partir del istream que se pasa como parámetro.
    virtual void Traduce(std::istream &is) = 0;
    void Traduce(const std::string &str);
  public:

    typedef l_Expr::const_iterator const_iterator_segnales;
    typedef l_Expr::iterator iterator_segnales;

    //! @brief Constructor por defecto.
    Expresion(void)
      : ExprBase(false), lista() {}
    //! @brief Constructor de copia.
    Expresion(const Expresion &otra)
      : ExprBase(otra), lista(otra.lista)
      { update_nueva_lista(); }
    //! @brief Operador de asignación. 
    Expresion &operator=(const Expresion &otra)
      {
	ExprBase::operator=(otra);
        borra_lista();
        lista=(otra.lista);
        update_nueva_lista();
        return *this;
      }
    //! @brief Operador de asignación. 
    Expresion &operator=(const std::string &str)
      {
        Traduce(str);
        return *this;
      }
    //! @brief Devuelve verdadero si la expresión está vacía. 
    bool Vacia(void) const
      { return lista.empty(); }
    //! @brief Devuelve el tamaño de la expresión. 
    bool Size(void) const
      { return lista.size(); }
    //! @brief Devuelve un iterador apuntando al principio de la lista de señales.
    Expresion::l_Expr::const_iterator Begin(void) const
      { return lista.begin(); }
    //! @brief Devuelve un iterador apuntando al final de la lista de señales.
    Expresion::l_Expr::const_iterator End(void) const
      { return lista.end(); }

    void PonerDouble(const double &);
    void PonerSegnal(const Segnal *);

    bool Inicial(void);

    friend std::ostream &operator <<(std::ostream &stream,const Expresion &expr);
    //! @brief Operador entrada.
    friend std::istream &operator >>(std::istream &is, Expresion &e)
      {
        e.Traduce(is);
        return is;
      }
    virtual ~Expresion(void);
  };

#endif













