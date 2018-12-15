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
//Grid2d.h

#ifndef Grid2d_h 
#define Grid2d_h 

#include "Surface2d.h"
#include "../pos_vec/Pos2dArray.h"

//! @ingroup GEOM
//
//! @brief Grid in a two-dimensional space.
class Grid2d: public Surface2d
  {
    Pos2dArray points; //!< mesh points
  public:
    Grid2d(void);
    Grid2d(int numSubdivIJ, int numSubdivJK);
    explicit Grid2d(const Pos2dArray &m)
      : Surface2d(), points(m) {}
    virtual ~Grid2d(void);
    virtual GeomObj *clon(void) const
      { return new Grid2d(*this); }

    inline const Pos2d &operator()(const size_t &i,const size_t &j) const
      { return points(i,j); }
    inline Pos2d &operator()(const size_t &i,const size_t &j)
      { return points(i,j); }
    inline Pos2dArray &getPoints(void)
      { return points; }

    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    GEOM_FT getArea(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Pxy(void) const;
    Pos2d getCenterOfMass(void) const;
    const FT_matrix &GetVertCoords(const size_t &,const size_t &) const;
    Pos2d getPoint(const size_t &,const size_t &) const;
    Quadrilateral2d GetQuad(const size_t &i,const size_t &j) const;
    bool In(const Pos2d &, const double &) const;
    
    void Transform(const Trf2d &trf2d);

    void Print(std::ostream &os) const;
  };

#endif

