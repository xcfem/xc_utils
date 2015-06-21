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
//SemiEspacio3d.cc

#include "SemiEspacio3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"


//! @brief Constructor por defecto.
SemiEspacio3d::SemiEspacio3d(const Plano3d &p)
  : GeomObj3d(), lim(p) {}

//! @brief Devuelve el plano que limita el semiespacio.
const Plano3d &SemiEspacio3d::getPlanoLimite(void) const
  { return lim; }

void SemiEspacio3d::setPlanoLimite(const Plano3d &p)
  { lim= p; }

bool SemiEspacio3d::procesa_comando(CmdStatus &status)
  {
    const std::string &cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SemiEspacio3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "setPlano")
      {
        lim= interpretaPlano3d(status.GetString());
        return true;
      }
    else if(cmd == "planoLimite")
      {
        lim.LeeCmd(status);
        return true;
      }
    else if(cmd == "swap")
      {
        status.GetString();
        Swap();
        return true;
      }
    else
      return GeomObj3d::procesa_comando(status);
  }

//! @brief Devuelve verdadero si el punto está dentro del semiplano.
//! los puntos de la recta límite son del semiplano
bool SemiEspacio3d::In(const Pos3d &p, const double &tol) const
  {
    bool retval= false;
    if(lim.LadoNegativo(p))
      retval= true;
    else if(lim.In(p,tol))
      retval= true;
    return retval;
  }

//! @brief Devuelve la distancia al cuadrado desde el punto al semiplano.
GEOM_FT SemiEspacio3d::distSigno(const Pos3d &p) const
  { return lim.PseudoDist(p); }

//Devuelve la distancia al cuadrado desde el punto al semiplano.
GEOM_FT SemiEspacio3d::distSigno2(const Pos3d &p) const
  { return lim.PseudoDist2(p); }

//Devuelve la distancia al cuadrado desde el punto al semiplano.
GEOM_FT SemiEspacio3d::dist(const Pos3d &p) const
  { return fabs(distSigno(p)); }

//Devuelve la distancia al cuadrado desde el punto al semiplano.
GEOM_FT SemiEspacio3d::dist2(const Pos3d &p) const
  { return fabs(distSigno2(p)); }

//! @brief Devuelve el ángulo que forma con el semiespacio que
//! se pasa como parámetro.
GEOM_FT SemiEspacio3d::getAngulo(const SemiEspacio3d &se) const
  { return angulo(lim,se.getPlano()); }

//! @brief Devuelve el ángulo que forma con el plano que
//! se pasa como parámetro.
GEOM_FT SemiEspacio3d::getAngulo(const Plano3d &p) const
  { return angulo(lim,p); }

//! @brief Devuelve el ángulo que forma con el vector que
//! se pasa como parámetro.
GEOM_FT SemiEspacio3d::getAngulo(const Vector3d &v) const
  { return angulo(v,lim); }

//! @brief Devuelve la arista de la intersección entre semiespacios.
Recta3d SemiEspacio3d::getLima(const SemiEspacio3d &se) const
  {
     const Recta3d retval= lim.Interseccion(se.lim);
     if(!retval.exists())
       std::cerr << "getLima: los planos que limitan los semiespacios no se cortan."
                 << std::endl;
     return retval;
  }

//!brief Devuelve la dimensión del objeto 0, 1, 2 ó 3.
unsigned short int SemiEspacio3d::Dimension(void) const
  { return 3; }
GEOM_FT SemiEspacio3d::Longitud(void) const
  { return NAN; }
GEOM_FT SemiEspacio3d::Area(void) const
  { return NAN; }
GEOM_FT SemiEspacio3d::Volumen(void) const
  { return NAN; }
Pos3d SemiEspacio3d::Cdg(void) const
  { return lim.Cdg(); }

//! @brief Devuelve el momento de inercia respecto al CDG en ejes locales.
GEOM_FT SemiEspacio3d::Ix(void) const
  { return NAN; }

//! @brief Devuelve el momento de inercia respecto al CDG en ejes locales.
GEOM_FT SemiEspacio3d::Iy(void) const
  { return NAN; }

//! @brief Devuelve el producto de inercia.
GEOM_FT SemiEspacio3d::Pxy(void) const
  { return NAN; }

//! @brief Devuelve el momento de inercia respecto al CDG en ejes locales.
GEOM_FT SemiEspacio3d::Iz(void) const
  { return NAN; }

//! @brief Devuelve verdadero si los semiespacios son iguales.
bool operator==(const SemiEspacio3d &r1,const SemiEspacio3d &r2)
  {
    if(&r1.lim==&r2.lim)
      return true;
    else
      return (r1.lim==r2.lim); 
  }

//! @brief Devuelve un vector normal al plano que limita
//! el semiespacio dirigido hacia el exterior del mismo.
Vector3d SemiEspacio3d::NormalExterior(void) const
  { return lim.Normal(); }

//! @brief Devuelve un vector normal al plano que limita
//! el semiespacio dirigido hacia el exterior del mismo.
Vector3d SemiEspacio3d::NormalInterior(void) const
  { return -NormalExterior(); }

