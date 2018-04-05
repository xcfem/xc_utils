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

#ifndef SECTORCIRCULAR2D_H
#define SECTORCIRCULAR2D_H

#include "Circulo2d.h"

class Pos2d;
class MatrizPos2d;

//! @ingroup GEOM
//
//! @brief 2D circular sector.
class SectorCircular2d : public Circulo2d
  {
    double theta1; //!< Angle that defines the start point of the arc.
    double theta2; //!< Angle that defines the end point of the arc.
  public:
    SectorCircular2d(void);
    SectorCircular2d(const Circulo2d &c,const double &th1,const double &th2);
    SectorCircular2d(const SectorCircular2d &otro);
    SectorCircular2d &operator=(const SectorCircular2d &p);
    virtual Superficie2d *clon(void) const;
    virtual Pos2d Cdg(void) const;
    virtual Pos2d ArcCentroid(void) const;
    Pos2d PInic(void) const;
    Pos2d PFin(void) const;
    Pos2d PMed(void) const;
    inline const double &Theta1(void) const
      { return theta1; }
    inline double &Theta1(void)
      { return theta1; }
    inline const double &Theta2(void) const
      { return theta2; }
    inline double &Theta2(void)
      { return theta2; }
    double Angulo(const Pos2d &p) const;
    double getLambda(const Pos2d &) const;
    double AnguloComprendido(void) const;
    virtual GEOM_FT LongitudArco(void) const;
    virtual GEOM_FT Longitud(void) const;
    virtual GEOM_FT Area(void) const;
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    MatrizPos2d getArcPoints(const size_t &n) const;

    void Print(std::ostream &os) const;
    void Plot(Plotter &) const;
  };

bool operator==(const SectorCircular2d &a,const SectorCircular2d &b);
SectorCircular2d SectorCircular2dThreepoints(const Pos2d &,const Pos2d &,const Pos2d &);


#endif



