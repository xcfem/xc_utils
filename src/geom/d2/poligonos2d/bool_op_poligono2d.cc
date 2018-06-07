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
//bool_op_poligono2d.cc
//Operaciones booleanas con polígonos.

#include "bool_op_poligono2d.h"
#include "Poligono2d.h"
#include "../../d1/Segment2d.h"
#include "../../d1/Polilinea2d.h"
#include "xc_utils/src/geom/d2/HalfPlane2d.h"
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Filtered_extended_homogeneous.h>
#include <CGAL/Nef_polyhedron_2.h>
#include <list>

//The Nef_Polyhedron types
typedef CGAL::Gmpz RT;
typedef CGAL::Filtered_extended_homogeneous<RT> Extended_kernel;
typedef CGAL::Nef_polyhedron_2<Extended_kernel> Nef_polyhedron;
typedef Nef_polyhedron::Point Point;
typedef Nef_polyhedron::Line Line;

typedef Nef_polyhedron::Explorer  PMCDec;
typedef PMCDec::Face_const_iterator Face_const_iterator;
typedef PMCDec::Hole_const_iterator Hole_const_iterator;
typedef PMCDec::Halfedge_around_face_const_circulator Halfedge_around_face_const_circulator;

const double escala= 1e5;
const double areaMin= 1/(escala*escala);

inline double double2intdouble(const double &d)
  { return sgn(d)*floor(std::abs(d)*escala); }

Point convert_point(const CGPoint_2 &p)
  { return Point(double2intdouble(p.hx()),double2intdouble(p.hy()),double2intdouble(p.hw())); }

Poligono2d devuelve_poligono(const Poligono2d &p)
  {
    Poligono2d retval;
    const size_t num_vertices= p.GetNumVertices();
    for(register size_t i=1;i<=num_vertices;i++)
      {
        const Pos2d &pto= p.Vertice(i);
        retval.push_back(Pos2d(pto.x()/escala,pto.y()/escala));
      }
    return retval;
  }

Nef_polyhedron Poligono2d_to_Nef_2(const Poligono2d &poly)
  {
    Poligono2d::vertex_iterator it = poly.vertices_begin();
    std::list<Point> l_of_p;        
    while(it != poly.vertices_end())
      {
        l_of_p.push_back(convert_point(*it));
        it++;
      }
    return Nef_polyhedron(l_of_p.begin(),l_of_p.end(),Nef_polyhedron::INCLUDED);
  }

Nef_polyhedron HalfPlane2d_to_Nef_2(const HalfPlane2d &sp)
  {
    Nef_polyhedron N(Line(double2intdouble(sp.a()),double2intdouble(sp.b()),double2intdouble(sp.c())),Nef_polyhedron::EXCLUDED);
    return N.complement();
  }

bool es_estandar(const Halfedge_around_face_const_circulator &c,const PMCDec &explo)
  {
    Halfedge_around_face_const_circulator i(c);
    const Halfedge_around_face_const_circulator c_end(c);

    bool retval=  explo.is_standard(i->vertex());
    i++;
    for(;i!=c_end;i++)
      retval&= explo.is_standard(i->vertex());
    return retval;
  } 

Poligono2d face_cycle(const Halfedge_around_face_const_circulator &c)
  {
    
    Poligono2d retval;
    Halfedge_around_face_const_circulator i(c);
    const Halfedge_around_face_const_circulator c_end(c);

    retval.push_back(Pos2d(CGAL::to_double(i->vertex()->point().x()),
                           CGAL::to_double(i->vertex()->point().y())));
    i++;
    for(;i!=c_end;i++)
      retval.push_back(Pos2d(CGAL::to_double(i->vertex()->point().x()),
 	                     CGAL::to_double(i->vertex()->point().y())));
    return retval;
  }

std::list<Poligono2d> Nef_2_to_Poligono2d(const Nef_polyhedron &n)
  {
    std::list<Poligono2d> retval;
    PMCDec D = n.explorer(); 

    Face_const_iterator fit = D.faces_begin();
    for (++fit; fit != D.faces_end(); ++fit)
      {
        Halfedge_around_face_const_circulator hfc(fit->halfedge());//Bordes de la faceta.
        if(fit->mark())
          {
            if(es_estandar(hfc,D))
              retval.push_back(Poligono2d(face_cycle(hfc)));
            Hole_const_iterator hit;
            for (hit = fit->fc_begin(); hit != fit->fc_end(); ++hit)
              {
                hfc = Halfedge_around_face_const_circulator(hit);
                if(es_estandar(hfc,D))
                  retval.push_back(devuelve_poligono(Poligono2d(face_cycle(hfc))));
              }
          }
      }
    return retval;
  }

