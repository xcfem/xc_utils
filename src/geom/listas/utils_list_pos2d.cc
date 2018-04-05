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
//utils_list_pos2d.cc

#include "utils_list_pos2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include <plotter.h>
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/geom/d2/BND2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"

void plot(Plotter &plt,const GeomObj::list_Pos2d &l)
  {
    for(GeomObj::list_Pos2d::const_iterator i= l.begin();i!=l.end();i++)
      (*i).Plot(plt);
  }


//! @brief Moves the points of the list.
void mueve(GeomObj::list_Pos2d &l,const Vector2d &v)
  {
    for(register GeomObj::list_Pos2d::iterator j=l.begin();j != l.end();j++)
      (*j)= (*j) + v;
  }

//! @brief Aplica a los vértices la transformación que se pasa como parámetro.
void transforma(GeomObj::list_Pos2d &l,const Trf2d &t)
  { t.Transforma(l.begin(),l.end()); }

//! @brief Devuelve la esquina superior derecha del rectángulo envolvente. 
Pos2d getPMax(const GeomObj::list_Pos2d &l)
  { return Pos2d(l.GetMax(1),l.GetMax(2)); }

//! @brief Devuelve la esquina inferior izquierda del rectángulo envolvente. 
Pos2d getPMin(const GeomObj::list_Pos2d &l)
  { return Pos2d(l.GetMin(1),l.GetMin(2)); }

//! @brief Devuelve el rectángulo envolvente. 
BND2d getBnd(const GeomObj::list_Pos2d &l)
  { return BND2d(getPMin(l),getPMax(l)); }

//! @brief Calcula los recubrimientos de las fibras.
std::deque<GEOM_FT> &getRecubrimientos(const GeomObj::list_Pos2d &l,const Poligono2d &plg)
  {
    const size_t sz= l.size();
    static std::deque<GEOM_FT> retval;
    retval.resize(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= plg.GetRecubrimiento(l[i]);
    return retval;
  }
