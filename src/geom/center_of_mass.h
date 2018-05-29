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
//center_of_mass.h

#ifndef CENTER_OF_MASS_H
#define CENTER_OF_MASS_H

//! @ingroup GEOM
//! 
//! @brief Return the center of mass of the objects.
template<class InputIter>
const Pos2d center_of_mass(InputIter begin, InputIter end)
  {
    Pos2d retval;
    if(begin!=end)
      {
        InputIter i=begin;
        GEOM_FT area= (*i).getArea();
        Vector2d vpos= (*i).getCenterOfMass().VectorPos()*(*i).getArea();
        i++;
        for(;i!=end;i++)
          {
            area+= (*i).getArea();
            vpos= vpos + (*i).getCenterOfMass().VectorPos()*(*i).getArea();
          }
        vpos= vpos/area;
        retval= Pos2d(vpos[0],vpos[1]);
      }
    return retval;
  }


#endif
