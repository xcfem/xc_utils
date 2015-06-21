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
//GeomObj3d.h

#ifndef GEOMOBJ3D_H
#define GEOMOBJ3D_H

#include "../GeomObj.h"

#include "../listas/PoliPos.h"

class SoGroup;
class Pos3d;
class Vector3d;
class Recta3d;
class BND3d;
class Ref3d3d;
class matriz_FT;
class SemiEspacio3d;


//! @ingroup GEOM
//
//! @brief Clase base para los objetos en tres dimensiones.
class GeomObj3d: public GeomObj
  {
  protected:
    std::deque<SemiEspacio3d> interpretaSemiEspacios3d(const std::string &str);
  public:
    typedef PoliPos<Pos3d> list_Pos3d;

    GeomObj3d(void) {}
    virtual ~GeomObj3d(void) {}
    virtual GeomObj *clon(void) const=0;
    virtual GEOM_FT GetMax(unsigned short int i) const= 0;
    //Devuelve el valor maximo de la coordenada i.
    virtual GEOM_FT GetMin(unsigned short int i) const= 0;
    //Devuelve el valor minimo de la coordenada i.
    GEOM_FT GetXMax(void) const { return GetMax(1); }
    GEOM_FT GetYMax(void) const { return GetMax(2); }
    GEOM_FT GetZMax(void) const { return GetMax(3); }
    GEOM_FT GetXMin(void) const { return GetMin(1); }
    GEOM_FT GetYMin(void) const { return GetMin(2); }
    GEOM_FT GetZMin(void) const { return GetMin(3); }
    virtual void ProyX(void) {}
    virtual void ProyY(void) {}
    virtual void ProyZ(void) {}
    Pos3d GetPMax(void) const;
    Pos3d GetPMin(void) const;
    BND3d Bnd(void) const;
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    virtual bool Out(const Pos3d &p, const double &tol= 0.0) const;
    //Devuelve el peso para el cálculo del CDG
    //por defecto es 1
    virtual GEOM_FT PesoCdg(void) const
      { return 1.0; }
    virtual Pos3d Cdg(void) const= 0;
    virtual GEOM_FT Longitud(void) const= 0;
    virtual GEOM_FT Area(void) const= 0;
    virtual GEOM_FT Volumen(void) const= 0;
    virtual GEOM_FT Ix(void) const= 0;
    virtual GEOM_FT Iy(void) const= 0;
    virtual GEOM_FT Iz(void) const= 0;

    //Producto de inercia respecto al CDG en ejes locales.
    //Suponemos ejes ortonormales.
    inline virtual GEOM_FT Pxy(void) const
      { return Ix()+Iy()-Iz(); }
    //Producto de inercia respecto al CDG en ejes locales.
    //Suponemos ejes ortonormales.
    inline virtual GEOM_FT Pxz(void) const
      { return Ix()+Iz()-Iy(); }
    //Producto de inercia respecto al CDG en ejes locales.
    //Suponemos ejes ortonormales.
    inline virtual GEOM_FT Pyz(void) const
      { return Iy()+Iz()-Ix(); }
    inline GEOM_FT I( const unsigned short int &i,
                     const unsigned short int &j) const;
    //Devuelve el area que se emplea para calcular el momento de inercia
    virtual inline GEOM_FT IArea(void) const
      { return 0.0; }
    GEOM_FT I(const Pos3d &O,const Vector3d &e) const;
    GEOM_FT I(const Recta3d &r) const;
    GEOM_FT I( const unsigned short int i,
              const unsigned short int j,
              const Pos3d &o) const;
    GEOM_FT IO(const Pos3d &o) const;
    matriz_FT I(void) const;
    matriz_FT I(const Pos3d &o) const;
    any_const_ptr GetProp(const std::string &cod) const;
    virtual void SalvaCmd(std::ostream &os,const std::string &indent= "  ") const;
  };

#endif




