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
//utils_any.h
//Utilidades para la clase any de la biblioteca boost.

#ifndef UTILS_ANY_H
#define UTILS_ANY_H

#include <string>
#include <vector>
#include <deque>
#include "xc_basic/src/matrices/m_int.h"
#include "xc_basic/src/matrices/m_sizet.h"
#include "xc_basic/src/matrices/m_double.h"
#include "xc_basic/src/matrices/m_int.h"
#include "xc_basic/src/matrices/m_string.h"
#include "xc_utils/src/geom/tipos_cgal.h"

namespace boost
  {
    class any;
  }

class Path;
class ExprAlgebra;
class EntProp;
class EntCmd;
class EntCmdPtr;
class Lista;
class Mapa;
class Record;
class CmdFuncPorPuntos;
class MatrizAny;
class matrizExpr;
class matrizM;
class matrizMExpr;
class matriz_FT;
class Poligono2d;
class PoligonoConAgujeros2d;
class ListaPos2d;
class Polilinea2d;
class ListaPos3d;
class Pos2d;
class Recta2d;
class Pos3d;
class Vector2d;
class Segmento2d;
class Circulo2d;
class Vector3d;
class Segmento3d;
class VDesliz2d;
class VDesliz3d;
class VFijo2d;
class VFijo3d;
class Recta3d;
class Plano3d;
class SemiEspacio3d;
class Tetraedro3d;
class Poliedro3d;
class BlockPyramid;
class SisCooRect2d3d;
class Ref2d3d;
class SVD3d;

bool boost_any_is_empty(const boost::any &);

bool boost_any_is_bool(const boost::any &);
const bool &boost_any_to_bool(const boost::any &);
bool convert_to_bool(const boost::any &);

bool boost_any_is_vector_char(const boost::any &);
const std::vector<char> &boost_any_to_vector_char(const boost::any &);
std::vector<char> convert_to_vector_char(const boost::any &);

bool boost_any_is_vector_string(const boost::any &operand);
const std::vector<std::string> &boost_any_to_vector_string(const boost::any &operand);
std::vector<std::string> convert_to_vector_string(const boost::any &operand);

bool boost_any_is_int(const boost::any &);
const int &boost_any_to_int(const boost::any &);
int convert_to_int(const boost::any &);

bool boost_any_is_long_int(const boost::any &);
const long int &boost_any_to_long_int(const boost::any &);
long int convert_to_long_int(const boost::any &);

bool boost_any_is_vector_int(const boost::any &);
const std::vector<int> &boost_any_to_vector_int(const boost::any &);
std::vector<int> convert_to_vector_int(const boost::any &);

bool boost_any_is_dq_int(const boost::any &);
const std::deque<int> &boost_any_to_dq_int(const boost::any &);
std::deque<int> convert_to_dq_int(const boost::any &operand);

bool boost_any_is_vector_long_int(const boost::any &);
const std::vector<long int> &boost_any_to_vector_long_int(const boost::any &);


bool boost_any_is_size_t(const boost::any &);
const size_t &boost_any_to_size_t(const boost::any &);
size_t convert_to_size_t(const boost::any &);

bool boost_any_is_vector_size_t(const boost::any &);
const std::vector<size_t> &boost_any_to_vector_size_t(const boost::any &);
std::vector<size_t> convert_to_vector_size_t(const boost::any &);

bool boost_any_is_char_ptr(const boost::any &);
const std::string char_ptr_to_string(const boost::any &);

bool boost_any_is_char(const boost::any &);
const char &boost_any_to_char(const boost::any &);
char convert_to_char(const boost::any &);

bool boost_any_is_string(const boost::any &);
const std::string &boost_any_to_string(const boost::any &);
std::string convert_to_string(const boost::any &);
std::deque<std::string> convert_to_dq_string(const std::deque<boost::any> &);

bool boost_any_is_path(const boost::any &);
const Path &boost_any_to_path(const boost::any &);
Path convert_to_path(const boost::any &);

bool boost_any_is_float(const boost::any &);
const float &boost_any_to_float(const boost::any &);

