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
//FuncPorPuntosR_T.h

#ifndef FUNCPORPUNTOSR_T_H
#define FUNCPORPUNTOSR_T_H

#include <map>
#include <iostream>
#include <vector>
#include <boost/python/list.hpp>

//! @brief función de R en T definida por puntos.
//!
//! Función que a cada punto x de la recta real le asigna un
//! valor de clase T. La correspondencia se define por puntos,
//! esto es, por pares (x1,T1), (x2,T2), ...
template <class T>
class FuncPorPuntosR_T
  {
  public:
    typedef std::map<double,T> map_valores;
    typedef typename map_valores::iterator iterator;
    typedef typename map_valores::const_iterator const_iterator;
    typedef typename map_valores::const_reverse_iterator const_reverse_iterator;
  private:
    map_valores puntos;
  public:
    T Valor(const double &) const;
    std::vector<T> Valores(const std::vector<double> &) const;
    T operator()(const double &z) const
      { return Valor(z); }
    std::vector<T> operator()(const std::vector<double> &zs) const
      { return Valores(zs); }
    //! @brief Devuelve un iterador al principio de la tabla de puntos.
    const_iterator begin(void) const
      { return puntos.begin(); }
    //! @brief Devuelve un iterador inverso al final de la tabla de puntos.
    const_reverse_iterator rbegin(void) const
      { return puntos.rbegin(); }
    //! @brief Devuelve un iterador al final de la tabla de puntos.
    const_iterator end(void) const
      { return puntos.end(); }
    //! @brief Devuelve un iterador al principio de la tabla de puntos.
    const_reverse_iterator rend(void) const
      { return puntos.rend(); }
    //! @brief Devuelve el número de puntos que definen la función.
    size_t size(void) const
      { return puntos.size(); }
    //! @brief Devuelve verdadero si no tiene puntos.
    size_t empty(void) const
      { return puntos.empty(); }
    void Inserta(const double &x,const T &y);
    void clear(void)
      { puntos.clear(); }
  };

//! @brief Devuelve el valor que corresponde a la abcisa z.
template <class T>
T FuncPorPuntosR_T<T>::Valor(const double &z) const
  {
    T retval= T();
    if(puntos.empty()) return retval; //Si esta vacío devolvemos el valor por defecto.
    const_iterator j= puntos.upper_bound(z);
    if(j==begin()) //La abcisa z es menor que todas las de los puntos.
      j++;//retval= (*j).second/(*j).first*z;
    if(j==end()) //La abcisa z es mayor que todas las de los puntos.
      j--;//retval= (*j).second/(*j).first*z;
    const_iterator i= j;
    i--;
    const double x0= (*i).first;
    const T y0= (*i).second;
    const double x1= (*j).first;
    const T y1= (*j).second;
    const T a= (y1-y0)/(x1-x0);
    const T b= y1-a*x1;
    retval= a*z+b;
    return retval;
  }

//! @brief Devuelve los valores que corresponden a las abcisas z.
template <class T>
std::vector<T> FuncPorPuntosR_T<T>::Valores(const std::vector<double> &zs) const
  {
    const size_t sz= zs.size();
    std::vector<T> retval(sz);
    if(puntos.empty()) return retval; //Si esta vacío devolvemos el valor por defecto.
    for(size_t i= 0;i<sz;i++)
      retval[i]= Valor(zs[i]);
    return retval;
  }

//! @brief Inserta el par (x,y) como punto de la función.
template <class T>
void FuncPorPuntosR_T<T>::Inserta(const double &x,const T &y)
  {
    puntos[x]= y;
  }
template <class T>
std::ostream &operator<<(std::ostream &os, const FuncPorPuntosR_T<T> &lt)
  {
    if(!lt.empty())
      {
        typename FuncPorPuntosR_T<T>::const_iterator i= lt.begin();
        os << "x= " << (*i).first
           << " y= " << (*i).second;
        i++;
        for(;i!=lt.end();i++)
          os << std::endl << "x= " << (*i).first
             << " y= " << (*i).second;
      }
    return os;
  }


#endif
