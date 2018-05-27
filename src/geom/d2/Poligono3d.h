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
//Poligono3d.h

#ifndef POLIGONO3D_H
#define POLIGONO3D_H

#include "xc_utils/src/geom/d2/D2to3d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"
#include "../tipos_cgal.h"


//! @ingroup GEOM
//
//! @brief Polígono en tres dimensiones.
class Poligono3d: public D2to3d
  {
    Poligono2d plg2d;

  protected:
    Poligono3d(const Ref2d3d &rf,const Poligono2d &p)
      : D2to3d(rf), plg2d(p) {}

  public:
    Poligono3d(void): D2to3d(),plg2d() {}
    Poligono3d(const Poligono3d &otro)
      :  D2to3d(otro),plg2d(otro.plg2d) {}
    template <typename InputIterator>
    Poligono3d(InputIterator first,InputIterator last);
    Poligono3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Poligono3d &operator =(const Poligono3d &otro) 
      {
	D2to3d::operator=(otro);
        plg2d=otro.plg2d;
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new Poligono3d(*this); }

    inline void push_back(const Pos3d &p)
      { plg2d.push_back(to_2d(p)); }

    inline virtual unsigned int GetNumVertices(void) const
      { return plg2d.GetNumVertices(); }
    inline virtual unsigned int GetNumLados(void) const
      { return plg2d.GetNumLados(); }
    //! @brief Return the length of the object.
    inline GEOM_FT getLength(void) const
      { return plg2d.getLength(); }
    inline GEOM_FT Area(void) const
      { return plg2d.Area(); }
    std::vector<Poligono3d> getPoligonosTributarios(void) const;
    inline std::vector<double> getAreasTributarias(void) const
      { return plg2d.getAreasTributarias(); }
    inline Pos3d Vertice(unsigned int i) const
      //Return the posición del vértice.
      { return to_3d(plg2d.Vertice(i)); }
    inline Pos3d Vertice0(unsigned int j) const
      //Return the posición del vértice de indice j (j=0..GetNumVertices()-1)
      { return to_3d(plg2d.Vertice0(j)); }
    GeomObj::list_Pos3d ListaVertices(void) const;
    Segmento3d Lado0(unsigned int i) const;
    Segmento3d Lado(unsigned int i) const;

    inline bool Horario(void) const
      { return plg2d.Horario(); }
    inline bool Antihorario(void) const
      { return plg2d.Antihorario(); }

    Plano3d GetPlanoLado0(unsigned int i) const;
    Plano3d GetPlanoLado(unsigned int i) const;

    Pos3d getCenterOfMass(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Iz(void) const;

    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    bool In(const Pos3d &p,const double &tol);
    bool TocaCuadrante(const int &) const;

    GEOM_FT distSigno(const Pos3d &p,const bool &sentido_horario= false) const;
    GEOM_FT dist(const Pos3d &p) const;
    GEOM_FT distSigno2(const Pos3d &p,const bool &sentido_horario= false) const;
    GEOM_FT dist2(const Pos3d &p) const;

    std::list<Poligono3d> Corta(const Plano3d &p) const;

    void Print(std::ostream &os) const;
  };

template <typename InputIterator>
Poligono3d::Poligono3d(InputIterator first,InputIterator last)
  : D2to3d(),plg2d()
  {
    InputIterator i= first;
    const Pos3d p1= *i; i++;
    const Pos3d p2= *i; i++;
    const Pos3d p3= *i; i++;
    ThreePoints(p1,p2,p3);
    push_back(p1);
    push_back(p2);
    push_back(p3);
    for(;i!=last;i++)
      push_back(*i);
  }

inline std::list<Poligono3d> corta(const Poligono3d &pol,const Plano3d &pl)
  { return pol.Corta(pl); }

#endif
