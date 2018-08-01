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
//BSPTREE3D.h

#ifndef BSPTREE3D_H
#define BSPTREE3D_H

#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d2/Polygon3d.h"
#include <list>


class BspTree3d
  {
  public:
    typedef std::list<Polygon3d> polygons_list;
    typedef polygons_list::value_type polygon;

    friend void Build_BSP_Tree(BspTree3d *,const polygons_list &);

  private:
    Plane particion;         //Partition plane.
    polygons_list polygons; //List of the polygons that lie 
                               //in the partition plane.
    BspTree3d *front,*back; //Pointer to the children.
  public:
    BspTree3d(void)
      : particion(), polygons(), front(nullptr), back(nullptr) {}
    BspTree3d(const polygons_list &polygons)
      : particion(), polygons(), front(nullptr), back(nullptr)
      { Build_BSP_Tree(this,polygons); }
    inline BspTree3d *Delante(void) const
      { return front; }
    inline BspTree3d *Detras(void) const
      { return back; }
    inline void PutDelante(BspTree3d *ptr)
      { front= ptr; }
    inline void PutDetras(BspTree3d *ptr)
      { back= ptr; }
  };

#endif
