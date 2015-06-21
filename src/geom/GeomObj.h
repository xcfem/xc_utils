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
#include "listas/PoliPos.h"

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
    typedef PoliPos<Pos3d> list_Pos3d;
    typedef PoliPos<Pos2d> list_Pos2d;

    GeomObj(void);
    virtual ~GeomObj(void) {}
    virtual GeomObj *clon(void) const=0;
    //! @brief Devuelve la dimensión del objeto 0, 1, 2 ó 3.
    virtual unsigned short int Dimension(void) const= 0;
    virtual GEOM_FT Longitud(void) const= 0;
    virtual GEOM_FT Area(void) const= 0;
    virtual GEOM_FT Volumen(void) const= 0;
    inline virtual bool TieneCdg(void) const
      //Devuelve verdadero si el objeto tiene centro de gravedad
      //Una recta o un plano no lo tienen.
      { return false;}
    GEOM_FT AreaCdg(void) const;
    virtual void SalvaCmd(std::ostream &os,const std::string &indent= "  ") const;

    virtual void Print(std::ostream &os) const= 0;
    virtual void Plot(Plotter &) const {}
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

std::ostream &operator<<(std::ostream &, const GeomObj &);


//! @brief Devuelve la suma de las areas.
template <class input_iterator>
GEOM_FT area(input_iterator begin,input_iterator end)
  {
    GEOM_FT retval= 0.0;
    for(input_iterator i=begin;i!=end;i++)
      retval+= i->Area();
    return retval;
  }

//! @brief Devuelve la suma de los volumenes.
template <class input_iterator>
GEOM_FT volumen(input_iterator begin,input_iterator end)
  {
    GEOM_FT retval= 0.0;
    for(input_iterator i=begin;i!=end;i++)
      retval+= i->Volumen();
    return retval;
  }

//! @brief Devuelve la suma de las longitudes.
template <class input_iterator>
GEOM_FT longitud(input_iterator begin,input_iterator end)
  {
    GEOM_FT retval= 0.0;
    for(input_iterator i=begin;i!=end;i++)
      retval+= i->Longitud();
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
