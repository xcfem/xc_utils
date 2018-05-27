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
//SupPoligonal2d.cc

#include "SupPoligonal2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/d1/Polilinea2d.h"
#include "xc_utils/src/geom/d2/Semiplano2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "carsten_steger.h"
#include "xc_basic/src/util/matem.h"
#include "../BND2d.h"
#include <plotter.h>


#include "xc_utils/src/geom/pos_vec/ListaPos2d.h"




//! @brief Return los vertices del polígono.
GeomObj::list_Pos2d SupPoligonal2d::getVertices(void) const
  {
    unsigned int nv= GetNumVertices();
    GeomObj::list_Pos2d lv;
    for(register size_t i= 1; i <= nv; i++) lv.push_back(Vertice(i));
    return lv;
  }

//! @brief Return la normal al lado del polígono.
Vector2d SupPoligonal2d::getLado0Normal(const size_t i) const
  { return Lado0(i).Normal(); }


//! @brief Return la normal en el vértice del polígono.
Vector2d SupPoligonal2d::getVertex0Normal(const size_t i) const
  {
    const size_t nv= GetNumVertices();
    size_t I= i-1;size_t J= i;
    if(i==0)
      I= nv-1;
    const Vector2d n1= getLado0Normal(I);
    const Vector2d n2= getLado0Normal(J);
    return (n1+n2)/2.0;
  }

//! @brief Return la polilinea cerrada con los vértices del polígono.
Polilinea2d SupPoligonal2d::GetPolilinea(void) const
  {
    Polilinea2d retval;
    unsigned int nv= GetNumVertices();
    for(register size_t i= 1; i <= nv; i++) retval.AgregaVertice(Vertice(i));
    retval.AgregaVertice(Vertice(1)); //Cerramos la polilínea.
    return retval;
  }


Segmento2d SupPoligonal2d::Lado0(unsigned int i, unsigned int j) const
  { return Segmento2d(Vertice0(i),Vertice0(j)); }
Segmento2d SupPoligonal2d::Lado0(unsigned int i) const
  {
    const size_t nl= GetNumLados();
    unsigned int i1= i%nl;
    unsigned int i2= (i+1)%nl;
    return Lado0(i1,i2);
  }
Segmento2d SupPoligonal2d::Lado(unsigned int i) const
  { return Lado0(i-1); }

//! @brief Return the perimeter of the surface.
GEOM_FT SupPoligonal2d::getLength(void) const
  {
    unsigned int nl= GetNumLados();
    register GEOM_FT temp = 0;
    for(register unsigned int i= 1; i<=nl;i++)
      temp += Lado(i).getLength();
    return temp;
  }

GEOM_FT SupPoligonal2d::Area(void) const
  { return ::Abs(AreaSigno()); }

//! @brief Return el valor maximo de la coordenada i.
GEOM_FT SupPoligonal2d::GetMax(unsigned short int i) const
  { 
    register GEOM_FT mx= Vertice(0)(i);
    unsigned int nv= GetNumVertices();
    for(register unsigned short int j= 0;j < nv;j++)
      mx= max(Vertice(j)(i),mx);
    return mx;
  }

//! @brief Return el valor minimo de la coordenada i.
GEOM_FT SupPoligonal2d::GetMin(unsigned short int i) const
  {
    register GEOM_FT mn= Vertice(0)(i);
    unsigned int nv= GetNumVertices();
    for(register unsigned short int j= 0;j < nv;j++)
      mn= min(Vertice(j)(i),mn);
    return mn;
  }

//! @brief Return el centro de gravedad.
Pos2d SupPoligonal2d::getCenterOfMass(void) const
  {
     const GEOM_FT area= Area();
     return Pos2d(getMoment(1,0)/area,getMoment(0,1)/area);
  }
//! @brief Return the centroid (point interior to the polygon).
//! Return the centroid (point interior to the polygon).
//! See the book Sistemas de Información Geográfica de
//! Joaquín Bosque Sendra (Ed. Rialp ).
Pos2d SupPoligonal2d::Centroide(void) const
  {
    Pos2d retval=getCenterOfMass();
    if(In(retval)) return retval; //If the center of mass is inside, 
                                  //we prefer it.
    const BND2d bnd= Bnd();
    const Pos2d c= bnd.getCenterOfMass();
    const Recta2d r(c,c+Vector2d(0,100));
    list<Segmento2d> intersec= interseccion(*this,r);
    if(!intersec.empty())
      {
        Segmento2d sg= *intersec.begin();
        retval= sg.getCenterOfMass();
      }
    else
      cerr << getClassName() << "::" << __FUNCTION__
	   << "; error computing the polygon centroid: " << *this << endl;
    return retval;
  }
