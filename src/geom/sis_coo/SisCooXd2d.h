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

#ifndef SIS_COO_XD2D_H
#define SIS_COO_XD2D_H

#include "SisCoo.h"

class Vector2d;
class Pos2d;
class Dir2d;


//! @ingroup SisCoo
//
//! @brief Sistema de coordenadas de X dimensiones definido
//! en un espacio de 2 dimensiones.
class SisCooXd2d: public SisCoo
  {
  public:
    typedef Vector2d VGlobal; //!< Vector en el espacio de 2 dimensiones.
    typedef Dir2d DGlobal; //!< Dirección en el espacio de 2 dimensiones.
    typedef Pos2d PGlobal; //!< Punto en el espacio de 2 dimensiones.
  protected:
    virtual bool procesa_comando(CmdStatus &status);
    SisCooXd2d(const size_t &);
    SisCooXd2d(const size_t &,const VGlobal &);
    SisCooXd2d(const size_t &,const PGlobal &,const PGlobal &);

    void PutFila(const size_t &eje,const VGlobal &v);
    void VectorEjeX(const VGlobal &vX);

  public:
    virtual VGlobal GetVDirEje(const size_t &eje) const;
    //Devuelve el vector dirección del eje que se pasa como parámetro.
    virtual DGlobal GetDirEje(const size_t &eje) const;
    //Devuelve la dirección del eje que se pasa como parámetro.

    VGlobal GetCooGlobales(const matriz_FT &v) const;
    matriz_FT GetCooLocales(const VGlobal &v) const;
  };

#endif
