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
//FuncPorPuntosR_R.h

#ifndef FUNCPORPUNTOSR_R_H
#define FUNCPORPUNTOSR_R_H

#include "FuncPorPuntosR_T.h"
#include <deque>

typedef std::deque<double> dq_double;

//! @brief función de R en R definida por puntos.
//!
//! Función que a cada punto x de la recta real le asigna un
//! real. La correspondencia se define por puntos,
//! esto es, por pares (x1,y1), (x2,y2), ...
class FuncPorPuntosR_R: public FuncPorPuntosR_T<double>
  {
  public:
    FuncPorPuntosR_R::const_iterator PosMax(void) const;
    FuncPorPuntosR_R &operator=(const FuncPorPuntosR_R &);
    FuncPorPuntosR_R &operator=(const double &);
    //! @brief Devuelve el valor máximo de las ordenadas definidas.
    double Max(void) const
      { return (*PosMax()).second; }
    //! @brief Devuelve la abcisa correspondiente al valor máximo de las ordenadas definidas.
    double AbcisaMax(void) const
      { return (*PosMax()).first; }
    FuncPorPuntosR_R::const_iterator PosMin(void) const;
    //! @brief Devuelve el valor mínimo de las ordenadas definidas.
    double Min(void) const
      { return (*PosMin()).second; }
    //! @brief Devuelve la abcisa correspondiente al valor mínimo de las ordenadas definidas.
    double AbcisaMin(void) const
      { return (*PosMin()).first; }
    double Area(void) const;
    double firstX(void) const;
    double firstY(void) const;
    double lastX(void) const;
    double lastY(void) const;
    dq_double Dominio(void) const;
    dq_double Abcisas(void) const;
    dq_double Ordenadas(void) const;
    dq_double Ceros(void) const;

    FuncPorPuntosR_R sub(const double &x0,const double &x1) const;
    FuncPorPuntosR_R getNeg(void) const;
    FuncPorPuntosR_R &Neg(void);
    FuncPorPuntosR_R &operator+=(const double &);
    FuncPorPuntosR_R &operator+=(const FuncPorPuntosR_R &);
    FuncPorPuntosR_R &operator-=(const double &);
    FuncPorPuntosR_R &operator-=(const FuncPorPuntosR_R &);
    FuncPorPuntosR_R &operator*=(const double &);
    FuncPorPuntosR_R &operator*=(const FuncPorPuntosR_R &);
    FuncPorPuntosR_R &operator/=(const double &);
    FuncPorPuntosR_R &operator/=(const FuncPorPuntosR_R &);
    FuncPorPuntosR_R integra(const double &x0,const double &x1,const double &delta= -1.0) const;

  };

FuncPorPuntosR_R asigna(const FuncPorPuntosR_R &,const double &);
FuncPorPuntosR_R operator+(const FuncPorPuntosR_R &,const double &);
FuncPorPuntosR_R operator+(const FuncPorPuntosR_R &,const FuncPorPuntosR_R &);
inline FuncPorPuntosR_R operator+(const double &c,const FuncPorPuntosR_R &f)
  { return f+c;}
inline FuncPorPuntosR_R operator-(const FuncPorPuntosR_R &f,const double &c)
  { return f+(-c); }
inline FuncPorPuntosR_R operator-(const double &c,const FuncPorPuntosR_R &f)
  { return c+f.getNeg();}
FuncPorPuntosR_R operator-(const FuncPorPuntosR_R &,const FuncPorPuntosR_R &);
FuncPorPuntosR_R operator*(const double &,const FuncPorPuntosR_R &);
inline FuncPorPuntosR_R operator*(const FuncPorPuntosR_R &f,const double &c)
  { return c*f; }
FuncPorPuntosR_R operator*(const FuncPorPuntosR_R &,const FuncPorPuntosR_R &);
inline FuncPorPuntosR_R operator/(const FuncPorPuntosR_R &f,const double &c)
  { return (1.0/c)*f; }
FuncPorPuntosR_R operator/(const FuncPorPuntosR_R &,const FuncPorPuntosR_R &);

#endif
