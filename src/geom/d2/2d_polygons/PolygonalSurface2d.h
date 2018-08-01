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
//PolygonalSurface2D.h

#ifndef POLYGONALSURFACE2D_H
#define POLYGONALSURFACE2D_H

#include "xc_utils/src/geom/d2/Superficie2d.h"

class Line2d;
class Ray2d;
class Segment2d;
class Polygon2d;
class Polyline2d;


//! @ingroup GEOM
//
//! @brief Base class for the polygonal surfaces.
class PolygonalSurface2d: public Superficie2d
  {
  private:
    inline GEOM_FT a_i(unsigned int i) const
      { return Vertice(i).x()*Vertice(i+1).y()-Vertice(i+1).x()*Vertice(i).y(); }
    GEOM_FT moment_sign(const int &p,const int &q) const;
  protected:
    Segment2d Lado0(unsigned int i, unsigned int j) const;
  public:
    PolygonalSurface2d(void): Superficie2d(){}

    virtual GeomObj *clon(void) const= 0;
    inline virtual unsigned int GetNumVertices(void) const
      { return 0; }
    inline virtual unsigned int GetNumLados(void) const
      { return GetNumVertices(); }
    inline bool empty(void) const
      { return (GetNumVertices()<1); }
    virtual Pos2d Vertice(unsigned int i) const= 0;
    //Return el vértice de indice i (i=1..GetNumVertices())
    virtual Pos2d Vertice0(unsigned int j) const= 0;
    //Return el vértice de indice j (j=0..GetNumVertices()-1)
    inline const Pos2d operator()(const size_t &i) const //Offset 1.
      { return Vertice(i); }
    inline const Pos2d operator[](const size_t &j) const //Offset 0.
      { return Vertice0(j); }
    Segment2d Lado(unsigned int i) const;
    Segment2d Lado0(unsigned int i) const;
    GeomObj::list_Pos2d getVertices(void) const;
    Vector2d getLado0Normal(const size_t i) const;
    Vector2d getVertex0Normal(const size_t i) const;
    Polyline2d getPolyline(void) const;
    virtual GEOM_FT getLength(void) const;
    inline GEOM_FT Perimetro(void) const
      { return getLength(); }
    inline GEOM_FT AreaSigno(void) const
      { return moment_sign(0,0); }
    virtual GEOM_FT getArea(void) const;
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual Pos2d getCenterOfMass(void) const;
    virtual Pos2d Centroide(void) const;
    GEOM_FT getMoment(const int &p,const int &q) const;
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;

    GeomObj::list_Pos2d getApproxTangentPositions(const Vector2d &) const;

    GEOM_FT DistSigno(const Pos2d &p,const bool &sentido_horario= false) const;
    GEOM_FT Dist(const Pos2d &p) const;
    inline GEOM_FT GetRecubrimiento(const Pos2d &p) const
      { return -DistSigno(p); }

    bool Overlap(const Line2d &r) const;
    bool Overlap(const Ray2d &sr) const;

    Segment2d Clip(const Line2d &) const;
    Segment2d Clip(const Ray2d &) const;
    Segment2d Clip(const Segment2d &) const;

    
    void Print(std::ostream &os) const;
    void Plot(Plotter &plotter) const;
  };


std::list<Segment2d> intersection(const PolygonalSurface2d &p,const Line2d &r);
std::list<Segment2d> intersection(const Line2d &r,const PolygonalSurface2d &p);

std::list<Segment2d> intersection(const PolygonalSurface2d &p,const Ray2d &sr);
std::list<Segment2d> intersection(const Ray2d &sr,const PolygonalSurface2d &p);

std::list<Segment2d> intersection(const PolygonalSurface2d &p,const Segment2d &sg);
std::list<Segment2d> intersection(const Segment2d &sg,const PolygonalSurface2d &p);

#endif



