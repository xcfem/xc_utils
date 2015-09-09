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
//SisCoo.h
//Sistema de coordenadas (abstracto).

#ifndef SIS_COO_XD3D_H
#define SIS_COO_XD3D_H

#include "SisCoo.h"

class Vector3d;
class Dir3d;
class Pos3d;

//! @ingroup SisCoo
//! 
//! @brief Clase base para los sistemas de coordenadas
//! definidos en un espacio de 3 dimensiones.
class SisCooXd3d: public SisCoo
  {
  public:
    typedef Vector3d VGlobal; //!< Vector en el espacio de 3 dimensiones.
    typedef Pos3d PGlobal; //!< Punto en el espacio de 3 dimensiones.
    typedef Dir3d DGlobal; //!< Dirección en el espacio de 3 dimensiones.
  protected:
    virtual bool procesa_comando(CmdStatus &status);
    void vectores_unitarios(const VGlobal &i_,const VGlobal &j_,const VGlobal &k_);
    SisCooXd3d(const size_t &i)
      : SisCoo(i,3) {}
    SisCooXd3d(const size_t &i,const VGlobal &v1);
    SisCooXd3d(const size_t &i,const VGlobal &v1,const VGlobal &v2);
    SisCooXd3d(const size_t &i,const PGlobal &o,const PGlobal &p);
    SisCooXd3d(const size_t &i,const PGlobal &p1,const PGlobal &p2, const PGlobal &p3);
    SisCooXd3d(const size_t &i,const VGlobal &v1,const VGlobal &v2,const VGlobal &v3);


    void PutFila(const size_t &eje,const VGlobal &v);
    void VectorEjeX(const VGlobal &v);
    void DosPuntos(const PGlobal &o,const PGlobal &p);
    void TresPuntos(const PGlobal &o,const PGlobal &p1,const PGlobal &p2);

  public:
    //@ brief Constructor virtual.
    virtual SisCooXd3d *CopiaXd3d(void) const= 0;
    virtual VGlobal GetVDirEje(const size_t &eje) const;
    //Devuelve el vector dirección del eje que se pasa como parámetro.
    virtual DGlobal GetDirEje(const size_t &eje) const;

    VGlobal GetCooGlobales(const matriz_FT &v) const;
    matriz_FT GetCooLocales(const VGlobal &v) const;
  };

#endif
