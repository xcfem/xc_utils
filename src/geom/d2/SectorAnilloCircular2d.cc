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
//SectorAnilloCircular2d.cc

#include "SectorAnilloCircular2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"


bool SectorAnilloCircular2d::procesa_comando(CmdStatus &status)
  {
    const std::string &cmd= deref_cmd(status.Cmd());
    const std::string str_aviso= "(SectorAnilloCircular2d) Procesando comando: " + cmd;
    if(verborrea>2)
      std::clog << str_aviso << std::endl;
    static Pos2d c;
    if(cmd == "rInt")
      {
        rint= double_to_FT(interpretaDouble(status.GetString()));
        if(rint>=Radio())
	  std::clog << str_aviso << " el radio interior es mayor o igual que el exterior." << std::endl; 
        return true;
      }
    else
      return SectorCircular2d::procesa_comando(status);
  }

//! @brief Construye el círculo a partir del centro y el radio.
SectorAnilloCircular2d::SectorAnilloCircular2d(const SectorCircular2d &c,const double &r)
  : SectorCircular2d(c), rint(r) {}

//! @brief Devuelve la posición del centro de gravedad del sector circular.
Pos2d SectorAnilloCircular2d::Cdg(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Cdg() no implementada." << std::endl;
    return Centro();
  }

//! @brief Devuelve un sector circular con el mismo centro y ángulos y otro radio
SectorCircular2d SectorAnilloCircular2d::getSector(const double &R) const
  { return SectorCircular2d(Circulo2d(Centro(),R),Theta1(),Theta2()); }

//! @brief Devuelve el sector circular interior a éste.
SectorCircular2d SectorAnilloCircular2d::SectorInterior(void) const
  { return getSector(rint); }


//! @brief Devuelve el punto inicial del arco exterior.
Pos2d SectorAnilloCircular2d::PInicExt(void) const
  { return SectorCircular2d::PInic(); }

//! @brief Devuelve el punto final del arco exterior.
Pos2d SectorAnilloCircular2d::PFinExt(void) const
  { return SectorCircular2d::PFin(); }

//! @brief Devuelve el punto inicial del arco interior.
Pos2d SectorAnilloCircular2d::PInicInt(void) const
  { return SectorInterior().PInic(); }

//! @brief Devuelve el punto final del arco interior.
Pos2d SectorAnilloCircular2d::PFinInt(void) const
  { return SectorInterior().PFin(); }


//! @brief Devuelve el punto medio del arco exterior.
Pos2d SectorAnilloCircular2d::PMedExt(void) const
  { return SectorCircular2d::PMed(); }

//! @brief Devuelve el punto medio del arco interior.
Pos2d SectorAnilloCircular2d::PMedInt(void) const
  { return SectorInterior().PMed(); }

//! @brief Devuelve la longitud del arco exterior del sector de anillo circular.
GEOM_FT SectorAnilloCircular2d::LongitudArcoExt(void) const
  { return double_to_FT(AnguloComprendido())*RadioExt(); }

//! @brief Devuelve la longitud del arco interior del sector de anillo circular.
GEOM_FT SectorAnilloCircular2d::LongitudArcoInt(void) const
  { return double_to_FT(AnguloComprendido())*RadioInt(); }

//! @brief Devuelve la longitud del sector circular.
GEOM_FT SectorAnilloCircular2d::Longitud(void) const
  { return LongitudArcoExt()+LongitudArcoInt()+2*(RadioExt()-RadioInt()); }

//! @brief Devuelve el área del sector circular.
GEOM_FT SectorAnilloCircular2d::Area(void) const
  { return SectorCircular2d::Area()-SectorInterior().Area(); }

//! @brief Devuelve el valor máximo de la coordenada i de los puntos del sector circular.
GEOM_FT SectorAnilloCircular2d::GetMax(unsigned short int i) const
  {
    std::cerr << "SectorAnilloCircular2d::GetMax() no implementada." << std::endl;
    return 0;
  }
