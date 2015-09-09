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
//Variaciones.hxx
//Conjunto de las posibles variaciones de dos elementos
//(gamma_f_fav y gamma_f_desfav) tomados de n en n.

#ifndef VARIACIONES_HXX
#define VARIACIONES_HXX

#include "Variacion.h"

namespace cmb_acc{

class ListaVRAccion;

//! @ingroup CMBACC
//
//! @brief Conjunto de las posibles variaciones de dos elementos (gamma_f_fav y gamma_f_desfav) tomados de n en n.
class Variaciones: public std::vector<Variacion>
  {
    void print(std::ostream &os) const;
    static Variaciones primera_combinacion(const Variacion &v);
    static Variaciones prod_cartesiano(const Variaciones &a,const Variaciones &b,const ListaVRAccion &lvr);
    static Variaciones n_esima_combinacion(const Variacion &v,const int &d,const ListaVRAccion &lvr);
  public:
    Variaciones(const size_t &sz=0,const Variacion &v=Variacion());
    static Variaciones Calcula(const Variacion &v,const int &d,const ListaVRAccion &lvr);
    friend std::ostream &operator<<(std::ostream &os,const Variaciones &vs);
  };

    std::ostream &operator<<(std::ostream &os,const Variaciones &vs);
} //fin namespace nmb_acc.

#endif
