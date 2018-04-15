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
//Polilinea3d.

#ifndef POLILINEA3D_H
#define POLILINEA3D_H

#include "../pos_vec/Pos3d.h"
#include "../listas/PoliPos.h"
#include "Linea3d.h"
#include "Segmento3d.h"

//! @ingroup GEOM
//
//! @brief Polilínea en 3 dimensiones.
class Polilinea3d : public Linea3d, public GeomObj::list_Pos3d
  {
  public:
    Polilinea3d(void): Linea3d(), GeomObj::list_Pos3d() {}
    virtual GeomObj *clon(void) const
      { return new Polilinea3d(*this); }
    virtual void Mueve(const Vector3d &);
    const GeomObj::list_Pos3d &getVertices(void) const
      { return *this; }
    inline size_t GetNumVertices(void) const
      { return GeomObj::list_Pos3d::size(); }
    size_t GetNumSegmentos(void) const;

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

    virtual GEOM_FT Longitud(void) const
      //Return the longitud de la Polilinea3d.
      { return GeomObj::list_Pos3d::Longitud(); }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    //Return the maximum value of the i coordinate.
    virtual GEOM_FT GetMin(unsigned short int i) const;
    //Return the minimum value of the i coordinate.
    Polilinea3d GetMayores(unsigned short int i,const GEOM_FT &d) const;
    //Return una Polilinea3d con los vertices cuya coordenada i
    //es mayor que d.
    Polilinea3d GetMenores(unsigned short int i,const GEOM_FT &d) const;
    //Return una Polilinea3d con los vertices cuya coordenada i
    //es menor que d.
    Segmento3d GetSegmento(const list_Pos3d::const_iterator &) const;
    Segmento3d GetSegmento(const size_t &) const;
/*     virtual list_Pos3d Int(unsigned short int i, const double d) const */
/*       { */
/*         std::cerr << "Polilinea3d Int(i,d) not implemented" << endl; */
/*         return list_Pos3d(); */
/*       } */
    list_Pos3d Int(unsigned short int i,const GEOM_FT &d) const;
    //Return las intersecciones de la Polilinea3d con el plano
    //coord_i= d
    list_Pos3d getIntersection(const Plano3d &) const;
    Polilinea3d Corta(unsigned short int i,const GEOM_FT &d) const;
    //Return the Polilinea3d con los vertices correspondientes a los
    //cortes con el plano coord_i= d
    Polilinea3d Separa(const Pos3d &p,const short int &sgn) const;
    //Suponemos que p es vertice de la Polilinea3d
    //Return el trozo de Polilinea3d:
    //hasta p si sgn < 0
    //desde p si sgn >= 0
    Pos3d Cdg(void) const
      { return GeomObj::list_Pos3d::Cdg(); }

    iterator getFarthestPointFromSegment(iterator it1, iterator it2, GEOM_FT &pMaxDist);

    void Print(std::ostream &stream) const;
  };

#endif






