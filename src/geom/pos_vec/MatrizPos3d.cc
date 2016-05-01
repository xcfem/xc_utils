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
//MatrizPos3d.cc

#include "MatrizPos3d.h"
#include "xc_basic/src/util/matem.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d2/Triangulo3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d3/BND3d.h"

#include "xc_utils/src/geom/trf/Trf3d.h"
#include "xc_utils/src/geom/trf/Revolucion3d.h"

//! @brief Constructor.
MatrizPos3d::MatrizPos3d(const MatrizPos<Pos3d> &mp3d)
  : MatrizPos<Pos3d>(mp3d) {}
//! @brief Constructor.
MatrizPos3d::MatrizPos3d(const size_t &f,const size_t &c,const Pos3d &p)
  : MatrizPos<Pos3d>(f,c,p) {}
//! @brief Constructor.
MatrizPos3d::MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const size_t &ndiv)
  : MatrizPos<Pos3d>(p1,p2,ndiv) {}

//! @brief Ver el constructor correspondiente en MatrizPos<POS>.
MatrizPos3d::MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const std::vector<GEOM_FT> &longs)
  : MatrizPos<Pos3d>(p1,p2,longs) {}

//! @brief Constructor.
MatrizPos3d::MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const size_t &num,const GEOM_FT &ratio)
  : MatrizPos<Pos3d>(p1,p2,num,ratio) {}
//! @brief Constructor.
MatrizPos3d::MatrizPos3d(const Pos3d &p0,const Pos3d &p1,const Pos3d &p2,const size_t &ndiv1,const size_t &ndiv2)
  : MatrizPos<Pos3d>(p0,p1,p2,ndiv1,ndiv2) {}

MatrizPos3d::MatrizPos3d(const MatrizPos3d &puntos_l1,const MatrizPos3d &puntos_l2,const MatrizPos3d &puntos_l3,const MatrizPos3d &puntos_l4)
  : MatrizPos<Pos3d>(puntos_l1,puntos_l2,puntos_l3,puntos_l4) {}

MatrizPos3d::MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4,const size_t &ndiv1,const size_t &ndiv2)
  : MatrizPos<Pos3d>(cuadrilatero<Pos3d>(p1,p2,p3,p4,ndiv1,ndiv2)) {}


Pos3d MatrizPos3d::GetCentro(void) const
  { return get_centro(*this,Segmento3d()); }

Pos3d MatrizPos3d::pos_lagrangiana(const size_t &i,const size_t &j) const
  {
    assert(interior(i,j));
    const GEOM_FT x= ((*this)(i-1,j).x()+(*this)(i+1,j).x()+(*this)(i,j-1).x()+(*this)(i,j+1).x())/GEOM_FT(4);
    const GEOM_FT y= ((*this)(i-1,j).y()+(*this)(i+1,j).y()+(*this)(i,j-1).y()+(*this)(i,j+1).y())/GEOM_FT(4);
    const GEOM_FT z= ((*this)(i-1,j).z()+(*this)(i+1,j).z()+(*this)(i,j-1).z()+(*this)(i,j+1).z())/GEOM_FT(4);
    return Pos3d(x,y,z);
  }

//! @brief Devuelve el máximo de las distancias entre los puntos de la malla
//! y los correspondientes de la interpolación de Lagrange (ver pág IX-19 del manual de SAP90).
GEOM_FT MatrizPos3d::dist_lagrange(void) const
  {
    GEOM_FT retval(0.0);
    for(size_t i=2;i<fls;i++) //Puntos interiores.
      for(size_t j=2;j<cls;j++)
        retval= std::max(retval,dist((*this)(i,j),pos_lagrangiana(i,j)));
    return retval;
  }

//! @brief Asigna a los puntos interiores de la malla
//! los correspondientes de la interpolación de Lagrange (ver pág IX-19 del manual de SAP90).
//! Devuelve la distancia máxima obtenida.
GEOM_FT MatrizPos3d::ciclo_lagrange(void)
  {
    for(size_t i=2;i<fls;i++) //Puntos interiores.
      for(size_t j=2;j<cls;j++)
        (*this)(i,j)= pos_lagrangiana(i,j);
    return dist_lagrange();
  }

//! @brief Asigna a los puntos interiores de la malla
//! los correspondientes de la interpolación de Lagrange (ver pág IX-19 del manual de SAP90).
GEOM_FT MatrizPos3d::Lagrange(const GEOM_FT &tol)
  {
    GEOM_FT err= dist_lagrange();
    size_t conta= 0;
    while(err>tol)
      {
        if(conta<10)
          err= ciclo_lagrange();
        else
          {
	    std::cerr << "MatrizPos3d::Lagrange; no se alcanzó la convergencia tras: "
                      << conta << " iteraciones." << std::endl;
            break;
          }
      }
    return err;
  }

