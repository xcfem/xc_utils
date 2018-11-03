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
//op_dif.h
//Operadores diferenciales.
#ifndef OP_DIF_H
#define OP_DIF_H

#include "xc_utils/src/matrices/m_double.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/utils/misc_utils/mchne_eps.h"

inline double calcula_incremento(const double &t)
  {
    double retval(sqrt_mchne_eps_dbl); // sqrt_mchne_eps_dbl: Valor de la raiz cuadrada de
                                       //la precisión de la máquina.
    if(t != 0.0) retval*=fabs(t);
    return retval;
  }

template<class F>
inline double parcial_fd(const m_double &x,const F &f,const size_t &i)
//Return la derivada parcial de la función f
//en el punto x respecto al parámetro i empleando
//el método "forward difference" 
  {
    m_double x2(x);
    register const double temp= x2(i);
    register const double h= calcula_incremento(temp);
    x2(i)+=h;
    return (f(x2)-f(x))/h;
  }

template<class F>
inline double parcial_cdf(const m_double &x,const F &f,const size_t &i)
//Return la derivada parcial de la función f
//en el punto x respecto al parámetro i empleando
//el método "extended central difference" 
  {
    m_double x_2(x); //Punto a -2*h de x
    m_double x_1(x); //Punto a -h de x
    m_double x1(x);  //Punto a +x de x
    m_double x2(x);  //Punto a +2h de x
    register const double temp= x(i);
    register const double h= calcula_incremento(temp);
    register const double h2= 2.0*h;
    x_2(i)-=h2;
    x_1(i)-=h;
    x1(i)+=h;
    x2(i)+=h2;
    return (f(x_2)-8.0*f(x_1)+8.0*f(x1)-f(x2))/(12.0*h);
  }

template<class F>
inline m_double gradiente_cdf(const m_double &x,const F &f)
//Return el vector gradiente de f en el punto x
//empleando el método "extended central difference"
  {
    m_double g(x);
    size_t n_rows= x.getNumberOfRows();
    for(register size_t i= 1;i<=n_rows;i++)
      g(i)= parcial_cdf(x,f,i);
    return g;
  }

//! @brief Return el vector gradiente de f en el punto x
//! empleando el método "extended central difference"
//! como row vector
template<class F>
inline m_double extended_central_differece_row_gradient(const m_double &x,const F &f)
  {
    m_double g(1,x.getNumberOfRows());
    size_t n_rows= x.getNumberOfRows();
    for(register size_t i= 1;i<=n_rows;i++)
      g(1,i)= parcial_cdf(x,f,i);
    return g;
  }

//! @brief Return the jacobian vector de f en el punto x
//! using the "extended central difference" method
template<class MF>
inline m_double jacobiano_cdf(const m_double &x,const MF &mf)
  {
    size_t n_rows= mf.getNumberOfRows();
    size_t n_columns= x.getNumberOfRows();
    m_double J(n_rows,n_columns);
    for(register size_t i= 1;i<=n_rows;i++)
      {
        m_double g= extended_central_differece_row_gradient(x,mf(i));
        J.putRow(i,g);
      }
    return J;
  }

#endif
