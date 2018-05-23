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
//Segmento3d.h

#ifndef SEGMENTO3D_H
#define SEGMENTO3D_H

#include "Linea3d.h"
#include "Recta3d.h"
#include "SemiRecta3d.h"
#include "../pos_vec/Pos3d.h"

class Dir3d;


//! @ingroup GEOM
//
//! @brief Segmento en tres dimensiones.
class Segmento3d : public Linea3d
  {
    CGSegmento_3 cgseg;
  public:
    Segmento3d(void);
    Segmento3d(const CGSegmento_3 &r);
    Segmento3d(const Pos3d &p1,const Pos3d &p2);
    Segmento3d(const Segmento3d &r);
    Segmento3d &operator=(const Segmento3d &r);

    const CGSegmento_3 &ToCGAL(void) const
      { return cgseg; }
    virtual GeomObj *clon(void) const;
    void TwoPoints(const Pos3d &p1,const Pos3d &p2);
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    Recta3d RectaSoporte(void) const;
    Pos3d Origen(void) const;
    Pos3d Destino(void) const;
    GEOM_FT getSlope(void) const;
    const Pos3d Point(const int &i) const;
    Pos3d PtoParametricas(const GEOM_FT &lambda) const;
    double getParamCooNatural(const GEOM_FT &) const;
    Pos3d PtoCooNatural(const GEOM_FT &chi) const;
    GEOM_FT getLambda(const Pos3d &p) const;
    bool EsDegenerada(void) const;
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    virtual GEOM_FT dist2(const Pos3d &p) const;
    GEOM_FT dist(const Pos3d &p) const;
    void Put(const Pos3d &p1,const Pos3d &p2);

    bool Paralelo(const Recta3d &r) const;
    bool Paralelo(const SemiRecta3d &sr) const;
    bool Paralelo(const Segmento3d &r) const;

    GeomObj3d::list_Pos3d Interseccion(unsigned short int, const double &) const;
    GeomObj3d::list_Pos3d Interseccion(const Recta3d &r) const;
    GeomObj3d::list_Pos3d Interseccion(const SemiRecta3d &sr) const;
    GeomObj3d::list_Pos3d Interseccion(const Segmento3d &sg) const;

    virtual GEOM_FT Longitud(void) const;
    virtual Pos3d getCenterOfMass(void) const;
    Dir3d GetDir(void) const;
    Vector3d VDir(void) const;
    GEOM_FT Angulo(const Vector3d &v) const;
    GEOM_FT Angulo(const Segmento3d &v) const;
    friend GEOM_FT angulo(const Segmento3d &r,const Vector3d &v);
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;
    friend bool operator==(const Segmento3d &r1,const Segmento3d &r2);
    void Print(std::ostream &os) const;
    
  };

inline GEOM_FT dist2(const Pos3d &p,const Segmento3d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const Segmento3d &r,const Pos3d &p)
  { return dist2(p,r); }
GEOM_FT dist(const Pos3d &p,const Segmento3d &r);
inline GEOM_FT dist(const Segmento3d &r,const Pos3d &p)
  { return dist(p,r); }

inline bool paralelas(const Segmento3d &sg,const Recta3d &r)
  { return sg.Paralelo(r); }
inline bool paralelas(const Recta3d &r, const Segmento3d &sg)
  { return paralelas(sg,r); }
inline bool paralelas(const Segmento3d &sg,const SemiRecta3d &sr)
  { return sg.Paralelo(sr); }
inline bool paralelas(const SemiRecta3d &sr, const Segmento3d &sg)
  { return paralelas(sg,sr); }
inline bool paralelas(const Segmento3d &r1,const Segmento3d &r2)
  { return r1.Paralelo(r2); }

inline bool colineales(const Segmento3d &sg,const Recta3d &r)
  { return colineales(sg.RectaSoporte(),r); }
inline bool colineales(const Recta3d &r,const Segmento3d &sg)
  { return colineales(sg,r); }
inline bool colineales(const Segmento3d &sg,const SemiRecta3d &sr)
  { return colineales(sg.RectaSoporte(),sr); }
inline bool colineales(const SemiRecta3d &sr,const Segmento3d &sg)
  { return colineales(sg,sr); }
inline bool colineales(const Segmento3d &sg1,const Segmento3d &sg2)
  { return colineales(sg1,sg2.RectaSoporte()); }

inline GeomObj3d::list_Pos3d interseccion(const Segmento3d &sg,const Recta3d &r)
  { return sg.Interseccion(r); }
inline GeomObj3d::list_Pos3d interseccion(const Recta3d &r, const Segmento3d &sg)
  { return sg.Interseccion(r); }
inline GeomObj3d::list_Pos3d interseccion(const Segmento3d &sg,const SemiRecta3d &sr)
  { return sg.Interseccion(sr); }
inline GeomObj3d::list_Pos3d interseccion(const SemiRecta3d &sr, const Segmento3d &sg)
  { return sg.Interseccion(sr); } 
inline GeomObj3d::list_Pos3d interseccion(const Segmento3d &sg1,const Segmento3d &sg2)
  { return sg1.Interseccion(sg2); }



#endif
