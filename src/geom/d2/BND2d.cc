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
//BND2d.cc

#include "BND2d.h"
#include "../pos_vec/Pos2d.h"
#include "../pos_vec/Vector2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/d1/Polyline2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"
#include <iostream>
#include <plotter.h>
#include "xc_utils/src/geom/trf/Trf2d.h"

BND2d::BND2d(const Pos2d &p_min,const Pos2d &p_max)
  : GeomObj2d(), cgrectg(p_min.ToCGAL(),p_max.ToCGAL()) {}

void BND2d::Update(const Pos2d &p)
  {
    if(!In(p))
      {
        GEOM_FT xmin= GetXMin();
        GEOM_FT xmax= GetXMax();
        GEOM_FT ymin= GetYMin();
        GEOM_FT ymax= GetYMax();
        if(p.x()< xmin)
          xmin= p.x();
        else if(p.x()>xmax)
          xmax= p.x();
        if(p.y()<ymin)
          ymin= p.y();
        else if(p.y()>ymax)
          ymax= p.y();
        PutPMin(Pos2d(xmin,ymin));
        PutPMax(Pos2d(xmax,ymax));
      }
  }
void BND2d::PutPMax(const Pos2d &pmax)
  { BND2d::operator=(BND2d(GetPMin(),pmax)); }
void BND2d::PutPMin(const Pos2d &pmin)
  { BND2d::operator=(BND2d(pmin,GetPMax())); }
void BND2d::PutPMinMax(const Pos2d &pmin,const Pos2d &pmax)
  { BND2d::operator=(BND2d(pmin,pmax)); }
Pos2d BND2d::GetPMax(void) const
  { return Pos2d(cgrectg.max()); }
Pos2d BND2d::GetPMin(void) const
  { return Pos2d(cgrectg.min()); }

Poligono2d BND2d::GetPoligono(void) const
  {
    const Pos2d p1= GetPMin();
    const Pos2d p2= GetPMax();
    Poligono2d retval;
    retval.push_back(p1);
    retval.push_back(Pos2d(p2.x(),p1.y()));
    retval.push_back(p2);
    retval.push_back(Pos2d(p1.x(),p2.y()));
    return retval;
  }

//! @brief Return the object area.
GEOM_FT BND2d::getArea(void) const
  { return cgrectg.area(); }
Vector2d BND2d::Diagonal(void) const
  { return GetPMax() - GetPMin(); }
Pos2d BND2d::getCenterOfMass(void) const
  {
    Pos2d center_of_mass= GetPMin() + Diagonal()/2;
    return center_of_mass;
  }
GEOM_FT BND2d::Ix(void) const
  { return (Anchura()*Altura()*Altura()*Altura())/12; }
GEOM_FT BND2d::Iy(void) const
  { return (Altura()*Anchura()*Anchura()*Anchura())/12; }


//! @brief Return true it the boundary contains the point.
bool BND2d::In(const Pos2d &p) const
  {
    const GEOM_FT xmin= GetXMin();
    const GEOM_FT xmax= GetXMax();
    const GEOM_FT ymin= GetYMin();
    const GEOM_FT ymax= GetYMax();
    if(p.x()< xmin)
      return false;
    else if(p.x()>xmax)
      return false;
    else if(p.y()<ymin)
      return false;
    else if(p.y()>ymax)
      return false;
    else
      return true;
  }

//! @brief Return verdadero si el BND contiene a la polilínea.
bool BND2d::In(const Polyline2d &p) const
  { return In(p.begin(),p.end()); }

//! @brief Return verdadero si el BND contiene al polígono.
bool BND2d::In(const Poligono2d &p) const
  { return In(p.vertices_begin(),p.vertices_end()); }

//! @brief Return true if the boundary contains the point.
bool BND2d::Overlap(const Pos2d &p) const
  { return In(p); }

//! @brief Return true if the line and the boundary overlap.
bool BND2d::Overlap(const Recta2d &r) const
  { return Interseca(r); }
  
