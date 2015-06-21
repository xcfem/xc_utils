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
//GeneradorCombinaciones.h

#ifndef GENERADORCOMBINACIONES_H
#define GENERADORCOMBINACIONES_H

#include "MapPondAcciones.h"

namespace cmb_acc{

class Combinaciones;

//! @ingroup CMBACC
//
//! @brief Objeto encargado de generar y gestionar las combinaciones.
class GeneradorCombinaciones: public EntCmd
  {
  private:
    MapPondAcciones pond_acciones;
    Combinaciones *combinaciones;

  protected:
    virtual bool procesa_comando(CmdStatus &status);
  public:
    GeneradorCombinaciones(EntCmd *owr= NULL);

    AccionesClasificadas *defPonderacion(const std::string &,const MapCoefsPsi &coefs= MapCoefsPsi());
    VRAccion &inserta(const std::string &pond,const std::string &,const Accion &,const std::string &nmb_coefs_psi="",const std::string &subfamilia= "");
    void genera(void);
    inline MapPondAcciones &getPondAcciones(void)
      { return pond_acciones; }
    inline void setPondAcciones(const MapPondAcciones &pa)
      { pond_acciones= pa; }
    inline Combinaciones *getLoadCombinations(void)
      { return combinaciones; }

    virtual any_const_ptr GetProp(const std::string &cod) const;
  };
} //fin namespace nmb_acc.


#endif
