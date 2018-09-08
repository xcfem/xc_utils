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
//Ref2d2d.h

#ifndef REF2D2D_H
#define REF2D2D_H

#include "Ref.h"
#include "../coo_sys/Rect2d2dCooSys.h"
#include "../d2/GeomObj2d.h"
#include "../pos_vec/Pos2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Dir2d.h"

class Line2d;

//! @ingroup SisRef
//! 
//! @brief Sistema de referencia bidimensional definido
//! en un sistema de referencia bidimensional.
class Ref2d2d : public Ref<Rect2d2dCooSys>
  {
  public:
    typedef GeomObj2d::list_Pos2d list_Pos2d;
    typedef Ref<Rect2d2dCooSys> BaseRef;

  public:
    Ref2d2d(void);
    Ref2d2d(const Pos2d &o);
    Ref2d2d(const Pos2d &,const Rect2d2dCooSys &);
    Ref2d2d(const Pos2d &o,const Vector2d &vX);
    Ref2d2d(const Pos2d &o,const Dir2d &dirX);
    Ref2d2d(const Pos2d &o,const Pos2d &p);
    Vector2d GetI(void) const; //I unary vector.
    Vector2d GetJ(void) const; //J unary vector.
    Line2d getXAxis(void) const; //Return the x axis.
    Line2d getYAxis(void) const; //Return the y axis.

    virtual ~Ref2d2d(void)
      {}
  };

#endif






