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
//Ref3d3d.h

#ifndef REF3D3D_H
#define REF3D3D_H

#include "Ref.h"
#include "../sis_coo/SisCooRect3d3d.h"
#include "../d3/GeomObj3d.h"
#include "../pos_vec/Pos3d.h"

class Recta3d;
class Vector3d;
class Plano3d;

//! @ingroup SisRef
//! 
//! @brief Sistema de referencia tridimensional definido
//! en un sistema de referencia tridimensional.
class Ref3d3d : public Ref<SisCooRect3d3d>
  {
  public:
    typedef GeomObj3d::list_Pos3d list_Pos3d;
    typedef Ref<SisCooRect3d3d> BaseRef;

  protected:

/*     void salva_org(ostream &os,const string &indent) const */
/*       { */
/*         os << indent << "\\org{"; */
/*         org.salva_miembros(os,""); */
/*         os << '}' << endl; */
/*       } */
/*     void salva_miembros(ostream &os,const string &indent) const */
/*       { */
/*         salva_org(os,indent); */
/*         os << indent + "  }" << endl; */
/*         os << indent << "\\ejes" << endl */
/*            << indent + "  {" << endl; */
/*         trf.SalvaCmd(os,indent+"  "); */
/*         os << indent + "  }" << endl; */
/*       } */
  public:
    Ref3d3d(void);
    Ref3d3d(const Ref3d3d &otro);
    Ref3d3d(const Pos3d &o);
    Ref3d3d(const Pos3d &o,const Pos3d &p);
    Ref3d3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Ref3d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2);
    Ref3d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2,const Vector3d &v3);
    Ref3d3d(const Recta3d &r,const Pos3d &p);
    Ref3d3d &operator =(const Ref3d3d &otro);
    Vector3d GetI(void) const;
    //Devuelve el vector unitario I en el sistema global.
    Vector3d GetJ(void) const;
    //Devuelve el vector unitario J en el sistema global.
    Vector3d GetK(void) const;
    //Devuelve el vector unitario K en el sistema global.
    Recta3d GetEjeX(void) const; //Devuelve la recta que define el eje x.
    Recta3d GetEjeY(void) const; //Devuelve la recta que define el eje y.
    Recta3d GetEjeZ(void) const; //Devuelve la recta que define el eje z.
    Plano3d GetPlanoXY(void) const; //Devuelve el plano XY.
    Plano3d GetPlanoXZ(void) const; //Devuelve el plano XZ.
    Plano3d GetPlanoYZ(void) const; //Devuelve el plano YZ.
/*     virtual void Mueve(double Ax,double Ay,double Az) */
/*       { org.Mueve(Ax,Ay,Az); } */
/*     inline virtual void GiraX(const double &ang_rad) */
/*       { trf.GiraX(ang_rad); } */
/*     inline virtual void GiraY(const double &ang_rad) */
/*       { trf.GiraY(ang_rad); } */
/*     inline virtual void GiraZ(const double &ang_rad) */
/*       { trf.GiraZ(ang_rad); } */

    //double GetZLocal(const Pos3d &p) const;
    //Devuelve la Z del punto p expresado en locales
    //expresada en coordenadas locales.

    //Devuelve el vector v expresado en globales
    //expresado en coordenadas locales.
/*     m_double Trf(const m_double &v) */
/*       { */
/*         m_double vt(3,1); */
/*         vt= trf * v; */
/*         return vt; */
/*       } */
    //virtual void SalvaCmd(ostream &os,const string &indent= "  ") const;
    virtual ~Ref3d3d(void);
  };

#endif






