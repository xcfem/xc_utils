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
//ListaVRAccion.hxx
//Conjunto de acciones.

#ifndef LISTAVRACCION_HXX
#define LISTAVRACCION_HXX

#include "xc_utils/src/nucleo/EntCmd.h"
#include <deque>
#include "VRAccion.h"

namespace cmb_acc{
class Variacion;
class MapCoefsPsi;
class FamiliaAcciones;

//! @ingroup CMBACC
//
//! @brief Lista de valores representativos de las acciones (objetos VRAccion).
class ListaVRAccion: public std::deque<VRAccion>, public EntCmd
  {
    friend class Variacion;
    friend class FamiliaAcciones;

    VRAccion &push_back(const VRAccion &a);

  protected:
    void for_each(CmdStatus &,const std::string &);
    virtual bool procesa_comando(CmdStatus &status);
  public:
    //! @brief Devuelve el valor de la acción de índice i
    inline Accion GetValor(const size_t &i,short int r) const
      { return (*this)[i].Valor(r); }
    VRAccion &inserta(const Accion &,const std::string &);
    Accion FormaProdEscalar(const Variacion &v,short int r,const int &d=-1,const short int &rr=-1) const;
    const MapCoefsPsi *getPtrCoefsPsi(void) const;
    void Print(std::ostream &os) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

std::ostream &operator<<(std::ostream &os,const ListaVRAccion &vs);

} //fin namespace nmb_acc.

#endif
