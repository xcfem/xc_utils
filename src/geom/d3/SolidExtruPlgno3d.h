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
//SolidExtruPlgno3d.h

#ifndef SOLIDEXTRUPLGNO3D_H
#define SOLIDEXTRUPLGNO3D_H

#include "SolidExtru3d.h"

//! @ingroup GEOM
//
//! @brief Sólido de extrusión generado por un polígono.
template<class PG>
class SolidExtruPlgno3d : public SolidExtru3d<PG>
  {
  public:
    typedef SolidExtru3d<PG> solid_extru_pg;
    inline unsigned int get_num_vertices_plgno(void) const
      { return this->scc.GetNumVertices(); }
  public:
    SolidExtruPlgno3d(void) {}
    SolidExtruPlgno3d(const PG &secc,const GEOM_FT &lng): solid_extru_pg(secc,lng) {}
    SolidExtruPlgno3d<PG> &operator=(const SolidExtruPlgno3d<PG> &se)
      {
	solid_extru_pg::operator=(se);
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new SolidExtruPlgno3d<PG>(*this); }
    virtual unsigned int GetNumVertices(void) const
      { return 2*get_num_vertices_plgno(); }
    virtual unsigned int GetNumVerticesFaceta(unsigned int faceta) const;
    inline virtual unsigned int getNumEdges(void) const
      { return 3*this->scc.GetNumLados(); }
    inline virtual unsigned int GetNumFacetas(void) const
      { return 2+this->scc.GetNumLados(); }
    Pos3d Vertice(unsigned int i) const;
/*     virtual Poliedro::v_ind_vertices IndVerticesArista(unsigned int arista) const; */
/*     virtual Poliedro::v_ind_vertices IndVerticesFaceta(unsigned int faceta) const; */
    inline BND3d Bnd(void) const
    //Return la extension del objeto.
      { return solid_extru_pg::Bnd(); }
    inline FT_matrix I(void) const
      { return solid_extru_pg::I(); }
    inline Pos3d getCenterOfMass(void) const
      { return solid_extru_pg::getCenterOfMass(); }
    
  };

template <class PG>
unsigned int SolidExtruPlgno3d<PG>::GetNumVerticesFaceta(unsigned int faceta) const
  {
    unsigned int retval= 4;
    unsigned int nf= GetNumFacetas();
    unsigned int ifc= faceta%nf;
    if((ifc==0)||(ifc==(nf-1))) retval= get_num_vertices_plgno();
    return retval;
  }

template <class PG>
Pos3d SolidExtruPlgno3d<PG>::Vertice(unsigned int i) const
  {
    Pos3d p;
    const unsigned int num_vert_plgno= get_num_vertices_plgno();
    unsigned int j=i;
    if(i>num_vert_plgno) j-=num_vert_plgno;
    if(i<num_vert_plgno)
      p= this->GetBase(0).Vertice(j);
    else
      p= this->GetBase(1).Vertice(j);
    return p;
  }

/* template <class PG> */
/* Poliedro::v_ind_vertices SolidExtruPlgno3d<PG>::IndVerticesArista(unsigned int arista) const */
/*   { */
/*     const unsigned int num_edges= getNumEdges(); */
/*     Poliedro::v_ind_vertices va(2); */
/*     const unsigned int indice= arista%num_edges; */
/*     const unsigned int num_vert_plgno= get_num_vertices_plgno(); */
/*     if(indice<num_vert_plgno) //Si es una arista de la base */
/*       { */
/*         va[0]= indice; va[1]= indice + 1; */
/*         if(va[1]>=num_vert_plgno) va[1]= 0; //Cierra con el primer vértice de la base. */
/*         return va; */
/*       } */
/*     if(indice>=(2*num_vert_plgno)) //Si es una arista de la tapa. */
/*       { */
/*         va[0]= indice-num_vert_plgno; */
/*         va[1]= va[0] + 1; */
/*         if(va[1]>=2*num_vert_plgno) va[1]= num_vert_plgno; //Cierra con el primer vértice de la tapa. */
/*         return va; */
/*       } */
/* 	//En other caso, es una arista lateral. */
/*     va[1]= indice; */
/*     va[0]= indice - num_vert_plgno; */
/*     return va; */
/*   } */
/* template <class PG> */
/* Poliedro::v_ind_vertices SolidExtruPlgno3d<PG>::IndVerticesFaceta(unsigned int faceta) const */
/*   { */
/*     const unsigned int num_facetas= GetNumFacetas(); */
/*     const unsigned int num_vert_plgno= get_num_vertices_plgno(); */
/*     const unsigned int nv= GetNumVertices(); */
/*     const unsigned int ifac= faceta%num_facetas; */
/*     if(ifac == 0) //Es la base. */
/*       { */
/* 	    Poliedro::v_ind_vertices iv(num_vert_plgno); */
/*         for(register size_t i= 0;i<num_vert_plgno;i++) */
/*           iv[i]= i; */
/*         return iv; */
/*       } */
/*     if(ifac == num_facetas-1) //Es la tapa. */
/*       { */
/* 	    Poliedro::v_ind_vertices iv(num_vert_plgno); */
/*         for(register size_t i= nv-1,j=0;i>=num_vert_plgno;i--,j++) */
/*           iv[j]= i; */
/*         return iv; */
/*       } */
/*     //Es un lateral. */
/*     Poliedro::v_ind_vertices iv(4); */
/*     iv[0]= ifac-1; //En la base. */
/*     iv[1]= iv[0]+num_vert_plgno; //En la tapa. */
/*     iv[2]= iv[1]+1; //En la tapa. */
/*     if(iv[2]==nv) iv[2]= num_vert_plgno; */
/*     iv[3]= iv[0]+1; //En la base. */
/*     if(iv[3]==num_vert_plgno) iv[3]= 0; */
/*     return iv; */
/*   } */


#endif
