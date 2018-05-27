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
//ListaPos3d.

#ifndef LISTAPOS3D_H
#define LISTAPOS3D_H

#include "Pos3d.h"
#include "Vector3d.h"
#include "../d3/GeomObj3d.h"

class Trf3d;


//! @ingroup GEOM
//
//! @brief Lista de posiciones en tres dimensiones.
class ListaPos3d: public GeomObj3d
  {
  public:
    typedef GeomObj::list_Pos3d list_Pos3d;
    typedef GeomObj::list_Pos3d::iterator point_iterator;
    typedef GeomObj::list_Pos3d::const_iterator point_const_iterator;
  protected:
    list_Pos3d lista_ptos;
    Pos3d &operator[](const size_t &i);
  public:
    ListaPos3d(void);
    explicit ListaPos3d(const GeomObj::list_Pos3d &l);
    virtual GeomObj *clon(void) const
      { return new ListaPos3d(*this); }
    inline size_t getNumberOfPoints(void) const
      { return lista_ptos.size(); }
    inline point_const_iterator points_begin(void) const
      { return lista_ptos.begin(); }
    const point_const_iterator points_end(void) const
      { return lista_ptos.end(); }
    inline short unsigned int Dimension(void) const
      { return 0; }

    const GeomObj::list_Pos3d &getPoints(void) const
      { return lista_ptos; }
    const Pos3d &operator[](const size_t &i) const;

    const Pos3d *appendPoint(const Pos3d &p);
    //! @brief Insert the vertices between [first,last).
    template <class InputIterator>
    inline void assign(InputIterator first, InputIterator last)
      { lista_ptos.assign(first,last); }
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;

    //Producto de inercia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //! @brief Return the length of the ListaPos3d.
    virtual GEOM_FT getLength(void) const
      { return 0.0; }
    //! @brief Return el área de la ListaPos3d.
    virtual GEOM_FT Area(void) const
      { return 0.0; }
    //! @brief Return el volumen de la ListaPos3d.
    virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    ListaPos3d GetMayores(unsigned short int i,const GEOM_FT &d) const;
    ListaPos3d GetMenores(unsigned short int i,const GEOM_FT &d) const;
    const Pos3d &Point(const size_t &i) const;
    Pos3d getCenterOfMass(void) const
      { return lista_ptos.getCenterOfMass(); }

    void Transforma(const Trf3d &trf3d);

    std::deque<GEOM_FT> &GetSeparaciones(void) const;
    double GetSeparacionMedia(void) const;

    void Print(std::ostream &stream) const;
    void Plot(Plotter &) const;
  };

#endif






