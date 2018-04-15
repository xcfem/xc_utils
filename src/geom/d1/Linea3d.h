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
//Linea3d.h

#ifndef LINEA3D_H
#define LINEA3D_H

#include "../d3/GeomObj3d.h"


//! @ingroup GEOM
//
//! @brief Clase base para las líneas en tres dimensiones.
class Linea3d : public GeomObj3d
  {
  public:
    Linea3d(void): GeomObj3d(){}
    ~Linea3d(void) {}
    inline virtual unsigned short int Dimension(void) const
      { return 1; }
    virtual GEOM_FT Area(void) const
      { return 0.0; }
    virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    //@brief Return true if the points is on sobre la Linea.
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const= 0;
    //Return la intersección de la Linea con un plano coord_i=cte.
/*     virtual list_Pos3d Int(unsigned short int i, const double &d) const= 0; */
/*     inline list_Pos3d intx(const double &x) */
/*     //Return la intersección de la Linea con un plano x=cte. */
/*       { return Int(1,x); } */
/*     inline list_Pos3d inty(const double &y) */
/*     //Return la intersección de la Linea con un plano y=cte. */
/*       { return Int(2,y); } */
/*     inline list_Pos3d intz(const double &z) */
/*     //Return la intersección de la Linea con un plano z=cte. */
/*       { return Int(3,z); } */
  };
#endif