GEOM_FT SupPoligonal2d::moment_sign(const int &p,const int &q) const
  { return p_q_moment(*this,p,q); }
GEOM_FT SupPoligonal2d::getMoment(const int &p,const int &q) const
  {
    GEOM_FT retval= moment_sign(p,q); 
    if(AreaSigno()<0) retval*=-1;
    return retval;
  }

//! @brief Calcula el moment of inertia with respect to an axis parallel to the
//! x axis que pasa por el center of mass of the surface.
//! Ix = Integral y^2 dA
GEOM_FT SupPoligonal2d::Ix(void) const
  { 
    const GEOM_FT Ixo= getMoment(0,2);
    return Ixo-Area()*sqr(getCenterOfMass().y()); //Teorema de Steiner.
  }

//! @brief Calcula el moment of inertia with respect to an axis parallel to the
//! y axis that passes through the polygon centroid.
//! Iy = Integral x^2 dA
GEOM_FT SupPoligonal2d::Iy(void) const
  { 
    const GEOM_FT Iyo= getMoment(2,0);
    return Iyo-Area()*sqr(getCenterOfMass().x()); //Teorema de Steiner.
  }

//! @brief Calcula el product of inertia with respect to the axis parallel
//! to the axis x and y with origin in the polygon centroid.
//! Pxy = Integral x*y dA
GEOM_FT SupPoligonal2d::Pxy(void) const
  {
    const GEOM_FT Ixy= getMoment(1,1);
    const Pos2d center_of_mass=getCenterOfMass();
    const GEOM_FT dx= center_of_mass.x();
    const GEOM_FT dy= center_of_mass.y();
    return Ixy-Area()*dx*dy; //Theorem of parallel axis.
  }

//! @brief Return the points for which the polygon is almost tangent
//! to the direction argument.
// XXX Posiblemente falle con polígonos no convexos.
GeomObj::list_Pos2d SupPoligonal2d::getPosTangAprox(const Vector2d &v) const
  {
    const size_t sz= GetNumLados();
    std::vector<double> tangsEnVertices(sz+1);
    Segmento2d li= Lado0(sz-1);
    Segmento2d lj= Lado0(0);
    GEOM_FT anguloI= li.AnguloSigno(v),anguloJ= 0;
    const GEOM_FT dosPi= 2*M_PI;
    if(anguloI>=dosPi)
      anguloI-=dosPi;
    for(size_t i=0;i<sz;i++)
      {
        anguloJ= anguloI+lj.AnguloSigno(li);
        tangsEnVertices[i]= (anguloI+anguloJ)/2.0; 
        li= lj;
        anguloI= anguloJ;
        lj= Lado0(i+1);
      }
    tangsEnVertices[sz]= tangsEnVertices[0]+dosPi;

    GeomObj::list_Pos2d retval;
    for(size_t i=0;i<sz;i++)
      {
        li= Lado0(i);
        anguloI= tangsEnVertices[i];
        anguloJ= tangsEnVertices[i+1];
        if((anguloI<dosPi) && (anguloJ>=dosPi))
          {
            anguloI-=dosPi;
            anguloJ-=dosPi;
            const double s= li.getLength()*(-anguloI)/(anguloJ-anguloI);
            retval.AgregaSiNuevo(li.PtoParametricas(s));
          }
        else if(anguloI*anguloJ<=0)
          {
            const double s= li.getLength()*(-anguloI)/(anguloJ-anguloI);
            retval.AgregaSiNuevo(li.PtoParametricas(s));
          }
      }
    return retval;
  }

