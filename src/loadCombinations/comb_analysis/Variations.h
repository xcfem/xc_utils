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
//Variations.hxx
//Conjunto de las posibles variations de dos elementos
//(gamma_f_fav y gamma_f_desfav) tomados de n en n.

#ifndef VARIATIONS_HXX
#define VARIATIONS_HXX

#include "Variation.h"

namespace cmb_acc{

class ListaVRAccion;

//! @ingroup CMBACC
//
//! @brief Conjunto de las posibles variations de dos elementos (gamma_f_fav y gamma_f_desfav) tomados de n en n.
class Variations: public std::vector<Variation>
  {
    void print(std::ostream &os) const;
    static Variations primera_combinacion(const Variation &v);
    static Variations prod_cartesiano(const Variations &a,const Variations &b,const ListaVRAccion &lvr);
    static Variations n_esima_combinacion(const Variation &v,const int &d,const ListaVRAccion &lvr);
  public:
    Variations(const size_t &sz=0,const Variation &v=Variation());
    static Variations Calcula(const Variation &v,const int &d,const ListaVRAccion &lvr);
    friend std::ostream &operator<<(std::ostream &os,const Variations &vs);
  };

    std::ostream &operator<<(std::ostream &os,const Variations &vs);
} //fin namespace nmb_acc.

#endif
