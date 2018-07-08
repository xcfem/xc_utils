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
//BND3D.h

#ifndef BND3D_H
#define BND3D_H

#include <iostream>
#include "GeomObj3d.h"
#include "../cgal_types.h"


//! @ingroup GEOM
//
//! @brief "boundary" en tres dimensiones.
class BND3d: public GeomObj3d
  {
    CGIsoCuboid_3 cgisocub;
  protected:
    bool LBClipTest(const GEOM_FT &p,const GEOM_FT &q,GEOM_FT &u1,GEOM_FT &u2) const;
    //Esta funcion forma parte del algoritmo de recorte de l'ineas de 
    //Liang-Barsky (página 231 del libro Computer Graphics de Donald Hearn y 
    //Pauline Baker isbn 0-13-578634-7).
    bool LBClipLine(const Pos3d &p1,const Pos3d &p2) const;
  public:
    BND3d(void): GeomObj3d(), cgisocub() {}
    BND3d(const Pos3d &p_min,const Pos3d &p_max);
    BND3d(const BND3d &other) 
      : GeomObj3d(), cgisocub(other.cgisocub) {}
    BND3d &operator =(const BND3d &other)
      {
	GeomObj3d::operator=(other);
        cgisocub= other.cgisocub;
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new BND3d(*this); }
    //! @brief Return the dimension of the object 0, 1, 2 or 3.
    inline virtual unsigned short int Dimension(void) const
      { return 3; }
    //! @brief Return object length.
    inline virtual GEOM_FT getLength(void) const
      { return GetXMax()-GetXMin(); }
    inline GEOM_FT Anchura(void) const
      { return GetYMax()-GetYMin(); }
    inline GEOM_FT Altura(void) const
      { return GetZMax()-GetZMin(); }
    Vector3d Diagonal(void) const;
    GEOM_FT getAreaXYFace(void) const;
    GEOM_FT getAreaXZFace(void) const;
    GEOM_FT getAreaYZFace(void) const;
    virtual GEOM_FT getArea(void) const;
    //! @brief Return the object volume
    inline virtual GEOM_FT getVolume(void) const
      { return cgisocub.volume(); }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;
    void Update(const Pos3d &);
    void PutPMax(const Pos3d &);
    void PutPMin(const Pos3d &);
    void PutPMinMax(const Pos3d &,const Pos3d &);
    Pos3d GetPMax(void) const;
    Pos3d GetPMin(void) const;
    inline GEOM_FT GetMax(unsigned short int i) const
      { return cgisocub.max_coord(i-1); }
    inline GEOM_FT GetMin(unsigned short int i) const
      { return cgisocub.min_coord(i-1); }
    int GetNumCaras(void) const
      { return 6; }
    CGBbox_3 GetCGALBbox_3(void) const;
    Pos3d getCenterOfMass(void) const;
    Pos3d Vertice(unsigned int i) const;
    unsigned short int RegionCode(const Pos3d &,const double &tol= 0.0) const;
    bool In(const Pos3d &p,const double &tol= 0.0) const;
    bool ClipLine(const Pos3d &p1,const Pos3d &p2) const;
    BND3d Offset(const GEOM_FT &o) const;
    BND3d &operator +=(const Pos3d &p);
    BND3d &operator +=(const BND3d &a);
    friend BND3d operator +(const BND3d &a, const BND3d &b);
    friend bool operator ==(const BND3d &a,const BND3d &b);
    void Print(std::ostream &stream) const;
  };

#endif
