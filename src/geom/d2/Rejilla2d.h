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
//Rejilla2d.h

#ifndef Rejilla2d_h 
#define Rejilla2d_h 

#include "Superficie2d.h"
#include "../pos_vec/MatrizPos2d.h"

//! @ingroup GEOM
//
//! @brief Rejilla en dos dimensiones.
class Rejilla2d: public Superficie2d
  {
    MatrizPos2d puntos; //!< Puntos de la malla.
  public:
    Rejilla2d(void);
    Rejilla2d(int numSubdivIJ, int numSubdivJK);
    explicit Rejilla2d(const MatrizPos2d &m)
      : Superficie2d(), puntos(m) {}
    virtual ~Rejilla2d(void);
    virtual GeomObj *clon(void) const
      { return new Rejilla2d(*this); }

    inline const Pos2d &operator()(const size_t &i,const size_t &j) const
      { return puntos(i,j); }
    inline Pos2d &operator()(const size_t &i,const size_t &j)
      { return puntos(i,j); }
    inline MatrizPos2d &getPoints(void)
      { return puntos; }

    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    GEOM_FT Area(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Pxy(void) const;
    Pos2d Cdg(void) const;
    const matriz_FT &GetVertCoords(const size_t &,const size_t &) const;
    Pos2d GetPunto(const size_t &,const size_t &) const;
    Cuadrilatero2d GetQuad(const size_t &i,const size_t &j) const;
    bool In(const Pos2d &, const double &) const;
    
    void Transforma(const Trf2d &trf2d);

    void Print(std::ostream &os) const;
  };

#endif

