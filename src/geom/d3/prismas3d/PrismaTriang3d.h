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
//PrismaTriang3d.h

#ifndef PRISMATRIANG3D_H
#define PRISMATRIANG3D_H

#include "PrismaRecto3d.h"
#include "xc_utils/src/geom/d2/Triangulo3d.h"


//! @ingroup GEOM
//
//! @brief Prisma recto de base triangular.
class PrismaTriang3d : public PrismaRecto3d<Triangulo3d>
  {
  public:
    typedef PrismaRecto3d<Triangulo3d> prisma_triang;
  public:
    PrismaTriang3d(const Triangulo3d &tr= Triangulo3d(),const double &h=1.0);
    PrismaTriang3d(const PrismaTriang3d &otro);
    PrismaTriang3d &operator=(const PrismaTriang3d &c);
    virtual GeomObj *clon(void) const;
    
  };
#endif






