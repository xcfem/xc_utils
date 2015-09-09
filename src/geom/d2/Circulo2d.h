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
//Circulo2d.h

#ifndef CIRCULO2D_H
#define CIRCULO2D_H

#include "Superficie2d.h"
#include "../tipos_cgal.h"
#include "xc_basic/src/util/matem.h"

class Pos2d;
class MatrizPos2d;
class Poligono2d;

//! @ingroup GEOM
//
//! @brief Círculo en dos dimensiones.
class Circulo2d : public Superficie2d
  {
    CGCirculo_2 cgcirc;

  protected:
    void puntos_arco(const double &theta_inic,const double &delta_theta,MatrizPos2d &ptos) const;
    bool procesa_comando(CmdStatus &status);
  public:
    Circulo2d(void) : Superficie2d(), cgcirc() {}
    Circulo2d(const Pos2d &centro,const GEOM_FT &rad);
    Circulo2d(const GEOM_FT &rad2,const Pos2d &centro);
    Circulo2d(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3);
    Circulo2d(const Circulo2d &otro)
     : Superficie2d(otro), cgcirc(otro.cgcirc) {}
    Circulo2d &operator=(const Circulo2d &p)
      {
	Superficie2d::operator=(p);
        cgcirc= p.cgcirc;
        return *this;
      }
    virtual Superficie2d *clon(void) const
      { return new Circulo2d(*this); }
    Pos2d Centro(void) const;
    virtual Pos2d Cdg(void) const;
    Pos2d Punto(const double &ang) const;
    inline GEOM_FT Radio2(void) const
      { return cgcirc.squared_radius(); }
    GEOM_FT Radio(void) const;
    inline GEOM_FT Diametro(void) const
      { return 2*Radio(); }
    double Angulo(const Pos2d &p) const;
    virtual GEOM_FT Longitud(void) const;
    inline GEOM_FT Perimetro(void) const
      { return Longitud(); }
    virtual double AnguloComprendido(void) const;
    virtual GEOM_FT Area(void) const;
    virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const
      { return Ix(); }
    inline virtual GEOM_FT Pxy(void) const
      { return 0.0; }
    virtual GEOM_FT Iz(void) const
      { return 2*Ix(); }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    MatrizPos2d PuntosPerimetro(const size_t &n,const double &theta_inic= 0.0) const;
    Poligono2d getPoligonoInscrito(const size_t &n,const double &theta_inic= 0.0) const;

    void Transforma(const Trf2d &trf2d);

    friend int operator ==(const Circulo2d &a,const Circulo2d &b)
      { return ( a.cgcirc == b.cgcirc ); };
    virtual void SalvaCmd(std::ostream &os,const std::string &indent= "  ") const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
    void Print(std::ostream &os) const;
    void Plot(Plotter &) const;
  };

Circulo2d Circulo2dRTT(const GEOM_FT &,const Recta2d &,const Recta2d &,const bool &left,const bool &far);

#endif