bool boost_any_is_double(const boost::any &);
const double &boost_any_to_double(const boost::any &);
double convert_to_double(const boost::any &);

bool boost_any_is_vector_double(const boost::any &);
const std::vector<double> &boost_any_to_vector_double(const boost::any &);
std::vector<double> convert_to_vector_double(const boost::any &);

bool boost_any_is_m_int(const boost::any &operand);
const m_int &boost_any_to_m_int(const boost::any & operand);

bool boost_any_is_m_double(const boost::any &operand);
const m_double &boost_any_to_m_double(const boost::any &operand);
m_double convert_to_m_double(const boost::any &operand);

bool boost_any_is_m_sizet(const boost::any &operand);
const m_sizet &boost_any_to_m_sizet(const boost::any & operand);

bool boost_any_is_m_string(const boost::any &operand);
const m_string &boost_any_to_m_string(const boost::any &operand);
m_string convert_to_m_string(const boost::any &operand);

bool boost_any_is_m_int(const boost::any &operand);
const m_int &boost_any_to_m_int(const boost::any &operand);
m_int convert_to_m_int(const boost::any &operand);

bool boost_any_is_matrizM(const boost::any & operand);
const matrizM &boost_any_to_matrizM(const boost::any & operand);

bool boost_any_is_matrizMExpr(const boost::any & operand);
const matrizMExpr &boost_any_to_matrizMExpr(const boost::any & operand);

bool boost_any_is_long_double(const boost::any &);
const long double &boost_any_to_long_double(const boost::any &);
long double convert_to_long_double(const boost::any &);

bool boost_any_is_expr_algebra(const boost::any &);
const ExprAlgebra &boost_any_to_ExprAlgebra(const boost::any &);
ExprAlgebra convert_to_ExprAlgebra(const boost::any &);

bool boost_any_is_vector_expr(const boost::any &);
const std::vector<ExprAlgebra> &boost_any_to_vector_expr(const boost::any &);
std::vector<ExprAlgebra> convert_to_vector_expr(const boost::any &);

bool boost_any_is_matriz_expr(const boost::any &operand);
const matrizExpr &boost_any_to_matrizExpr(const boost::any & operand);

bool boost_any_is_number(const boost::any &);
double boost_any_number_to_double(const boost::any &);
long double boost_any_number_to_long_double(const boost::any &);

bool boost_any_is_lista(const boost::any &);
const Lista &boost_any_to_lista(const boost::any &);
Lista convert_to_lista(const boost::any &);

bool boost_any_is_mapa(const boost::any &);
const Mapa &boost_any_to_mapa(const boost::any &);
Mapa convert_to_mapa(const boost::any &);

bool boost_any_is_record(const boost::any &);
const Record &boost_any_to_record(const boost::any &);
Record convert_to_record(const boost::any &);

bool boost_any_is_CmdFuncPorPuntos(const boost::any &);
const CmdFuncPorPuntos &boost_any_to_CmdFuncPorPuntos(const boost::any &);
CmdFuncPorPuntos convert_to_CmdFuncPorPuntos(const boost::any &);

bool boost_any_is_ent_cmd(const boost::any &);
const EntCmd &boost_any_to_ent_cmd(const boost::any &);
bool boost_any_is_ent_cmd_ptr(const boost::any &);
const EntCmdPtr &boost_any_to_ent_cmd_ptr(const boost::any &);

bool boost_any_is_vector_any(const boost::any &);
const std::vector<boost::any> &boost_any_to_vector_any(const boost::any &);
std::vector<boost::any> convert_to_vector_any(const boost::any &);

bool boost_any_is_dq_any(const boost::any &);
const std::deque<boost::any> &boost_any_to_dq_any(const boost::any &);
std::deque<boost::any> convert_to_dq_any(const boost::any &);

bool boost_any_is_matriz_any(const boost::any &);
const MatrizAny &boost_any_to_matriz_any(const boost::any &);
MatrizAny convert_to_matriz_any(const boost::any &);

bool boost_any_is_geom_FT(const boost::any &);
const GEOM_FT &boost_any_to_geom_FT(const boost::any &);
GEOM_FT convert_to_geom_FT(const boost::any &);

