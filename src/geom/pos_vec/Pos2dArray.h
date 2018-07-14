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
//Pos2dArray

#ifndef POS2DARRAY_H
#define POS2DARRAY_H

#include "Pos2d.h"
#include "PosArray.h"

class Triangle2d;
class Cuadrilatero2d;
class FT_matrix;
class Trf2d;


//! @ingroup GEOM
//
//! @brief Array of positions in a two-dimensional space.
class Pos2dArray: public PosArray<Pos2d>
  {
    friend class Pos2dArray3d;
    typedef PosArray<Pos2d> m_pos;
    Pos2d pos_lagrangiana(const size_t &i,const size_t &j) const;
    GEOM_FT dist_lagrange(void) const;
    GEOM_FT ciclo_lagrange(void);
    
  public:
    Pos2dArray(const size_t &f=1,const size_t &c=1,const Pos2d &p=Pos2d()): m_pos(f,c,p) {}
    Pos2dArray(const Pos2d &p1,const Pos2d &p2,const size_t &num,const GEOM_FT &ratio);
    Pos2dArray(const Pos2d &p1,const Pos2d &p2,const size_t &ndiv);
    Pos2dArray(const Pos2d &p1,const Pos2d &p2,const std::vector<GEOM_FT> &longs);
    Pos2dArray(const Pos2d &p0,const Pos2d &p1,const Pos2d &p2,const size_t &ndiv1,const size_t &ndiv2);
    Pos2dArray(const Pos2dArray &,const Pos2dArray &,const Pos2dArray &,const Pos2dArray &);
 
    size_t GetNumQuads(void) const;
    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    GEOM_FT GetIx(void) const;
    GEOM_FT GetIy(void) const;
    GEOM_FT GetPxy(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Pxy(void) const;
    Pos2d GetCentro(void) const;
    Pos2d getCenterOfMass(void) const;
    GEOM_FT GetArea(void) const;
    Triangle2d getTriangle1(const size_t &i,const size_t &j) const;
    Triangle2d getTriangle2(const size_t &i,const size_t &j) const;
    GEOM_FT GetX(const size_t &,const size_t &) const;
    GEOM_FT GetY(const size_t &,const size_t &) const;
    const FT_matrix &GetVertCoords(const size_t &,const size_t &) const;
    Pos2d getPoint(const size_t &,const size_t &) const;
    Cuadrilatero2d GetQuad(const size_t &i,const size_t &j) const;
    double GetAreaQuad(const size_t &i,const size_t &j) const;
    Pos2d GetCentroideQuad(const size_t &i,const size_t &j) const;
    bool In(const Pos2d &, const double &) const;

    void Transforma(const Trf2d &trf2d);

    GEOM_FT Lagrange(const GEOM_FT &tol);
  };

#endif