//! @brief Aplica a la matriz la transformación que se pasa como parámetro.
void MatrizPos3d::Transforma(const Trf3d &trf)
  { trf.Transforma(*this); }

//! @brief Devuelve la superficie de revolución que se obtiene al aplicar
//! a la matriz la transformación la revolución cuya definición se pasa como parámetro.
MatrizPos3d crea_sup_revolucion(const Revolucion3d &r,const MatrizPos3d &m)
  { return r(m); }

MatrizPos3d cuadrilatero(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4,const size_t &ndiv1,const size_t &ndiv2)
  { return MatrizPos3d(p1,p2,p3,p4,ndiv1,ndiv2); }


//! Devuelve el triángulo inscrito en la malla cuyo vértice inferior izquierdo
//! es el de índices i,j y que queda bajo la diagonal que lo une con
//! el vértice de índices i+1,j+1.
//!                                                                              i+1,j +---+ i+1,j+1
//!                                                                                    |2 /|
//!                                                                                    | / |
//!                                                                                    |/ 1|
//!                                                                                i,j +---+ i,j+1
Triangulo3d MatrizPos3d::GetTriangulo1(const size_t &i,const size_t &j) const
  { return Triangulo3d((*this)(i,j),(*this)(i,j+1),(*this)(i+1,j+1)); }

//! Devuelve el triángulo inscrito en la malla cuyo vértice inferior izquierdo
//! es el de índices i,j y que queda bajo la diagonal que lo une con
//! el vértice de índices i+1,j+1.
//!                                                                              i+1,j +---+ i+1,j+1
//!                                                                                    |2 /|
//!                                                                                    | / |
//!                                                                                    |/ 1|
//!                                                                                i,j +---+ i,j+1
Triangulo3d MatrizPos3d::GetTriangulo2(const size_t &i,const size_t &j) const
  { return Triangulo3d((*this)(i,j),(*this)(i+1,j+1),(*this)(i+1,j)); }


//! @brief Distancia del punto a la superficie definida por la matriz de puntos         i+1,j +---+ i+1,j+1
//! Como el objeto esta formado "aproximadamente" por la unión de triángulos           |2 /|
//! la distancia se calcula como el mínimo de las distancias                           | / |
//! a cada uno de los triángulos.                                                      |/ 1|
//! Cada malla se cubre con dos triángulos                                         i,j +---+ i,j+1
GEOM_FT dist2(const MatrizPos3d &ptos,const Pos3d &pt)
  {
    if(ptos.size()<1) return NAN; //El conjunto está vacío.
    GEOM_FT d= dist2(ptos(1,1),pt);
    if(ptos.size()==1) return d; //La malla degenera en un punto.
    //Distancia a los triángulos.
    const size_t fls= ptos.getNumFilas();
    const size_t cls= ptos.getNumCols();
    if(fls<2) //Solo hay una fila de puntos.
      {
        for(size_t j=1;j<cls;j++) //Hasta la penúltima columna.
          {
            Segmento3d s(ptos(1,j),ptos(1,j+1));
            d= std::min(d,s.dist2(pt));
          }
      }
    if(cls<2) //Solo hay una columna de puntos.
      {
        for(size_t i=1;i<fls;i++) //Hasta la penúltima fila.
          {
            Segmento3d s(ptos(i,1),ptos(i+1,1));
            d= std::min(d,s.dist2(pt));
          }
      }
    for(size_t i=1;i<fls;i++) //Hasta la penúltima fila.
      for(size_t j=1;j<cls;j++) //Hasta la penúltima columna.
        {
          Triangulo3d t1=ptos.GetTriangulo1(i,j); //Primer triángulo.
          d= std::min(d,t1.dist2(pt));
          Triangulo3d t2=ptos.GetTriangulo2(i,j); //Segundo triángulo.
          d= std::min(d,t2.dist2(pt));
        }
    return d;
  }

