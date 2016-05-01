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
//Ref1d3d.h

#ifndef REF1D3D_H
#define REF1D3D_H

#include "Ref.h"
#include "../sis_coo/SisCooRect1d3d.h"
#include "../d3/GeomObj3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Dir3d.h"

class Recta3d;

//! @ingroup SisRef
//! 
//! @brief Sistema de referencia unidimensional definido
//! en un sistema de referencia tridimensional.
class Ref1d3d : public Ref<SisCooRect1d3d>
  {
  public:
    typedef GeomObj3d::list_Pos3d list_Pos3d;
    typedef Ref<SisCooRect1d3d> BaseRef;

  public:
    Ref1d3d(void);
    Ref1d3d(const Ref1d3d &otro);
    Ref1d3d(const Pos3d &o);
    Ref1d3d(const Pos3d &o,const Vector3d &vX);
    Ref1d3d(const Pos3d &o,const Dir3d &dirX);
    Ref1d3d(const Pos3d &o,const Pos3d &p);
    Ref1d3d &operator =(const Ref1d3d &otro);

    Vector3d GetI(void) const;
    //Devuelve el vector unitario I en el sistema global.
    Recta3d GetEjeX(void) const; //Devuelve la recta que define el eje x.


    virtual ~Ref1d3d(void)
      {}
  };

#endif






