//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//LabelContainer.cc

#include "LabelContainer.h"
#include <iostream>

//! @brief Devuelve el valor de la etiqueta de índice i.
const std::string &DiccionarioEtiquetas::get_etiqueta_indice(const int &i) const
  {
    static std::string retval;
    retval= "";
    bm_type::const_iterator it=boost::multi_index::get<from>(bm).find(i);
    if(it!=bm.end())
      retval= it->second;
    else
      std::cerr << "LabelContainer::get_etiqueta_indice; indice "
                << i << " fuera de rango." << std::endl;
    return retval;
  }

//! @brief Devuelve el valor del indice de la etiqueta que se pasa como
//! parámetro.
int DiccionarioEtiquetas::get_indice_etiqueta(const std::string &e) const
  {
    int retval= -1;
    bm_type::index_iterator<to>::type it=boost::multi_index::get<to>(bm).find(e);
    if(it!= bm.get<to>().end())
      retval= it->first;
    return retval;
  }

const std::string &DiccionarioEtiquetas::operator()(const int &i) const
  { return get_etiqueta_indice(i); }

int DiccionarioEtiquetas::operator()(const std::string &str) const
  { return get_indice_etiqueta(str); }

int DiccionarioEtiquetas::insert(const std::string &e)
  {
    int id= get_indice_etiqueta(e);
    if(id<0) //la etiqueta no existe.
      {
        id= bm.size();
        bm.insert(bm_type::value_type(id,e));
      }
    assert(id>=0);
    return id;
  }

size_t DiccionarioEtiquetas::getNumEtiquetas(void) const
  { return bm.size(); }

void DiccionarioEtiquetas::Print(std::ostream &os) const
  {
    bm_type::index_iterator<to>::type i=boost::multi_index::get<to>(bm).begin();
    for(;i!=boost::multi_index::get<to>(bm).end();i++)
      os << i->first << " " << i->second << std::endl;
  }

std::ostream &operator<<(std::ostream &os,const DiccionarioEtiquetas &d)
  {
    d.Print(os);
    return os;
  }

DiccionarioEtiquetas LabelContainer::dic;

//! @brief Constructor.
LabelContainer::LabelContainer(void)
   {}

//! @brief += operator.
LabelContainer &LabelContainer::operator+=(const LabelContainer &otro)
  {
    extend(otro);
    return *this;
  }

//! @brief -= operator.
LabelContainer &LabelContainer::operator-=(const LabelContainer &otro)
  {
    std::set<int> tmp;
    std::set_difference(etiquetas.begin(),etiquetas.end(),otro.etiquetas.begin(),otro.etiquetas.end(), std::inserter(tmp,tmp.begin()));
    etiquetas= tmp;
    return *this;
  }

//! @brief *= operator (intersection).
LabelContainer &LabelContainer::operator*=(const LabelContainer &otro)
  {
    std::set<int> tmp;
    std::set_intersection(etiquetas.begin(),etiquetas.end(),otro.etiquetas.begin(),otro.etiquetas.end(), std::inserter(tmp,tmp.begin()));
    etiquetas= tmp;
    return *this;
  }

//! @brief Return a reference to the label dictionary.
const DiccionarioEtiquetas &LabelContainer::getDiccionario(void)
  { return dic; }

//! @brief Return the number of labels in this object.
size_t LabelContainer::getNumEtiquetas(void) const
  { return etiquetas.size(); }

//! @brief Return the label identifiers.
const std::set<int> &LabelContainer::getIdsEtiquetas(void) const
  { return etiquetas; }

void LabelContainer::extend(const LabelContainer &otro)
  {
    for(std::set<int>::const_iterator i= otro.etiquetas.begin();i!=otro.etiquetas.end();i++)
      etiquetas.insert(*i);
  }

int LabelContainer::addEtiqueta(const std::string &e)
  {
    int retval= dic.insert(e);
    etiquetas.insert(retval);
    return retval;
  }

int LabelContainer::removeEtiqueta(const std::string &e)
  {
    const int retval= dic.get_indice_etiqueta(e);
    if(retval>=0)
      if(hasEtiqueta(retval))
        { etiquetas.erase(retval); }
    return retval;
  }

bool LabelContainer::hasEtiqueta(const int &id) const
  {
    bool retval= false;
    std::set<int>::iterator it= etiquetas.find(id);
    retval= (it!=etiquetas.end());
    return retval;
  }

bool LabelContainer::hasEtiqueta(const std::string &e) const
  {
    bool retval= false;
    const int id= dic.get_indice_etiqueta(e);
    if(id>=0)
      retval= hasEtiqueta(id);
    return retval;
  }

void LabelContainer::clear(void)
  { etiquetas.clear(); }

void LabelContainer::Print(std::ostream &os) const
  {
    for(std::set<int>::const_iterator i= etiquetas.begin();i!=etiquetas.end();i++)
      os << dic.get_etiqueta_indice(*i) << " ";
  }



std::ostream &operator<<(std::ostream &os,const LabelContainer &lc)
  {
    lc.Print(os);
    return os;
  }

//! @brief Return the union of both containers.
LabelContainer operator+(const LabelContainer &a,const LabelContainer &b)
  {
    LabelContainer retval(a);
    retval+=b;
    return retval;
  }

//! @brief Return the labels in a that are not in b.
LabelContainer operator-(const LabelContainer &s1,const LabelContainer &s2)
  {
    LabelContainer retval(s1);
    retval-=s2;
    return retval;
  }

//! @brief Return the labels in a that are also in b.
LabelContainer operator*(const LabelContainer &s1,const LabelContainer &s2)
  {
    LabelContainer retval(s1);
    retval*=s2;
    return retval;    
  }
