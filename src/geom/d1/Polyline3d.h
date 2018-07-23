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
//Polyline3d.

#ifndef POLILINEA3D_H
#define POLILINEA3D_H

#include "../pos_vec/Pos3d.h"
#include "../listas/PoliPos.h"
#include "Linea3d.h"
#include "Segment3d.h"

//! @ingroup GEOM
//
//! @brief Polilínea en 3 dimensiones.
class Polyline3d : public Linea3d, public GeomObj::list_Pos3d
  {
  public:
    Polyline3d(void): Linea3d(), GeomObj::list_Pos3d() {}
    virtual GeomObj *clon(void) const
      { return new Polyline3d(*this); }
    virtual void Mueve(const Vector3d &);
    const GeomObj::list_Pos3d &getVertices(void) const
      { return *this; }
    inline size_t GetNumVertices(void) const
      { return GeomObj::list_Pos3d::size(); }
    size_t getNumSegments(void) const;

/*     inline virtual void GiraX(double ang) */
/*       { Ref3d::GiraX(ang); TrfPoints(); } */
/*     inline virtual void GiraY(double ang) */
/*       { Ref3d::GiraY(ang); TrfPoints();  } */
/*     inline virtual void GiraZ(double ang) */
/*       { Ref3d::GiraZ(ang); TrfPoints();  } */
    const Pos3d *AgregaVertice(const Pos3d &p);
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;

    //! @brief Return the length of the object.
    virtual GEOM_FT getLength(void) const
      { return GeomObj::list_Pos3d::getLength(); }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    //Return the maximum value of the i coordinate.
    virtual GEOM_FT GetMin(unsigned short int i) const;
    //Return the minimum value of the i coordinate.
    Polyline3d GetMayores(unsigned short int i,const GEOM_FT &d) const;
    //Return una Polyline3d con los vertices cuya coordenada i
    //es mayor que d.
    Polyline3d GetMenores(unsigned short int i,const GEOM_FT &d) const;
    //Return una Polyline3d con los vertices cuya coordenada i
    //es menor que d.
    Segment3d getSegment(const list_Pos3d::const_iterator &) const;
    Segment3d getSegment(const size_t &) const;
    //list_Pos3d Int(unsigned short int i,const GEOM_FT &d) const;
    list_Pos3d getIntersection(const Plane &) const;
    //Polyline3d Corta(unsigned short int i,const GEOM_FT &d) const;
    Polyline3d Separa(const Pos3d &p,const short int &sgn) const;
    Pos3d getCenterOfMass(void) const
      { return GeomObj::list_Pos3d::getCenterOfMass(); }

    iterator getFarthestPointFromSegment(iterator it1, iterator it2, GEOM_FT &pMaxDist);

    void Print(std::ostream &stream) const;
  };

#endif