Nef_polyhedron une(const Poligono2d &p1,const Poligono2d &p2)
  {
    Nef_polyhedron n1=Poligono2d_to_Nef_2(p1);
    Nef_polyhedron n2=Poligono2d_to_Nef_2(p2);
    if(p1.empty())
      return n2;
    else if(p2.empty())
      return n1;
    else
      return n1.join(n2);
  }

Nef_polyhedron une(const Nef_polyhedron &n1,const Poligono2d &p2)
  {
    if(p2.empty())
      return n1;
    else
      {
        Nef_polyhedron n2=Poligono2d_to_Nef_2(p2);
        return n1.join(n2);
      }
  }

std::list<Poligono2d> join(const Poligono2d &p1,const Poligono2d &p2)
  {
    std::list<Poligono2d> retval;
    if(p1.empty())
      if(!p2.empty())
        retval.push_back(p2);
    if(p2.empty())
      if(!p1.empty())
        retval.push_back(p1);
    if(!p1.empty() && !p2.empty())
      retval= Nef_2_to_Poligono2d(une(p1,p2));
    return retval;
  }

//! @brief Return la unión de los polígonos de la lista.
std::list<Poligono2d> join(const std::list<Poligono2d> &l)
  {
    std::list<Poligono2d> retval;
    if(!l.empty())
      {
        std::list<Poligono2d>::const_iterator i= l.begin();
        if(l.size()>1)
          {
            Nef_polyhedron nfRetval= Poligono2d_to_Nef_2(*i);
            i++;
            for(;i!=l.end();i++)
              if(!(i->empty()))
                nfRetval= une(nfRetval,*i);
            retval= Nef_2_to_Poligono2d(nfRetval);
          }
        else
          retval.push_back(*i);
      }
    return retval;
  }

//! @brief Return la unión de los polígonos de la lista con el que se pasa
//! como parámetro.
std::list<Poligono2d> join(const std::list<Poligono2d> &l,const Poligono2d &p)
  {
    std::list<Poligono2d> retval;
    if(p.empty())
      retval= join(l);
    else
      {
        if(!l.empty())
          {
            retval= l;
            retval.push_back(p);
            retval= join(retval);
          }
        else
          retval.push_back(p);
      }
    return retval;
  }

//! @brief Return verdadero si el polígono pl1 se superpone
//! el p2.
bool overlap(const Poligono2d &p1,const Poligono2d &p2)
  { return p1.Overlap(p2); }

//! @brief Return verdadero si alguno de los polígonos de l1 se superpone
//! con alguno de los de l2.
bool overlap(const std::list<Poligono2d> &l1,const std::list<Poligono2d> &l2)
  {
    bool retval= false;
    if(!l1.empty() && !l2.empty())
      {
        for(std::list<Poligono2d>::const_iterator i= l1.begin();i!=l1.end();i++)
          {
            const Poligono2d &p1= *i;
            for(std::list<Poligono2d>::const_iterator j= l2.begin();j!=l2.end();j++)
              if(p1.Overlap(*j))
                {
                  retval= true;
                  break;
                }
            if(retval)
              break;
          }
      }
    return retval;
  }

Nef_polyhedron interseca(const Poligono2d &p1,const Nef_polyhedron &n2)
  {
    Nef_polyhedron n1=Poligono2d_to_Nef_2(p1);
    return n1.intersection(n2);
  }
Nef_polyhedron interseca(const Poligono2d &p1,const Poligono2d &p2)
  {
    Nef_polyhedron n1=Poligono2d_to_Nef_2(p1);
    Nef_polyhedron n2=Poligono2d_to_Nef_2(p2);
    return n1.intersection(n2);
  }

//! @brief Return the intersection of the polygon with the half-plane.
// When the direction vector (VDir()) of the line has a very big modulus,
// , the function crashes when computing the intersection. The problem was
// fixed defining the line with points that were nearer between them
// (100 units apart).
Nef_polyhedron interseca(const Poligono2d &p,const HalfPlane2d &sp)
  {
    Nef_polyhedron n2=HalfPlane2d_to_Nef_2(sp);
    Nef_polyhedron n1=Poligono2d_to_Nef_2(p);
    Nef_polyhedron retval= n1.intersection(n2);
    return retval;
  }

//! @brief Return the polygons that result from clipping the polygons on the
//! list with the polygon argument.
std::list<Poligono2d> clip(const std::list<Poligono2d> &l,const Poligono2d &p)
  {
    std::list<Poligono2d> retval;
    if(!p.empty() && (p.getArea()>areaMin))
      {
        Nef_polyhedron tmp=Poligono2d_to_Nef_2(p);
        if(!l.empty())
          {
            std::list<Poligono2d> tmpLst;
            for(std::list<Poligono2d>::const_iterator i= l.begin();i!=l.end();i++)
              {
                if((*i).getArea()>areaMin)
                  {
                    tmpLst= Nef_2_to_Poligono2d(interseca(*i,tmp));
                    if(!tmpLst.empty())
                      retval.insert(retval.end(),tmpLst.begin(),tmpLst.end());
                  }
              }
          }
      }
    return retval;
  }

