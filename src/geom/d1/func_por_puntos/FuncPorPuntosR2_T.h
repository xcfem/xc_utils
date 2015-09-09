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
//FuncPorPuntosR2_T.h

#ifndef FUNCPORPUNTOSR2_T_H
#define FUNCPORPUNTOSR2_T_H

#include <map>
#include <iostream>
#include <xc_utils/src/geom/pos_vec/MatrizPos2d.h>
#include <xc_utils/src/geom/pos_vec/Vector2d.h>

//! @brief función de R2 en T definida por puntos.
//!
//! Función que a cada punto P del plano le asigna un
//! valor de clase T. La correspondencia se define por puntos,
//! esto es, por pares (p1,T1), (p2,T2), ...
template <class T>
class FuncPorPuntosR2_T
  {
  public:
    typedef MatrizT<T,std::vector<T> > m_valores;
  private:
    MatrizPos2d dominio; //< @brief Puntos en los que se define la función.
    m_valores valores; //< @brief Valores de la función en cada punto.
  public:
    //! Constructor.
    FuncPorPuntosR2_T(const size_t &fls=1,const size_t &cls=1)
      : dominio(fls,cls), valores(fls,cls) {}
    //! Constructor.
    FuncPorPuntosR2_T(const MatrizPos2d &dom,const T &vdef)
      : dominio(dom), valores(m_valores(dom.getNumFilas(),dom.getNumCols(),vdef)) {}
    FuncPorPuntosR2_T(const MatrizPos2d &dom,const m_valores &v);
    //! @brief Devuelve el número de filas del dominio.
    size_t GetNumFilas(void) const
      { return dominio.getNumFilas(); }
    //! @brief Devuelve el número de columnas del dominio.
    size_t GetNumCols(void) const
      { return dominio.getNumCols(); }
    //! @brief Devuelve verdadero si no tiene puntos.
    size_t empty(void) const
      { return dominio.empty(); }
    const Pos2d &Posicion(const size_t &i,const size_t &j) const;
    Pos2d &Posicion(const size_t &i,const size_t &j);
    const T &Valor(const size_t &i,const size_t &j) const;
    T &Valor(const size_t &i,const size_t &j);
  };

//! Constructor.
template <class T>
FuncPorPuntosR2_T<T>::FuncPorPuntosR2_T(const MatrizPos2d &dom,const m_valores &v)
  : dominio(dom), valores(m_valores(dom.getNumFilas(),dom.getNumCols(),T()))
  {
    if((v.getNumFilas()==dom.getNumFilas()) && (v.getNumCols()==dom.getNumCols()) )
      valores= v;
    else
      {
	std::cerr << "FuncPorPuntosR2_T<T>::Constructor: La matriz de valores"
                  << " tiene dimensiones distintas a la de puntos." << std::endl;
      }
  }

//! @brief Devuelve el punto de índices (i,j).
template <class T>
const Pos2d &FuncPorPuntosR2_T<T>::Posicion(const size_t &i,const size_t &j) const
  { return dominio(i,j); }
//! @brief Devuelve una referencia al punto de índices (i,j).
template <class T>
Pos2d &FuncPorPuntosR2_T<T>::Posicion(const size_t &i,const size_t &j)
  { return dominio(i,j); }
//! @brief Devuelve el valor correspondiente al punto de índices (i,j).
template <class T>
const T &FuncPorPuntosR2_T<T>::Valor(const size_t &i,const size_t &j) const
  { return valores(i,j); }
//! @brief Devuelve una referencia al valor correspondiente al punto de índices (i,j).
template <class T>
T &FuncPorPuntosR2_T<T>::Valor(const size_t &i,const size_t &j)
  { return valores(i,j); }
template <class T>
std::ostream &operator<<(std::ostream &os, const FuncPorPuntosR2_T<T> &m)
  {
    const size_t fls= m.GetNumFilas();
    const size_t cls= m.GetNumCols();
    for(size_t i=1;i<=fls;i++)
      for(size_t j=1;j<=cls;j++)
        os << "posición: " << m.Posicion(i,j) << " valor: " << m.Valor(i,j) << std::endl;
    return os;
  }


#endif
