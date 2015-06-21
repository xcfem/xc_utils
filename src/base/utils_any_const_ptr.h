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
//utils_any_const_ptr.h
//Utilidades para la clase any_const_ptr.

#ifndef UTILS_ANY_CONST_PTR_H
#define UTILS_ANY_CONST_PTR_H

#include <string>
#include <vector>
#include "xc_basic/src/matrices/m_int.h"
#include "xc_basic/src/matrices/m_sizet.h"
#include "xc_basic/src/matrices/m_double.h"
#include "xc_basic/src/matrices/m_string.h"
#include "xc_utils/src/geom/tipos_cgal.h"

class Path;
class ExprAlgebra;
class EntCmd;
class Lista;
class Mapa;
class CmdFuncPorPuntos;
class any_const_ptr;
class matrizExpr;
class matrizM;
class matrizMExpr;
class matriz_FT;
class MatrizAny;
class Pos2d;
class ListaPos2d;
class Polilinea2d;
class Pos3d;
class ListaPos3d;
class Vector2d;
class Segmento2d;
class Poligono2d;
class PoligonoConAgujeros2d;
class Circulo2d;
class Vector3d;
class Recta3d;
class Recta2d;
class Plano3d;
class Segmento3d;
class VDesliz2d;
class VDesliz3d;
class VFijo2d;
class VFijo3d;
class SemiEspacio3d;
class Poliedro3d;
class Tetraedro3d;
class BlockPyramid;
class SisCooRect2d3d;
class Ref2d3d;
class SVD3d;

namespace boost
  {
    class any;
  }

struct EntCmdPtr
  {
    const EntCmd *ent_cmd_ptr;
    EntCmdPtr(const EntCmd *p=NULL)
      : ent_cmd_ptr(p) {}
    const EntCmd *getPtr(void) const
      { return ent_cmd_ptr; }
  };

bool const_ptr_is_empty(const any_const_ptr &operand);

//! @brief Devuelve verdadero si el objeto es un bool.
bool is_const_ptr_to_bool(const any_const_ptr &operand);
const bool &deref_to_bool(const any_const_ptr &operand);

bool is_const_ptr_to_int(const any_const_ptr &operand);
const int &deref_to_int(const any_const_ptr &operand);

bool is_const_ptr_to_long_int(const any_const_ptr &operand);
const long int &deref_to_long_int(const any_const_ptr &operand);

bool is_const_ptr_to_vector_string(const any_const_ptr &operand);
const std::vector<std::string> &deref_to_vector_string(const any_const_ptr &operand);

bool is_const_ptr_to_vector_int(const any_const_ptr &operand);
const std::vector<int> &deref_to_vector_int(const any_const_ptr &operand);

bool is_const_ptr_to_vector_double(const any_const_ptr &operand);
const std::vector<double> &deref_to_vector_double(const any_const_ptr &operand);

bool is_const_ptr_to_vector_long_int(const any_const_ptr &);
const std::vector<long int> &deref_to_vector_long_int(const any_const_ptr &);

bool is_const_ptr_to_vector_any(const any_const_ptr &);
const std::vector<boost::any> &deref_to_vector_any(const any_const_ptr &);

bool is_const_ptr_to_size_t(const any_const_ptr &operand);
const size_t &deref_to_size_t(const any_const_ptr &operand);

bool is_const_ptr_to_string(const any_const_ptr &operand);
const std::string &deref_to_string(const any_const_ptr &operand);

bool is_const_ptr_to_path(const any_const_ptr &operand);
const Path &deref_to_path(const any_const_ptr &operand);

//! @brief Devuelve verdadero si el objeto es un float.
bool is_const_ptr_to_float(const any_const_ptr &operand);
const float &deref_to_float(const any_const_ptr &operand);

bool is_const_ptr_to_double(const any_const_ptr &operand);
const double &deref_to_double(const any_const_ptr &operand);

bool is_const_ptr_to_long_double(const any_const_ptr &operand);
const long double &deref_to_long_double(const any_const_ptr &operand);

bool is_const_ptr_to_m_int(const any_const_ptr &operand);
const m_int &deref_to_m_int(const any_const_ptr &operand);

bool is_const_ptr_to_m_sizet(const any_const_ptr &operand);
const m_sizet &deref_to_m_sizet(const any_const_ptr &operand);

bool is_const_ptr_to_m_double(const any_const_ptr &operand);
const m_double &deref_to_m_double(const any_const_ptr &operand);

bool is_const_ptr_to_m_string(const any_const_ptr &operand);
const m_string &deref_to_m_string(const any_const_ptr &operand);

bool is_const_ptr_to_matrizM(const any_const_ptr &operand);
const matrizM &deref_to_matrizM(const any_const_ptr &operand);

bool is_const_ptr_to_matrizMExpr(const any_const_ptr &operand);
const matrizMExpr &deref_to_matrizMExpr(const any_const_ptr &operand);

bool is_const_ptr_to_matriz_any(const any_const_ptr &operand);
const MatrizAny &deref_to_matriz_any(const any_const_ptr &operand);

bool is_const_ptr_to_expr_algebra(const any_const_ptr &operand);
const ExprAlgebra &deref_to_ExprAlgebra(const any_const_ptr &operand);

bool is_const_ptr_to_matriz_expr(const any_const_ptr &operand);
const matrizExpr &deref_to_matrizExpr(const any_const_ptr &operand);

bool is_const_ptr_to_number(const any_const_ptr &operand);
double deref_number_to_double(const any_const_ptr &operand);

