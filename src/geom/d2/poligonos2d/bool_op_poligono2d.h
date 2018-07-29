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
//bool_op_poligono2d.h

#ifndef BOOL_OP_POLIGONO2D_H
#define BOOL_OP_POLIGONO2D_H

#include "xc_utils/src/geom/d2/poligonos2d/SupPoligonal2d.h"
#include <list>

class Poligono2d;
class HalfPlane2d;
class Line2d;

Poligono2d prueba_conversion(const Poligono2d &p);

std::list<Poligono2d> join(const Poligono2d &p1,const Poligono2d &p2);
std::list<Poligono2d> join(const std::list<Poligono2d> &l);
std::list<Poligono2d> join(const std::list<Poligono2d> &,const Poligono2d &);

bool overlap(const Poligono2d &p1,const Poligono2d &p2);
bool overlap(const std::list<Poligono2d> &,const std::list<Poligono2d> &);

std::list<Poligono2d> clip(const std::list<Poligono2d> &,const Poligono2d &);

std::list<Poligono2d> intersection(const Poligono2d &p1,const Poligono2d &p2);
std::list<Poligono2d> intersection(const Poligono2d &p,const HalfPlane2d &r);
std::list<Poligono2d> intersection(const std::list<Poligono2d> &,const HalfPlane2d &);
std::list<Poligono2d> intersection(const std::list<Poligono2d> &,const Poligono2d &);
std::list<Poligono2d> intersection(const std::list<Poligono2d> &,const std::list<Poligono2d> &);

void particiona(const Pos2d &c1,Poligono2d &p1,const Pos2d &c2,Poligono2d &p2);
void particiona(Poligono2d &p1,Poligono2d &p2);
void particiona(const Pos2d &,std::list<Poligono2d> &,const Pos2d &,std::list<Poligono2d> &);
void particiona(const std::list<Pos2d> &,std::list<Poligono2d> &);
void particiona(std::list<Poligono2d> &);

#endif
