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
//SectorAnilloCircular2d.cc

#include "SectorAnilloCircular2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"

#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"


//! @brief Construye el círculo a partir del centro and el radio.
SectorAnilloCircular2d::SectorAnilloCircular2d(const SectorCircular2d &c,const double &r)
  : SectorCircular2d(c), rint(r) {}

//! @brief Return the posición del centro de gravedad del sector circular.
Pos2d SectorAnilloCircular2d::getCenterOfMass(void) const
  {
    std::cerr << "SectorAnilloCircular2d::getCenterOfMass() not implemented." << std::endl;
    return Centro();
  }

//! @brief Return un sector circular con el mismo centro and ángulos and otro radio
SectorCircular2d SectorAnilloCircular2d::getSector(const double &R) const
  { return SectorCircular2d(Circulo2d(Centro(),R),Theta1(),Theta2()); }

//! @brief Return el sector circular interior a éste.
SectorCircular2d SectorAnilloCircular2d::SectorInterior(void) const
  { return getSector(rint); }


//! @brief Return the point inicial del arco exterior.
Pos2d SectorAnilloCircular2d::PInicExt(void) const
  { return SectorCircular2d::PInic(); }

//! @brief Return the point final del arco exterior.
Pos2d SectorAnilloCircular2d::PFinExt(void) const
  { return SectorCircular2d::PFin(); }

//! @brief Return the point inicial del arco interior.
Pos2d SectorAnilloCircular2d::PInicInt(void) const
  { return SectorInterior().PInic(); }

//! @brief Return the point final del arco interior.
Pos2d SectorAnilloCircular2d::PFinInt(void) const
  { return SectorInterior().PFin(); }


//! @brief Return the point medio del arco exterior.
Pos2d SectorAnilloCircular2d::PMedExt(void) const
  { return SectorCircular2d::PMed(); }

//! @brief Return the point medio del arco interior.
Pos2d SectorAnilloCircular2d::PMedInt(void) const
  { return SectorInterior().PMed(); }

//! @brief Return the length of the arco exterior del sector de anillo circular.
GEOM_FT SectorAnilloCircular2d::getExteriorArcLength(void) const
  { return double_to_FT(AnguloComprendido())*RadioExt(); }

//! @brief Return the length of the arco interior del sector de anillo circular.
GEOM_FT SectorAnilloCircular2d::getInteriorArcLength(void) const
  { return double_to_FT(AnguloComprendido())*RadioInt(); }

//! @brief Return the length of the object.
GEOM_FT SectorAnilloCircular2d::getLength(void) const
  { return getExteriorArcLength()+getInteriorArcLength()+2*(RadioExt()-RadioInt()); }

//! @brief Return the area of the object.
GEOM_FT SectorAnilloCircular2d::getArea(void) const
  { return SectorCircular2d::getArea()-SectorInterior().getArea(); }

//! @brief Return the maximum value of the i coordinate of the object points.
GEOM_FT SectorAnilloCircular2d::GetMax(unsigned short int i) const
  {
    std::cerr << "SectorAnilloCircular2d::GetMax() not implemented." << std::endl;
    return 0;
  }
//! @brief Return el valor mínimo of the i coordinate of the object points.
GEOM_FT SectorAnilloCircular2d::GetMin(unsigned short int i) const
  {
    std::cerr << "SectorAnilloCircular2d::GetMin() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el moment of inertia del sector circular with respect to 
//! axis parallel to x que pasa por su centro.
GEOM_FT SectorAnilloCircular2d::Ix(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Ix() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el moment of inertia del sector circular with respect to 
//! axis parallel to y que pasa por su centro.
GEOM_FT SectorAnilloCircular2d::Iy(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Iy() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el moment of inertia del sector circular with respect to 
//! axis parallel to z que pasa por su centro.
GEOM_FT SectorAnilloCircular2d::Iz(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Iz() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el product of inertia del sector circular with respect to
//! the axis parallel to x e y que pasan por su centro.
GEOM_FT SectorAnilloCircular2d::Pxy(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Pxy() not implemented." << std::endl;
    return 0;
  }

//! @brief Return true if the point is inside the object.
bool SectorAnilloCircular2d::In(const Pos2d &p, const double &tol) const
  {
    if(SectorCircular2d::In(p,tol))
      {
        return !(SectorInterior().In(p,tol)); //XXX ¿tol?
      }
    else
      return false;
  }

MatrizPos2d SectorAnilloCircular2d::getExtArcPoints(const size_t &n) const
  { return SectorCircular2d::getArcPoints(n); }

MatrizPos2d SectorAnilloCircular2d::getIntArcPoints(const size_t &n) const
  { return SectorInterior().getArcPoints(n); }

//! @brief Return n points equally spaced over the object perimeter.
MatrizPos2d SectorAnilloCircular2d::getPointsOnPerimeter(const size_t &n) const
  {
    MatrizPos2d retval;
    if(n>3)
      {
        retval= MatrizPos2d(n,2);
        if(n==4)
          {
            retval(1,2)= PInicExt(); //Initial and final points
            retval(n,2)= PFinExt();
            retval(1,1)= PInicInt(); //Initial and final points
            retval(n,1)= PFinInt();
          }
        else
          {
            retval.PutCol(2,getExtArcPoints(n));
            retval.PutCol(1,getIntArcPoints(n));
          }
      }
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
		<< "; number of points must be greater or equal to four."
		<< std::endl;
    return retval;
  }
//! @brief Returns a point mesh equiespaciados sobre el sector del anillo circular.
MatrizPos2d SectorAnilloCircular2d::genMesh(const size_t &nDivRad,const size_t &nDivCirc) const
  {
    MatrizPos2d retval(nDivCirc+1,nDivRad+1);
    if(nDivRad>0  && nDivCirc>0)
      {
        const double deltaRad= (RadioExt() - RadioInt())/nDivRad;

        double rad_j= RadioInt();
        for(size_t j= 0;j<nDivRad+1;j++)
          {
            MatrizPos2d tmp= getSector(rad_j).getArcPoints(nDivCirc+1);
            retval.PutCol(j+1,tmp);
            rad_j+= deltaRad;
          }
      }
    return retval;
  }

Poligono2d SectorAnilloCircular2d::getPoligono2d(const size_t &n) const
  {
    Poligono2d retval;
    MatrizPos2d ptos= getPointsOnPerimeter(n);
    for(size_t i=1;i<=n;i++)
      retval.push_back(ptos(i,2));
    for(size_t i=n;i>0;i--)
      retval.push_back(ptos(i,1));
    return retval;
  }

void SectorAnilloCircular2d::Print(std::ostream &os) const
  {
    SectorCircular2d::Print(os);
    os << " rint= " << rint;
  }

bool operator==(const SectorAnilloCircular2d &a,const SectorAnilloCircular2d &b)
  {
    if((const SectorCircular2d &)(a) == (const SectorCircular2d &)(b))
      return ( (a.Theta1() == b.Theta1()) && (a.Theta2() == b.Theta2()));
   else
     return false;
  }
