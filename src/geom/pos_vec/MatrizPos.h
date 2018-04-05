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
//MatrizPos.h
//Matrix of points

#ifndef MATRIZPOS_H
#define MATRIZPOS_H

#include "xc_basic/src/matrices/matrizT.h"
#include "../tipos_cgal.h"
#include "boost/lexical_cast.hpp"
#include "xc_basic/src/util/matem.h"


//! @ingroup GEOM
//
//! @brief Clase base para las matrices de posiciones.
template <class POS>
class MatrizPos: public MatrizT<POS,std::vector<POS> >
  {
  public:
    typedef MatrizT<POS,std::vector<POS> > m_pos;
    typedef typename POS::vector vector;
  protected:
    MatrizPos(const MatrizPos<POS> &mp, size_t &f1, size_t &c1, size_t &f2, size_t &c2)
      : m_pos(mp,f1,c1,f2,c2) {}
  public:
    MatrizPos(const size_t &f=1,const size_t &c=1,const POS &p= POS()): m_pos(f,c,p) {}
    MatrizPos(const POS &p1,const POS &p2,const size_t &num,const GEOM_FT &ratio);
    MatrizPos(const POS &p1,const POS &p2,const size_t &ndiv);
    MatrizPos(const POS &p1,const POS &p2,const std::vector<GEOM_FT> &longs);
    MatrizPos(const POS &p0,const POS &p1,const POS &p2,const size_t &ndiv1,const size_t &ndiv2);
    MatrizPos(const MatrizPos &l1_points,const MatrizPos &l2_points,const MatrizPos &l3_points,const MatrizPos &l4_points);
    inline MatrizPos<POS> GetCaja(size_t f1, size_t c1, size_t f2, size_t c2) const
      { return MatrizPos(*this,f1,c1,f2,c2); }
    inline MatrizPos<POS> GetFila(size_t fila) const
      { return GetCaja(fila,1,fila,this->cls); }
    inline MatrizPos<POS> GetCol(size_t col) const
      { return GetCaja(1,col,this->fls,col); }
  };

//! Build the point matrix between p1 and p2 in such way that, the firs point
//! is p1, the number of point is num and each point is obtained by summing
//! the product of ratio by the p1p2 vector to the previous one.
template <class POS>
MatrizPos<POS>::MatrizPos(const POS &p1,const POS &p2,const size_t &num,const GEOM_FT &ratio)
  : m_pos(num,1)
  {
    POS p(p1);
    const vector v_ratio= ratio * (p2-p1);
    for(size_t i=1;i<=num;i++)
      {
        p= p + v_ratio;
        (*this)(i,1)= p;
      }
  }

//! Build the point matrix between p1 and p2 in such way that, the firs point
//! is p1, the last one is p2 and the intermediate points result from dividing
//! the segment p1p2 in ndiv equal parts. So if ndiv= 1 only the p1 and p2
//! points are created. If ndiv= 2 the midpoint of the segment is created
//! in addition to p1 and p2, and so on...
template <class POS>
MatrizPos<POS>::MatrizPos(const POS &p1,const POS &p2,const size_t &ndiv)
  : m_pos(ndiv+1,1)
  {
    POS p(p1);
    if(ndiv==0)
      (*this)(1,1)= p;
    else
      {
        const GEOM_FT ratio= double_to_FT(1.0/boost::lexical_cast<double>(ndiv));
        const vector v_ratio= ratio * (p2-p1);
        for(size_t i=1;i<=ndiv+1;i++)
          {
            (*this)(i,1)= p;
            p= p + v_ratio;
          }
      }
  }

//! Build the point matrix between p1 and p2 in such way that, the firs point
//! is p1 the last one is p2, the number of points is longs.size()+1 and the
//! lenghts of interior segments are proportional to those in longs.
//!
//!       l[0]     l[1]     l[2]     l[3]     l[4]
//!    *-------+----------+-----+-----------+-----+
//!   p1                                          p2
//!
template <class POS>
MatrizPos<POS>::MatrizPos(const POS &p1,const POS &p2,const std::vector<GEOM_FT> &longs)
  : m_pos(longs.size()+1,1)
  {
    const size_t sz= longs.size();
    const size_t num= sz+1;
    if(num<1)
      {
	std::cerr << "MatrizPos<POS>::MatrizPos; la lista de longitudes está vacía." << std::endl;
        return;
      }
    else
      {
        (*this)(1,1)= p1;
        (*this)(num,1)= p2;
        if(num>1)
          {
            //Normalizamos la lista.
            GEOM_FT denom(0);
            for(std::vector<GEOM_FT>::const_iterator i=longs.begin();i!=longs.end();i++)
              denom+= *i;
            POS p(p1);        
            const vector v= p2-p1;
            for(size_t i=0;i<sz;i++)
              {
                p= p + (longs[i]/denom)*v;
                (*this)(i+2,1)= p;
              }
          }
      }
  }