bool is_const_ptr_to_lista(const any_const_ptr &operand);
const Lista &deref_to_lista(const any_const_ptr &operand);

bool is_const_ptr_to_mapa(const any_const_ptr &operand);
const Mapa &deref_to_mapa(const any_const_ptr &operand);

bool is_const_ptr_to_CmdFuncPorPuntos(const any_const_ptr &operand);
const CmdFuncPorPuntos &deref_to_CmdFuncPorPuntos(const any_const_ptr &operand);

bool is_const_ptr_to_ent_cmd(const any_const_ptr &operand);
const EntCmd &deref_to_ent_cmd(const any_const_ptr &operand);

bool is_const_ptr_to_geom_FT(const any_const_ptr &);
const GEOM_FT &deref_to_geom_FT(const any_const_ptr &);

bool is_const_ptr_to_matriz_FT(const any_const_ptr &operand);
const matriz_FT &deref_to_matriz_FT(const any_const_ptr &operand);

bool is_const_ptr_to_pos2d(const any_const_ptr &operand);
const Pos2d &deref_to_pos2d(const any_const_ptr &operand);

bool is_const_ptr_to_lista_pos2d(const any_const_ptr &operand);
const ListaPos2d &deref_to_lista_pos2d(const any_const_ptr &operand);

bool is_const_ptr_to_polilinea2d(const any_const_ptr &operand);
const Polilinea2d &deref_to_polilinea2d(const any_const_ptr &operand);

bool is_const_ptr_to_vector2d(const any_const_ptr &operand);
const Vector2d &deref_to_vector2d(const any_const_ptr &operand);

bool is_const_ptr_to_segmento2d(const any_const_ptr &operand);
const Segmento2d &deref_to_segmento2d(const any_const_ptr &operand);

bool is_const_ptr_to_poligono2d(const any_const_ptr &operand);
const Poligono2d &deref_to_poligono2d(const any_const_ptr &operand);

bool is_const_ptr_to_poligono_con_agujeros2d(const any_const_ptr &operand);
const PoligonoConAgujeros2d &deref_to_poligono_con_agujeros2d(const any_const_ptr &operand);

bool is_const_ptr_to_circulo2d(const any_const_ptr &operand);
const Circulo2d &deref_to_circulo2d(const any_const_ptr &operand);

bool is_const_ptr_to_vector3d(const any_const_ptr &operand);
const Vector3d &deref_to_vector3d(const any_const_ptr &operand);

bool is_const_ptr_to_recta2d(const any_const_ptr &operand);
const Recta2d &deref_to_recta2d(const any_const_ptr &operand);

bool is_const_ptr_to_recta3d(const any_const_ptr &operand);
const Recta3d &deref_to_recta3d(const any_const_ptr &operand);

bool is_const_ptr_to_plano3d(const any_const_ptr &operand);
const Plano3d &deref_to_plano3d(const any_const_ptr &operand);

bool is_const_ptr_to_segmento3d(const any_const_ptr &operand);
const Segmento3d &deref_to_segmento3d(const any_const_ptr &operand);

bool is_const_ptr_to_vdesliz2d(const any_const_ptr &operand);
const VDesliz2d &deref_to_vdesliz2d(const any_const_ptr &operand);

bool is_const_ptr_to_vdesliz3d(const any_const_ptr &operand);
const VDesliz3d &deref_to_vdesliz3d(const any_const_ptr &operand);

bool is_const_ptr_to_vfijo2d(const any_const_ptr &operand);
const VFijo2d &deref_to_vfijo2d(const any_const_ptr &operand);

bool is_const_ptr_to_vfijo3d(const any_const_ptr &operand);
const VFijo3d &deref_to_vfijo3d(const any_const_ptr &operand);

bool is_const_ptr_to_svd3d(const any_const_ptr &operand);
const SVD3d &deref_to_svd3d(const any_const_ptr &operand);

bool is_const_ptr_to_pos3d(const any_const_ptr &operand);
const Pos3d &deref_to_pos3d(const any_const_ptr &operand);

bool is_const_ptr_to_lista_pos3d(const any_const_ptr &operand);
const ListaPos3d &deref_to_lista_pos3d(const any_const_ptr &operand);

bool is_const_ptr_to_semiEspacio3d(const any_const_ptr &operand);
const SemiEspacio3d &deref_to_semiEspacio3d(const any_const_ptr &operand);

bool is_const_ptr_to_poliedro3d(const any_const_ptr &operand);
const Poliedro3d &deref_to_poliedro3d(const any_const_ptr &operand);

bool is_const_ptr_to_tetraedro3d(const any_const_ptr &operand);
const Tetraedro3d &deref_to_tetraedro3d(const any_const_ptr &operand);

bool is_const_ptr_to_blockPyramid(const any_const_ptr &operand);
const BlockPyramid &deref_to_blockPyramid(const any_const_ptr &operand);

bool is_const_ptr_to_sisCooRect2d3d(const any_const_ptr &operand);
const SisCooRect2d3d &deref_to_sisCooRect2d3d(const any_const_ptr &operand);

bool is_const_ptr_to_ref2d3d(const any_const_ptr &operand);
const Ref2d3d &deref_to_ref2d3d(const any_const_ptr &operand);

bool is_const_ptr_to_any_const_ptr(const any_const_ptr &operand);

std::string const_ptr_format(const any_const_ptr &operand,const std::string &format);
std::ostream &operator<<(std::ostream &os,const any_const_ptr &operand);


#endif
