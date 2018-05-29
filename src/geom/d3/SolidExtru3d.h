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
//SolidExtru3d.h

#ifndef SOLIDEXTRU3D_H
#define SOLIDEXTRU3D_H

#include "Solido3d.h"
#include "BND3d.h"
#include "../matriz_FT.h"
#include "../pos_vec/Pos3d.h"


//! @ingroup GEOM
//
//! @brief SolidExtru3d, sólidos de extrusión.
//! La base inferior está a (z=-l/2)
//! y la base superior (z=+l/2).
template<class S>
class SolidExtru3d : public Solido3d
  {
  protected:
    S scc; //!< Surface that create the solid.
    GEOM_FT l; //!< Lentgh of the extruded solid (negative if undefined).
  public:
    SolidExtru3d(void): Solido3d(), scc(),l(1.0) {}
    SolidExtru3d(const S &secc,const GEOM_FT &lng): scc(secc), l(lng) {}
    SolidExtru3d(const SolidExtru3d<S> &se): Solido3d(se), scc(se.scc), l(se.l) {}
    SolidExtru3d<S> &operator=(const SolidExtru3d<S> &se)
      {
	Solido3d::operator=(se);
        scc=se.scc;
        l= se.l;
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new SolidExtru3d<S>(*this); }
    void Offset(const GEOM_FT &offset)
      //Similar al offset de AutoCad.
      {
        scc.Offset(offset);
        l+=2.0*offset;
      }
    SolidExtru3d<S> GetOffset(const GEOM_FT &offset) const
      {
        SolidExtru3d<S> retval(this);
        retval.Offset(offset);
        return retval;
      }
    const S &Seccion(void) const
      { return scc; }
    S &Seccion(void)
      { return scc; }
    //! @brief Return the object area.
    inline GEOM_FT getArea(void) const
      {
        GEOM_FT area= 2*scc.getArea();
        area+= scc.getLength()*l;
        return area;
      }
    //! @brief Return object length.
    inline GEOM_FT getLength(void) const
      { return l; }
    //! @brief Return the object volume
    inline GEOM_FT getVolume(void) const
      { return scc.getArea() * l; }
    inline virtual GEOM_FT Ix(void) const
      { return scc.Ix()*l + scc.getArea()*l*l*l/12; }
    inline virtual GEOM_FT Iy(void) const
      { return scc.Iy()*l + scc.getArea()*l*l*l/12; }
    inline virtual GEOM_FT Iz(void) const
      { return (scc.Ix()+scc.Iy())*l; }
/*     inline Pos3d getCenterOfMassOfBase(unsigned short int i) const */
/*     //Return el centro de gravedad de una de las bases. */
/*     //0 la base inferior (z=-l/2) y 1 la */
/*     //base superior (z=+l/2). */
/*       {  */
/*         if(i) */
/*           return scc.GetPosGlobal(Pos3d(0,0,l/2.0)); */
/*         else */
/*           return scc.GetPosGlobal(Pos3d(0,0,-l/2.0)); */
/*       } */
/*     inline Pos3d getCenterOfMassOfTop(void) const */
/*       { return getCenterOfMassOfBase(1); } */
/*     inline Pos3d getCenterOfMassOfBottom(void) const */
/*       { return getCenterOfMassOfBase(0); } */
/*     inline S GetBase(unsigned short int i) const */
/*     //0 la base inferior (z=-l/2) y 1 la */
/*     //base superior (z=+l/2). */
/*       {  */
/*         Pos3d p= getCenterOfMassOfBase(i); */
/*         S secc= scc; */
/*         secc.setOrg(p); */
/*         return secc; */
/*       } */
    inline virtual GEOM_FT GetMax(unsigned short int i) const
    //Return el valor maximo de la coordenada i.
      { 
        //return max(GetBase(0).GetMax(i),GetBase(1).GetMax(i));
	std::cerr << "SolidExtru3d::GetMax no implementada" << std::endl;
        return 0.0;
      }
    inline virtual GEOM_FT GetMin(unsigned short int i) const
    //Return el valor minimo de la coordenada i.
      {
        //return min(GetBase(0).GetMin(i),GetBase(1).GetMin(i));
	std::cerr << "SolidExtru3d::GetMax no implementada" << std::endl;
        return 0.0;
      }
    BND3d Bnd(void) const
    //Return la extension del objeto.
      { return GeomObj3d::Bnd(); }
    matriz_FT I(void) const
      { return GeomObj3d::I(); }
    Pos3d getCenterOfMass(void) const
      { return scc.getCenterOfMass(); }
  };

#endif