//! @brief Devuelve verdadero si la distancia del punto a la superficie definida por 
//! la matriz de puntos es menor que la que se pasa como parámetro.
bool dist_menor(const MatrizPos3d &ptos,const Pos3d &pt,const GEOM_FT &d_max)
  {
    const GEOM_FT d_max2(d_max*d_max);
    if(ptos.size()<1) return false; //El conjunto está vacío.
    GEOM_FT d= dist2(ptos(1,1),pt);
    if(ptos.size()==1) //La malla degenera en un punto.
      return (d<d_max2);
    if(d<d_max2) //Ya cumple, el primer punto está suficientemente cerca.
      return true;
    const size_t fls= ptos.getNumFilas();
    const size_t cls= ptos.getNumCols();
    if(fls<2) //Solo hay una fila de puntos.
      {
        for(size_t j=1;j<cls;j++) //Hasta la penúltima columna.
          {
            Segmento3d s(ptos(1,j),ptos(1,j+1));
            d= std::min(d,s.dist2(pt));
            if(d<d_max2)
              return true;
          }
      }
    if(cls<2) //Solo hay una columna de puntos.
      {
        for(size_t i=1;i<fls;i++) //Hasta la penúltima fila.
          {
            Segmento3d s(ptos(i,1),ptos(i+1,1));
            d= std::min(d,s.dist2(pt));
            if(d<d_max2)
              return true;
          }
      }
    //Distancia a los triángulos.
    for(size_t i=1;i<fls;i++) //Hasta la penúltima fila.
      for(size_t j=1;j<cls;j++) //Hasta la penúltima columna.
        {
          Triangulo3d t1=ptos.GetTriangulo1(i,j); //Primer triángulo.
          d= std::min(d,t1.dist2(pt));
          if(d<d_max2)
            return true;
          Triangulo3d t2=ptos.GetTriangulo2(i,j); //Segundo triángulo.
          d= std::min(d,t2.dist2(pt));
          if(d<d_max2)
            return true;
        }
    return (d<d_max2);
  }
//! ! @brief Ver dist2.
GEOM_FT dist(const MatrizPos3d &ptos,const Pos3d &pt)
  { return sqrt_FT(dist2(ptos,pt)); }


//! Máximo de las distancias del punto a cada uno de los planos
//! definidos por los triángulos inscritos en las mallas                         i+1,j +---+ i+1,j+1
//!                                                                                    |2 /|
//!                                                                                    | / |
//!                                                                                    |/ 1|
//!                                                                                i,j +---+ i,j+1
GEOM_FT pseudo_dist2(const MatrizPos3d &ptos,const Pos3d &pt)
  {
    if(ptos.size()<1) return NAN; //El conjunto está vacío.
    GEOM_FT d= dist2(ptos(1,1),pt);
    if(ptos.size()==1) return d; //La malla degenera en un punto.
    //Distancia a los triángulos.
    const size_t fls= ptos.getNumFilas();
    const size_t cls= ptos.getNumCols();
    if(fls<2) //Solo hay una fila de puntos.
      {
        for(size_t j=1;j<cls;j++) //Hasta la penúltima columna.
          {
            Segmento3d s(ptos(1,j),ptos(1,j+1));
            d= std::max(d,s.dist2(pt));
          }
      }
    if(cls<2) //Solo hay una columna de puntos.
      {
        for(size_t i=1;i<fls;i++) //Hasta la penúltima fila.
          {
            Segmento3d s(ptos(i,1),ptos(i+1,1));
            d= std::max(d,s.dist2(pt));
          }
      }
    d= Plano3d(ptos.GetTriangulo1(1,1)).PseudoDist2(pt);
    for(size_t i=1;i<fls;i++) //Hasta la penúltima fila.
      for(size_t j=1;j<cls;j++) //Hasta la penúltima columna.
        {
          Plano3d p1(ptos.GetTriangulo1(i,j)); //Plano del primer triángulo.
          d= std::max(d,p1.PseudoDist2(pt));
          Plano3d p2(ptos.GetTriangulo2(i,j)); //Plano del segundo triángulo.
          d= std::max(d,p2.PseudoDist2(pt));
        }
    return d;
  }

//! @brief Ver pseudo_dist2.
GEOM_FT pseudo_dist(const MatrizPos3d &ptos,const Pos3d &pt)
  { return sqrt_FT(::Abs(pseudo_dist2(ptos,pt))); }

BND3d get_bnd(const MatrizPos3d &ptos)
  {
    BND3d retval;
    if(ptos.size()<1) //El conjunto está vacío.
      {
	std::cerr << "get_bnd; la matriz de puntos está vacia." << std::endl;
        return retval;
      }
    if(ptos.size()<2)
      {
	std::cerr << "La matriz sólo tiene un punto." << std::endl;
        retval= BND3d(ptos(1,1),ptos(1,1));
        return retval;
      }
    retval= BND3d(ptos.front(),ptos.back());
    const size_t fls= ptos.getNumFilas();
    const size_t cls= ptos.getNumCols();
    retval+= ptos(1,1);
    retval+= ptos(fls,1);
    retval+= ptos(1,cls);
    retval+= ptos(fls,cls);
    return retval;
  }
