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
//MatrizPos2d.cc

#include "MatrizPos2d.h"
#include "xc_basic/src/util/matem.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Triangulo2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Cuadrilatero2d.h"
#include "xc_utils/src/geom/matriz_FT.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

//! @brief Ver el constructor correspondiente en MatrizPos<POS>.
MatrizPos2d::MatrizPos2d(const Pos2d &p1,const Pos2d &p2,const size_t &num,const GEOM_FT &ratio)
  : m_pos(p1,p2,num,ratio) {}

//! @brief Ver el constructor correspondiente en MatrizPos<POS>.
MatrizPos2d::MatrizPos2d(const Pos2d &p1,const Pos2d &p2,const size_t &ndiv)
  : m_pos(p1,p2,ndiv) {}

//! @brief Ver el constructor correspondiente en MatrizPos<POS>.
MatrizPos2d::MatrizPos2d(const Pos2d &p1,const Pos2d &p2,const std::vector<GEOM_FT> &longs)
  : m_pos(p1,p2,longs) {}

//! @brief Constructor.
MatrizPos2d::MatrizPos2d(const Pos2d &p0,const Pos2d &p1,const Pos2d &p2,const size_t &ndiv1,const size_t &ndiv2)
  : MatrizPos<Pos2d>(p0,p1,p2,ndiv1,ndiv2) {}

//! @brief Constructor.
MatrizPos2d::MatrizPos2d(const MatrizPos2d &puntos_l1,const MatrizPos2d &puntos_l2,const MatrizPos2d &puntos_l3,const MatrizPos2d &puntos_l4)
  : m_pos(puntos_l1,puntos_l2,puntos_l3,puntos_l4) {}

Pos2d MatrizPos2d::pos_lagrangiana(const size_t &i,const size_t &j) const
  {
    assert(interior(i,j));
    const GEOM_FT x= ((*this)(i-1,j).x()+(*this)(i+1,j).x()+(*this)(i,j-1).x()+(*this)(i,j+1).x())/GEOM_FT(4);
    const GEOM_FT y= ((*this)(i-1,j).y()+(*this)(i+1,j).y()+(*this)(i,j-1).y()+(*this)(i,j+1).y())/GEOM_FT(4);
    return Pos2d(x,y);
  }

//! @brief Devuelve el máximo de las distancias entre los mesh points
//! y los correspondientes de la interpolación de Lagrange (ver pág IX-19 del manual de SAP90).
GEOM_FT MatrizPos2d::dist_lagrange(void) const
  {
    GEOM_FT retval(0.0);
    for(size_t i=2;i<fls;i++) //Puntos interiores.
      for(size_t j=2;j<cls;j++)
        retval= std::max(retval,dist((*this)(i,j),pos_lagrangiana(i,j)));
    return retval;
  }

//! @brief Devuelve el número de cuadriláteross
size_t MatrizPos2d::GetNumQuads(void) const
  { return (fls-1)*(cls-1); }

//! @brief Asigna a los puntos interiores of the mesh
//! los correspondientes de la interpolación de Lagrange (ver pág IX-19 del manual de SAP90).
//! Devuelve la distancia máxima obtenida.
GEOM_FT MatrizPos2d::ciclo_lagrange(void)
  {
    for(size_t i=2;i<fls;i++) //Puntos interiores.
      for(size_t j=2;j<cls;j++)
        (*this)(i,j)= pos_lagrangiana(i,j);
    return dist_lagrange();
  }

//! @brief Asigna a los puntos interiores of the mesh
//! los correspondientes de la interpolación de Lagrange (ver pág IX-19 del manual de SAP90).
GEOM_FT MatrizPos2d::Lagrange(const GEOM_FT &tol)
  {
    GEOM_FT err= dist_lagrange();
    size_t conta= 0;
    while(err>tol)
      {
        if(conta<10)
          err= ciclo_lagrange();
        else
          {
	    std::cerr << "MatrizPos2d::Lagrange; no se alcanzó la convergencia tras: "
                      << conta << " iteraciones." << std::endl;
            break;
          }
      }
    return err;
  }

Pos2d MatrizPos2d::GetCentro(void) const
  { return get_centro(*this,Segmento2d()); }

