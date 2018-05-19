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
//python_interface.cc

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/docstring_options.hpp>
#include "xc_utils/src/loadCombinations/factors/PartialSafetyFactors.h"
#include "xc_utils/src/loadCombinations/factors/PartialSafetyFactorsMap.h"
#include "xc_utils/src/loadCombinations/factors/CombinationFactors.h"
#include "xc_utils/src/loadCombinations/actions/Action.h"
#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"
#include "xc_utils/src/loadCombinations/actions/ActionsFamily.h"
#include "xc_utils/src/loadCombinations/actions/ActionContainer.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinations.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationGenerator.h"

BOOST_PYTHON_MODULE(loadCombinations)
  {
    using namespace boost::python;
    using namespace cmb_acc;
    docstring_options doc_options;


    class_<std::vector<double> >("StdVectorDouble")
        .def(vector_indexing_suite<std::vector<double> >() );

#include "factors/python_interface.tcc"
#include "actions/python_interface.tcc"
#include "comb_analysis/python_interface.tcc"
  }

