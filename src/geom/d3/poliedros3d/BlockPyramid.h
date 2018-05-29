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
//BLOCKPYRAMID.h

#ifndef BLOCKPYRAMID_H
#define BLOCKPYRAMID_H

#include <iostream>
#include "../GeomObj3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_basic/src/matrices/m_double.h"


//! @ingroup GEOM
//
//! @brief Ángulo poliedrico (XXX cambiarle el nombre).
class BlockPyramid: public GeomObj3d
  {
  protected:
    std::deque<SemiEspacio3d> semiespacios; //! Semiespacios que definen el BP.

    std::deque<Vector3d> haz_vectores(void) const;
    static bool es_interior(const SemiEspacio3d &,const Vector3d &);
    bool es_interior(const Vector3d &) const;
    std::deque<Vector3d> haz_vectores_interiores(void) const;
  public:
    BlockPyramid(void);
    BlockPyramid(const std::deque<SemiEspacio3d> &);
    virtual GeomObj *clon(void) const
      { return new BlockPyramid(*this); }
    inline unsigned short int Dimension(void) const
      { return 3; }
    GEOM_FT getLength(void) const;
    GEOM_FT Area(void) const;
    GEOM_FT getVolume(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Iz(void) const;
    Pos3d getCenterOfMass(void) const;
    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    m_double getVectoresBorde(void) const;
    Vector2d getVectorExterno1(const Ref2d3d &) const;
    Vector2d getVectorExterno2(const Ref2d3d &) const;
    std::deque<Vector2d> getVectoresExternos(const Ref2d3d &) const;
    bool Vacio(void) const;
    void Print(std::ostream &os) const;
  };

#endif