bool boost_any_is_matriz_FT(const boost::any &);
const matriz_FT &boost_any_to_matriz_FT(const boost::any &);
matriz_FT convert_to_matriz_FT(const boost::any &);

bool boost_any_is_poligono2d(const boost::any &);
const Poligono2d &boost_any_to_poligono2d(const boost::any &);
Poligono2d convert_to_poligono2d(const boost::any &);

bool boost_any_is_poligono_con_agujeros2d(const boost::any &);
const PoligonoConAgujeros2d &boost_any_to_poligono_con_agujeros2d(const boost::any &);
PoligonoConAgujeros2d convert_to_poligono_con_agujeros2d(const boost::any &);

bool boost_any_is_lista_pos2d(const boost::any &);
const ListaPos2d &boost_any_to_lista_pos2d(const boost::any &);
ListaPos2d convert_to_lista_pos2d(const boost::any &);

bool boost_any_is_polilinea2d(const boost::any &);
const Polilinea2d &boost_any_to_polilinea2d(const boost::any &);
Polilinea2d convert_to_polilinea2d(const boost::any &);

bool boost_any_is_lista_pos3d(const boost::any &);
const ListaPos3d &boost_any_to_lista_pos3d(const boost::any &);
ListaPos3d convert_to_lista_pos3d(const boost::any &);

bool boost_any_is_vector2d(const boost::any &);
const Vector2d &boost_any_to_vector2d(const boost::any &);
Vector2d convert_to_vector2d(const boost::any &);

bool boost_any_is_segmento2d(const boost::any &);
const Segmento2d &boost_any_to_segmento2d(const boost::any &);
Segmento2d convert_to_segmento2d(const boost::any &);

bool boost_any_is_circulo2d(const boost::any &);
const Circulo2d &boost_any_to_circulo2d(const boost::any &);
Circulo2d convert_to_circulo2d(const boost::any &);

bool boost_any_is_pos2d(const boost::any &);
const Pos2d &boost_any_to_pos2d(const boost::any &);
Pos2d convert_to_pos2d(const boost::any &);

bool boost_any_is_recta2d(const boost::any &);
const Recta2d &boost_any_to_recta2d(const boost::any &);
Recta2d convert_to_recta2d(const boost::any &);

bool boost_any_is_pos3d(const boost::any &);
const Pos3d &boost_any_to_pos3d(const boost::any &);
Pos3d convert_to_pos3d(const boost::any &);

bool boost_any_is_vector3d(const boost::any &);
const Vector3d &boost_any_to_vector3d(const boost::any &);
Vector3d convert_to_vector3d(const boost::any &);

bool boost_any_is_segmento3d(const boost::any &);
const Segmento3d &boost_any_to_segmento3d(const boost::any &);
Segmento3d convert_to_segmento3d(const boost::any &);

bool boost_any_is_vdesliz2d(const boost::any &);
const VDesliz2d &boost_any_to_vdesliz2d(const boost::any &);
VDesliz2d convert_to_vdesliz2d(const boost::any &);

bool boost_any_is_vdesliz3d(const boost::any &);
const VDesliz3d &boost_any_to_vdesliz3d(const boost::any &);
VDesliz3d convert_to_vdesliz3d(const boost::any &);

bool boost_any_is_vfijo2d(const boost::any &);
const VFijo2d &boost_any_to_vfijo2d(const boost::any &);
VFijo2d convert_to_vfijo2d(const boost::any &);

bool boost_any_is_vfijo3d(const boost::any &);
const VFijo3d &boost_any_to_vfijo3d(const boost::any &);
VFijo3d convert_to_vfijo3d(const boost::any &);

bool boost_any_is_recta3d(const boost::any &);
const Recta3d &boost_any_to_recta3d(const boost::any &);
Recta3d convert_to_recta3d(const boost::any &);

bool boost_any_is_plano3d(const boost::any &);
const Plano3d &boost_any_to_plano3d(const boost::any &);
Plano3d convert_to_plano3d(const boost::any &);

bool boost_any_is_se3d(const boost::any &);
const SemiEspacio3d &boost_any_to_se3d(const boost::any &);
SemiEspacio3d convert_to_se3d(const boost::any &);