//! @brief Devuelve el valor mínimo de la coordenada i de los puntos del sector circular.
GEOM_FT SectorAnilloCircular2d::GetMin(unsigned short int i) const
  {
    std::cerr << "SectorAnilloCircular2d::GetMin() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el momento de inercia del sector circular respecto al 
//! eje paralelo al x que pasa por su centro.
GEOM_FT SectorAnilloCircular2d::Ix(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Ix() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el momento de inercia del sector circular respecto al 
//! eje paralelo al y que pasa por su centro.
GEOM_FT SectorAnilloCircular2d::Iy(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Iy() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el momento de inercia del sector circular respecto al 
//! eje paralelo al z que pasa por su centro.
GEOM_FT SectorAnilloCircular2d::Iz(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Iz() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el producto de inercia del sector circular respecto a
//! los ejes paralelos a x e y que pasan por su centro.
GEOM_FT SectorAnilloCircular2d::Pxy(void) const
  {
    std::cerr << "SectorAnilloCircular2d::Pxy() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve verdadero si el punto est'a sobre el sector circular.
bool SectorAnilloCircular2d::In(const Pos2d &p, const double &tol) const
  {
    if(SectorCircular2d::In(p,tol))
      {
        return !(SectorInterior().In(p,tol)); //XXX ¿tol?
      }
    else
      return false;
  }

MatrizPos2d SectorAnilloCircular2d::PuntosArcoExt(const size_t &n) const
  { return SectorCircular2d::PuntosArco(n); }

MatrizPos2d SectorAnilloCircular2d::PuntosArcoInt(const size_t &n) const
  { return SectorInterior().PuntosArco(n); }

//! @brief Devuelve n puntos equiespaciados sobre el arco del sector circular.
MatrizPos2d SectorAnilloCircular2d::PuntosPerimetro(const size_t &n) const
  {
    MatrizPos2d retval;
    if(n>3)
      {
        retval= MatrizPos2d(n,2);
        if(n==4)
          {
            retval(1,2)= PInicExt(); //Puntos inicial y final
            retval(n,2)= PFinExt();
            retval(1,1)= PInicInt(); //Puntos inicial y final
            retval(n,1)= PFinInt();
          }
        else
          {
            retval.PutCol(2,PuntosArcoExt(n));
            retval.PutCol(1,PuntosArcoInt(n));
          }
      }
    else
      std::cerr << "SectorAnilloCircular2d::Puntos; el número de puntos ha de ser mayor o igual a cuatro." << std::endl;
    return retval;
  }
//! @brief Devuelve una malla de puntos equiespaciados sobre el sector del anillo circular.
MatrizPos2d SectorAnilloCircular2d::Malla(const size_t &nDivRad,const size_t &nDivCirc) const
  {
    MatrizPos2d retval(nDivCirc+1,nDivRad+1);
    if(nDivRad>0  && nDivCirc>0)
      {
        const double deltaRad= (RadioExt() - RadioInt())/nDivRad;

        double rad_j= RadioInt();
        for(size_t j= 0;j<nDivRad+1;j++)
          {
            MatrizPos2d tmp= getSector(rad_j).PuntosArco(nDivCirc+1);
            retval.PutCol(j+1,tmp);
            rad_j+= deltaRad;
          }
      }
    return retval;
  }

Poligono2d SectorAnilloCircular2d::getPoligono2d(const size_t &n) const
  {
    Poligono2d retval;
    MatrizPos2d ptos= PuntosPerimetro(n);
    for(size_t i=1;i<=n;i++)
      retval.push_back(ptos(i,2));
    for(size_t i=n;i>0;i--)
      retval.push_back(ptos(i,1));
    return retval;
  }

void SectorAnilloCircular2d::Print(std::ostream &os) const
  {
    SectorCircular2d::Print(os);
    os << " rint= " << rint;
  }

bool operator==(const SectorAnilloCircular2d &a,const SectorAnilloCircular2d &b)
  {
    if((const SectorCircular2d &)(a) == (const SectorCircular2d &)(b))
      return ( (a.Theta1() == b.Theta1()) && (a.Theta2() == b.Theta2()));
   else
     return false;
  }
