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
#include "../sis_coo/SisCooRect2d2d.h"
#include "../d2/GeomObj2d.h"
#include "../pos_vec/Pos2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Dir2d.h"

class Recta2d;

//! @ingroup SisRef
//! 
//! @brief Sistema de referencia bidimensional definido
//! en un sistema de referencia bidimensional.
class Ref2d2d : public Ref<SisCooRect2d2d>
  {
  public:
    typedef GeomObj2d::list_Pos2d list_Pos2d;
    typedef Ref<SisCooRect2d2d> BaseRef;

  public:
    Ref2d2d(void);
    Ref2d2d(const Pos2d &o);
    Ref2d2d(const Pos2d &,const SisCooRect2d2d &);
    Ref2d2d(const Pos2d &o,const Vector2d &vX);
    Ref2d2d(const Pos2d &o,const Dir2d &dirX);
    Ref2d2d(const Pos2d &o,const Pos2d &p);
    Vector2d GetI(void) const;
    //Return el vector unitario I en el sistema global.
    Vector2d GetJ(void) const;
    //Return el vector unitario J en el sistema global.
    Recta2d GetEjeX(void) const; //Return la recta que define el x axis.
    Recta2d GetEjeY(void) const; //Return la recta que define el y axis.

    virtual ~Ref2d2d(void)
      {}
  };

#endif






