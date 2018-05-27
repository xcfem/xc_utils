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
//PoliPos.h

#ifndef POLIPOS_H
#define POLIPOS_H

#include <deque>
#include "../tipos_cgal.h"
#include "xc_basic/src/util/matem.h"


//! @ingroup GEOM
//
//! @brief Clase base para las listas de posiciones.
template<class pos>
class PoliPos : public std::deque<pos>
  {
  protected:
    typedef std::deque<pos> deque_pos;
  protected:
  //Funcion auxiliar.
    static GEOM_FT g(GEOM_FT v1, GEOM_FT v2)
      { return (sqr(v1) + v1 * v2 + sqr(v2)); }
  public:
    typedef typename deque_pos::iterator iterator;
    typedef typename deque_pos::const_iterator const_iterator;
    typedef typename pos::vector vector;

    PoliPos(void): deque_pos() {}
    PoliPos(const PoliPos<pos> &otra): deque_pos(otra) {}
    PoliPos<pos> &operator =(const PoliPos<pos> &l)
      {
        deque_pos::operator= (l);
        return *this;
      }
    inline pos *Agrega(const pos &p)
      {
        deque_pos::push_back(p);
        return &(this->back());
      }
    inline void Agrega(const PoliPos<pos> &p)
      { Cat(p); }
    void AgregaSiNuevo(const pos &);
    const_iterator find(const pos &p) const
      { return std::find(this->begin(),this->end(),p); }
    iterator find(const pos &p)
      { return std::find(this->begin(),this->end(),p); }
    bool In(const pos &p) const;
    bool isClosed(const GEOM_FT &tol= 1e-6) const;
    GEOM_FT getLength(void) const;
    GEOM_FT GetMax(unsigned short i) const;
    GEOM_FT GetMin(unsigned short i) const;
    PoliPos GetMayores(unsigned short int i,const GEOM_FT &d) const;
    PoliPos GetMenores(unsigned short int i,const GEOM_FT &d) const;
    pos getCenterOfMass(void) const;
    pos getWeightedCenterOfMass(const std::deque<GEOM_FT> &) const;
    PoliPos<pos> GetSwap(void) const;
    void Swap(void)
      { *this= this->GetSwap(); }
    std::deque<GEOM_FT> &GetSeparaciones(void) const;
    GEOM_FT GetSeparacionMedia(void) const;

    iterator getFarthestPoint(const pos &);
    virtual iterator getFarthestPointFromSegment(iterator it1, iterator it2, GEOM_FT &pMaxDist);
    void simplify(GEOM_FT epsilon, iterator it1, iterator it2);
    void simplify(GEOM_FT epsilon);

    void Cat(const PoliPos<pos> &l);
    template <class inputIterator>
    void Cat(inputIterator begin, inputIterator end);
    friend int operator ==(const PoliPos<pos> &a,const PoliPos<pos> &b)
      {
        if ( (const deque_pos &) a != (const deque_pos &) b ) return 0;
        return 1;
      }
  };


//! @brief Return true if the points is on en la lista.
template <class pos>
bool PoliPos<pos>::In(const pos &p) const
  { return (find(p)!=this->end()); }

//! @brief Appends the point to the list (if not already there).
template <class pos>
void PoliPos<pos>::AgregaSiNuevo(const pos &p)
  {
    if(!In(p))
      this->push_back(p);
  }

//! @brief True if dist(lastPoint,firstPoint)< tol*length
template <class pos>
bool PoliPos<pos>::isClosed(const GEOM_FT &tol) const
  {
    bool retval= false;
    const GEOM_FT treshold= tol*getLength();
    const pos &first= this->front();
    const pos &last= this->back();
    if(dist(first,last)<treshold)
      retval= true;
    return retval;
  }

//! @brief Return the length of the PoliPos.
template <class pos>
GEOM_FT PoliPos<pos>::getLength(void) const
  {
    if(this->size()<2) return 0.0;
    GEOM_FT temp = 0;
    register const_iterator j;
    for(register const_iterator i=this->begin(); i != this->end(); i++)
      {
        j= i;j++;
        if (j!=this->end()) temp += dist(*i,*j);
      }
    return temp;
  }

