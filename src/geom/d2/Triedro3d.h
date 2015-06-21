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
//Triedro3d.h

#ifndef TRIEDRO3D_H
#define TRIEDRO3D_H

#include "../d3/GeomObj3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d2/Triangulo3d.h"

class Plano3d;
class Poliedro3d;

//! @ingroup GEOM
//
//! @brief Ángulo formado por tres planos que pasan por un punto.
class Triedro3d: public GeomObj3d
  {
    Pos3d p0;
    Triangulo3d tr;
  protected:
    Plano3d get_plano(const size_t &i) const;
  public:
    Triedro3d(void);
    Triedro3d(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3);
    Triedro3d(const Pos3d &p0, const Triangulo3d &tr);
    virtual GeomObj *clon(void) const
      { return new Triedro3d(*this); }
    ~Triedro3d(void) {}
    void Put( const Pos3d &p0, const Pos3d &p1,
              const Pos3d &p2, const Pos3d &p3);
    void Put(const Pos3d &p0, const Triangulo3d &tr);
    inline virtual unsigned int GetNumVertices(void) const
      { return 4; }
    inline virtual unsigned int GetNumVerticesFaceta(unsigned int faceta) const
      { return 3; }
    inline virtual unsigned int GetNumAristas(void) const
      { return 3; }
    inline virtual unsigned int GetNumFacetas(void) const
      { return 3; }
    inline virtual GEOM_FT Longitud(void) const
      { return 0.0; }
    virtual GEOM_FT Area(void) const
      { return NAN; }
    virtual GEOM_FT Volumen(void) const
      { return NAN; }
    virtual GEOM_FT Ix(void) const
      { return NAN; }
    virtual GEOM_FT Iy(void) const
      { return NAN; }
    virtual GEOM_FT Iz(void) const
      { return NAN; }
    short unsigned int Dimension() const
      { return 3; }
    GEOM_FT GetMax(short unsigned int) const;
    GEOM_FT GetMin(short unsigned int) const;
    Pos3d Cdg() const;
    bool TocaCuadrante(const int &) const;

    const Triangulo3d &Base(void) const;
    const Pos3d &Cuspide(void) const;
    Recta3d Eje(void) const;
    GEOM_FT GetAnguloConico(void) const;

    Poliedro3d GetPoliedro3d(void) const;
    Pos3d Vertice(const size_t &i) const;
    virtual GEOM_FT PseudoDist(const Pos3d &p) const;
    virtual bool In(const Pos3d &p,const double &tol= 0.0) const;

    void Print(std::ostream &os) const;
  };


#endif



