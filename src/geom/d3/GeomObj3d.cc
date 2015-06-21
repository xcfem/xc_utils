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
//GeomObj3d.cc

#include "GeomObj3d.h"
#include "BND3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include "../sis_ref/Ref3d3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/matriz_FT.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/base/utils_any.h"

std::deque<SemiEspacio3d> GeomObj3d::interpretaSemiEspacios3d(const std::string &str)
  {
    typedef std::deque<boost::any> dq_objetos;
    const dq_objetos tmp= crea_deque_boost_any(str);
    std::deque<SemiEspacio3d> retval;
    for(dq_objetos::const_iterator i= tmp.begin();i!=tmp.end();i++)
      {
        if(boost_any_is_empty(*i))
          std::cerr << "La expresión '" << str 
                    << "' da como resultado un objeto vacío." << std::endl;
        else
          retval.push_back(convert_to_se3d(*i));
      }
    return retval;
  }

Pos3d GeomObj3d::GetPMax(void) const
  {
    Pos3d p(GetXMax(),GetYMax(),GetZMax());
    return p;
  }
Pos3d GeomObj3d::GetPMin(void) const
  {
    Pos3d p(GetXMin(),GetYMin(),GetZMin());
    return p;
  }

BND3d GeomObj3d::Bnd(void) const
//Devuelve la extension del objeto.
  { return BND3d(GetPMin(),GetPMax()); }

//! @brief Devuelve verdadero si el punto esta sobre el objeto.
bool GeomObj3d::In(const Pos3d &p, const double &tol) const
  {
    std::cerr << "Función 'In', no definida" << std::endl;
    return (BND3d().In(p,tol));
  }

//! @brief Devuelve verdadero si el punto no esta sobre el objeto.
bool GeomObj3d::Out(const Pos3d &p, const double &tol) const
  { return !In(p,tol); }

// Pos3d GeomObj3d::BrazoCdg(void) const
//   { return PesoCdg()*Cdg(); }
GEOM_FT GeomObj3d::I( const unsigned short int &i, const unsigned short int &j) const
  {
    unsigned short int k= i + (j-1)*3;
    switch(k)
      {
	    case 1:
          return Ix();
	    case 2:
	    case 4:
          return Pxy();
	    case 3:
	    case 7:
          return Pxz();
	    case 5:
          return Iy();
	    case 6:
	    case 8:
          return Pyz();
	    case 9:
          return Iz();
	    default:
          return Ix();
      }        
  }

//! @brief Devuelve el momento de inercia respecto al eje que pasa por O
//! con direcci'on la de e.
GEOM_FT GeomObj3d::I(const Pos3d &O,const Vector3d &e) const
  {
    matriz_FT Io= I(O);
    return dot(e,Io*e.GetMatriz())/Abs2(e);
  }

//! @brief Devuelve el momento de inercia respecto a la recta que se pasa
//! como parámetro.
GEOM_FT GeomObj3d::I(const Recta3d &r) const
  { return I(r.Punto(),r.VDir()); }

//! @brief Devuelve el momento de inercia (i,j) respecto eje paralelo al i
//! que pasa por o.
GEOM_FT GeomObj3d::I( const unsigned short int i,
                     const unsigned short int j,
                     const Pos3d &o) const
  {
    const GEOM_FT Iij= I(i,j);
    if(TieneCdg())
      {
        Ref3d3d ejes(Cdg()); //
        Pos3d pos_local= ejes.GetPosLocal(o);
        return Iij + IArea() * pos_local(i) * pos_local(j);
      }
    else
      {
        std::cerr << "El objeto no tiene centro de gravedad." << std::endl;
        return Iij;
      }
  }

//! @brief Devuelve el tensor de inercia respecto al centro de gravedad
//! del objeto.
matriz_FT GeomObj3d::I(void) const
  {
    matriz_FT i(3,3);
    i(1,1)= Ix();i(1,2)= -Pxy();i(1,3)= -Pxz();
    i(2,1)= -Pxy();i(2,2)= Iy();i(2,3)= -Pyz();
    i(3,1)= -Pxz();i(3,2)= -Pyz();i(3,3)= Iz();
    return i;
  }

//! @brief Devuelve el tensor de inercia respector al punto o.
matriz_FT GeomObj3d::I(const Pos3d &o) const
  {
    matriz_FT Ig= I();
    Vector3d og= Cdg() - o;
    GEOM_FT m= IArea();
    return Ig+m*(Abs2(og)*identidad(Ig)-(og & og));
  }

//! @brief Devuelve el momento polar de inercia respecto al punto o.
GEOM_FT GeomObj3d::IO(const Pos3d &o) const
  { return (I(1,1,o)+I(2,2,o)+I(3,3,o))/2; }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
any_const_ptr GeomObj3d::GetProp(const std::string &cod) const
  {
    static GEOM_FT tmp_ft= 0.0;
    if(cod=="cdg")
      {
        tmp_gp_pos3d= Cdg();
        return any_const_ptr(&tmp_gp_pos3d);
      }
    else if(cod=="getXMax")
      {
        tmp_ft= GetXMax();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getYMax")
      {
        tmp_ft= GetYMax();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getZMax")
      {
        tmp_ft= GetZMax();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getXMin")
      {
        tmp_ft= GetXMin();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getYMin")
      {
        tmp_ft= GetYMin();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getZMin")
      {
        tmp_ft= GetZMin();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getIx")
      {
        tmp_ft= Ix();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getIy")
      {
        tmp_ft= Iy();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getIz")
      {
        tmp_ft= Iz();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getPxy")
      {
        tmp_ft= Pxy();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getPxz")
      {
        tmp_ft= Pxz();
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getPyz")
      {
        tmp_ft= Pyz();
        return any_const_ptr(tmp_ft);
      }
    else
      return GeomObj::GetProp(cod);
  }

void GeomObj3d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    os << indent << "\\c{SalvaCmd no implementada}" << std::endl;
  }
// SoGroup *GeomObj3d::Traza(void) const 
//   {
//     std::cerr << "Método Traza() no implementado." << std::endl;
//     return NULL;
//   }
