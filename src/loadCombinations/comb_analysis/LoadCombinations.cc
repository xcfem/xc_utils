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
//LoadCombinations.cc

#include "LoadCombinations.h"
#include "xc_utils/src/loadCombinations/actions/ActionContainer.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor por defecto.
cmb_acc::LoadCombinations::LoadCombinations(void)
 {}

//! @brief Constructor.
cmb_acc::LoadCombinations::LoadCombinations(const ActionContainer &acc)
  : comb_uls_transient(acc.GetPersistentesOTransit()), comb_uls_accid(acc.GetAccidentales()),
    comb_uls_sism(acc.GetSismicas()), comb_sls_poco_frec(acc.GetPocoFrecuentes()),
    comb_sls_frec(acc.GetFrecuentes()), comb_sls_cuasi_perm(acc.GetCuasiPermanentes())
  {}


//! @brief Concatena las combinaciones de ambos objetos.
void cmb_acc::LoadCombinations::Concat(const LoadCombinations &otras)
  {
    comb_uls_transient= LoadCombinationVector::Concat(comb_uls_transient,otras.comb_uls_transient,0.0);
    comb_uls_accid= LoadCombinationVector::Concat(comb_uls_accid,otras.comb_uls_accid,0.0);
    comb_uls_sism= LoadCombinationVector::Concat(comb_uls_sism,otras.comb_uls_sism,0.0);
    comb_sls_poco_frec= LoadCombinationVector::Concat(comb_sls_poco_frec,otras.comb_sls_poco_frec,0.0);
    comb_sls_frec= LoadCombinationVector::Concat(comb_sls_frec,otras.comb_sls_frec,0.0);
    comb_sls_cuasi_perm= LoadCombinationVector::Concat(comb_sls_cuasi_perm,otras.comb_sls_cuasi_perm,0.0);
  }
