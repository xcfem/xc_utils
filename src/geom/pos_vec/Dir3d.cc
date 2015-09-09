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
//Dir3d.cc

#include "Dir3d.h"
#include "Vector3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/geom/matriz_FT.h"

Dir3d::Dir3d(GEOM_FT x,GEOM_FT y,GEOM_FT z)
  : cgd(x,y,z) {}

Dir3d::Dir3d(const Vector3d &v)
  : cgd(v.ToCGAL()) {}
matriz_FT Dir3d::GetMatriz(void) const
  {
    matriz_FT retval(3,1,0.0);
    retval(1)= cgd.dx(); retval(2)= cgd.dy(); retval(3)= cgd.dz();
    return retval;
  }
Vector3d Dir3d::GetVector(void) const
  { return Vector3d(cgd.vector()); }

std::ostream &operator<<(std::ostream &stream,const Dir3d &n)
  {
    stream << "[[" << n.dx() << "][" << n.dy() << "]["
           << n.dz() << "]]";
    return stream;
  }
