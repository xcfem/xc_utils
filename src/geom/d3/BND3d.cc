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
//BND.cc

#include "BND3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include <iostream>

BND3d::BND3d(const Pos3d &p_min,const Pos3d &p_max)
  : GeomObj3d(), cgisocub(p_min.ToCGAL(),p_max.ToCGAL()) {}
//! @brief Area of the face parallel to XY plane.
GEOM_FT BND3d::getAreaXYFace(void) const
  { return getLength()*Anchura(); }
//! @brief Area of the face parallel to XZ plane.
GEOM_FT BND3d::getAreaXZFace(void) const
  { return getLength()*Altura(); }
//! @brief Area of the face parallel to YZ plane.
GEOM_FT BND3d::getAreaYZFace(void) const
  { return Anchura()*Altura(); }
GEOM_FT BND3d::getArea(void) const
  {
    GEOM_FT A= 2*getAreaXYFace();
    A+= 2*getAreaXZFace();
    A+= 2*getAreaYZFace();
    return A;
  }
GEOM_FT BND3d::Ix(void) const
  {
    std::cerr << "Ix() no implementado." << std::endl;
    return 0;
  }
GEOM_FT BND3d::Iy(void) const
  {
    std::cerr << "Iy() no implementado." << std::endl;
    return 0;
  }
GEOM_FT BND3d::Iz(void) const
  {
    std::cerr << "Iy() no implementado." << std::endl;
    return 0;
  }

//! @brief Updates (enlarges) the boundary with the point.
void BND3d::Update(const Pos3d &p)
  {
    if(!In(p))
      {
        GEOM_FT xmin= GetXMin();
        GEOM_FT xmax= GetXMax();
        GEOM_FT ymin= GetYMin();
        GEOM_FT ymax= GetYMax();
        GEOM_FT zmin= GetZMin();
        GEOM_FT zmax= GetZMax();
        if(p.x()< xmin)
          xmin= p.x();
        else if(p.x()>xmax)
          xmax= p.x();
        if(p.y()<ymin)
          ymin= p.y();
        else if(p.y()>ymax)
          ymax= p.y();
        if(p.z()<zmin)
          zmin= p.z();
        else if(p.z()>zmax)
          zmax= p.z();
        PutPMin(Pos3d(xmin,ymin,zmin));
        PutPMax(Pos3d(xmax,ymax,zmax));
      }
  }

void BND3d::PutPMax(const Pos3d &pmax)
  { BND3d::operator=(BND3d(GetPMin(),pmax)); }
void BND3d::PutPMin(const Pos3d &pmin)
  { BND3d::operator=(BND3d(pmin,GetPMax())); }
void BND3d::PutPMinMax(const Pos3d &pmin,const Pos3d &pmax)
  { BND3d::operator=(BND3d(pmin,pmax)); }
Pos3d BND3d::GetPMax(void) const
  { return Pos3d(cgisocub.max()); }
Pos3d BND3d::GetPMin(void) const
  { return Pos3d(cgisocub.min()); }

Vector3d BND3d::Diagonal(void) const
  { return GetPMax() - GetPMin(); }
Pos3d BND3d::getCenterOfMass(void) const
  {
    Pos3d center_of_mass= GetPMin() + Diagonal()/2;
    return center_of_mass;
  }
bool BND3d::ClipLine(const Pos3d &p1,const Pos3d &p2) const
  { return LBClipLine(p1,p2); }
BND3d &BND3d::operator +=(const Pos3d &p)
  {
    PutPMinMax(pos_min(GetPMin(),p),pos_max(GetPMax(),p));
    return *this;
  }
BND3d &BND3d::operator +=(const BND3d &a)
  {
    PutPMinMax(pos_min(GetPMin(),a.GetPMin()),pos_max(GetPMax(),a.GetPMax()));
    return *this;
  }
BND3d operator +(const BND3d &a, const BND3d &b)
  {
    BND3d retval(a);
    return (retval+=b);
  }
bool operator ==(const BND3d &a,const BND3d &b)
  {
    if ( a.GetPMax() != b.GetPMax() ) return false; 
    if ( a.GetPMin() != b.GetPMin() ) 
      return false;
    else
      return true;
  }