bool boost_any_is_tetra3d(const boost::any &);
const Tetraedro3d &boost_any_to_tetra3d(const boost::any &);
Tetraedro3d convert_to_tetra3d(const boost::any &);

bool boost_any_is_blockPyramid(const boost::any &);
const BlockPyramid &boost_any_to_blockPyramid(const boost::any &);
BlockPyramid convert_to_blockPyramid(const boost::any &);

bool boost_any_is_sisCooRect2d3d(const boost::any &);
const SisCooRect2d3d &boost_any_to_sisCooRect2d3d(const boost::any &);
SisCooRect2d3d convert_to_sisCooRect2d3d(const boost::any &);

bool boost_any_is_ref2d3d(const boost::any &);
const Ref2d3d &boost_any_to_ref2d3d(const boost::any &);
Ref2d3d convert_to_ref2d3d(const boost::any &);

bool boost_any_is_poliedro3d(const boost::any &);
const Poliedro3d &boost_any_to_poliedro3d(const boost::any &);
Poliedro3d convert_to_poliedro3d(const boost::any &);

bool boost_any_is_svd3d(const boost::any &);
const SVD3d &boost_any_to_svd3d(const boost::any &);
SVD3d convert_to_svd3d(const boost::any &);

//! @brief Devuelve verdadero si los objetos son del mismo tipo.
bool boost_any_same_type(const boost::any &a,const boost::any &b);



std::string boost_any_format(const boost::any &operand,const std::string &format);
std::string boost_any_to_sql_value(const boost::any &operand);
std::ostream &operator<<(std::ostream &os,const boost::any &);

std::vector<boost::any> def_vector_any(const size_t &,const boost::any &);

boost::any suma_boost_any(const boost::any &,const boost::any &);
boost::any resta_boost_any(const boost::any &,const boost::any &);
boost::any mult_boost_any(const boost::any &,const boost::any &);
boost::any dot_boost_any(const boost::any &,const boost::any &);
boost::any cross_boost_any(const boost::any &,const boost::any &);
boost::any proj_boost_any(const boost::any &,const boost::any &);
boost::any normaliza_boost_any(const boost::any &);
boost::any div_boost_any(const boost::any &,const boost::any &);
boost::any pow_boost_any(const boost::any &,const boost::any &);
boost::any neg_boost_any(const boost::any &);
int sign_boost_any(const boost::any &);
boost::any abs_boost_any(const boost::any &);
boost::any traza_boost_any(const boost::any &);
boost::any traspuesta_boost_any(const boost::any &);
boost::any inv_boost_any(const boost::any &);
boost::any sqrt_boost_any(const boost::any &);
boost::any max_boost_any(const boost::any &,const boost::any &);
boost::any min_boost_any(const boost::any &,const boost::any &);
boost::any menor_boost_any(const boost::any &,const boost::any &);
boost::any mayor_boost_any(const boost::any &,const boost::any &);
boost::any igual_boost_any(const boost::any &,const boost::any &);
boost::any menor_o_igual_boost_any(const boost::any &,const boost::any &);
boost::any mayor_o_igual_boost_any(const boost::any &,const boost::any &);
boost::any distinto_boost_any(const boost::any &,const boost::any &);
boost::any and_boost_any(const boost::any &,const boost::any &);
boost::any or_boost_any(const boost::any &,const boost::any &);
boost::any not_boost_any(const boost::any &);
const boost::any &ifte_boost_any(const boost::any &,const boost::any &,const boost::any &c);
boost::any at_boost_any(const boost::any &,const boost::any &);
size_t size_boost_any(const boost::any &);
size_t nfilas_boost_any(const boost::any &);
size_t ncols_boost_any(const boost::any &);

//Geometria.
boost::any distancia_boost_any(const boost::any &,const boost::any &);
boost::any angulo_boost_any(const boost::any &,const boost::any &);
boost::any interseccion_boost_any(const boost::any &,const boost::any &);
boost::any punto_interseccion_boost_any(const boost::any &,const boost::any &);

#endif
