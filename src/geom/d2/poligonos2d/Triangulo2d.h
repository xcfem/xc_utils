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
//Triangulo2d.h

#ifndef TRIANGULO2D_H
#define TRIANGULO2D_H

#include "SupPoligonal2d.h"
#include "xc_utils/src/geom/tipos_cgal.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_basic/src/util/matem.h"

class Segmento2d;
class Poligono2d;


//! @ingroup GEOM
//
//! @brief Triángulo en dos dimensiones.
class Triangulo2d : public SupPoligonal2d
  {
    CGTriangulo_2 cgtriang;
  public:
    Triangulo2d(void) : SupPoligonal2d(), cgtriang() {}
    Triangulo2d(const Pos2d p1,const Pos2d &p2,const Pos2d &p3)
     : SupPoligonal2d(), cgtriang(p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL())
      {}
    Triangulo2d(const Triangulo2d &otro) : SupPoligonal2d(otro), cgtriang(otro.cgtriang) {}
    Triangulo2d &operator=(const Triangulo2d &p)
      {
	SupPoligonal2d::operator=(p);
        cgtriang= p.cgtriang;
        return *this;
      }
    virtual SupPoligonal2d *clon(void) const
      { return new Triangulo2d(*this); }
    inline virtual unsigned int GetNumVertices(void) const
      { return 3; }
    bool Degenerado(void) const
      { return cgtriang.is_degenerate(); }
    Pos2d Vertice(unsigned int i) const
      { return Vertice0(i-1); }
    Pos2d Vertice0(unsigned int j) const
      { return Pos2d(cgtriang.vertex(j)); }
    Segmento2d Base(const size_t &i) const; //Return la base opuesta al vertice i.
    Segmento2d Altura(const size_t &i) const; //Return la altura del vertice i.
    virtual Pos2d getCenterOfMass(void) const;
    virtual GEOM_FT getLength(void) const;
    virtual GEOM_FT Area(void) const
      { return cgtriang.area(); }
    virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    //! @brief Return true if the point is inside the triangle.
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const
      { return (cgtriang.has_on_positive_side(p.ToCGAL()) || cgtriang.has_on_boundary(p.ToCGAL())); }

    Poligono2d GetPoligono(void) const;

    void Transforma(const Trf2d &trf2d);

    friend int operator ==(const Triangulo2d &a,const Triangulo2d &b)
      { return ( a.cgtriang == b.cgtriang ); };
    inline friend bool intersecan(const Triangulo2d &tr1,const Triangulo2d &tr2)
      { return do_intersect(tr1.cgtriang,tr2.cgtriang); }
    
    void Print(std::ostream &os) const;
    void Plot(Plotter &) const;
  };
#endif



