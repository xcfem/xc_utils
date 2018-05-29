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
//BND2d.h

#ifndef BND2D_H
#define BND2D_H

#include "GeomObj2d.h"
#include "../tipos_cgal.h"

class Segmento2d;
class SemiRecta2d;
class Poligono2d;
class Polilinea2d;


//! @ingroup GEOM
//
//! @brief "boundary" en dos dimensiones.
class BND2d: public GeomObj2d
  {
    CGIsoRectangle_2 cgrectg;
    template <class inputIterator>
    bool Overlap(inputIterator begin, inputIterator end) const;
  public:
    BND2d(void): GeomObj2d(),cgrectg() {}
    BND2d(const Pos2d &p_min,const Pos2d &p_max);
    BND2d(const BND2d &otro) 
      :  GeomObj2d(otro),cgrectg(otro.cgrectg) {}
    BND2d &operator =(const BND2d &otro) 
      {
	GeomObj2d::operator=(otro);
        cgrectg=otro.cgrectg;
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new BND2d(*this); }
    inline virtual unsigned short int Dimension(void) const
    //Return the dimension of the object 0, 1, 2 or 3.
      { return 2; }
    inline virtual GEOM_FT Anchura(void) const
      { return GetXMax()-GetXMin(); }
    inline GEOM_FT Altura(void) const
      { return GetYMax()-GetYMin(); }

    Poligono2d GetPoligono(void) const;
    //! @brief Return the object length.
    inline virtual GEOM_FT getLength(void) const
      { return 2*Anchura()+2*Altura(); }
    Vector2d Diagonal(void) const;
    virtual GEOM_FT Area(void) const;
    //! @brief Return the volume of the object.
    inline virtual GEOM_FT getVolume(void) const
      { return 0.0; }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    inline virtual GEOM_FT Pxy(void) const
      { return 0.0; }

    void Update(const Pos2d &);
    void PutPMax(const Pos2d &);
    void PutPMin(const Pos2d &);
    void PutPMinMax(const Pos2d &,const Pos2d &);
    Pos2d GetPMax(void) const;
    Pos2d GetPMin(void) const;
    inline GEOM_FT GetMax(unsigned short int i) const
      { return cgrectg.max_coord(i-1); }
    inline GEOM_FT GetMin(unsigned short int i) const
      { return cgrectg.min_coord(i-1); }

    Pos2d getCenterOfMass(void) const;

    bool In(const Pos2d &) const;
    template <class inputIterator>
    bool In(inputIterator begin, inputIterator end) const;
    bool In(const Polilinea2d &) const;
    bool In(const Poligono2d &) const;
    bool Overlap(const Pos2d &) const;
    bool Overlap(const Recta2d &r) const;
    bool Overlap(const SemiRecta2d &sr) const;
    bool Overlap(const Segmento2d &sg) const;
    bool Overlap(const BND2d &) const;
    bool Overlap(const Polilinea2d &) const;
    bool Overlap(const Poligono2d &) const;
    bool Overlap(const std::list<Poligono2d> &) const;
    bool Interseca(const Recta2d &r) const;
    bool Interseca(const SemiRecta2d &sr) const;
    bool Interseca(const Segmento2d &sg) const;
    bool Interseca(const BND2d &) const;

    void Transforma(const Trf2d &trf2d);

    BND2d &operator +=(const Pos2d &p);
    BND2d &operator +=(const BND2d &a);
    friend BND2d operator +(const BND2d &a, const BND2d &b);
    friend bool operator ==(const BND2d &a,const BND2d &b);
    void Print(std::ostream &stream) const;
    void Plot(Plotter &) const;
  };

inline bool intersecan(const Recta2d &r,const BND2d &bnd)
  { return bnd.Interseca(r); }
inline bool intersecan(const SemiRecta2d &sr,const BND2d &bnd)
  { return bnd.Interseca(sr); }
inline bool intersecan(const Segmento2d &sg,const BND2d &bnd)
  { return bnd.Interseca(sg); }
inline bool intersecan(const BND2d &bnd,const Recta2d &r)
  { return bnd.Interseca(r); }
inline bool intersecan(const BND2d &bnd,const SemiRecta2d &sr)
  { return bnd.Interseca(sr); }
inline bool intersecan(const BND2d &bnd,const Segmento2d &sg)
  { return bnd.Interseca(sg); }

//!@brief Return verdadero si todos los objetos de la secuencia
//! están contenidos en el BND.
template <class inputIterator>
bool BND2d::In(inputIterator begin, inputIterator end) const
  {
    bool retval= true;
    for(inputIterator i= begin;i!=end;i++)
      if(!In(*i))
        {
          retval= false;
          break;
        }
    return retval;
  }

//!@brief Return verdadero si alguno de los objetos de la secuencia
//! está contenido total o parcialmente en el polígono.
template <class inputIterator>
bool BND2d::Overlap(inputIterator begin, inputIterator end) const
  {
    bool retval= false;
    for(inputIterator i= begin;i!=end;i++)
      if(Overlap(*i))
        {
          retval= true;
          break;
        }
    return retval;
  }

#endif
