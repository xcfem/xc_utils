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
//Combinaciones.h

#ifndef COMBINACIONES_H
#define COMBINACIONES_H

#include "VectorCombinaciones.h"

namespace cmb_acc{
class AccionesClasificadas;
class MapPondAcciones;

//! @ingroup CMBACC
//
//! @brief Almacena todas las combinaciones que deben formarse para las acciones.
class Combinaciones: public EntCmd
  {
  private:
    //Combinaciones para estados límite últimos.
    VectorCombinaciones comb_uls_transient; //!< Combinaciones para estados límite últimos en situaciones persistentes o transitorias.
    VectorCombinaciones comb_uls_accid; //!< Combinaciones para estados límite últimos en situaciones accidentales.
    VectorCombinaciones comb_uls_sism; //!< Combinaciones para estados límite últimos en situaciones sísmicas.

    //Combinaciones para estados límite de servicio.
    VectorCombinaciones comb_sls_poco_frec; //!< Combinaciones para estados límite de servicio en situaciones poco frecuentes.
    VectorCombinaciones comb_sls_frec; //!< Combinaciones para estados límite de servicio en situaciones frecuentes.
    VectorCombinaciones comb_sls_cuasi_perm; //!< Combinaciones para estados límite de servicio en situaciones cuasi - permanentes.

  protected:
    virtual bool procesa_comando(CmdStatus &status);
  public:
    Combinaciones(void);
    Combinaciones(const AccionesClasificadas &acc);
    inline virtual ~Combinaciones(void) {}
    void Concat(const Combinaciones &otras);

    inline VectorCombinaciones getULSTransientCombinations(void)
      { return comb_uls_transient;}
    inline VectorCombinaciones getULSAccidentalCombinations(void)
      { return comb_uls_accid; }
    inline VectorCombinaciones getULSSeismicCombinations(void)
      { return comb_uls_sism; }

    inline VectorCombinaciones getSLSCharacteristicCombinations(void)
      { return comb_sls_poco_frec; }
    inline VectorCombinaciones getSLSFrequentCombinations(void)
      { return comb_sls_frec; }
    inline VectorCombinaciones getSLSQuasiPermanentCombinations(void)
      { return comb_sls_cuasi_perm; }

    virtual any_const_ptr GetProp(const std::string &cod) const;
  };
} //fin namespace nmb_acc.


#endif
