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
//GmGrupo2d.h

#ifndef GMGRUPO2D_H
#define GMGRUPO2D_H

#include "xc_basic/src/stl/pdeque.h"
#include "GeomObj2d.h"
#include "xc_utils/src/geom/listas/GmGrupo.h"

class Recta2d;

//! @ingroup GEOM
//
//! @brief Grupo de entidades geométricas en dos dimensiones.
class GmGrupo2d : public GmGrupo<GeomObj2d>
  {

    virtual GEOM_FT inercia(const Recta2d &e) const;
    virtual bool procesa_comando(CmdStatus &status);

  public:
    typedef pdeque_geom_obj::const_iterator const_iterator;
    typedef pdeque_geom_obj::iterator iterator;


    GmGrupo2d(void) : GmGrupo<GeomObj2d>() {}
    GmGrupo2d(const GmGrupo2d &otro) : GmGrupo<GeomObj2d>(otro) {}

    virtual GeomObj2d *clon(void) const
      { return new GmGrupo2d(*this); }

    inline virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    virtual Pos2d Cdg(void) const;

    virtual GEOM_FT Ix(void) const;
    //Momento de inercia respecto al CDG en ejes locales.
    virtual GEOM_FT Iy(void) const;
    //Momento de inercia respecto al CDG en ejes locales.
    GEOM_FT Pxy(void) const;
    //Producto de inercia respecto al CDG en ejes locales.

    void Print(std::ostream &stream) const;
    void Plot(Plotter &) const;

    void Transforma(const Trf2d &trf2d);

    virtual void SalvaCmd(std::ostream &os,const std::string &indent= "  ") const;
  };

#endif
