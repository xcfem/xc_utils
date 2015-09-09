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
//Rejilla2d.cpp

#include "Rejilla2d.h" 
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/geom/d2/poligonos2d/Cuadrilatero2d.h"
#include "xc_utils/src/geom/matriz_FT.h"
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

//! @brief Constructor.
Rejilla2d::Rejilla2d(void)
  : Superficie2d(), puntos(1,1) {}

Rejilla2d::Rejilla2d(int numSubdivIJ, int numSubdivJK)
  : Superficie2d(), puntos(numSubdivIJ,numSubdivJK) {}

//! @brief Lee un objeto RgSccCuadrilatero desde archivo
bool Rejilla2d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Rejilla2d) Procesando comando: " << cmd << std::endl;

    if(cmd == "for_each_quad")
      {
        EjecutaBloqueForEachQuad(status,status.GetBloque());
        return true;
      }
    else if(cmd == "for_each_point")
      {
        EjecutaBloqueForEachPoint(status,status.GetBloque());
        return true;
      }
    else
      return Superficie2d::procesa_comando(status);
  }

Rejilla2d::~Rejilla2d(void)
  {}

//! @brief Devuelve el área de la rejilla.
GEOM_FT Rejilla2d::Area(void) const
  { return puntos.GetArea();  }

//! @briefMomento de inercia respecto al CDG en ejes locales.
GEOM_FT Rejilla2d::Ix(void) const
  { return puntos.Ix(); }

//! @brief Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Rejilla2d::Iy(void) const
  { return puntos.Iy(); }

//! @brief Producto de inercia respecto al CDG en ejes locales.
GEOM_FT Rejilla2d::Pxy(void) const
  { return puntos.Pxy(); }

//! @brief Devuelve el centro de gravedad de la rejilla.
Pos2d Rejilla2d::Cdg(void) const
  { return puntos.GetCdg(); }

//! @brief Devuelve las coordenadas del punto i,j.
const matriz_FT &Rejilla2d::GetVertCoords(const size_t &i,const size_t &j) const
  { return puntos.GetVertCoords(i,j); }

//! @brief Devuelve el punto i,j.
Pos2d Rejilla2d::GetPunto(const size_t &i,const size_t &j) const
  { return puntos.GetPunto(i,j); }

//! @brief Devuelve el cuadrilátero correspondiente a la celda i,j:
Cuadrilatero2d Rejilla2d::GetQuad(const size_t &i,const size_t &j) const
  { return puntos.GetQuad(i,j); }

//! @brief Devuelve verdadero si el punto está dentro de la rejilla.
bool Rejilla2d::In(const Pos2d &p, const double &tol) const
  { return puntos.In(p,tol); }

//! @brief Devuelve el valor maximo de la coordenada i.
GEOM_FT Rejilla2d::GetMax(unsigned short int i) const
  { return puntos.GetMax(i); }

//! @brief Devuelve el valor minimo de la coordenada i.
GEOM_FT Rejilla2d::GetMin(unsigned short int i) const
  { return puntos.GetMin(i); }


void Rejilla2d::EjecutaBloqueForEachPoint(CmdStatus &status,const std::string &bloque)
  {
    for(MatrizPos2d::iterator i= puntos.begin();i!=puntos.end();i++)
      (*i).EjecutaBloque(status,bloque,"Rejilla2d:ForEachPoint");
  }

void Rejilla2d::EjecutaBloqueForEachQuad(CmdStatus &status,const std::string &bloque)
  {
    const size_t fls= puntos.getNumFilas();
    const size_t cls= puntos.getNumCols();
    for(size_t i=1;i<fls;i++)
      for(size_t j=1;j<cls;j++)
        puntos.GetQuad(i,j).EjecutaBloque(status,bloque,"Rejilla2d:ForEachQuad");
  }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Rejilla2d::Transforma(const Trf2d &trf2d)
  { puntos.Transforma(trf2d); }

