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
//EntBase.cc

#include "EntBase.h"

#include <boost/any.hpp>
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/nucleo/aux_any.h"
#include "VarTypes.h"
#include "boost/lexical_cast.hpp"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe existir la variable
//! estática correspondiente que se define aquí.
std::string EntBase::tmp_gp_str="";
int EntBase::tmp_gp_int= 0;
long int EntBase::tmp_gp_lint= 0;
size_t EntBase::tmp_gp_szt= 0;
bool EntBase::tmp_gp_bool= false;
double EntBase::tmp_gp_dbl= 0.0;
long double EntBase::tmp_gp_ldbl= 0.0;
Path EntBase::tmp_gp_path;
//Al parecer el problema con la inicialización
//de ExprAlgebra como miembro estático aquí
//se llama: «static initialization order fiasco»
const LexAlgebra &tmp= ProtoExpresion::CreaLexico();
ExprAlgebra EntBase::tmp_gp_expr(0.0);
Lista EntBase::tmp_gp_lista(NULL);
Mapa EntBase::tmp_gp_mapa(NULL);
std::vector<boost::any> EntBase::tmp_gp_vany;
matrizExpr EntBase::tmp_gp_mexpr;
m_double EntBase::tmp_gp_mdbl;
m_string EntBase::tmp_gp_mstr;
m_int EntBase::tmp_gp_mint;
MatrizAny EntBase::tmp_gp_many;
//Lista EntBase::tmp_gp_lista(NULL);
CmdFuncPorPuntos EntBase::tmp_gp_func_pts(NULL);
Record EntBase::tmp_gp_record(NULL);
RangoIndice EntBase::tmp_gp_rng;
Pos2d EntBase::tmp_gp_pos2d;
Vector2d EntBase::tmp_gp_vector2d;
Segmento2d EntBase::tmp_gp_segmento2d;
Circulo2d EntBase::tmp_gp_circulo2d;
Poligono2d EntBase::tmp_gp_pol2d;
PoligonoConAgujeros2d EntBase::tmp_gp_poligonoConAgujeros2d;
ListaPos2d EntBase::tmp_gp_lpos2d;
Polilinea2d EntBase::tmp_gp_polilinea2d;
ListaPos3d EntBase::tmp_gp_lpos3d;
Pos3d EntBase::tmp_gp_pos3d;
Segmento3d EntBase::tmp_gp_segmento3d;
Vector3d EntBase::tmp_gp_vector3d;
VDesliz2d EntBase::tmp_gp_vdesliz2d;
VDesliz3d EntBase::tmp_gp_vdesliz3d;
VFijo2d EntBase::tmp_gp_vfijo2d;
VFijo3d EntBase::tmp_gp_vfijo3d;
SVD3d EntBase::tmp_gp_svd3d;
Recta2d EntBase::tmp_gp_recta2d;
Recta3d EntBase::tmp_gp_recta3d;
Plano3d EntBase::tmp_gp_plano3d;
SemiEspacio3d EntBase::tmp_gp_se3d;
Tetraedro3d EntBase::tmp_gp_tetra3d;
Poliedro3d EntBase::tmp_gp_poliedro3d;
BlockPyramid EntBase::tmp_gp_blockPyramid;
SisCooRect2d3d EntBase::tmp_gp_sisCooRect2d3d; //!< Variable temporal para devolución de propiedades (GetProp).
Ref2d3d EntBase::tmp_gp_ref2d3d; //!< Variable temporal para devolución de propiedades (GetProp).


//! @brief Constructor por defecto.
EntBase::EntBase(void)
  {}

//! @brief Devuelve la cadena de caracteres que resulta de interpretar la que se pasa como parámetro.
const boost::any &EntBase::interpretaAny(const std::string &str) const
  {
    static boost::any tmp_gp_any;
    if(str.empty())
      tmp_gp_any= boost::any();
    else
      {
        if(interpretaUno(str))
          tmp_gp_any= InterpreteRPN::Pila().Pop();
        else
          {
	    std::cerr << "EntBase::interpretaAny, no se pudo interpretar la expresión: '"
                      << str << "'" << std::endl;
            tmp_gp_any= boost::any();
          }
      }
    return tmp_gp_any;
  }

//! @brief Devuelve la cadena de caracteres que resulta de interpretar la que se pasa como parámetro.
const std::string &EntBase::interpretaString(const std::string &str) const
  {
    tmp_gp_str= "";
    if(interpretaUno(str))
      tmp_gp_str= convert_to_string(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaString, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_str.clear();
      }
    return tmp_gp_str;
  }

