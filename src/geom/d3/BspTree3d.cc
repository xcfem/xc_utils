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
//BspTree3d.cc

#include "BspTree3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"


void Split_Polygon(const BspTree3d::polygon &pg,const Plane &particion,
                   BspTree3d::polygons_list &front_pieces,BspTree3d::polygons_list &back_pieces)
  {
    BspTree3d::polygons_list inter= corta(pg,particion);

    for(BspTree3d::polygons_list::const_iterator i= inter.begin();i!=inter.end();i++)
      {
        if(particion.classifyPolygon(*i) == Plane::DELANTE)
          front_pieces.push_back(*i);
        else
          back_pieces.push_back(*i);
      }
  }

void Build_BSP_Tree(BspTree3d *tree,const BspTree3d::BspTree3d::polygons_list &polygons)
  {
    typedef BspTree3d::BspTree3d::polygons_list::const_iterator const_pol_iterator;

    const_pol_iterator pol_iter= polygons.begin();
    const_pol_iterator root = pol_iter; pol_iter++;
    tree->particion = root->getPlane();
    tree->polygons.push_back(*root);
    BspTree3d::BspTree3d::polygons_list frontlist,backlist;

    for(;pol_iter!=polygons.end();pol_iter++)
      {
	Plane::polygon_classification result= tree->particion.classifyPolygon(*pol_iter);
        switch (result)
          {
	   case Plane::DENTRO:
              tree->polygons.push_back(*pol_iter);
              break;
           case Plane::DETRAS:
              backlist.push_back(*pol_iter);
              break;
           case Plane::DELANTE:
              frontlist.push_back(*pol_iter);
              break;
           case Plane::CRUZA:
              BspTree3d::polygons_list front_pieces,back_pieces;
              Split_Polygon(*pol_iter,tree->particion,front_pieces,back_pieces);
              backlist.insert(backlist.end(),back_pieces.begin(),back_pieces.end());
              frontlist.insert(frontlist.end(),front_pieces.begin(),front_pieces.end());
              break;
          }
      }
    if(!frontlist.empty())
      {
        tree->front = new BspTree3d;
        Build_BSP_Tree(tree->front, frontlist);
      }
    if(!backlist.empty())
      {
        tree->back = new BspTree3d;
        Build_BSP_Tree(tree->back, backlist);
      }
  }
