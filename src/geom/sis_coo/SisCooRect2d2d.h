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
//SisCooRect2d2d.h

#ifndef SIS_COO_RECT_2D2D_H
#define SIS_COO_RECT_2D2D_H

#include "SisCooXd2d.h"


//! @ingroup SisCoo
//
//! @brief Sistema de coordenadas rectangular de 2 dimensiones
//! definido en un espacio de dos dimensiones.
class SisCooRect2d2d: public SisCooXd2d
  {
  public:
    typedef Vector2d VLocal; //!< Dimension of the vector in local coordinates.
    typedef Pos2d PLocal; //!< Dimension of the point in local coordinates.


    SisCooRect2d2d(void);
    SisCooRect2d2d(const Pos2d &p1,const Pos2d &p2);
    SisCooRect2d2d(const VGlobal &vX);
    virtual SisCoo *Copia(void) const;

    //Acceso a miembros.
    VGlobal GetI(void) const;
    VGlobal GetJ(void) const;
    void PutI(const VGlobal &);
    void PutJ(const VGlobal &);

    //Conversión vectores.
    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;

    virtual ~SisCooRect2d2d(void) {}
  };

#endif
