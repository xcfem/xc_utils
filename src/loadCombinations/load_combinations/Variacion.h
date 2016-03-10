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
//Variacion.hxx

#ifndef VARIACION_HXX
#define VARIACION_HXX

#include <vector>
#include <iostream>

namespace cmb_acc{

class ListaVRAccion;

//! @ingroup CMBACC
//
//! @brief Vector que almacena los coeficientes de la combinación lineal de acciones.
class Variacion: public std::vector<double>
  {
    void print(std::ostream &os) const;
  public:
    //! @brief Constructor.
    Variacion(const size_t &sz=0,const double &valor=0.0)
      : std::vector<double>(sz,valor) {}
    static Variacion concat(const Variacion &a,const Variacion &b);
    bool compatible(const ListaVRAccion &lvr);
    friend std::ostream &operator<<(std::ostream &os,const Variacion &v);
  };
} //fin namespace nmb_acc.

#endif
