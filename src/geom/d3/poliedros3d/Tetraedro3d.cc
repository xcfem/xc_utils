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
//Tetraedro3c.cc

#include "Tetraedro3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_basic/src/matrices/m_double.h"
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"

const Pos3d v1PorDefecto(1.0,0.0,0.0);
const Pos3d v2PorDefecto(0.0,1.0,0.0);
const Pos3d v3PorDefecto(0.0,0.0,1.0);
const Pos3d v4PorDefecto(0.0,0.0,0.0);

//! @brief Constructor por defecto.
Tetraedro3d::Tetraedro3d(void)
  : Poliedro3d(v1PorDefecto,v2PorDefecto,v3PorDefecto,v4PorDefecto) {}

//! @brief Constructor.
Tetraedro3d::Tetraedro3d(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3)
  : Poliedro3d(p0,p1,p2,p3) {}

//! @brief Constructor.
Tetraedro3d::Tetraedro3d(const SemiEspacio3d &se0, const SemiEspacio3d &se1,const SemiEspacio3d &se2, const SemiEspacio3d &se3)
  : Poliedro3d(se0,se1,se2,se3) {}

//! @brief Interpreta comandos del objeto.
bool Tetraedro3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string str_msg= "(Tetraedro3d) Procesando comando: "+cmd;
    if(verborrea>2)
      std::clog << str_msg << std::endl;
    if(cmd == "semiespacios")
      {
        semiespacios(status.GetBloque(),true);
        if(GetNumVertices()!=4)
	  std::cerr << str_msg
                    << ". No se generó un tetraedro." << std::endl;
        return true;
      }
    else
      return Poliedro3d::procesa_comando(status);
  }

//! @brief Devuelve el volumen con signo del tetraedro.
GEOM_FT Tetraedro3d::getVolumenSigno(void) const
  {
    m_double tmp(4,4);
    const GeomObj::list_Pos3d vertices= getVertices();
    assert(vertices.size()==4);
    const Pos3d &p1= vertices[0];
    tmp(1,1)= 1; tmp(1,2)= p1.x(); tmp(1,3)= p1.y(); tmp(1,4)= p1.z();
    const Pos3d &p2= vertices[1];
    tmp(2,1)= 1; tmp(2,2)= p2.x(); tmp(2,3)= p2.y(); tmp(2,4)= p2.z();
    const Pos3d &p3= vertices[2];
    tmp(3,1)= 1; tmp(3,2)= p3.x(); tmp(3,3)= p3.y(); tmp(3,4)= p3.z();
    const Pos3d &p4= vertices[3];
    tmp(4,1)= 1; tmp(4,2)= p4.x(); tmp(4,3)= p4.y(); tmp(4,4)= p4.z();
    GEOM_FT retval= tmp.GetDet()/6;
    return retval;
  }

//! @brief Devuelve el volumen del tetraedro.
GEOM_FT Tetraedro3d::Volumen(void) const
  { return std::abs(getVolumenSigno()); }