//! @brief Devuelve la ruta que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Path &EntBase::interpretaPath(const std::string &str) const
  {
    tmp_gp_str= "";
    if(interpretaUno(str))
      tmp_gp_path= Path(convert_to_string(InterpreteRPN::Pila().Pop()));
    else
      {
	std::cerr << "EntBase::interpretaPath, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_path.clear();
      }
    return tmp_gp_path;
  }

//! @brief Devuelve la expresión que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const ExprAlgebra &EntBase::interpretaExpr(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_expr= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaExpr, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_expr= ExprAlgebra();
      }
    return tmp_gp_expr;
  }

//! @brief Devuelve la matriz de expresiones que resulta de interpretar la cadena de
//! caracteres que se pasa como parámetro.
const matrizExpr &EntBase::interpretaMatrizExpr(const std::string &str) const
  {
    if(!str.empty())
      {
        const MatrizAny tmp= interpretaMatrizAny(str);
        const size_t fls= tmp.getNumFilas();
        const size_t cls= tmp.getNumCols();
        tmp_gp_mexpr= matrizExpr(fls,cls);
        for(size_t i=1;i<=fls;i++)
          for(size_t j=1;j<=cls;j++)
            tmp_gp_mexpr(i,j)= convert_to_ExprAlgebra(tmp(i,j));
      }
    else
      {
	std::cerr << "EntBase::interpretaMatrizExpr, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_mexpr.clear();
      }
    return tmp_gp_mexpr;
  }


//! @brief Devuelve el double que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const double &EntBase::interpretaDouble(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_dbl= convert_to_double(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaDouble, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_dbl= 0.0;
      }
    return tmp_gp_dbl;
  }

//! @brief Devuelve el bool que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const bool &EntBase::interpretaBool(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_bool= convert_to_bool(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaBool, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_bool= false;
      }
    return tmp_gp_bool;
  }

//! @brief Devuelve el entero que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const int &EntBase::interpretaInt(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_int= convert_to_int(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaInt, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_int= 0;
      }
    return tmp_gp_int;
  }

//! @brief Devuelve el size_t que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const size_t &EntBase::interpretaSize_t(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_szt= convert_to_size_t(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaSize_t, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_szt= 0;
      }
    return tmp_gp_szt;
  }

//! @brief Devuelve la lista que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Lista &EntBase::interpretaLista(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_lista= convert_to_lista(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaLista, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_lista.clear();
      }
    return tmp_gp_lista;
  }

//! @brief Devuelve el registro que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Record &EntBase::interpretaRecord(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_record= convert_to_record(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaRecord, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        //tmp_gp_record.clear();
      }
    return tmp_gp_record;
  }

//! @brief Devuelve el mapa que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Mapa &EntBase::interpretaMapa(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_mapa= convert_to_mapa(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaMapa, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_mapa.clear();
      }
    return tmp_gp_mapa;
  }

//! @brief Devuelve la función por puntos que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const CmdFuncPorPuntos &EntBase::interpretaFuncPorPuntos(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_func_pts= convert_to_CmdFuncPorPuntos(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaFuncPorPuntos, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_func_pts.clear();
      }
    return tmp_gp_func_pts;
  }

//! @brief Devuelve el vector que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const std::vector<boost::any> &EntBase::interpretaVectorAny(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_vany= convert_to_vector_any(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaVectorAny, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_vany.clear();
      }
    return tmp_gp_vany;
  }

//! @brief Devuelve la matriz de "doubles" que resulta de interpretar la cadena de
//! caracteres que se pasa como parámetro.
const m_double &EntBase::interpretaMDouble(const std::string &str) const
  {
    if(!str.empty())
      {
        const MatrizAny tmp= interpretaMatrizAny(str);
        tmp_gp_mdbl= convert_to_m_double(tmp);
      }
    else
      {
	std::cerr << "EntBase::interpretaMDouble, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_mdbl.clear();
      }
    return tmp_gp_mdbl;
  }

//! @brief Devuelve la matriz de entreros que resulta de interpretar la cadena de
//! caracteres que se pasa como parámetro.
const m_int &EntBase::interpretaMInt(const std::string &str) const
  {
    if(!str.empty())
      {
        const MatrizAny tmp= interpretaMatrizAny(str);
        tmp_gp_mint= convert_to_m_int(tmp);
      }
    else
      {
	std::cerr << "EntBase::interpretaMInt, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_mint.clear();
      }
    return tmp_gp_mint;
  }

