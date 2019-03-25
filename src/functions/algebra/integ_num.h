//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.  
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//integ_num.h
//Rutinas de integración numérica.

#ifndef INTEG_NUM_H
#define INTEG_NUM_H

#include "ExprAlgebra.h"
#include <string>
#include <vector>

//! @brief Intervalo de integración en una dimensión.
class Intervalo1D
  {
    std::string nmb_var; //!< Nombre de la variable respecto a la que se integra.
    int n; //!< Número de intervalos a adoptar.
    ExprAlgebra x0; //!< Límite de integración inferior.
    ExprAlgebra x1; //!< Límite de integración superior.
  public:
    Intervalo1D(const std::string &palabra,const ExprAlgebra &a= ExprAlgebra(0.0),const ExprAlgebra &b=ExprAlgebra(1.0),const unsigned int &N=10)
      : nmb_var(palabra), n(N),x0(a),x1(b) {}
    const std::string &NmbVar(void) const
      { return nmb_var; }
    const int &N(void) const
      { return n; }
    const ExprAlgebra &LimInf(void) const
      { return x0; }
    const ExprAlgebra &LimSup(void) const
      { return x1; }
  };

ExprAlgebra integ_trapecio(const ExprAlgebra &f,const Intervalo1D &i);
ExprAlgebra integ_simpson(const ExprAlgebra &f,const Intervalo1D &i);
std::vector<ExprAlgebra> integ_simpson(const ExprAlgebra &f,const std::string &nmb_var,const std::vector<ExprAlgebra> &intervalos,const int &n= 10);


#endif

