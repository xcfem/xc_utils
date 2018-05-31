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
#include "xc_utils/src/geom/d2/Poligono3d.h"
#include <list>


class BspTree3d
  {
  public:
    typedef std::list<Poligono3d> lista_poligonos;
    typedef lista_poligonos::value_type poligono;

    friend void Build_BSP_Tree(BspTree3d *tree,const lista_poligonos &poligonos);

  private:
    Plane particion;         //Plano de partición.
    lista_poligonos poligonos; //Lista de poligonos coincidentes 
                               //con el plano de partición.
    BspTree3d *front,*back; //Punteros a hijos.
  public:
    BspTree3d(void)
      : particion(), poligonos(), front(nullptr), back(nullptr) {}
    BspTree3d(const lista_poligonos &poligonos)
      : particion(), poligonos(), front(nullptr), back(nullptr)
      { Build_BSP_Tree(this,poligonos); }
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