//! @brief Return the distance from the point to the perímeter
//! The distance is computed as the maximum of:
//! -The signed distances from the point to each of the half-planes
//!  that contain a side.
// If the vertices are in couterclockwise order, positive distances
// correspond to point AT THE SAME SIDE OF THE POLYGON with respect
// to the segment, otherwise the sign of the computed distance must
// be changed.
GEOM_FT SupPoligonal2d::DistSigno(const Pos2d &p,const bool &sentido_horario) const
  {
     const short int signo= (sentido_horario ? 1 : -1);
     const size_t nv= GetNumVertices();
     GEOM_FT retval= NAN;
     if(nv>0)
       {
         if(nv==1)
           retval= dist(Vertice(1),p);
         else if(nv==2)
           {
             Semiplano2d semiplano(Vertice(1),Vertice(2));
             retval= signo*semiplano.DistSigno(p);
           }
         else
           {
             //Distancia al primer lado
             Pos2d p1= Vertice(1);
             Pos2d p2= Vertice(2);
             Semiplano2d semiplano(p1,p2);
             retval= signo*semiplano.DistSigno(p);
             for(register unsigned int i=2; i<nv; i++)
               {
                 p1= Vertice(i);
                 p2= Vertice(i+1);
                 semiplano= Semiplano2d(p1,p2);
                 const GEOM_FT d_i= signo*semiplano.DistSigno(p);
                 retval= max(retval,d_i);
               }
             //Distancia al último lado.
             p1= Vertice(nv);
             p2= Vertice(1);
             semiplano= Semiplano2d(p1,p2);
             const GEOM_FT d_i= signo*semiplano.DistSigno(p);
             retval= max(retval,d_i);
           }
       }
    return retval;
  }

//! @brief Return the distance from the point to the polígono.
//! The distance is computed as the maximim of:
//! -The signed distances from the point to each of the planes that contain
//! one of the sides and are perpendicular to the surface.
//! If the point is inside the surface 0 is returned.
GEOM_FT SupPoligonal2d::Dist(const Pos2d &p) const
  {
    const GEOM_FT retval= DistSigno(p);
    return (retval >= 0 ? retval : 0);
  }


void SupPoligonal2d::Print(std::ostream &os) const
  {
    unsigned int nv= GetNumVertices();
    if(nv<1) return;
    os << Vertice(1);
    for(register unsigned int i= 2; i <= nv; i++)
      os << ", " << Vertice(i);
  }
void SupPoligonal2d::Plot(Plotter &plotter) const
  {
    unsigned int nv= GetNumVertices();
    if(nv<2) return;
    Pos2d p1= Vertice(1);
    for(register unsigned int i= 2; i <= nv; i++)
      {
        Pos2d p2= Vertice(i);
        plotter.fline(p1.x(),p1.y(),p2.x(),p2.y());
        p1=p2;
      }
  }


//! @brief Return true if the line and the polygonal surface overlap.
bool SupPoligonal2d::Overlap(const Recta2d &r) const
  {
    GeomObj::list_Pos2d tmp= GetPolilinea().Interseccion(r);
    return !tmp.empty();
  }
  
//! @brief Return true if the ray and the polygonal surface overlap.
bool SupPoligonal2d::Overlap(const SemiRecta2d &sr) const
  {
    GeomObj::list_Pos2d tmp= GetPolilinea().Interseccion(sr);
    return !tmp.empty();
  }

// SOLO debe llamarse desde Clip(recta)
std::list<Segmento2d> empalma(const std::list<Segmento2d> &lista)
  {
    std::list<Segmento2d> retval;
    if(lista.size()>1)
      {
        list<Segmento2d>::const_iterator i=lista.begin();
        Segmento2d s1= *i; i++;
        for(;i!=lista.end();i++)
          {
            const Segmento2d &s2= *i;
            if(dist2(s1.Destino(),s2.Origen())<sqrt_mchne_eps_dbl)
              s1= Segmento2d(s1.Origen(),s2.Destino());
            else
              {
                retval.push_back(s1);
                s1= s2;
              }
          }
        retval.push_back(s1);
      }
    else
      retval= lista;
    return retval;
  }

//! @brief Return la intersección del polígono con la recta (if exists).
Segmento2d SupPoligonal2d::Clip(const Recta2d &r) const
  {
    Segmento2d retval;
    list<Segmento2d> lista= sin_degenerados(interseccion(*this,r));
    if(lista.size()>1)
      lista= empalma(lista);
    if(!lista.empty())
      {
        retval= *lista.begin();
        if(lista.size()>1)
          {
            std::cerr << "SupPoligonal2d::Clip, el polígono "
                      << *this << " corta a la recta " << r << " en "
                      << lista.size() << " tramos." << std::endl;
	    std::cerr << "lista: ";
            ::print(std::cerr,lista.begin(),lista.end());
	    std::cerr << std::endl;
          }
      }
    return retval;
  }

