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
//GeomObj.h

#ifndef GEOMOBJ2D_H
#define GEOMOBJ2D_H

#include "xc_utils/src/geom/GeomObj.h"
#include "xc_utils/src/geom/sis_ref/PrincipalAxesOfInertia2D.h"

class BND2d;
class Dir2d;
class Recta2d;
class matriz_FT;

//! @ingroup GEOM
//
//! @brief Clase base para las entidades geométricas en dos dimensiones.
class GeomObj2d: public GeomObj
  {
  public:
   typedef PoliPos<Pos2d> list_Pos2d;
/*     typedef MatrizT<Pos3d,vector<Pos3d> > m_pos3d; */

    GeomObj2d(void) {}
    virtual ~GeomObj2d(void) {}
    virtual GEOM_FT GetMax(unsigned short int i) const= 0;
    //Devuelve el valor maximo de la coordenada i.
    virtual GEOM_FT GetMin(unsigned short int i) const= 0;
    //Devuelve el valor minimo de la coordenada i.
    GEOM_FT GetXMax(void) const { return GetMax(1); }
    GEOM_FT GetYMax(void) const { return GetMax(2); }
    GEOM_FT GetXMin(void) const { return GetMin(1); }
    GEOM_FT GetYMin(void) const { return GetMin(2); }
    Pos2d GetPMax(void) const;
    Pos2d GetPMin(void) const;
    BND2d Bnd(void) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    virtual bool Out(const Pos2d &p, const double &tol= 0.0) const;
    virtual GEOM_FT PesoCdg(void) const
      //Devuelve el peso para el cálculo del CDG
      //por defecto es 1
      { return 1.0; }
    virtual Pos2d Cdg(void) const= 0;
    virtual GEOM_FT Longitud(void) const= 0; //?? Por que se re-declara (está en GeomObj).
    virtual GEOM_FT Area(void) const= 0; //?? Por que se re-declara (está en GeomObj).
    inline virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    //! @briefMomento de inercia respecto al CDG en ejes locales.
    virtual GEOM_FT Ix(void) const= 0;
    //! @briefMomento de inercia respecto al CDG en ejes locales.
    virtual GEOM_FT Iy(void) const= 0;
    //! @brief Producto de inercia respecto al CDG en ejes locales.
    virtual GEOM_FT Pxy(void) const= 0;
    inline virtual GEOM_FT Iz(void) const
    //Momento de inercia polar respecto al CDG en ejes locales.
      { return Ix()+Iy(); }
    double Theta_p(void) const;
    //Devuelve el ángulo que define un eje principal de inercia.
    Dir2d DirEjeI_a(void) const;
    //Devuelve la dirección de un eje principal de inercia (no sabemos si
    //el mayor o el menor
    Dir2d DirEjeI_b(void) const;
    //Devuelve la dirección del otro eje principal de inercia (no sabemos si
    //el mayor o el menor
    Recta2d EjeI_a(void) const;
    //Devuelve un eje principal de inercia (no sabemos si
    //el mayor o el menor).
    Recta2d EjeI_b(void) const;
    //Devuelve el otro eje principal de inercia (no sabemos si
    //el mayor o el menor).
    Ref2d2d PrincipalAxesOfInertia(void) const;
    GEOM_FT I1(void) const;
    //Devuelve el momento de inercia principal mayor.
    GEOM_FT I2(void) const;
    //Devuelve el momento de inercia principal menor.
    inline PrincipalAxesOfInertia2D Inercia(void)
      { return PrincipalAxesOfInertia2D(Cdg(),Ix(),Iy(),Pxy()); }
    GEOM_FT I( const unsigned short int &i,
              const unsigned short int &j) const;
    //! @brief Devuelve el area que se emplea para calcular el momento de inercia
    //! por defecto suponemos que es igual al area del objeto.
    virtual inline GEOM_FT IArea(void) const
      { return Area(); }
    GEOM_FT I(const Pos2d &O,const Vector2d &e) const;
    GEOM_FT I(const Recta2d &r) const;
      //Devuelve el momento de inercia respecto a la recta que se pasa
      //como parámetro.
    GEOM_FT I( const unsigned short int i,
              const unsigned short int j,
              const Pos2d &o) const;
    GEOM_FT IO(const Pos2d &o) const;
    matriz_FT I(void) const;
    matriz_FT I(const Pos2d &o) const;

    virtual void Mueve(const Vector2d &);
    virtual void Transforma(const Trf2d &trf2d)= 0;    
  };

//! @brief Devuelve el objeto transformado.
template <class T>
T getTransformado(const T &obj,const Trf2d &trf2d)
  {
    T retval(obj);
    retval.Transforma(trf2d);
    return retval;
  }

#endif




