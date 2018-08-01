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
//polygon2d_bool_op.h

#ifndef POLYGON2D_BOOL_OP_H
#define POLYGON2D_BOOL_OP_H

#include "xc_utils/src/geom/d2/2d_polygons/PolygonalSurface2d.h"
#include <list>

class Polygon2d;
class HalfPlane2d;
class Line2d;

Polygon2d prueba_conversion(const Polygon2d &p);

std::list<Polygon2d> join(const Polygon2d &p1,const Polygon2d &p2);
std::list<Polygon2d> join(const std::list<Polygon2d> &l);
std::list<Polygon2d> join(const std::list<Polygon2d> &,const Polygon2d &);

bool overlap(const Polygon2d &p1,const Polygon2d &p2);
bool overlap(const std::list<Polygon2d> &,const std::list<Polygon2d> &);

std::list<Polygon2d> clip(const std::list<Polygon2d> &,const Polygon2d &);

std::list<Polygon2d> intersection(const Polygon2d &p1,const Polygon2d &p2);
std::list<Polygon2d> intersection(const Polygon2d &p,const HalfPlane2d &r);
std::list<Polygon2d> intersection(const std::list<Polygon2d> &,const HalfPlane2d &);
std::list<Polygon2d> intersection(const std::list<Polygon2d> &,const Polygon2d &);
std::list<Polygon2d> intersection(const std::list<Polygon2d> &,const std::list<Polygon2d> &);

void particiona(const Pos2d &c1,Polygon2d &p1,const Pos2d &c2,Polygon2d &p2);
void particiona(Polygon2d &p1,Polygon2d &p2);
void particiona(const Pos2d &,std::list<Polygon2d> &,const Pos2d &,std::list<Polygon2d> &);
void particiona(const std::list<Pos2d> &,std::list<Polygon2d> &);
void particiona(std::list<Polygon2d> &);

#endif