//! @brief Devuelve la matriz de "strings" que resulta de interpretar la cadena de
//! caracteres que se pasa como parámetro.
const m_string &EntBase::interpretaMString(const std::string &str) const
  {
    if(!str.empty())
      {
        const MatrizAny tmp= interpretaMatrizAny(str);
        tmp_gp_mstr= convert_to_m_string(tmp);
      }
    else
      {
	std::cerr << "EntBase::interpretaMString, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_mstr.clear();
      }
    return tmp_gp_mstr;
  }

//! @brief Devuelve la matriz que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const MatrizAny &EntBase::interpretaMatrizAny(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_many= convert_to_matriz_any(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaMatrizAny, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_many.clear();
      }
    return tmp_gp_many;
  }

//! @brief Devuelve un rango de variación de un índice.
const RangoIndice &EntBase::interpretaRango(const std::string &str) const
  {
    if(!str.empty())
      {
        if(str.find(":",0) == std::string::npos) //Tiene un sólo argumento
          {
            const size_t tmp= interpretaInt(str);
            tmp_gp_rng.SetInfSup(tmp,tmp); 
          }
        else
          {
            const std::string sep= boost::lexical_cast<std::string>(RangoIndice::Separador());
            std::deque<std::string> tmp= separa_cadena(str,sep,2);
            const size_t ne= tmp.size(); //No. de elementos leídos.
            size_t tmp1= 1;
            size_t tmp2= 1;
            if(ne>0) tmp1= interpretaInt(tmp[0]);
            if(ne>1) tmp2= interpretaInt(tmp[1]);
            tmp_gp_rng.SetInfSup(tmp1,tmp2);
          }
      }
    else
      {
	std::cerr << "EntBase::interpretaRango, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_rng= RangoIndice();
      }
    return tmp_gp_rng;
  }



//! @brief Devuelve el punto 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Pos2d &EntBase::interpretaPos2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_pos2d= convert_to_pos2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaPos2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_pos2d= Pos2d();
      }
    return tmp_gp_pos2d;
  }

//! @brief Devuelve el polígono 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Poligono2d &EntBase::interpretaPoligono2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_pol2d= convert_to_poligono2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaPoligono2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_pol2d= Poligono2d();
      }
    return tmp_gp_pol2d;
  }

//! @brief Devuelve el polígono 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const PoligonoConAgujeros2d &EntBase::interpretaPoligonoConAgujeros2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_poligonoConAgujeros2d= convert_to_poligono_con_agujeros2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaPoligonoConAgujeros2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_poligonoConAgujeros2d= PoligonoConAgujeros2d();
      }
    return tmp_gp_poligonoConAgujeros2d;
  }

//! @brief Devuelve el conjunto de puntos que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const ListaPos2d &EntBase::interpretaListaPos2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_lpos2d= convert_to_lista_pos2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaListaPos2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_lpos2d= ListaPos2d();
      }
    return tmp_gp_lpos2d;
  }

//! @brief Devuelve la polilinea 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Polilinea2d &EntBase::interpretaPolilinea2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_polilinea2d= convert_to_polilinea2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaPolilinea2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_polilinea2d= Polilinea2d();
      }
    return tmp_gp_polilinea2d;
  }

//! @brief Devuelve el conjunto de puntos que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const ListaPos3d &EntBase::interpretaListaPos3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_lpos3d= convert_to_lista_pos3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaListaPos3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_lpos3d= ListaPos3d();
      }
    return tmp_gp_lpos3d;
  }

//! @brief Devuelve el vector 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Vector2d &EntBase::interpretaVector2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_vector2d= convert_to_vector2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaVector2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_vector2d= Vector2d();
      }
    return tmp_gp_vector2d;
  }

//! @brief Devuelve el segmento 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Segmento2d &EntBase::interpretaSegmento2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_segmento2d= convert_to_segmento2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaSegmento2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_segmento2d= Segmento2d();
      }
    return tmp_gp_segmento2d;
  }

//! @brief Devuelve el punto 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Pos3d &EntBase::interpretaPos3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_pos3d= convert_to_pos3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaPos3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_pos3d= Pos3d();
      }
    return tmp_gp_pos3d;
  }

//! @brief Devuelve el vector 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Vector3d &EntBase::interpretaVector3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_vector3d= convert_to_vector3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaVector3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_vector3d= Vector3d();
      }
    return tmp_gp_vector3d;
  }

//! @brief Devuelve el segmento 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Segmento3d &EntBase::interpretaSegmento3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_segmento3d= convert_to_segmento3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaSegmento3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_segmento3d= Segmento3d();
      }
    return tmp_gp_segmento3d;
  }

