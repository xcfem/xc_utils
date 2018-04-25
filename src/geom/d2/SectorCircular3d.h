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
//SectorCircular2d.h

#ifndef SECTORCIRCULAR3D_H
#define SECTORCIRCULAR3D_H

#include "D2to3d.h"
#include "SectorCircular2d.h"

class Pos3d;

//! @ingroup GEOM
//
//! @brief Sector de círculo en tres dimensiones.
class SectorCircular3d : public D2to3d
  {
    SectorCircular2d sect_circ;
  public:
    SectorCircular3d(void) : D2to3d(), sect_circ() {}
    SectorCircular3d(const Pos3d centro,const GEOM_FT &rad,const double &th1,const double &th2);
    SectorCircular3d(const GEOM_FT &rad2,const Pos3d &centro,const double &th1,const double &th2);
    SectorCircular3d(const Pos3d &c,const double &r,const Vector3d &n,const Vector3d &Xaxis,const double &angIni,const double &angFin);
    SectorCircular3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    SectorCircular3d(const SectorCircular3d &otro);
    SectorCircular3d &operator=(const SectorCircular3d &p);
    virtual D2to3d *clon(void) const;
    Pos3d Centro(void) const;
    Pos3d PInic(void) const;
    Pos3d PFin(void) const;
    Pos3d PMed(void) const;
    virtual Pos3d Cdg(void) const;
    virtual Pos3d ArcCentroid(void) const;
    GEOM_FT Radio2(void) const;
    GEOM_FT Radio(void) const;
    GEOM_FT Diametro(void) const;
    inline double AnguloComprendido(void) const
      { return sect_circ.AnguloComprendido(); }
    double Angulo(const Pos3d &) const;
    double getLambda(const Pos3d &) const;
    virtual GEOM_FT Longitud(void) const
      { return sect_circ.Longitud(); }
    virtual GEOM_FT LongitudArco(void) const
      { return sect_circ.LongitudArco(); }
    inline GEOM_FT Perimetro(void) const
      { return Longitud(); }
    virtual GEOM_FT Area(void) const
      { return sect_circ.Area(); }
    virtual GEOM_FT Volumen(void) const
      { return 0; }
    inline const double &Theta1(void) const
      { return sect_circ.Theta1(); }
    inline double &Theta1(void)
      { return sect_circ.Theta1(); }
    inline const double &Theta2(void) const
      { return sect_circ.Theta2(); }
    inline double &Theta2(void)
      { return sect_circ.Theta2(); }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;

    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;

    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    MatrizPos3d getArcPoints(const size_t &n) const;

    friend bool operator ==(const SectorCircular3d &a,const SectorCircular3d &b);

    
    void Print(std::ostream &os) const;
  };

#endif



