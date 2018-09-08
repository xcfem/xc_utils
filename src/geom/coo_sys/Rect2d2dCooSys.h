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
//Rect2d2dCooSys.h

#ifndef RECT_2D2D_COO_SYS_H
#define RECT_2D2D_COO_SYS_H

#include "Xd2dCooSys.h"


//! @ingroup CooSys
//
//! @brief Sistema de coordenadas rectangular de 2 dimensiones
//! definido en un espacio de dos dimensiones.
class Rect2d2dCooSys: public Xd2dCooSys
  {
  public:
    typedef Vector2d VLocal; //!< Dimension of the vector in local coordinates.
    typedef Pos2d PLocal; //!< Dimension of the point in local coordinates.


    Rect2d2dCooSys(void);
    Rect2d2dCooSys(const Pos2d &p1,const Pos2d &p2);
    Rect2d2dCooSys(const VGlobal &vX);
    virtual CooSys *Copia(void) const;

    //Acceso a miembros.
    VGlobal GetI(void) const;
    VGlobal GetJ(void) const;
    void PutI(const VGlobal &);
    void PutJ(const VGlobal &);

    //Conversión vectores.
    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;

    virtual ~Rect2d2dCooSys(void) {}
  };

#endif
