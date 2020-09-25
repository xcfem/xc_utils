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
//SlidingVectorsSystem2d.cc

#include "SlidingVectorsSystem2d.h"
#include "SlidingVector2d.h"
#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"



SlidingVectorsSystem2d::SlidingVectorsSystem2d(const SlidingVector2d &v)
  : SlidingVector2d(v), mom(0.0) {}

//! @brief Return the moment about P.
GEOM_FT SlidingVectorsSystem2d::getMoment(const Pos2d &P) const
  {
    const GEOM_FT m2= SlidingVector2d::getMoment(P);
    return mom+m2;
  }

void SlidingVectorsSystem2d::Print(std::ostream &os) const
  {
    os << "Resultant R=" << getResultant()
       << " , moment with respect to " << getOrg() << " Mo= " << mom; 
  }

void SlidingVectorsSystem2d::PrintLtx(std::ostream &os,const std::string &ud_long,const GEOM_FT &f_long, const std::string &ud_f,const GEOM_FT &f_f) const
  {
    //Se asume que imprimimos en una tabla.
    os << "Point of application: " << getOrg().VectorPos()*f_long << ud_long << "\\\\" << std::endl
       << "Resultant: " << getResultant()*f_f << ud_f << "\\\\" << std::endl 
       << "Moment: " << mom*f_f << ud_f << ud_long << "\\\\" << std::endl;
  }
Vector2d SlidingVectorsSystem2d::getResultant(const Ref2d2d &ref) const
  { return ref.GetCooLocales(getResultant()); } 

SlidingVectorsSystem2d SlidingVectorsSystem2d::reduceTo(const Pos2d &Q)
  { return SlidingVectorsSystem2d(Q,getResultant(),getMoment(Q)); }

SlidingVectorsSystem2d &SlidingVectorsSystem2d::operator+=(const SlidingVector2d &v)
  {
    SlidingVector2d::operator+=(v);
    mom-= v.getMoment(getOrg());
    return *this;
  }
SlidingVectorsSystem2d &SlidingVectorsSystem2d::operator-=(const SlidingVector2d &v)
  {
    SlidingVector2d::operator-=(v);
    mom-= v.getMoment(getOrg());
    return *this;
  }
SlidingVectorsSystem2d &SlidingVectorsSystem2d::operator+=(const SlidingVectorsSystem2d &s)
  //The origin is preserved.
  {
    SlidingVector2d::operator+=(s);
    mom+= s.getMoment(getOrg());
    return *this;
  }
SlidingVectorsSystem2d &SlidingVectorsSystem2d::operator-=(const SlidingVectorsSystem2d &s)
  //The origin is preserved.
  {
    SlidingVector2d::operator-=(s);
    mom-= s.getMoment(getOrg());
    return *this;
  }
SlidingVectorsSystem2d &SlidingVectorsSystem2d::operator*=(const GEOM_FT &d)
  {
    SlidingVector2d::operator*=(d);
    mom*= d;
    return *this;
  }

SlidingVectorsSystem2d operator+(const SlidingVectorsSystem2d &s1,const SlidingVectorsSystem2d &s2)
  {
    SlidingVectorsSystem2d retval(s1);
    retval+=s2;
    return retval;
  }
SlidingVectorsSystem2d operator-(const SlidingVectorsSystem2d &s1,const SlidingVectorsSystem2d &s2)
  {
    SlidingVectorsSystem2d retval(s1);
    retval-=s2;
    return retval;
  }
SlidingVectorsSystem2d operator*(const GEOM_FT &d, const SlidingVectorsSystem2d &s)
  {
    SlidingVectorsSystem2d retval(s);
    return retval*=d;
  }

SlidingVectorsSystem2d operator*(const SlidingVectorsSystem2d &s,const GEOM_FT &d)
  { return d*s; }

SlidingVectorsSystem2d operator+(const SlidingVector2d &v1,const SlidingVector2d &v2)
  {
    SlidingVectorsSystem2d suma(v1);
    suma+=v2;
    return suma;
  }

SlidingVectorsSystem2d operator+(const SlidingVectorsSystem2d &s,const SlidingVector2d &v)
  {
    SlidingVectorsSystem2d suma(s);
    suma+=v;
    return suma;
  }

SlidingVectorsSystem2d operator+(const SlidingVector2d &v,const SlidingVectorsSystem2d &s)
  { return s+v; }

bool SlidingVectorsSystem2d::Nulo(void) const
  {
    bool retval= true;
    if(!SlidingVector2d::Nulo()) retval= false;
    if(mom!=0) retval= false;
    return retval;
  }

void SlidingVectorsSystem2d::Neg(void)
  {
    SlidingVector2d::Neg();
    mom= -mom;
  }

//! @brief Cambia de signo al sliding vector.
SlidingVectorsSystem2d operator-(const SlidingVectorsSystem2d &svd2d)
  {
    SlidingVectorsSystem2d retval(svd2d);
    retval.Neg();
    return retval;
  }

//! @brief Line of points with zero moment.
Line2d SlidingVectorsSystem2d::getZeroMomentLine(void) const
  {
    Line2d retval; //= Line2d(Pos2d(NAN,NAN),Pos2d(NAN,NAN));
    const Vector2d resul= getResultant();
    const GEOM_FT rx= resul.x();
    const GEOM_FT ry= resul.y();
    const GEOM_FT k= rx*getOrg().y()-ry*getOrg().x()-mom; 
    if(rx!=0.0)
      {
	const GEOM_FT xA= 1.0;
	const GEOM_FT yA= (ry*xA+k)/rx;
	const GEOM_FT xB= 1.0e3;
	const GEOM_FT yB= (ry*xB+k)/rx;
        retval= Line2d(Pos2d(xA,yA),Pos2d(xB,yB));
      }
    else if(ry!=0.0)
      {
	const GEOM_FT x= -k/ry;
        retval= Line2d(Pos2d(x,0.0),Pos2d(x,1e3));
      }
    else if(mom==0.0)
      std::clog << getClassName() << "::" << __FUNCTION__
	        << "; all points have zero moment." << std::endl; 
    else
      std::clog << getClassName() << "::" << __FUNCTION__
	        << "; no point has zero moment." << std::endl;
    const Pos2d p= retval.Point();
    const GEOM_FT m= getMoment(p);
    if(abs(m)>1E-6)
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "ERROR in computing zero moment line; "
                << " moment for point: " << p
	        << " m= " << m << " not zero." << std::endl;
    return retval;
  }

std::ostream &operator<<(std::ostream &os, const SlidingVectorsSystem2d &svd2d)
  {
    svd2d.Print(os);
    return os;
  }
