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
//Trf.h
//Transformación afín (abstracto).

#ifndef TRF_H
#define TRF_H

#include "../tipos_cgal.h"
#include "xc_utils/src/nucleo/EntCmd.h"

class matriz_FT;


//! @ingroup GEOM
//
//! @brief Clase base para las transformaciones de coordenadas.
class Trf: public EntCmd
  {
  public:
    inline virtual ~Trf(void) {}
    virtual GEOM_FT Cartesianas(const size_t &i,const size_t &j) const= 0;
    //Return el elemento (i,j) de la matriz de transformación en cartesianas.
    //       -              -
    //       | m11  m12 m13 |
    //       | m21  m22 m23 |
    //       |   0    0  1  |
    //       -              -
    virtual GEOM_FT Homogeneas(const size_t &i,const size_t &j) const= 0;
    //Return el elemento (i,j) de la matriz de transformación en homogéneas.
    //       -              -
    //       | m11  m12 m13 |
    //       | m21  m22 m23 |
    //       |   0    0  hw |
    //       -              -
    virtual matriz_FT Cartesianas(void) const= 0;
    //Return la matriz de transformación en cartesianas.
    virtual matriz_FT Homogeneas(void) const= 0;
    //Return la matriz de transformación en homogéneas.
  };

#endif
