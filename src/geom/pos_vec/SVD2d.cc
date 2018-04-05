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
//SVD2D.cc

#include "SVD2d.h"
#include "VDesliz2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"



SVD2d::SVD2d(const VDesliz2d &v)
  : org(v.getOrg()), resul(v),mom(0.0) {}

//! @brief Return the moment about P.
GEOM_FT SVD2d::getMomento(const Pos2d &P) const
  {
    VDesliz2d R(org,resul);
    return mom+R.Momento(P);
  }

void SVD2d::Print(std::ostream &os) const
  {
    os << "Resultante R=" << resul
       << " , momento respecto a " << org << " Mo= " << mom; 
  }

void SVD2d::PrintLtx(std::ostream &os,const std::string &ud_long,const GEOM_FT &f_long, const std::string &ud_f,const GEOM_FT &f_f) const
  {
    //Se asume que imprimimos en una tabla.
    os << "Point of application: " << org.VectorPos()*f_long << ud_long << "\\\\" << std::endl
       << "Resultant: " << resul*f_f << ud_f << "\\\\" << std::endl 
       << "Moment: " << mom*f_f << ud_f << ud_long << "\\\\" << std::endl;
  }
Vector2d SVD2d::getResultante(const Ref2d2d &ref) const
  { return ref.GetCooLocales(resul); } 

SVD2d SVD2d::ReduceA(const Pos2d &Q)
  { return SVD2d(Q,resul,getMomento(Q)); }

SVD2d &SVD2d::operator+=(const VDesliz2d &v)
  {
    resul= resul+v;
    mom= mom + v.Momento(org);
    return *this;
  }
SVD2d &SVD2d::operator-=(const VDesliz2d &v)
  {
    resul= resul - v;
    mom= mom - v.Momento(org);
    return *this;
  }
SVD2d &SVD2d::operator+=(const SVD2d &s)
  //The origin is preserved.
  {
    resul= resul + s.resul;
    mom= mom + s.getMomento(org);
    return *this;
  }
SVD2d &SVD2d::operator-=(const SVD2d &s)
  //The origin is preserved.
  {
    resul= resul - s.resul;
    mom= mom - s.getMomento(org);
    return *this;
  }
SVD2d &SVD2d::operator*=(const GEOM_FT &d)
  {
    resul= resul * d;
    mom= mom * d;
    return *this;
  }

bool SVD2d::Nulo(void) const
  {
    bool retval= true;
    if(!resul.Nulo()) retval= false;
    if(mom!=0) retval= false;
    return retval;
  }

//! @brief Line of points with zero moment.
Recta2d SVD2d::RectaMomNulo(void) const
  {
    Recta2d retval; //= Recta2d(Pos2d(NAN,NAN),Pos2d(NAN,NAN));
    const GEOM_FT rx= resul.x();
    const GEOM_FT ry= resul.y();
    const GEOM_FT k= rx*org.y()-ry*org.x()-mom; 
    if(rx!=0.0)
      {
	const GEOM_FT xA= 1.0;
	const GEOM_FT yA= (ry*xA+k)/rx;
	const GEOM_FT xB= 1.0e3;
	const GEOM_FT yB= (ry*xB+k)/rx;
        retval= Recta2d(Pos2d(xA,yA),Pos2d(xB,yB));
      }
    else if(ry!=0.0)
      {
	const GEOM_FT x= -k/ry;
        retval= Recta2d(Pos2d(x,0.0),Pos2d(x,1e3));
      }
    else if(mom==0.0)
      std::clog << getClassName() << "::" << __FUNCTION__
	        << "; all points have zero moment." << std::endl; 
    else
      std::clog << getClassName() << "::" << __FUNCTION__
	        << "; no point has zero moment." << std::endl;
    const Pos2d p= retval.Point();
    const GEOM_FT m= getMomento(p);
    if(abs(m)>1E-6)
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "ERROR in computing zero moment line; "
                << " moment for point: " << p
	        << " m= " << m << " not zero." << std::endl;
    return retval;
  }