template <class pos>
GEOM_FT PoliPos<pos>::GetMax(unsigned short j) const
//Return el valor mínimo de la coordenada j.
  {
    GEOM_FT retval(0.0);
    if(!this->empty())
      {
        register const_iterator i=this->begin();
        retval= (*i)(j);
        for(; i != this->end(); i++)
          retval= std::max(retval,(*i)(j));
      }
    return retval;
  }

template <class pos>
GEOM_FT PoliPos<pos>::GetMin(unsigned short j) const
//Return el valor mínimo de la coordenada j.
  {
    GEOM_FT retval(0.0);
    if(!this->empty())
      {
        register const_iterator i=this->begin();
        retval= (*i)(j);
        for(; i != this->end(); i++)
          retval= std::min(retval,(*i)(j));
      }
    return retval;
  }

template <class pos>
//! @brief Return el centro de gravedad del polígono.
pos PoliPos<pos>::getCenterOfMass(void) const
  {
    if(this->size()<1) return pos();
    if(this->size()<2) return *(this->begin());
    const_iterator i= this->begin();
    vector vpos_center_of_mass((*i).VectorPos());
    i++;
    for(; i != this->end(); i++) 
      vpos_center_of_mass= vpos_center_of_mass + (*i).VectorPos();
    vpos_center_of_mass= vpos_center_of_mass * (1.0/this->size());
    return pos()+ vpos_center_of_mass;
  }

template <class pos>
//! @brief Return el centro de gravedad del polígono.
pos PoliPos<pos>::getWeightedCenterOfMass(const std::deque<GEOM_FT> &areas) const
  {
    pos retval;
    const size_t sz= this->size();
    if(sz>0)
      {
        assert(sz==areas.size());
        if(sz<2)
          retval= *(this->begin());
        else
          {
            std::deque<GEOM_FT>::const_iterator iArea= areas.begin();
            GEOM_FT areaTot(0.0);
            const_iterator i= this->begin();
            vector vpos_center_of_mass((*i).VectorPos()*(*iArea));
            areaTot+= *iArea;
            i++; iArea++;
            for(; i != this->end(); i++)
              {
                vpos_center_of_mass= vpos_center_of_mass + (*i).VectorPos()*(*iArea);
                areaTot+= *iArea;
              }
            if(areaTot!=0.0)
              {
                vpos_center_of_mass= vpos_center_of_mass * (1.0/areaTot);
                retval= pos()+vpos_center_of_mass;
              }
          }
      }
    return retval;
  }

template <class pos>
PoliPos<pos> PoliPos<pos>::GetSwap(void) const
  //Return una lista con los elementos en orden inverso
  //al de esta.
  {
    PoliPos<pos> retval(*this);
    const size_t sz= this->size();
    if (sz<2) return retval;
    for(register size_t i=0; i<sz; i++) 
      retval[sz-i-1]= (*this)[i];
    return retval;
  }

//! @brief Compute the distance from each point to the nearest one.
template <class pos>
std::deque<GEOM_FT> &PoliPos<pos>::GetSeparaciones(void) const
  {
    const size_t sz= this->size();
    static std::deque<GEOM_FT> retval;
    retval.resize(sz);
    const double grande= 10.0*getBnd((*this)).Diagonal().GetModulus();
    for(size_t i= 0;i<sz;i++)
      retval[i]= grande;
    if(sz>1)
      {
        double d;
        for(size_t i= 0;i<sz;i++)
          {
            const pos &pi= (*this)[i];
            for(size_t j= 0;j<sz;j++)
              if(i!=j)
                {
                  const pos &pj= (*this)[j];
                  d= dist(pi,pj);
                  if(d<retval[i] && d>0.0)
                    retval[i]= d;
                }
          }
      }
    return retval;
  }
//! @brief Return the average distance between points.
template <class pos>
GEOM_FT PoliPos<pos>::GetSeparacionMedia(void) const
  {
    GEOM_FT retval(0);
    const size_t sz= this->size();
    if(sz>0)
      {
        const std::deque<GEOM_FT> &seps= this->GetSeparaciones();
        for(size_t i= 0;i<sz;i++)
          retval+= seps[i];
        retval/=sz;
      }
    return retval;
  }