//! @brief Return la intersección del polígono con la semirecta (if exists).
Segmento2d SupPoligonal2d::Clip(const SemiRecta2d &sr) const
  {
    Segmento2d retval;
    list<Segmento2d> lista= sin_degenerados(interseccion(*this,sr));
    if(!lista.empty())
      {
        retval= *lista.begin();
        if(lista.size()>1)
          std::cerr << "SupPoligonal2d::Clip, el polígono corta a la semirecta en "
                    << lista.size() << " tramos." << std::endl;
      }
    return retval;
  }

//! @brief Return la intersección del polígono con el segmento (if exists).
Segmento2d SupPoligonal2d::Clip(const Segmento2d &sg) const
  {
    Segmento2d retval;
    list<Segmento2d> lista= sin_degenerados(interseccion(*this,sg));
    if(!lista.empty())
      {
        retval= *lista.begin();
        if(lista.size()>1)
          std::cerr << "SupPoligonal2d::Clip, el polígono corta al segmento en "
                    << lista.size() << " tramos." << std::endl;
      }
    return retval;
  }

//! @brief Return la intersección del polígono con la recta.
list<Segmento2d> interseccion(const SupPoligonal2d &pg,const Recta2d &r)
  {
    list<Segmento2d> retval;
    if(pg.GetNumVertices()>0)
      {
        Polilinea2d pl= pg.GetPolilinea();
        GeomObj::list_Pos2d ptos= interseccion(r,pl);
        if(!ptos.empty())
          {
            GeomObj::list_Pos2d ordenados= r.Ordena(ptos);

            Polilinea2d tmp;
            tmp.assign(ordenados.begin(),ordenados.end());
            const size_t ns= tmp.GetNumSegmentos();
            for(size_t i= 1;i<=ns;i++)
              {
                const Segmento2d s= tmp.GetSegmento(i);
                if(pg.In(s.getCenterOfMass()))
                  retval.push_back(s);
              }
          }
      }
    return retval;     
  }

//! @brief Return la intersección del polígono con la recta.
list<Segmento2d> interseccion(const Recta2d &r,const SupPoligonal2d &pg)
  { return interseccion(pg,r); }

//! @brief Return la intersección del polígono con la semirecta.
list<Segmento2d> interseccion(const SupPoligonal2d &pg,const SemiRecta2d &sr)
  {
    
    list<Segmento2d> retval;
    if(!pg.GetNumVertices()) return retval;

    Polilinea2d pl= pg.GetPolilinea();
    
    GeomObj::list_Pos2d ptos= interseccion(sr,pl);
    const Pos2d org= sr.Origen();
    if(pg.In(org))
      ptos.push_front(org);

    GeomObj::list_Pos2d ordenados= sr.Ordena(ptos);

    Polilinea2d tmp;
    tmp.assign(ordenados.begin(),ordenados.end());
    const size_t ns= tmp.GetNumSegmentos();
    for(size_t i= 1;i<=ns;i++)
      {
        const Segmento2d s= tmp.GetSegmento(i);
        if(pg.In(s.getCenterOfMass()))
          retval.push_back(s);
      }
    return retval;
  }

//! @brief Return la intersección del polígono con la semirecta.
list<Segmento2d> interseccion(const SemiRecta2d &sr,const SupPoligonal2d &pg)
  { return interseccion(pg,sr); }

//! @brief Return la intersección del polígono con el segmento.
list<Segmento2d> interseccion(const SupPoligonal2d &pg,const Segmento2d &sg)
  {
    
    list<Segmento2d> retval;
    if(!pg.GetNumVertices()) return retval;

    Polilinea2d pl= pg.GetPolilinea();
    
    GeomObj::list_Pos2d ptos= interseccion(sg,pl);
    const Pos2d org= sg.Origen();
    if(pg.In(org))
      ptos.push_front(org);
    const Pos2d dest= sg.Destino();
    if(pg.In(org))
      ptos.push_back(dest);

    GeomObj::list_Pos2d ordenados= sg.Ordena(ptos);

    Polilinea2d tmp;
    tmp.assign(ordenados.begin(),ordenados.end());
    const size_t ns= tmp.GetNumSegmentos();
    for(size_t i= 1;i<=ns;i++)
      {
        const Segmento2d s= tmp.GetSegmento(i);
        if(pg.In(s.getCenterOfMass()))
          retval.push_back(s);
      }
    return retval;
  }

//! @brief Return la intersección del polígono con el segmento.
list<Segmento2d> interseccion(const Segmento2d &sg,const SupPoligonal2d &pg)
  { return interseccion(pg,sg); }
