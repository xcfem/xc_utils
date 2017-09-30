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
//Polilinea3d.cc

#include "Polilinea3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"

const Pos3d *Polilinea3d::AgregaVertice(const Pos3d &p)
  {
    GeomObj::list_Pos3d::push_back(p);
    return &(*rbegin());
  }

size_t Polilinea3d::GetNumSegmentos(void) const
  {
    size_t retval= GetNumVertices();
    if(retval>0)
      retval-=1;
    return retval;
  }

//! @brief Return the segment pointed by the iterator.
Segmento3d Polilinea3d::GetSegmento(const list_Pos3d::const_iterator &i) const
  {
    list_Pos3d::const_iterator j= i; j++;
    Segmento3d s(*i,*j);
    return s;
  }

//! @brief Return the i-th segment (firt on has index 1).
Segmento3d Polilinea3d::GetSegmento(const size_t &i) const
  {
    const size_t ns= GetNumSegmentos();
    if(i>ns)
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "; you asked for the " << i
	        << "-th and " << ns
                << "-th is the last one." << std::endl;
    return Segmento3d((*this)[i-1],(*this)[i]);
  }


void Polilinea3d::Mueve(const Vector3d &v)
//Los puntos de la Polilinea3d estaran siempre en globales.
  {
    for(register list_Pos3d::iterator j=begin();j != end();j++)
      (*j)= (*j) + v;
  }
bool Polilinea3d::In(const Pos3d &p, const double &tol) const
  {
    for(register list_Pos3d::const_iterator j=begin();j != end();j++)
      if(GetSegmento(j).In(p,tol)) return true;
    return false;
  }

GeomObj3d::list_Pos3d Polilinea3d::getIntersection(const Plano3d &p) const
  {
    list_Pos3d retval;
    list_Pos3d::iterator i= retval.end();
    Segmento3d s;
    for(register list_Pos3d::const_iterator j=begin();j != end();j++)
      {
        s= GetSegmento(j);
        list_Pos3d lp= interseccion(p,s);
        retval.insert(i,lp.begin(),lp.end());
        i= retval.end();
      }
    return retval;
  }

GEOM_FT Polilinea3d::GetMax(unsigned short int i) const
//Devuelve el valor maximo de la coordenada i.
  { 
    if(empty()) return 0.0;
    const list_Pos3d::const_iterator primero= begin();
    GEOM_FT mx= (*primero)(i);
    for(register list_Pos3d::const_iterator j=primero;j != end();j++)
      mx= std::max((*j)(i),mx);
    return mx;
  }
GEOM_FT Polilinea3d::GetMin(unsigned short int i) const
//Devuelve el valor minimo de la coordenada i.
  {
    if(empty()) return 0.0;
    const list_Pos3d::const_iterator primero= begin();
    GEOM_FT mn= (*primero)(i);
    for(register list_Pos3d::const_iterator j=primero;j != end();j++)
      mn= std::min((*j)(i),mn);
    return mn;
  }
Polilinea3d Polilinea3d::GetMayores(unsigned short int i,const GEOM_FT &d) const
//Devuelve una Polilinea3d con los vertices cuya coordenada i
//es mayor que d.
  {
    Polilinea3d retval;
    for(register list_Pos3d::const_iterator j=begin();j != end();j++)
      if ((*j)(i) > d) retval.push_back(*j);
    return retval;
  }
Polilinea3d Polilinea3d::GetMenores(unsigned short int i,const GEOM_FT &d) const
//Devuelve una Polilinea3d con los vertices cuya coordenada i
//es menor que d.
  {
    Polilinea3d retval;
    for(register list_Pos3d::const_iterator j=begin();j != end();j++)
      if ((*j)(i) < d) retval.push_back(*j);
    return retval;
  }
// Polilinea3d::list_Pos3d Polilinea3d::Int(unsigned short int i,const double &d) const
// //Devuelve las intersecciones de la Polilinea3d con el plano
// //coord_i= d
//   {
//     list_Pos3d l_int; //Lista de intersecciones
// 	list_Pos3d::const_iterator ultimo= end();
//     ultimo--;
//     for(register list_Pos3d::const_iterator j= begin();j != ultimo;j++)
//       {
//         Segmento3d s= GetSegmento(j);
//         list_Pos3d l_temp= s.Int(i,d);
//         copy(l_temp.begin(),l_temp.end(), back_inserter(l_int)); 
//       }
// 	//l_int.unique();
//      return l_int;
//   }
// Polilinea3d Polilinea3d::Corta(unsigned short int i,const double &d) const
// //Devuelve la Polilinea3d con los vertices correspondientes a los
// //cortes con el plano coord_i= d
//   {
//     Polilinea3d result; //Lista de intersecciones
// 	list_Pos3d::const_iterator ultimo= end();
//     ultimo--;
//     for(register list_Pos3d::const_iterator j=begin();j != ultimo;j++)
//       {
//         Segmento3d s= GetSegmento(j);
//         list_Pos3d l_temp= s.Int(i,d);
//         result.push_back(*j);
//         if (!l_temp.empty()) result.push_back(*l_temp.begin());
//       }
//      result.push_back(*ultimo);
//      //result.unique();
//      return result;
//   }

GEOM_FT Polilinea3d::Ix(void) const
  {
    std::cerr << "Polilinea3d Ix() no implementada" << std::endl;
    return 0.0;
  }
GEOM_FT Polilinea3d::Iy(void) const
  {
    std::cerr << "Polilinea3d Iy() no implementada" << std::endl;
    return 0.0;
  }
GEOM_FT Polilinea3d::Iz(void) const
  {
    std::cerr << "Polilinea3d Iz() no implementada" << std::endl;
    return 0.0;
  }

Polilinea3d Polilinea3d::Separa(const Pos3d &p,const short int &sgn) const
//Suponemos que p es vertice de la Polilinea3d
//Devuelve el trozo de Polilinea3d:
//hasta p si sgn < 0
//desde p si sgn >= 0
  {
    Polilinea3d result;
    GeomObj::list_Pos3d::const_iterator i= find(p);
    if (i == end()) return result;
    if(sgn < 0)
      copy(begin(),++i,back_inserter(result));
    else
      copy(i,end(),back_inserter(result));
    return result;
  }


/**
   * @param i1 iterator to the first point.
   * @param i2 iterator to the second point.
   * @param pMaxDist pointer to the maximum distance of _line[return index].
   * @return the index of the point farthest fromthe segment (t1,t2).
   */
Polilinea3d::iterator Polilinea3d::getFarthestPointFromSegment(iterator it1, iterator it2, GEOM_FT &pMaxDist)
  {
    // Keep track of the point with the maximum distance.
    iterator maxIt = it1;
    maxIt++;
    Segmento3d s= Segmento3d(*it1,*it2);
    GEOM_FT maxDist= s.dist(*maxIt);

    iterator it = it1;
    it++;
    while(it != it2)
      {
        Segmento3d s= Segmento3d(*it1,*it2);
        GEOM_FT dist= s.dist(*it);
        if(dist > maxDist)
	  {
            maxIt = it;
            maxDist = dist;
          }

        it++;
      }
    // Assign pMaxDist.
    pMaxDist = maxDist;
    return maxIt;
  }


void Polilinea3d::Print(std::ostream &stream) const
  {
    if(empty()) return;
    register Polilinea3d::list_Pos3d::const_iterator i= begin();
    stream << *i; i++;
    for(; i!=end(); i++)
      stream << ", " << *i;
  }