template <class pos>
PoliPos<pos> PoliPos<pos>::GetMayores(unsigned short int i,const GEOM_FT &d) const
  {
    PoliPos<pos> retval;
    for(register const_iterator j=this->begin();j != this->end();j++)
      if ((*j)(i) > d) retval.push_back(*j);
    return retval;
  }

template <class pos>
PoliPos<pos> PoliPos<pos>::GetMenores(unsigned short int i,const GEOM_FT &d) const
  {
    PoliPos<pos> retval;
    for(register const_iterator j=this->begin();j != this->end();j++)
      if ((*j)(i) < d) retval.push_back(*j);
    return retval;
  }

//! @brief Returns the farthest point from those of the list.
template <class pos>
typename PoliPos<pos>::iterator PoliPos<pos>::getFarthestPoint(const pos &p)
  {
    iterator i= this->begin();
    iterator retval= i; i++;
    GEOM_FT maxDist= dist(p,*retval);
    GEOM_FT d= 0.0;
    for(;i!= this->end();i++)
      {
    	d= dist(p,*i);
    	if(d>maxDist)
    	  {
    	    maxDist= d;
    	    retval= i;
    	  }
      }
    return retval;
  }

/**
   * @param i1 iterator to the first point.
   * @param i2 iterator to the second point.
   * @param pMaxDist pointer to the maximum distance of _line[return index].
   * @return the index of the point farthest fromthe segment (t1,t2).
   */
template <class pos>
typename PoliPos<pos>::iterator PoliPos<pos>::getFarthestPointFromSegment(iterator , iterator , GEOM_FT &)
  {
    std::cerr << "getFarthestPointFromSegment must be redefined in derived classes." << std::endl;
    return this->begin();
  }

/**
   * Douglas Peucker algorithm implementation. 
   * Recursively delete points that are within epsilon.
   * @param epsilon the higher the more aggressive.
   * @param iterator of the first point in a segment.
   * @param iterator of the last point in a segment.
   */
template <class pos>
void PoliPos<pos>::simplify(GEOM_FT epsilon, iterator it1, iterator it2)
  {
    if (distance(it1, it2) <= 1) return;

    // Acquire the farthest point from the segment it1, it2
    GEOM_FT dist= -1.0;
    iterator index= getFarthestPointFromSegment(it1, it2, dist);

    // If the farthest point exceeds epsilon, recurse, with index as pivot.
    if (dist > epsilon)
      {
        simplify(epsilon, it1, index);
        simplify(epsilon, index, it2);
      }
    else
      {
        // Delete everything except it1 and it2.
        auto it = it1;
        it++;
        for (; it != it2; )
	  { this->erase(it++); }
      }
  }

/**
 * @param epsilon The higher, the more points gotten rid of.
 */
template <class pos>
void PoliPos<pos>::simplify(GEOM_FT epsilon)
  {
    const bool closed= this->isClosed();
    if(closed)
      {
        iterator i= this->begin();
	iterator j= this->getFarthestPoint(*i);
	simplify(epsilon,i,j);
	i= j;
        j= this->end(); --j; //Last point.
        simplify(epsilon,i,j);
      }
    else
      {
        iterator i= this->begin();
        iterator j= this->end(); --j; //Last point.
        simplify(epsilon,i,j);
      }
  }

template <class pos>
void PoliPos<pos>::Cat(const PoliPos<pos> &l)
  {
    for(register typename PoliPos<pos>::const_iterator k= l.begin();k!=l.end();k++)
      this->push_back(*k);
  }

//!@brief Insert the objects between [first,last).
template <class pos> template<class inputIterator>
void PoliPos<pos>::Cat(inputIterator begin, inputIterator end)
  {
    for(inputIterator i= begin;i!=end;i++)
      this->push_back(*i);
  }

template <class pos>
std::ostream &operator<<(std::ostream &os,const PoliPos<pos> &l)
  {
    if(l.size()<1) return os;
    typedef typename PoliPos<pos>::const_iterator c_iterator;
    register c_iterator i= l.begin();
    os << *i; i++;
    for(;i!= l.end();i++)
      os << " , " << *i;
    return os;
  }


#endif






