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
//SupPoligonal2D.h

#ifndef SUPPOLIGONAL2D_H
#define SUPPOLIGONAL2D_H

#include "xc_utils/src/geom/d2/Superficie2d.h"

class Recta2d;
class SemiRecta2d;
class Segmento2d;
class Poligono2d;
class Polilinea2d;


//! @ingroup GEOM
//
//! @brief Clase base para las superficies poligonales.
class SupPoligonal2d: public Superficie2d
  {
  private:
    inline GEOM_FT a_i(unsigned int i) const
      { return Vertice(i).x()*Vertice(i+1).y()-Vertice(i+1).x()*Vertice(i).y(); }
    GEOM_FT momento_signo(const int &p,const int &q) const;
  protected:
    Segmento2d Lado0(unsigned int i, unsigned int j) const;
  public:
    SupPoligonal2d(void): Superficie2d(){}

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
    Segmento2d Lado(unsigned int i) const;
    Segmento2d Lado0(unsigned int i) const;
    GeomObj::list_Pos2d getVertices(void) const;
    Vector2d getLado0Normal(const size_t i) const;
    Vector2d getVertex0Normal(const size_t i) const;
    Polilinea2d GetPolilinea(void) const;
    virtual GEOM_FT Longitud(void) const;
    inline GEOM_FT Perimetro(void) const
      { return Longitud(); }
    inline GEOM_FT AreaSigno(void) const
      { return momento_signo(0,0); }
    virtual GEOM_FT Area(void) const;
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual Pos2d Cdg(void) const;
    virtual Pos2d Centroide(void) const;
    GEOM_FT Momento(const int &p,const int &q) const;
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;

    GeomObj::list_Pos2d getPosTangAprox(const Vector2d &) const;

    GEOM_FT DistSigno(const Pos2d &p,const bool &sentido_horario= false) const;
    GEOM_FT Dist(const Pos2d &p) const;
    inline GEOM_FT GetRecubrimiento(const Pos2d &p) const
      { return -DistSigno(p); }

    bool Overlap(const Recta2d &r) const;
    bool Overlap(const SemiRecta2d &sr) const;

    Segmento2d Clip(const Recta2d &) const;
    Segmento2d Clip(const SemiRecta2d &) const;
    Segmento2d Clip(const Segmento2d &) const;

    
    void Print(std::ostream &os) const;
    void Plot(Plotter &plotter) const;
  };


std::list<Segmento2d> interseccion(const SupPoligonal2d &p,const Recta2d &r);
std::list<Segmento2d> interseccion(const Recta2d &r,const SupPoligonal2d &p);

std::list<Segmento2d> interseccion(const SupPoligonal2d &p,const SemiRecta2d &sr);
std::list<Segmento2d> interseccion(const SemiRecta2d &sr,const SupPoligonal2d &p);

std::list<Segmento2d> interseccion(const SupPoligonal2d &p,const Segmento2d &sg);
std::list<Segmento2d> interseccion(const Segmento2d &sg,const SupPoligonal2d &p);

#endif