//! @brief Devuelve el centro de gravedad.
Pos2d MatrizPos2d::GetCdg(void) const
  {
    GEOM_FT areaQuad= 0.0;
    GEOM_FT Atot= 0.0;
    GEOM_FT Qy= 0.0;
    GEOM_FT Qx= 0.0;
    Pos2d c;
    for(size_t i=1;i<fls;i++)
      for(size_t j=1;j<cls;j++)
        {
          areaQuad= GetAreaQuad(i,j);
          c= GetCentroideQuad(i,j);
          Atot+= areaQuad;
          Qx+= c.x()*areaQuad;
          Qy+= c.y()*areaQuad;
        }
    Qx/=Atot;
    Qy/=Atot;
    return Pos2d(Qx,Qy);
  }

//! @brief Devuelve el momento de inercia respecto al paralelo al y por el origen
GEOM_FT MatrizPos2d::GetIy(void) const
  {
    GEOM_FT retval= 0.0;
    Pos2d c;
    Cuadrilatero2d q;
    for(size_t i=1;i<fls;i++)
      for(size_t j=1;j<cls;j++)
        {
          q= GetQuad(i,j);
          c= q.Centroide();
          retval+= q.Iy()+q.Area()*sqr(c.x());
        }
    return retval;
  }

//! @brief Devuelve el momento de inercia respecto al eje paralelo al x por el origen
GEOM_FT MatrizPos2d::GetIx(void) const
  {
    GEOM_FT retval= 0.0;
    Pos2d c;
    Cuadrilatero2d q;
    for(size_t i=1;i<fls;i++)
      for(size_t j=1;j<cls;j++)
        {
          q= GetQuad(i,j);
          c= q.Centroide();
          retval+= q.Ix()+q.Area()*sqr(c.y());
        }
    return retval;
  }

//! @brief Devuelve el producto de inercia respecto a los ejes que pasan por el origen de coordenadas.
GEOM_FT MatrizPos2d::GetPxy(void) const
  {
    GEOM_FT retval= 0.0;
    Pos2d c;
    Cuadrilatero2d q;
    for(size_t i=1;i<fls;i++)
      for(size_t j=1;j<cls;j++)
        {
          q= GetQuad(i,j);
          c= q.Centroide();
          retval+= q.Pxy()+q.Area()*c.x()*c.y();
        }
    return retval;
  }

GEOM_FT MatrizPos2d::GetArea(void) const
  {
    GEOM_FT retval= 0.0;
    for(size_t i=1;i<fls;i++)
      for(size_t j=1;j<cls;j++)
        retval+= GetAreaQuad(i,j);
    return retval;
  }

//! @brief Momento de inercia respecto al eje paralelo al x por el CDG.
GEOM_FT MatrizPos2d::Ix(void) const
  { return GetIx()-GetArea()*sqr(GetCdg().y()); }

//! @brief Momento de inercia respecto al CDG en ejes locales.
GEOM_FT MatrizPos2d::Iy(void) const
  { return GetIy()-GetArea()*sqr(GetCdg().x()); }

//! @brief Producto de inercia respecto al CDG en ejes locales.
GEOM_FT MatrizPos2d::Pxy(void) const
  {
    const GEOM_FT d2= GetCdg().x()*GetCdg().y();
    return GetPxy()-GetArea()*d2;
  }

//! Devuelve el triángulo inscrito in the mesh cuyo vértice inferior izquierdo
//! es el de índices i,j y que queda bajo la diagonal que lo une con
//! el vértice de índices i+1,j+1.
//                                                                             i+1,j +---+ i+1,j+1
//                                                                                   |2 /|
//                                                                                   | / |
//                                                                                   |/ 1|
//                                                                               i,j +---+ i,j+1
Triangulo2d MatrizPos2d::GetTriangulo1(const size_t &i,const size_t &j) const
  { return Triangulo2d((*this)(i,j),(*this)(i,j+1),(*this)(i+1,j+1)); }

