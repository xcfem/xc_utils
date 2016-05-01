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
//PrismaRecto3d.h

#ifndef PRISMARECTO3D_H
#define PRISMARECTO3D_H

#include "Prisma3d.h"
#include "../SolidExtruPlgno3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"


//! @ingroup GEOM
//
//! @brief Prisma recto.
template<class PG>
class PrismaRecto3d : public Prisma3d
  {
    SolidExtruPlgno3d<PG> extru;
  protected:
    inline unsigned int get_num_vertices_plgno(void) const
      { return extru.GetNumVertices(); }
  public:
    PrismaRecto3d(void) {}
    PrismaRecto3d(const PG &secc,const GEOM_FT &lng): Prisma3d(), extru(secc,lng) {}
    PrismaRecto3d(const PrismaRecto3d<PG> &se): Prisma3d(se), extru(se.extru) {}
    PrismaRecto3d<PG> &operator=(const PrismaRecto3d<PG> &se)
      {
	Prisma3d::operator=(se);
	extru=se.extru;
        return *this;
      }
    inline virtual GeomObj *clon(void) const
      { return new PrismaRecto3d<PG>(*this); }
    inline void Offset(const GEOM_FT &offset)
      { extru.Offset(offset); }
    inline PrismaRecto3d<PG> GetOffset(const GEOM_FT &offset) const
      {
        PrismaRecto3d<PG> retval(*this);
        retval.Offset(offset);
        return retval;
      }
/*     inline virtual Poliedro::v_ind_vertices IndVerticesFaceta(unsigned int faceta) const */
/*       { return extru.IndVerticesFaceta(faceta); } */
    const PG &Seccion(void) const
      { return extru.Seccion(); }
    PG &Seccion(void)
      { return extru.Seccion(); }
    inline GEOM_FT Longitud(void) const
      { return extru.Longitud(); }
    inline GEOM_FT Area(void) const
      { return extru.Area(); }
    inline GEOM_FT Volumen(void) const
      { return extru.Volumen(); }
    inline virtual GEOM_FT Ix(void) const
      { return extru.Ix(); }
    inline virtual GEOM_FT Iy(void) const
      { return extru.Iy(); }
    inline virtual GEOM_FT Iz(void) const
      { return extru.Iz(); }
    inline virtual GEOM_FT GetMax(unsigned short int i) const
    //Devuelve el valor maximo de la coordenada i.
      { return extru.GetMax(i); }
    inline virtual GEOM_FT GetMin(unsigned short int i) const
    //Devuelve el valor minimo de la coordenada i.
      { return extru.GetMin(i); }
    inline virtual unsigned int GetNumVertices(void) const
      { return extru.GetNumVertices(); }
    inline virtual unsigned int GetNumVerticesFaceta(unsigned int faceta) const
      { return extru.GetNumVerticesFaceta(faceta); }
    inline virtual unsigned int GetNumAristas(void) const
      { return extru.GetNumAristas(); }
    inline virtual unsigned int GetNumFacetas(void) const
      { return extru.GetNumFacetas(); }
    inline Pos3d Vertice(unsigned int i) const
      { return extru.Vertice(i); } 
/*     virtual v_ind_vertices IndVerticesArista(unsigned int arista) const */
/*       { return extru.IndVerticesArista(arista); } */
    BND3d Bnd(void) const
    //Devuelve la extension del objeto.
      { return extru.Bnd(); }
    inline matriz_FT I(void) const
      { return extru.I(); }
    inline Pos3d Cdg(void) const
      { return extru.Cdg(); }
    inline Pos3d GetCdgTop(void) const
      { return extru.GetCdgTop(); }
    inline Pos3d GetCdgBottom(void) const
      { return extru.GetCdgBottom(); }
    inline Pos3d GetCdgFaceta(unsigned int faceta) const
      { return this->Faceta(faceta).Cdg(); }
    
  };

#endif
