//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//TripletMap.h

#ifndef TRIPLETMAP_H
#define TRIPLETMAP_H

#include <map>
#include <iostream>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"

typedef boost::tuple<size_t,size_t,size_t> Triplete;

inline void printTriplete(std::ostream &os,const Triplete &t)
  {
    os << "[" << t.get<0>() << ","
       << t.get<1>() << ","
       << t.get<2>() << "]";
  }

//! @brief Mapa tipo «tensor disperso».
template<class T>
class TripletMap:public std::map<Triplete,T>
  {
  public:
    typedef std::map<Triplete,T> map_Ts;
    typedef typename map_Ts::const_iterator const_iterator;
    typedef typename map_Ts::iterator iterator;
    TripletMap(void): map_Ts() {}
    void PrintMember(std::ostream &os,const_iterator &) const;
    void Print(std::ostream &) const;
  };

template<class T>
void TripletMap<T>::PrintMember(std::ostream &os,const_iterator &i) const
  {
    printTriplete(os,(*i).first);
    os << "; " << (*i).second;
  }

template<class T>
void TripletMap<T>::Print(std::ostream &os) const
  {
    for(const_iterator i=this->begin();i!=this->end();i++)
      {
        PrintMember(os,i);
        os << std::endl;
      }
  }
template<class T>
std::ostream &operator<<(std::ostream &os,const TripletMap<T> &tm)
  {
    tm.Print(os);
    return os;
  }
    

#endif