//! @brief Devuelve el vector 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const VDesliz2d &EntBase::interpretaVDesliz2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_vdesliz2d= convert_to_vdesliz2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaVDesliz2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_vdesliz2d= VDesliz2d();
      }
    return tmp_gp_vdesliz2d;
  }

//! @brief Devuelve el vector 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const VDesliz3d &EntBase::interpretaVDesliz3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_vdesliz3d= convert_to_vdesliz3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaVDesliz3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_vdesliz3d= VDesliz3d();
      }
    return tmp_gp_vdesliz3d;
  }

//! @brief Devuelve el vector 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const VFijo2d &EntBase::interpretaVFijo2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_vfijo2d= convert_to_vfijo2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaVFijo2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_vfijo2d= VFijo2d();
      }
    return tmp_gp_vfijo2d;
  }

//! @brief Devuelve el vector 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const VFijo3d &EntBase::interpretaVFijo3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_vfijo3d= convert_to_vfijo3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaVFijo3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_vfijo3d= VFijo3d();
      }
    return tmp_gp_vfijo3d;
  }

//! @brief Devuelve el SVD 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const SVD3d &EntBase::interpretaSVD3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_svd3d= convert_to_svd3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaSVD3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_svd3d= SVD3d();
      }
    return tmp_gp_svd3d;
  }

//! @brief Devuelve el circulo que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Circulo2d &EntBase::interpretaCirculo2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_circulo2d= convert_to_circulo2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaCirculo2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_circulo2d= Circulo2d();
      }
    return tmp_gp_circulo2d;
  }

//! @brief Devuelve el recta 2d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Recta2d &EntBase::interpretaRecta2d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_recta2d= convert_to_recta2d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaRecta2d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_recta2d= Recta2d();
      }
    return tmp_gp_recta2d;
  }

//! @brief Devuelve el recta 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Recta3d &EntBase::interpretaRecta3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_recta3d= convert_to_recta3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaRecta3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_recta3d= Recta3d();
      }
    return tmp_gp_recta3d;
  }

//! @brief Devuelve el plano 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Plano3d &EntBase::interpretaPlano3d(const std::string &str) const
  { 
    if(interpretaUno(str))
      tmp_gp_plano3d= convert_to_plano3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaPlano3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_plano3d= Plano3d();
      }
    return tmp_gp_plano3d;
  }

//! @brief Devuelve el SemiEspacio 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const SemiEspacio3d &EntBase::interpretaSemiEspacio3d(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_se3d= convert_to_se3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaSemiEspacio3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_se3d= SemiEspacio3d();
      }
    return tmp_gp_se3d;
  }

//! @brief Devuelve el Tetraedro 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Tetraedro3d &EntBase::interpretaTetraedro3d(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_tetra3d= convert_to_tetra3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaTetraedro3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_tetra3d= Tetraedro3d();
      }
    return tmp_gp_tetra3d;
  }

//! @brief Devuelve el «block pyramid» que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const BlockPyramid &EntBase::interpretaBlockPyramid(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_blockPyramid= convert_to_blockPyramid(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaBlockPyramid, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_blockPyramid= BlockPyramid();
      }
    return tmp_gp_blockPyramid;
  }

//! @brief Devuelve el «block pyramid» que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const SisCooRect2d3d &EntBase::interpretaSisCooRect2d3d(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_sisCooRect2d3d= convert_to_sisCooRect2d3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaSisCooRect2d3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_sisCooRect2d3d= SisCooRect2d3d();
      }
    return tmp_gp_sisCooRect2d3d;
  }

//! @brief Devuelve el «block pyramid» que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Ref2d3d &EntBase::interpretaRef2d3d(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_ref2d3d= convert_to_ref2d3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaRef2d3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_ref2d3d= Ref2d3d();
      }
    return tmp_gp_ref2d3d;
  }

//! @brief Devuelve el Poliedro 3d que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
const Poliedro3d &EntBase::interpretaPoliedro3d(const std::string &str) const
  {
    if(interpretaUno(str))
      tmp_gp_poliedro3d= convert_to_poliedro3d(InterpreteRPN::Pila().Pop());
    else
      {
	std::cerr << "EntBase::interpretaPoliedro3d, no se pudo interpretar la expresión: '"
                  << str << "'" << std::endl;
        tmp_gp_poliedro3d= Poliedro3d();
      }
    return tmp_gp_poliedro3d;
  }

