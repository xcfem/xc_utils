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
//BlockPyramid3c.cc

#include "BlockPyramid.h"

#include "xc_utils/src/geom/d1/Recta3d.h"

#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"


//! @brief Return el haz de vectores que resulta de intersecar los
//! semiespacios 2 a 2.
std::deque<Vector3d> BlockPyramid::haz_vectores(void) const
  {
    std::deque<Vector3d> retval;
    const std::deque<Vector3d> normales= vectores_normales(semiespacios);
    const size_t sz= normales.size();
    for(size_t i=0;i<sz;i++)
      for(size_t j=i+1;j<sz;j++)
        {
          const Vector3d v= cross(normales[i],normales[j]);
          retval.push_back(v);
          retval.push_back(-v);
        }
    return retval;
  }

//! @brief Return true if el vector está orientado hacia
//! dentro del semiespacio.
bool BlockPyramid::es_interior(const SemiEspacio3d &se,const Vector3d &v)
  {
    const Pos3d p= se.getPlane().Point()+1e4*v;
    const bool retval= se.In(p,1e-4);
    return retval;
  }

//! @brief Return true if el vector está orientado hacia
//! dentro de todos y cada uno de los semiespacios.
bool BlockPyramid::es_interior(const Vector3d &v) const
  {
    bool retval= true;
    for(std::deque<SemiEspacio3d>::const_iterator j=semiespacios.begin();j!=semiespacios.end();j++)
      {
        if(!es_interior(*j,v))
          {
            retval= false;
            break;
          }
      }
    return retval;
  }

//! @brief Del haz de vectores que resulta de intersecar los
//! semiespacios 2 a 2, devuelve aquellos que son interiores a
//! todos los semiespacios.
std::deque<Vector3d> BlockPyramid::haz_vectores_interiores(void) const
  {
    std::deque<Vector3d> retval;
    const std::deque<Vector3d> haz= haz_vectores();
    for(std::deque<Vector3d>::const_iterator i= haz.begin();i!=haz.end();i++)
      if(es_interior(*i))
        retval.push_back(*i);
    return retval;
  }

//! @brief Constructor por defecto.
BlockPyramid::BlockPyramid(void)
  : GeomObj3d() {}

//! @brief Constructor.
BlockPyramid::BlockPyramid(const std::deque<SemiEspacio3d> &se)
  : GeomObj3d(), semiespacios(se) {}

//! @brief Return the object length.
GEOM_FT BlockPyramid::getLength(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented." << std::endl;
    return 0.0;
  }

//! @brief Return the area of the object surface.
GEOM_FT BlockPyramid::getArea(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }

//! @brief Return the volume of the object.
GEOM_FT BlockPyramid::getVolume(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }

//! @brief Return the moment of inertia with respect to the x axis.
GEOM_FT BlockPyramid::Ix(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }

//! @brief Return the moment of inertia with respect to the y axis.
GEOM_FT BlockPyramid::Iy(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }

//! @brief Return the moment of inertia with respect to the z axis.
GEOM_FT BlockPyramid::Iz(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }

//! @brief Return the posición del centro de gravedad.
Pos3d BlockPyramid::getCenterOfMass(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return Pos3d();
  }

GEOM_FT BlockPyramid::GetMax(unsigned short int i) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }
GEOM_FT BlockPyramid::GetMin(unsigned short int i) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }

m_double BlockPyramid::getVectoresBorde(void) const
  {
    const std::deque<Vector3d> haz= haz_vectores_interiores();
    m_double retval;
    if(!haz.empty())
      {
        const size_t sz= haz.size();
        retval= m_double(sz,3);
        size_t conta= 1;
        for(std::deque<Vector3d>::const_iterator i= haz.begin();i!=haz.end();i++,conta++)
          { retval(conta,1)= i->x(); retval(conta,2)= i->y(); retval(conta,3)= i->z(); }
      }
    return retval;
  }

Vector2d BlockPyramid::getVectorExterno1(const Ref2d3d &projPlane) const
  {
    const std::deque<Vector3d> haz= haz_vectores_interiores();
    Vector2d retval;
    if(!haz.empty())
      {
        std::deque<Vector3d>::const_iterator i= haz.begin();
        retval= projPlane.GetCooLocales(*i);
        double angle= retval.XAxisAngle();
        i++;
        for(;i!=haz.end();i++)
          {
            const Vector2d tmpV= projPlane.GetCooLocales(*i);
            const double tmpAng= tmpV.XAxisAngle();
            if(tmpAng<angle)
              {
                retval= tmpV;
                angle= tmpAng;
              }
          }
      }
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
                << " no hay vectores externos." << std::endl;
    return retval;
  }

Vector2d BlockPyramid::getVectorExterno2(const Ref2d3d &projPlane) const
  {
    const std::deque<Vector3d> haz= haz_vectores_interiores();
    Vector2d retval;
    if(!haz.empty())
      {
        std::deque<Vector3d>::const_iterator i= haz.begin();
        retval= projPlane.GetCooLocales(*i);
        double angle= retval.XAxisAngle();
        i++;
        for(;i!=haz.end();i++)
          {
            const Vector2d tmpV= projPlane.GetCooLocales(*i);
            const double tmpAng= tmpV.XAxisAngle();
            if(tmpAng>angle)
              {
                retval= tmpV;
                angle= tmpAng;
              }
          }
      }
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
                << " no hay vectores externos." << std::endl;
    return retval;
  }

//! @brief Return the pairs of external vectors of the
//! projected pyramid.
//! a: Return the projection direction (tunnel axis).
std::deque<Vector2d> BlockPyramid::getVectoresExternos(const Ref2d3d &a) const
  {
    std::deque<Vector2d> retval;
    retval.push_back(getVectorExterno1(a));
    retval.push_back(getVectorExterno2(a));
    if(retval.size()>1)
      if(retval[0]==retval[1])
        std::cerr << getClassName() << "::" << __FUNCTION__
                  << "; sólo se encontró un vector de borde."
		  << std::endl;
    return retval;
  }

//! @brief Return true if has no borders.
bool BlockPyramid::Vacio(void) const
  {
    const std::deque<Vector3d> haz= haz_vectores_interiores();
    return haz.empty();
  }

//! @brief Print stuff.
void BlockPyramid::Print(std::ostream &os) const
  {}


