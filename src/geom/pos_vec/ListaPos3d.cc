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
//ListaPos3d.cc

#include "ListaPos3d.h"
#include <plotter.h>

#include "xc_utils/src/geom/trf/Traslacion3d.h"
#include "xc_utils/src/geom/listas/utils_list_pos3d.h"


#include "xc_utils/src/geom/d3/BND3d.h"


ListaPos3d::ListaPos3d(void)
  : GeomObj3d(), lista_ptos() {}

ListaPos3d::ListaPos3d(const GeomObj::list_Pos3d &l)
  : GeomObj3d(), lista_ptos(l) {}

const Pos3d *ListaPos3d::AgregaPunto(const Pos3d &p)
  {
    lista_ptos.push_back(p);
    return &(*lista_ptos.rbegin());
  }

//! @brief Aplica a los puntos la transformación que se pasa como parámetro.
void ListaPos3d::Transforma(const Trf3d &trf3d)
  { trf3d.Transforma(lista_ptos.begin(),lista_ptos.end()); }


//! @brief Devuelve una referencia al objeto cuyo
//! índice se pasa como parámetro.
Pos3d &ListaPos3d::operator[](const size_t &i)
  {
    if(i<lista_ptos.size())
      return lista_ptos[i];
    else
      {
        std::cerr << "ListaPos3d; indice: " << i << " fuera de rango. "
                  << std::endl;
        exit(0);
      }
  }

//! @brief Devuelve una referencia al objeto cuyo
//! índice se pasa como parámetro.
const Pos3d &ListaPos3d::operator[](const size_t &i) const
  {
    if(i<lista_ptos.size())
      return lista_ptos[i];
    else
      {
        std::cerr << "ListaPos3d; indice: " << i << " fuera de rango. "
                  << std::endl;
        exit(0);
      }
  }

//! @brief Devuelve verdadero si el punto está en el conjunto.
bool ListaPos3d::In(const Pos3d &p, const double &tol) const
  {
    for(register point_const_iterator j=lista_ptos.begin();j != lista_ptos.end();j++)
      if(dist2(*j,p)<=tol) return true;
    return false;
  }
//! @brief Devuelve el valor maximo de la coordenada i.
GEOM_FT ListaPos3d::GetMax(unsigned short int i) const
  { return lista_ptos.GetMax(i); }

//! @brief Devuelve el valor minimo de la coordenada i.
GEOM_FT ListaPos3d::GetMin(unsigned short int i) const
  { return lista_ptos.GetMin(i); }

//! @brief Devuelve una ListaPos3d con los puntos cuya coordenada i
//! es mayor que d.
ListaPos3d ListaPos3d::GetMayores(unsigned short int i,const GEOM_FT &d) const
  {
    ListaPos3d retval;
    retval.lista_ptos= lista_ptos.GetMayores(i,d);
    return retval;
  }
//! @brief Devuelve una ListaPos3d con los puntos cuya coordenada i
//! es menor que d.
ListaPos3d ListaPos3d::GetMenores(unsigned short int i,const GEOM_FT &d) const
  {
    ListaPos3d retval;
    retval.lista_ptos= lista_ptos.GetMenores(i,d);
    return retval;
  }


//! @brief Devuelve el vértice i-ésimo (el primero es el 1).
const Pos3d &ListaPos3d::Punto(const size_t &i) const
  { return lista_ptos[i-1]; }


GEOM_FT ListaPos3d::Ix(void) const
  {
    std::cerr << "ListaPos3d Ix() no implementada" << std::endl;
    return 0.0;
  }
GEOM_FT ListaPos3d::Iy(void) const
  {
    std::cerr << "ListaPos3d Iy() no implementada" << std::endl;
    return 0.0;
  }
GEOM_FT ListaPos3d::Iz(void) const
  {
    std::cerr << "ListaPos3d Iz() no implementada" << std::endl;
    return 0.0;
  }

std::deque<GEOM_FT> &ListaPos3d::GetSeparaciones(void) const
  { return lista_ptos.GetSeparaciones(); }

double ListaPos3d::GetSeparacionMedia(void) const
  { return lista_ptos.GetSeparacionMedia(); }

void ListaPos3d::Print(std::ostream &stream) const
  {
    if(!lista_ptos.empty())
      {
        register point_const_iterator i= lista_ptos.begin();
        stream << *i; i++;
        for(; i!=lista_ptos.end(); i++)
          stream << ", " << *i;
      }
  }
void ListaPos3d::Plot(Plotter &plotter) const
  {
    std::cerr << "ListaPos3d::Plot no implementada." << std::endl;
  }
