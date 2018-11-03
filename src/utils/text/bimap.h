//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//bimap.h

#ifndef BIMAP_H
#define BIMAP_H

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <string>

/* tags for accessing both sides of a bidirectional map */

struct from{};
struct to{};

/* The class template bidirectional_map wraps the specification
 * of a bidirectional map based on multi_index_container.
 */

template<typename FromType,typename ToType>
struct bidirectional_map
  {
    typedef std::pair<FromType,ToType> value_type;


    /* A bidirectional map can be simulated as a multi_index_container
     * of pairs of (FromType,ToType) with two unique indices, one
     * for each member of the pair.
     */

    typedef boost::multi_index_container< value_type,
      boost::multi_index::indexed_by<
      boost::multi_index::ordered_unique<
        boost::multi_index::tag<from>,boost::multi_index::member<value_type,FromType,&value_type::first> >,
      boost::multi_index::ordered_unique<
        boost::multi_index::tag<to>,  boost::multi_index::member<value_type,ToType,&value_type::second> >
    >
    > type;
  };

#endif