//!  @brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
any_const_ptr Rejilla2d::GetProp(const std::string &cod) const
  {
    if(cod=="getNumPuntos")
      {
        tmp_gp_szt= puntos.size();
        return any_const_ptr(tmp_gp_szt);
      }
    if(cod=="getNumQuads")
      {
        tmp_gp_szt= puntos.GetNumQuads();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="getNumFilas")
      {
        tmp_gp_szt= puntos.getNumFilas();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="getNumCols")
      {
        tmp_gp_szt= puntos.getNumCols();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="getArea")
      {
        tmp_gp_dbl= puntos.GetArea();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="getCdg")
      {
        static m_double tmp_m_double(1,2);
        const Pos2d tmp= Cdg();
        tmp_m_double(1,1)= tmp.x();
        tmp_m_double(1,2)= tmp.y();
        return any_const_ptr(tmp_m_double);
      }
    else if(cod=="getIx")
      {
        tmp_gp_dbl= Ix();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="getIy")
      {
        tmp_gp_dbl= Iy();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="getPxy")
      {
        tmp_gp_dbl= Pxy();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="xMin")
      {
        tmp_gp_dbl= puntos.GetMin(1);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="yMin")
      {
        tmp_gp_dbl= puntos.GetMin(2);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="xMax")
      {
        tmp_gp_dbl= puntos.GetMax(1);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="yMax")
      {
        tmp_gp_dbl= puntos.GetMax(2);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="x")
      {
        size_t i= 0, j= 0;
        if(InterpreteRPN::Pila().size()>1)
          {
            j= convert_to_size_t(InterpreteRPN::Pila().Pop());
            i= convert_to_size_t(InterpreteRPN::Pila().Pop());
          }
        else
          std::cerr << "Se esperaban dos argumentos." << std::endl;
        tmp_gp_dbl= puntos.GetX(i,j);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="y")
      {
        size_t i= 0, j= 0;
        if(InterpreteRPN::Pila().size()>1)
          {
            j= convert_to_size_t(InterpreteRPN::Pila().Pop());
            i= convert_to_size_t(InterpreteRPN::Pila().Pop());
          }
        else
          std::cerr << "Se esperaban dos argumentos." << std::endl;
        tmp_gp_dbl= puntos.GetY(i,j);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="getVertCoords")
      {
        size_t i= 0, j= 0;
        if(InterpreteRPN::Pila().size()>1)
          {
            j= convert_to_size_t(InterpreteRPN::Pila().Pop());
            i= convert_to_size_t(InterpreteRPN::Pila().Pop());
          }
        else
          std::cerr << "Se esperaban dos argumentos." << std::endl;
        static m_double tmp_m_double(1,2);
        tmp_m_double= GetVertCoords(i,j);
        return any_const_ptr(tmp_m_double);
      }
    else if(cod=="getPunto")
      {
        size_t i= 0, j= 0;
        if(InterpreteRPN::Pila().size()>1)
          {
            j= convert_to_size_t(InterpreteRPN::Pila().Pop());
            i= convert_to_size_t(InterpreteRPN::Pila().Pop());
          }
        else
          std::cerr << "Se esperaban dos argumentos." << std::endl;
        static Pos2d tmp= GetPunto(i,j);
        return any_const_ptr(&tmp);
      }
    else if(cod=="getQuad")
      {
        size_t i= 0, j= 0;
        if(InterpreteRPN::Pila().size()>1)
          {
            j= convert_to_size_t(InterpreteRPN::Pila().Pop());
            i= convert_to_size_t(InterpreteRPN::Pila().Pop());
          }
        else
          std::cerr << "Se esperaban dos argumentos." << std::endl;
        static m_double tmp_m_double(1,2);
        const Cuadrilatero2d tmp= puntos.GetQuad(i,j);
        return any_const_ptr(&tmp);
      }
    else
      return Superficie2d::GetProp(cod);
  }

void Rejilla2d::Print(std::ostream &os) const
  {
    std::cerr << "Rejilla2d::Print, no implementada." << std::endl;
  }
