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
//EntPropSorter.h

#include "EntPropSorter.h"
#include "EntProp.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/nucleo/aux_any.h"

EntPropSorter::EntPropSorter(const std::string &c)
  : cod(c) {}

bool EntPropSorter::menor(const EntProp &a,const EntProp &b) const
  {
    const boost::any prpA= a.interpretaAny(cod);
    const boost::any prpB= b.interpretaAny(cod);
    return convert_to_bool(menor_boost_any(prpA,prpB));
  }

bool EntPropSorter::menor(const EntProp *a,const EntProp *b) const
  {
    bool retval= false;
    if(a && b)
      retval= menor(*a,*b);
    else
      std::cerr << "EntPropSorter::menor, se pasó un puntero nulo." << std::endl;
    return retval;
  }

bool EntPropSorter::mayor(const EntProp &a,const EntProp &b) const
  {
    const boost::any prpA= convert_to_boost_any(a.GetProp(cod));
    const boost::any prpB= convert_to_boost_any(b.GetProp(cod));
    return convert_to_bool(mayor_boost_any(prpA,prpB));
  }

bool EntPropSorter::mayor(const EntProp *a,const EntProp *b) const
  {
    bool retval= false;
    if(a && b)
      retval= mayor(*a,*b);
    else
      std::cerr << "EntPropSorter::mayor, se pasó un puntero nulo." << std::endl;
    return retval;
  }