//! @brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro
any_const_ptr SemiEspacio3d::GetProp(const std::string &cod) const
  {
    static GEOM_FT tmp_ft= 0.0;
    if(cod=="getNormalExterior")
      {
        tmp_gp_vector3d= NormalExterior();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getNormalInterior")
      {
        tmp_gp_vector3d= NormalInterior();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getBase1")
      {
        tmp_gp_vector3d= lim.Base1();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getBase2")
      {
        tmp_gp_vector3d= lim.Base2();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getDistSigno")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_ft= distSigno(tmp);
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getDistSigno2")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_ft= distSigno2(tmp);
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getDist")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_ft= dist(tmp);
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getDist2")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_ft= dist2(tmp);
        return any_const_ptr(tmp_ft);
      }
    else if(cod=="getInterseccionConRecta")
      {
        const Recta3d tmp= popRecta3d(cod);
        GeomObj3d::list_Pos3d lista= interseccion(lim,tmp);
        if(!lista.empty())
          tmp_gp_pos3d= lista[0];
	else
	  std::cerr << "getInterseccionConRecta: la recta no corta al plano." << std::endl;
        return any_const_ptr(tmp_gp_pos3d);
      }
    else if(cod=="getLima")
      {
        const SemiEspacio3d tmp= popSemiEspacio3d(cod);
        tmp_gp_recta3d= getLima(tmp);
        return any_const_ptr(tmp_gp_recta3d);
      }
    else if(cod=="getPlanoLimite")
      {
        return any_const_ptr(lim);
      }
    else
      return GeomObj3d::GetProp(cod);
  }

//! @brief Imprime el semiespacio
void SemiEspacio3d::Print(std::ostream &os) const
      { os << lim; }

//! @brief Devuelve los puntos de intersección entre los semiespacios.
TripletMap<Pos3d> puntos_interseccion(const std::deque<SemiEspacio3d> &se)
  {
    TripletMap<Pos3d> retval;
    const size_t sz= se.size();
    for(size_t i=0;i<sz;i++)
      for(size_t j=i+1;j<sz;j++)
        for(size_t k=j+1;k<sz;k++)
	  {
            const Pos3d p= punto_interseccion(se[i].getPlano(),se[j].getPlano(),se[k].getPlano());
            if(p.exists())
              retval[Triplete(i,j,k)]= p;
          }
    return retval;
  }

//! @brief Devuelve los vertices del poliedro intersección de los semiespacios.
TripletMap<Pos3d> vertices_poliedro(const std::deque<SemiEspacio3d> &se, const double &tol)
  {
    TripletMap<Pos3d> tmp= puntos_interseccion(se);
    TripletMap<Pos3d> retval= tmp;
    for(std::deque<SemiEspacio3d>::const_iterator j=se.begin();j!=se.end();j++)
      for(TripletMap<Pos3d>::const_iterator i= tmp.begin();i!=tmp.end();i++)
        if((*j).Out((*i).second,tol))
          {
            retval.erase(i->first);
            continue;
          }
    if(retval.size()<4)
      std::cerr << "vertices_poliedro; se obtuvieron menos de cuatro vértices."
                << std::endl;
    for(TripletMap<Pos3d>::const_iterator i= retval.begin();i!=retval.end();i++)
      {
        for(TripletMap<Pos3d>::const_iterator j= retval.begin();j!=retval.end();j++)
          if(j!=i)
            {
              const GEOM_FT d2= dist2(i->second,j->second);
              if(d2<1e-4)
                {
		  std::cerr << "Los vértices: ";
                  retval.PrintMember(std::cerr,i);
		  std::cerr << " y ";
                  retval.PrintMember(std::cerr,j);
		  std::cerr << " están muy próximos. d= "
                            << sqrt(d2) << std::endl;
                }
            }
      }
    return retval;
  }

//! @brief Devuelve las rectas de intersección entre los semiespacios.
std::deque<Recta3d> rectas_interseccion(const std::deque<SemiEspacio3d> &se)
  {
    std::deque<Recta3d> retval;
    const size_t sz= se.size();
    for(size_t i=0;i<sz;i++)
      for(size_t j=i+1;j<sz;j++)
        {
          const Recta3d r= recta_interseccion(se[i].getPlano(),se[j].getPlano());
          if(r.exists())
            retval.push_back(r);
        }
    return retval;
  }

//! @brief Devuelve los vectores normales a cada uno de los semiespacios.
std::deque<Vector3d> vectores_normales(const std::deque<SemiEspacio3d> &se)
  {
    std::deque<Vector3d> retval;
    const size_t sz= se.size();
    for(size_t i=0;i<sz;i++)
      retval.push_back(se[i].NormalExterior());
    return retval;
  }

//! @brief Devuelve el ángulo entre los semiespacios.
GEOM_FT angulo(const SemiEspacio3d &se1,const SemiEspacio3d &se2)
  { return se1.getAngulo(se2); }

//! @brief Devuelve el ángulo entre el semiespacio y el vector.
GEOM_FT angulo(const Vector3d &v,const SemiEspacio3d &se)
  { return se.getAngulo(v); }

//! @brief Devuelve el ángulo entre el semiespacio y el vector.
GEOM_FT angulo(const SemiEspacio3d &se,const Vector3d &v)
  { return se.getAngulo(v); }
