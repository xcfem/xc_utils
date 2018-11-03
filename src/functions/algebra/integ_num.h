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

