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
//Trf2d.cc

#include "Trf2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/matriz_FT.h"

// Trf2d from_racionales(const GEOM_FT &r00,const GEOM_FT &r01,const GEOM_FT &r02,
//              const GEOM_FT &r10,const GEOM_FT &r11,const GEOM_FT &r12)
//   {
//     const GEOM_RT hw= r00.denominator()*r01.denominator()
//                              *r10.denominator()*r11.denominator()
//                              *r02.denominator()*r12.denominator();
//     const GEOM_RT m00= r00.numerator()*r01.denominator()
//                              *r10.denominator()*r11.denominator()
//                              *r02.denominator()*r12.denominator();
//     const GEOM_RT m01= r00.denominator()*r01.numerator()
//                              *r10.denominator()*r11.denominator()
//                              *r02.denominator()*r12.denominator();
//     const GEOM_RT m02= r00.denominator()*r01.denominator()
//                              *r10.denominator()*r11.denominator()
//                              *r02.numerator()*r12.denominator();
//     const GEOM_RT m10= r00.denominator()*r01.denominator()
//                              *r10.numerator()*r11.denominator()
//                              *r02.denominator()*r12.denominator();
//     const GEOM_RT m11= r00.denominator()*r01.denominator()
//                              *r10.denominator()*r11.numerator()
//                              *r02.denominator()*r12.denominator();
//     const GEOM_RT m12= r00.denominator()*r01.denominator()
//                              *r10.denominator()*r11.denominator()
//                              *r02.denominator()*r12.numerator();
//     return Trf2d(m00,m01,m02,m10,m11,m12,hw);

//   }
// Trf2d::Trf2d( const GEOM_RT & m00,const GEOM_RT & m01,const GEOM_RT & m02,
//               const GEOM_RT & m10,const GEOM_RT & m11,const GEOM_RT & m12,
//               const GEOM_RT & hw)
// //Define la matriz de una transformación afin cualquiera.
// //La submatriz:
// //
// //    -1 [[ m00 m01]
// //  hw    [ m10 m11]] 
// //
// // contiene la información sobre escalado y rotación, 
// // el vector:
// //
// //    -1 [[ m02]
// //  hw    [ m12]] 
// //
// // contiene la parte traslacional de la transformación.
//   : Trf(), cgtrf(m00,m01,m02,m10,m11,m12,hw) {}

Trf2d::Trf2d( const GEOM_FT & m00,const GEOM_FT & m01,const GEOM_FT & m02,
              const GEOM_FT & m10,const GEOM_FT & m11,const GEOM_FT & m12)
  : Trf(), cgtrf(m00,m01,m02,m10,m11,m12) 
  {
    //Trf2d::operator=(from_racionales(m00,m01,m02,m10,m11,m12));
  }


Trf2d::Trf2d(const CGAL::Translation &tr,const Vector2d &v)
  : Trf(), cgtrf(tr,v.ToCGAL()) {}
Trf2d::Trf2d(const CGAL::Rotation &rot,const GEOM_RT &seno,const GEOM_RT &coseno)
  : Trf(), cgtrf(rot,seno,coseno) {}
// Trf2d::Trf2d(const CGAL::Reflection &ref,const Recta2d &r)
//   : Trf(), cgtrf(ref)) {}
Trf2d::Trf2d(const CGAL::Scaling &sc,const GEOM_FT &factor_escala)
  : Trf(), cgtrf(sc,factor_escala) {}
//  : Trf(), cgtrf(sc,factor_escala.numerator(),factor_escala.denominator()) {}
Trf2d::Trf2d(const CGAL::Identity_transformation &i)
  : Trf(), cgtrf(i) {}

matriz_FT Trf2d::Cartesianas(void) const
//Devuelve la matriz de transformación en cartesianas.
  {
    matriz_FT retval(3,3,0.0);
    retval(1,1)= Cartesianas(1,1); retval(1,2)= Cartesianas(1,2); retval(1,3)= Cartesianas(1,3);
    retval(2,1)= Cartesianas(2,1); retval(2,2)= Cartesianas(2,2); retval(2,3)= Cartesianas(2,3);
    retval(3,3)= Cartesianas(3,3);
    return retval;
  }
matriz_FT Trf2d::Homogeneas(void) const
//Devuelve la matriz de transformación en homogéneas.
  {
    matriz_FT retval(3,3,0.0);
    retval(1,1)= Homogeneas(1,1); retval(1,2)= Homogeneas(1,2); retval(1,3)= Homogeneas(1,3);
    retval(2,1)= Homogeneas(2,1); retval(2,2)= Homogeneas(2,2); retval(2,3)= Homogeneas(2,3);
    retval(3,3)= Homogeneas(3,3);
    return retval;
  }
CGPoint_2 Trf2d::Transforma(const CGPoint_2 &cgpt2) const
  { return cgtrf.transform(cgpt2);  }
Pos2d Trf2d::Transforma(const Pos2d &p) const
  { return Pos2d(Transforma(p.ToCGAL())); }
Vector2d Trf2d::Transforma(const Vector2d &v) const
  { return Vector2d(cgtrf.transform(v.ToCGAL())); }
GeomObj::list_Pos2d Trf2d::Transforma(const GeomObj::list_Pos2d &lp2d) const
//Devuelve los puntos de la lista transformados.
  {
    GeomObj::list_Pos2d retval(lp2d);
    Transforma(retval.begin(),retval.end());
    return retval;
  }
Pos2d Trf2d::operator()(const Pos2d &p) const
  { return Transforma(p); }
Vector2d Trf2d::operator()(const Vector2d &v) const
  { return Transforma(v); }
GeomObj::list_Pos2d Trf2d::operator()(const GeomObj::list_Pos2d &lp2d) const
  { return Transforma(lp2d); }
Trf2d operator*(const Trf2d &a,const Trf2d &b)
  {
    Trf2d retval(a*b);
    return retval;
  }