//! Devuelve el triángulo inscrito in the mesh cuyo vértice inferior izquierdo
//! es el de índices i,j y que queda bajo la diagonal que lo une con
//! el vértice de índices i+1,j+1.
//                                                                             i+1,j +---+ i+1,j+1
//                                                                                   |2 /|
//                                                                                   | / |
//                                                                                   |/ 1|
//                                                                               i,j +---+ i,j+1
Triangulo2d MatrizPos2d::GetTriangulo2(const size_t &i,const size_t &j) const
  { return Triangulo2d((*this)(i,j),(*this)(i+1,j+1),(*this)(i+1,j)); }


//! @brief Devuelve la coordenada x del punto i,j.
GEOM_FT MatrizPos2d::GetX(const size_t &i,const size_t &j) const
  { return (*this)(i,j).x(); }

//! @brief Devuelve la coordenada y del punto i,j.
GEOM_FT MatrizPos2d::GetY(const size_t &i,const size_t &j) const
  { return (*this)(i,j).y(); }

//! @brief Devuelve las coordenadas del punto i,j.
const matriz_FT &MatrizPos2d::GetVertCoords(const size_t &i,const size_t &j) const
  {
    const Pos2d tmp= GetPunto(i,j);
    static matriz_FT tmp_m(1,2);
    tmp_m(1,1)= tmp.x();
    tmp_m(1,2)= tmp.y();
    return tmp_m;
  }

//! @brief Devuelve el punto i,j.
Pos2d MatrizPos2d::GetPunto(const size_t &i,const size_t &j) const
{ return (*this)(i,j); }


//! @brief Devuelve la el cuadrilátero i,j:
//                                                                             i+1,j +---+ i+1,j+1
//                                                                                   |   |
//                                                                                   |   |
//                                                                                   |   |
//                                                                               i,j +---+ i,j+1
Cuadrilatero2d MatrizPos2d::GetQuad(const size_t &i,const size_t &j) const
  { return Cuadrilatero2d((*this)(i,j),(*this)(i,j+1),(*this)(i+1,j+1),(*this)(i+1,j)); }


bool MatrizPos2d::In(const Pos2d &p, const double &tol) const
  {
    bool retval= false;
    for(size_t i=1;i<fls;i++)
      for(size_t j=1;j<cls;j++)
        if(GetQuad(i,j).In(p,tol))
          {
            retval= true;
            break;
          }
    return retval;
  }

//! @brief Devuelve el área del cuadrilátero i,j:
//                                                                             i+1,j +---+ i+1,j+1
//                                                                                   |   |
//                                                                                   |   |
//                                                                                   |   |
//                                                                               i,j +---+ i,j+1
GEOM_FT MatrizPos2d::GetAreaQuad(const size_t &i,const size_t &j) const
  { return GetQuad(i,j).Area(); }

//! @brief Devuelve el centroide del cuadrilátero i,j:
//                                                                             i+1,j +---+ i+1,j+1
//                                                                                   |   |
//                                                                                   |   |
//                                                                                   |   |
//                                                                               i,j +---+ i,j+1
Pos2d MatrizPos2d::GetCentroideQuad(const size_t &i,const size_t &j) const
  { return GetQuad(i,j).Centroide(); }

//! @brief Devuelve el valor maximo de la coordenada k.
GEOM_FT MatrizPos2d::GetMax(unsigned short int k) const
  {
    register GEOM_FT mx= (*this)(1,1)(k);
    for(size_t i=1;i<=fls;i++)
      for(size_t j=1;j<=cls;j++)
        mx= std::max((*this)(i,j)(k),mx);
    return mx;
  }

//! @brief Devuelve el valor minimo de la coordenada k.
GEOM_FT MatrizPos2d::GetMin(unsigned short int k) const
  {
    register GEOM_FT mn= (*this)(1,1)(k);
    for(size_t i=1;i<=fls;i++)
      for(size_t j=1;j<=cls;j++)
        mn= std::min((*this)(i,j)(k),mn);
    return mn;
  }

//! @brief Aplica a los puntos la transformación que se
//! pasa como parámetro.
void MatrizPos2d::Transforma(const Trf2d &trf2d)
  {
    for(size_t i=1;i<=fls;i++)
      for(size_t j=1;j<=cls;j++)
        (*this)(i,j)= trf2d.Transforma((*this)(i,j));
  }
