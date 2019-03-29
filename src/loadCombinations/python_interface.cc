//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//python_interface.cc

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/docstring_options.hpp>
#include "xc_utils/src/loadCombinations/factors/PartialSafetyFactors.h"
#include "xc_utils/src/loadCombinations/factors/PartialSafetyFactorsMap.h"
#include "xc_utils/src/loadCombinations/factors/CombinationFactors.h"
#include "xc_utils/src/loadCombinations/actions/Action.h"
#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"
#include "xc_utils/src/loadCombinations/actions/ActionsFamily.h"
#include "xc_utils/src/loadCombinations/actions/ActionContainer.h"
#include "xc_utils/src/loadCombinations/actions/ActionsAndFactors.h"
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