//! @brief Return true if the ray and the boundary overlap.
bool BND2d::Overlap(const SemiRecta2d &sr) const
  { return Interseca(sr); }

//! @brief Return true if the segment and the boundary overlap.
bool BND2d::Overlap(const Segment2d &sg) const
  { return Interseca(sg); }

//! @brief Return true if boundary overlap.
bool BND2d::Overlap(const BND2d &bnd) const
  { return do_intersect(cgrectg,bnd.cgrectg); }

//! @brief Return true if the polyline and the boundary overlap.
bool BND2d::Overlap(const Polyline2d &p) const
  {
    bool retval= Overlap(p.begin(),p.end());
    if(!retval)
      for(Polyline2d::const_iterator j=p.begin();j!=p.end();j++)
        if(Overlap(p.getSegment(j)))
          {
            retval= true;
            break;
          }
    return retval;
  }

bool BND2d::Overlap(const Poligono2d &p) const
  {
    bool retval= Overlap(p.vertices_begin(),p.vertices_end());
    if(!retval)
      retval= p.Overlap(GetPoligono());
    if(!retval)
      {
        const unsigned int nl= p.GetNumLados();
        for(unsigned int i= 1; i<=nl;i++)
          if(Overlap(p.Lado(i)))
            {
              retval= true;
               break;
            }
      }
    return retval;
  }

bool BND2d::Overlap(const std::list<Poligono2d> &l) const
  {
    bool retval= false;
    if(!l.empty())
      for(std::list<Poligono2d>::const_iterator i=l.begin();i!=l.end();i++)
        if(Overlap(*i))
          {
            retval= true;
            break;
          }
    return retval;
  }


bool BND2d::Interseca(const Recta2d &r) const
  { return do_intersect(cgrectg,r.ToCGAL()); }
bool BND2d::Interseca(const SemiRecta2d &sr) const
  { return do_intersect(cgrectg,sr.ToCGAL()); }
bool BND2d::Interseca(const Segment2d &sg) const
  { return do_intersect(cgrectg,sg.ToCGAL()); }
bool BND2d::Interseca(const BND2d &bnd) const
  { return do_intersect(cgrectg,bnd.cgrectg); }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void BND2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d pA= trf2d.Transforma(GetPMin());
    const Pos2d pB= trf2d.Transforma(GetPMax());
    (*this)= BND2d(pA,pB);
  }

BND2d &BND2d::operator+=(const Pos2d &p)
  {
    PutPMinMax(pos_min(GetPMin(),p),pos_max(GetPMax(),p));
    return *this;
  }
BND2d &BND2d::operator+=(const BND2d &a)
  {
    PutPMinMax(pos_min(GetPMin(),a.GetPMin()),pos_max(GetPMax(),a.GetPMax()));
    return *this;
  }
BND2d operator +(const BND2d &a, const BND2d &b)
  {
    BND2d retval(a);
    return (retval+=b);
  }
bool operator ==(const BND2d &a,const BND2d &b)
  {
    if ( a.GetPMax() != b.GetPMax() ) return false; 
    if ( a.GetPMin() != b.GetPMin() ) 
      return false;
    else
      return true;
  }
void BND2d::Print(std::ostream &stream) const
  {
    stream << "PMax= " << GetPMax() << ','
           << "PMin= " << GetPMin();
  }
void BND2d::Plot(Plotter &plotter) const
  {
    const Pos2d pmin= GetPMin();
    const Pos2d pmax= GetPMax();
    plotter.fline(pmin.x(),pmin.y(),pmax.x(),pmin.y());
    plotter.fline(pmax.x(),pmin.y(),pmax.x(),pmax.y());
    plotter.fline(pmax.x(),pmax.y(),pmin.x(),pmax.y());
    plotter.fline(pmin.x(),pmax.y(),pmin.x(),pmin.y());
  }
