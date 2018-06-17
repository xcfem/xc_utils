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
//ListaPos2d.cc

#include "ListaPos2d.h"
#include <plotter.h>

#include "xc_utils/src/geom/trf/Translation2d.h"
#include "xc_utils/src/geom/listas/utils_list_pos2d.h"


#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"
#include "xc_utils/src/geom/d2/BND2d.h"

ListaPos2d::ListaPos2d(void)
  : GeomObj2d(), lista_ptos() {}

ListaPos2d::ListaPos2d(const GeomObj::list_Pos2d &l)
  : GeomObj2d(), lista_ptos(l) {}

//! @brief Appends the point to the list.
const Pos2d *ListaPos2d::appendPoint(const Pos2d &p)
  {
    lista_ptos.push_back(p);
    return &(*lista_ptos.rbegin());
  }

//! @brief Appends the point to the list.
//! added to make things easier to boost.Python.
void ListaPos2d::appendPointPy(const Pos2d &p)
  { appendPoint(p); }

//! @brief Applies the transformation to the points.
void ListaPos2d::Transforma(const Trf2d &trf2d)
  { trf2d.Transforma(lista_ptos.begin(),lista_ptos.end()); }

//! @brief Return the vertex list of a polyline parallel to
//! the polyline builded with the vertex of this line at the
//! distance being passed as parameter. Si the distance is
//! positive the new polyline is builded on the right.
ListaPos2d ListaPos2d::Offset(const GEOM_FT &d) const
  {
    ListaPos2d retval;
    const size_t nv= getNumberOfPoints();
    if(nv>1)
      {
        point_const_iterator i= points_begin();
        point_const_iterator j= i;j++;
        const Segment2d s1= Segment2d(*i,*j).Offset(d);
        Recta2d r1= s1.RectaSoporte();
        retval.appendPoint(s1.Origen());
        Segment2d s2= s1;
        i++;j++;//Next segment.
        for(;j != points_end();i++,j++)
          {
            s2= Segment2d(*i,*j).Offset(d);
            Recta2d r2= s2.RectaSoporte();
            Pos2d ptIntersection= intersection_point(r1,r2);
            retval.appendPoint(ptIntersection);
            if(!ptIntersection.exists())
	      std::cerr << getClassName() << "::" << __FUNCTION__
		        << "; itersection of lines"
                        << " r1: "
                        << r1 << " andr2: " << r2
			<< " not found." << std::endl;
            r1= r2;
          }
        retval.appendPoint(s2.Destino());
      }
    return retval;
  }


//! @brief Return a reference al objeto cuyo
//! índice se pasa como parámetro.
Pos2d &ListaPos2d::operator[](const size_t &i)
  {
    if(i<lista_ptos.size())
      return lista_ptos[i];
    else
      {
        std::cerr << "ListaPos2d; indice: " << i << " fuera de rango. "
                  << std::endl;
        exit(0);
      }
  }

//! @brief Return a reference al objeto cuyo
//! índice se pasa como parámetro.
const Pos2d &ListaPos2d::operator[](const size_t &i) const
  {
    if(i<lista_ptos.size())
      return lista_ptos[i];
    else
      {
        std::cerr << "ListaPos2d; indice: " << i << " fuera de rango. "
                  << std::endl;
        exit(0);
      }
  }

//! @brief Return true if the point belongs to the set.
bool ListaPos2d::In(const Pos2d &p, const double &tol) const
  {
    for(register point_const_iterator j=lista_ptos.begin();j != lista_ptos.end();j++)
      if(dist2(*j,p)<=tol) return true;
    return false;
  }
//! @brief Return the maximum value of the i coordinate.
GEOM_FT ListaPos2d::GetMax(unsigned short int i) const
  { return lista_ptos.GetMax(i); }

//! @brief Return the minimum value of the i coordinate.
GEOM_FT ListaPos2d::GetMin(unsigned short int i) const
  { return lista_ptos.GetMin(i); }

//! @brief Return a ListaPos2d with the points which i coordinate is greater
//! than d.
ListaPos2d ListaPos2d::GetMayores(unsigned short int i,const GEOM_FT &d) const
  {
    ListaPos2d retval;
    retval.lista_ptos= lista_ptos.GetMayores(i,d);
    return retval;
  }

//! @brief Return a ListaPos2d with the points which i coordinate is less
//! than d.
ListaPos2d ListaPos2d::GetMenores(unsigned short int i,const GEOM_FT &d) const
  {
    ListaPos2d retval;
    retval.lista_ptos= lista_ptos.GetMenores(i,d);
    return retval;
  }


//! @brief Return el vértice i-ésimo (el primero es el 1).
const Pos2d &ListaPos2d::Point(const size_t &i) const
  { return lista_ptos[i-1]; }


GEOM_FT ListaPos2d::Ix(void) const
  {
    std::cerr << "ListaPos2d Ix() not implemented" << std::endl;
    return 0.0;
  }
GEOM_FT ListaPos2d::Iy(void) const
  {
    std::cerr << "ListaPos2d Iy() not implemented" << std::endl;
    return 0.0;
  }
GEOM_FT ListaPos2d::Iz(void) const
  {
    std::cerr << "ListaPos2d Iz() not implemented" << std::endl;
    return 0.0;
  }

std::deque<GEOM_FT> &ListaPos2d::GetSeparaciones(void) const
  { return lista_ptos.GetSeparaciones(); }

std::deque<GEOM_FT> &ListaPos2d::GetRecubrimientos(const Poligono2d &plg) const
  { return getRecubrimientos(lista_ptos,plg); }

double ListaPos2d::GetSeparacionMedia(void) const
  { return lista_ptos.GetSeparacionMedia(); }

void ListaPos2d::Print(std::ostream &stream) const
  {
    if(lista_ptos.empty()) return;
    register point_const_iterator i= lista_ptos.begin();
    stream << *i; i++;
    for(; i!=lista_ptos.end(); i++)
      stream << ", " << *i;
  }
void ListaPos2d::Plot(Plotter &plotter) const
  {
    std::cerr << "ListaPos2d::Plot not implemented." << std::endl;
  }
