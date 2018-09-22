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
//LoadCombinations.h

#ifndef LOADCOMBINATIONS_H
#define LOADCOMBINATIONS_H

#include "LoadCombinationVector.h"

namespace cmb_acc{
class ActionContainer;
class ActionWeightingMap;

//! @ingroup CMBACC
//
//! @brief Almacena todas las Load Combinations que deben formarse para las acciones.
class LoadCombinations: public CommandEntity
  {
  private:
    //LoadCombinations para estados límite últimos.
    LoadCombinationVector comb_uls_transient; //!< LoadCombinations para estados límite últimos en situaciones persistentes o transitorias.
    LoadCombinationVector comb_uls_accid; //!< LoadCombinations para estados límite últimos en situaciones accidentales.
    LoadCombinationVector comb_uls_sism; //!< LoadCombinations para estados límite últimos en situaciones sísmicas.

    //LoadCombinations para estados límite de servicio.
    LoadCombinationVector comb_sls_poco_frec; //!< LoadCombinations para estados límite de servicio en situaciones poco frecuentes.
    LoadCombinationVector comb_sls_frec; //!< LoadCombinations para estados límite de servicio en situaciones frecuentes.
    LoadCombinationVector comb_sls_cuasi_perm; //!< LoadCombinations para estados límite de servicio en situaciones cuasi - permanentes.

  public:
    LoadCombinations(void);
    LoadCombinations(const ActionContainer &acc);
    inline virtual ~LoadCombinations(void) {}
    void Concat(const LoadCombinations &otras);

    inline LoadCombinationVector getULSTransientCombinations(void)
      { return comb_uls_transient;}
    inline LoadCombinationVector getULSAccidentalCombinations(void)
      { return comb_uls_accid; }
    inline LoadCombinationVector getULSSeismicCombinations(void)
      { return comb_uls_sism; }

    inline LoadCombinationVector getSLSCharacteristicCombinations(void)
      { return comb_sls_poco_frec; }
    inline LoadCombinationVector getSLSFrequentCombinations(void)
      { return comb_sls_frec; }
    inline LoadCombinationVector getSLSQuasiPermanentCombinations(void)
      { return comb_sls_cuasi_perm; }


  };
} //fin namespace nmb_acc.


#endif