//! @brief Return the intersection de los dos polígonos.
std::list<Poligono2d> interseccion(const Poligono2d &p1,const Poligono2d &p2)
  { return Nef_2_to_Poligono2d(interseca(p1,p2)); }

//! @brief Return la intersection of the polygon and the half plane.
std::list<Poligono2d> interseccion(const Poligono2d &p,const HalfPlane2d &sp)
  { return Nef_2_to_Poligono2d(interseca(p,sp)); }

//! @brief Return the intersection of the polygons in the list with the
//! half plane.
std::list<Poligono2d> interseccion(const std::list<Poligono2d> &l,const HalfPlane2d &sp)
  {
    std::list<Poligono2d> retval;
    if(!l.empty())
      {
        std::list<Poligono2d> tmpLst;
        for(std::list<Poligono2d>::const_iterator i= l.begin();i!=l.end();i++)
          {
            tmpLst= interseccion(*i,sp);
            if(!tmpLst.empty())
              retval.insert(retval.end(),tmpLst.begin(),tmpLst.end());
          }
      }
    return retval;
  }


//! @brief Return los polígonos que resultan de intersecar los de la lista
//! con el que se pasa como parámetro.
std::list<Poligono2d> interseccion(const std::list<Poligono2d> &l,const Poligono2d &p)
  {
    const std::list<Poligono2d> retval= clip(l,p);
    return join(retval);
  }

//! @brief Return los polígonos que resultan de intersecar los de la lista
//! l1 con cada uno de los de la lista l2.
std::list<Poligono2d> interseccion(const std::list<Poligono2d> &l1,const std::list<Poligono2d> &l2)
  {
    std::list<Poligono2d> retval;
    if(!l2.empty())
      {
        std::list<Poligono2d> tmpLst;
        for(std::list<Poligono2d>::const_iterator i= l2.begin();i!=l2.end();i++)
          {
            tmpLst= interseccion(l1,*i);
            if(!tmpLst.empty())
              retval.insert(retval.end(),tmpLst.begin(),tmpLst.end());
          }
      }
    return join(retval);
  }

//! @brief Return the partition of the common area of both polygons
//! using the Voronoi algorithm.
void particiona(const Pos2d &c1,Poligono2d &p1,const Pos2d &c2,Poligono2d &p2)
  {
    if(overlap(p1,p2))
      {
        const Recta2d m= mediatriz(c1,c2);
        const HalfPlane2d sp1(m,c1);
        const HalfPlane2d sp2(m,c2);
        p1= Poligono2d(interseccion(p1,sp1));
        p2= Poligono2d(interseccion(p2,sp2));
      }
  }

//! @brief Return the partition of the common area of both polygons
//! using the Voronoi algorithm.
void particiona(Poligono2d &p1,Poligono2d &p2)
  {
    if(overlap(p1,p2))
      {
        const Pos2d c1= p1.getCenterOfMass();
        const Pos2d c2= p2.getCenterOfMass();
        particiona(c1,p1,c2,p2);
      }
  }

//! @brief Return the partition of the common area of both polygons lists
//! using the Voronoi algorithm.
void particiona(const Pos2d &c1,std::list<Poligono2d> &lp1,const Pos2d &c2,std::list<Poligono2d> &lp2)
  {
    if(overlap(lp1,lp2))
      {
        const Recta2d m= mediatriz(c1,c2);
        const HalfPlane2d sp1(m,c1);
        const HalfPlane2d sp2(m,c2);
        lp1= interseccion(lp1,sp1);
        lp2= interseccion(lp2,sp2);
      }
  }


//! @brief Return the partition using the Voronoi algorithm.
void particiona(const std::list<Pos2d> &centros,std::list<Poligono2d> &areas)
  {
    const size_t sz= areas.size();
    if(sz>1)
      {
        assert(centros.size()==sz);
        std::list<Pos2d>::const_iterator cI= centros.begin();
        for(std::list<Poligono2d>::iterator i= areas.begin();i!=areas.end();i++,cI++)
          {
	    Poligono2d &pI= *i;
            std::list<Pos2d>::const_iterator cJ= cI; cJ++;
            std::list<Poligono2d>::iterator j= i; j++;
            for(;j!=areas.end();j++,cJ++)
              {
	        Poligono2d &pJ= *j;
                if(overlap(pI,pJ))
                  particiona(*cI,pI,*cJ,pJ);
              }
          }
      }
  }


//! @brief Return the partition using the Voronoi algorithm.
void particiona(std::list<Poligono2d> &areas)
  {
    if(areas.size()>1)
      {
        std::list<Pos2d> centros;
        for(std::list<Poligono2d>::iterator i= areas.begin();i!=areas.end();i++)
          centros.push_back((*i).getCenterOfMass());
        particiona(centros,areas);
      }
  }
