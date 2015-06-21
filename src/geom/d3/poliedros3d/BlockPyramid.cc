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
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "xc_utils/src/base/utils_any.h"

//! @brief Devuelve el haz de vectores que resulta de intersecar los
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

//! @brief Devuelve verdadero si el vector está orientado hacia
//! dentro del semiespacio.
bool BlockPyramid::es_interior(const SemiEspacio3d &se,const Vector3d &v)
  {
    const Pos3d p= se.getPlano().Punto()+1e4*v;
    const bool retval= se.In(p,1e-4);
    return retval;
  }

//! @brief Devuelve verdadero si el vector está orientado hacia
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

//! @brief Interpreta comandos del objeto.
bool BlockPyramid::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string str_msg= "(BlockPyramid) Procesando comando: "+cmd;
    if(verborrea>2)
      std::clog << str_msg << std::endl;
    if(cmd == "semiespacios")
      {
        const std::deque<SemiEspacio3d> se= interpretaSemiEspacios3d(status.GetBloque());
        for(std::deque<SemiEspacio3d>::const_iterator i=se.begin();i!=se.end();i++)
          semiespacios.push_back(*i);
        return true;
      }
    else
      return GeomObj3d::procesa_comando(status);
  }

//! @brief Devuelve la longitud del objeto.
GEOM_FT BlockPyramid::Longitud(void) const
  {
    std::cerr << "BlockPyramid::Longitud() no implementada." << std::endl;
    return 0.0;
  }

//! @brief Devuelve el área del objeto.
GEOM_FT BlockPyramid::Area(void) const
  {
    std::cerr << "BlockPyramid::Area() no implementada." << std::endl;
    return 0.0;
  }

//! @brief Devuelve el volumen del objeto.
GEOM_FT BlockPyramid::Volumen(void) const
  {
    std::cerr << "BlockPyramid::Volumen() no implementada." << std::endl;
    return 0.0;
  }

//! @brief Devuelve el momento de inercia respecto al eje x.
GEOM_FT BlockPyramid::Ix(void) const
  {
    std::cerr << "BlockPyramid::Ix() no implementado." << std::endl;
    return 0.0;
  }

//! @brief Devuelve el momento de inercia respecto al eje y.
GEOM_FT BlockPyramid::Iy(void) const
  {
    std::cerr << "BlockPyramid::Iy() no implementado." << std::endl;
    return 0.0;
  }

//! @brief Devuelve el momento de inercia respecto al eje z.
GEOM_FT BlockPyramid::Iz(void) const
  {
    std::cerr << "BlockPyramid::Iy() no implementado." << std::endl;
    return 0.0;
  }

//! @brief Devuelve la posición del centro de gravedad.
Pos3d BlockPyramid::Cdg(void) const
  {
    std::cerr << "BlockPyramid::Cdg() no implementado." << std::endl;
    return Pos3d();
  }

GEOM_FT BlockPyramid::GetMax(unsigned short int i) const
  {
    std::cerr << "BlockPyramid::GetMax() no implementado." << std::endl;
    return 0.0;
  }
GEOM_FT BlockPyramid::GetMin(unsigned short int i) const
  {
    std::cerr << "BlockPyramid::GetMin() no implementado." << std::endl;
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

Vector2d BlockPyramid::getVectorExterno1(const Ref2d3d &planoProy) const
  {
    const std::deque<Vector3d> haz= haz_vectores_interiores();
    Vector2d retval;
    if(!haz.empty())
      {
        std::deque<Vector3d>::const_iterator i= haz.begin();
        retval= planoProy.GetCooLocales(*i);
        double angulo= retval.AnguloEjeX();
        i++;
        for(;i!=haz.end();i++)
          {
            const Vector2d tmpV= planoProy.GetCooLocales(*i);
            const double tmpAng= tmpV.AnguloEjeX();
            if(tmpAng<angulo)
              {
                retval= tmpV;
                angulo= tmpAng;
              }
          }
      }
    else
      std::cerr << "BlockPyramid::getVectorExterno1 "
                << " no hay vectores externos." << std::endl;
    return retval;
  }

Vector2d BlockPyramid::getVectorExterno2(const Ref2d3d &planoProy) const
  {
    const std::deque<Vector3d> haz= haz_vectores_interiores();
    Vector2d retval;
    if(!haz.empty())
      {
        std::deque<Vector3d>::const_iterator i= haz.begin();
        retval= planoProy.GetCooLocales(*i);
        double angulo= retval.AnguloEjeX();
        i++;
        for(;i!=haz.end();i++)
          {
            const Vector2d tmpV= planoProy.GetCooLocales(*i);
            const double tmpAng= tmpV.AnguloEjeX();
            if(tmpAng>angulo)
              {
                retval= tmpV;
                angulo= tmpAng;
              }
          }
      }
    else
      std::cerr << "BlockPyramid::getVectorExterno2 "
                << " no hay vectores externos." << std::endl;
    return retval;
  }

//! @brief Devuelve los pares de vectores externos de la
//! proyección de la pirámide.
//! a: Define la dirección de proyección (eje del túnel).
std::deque<Vector2d> BlockPyramid::getVectoresExternos(const Ref2d3d &a) const
  {
    std::deque<Vector2d> retval;
    retval.push_back(getVectorExterno1(a));
    retval.push_back(getVectorExterno2(a));
    if(retval.size()>1)
      if(retval[0]==retval[1])
        std::cerr << "BlockPyramid::getVectoresExternos "
                << " sólo se encontró un vector de borde." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si no tiene bordes.
bool BlockPyramid::Vacio(void) const
  {
    const std::deque<Vector3d> haz= haz_vectores_interiores();
    return haz.empty();
  }

//! @brief Devuelve la propiedad cuyo código se pasa
//! como parámetro.
any_const_ptr BlockPyramid::GetProp(const std::string &cod) const
  {
    if(cod=="getVectoresBorde")
      {
        tmp_gp_mdbl= getVectoresBorde();
        return any_const_ptr(tmp_gp_mdbl);
      }
    else if(cod=="getVectoresBorde")
      {
        tmp_gp_mdbl= getVectoresBorde();
        return any_const_ptr(tmp_gp_mdbl);
      }
    else if(cod=="getVectorExterno1")
      {
        const Ref2d3d ref= popRef2d3d(cod);
        tmp_gp_vector2d= getVectorExterno1(ref);
        return any_const_ptr(tmp_gp_vector2d);
      }
    else if(cod=="getVectorExterno2")
      {
        const Ref2d3d ref= popRef2d3d(cod);
        tmp_gp_vector2d= getVectorExterno2(ref);
        return any_const_ptr(tmp_gp_vector2d);
      }
    else if(cod=="esInterior")
      {
        const Vector3d v= popVector3d(cod);
        tmp_gp_bool= es_interior(v);
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod=="Vacio")
      {
        tmp_gp_bool= Vacio();
        return any_const_ptr(tmp_gp_bool);
      }
    else
      return GeomObj3d::GetProp(cod);
  }

//! @brief Imprime el objeto.
void BlockPyramid::Print(std::ostream &os) const
  {}


