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
//GeomObj.h

#ifndef GEOMOBJ_H
#define GEOMOBJ_H

#include <iostream>
#include "ProtoGeom.h"
#include "lists/PolyPos.h"

class Pos2d;
class Pos3d;
class Vector2d;
class Trf2d;
class Plotter;


//! @ingroup GEOM
//
//! @brief Clase base para las entidades geométricas.
class GeomObj: public ProtoGeom
  {
  public:
    typedef PolyPos<Pos3d> list_Pos3d;
    typedef PolyPos<Pos2d> list_Pos2d;

    GeomObj(void);
    virtual ~GeomObj(void) {}
    virtual GeomObj *clon(void) const=0;
    //! @brief Return the dimension of the object 0, 1, 2 or 3.
    virtual unsigned short int Dimension(void) const= 0;
    //! @brief Return the length of the object.
    virtual GEOM_FT getLength(void) const= 0;
    //! @brief Return the area of the object.
    virtual GEOM_FT getArea(void) const= 0;
    //! @brief Return the volume of the object.
    virtual GEOM_FT getVolume(void) const= 0;
    //! @brief Return true if the object has a center of mass.
    inline virtual bool hasCenterOfMass(void) const
      { return false;}
    GEOM_FT getCenterOfMassArea(void) const;

    virtual void Print(std::ostream &os) const= 0;
    virtual void Plot(Plotter &) const {}
  };

std::ostream &operator<<(std::ostream &, const GeomObj &);


//! @brief Return the sum of the areas.
template <class input_iterator>
GEOM_FT area(input_iterator begin,input_iterator end)
  {
    GEOM_FT retval= 0.0;
    for(input_iterator i=begin;i!=end;i++)
      retval+= i->getArea();
    return retval;
  }

//! @brief Return the sum of the volumes.
template <class input_iterator>
GEOM_FT volume(input_iterator begin,input_iterator end)
  {
    GEOM_FT retval= 0.0;
    for(input_iterator i=begin;i!=end;i++)
      retval+= i->getVolume();
    return retval;
  }

//! @brief Return the sum of the lengths.
template <class input_iterator>
GEOM_FT length(input_iterator begin,input_iterator end)
  {
    GEOM_FT retval= 0.0;
    for(input_iterator i=begin;i!=end;i++)
      retval+= i->getLength();
    return retval;
  }

//! @brief Imprime los objetos.
template <class input_iterator>
void print(std::ostream &os,input_iterator begin,input_iterator end)
  {
    if(begin!=end)
      {
        register input_iterator i= begin;
        os << *i; i++;
        for(;i!=end;i++)
          os << ", " << *i;
      }
  }
#endif
