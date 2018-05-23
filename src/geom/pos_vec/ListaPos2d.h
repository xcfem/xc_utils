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
//ListaPos2d.

#ifndef LISTAPOS2D_H
#define LISTAPOS2D_H

#include "../d2/GeomObj2d.h"

class Poligono2d;

//! @ingroup GEOM
//
//! @brief Lista de posiciones en dos dimensiones.
class ListaPos2d: public GeomObj2d
  {
  public:
    typedef GeomObj::list_Pos2d list_Pos2d;
    typedef GeomObj::list_Pos2d::iterator point_iterator;
    typedef GeomObj::list_Pos2d::const_iterator point_const_iterator;
  protected:
    list_Pos2d lista_ptos;
    Pos2d &operator[](const size_t &i);
  public:
    ListaPos2d(void);
    explicit ListaPos2d(const GeomObj::list_Pos2d &l);
    virtual GeomObj *clon(void) const
      { return new ListaPos2d(*this); }
    inline size_t getNumberOfPoints(void) const
      { return lista_ptos.size(); }
    inline point_const_iterator points_begin(void) const
      { return lista_ptos.begin(); }
    const point_const_iterator points_end(void) const
      { return lista_ptos.end(); }
    inline short unsigned int Dimension(void) const
      { return 0; }

    const GeomObj::list_Pos2d &getPoints(void) const
      { return lista_ptos; }
    const Pos2d &operator[](const size_t &i) const;

    const Pos2d *appendPoint(const Pos2d &p);
    void appendPointPy(const Pos2d &p);
    template <class InputIterator>
    //! Insert the vertices between [first,last).
    inline void assign(InputIterator first, InputIterator last)
      { lista_ptos.assign(first,last); }
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;

    //Producto de inercia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //! @brief Return the longitud de la ListaPos2d.
    virtual GEOM_FT Longitud(void) const
      { return 0.0; }
    //! @brief Return el área de la ListaPos2d.
    virtual GEOM_FT Area(void) const
      { return 0.0; }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    ListaPos2d GetMayores(unsigned short int i,const GEOM_FT &d) const;
    ListaPos2d GetMenores(unsigned short int i,const GEOM_FT &d) const;
    const Pos2d &Point(const size_t &i) const;
    Pos2d getCenterOfMass(void) const
      { return lista_ptos.getCenterOfMass(); }

    void Transforma(const Trf2d &trf2d);
    ListaPos2d Offset(const GEOM_FT &d) const;

    std::deque<GEOM_FT> &GetSeparaciones(void) const;
    std::deque<GEOM_FT> &GetRecubrimientos(const Poligono2d &) const;
    double GetSeparacionMedia(void) const;

    void Print(std::ostream &stream) const;
    void Plot(Plotter &) const;
  };

#endif