bool BND3d::LBClipTest(const GEOM_FT &p,const GEOM_FT &q,GEOM_FT &u1,GEOM_FT &u2) const
//Esta funcion forma parte del algoritmo de recorte de l'ineas de 
//Liang-Barsky (p'agina 231 del libro Computer Graphics de Donald Hearn y 
//Pauline Baker isbn 0-13-578634-7.
  {
    GEOM_FT r;
    int retval= true;
    if(p<0)
      {
        r= q/p;
        if(r>u2)
          retval= false;
        else
          if(r>u1) u1= r;
      }
    else
      if(p>0)
        {
          r= q/p;
          if(r<u1)
            retval= false;
          else
            if(r<u2) u2= r;
        }
      else
        //p= 0, so the line is parallel to this boundary plane.
        if(q<0)
          retval= false; //the line is outside the boundary.
    return retval;
  }

bool BND3d::LBClipLine(const Pos3d &pa,const Pos3d &pb) const
  {
    const Pos3d PMin= GetPMin();
    const Pos3d PMax= GetPMax();
    Pos3d p1(pa);
    Pos3d p2(pb);
    GEOM_FT u1= 0, u2= 1, dx= p2.x()-p1.x(),dy,dz;
    if(LBClipTest(-dx,p1.x()-PMin.x(),u1,u2))
      if(LBClipTest(dx,PMax.x()-p1.x(),u1,u2))
        {
          dy= p2.y() - p1.y();
          if(LBClipTest(-dy,p1.y()-PMin.y(),u1,u2))
            if(LBClipTest(dy,PMax.y()-p1.y(),u1,u2))
              {
                dz= p2.z() - p1.z();
                if(LBClipTest(-dz,p1.z()-PMin.z(),u1,u2))
                  if(LBClipTest(dz,PMax.z()-p1.z(),u1,u2))
                    {
                      const Vector3d dd(dx,dy,dz);
                      if(u2<1)
                        {
                          p2= p1+ u2*dd;
                        }
                      if(u1>0)
                        {
                          p1+= u1*dd;
                        }
                      return true;
                    } //dz
              } //dy 
        } //dx
    return false;
  }
Pos3d BND3d::Vertice(unsigned int i) const
// Numeración de vértices y caras.
//
//      Z
//    ^
//    | /Y
//    |/
//    -----> X
//   
//   
//        4----------7
//       /|        / |
//      / |       /  |
//     /  |      /   |    0: base
//    5----------6   |    5: tapa 
//    |   |      |   |
//    |   3------|---2
//    |  /       |  /
//    | /        | /
//    |/         |/
//    0----------1
  {
    unsigned int indice= i%8;
    return Pos3d(cgisocub.vertex(indice));
  }
unsigned short int BND3d::RegionCode(const Pos3d &p,const double &tol) const
  {
    const Pos3d PMin= GetPMin();
    const Pos3d PMax= GetPMax();
    int reg_code= 0;
    const GEOM_FT tol_ft= tol;
    if ((p.x()-PMin.x()) < -tol_ft) reg_code= 1;  //00000001
    if ((p.x()-PMax.x()) >  tol_ft) reg_code|= 2; //00000010
    if ((p.y()-PMin.y()) < -tol_ft) reg_code|= 4; //00000100
    if ((p.y()-PMax.y()) >  tol_ft) reg_code|= 8; //00001000
    if ((p.z()-PMin.z()) < -tol_ft) reg_code|= 16;//00010000
    if ((p.z()-PMax.z()) >  tol_ft) reg_code|= 32;//00100000
    return reg_code;
  }
bool BND3d::In(const Pos3d &p,const double &tol) const
  {
    CGAL::Bounded_side side= cgisocub.bounded_side(p.ToCGAL());
    return (side != CGAL::ON_UNBOUNDED_SIDE);
  }

//! @brief Recrece el BND en la cantidad que se pasa como parámetro.
BND3d BND3d::Offset(const GEOM_FT &o) const
  {
    const Vector3d vo(o,o,o);
    return BND3d(GetPMin()-vo,GetPMax()+vo);
  }

CGBbox_3 BND3d::GetCGALBbox_3(void) const
  { return CGBbox_3(GetXMin(),GetYMin(),GetZMin(),GetXMax(),GetYMax(),GetZMax()); }
void BND3d::Print(std::ostream &stream) const
  {
    stream << "PMax= " << GetPMax() << ','
           << "PMin= " << GetPMin();
  }
