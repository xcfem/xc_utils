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
//Polilinea2d.

#ifndef POLILINEA2D_H
#define POLILINEA2D_H

#include "../pos_vec/Pos2d.h"
#include "Linea2d.h"

class Segmento2d;
class SemiRecta2d;
class Recta2d;
class ListaPos2d;

//! @ingroup GEOM
//
//! @brief Polilínea en dos dimensiones.
class Polilinea2d : public Linea2d, public GeomObj::list_Pos2d
  {
  public:
    Polilinea2d(void);
    explicit Polilinea2d(const GeomObj::list_Pos2d &);
    explicit Polilinea2d(const ListaPos2d &);

    virtual GeomObj *clon(void) const
      { return new Polilinea2d(*this); }
    const GeomObj::list_Pos2d &getVertices(void) const
      { return *this; }
    inline size_t GetNumVertices(void) const
      { return GeomObj::list_Pos2d::size(); }
    size_t GetNumSegmentos(void) const;
    inline const_iterator vertices_begin(void) const
      { return GeomObj::list_Pos2d::begin(); }
    const const_iterator vertices_end(void) const
      { return GeomObj::list_Pos2d::end(); }

    void Transforma(const Trf2d &trf2d);
    
/*     inline virtual void GiraX(double ang) */
/*       { Ref2d::GiraX(ang); TrfPoints(); } */
/*     inline virtual void GiraY(double ang) */
/*       { Ref2d::GiraY(ang); TrfPoints();  } */
/*     inline virtual void GiraZ(double ang) */
/*       { Ref2d::GiraZ(ang); TrfPoints();  } */
    const Pos2d *AgregaVertice(const Pos2d &p);
    template <class InputIterator>
    inline void assign(InputIterator first,
                       InputIterator last)
      //Inserta los vértices comprendidos en [first,last) antes
      //antes del vértice al que se refiere i.
      { GeomObj::list_Pos2d::assign(first,last); }
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;

    //Producto de inercia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    virtual GEOM_FT Longitud(void) const
    //Return the longitud de la Polilinea2d.
      { return GeomObj::list_Pos2d::Longitud(); }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    //Return the maximum value of the i coordinate.
    virtual GEOM_FT GetMin(unsigned short int i) const;
    //Return the minimum value of the i coordinate.
    Polilinea2d GetMayores(unsigned short int i,const GEOM_FT &d) const;
    //Devuelve una Polilinea2d con los vertices cuya coordenada i
    //es mayor que d.
    Polilinea2d GetMenores(unsigned short int i,const GEOM_FT &d) const;
    //Devuelve una Polilinea2d con los vertices cuya coordenada i
    //es menor que d.
    const Pos2d &Vertice(const size_t &i) const;
    Segmento2d GetSegmento(const const_iterator &i) const;
    Segmento2d GetSegmento(const size_t &i) const;
/*     virtual list_Pos2d Int(unsigned short int i, const double d) const */
/*       { */
/*         cerr << "Polilinea2d Int(i,d) not implemented" << endl; */
/*         return list_Pos2d(); */
/*       } */
    Polilinea2d Offset(const GEOM_FT &d) const;
    list_Pos2d Int(unsigned short int i,const GEOM_FT &d) const;
    //Devuelve las intersecciones de la Polilinea2d con la recta
    //coord_i= d
    list_Pos2d Interseccion(const Recta2d &r) const;
    list_Pos2d Interseccion(const SemiRecta2d &sr) const;
    list_Pos2d Interseccion(const Segmento2d &sr) const;
    Polilinea2d Corta(unsigned short int i,const GEOM_FT &d) const;
    //Return the Polilinea2d con los vertices correspondientes a los
    //cortes con el plano coord_i= d
    Polilinea2d Separa(const Pos2d &p,const short int &sgn) const;
    //Suponemos que p es vertice de la Polilinea2d
    //Devuelve el trozo de Polilinea2d:
    //hasta p si sgn < 0
    //desde p si sgn >= 0
    Pos2d Cdg(void) const
      { return GeomObj::list_Pos2d::Cdg(); }

    iterator getFarthestPointFromSegment(iterator it1, iterator it2, GEOM_FT &pMaxDist);

    void Print(std::ostream &stream) const;
    void Plot(Plotter &) const;
  };

GeomObj::list_Pos2d interseccion(const Polilinea2d &p,const Recta2d &r);
GeomObj::list_Pos2d interseccion(const Polilinea2d &p,const SemiRecta2d &);
GeomObj::list_Pos2d interseccion(const Polilinea2d &p,const Segmento2d &);
GeomObj::list_Pos2d interseccion(const Recta2d &,const Polilinea2d &);
GeomObj::list_Pos2d interseccion(const SemiRecta2d &,const Polilinea2d &p);
GeomObj::list_Pos2d interseccion(const Segmento2d &,const Polilinea2d &p);

#endif






