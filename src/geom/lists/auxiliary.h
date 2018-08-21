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
//auxiliary.h
//Auxiliary functions.

#ifndef AUXILIARY_H
#define AUXILIARY_H


//! @ingroup GEOM
//
//! @brief Return el valor máximo de la coordenada de indice i.
template <class InputIterator>
inline GEOM_FT get_max_i( short unsigned int i,
                                 InputIterator first,
                                 InputIterator last)
  {
    if(first==last)
      {
	std::cerr << "get_max_i: La lista está vacía, se devuelve 0."
		  << std::endl;
        return 0.0;
      }
    register InputIterator j= first;
    register GEOM_FT mx= (*j)(i); j++;
    for(;j!=last;j++)
      mx= std::max((*j)(i),mx);
    return mx;
  }

//! @ingroup GEOM
//
//! @brief Return el valor mínimo de la coordenada de indice i.
template <class InputIterator>
inline GEOM_FT get_min_i( short unsigned int i,
                                 InputIterator first,
                                 InputIterator last)
  {
    if(first==last)
      {
        std::cerr << "get_max_i: La lista está vacía, se devuelve 0."
		  << std::endl;
        return 0.0;
      }
    register InputIterator j= first;
    register GEOM_FT mn= (*j)(i); j++;
    for(;j!=last;j++)
      mn= std::min((*j)(i),mn);
    return mn;
  }

#endif
