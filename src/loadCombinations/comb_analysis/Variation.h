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
//Variation.hxx

#ifndef VARIATION_HXX
#define VARIATION_HXX

#include <vector>
#include <iostream>

namespace cmb_acc{

class ActionRValueList;

//! @ingroup CMBACC
//
//! @brief Vector that stores the factors of the linear combination of actions.
class Variation: public std::vector<double>
  {
    void print(std::ostream &os) const;
  public:
    //! @brief Constructor.
    Variation(const size_t &sz=0,const double &valor=0.0)
      : std::vector<double>(sz,valor) {}
    static Variation concat(const Variation &a,const Variation &b);
    bool compatible(const ActionRValueList &lvr);
    friend std::ostream &operator<<(std::ostream &os,const Variation &v);
  };

std::ostream &operator<<(std::ostream &os,const Variation &v);
} //fin namespace nmb_acc.

#endif
