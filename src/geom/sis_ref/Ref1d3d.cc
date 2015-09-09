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
//Ref1d3d.cc
#include "Ref1d3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

    Ref1d3d::Ref1d3d(void): BaseRef() {}
    Ref1d3d::Ref1d3d(const Ref1d3d &otro): BaseRef(otro) {}
    Ref1d3d::Ref1d3d(const Pos3d &o) : BaseRef(o) {}
    Ref1d3d::Ref1d3d(const Pos3d &o,const Vector3d &vX): BaseRef(o,vX) {}
    Ref1d3d::Ref1d3d(const Pos3d &o,const Dir3d &dirX): BaseRef(o,dirX) {}
    Ref1d3d::Ref1d3d(const Pos3d &o,const Pos3d &p) : BaseRef(o,p) {}
    Ref1d3d &Ref1d3d::operator =(const Ref1d3d &otro)
      {
	BaseRef::operator=(otro);
        return *this;
      }

bool Ref1d3d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(Ref1d3d) Procesando comando: " << cmd << endl;
    if(status.Cmd() == "org")
      {
        org.LeeCmd(status);
        return true;
      }
    else if(status.Cmd() == "ejes")
      {
        trf.LeeCmd(status);
        return true;
      }
    else
      return BaseRef::procesa_comando(status);
  }
Vector3d Ref1d3d::GetI(void) const
//Devuelve el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
Recta3d Ref1d3d::GetEjeX(void) const
//Devuelve la recta que define el eje x.
  {
    const Pos3d dest(org+1000.0*GetI());
    return Recta3d(org,dest);
  }

