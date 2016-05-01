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
//Ref2d3d.h

#ifndef REF2D3D_H
#define REF2D3D_H

#include "Ref.h"
#include "../sis_coo/SisCooRect2d3d.h"
#include "../d3/GeomObj3d.h"
#include "../pos_vec/Pos3d.h"

class Recta3d;
class Dir3d;
class Plano3d;
class Vector3d;

//! @ingroup SisRef
//! 
//! @brief Sistema de referencia bidimensional definido
//! en un sistema de referencia tridimensional.
class Ref2d3d : public Ref<SisCooRect2d3d>
  {
  public:
    typedef GeomObj3d::list_Pos3d list_Pos3d;
    typedef Ref<SisCooRect2d3d> BaseRef;
  public:
    Ref2d3d(void);
    Ref2d3d(const Ref2d3d &otro);
    Ref2d3d(const Pos3d &o);
    Ref2d3d(const Pos3d &o,const Pos3d &p,const Pos3d &q);
    Ref2d3d(const Pos3d &o,const Vector3d &v);
    Ref2d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2);
    Ref2d3d &operator =(const Ref2d3d &otro);
    Vector3d GetI(void) const;
    //Devuelve el vector unitario I en el sistema global.
    Vector3d GetJ(void) const;
    //Devuelve el vector unitario J en el sistema global.
    Recta3d GetEjeX(void) const; //Devuelve la recta que define el eje x.
    Recta3d GetEjeY(void) const; //Devuelve la recta que define el eje y.
    void PuntoVector(const Pos3d &o,const Vector3d &vX);
    void DosPuntos(const Pos3d &o,const Pos3d &p1);
    //Genera el triedro trirrectángulo cuyo origen esta en el punto o
    //y cuyos ejes se orientan:
    //eje x de o a p1;
    //eje y perpendicular a x.

    Plano3d GetPlanoXY(void) const; //Devuelve el plano XY.

  };

#endif






