//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//Pos3dList.cc

#include "Pos3dList.h"
#include <plotter.h>

#include "xc_utils/src/geom/trf/Translation3d.h"
#include "xc_utils/src/geom/lists/utils_list_pos3d.h"


#include "xc_utils/src/geom/d3/BND3d.h"


Pos3dList::Pos3dList(void)
  : GeomObj3d(), lista_ptos() {}

Pos3dList::Pos3dList(const GeomObj::list_Pos3d &l)
  : GeomObj3d(), lista_ptos(l) {}

const Pos3d *Pos3dList::appendPoint(const Pos3d &p)
  {
    lista_ptos.push_back(p);
    return &(*lista_ptos.rbegin());
  }

//! @brief Applies the transformation to the points.
void Pos3dList::Transform(const Trf3d &trf3d)
  { trf3d.Transform(lista_ptos.begin(),lista_ptos.end()); }


//! @brief Return a reference al objeto cuyo
//! índice se pasa como parámetro.
Pos3d &Pos3dList::operator[](const size_t &i)
  {
    if(i<lista_ptos.size())
      return lista_ptos[i];
    else
      {
        std::cerr << "Pos3dList; indice: " << i << " fuera de rango. "
                  << std::endl;
        exit(0);
      }
  }

//! @brief Return a reference al objeto cuyo
//! índice se pasa como parámetro.
const Pos3d &Pos3dList::operator[](const size_t &i) const
  {
    if(i<lista_ptos.size())
      return lista_ptos[i];
    else
      {
        std::cerr << "Pos3dList; indice: " << i << " fuera de rango. "
                  << std::endl;
        exit(0);
      }
  }

//! @brief Returns true if the points belongs to the list.
bool Pos3dList::In(const Pos3d &p, const double &tol) const
  {
    for(register point_const_iterator j=lista_ptos.begin();j != lista_ptos.end();j++)
      if(dist2(*j,p)<=tol) return true;
    return false;
  }
//! @brief Return the maximum value of the i coordinate.
GEOM_FT Pos3dList::GetMax(unsigned short int i) const
  { return lista_ptos.GetMax(i); }

//! @brief Return the minimum value of the i coordinate.
GEOM_FT Pos3dList::GetMin(unsigned short int i) const
  { return lista_ptos.GetMin(i); }

//! @brief Return a Pos2dList with the points which i coordinate is greater
//! than d.
Pos3dList Pos3dList::GetMayores(unsigned short int i,const GEOM_FT &d) const
  {
    Pos3dList retval;
    retval.lista_ptos= lista_ptos.GetMayores(i,d);
    return retval;
  }

//! @brief Return a Pos2dList with the points which i coordinate is less
//! than d.
Pos3dList Pos3dList::GetMenores(unsigned short int i,const GEOM_FT &d) const
  {
    Pos3dList retval;
    retval.lista_ptos= lista_ptos.GetMenores(i,d);
    return retval;
  }


//! @brief Return el vértice i-ésimo (el primero es el 1).
const Pos3d &Pos3dList::Point(const size_t &i) const
  { return lista_ptos[i-1]; }


GEOM_FT Pos3dList::Ix(void) const
  {
    std::cerr << "Pos3dList Ix() not implemented" << std::endl;
    return 0.0;
  }
GEOM_FT Pos3dList::Iy(void) const
  {
    std::cerr << "Pos3dList Iy() not implemented" << std::endl;
    return 0.0;
  }
GEOM_FT Pos3dList::Iz(void) const
  {
    std::cerr << "Pos3dList Iz() not implemented" << std::endl;
    return 0.0;
  }

std::deque<GEOM_FT> &Pos3dList::GetSeparaciones(void) const
  { return lista_ptos.GetSeparaciones(); }

double Pos3dList::GetSeparacionMedia(void) const
  { return lista_ptos.GetSeparacionMedia(); }

void Pos3dList::Print(std::ostream &stream) const
  {
    if(!lista_ptos.empty())
      {
        register point_const_iterator i= lista_ptos.begin();
        stream << *i; i++;
        for(; i!=lista_ptos.end(); i++)
          stream << ", " << *i;
      }
  }
void Pos3dList::Plot(Plotter &plotter) const
  {
    std::cerr << "Pos3dList::Plot not implemented." << std::endl;
  }