//! @brief Constructor.
template <class POS>
MatrizPos<POS>::MatrizPos(const POS &p0,const POS &p1,const POS &p2,const size_t &ndiv1,const size_t &ndiv2)
  : m_pos(ndiv1+1,ndiv2+1)
  {
    const GEOM_FT dn1= double_to_FT(1.0/boost::lexical_cast<double>(ndiv1));
    const GEOM_FT dn2= double_to_FT(1.0/boost::lexical_cast<double>(ndiv2));
    const vector v01= (p1-p0)*dn1;
    const vector v02= (p2-p0)*dn2;
    const size_t fls= this->getNumFilas();
    const size_t cls= this->getNumCols();
    for(size_t i=1;i<=fls;i++)
      {
        const vector vi= boost::lexical_cast<int>(i-1)*v02;
        for(size_t j=1;j<=cls;j++)
          (*this)(i,j)= p0+vi+boost::lexical_cast<int>(j-1)*v01;
      }
  }

template <class POS>
MatrizPos<POS>::MatrizPos(const MatrizPos &l1_points,const MatrizPos &l2_points,const MatrizPos &l3_points,const MatrizPos &l4_points)
  : m_pos(l1_points.getNumFilas(),l2_points.getNumFilas())
//The arguments are the points (X) in the following order (see rows).
//                 l3_points
//                  --->
//              X---X---X---X
//            ^ |           | ^
//  l4_points   | X           X | l2_points
//              |           |
//              X---X---X---X
//                  --->
//                 l1_points
//
// and return those points:
//
//              X---X---X---X
//            ^ |   |   |   | 
//            | X---X---X---X
//              |   |   |   |
//              X---X---X---X
//                  --->
//
//The rows are quasi-parallel to the lines l2 and l4
//The columns are quasi-parallel to 11 y l3
  {
    const size_t num_filas= l1_points.getNumFilas();
    const size_t num_cols= l2_points.getNumFilas();
    MatrizPos row_points= l4_points;
    for(size_t i=1;i<=num_filas;i++)
      {
        if(i>1)
          {
            if(i==num_filas)
              row_points= l2_points;
            else
              row_points= MatrizPos(l1_points(i,1),l3_points(i,1),num_cols-1);
          }
        for(size_t j=1;j<=num_cols;j++)
          (*this)(i,j)= row_points(j,1);
      }
  }

template <class POS,class SEG>
POS get_centro(const MatrizPos<POS> &m,const SEG &sg)
  {
    POS retval;
    const size_t nfilas= m.getNumFilas();
    const size_t ncols= m.getNumCols();
    const size_t fila= nfilas/2;
    const size_t columna= ncols/2;
    if(impar(nfilas) && impar(ncols))
      retval= m(fila+1,columna+1);
    else
      if(par(nfilas) && par(ncols))
        {
          SEG s(m(fila,columna),m(fila+1,columna+1));
          retval= s.Cdg();
        }
      else
        if(impar(nfilas))
          {
            SEG s(m(fila,columna),m(fila,columna+1));
            retval= s.Cdg();
          }
        else
          {
            SEG s(m(fila,columna),m(fila+1,columna));
            retval= s.Cdg();
          }
    return retval;
  }

//! @brief Generate point in a quadrilateral (see page IX-16 of the SAP90 manual).
// The arguments are the points (X):
//                        
//            q3             q4
//              X-----------X
//              |           |
//              |           |          
//              |           |
//              X-----------X
//            q1             q2
//                 
// and the number of divisions in directions q1->q2 (ndiv1) and q1->q3 (ndiv2)
// and returns the points:
//
//              X---X---X---X
//            ^ |   |   |   | 
//            | X---X---X---X
//              |   |   |   |
//              X---X---X---X
//                  --->
//
template <class POS>
MatrizPos<POS> cuadrilatero(const POS &q1,const POS &q2,const POS &q3,const POS &q4,const size_t &ndiv1,const size_t &ndiv2)
  {
    const MatrizPos<POS> l1(q1,q2,ndiv1);
    const MatrizPos<POS> l2(q2,q4,ndiv2);
    const MatrizPos<POS> l3(q3,q4,ndiv1);
    const MatrizPos<POS> l4(q1,q3,ndiv2);
    return MatrizPos<POS>(l1,l2,l3,l4);
  }

//! @brief Generate the points by means of the algorithm that SAP90
//! names "frontal generation" (see page IX-18 of the SAP90 manual).
//! The first point of both lists is supposed to be the same.
template <class POS>
MatrizPos<POS> generacion_frontal(const MatrizPos<POS> &l1_points,const MatrizPos<POS> &l2_points)
  {
    const size_t nptos1= l1_points.getNumFilas();
    const size_t nptos2= l2_points.getNumFilas();
    const size_t ntot= nptos1*nptos2;
    MatrizPos<POS> retval(nptos1,nptos2);

    //Points of the first row.
    for(size_t j=1;j<=nptos1;j++)
      retval(1,j)= l1_points(j);
    //Points of the first column.
    for(size_t i=2;i<=nptos1;i++)
      retval(i,1)= l2_points(i);
    
    for(size_t i=2;i<=nptos1;i++)
      {
        const typename MatrizPos<POS>::vector v= retval(i,1)-retval(i-1,1);
        for(size_t j=2;j<=nptos1;j++)
          retval(i,j)= retval(i-1,j)+v;
      }
    return retval;
  }

#endif
