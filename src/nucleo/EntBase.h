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
//EntBase.h

#ifndef ENTBASE_H
#define ENTBASE_H

#include <string>
#include <vector>
#include "xc_basic/src/matrices/m_double.h"
#include "xc_basic/src/matrices/m_int.h"
#include "xc_basic/src/matrices/m_string.h"

class any_const_ptr;
class ExprAlgebra;
class BloqueSub;
class Lista;
class Mapa;
class Record;
class Path;
class CmdFuncPorPuntos;
class RangoIndice;
class MatrizAny;
class matrizExpr;
class Pos2d;
class Vector2d;
class Segmento2d;
class Circulo2d;
class Poligono2d;
class PoligonoConAgujeros2d;
class ListaPos2d;
class Polilinea2d;
class ListaPos3d;
class Pos3d;
class Vector3d;
class Segmento3d;
class VDesliz2d;
class VFijo2d;
class VDesliz3d;
class VFijo3d;
class SVD3d;
class Recta2d;
class Recta3d;
class Plano3d;
class SemiEspacio3d;
class Tetraedro3d;
class BlockPyramid;
class SisCooRect2d3d;
class Ref2d3d;
class Poliedro3d;

namespace boost
  {
    class any;
  }

//! @defgroup CMDINTRP Intérprete de comandos.
//
//! @ingroup CMDINTRP
//
//! @defgroup NUCLEO Núcleo del intérprete de comandos.
//
//! @ingroup NUCLEO
//
//! @brief Funciones básicas para interpretar valores.
class EntBase
  {
  protected:
    static std::string tmp_gp_str; //!< Variable temporal para devolución de propiedades (GetProp).
    static Path tmp_gp_path; //!< Variable temporal para devolución de propiedades (GetProp).
    static int tmp_gp_int; //!< Variable temporal para devolución de propiedades (GetProp).
    static long int tmp_gp_lint; //!< Variable temporal para devolución de propiedades (GetProp).
    static size_t tmp_gp_szt; //!< Variable temporal para devolución de propiedades (GetProp).
    static bool tmp_gp_bool; //!< Variable temporal para devolución de propiedades (GetProp). 
    static double tmp_gp_dbl; //!< Variable temporal para devolución de propiedades (GetProp).
    static long double tmp_gp_ldbl; //!< Variable temporal para devolución de propiedades (GetProp).
    static ExprAlgebra tmp_gp_expr; //!< Variable temporal para devolución de propiedades (GetProp).
    static matrizExpr tmp_gp_mexpr; //!< Variable temporal para devolución de propiedades (GetProp).
    static m_double tmp_gp_mdbl; //!< Variable temporal para devolución de propiedades (GetProp).
    static m_int tmp_gp_mint; //!< Variable temporal para devolución de propiedades (GetProp).
    static m_string tmp_gp_mstr; //!< Variable temporal para devolución de propiedades (GetProp).
    static MatrizAny tmp_gp_many; //!< Variable temporal para devolución de propiedades (GetProp).
    static Lista tmp_gp_lista; //!< Variable temporal para devolución de propiedades (GetProp).
    static Mapa tmp_gp_mapa; //!< Variable temporal para devolución de propiedades (GetProp).
    static CmdFuncPorPuntos tmp_gp_func_pts; //!< Variable temporal para devolución de propiedades (GetProp).
    static RangoIndice tmp_gp_rng; //!< Variable temporal para devolución de propiedades (GetProp).
    static Record tmp_gp_record; //!< Variable temporal para devolución de propiedades (GetProp).
    static std::vector<boost::any> tmp_gp_vany; //!< Variable temporal para devolución de propiedades (GetProp).
    static Pos2d tmp_gp_pos2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Vector2d tmp_gp_vector2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Segmento2d tmp_gp_segmento2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Circulo2d tmp_gp_circulo2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Poligono2d tmp_gp_pol2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static PoligonoConAgujeros2d tmp_gp_poligonoConAgujeros2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static ListaPos2d tmp_gp_lpos2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Polilinea2d tmp_gp_polilinea2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static ListaPos3d tmp_gp_lpos3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Pos3d tmp_gp_pos3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Vector3d tmp_gp_vector3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Segmento3d tmp_gp_segmento3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static VDesliz2d tmp_gp_vdesliz2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static VDesliz3d tmp_gp_vdesliz3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static VFijo2d tmp_gp_vfijo2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static VFijo3d tmp_gp_vfijo3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static SVD3d tmp_gp_svd3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Recta2d tmp_gp_recta2d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Recta3d tmp_gp_recta3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Plano3d tmp_gp_plano3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static SemiEspacio3d tmp_gp_se3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Tetraedro3d tmp_gp_tetra3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Poliedro3d tmp_gp_poliedro3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static BlockPyramid tmp_gp_blockPyramid; //!< Variable temporal para devolución de propiedades (GetProp).
    static SisCooRect2d3d tmp_gp_sisCooRect2d3d; //!< Variable temporal para devolución de propiedades (GetProp).
    static Ref2d3d tmp_gp_ref2d3d; //!< Variable temporal para devolución de propiedades (GetProp).


    virtual bool interpretaUno(const std::string &) const= 0;

   public:
    EntBase(void);
    const boost::any &interpretaAny(const std::string &) const;
    const std::string &interpretaString(const std::string &) const;
    const Path &interpretaPath(const std::string &) const;
    const ExprAlgebra &interpretaExpr(const std::string &) const;
    const matrizExpr &interpretaMatrizExpr(const std::string &str) const;
    const double &interpretaDouble(const std::string &) const;
    const int &interpretaInt(const std::string &) const;
    const bool &interpretaBool(const std::string &) const;
    const size_t &interpretaSize_t(const std::string &) const;
    const Lista &interpretaLista(const std::string &) const;
    const Record &interpretaRecord(const std::string &) const;
    const Mapa &interpretaMapa(const std::string &) const;
    const CmdFuncPorPuntos &interpretaFuncPorPuntos(const std::string &) const;
    const std::vector<boost::any> &interpretaVectorAny(const std::string &) const;
    const MatrizAny &interpretaMatrizAny(const std::string &) const;
    const RangoIndice &interpretaRango(const std::string &) const;
    const m_double &interpretaMDouble(const std::string &) const;
    const m_int &interpretaMInt(const std::string &) const;
    const m_string &interpretaMString(const std::string &) const;
    const Pos2d &interpretaPos2d(const std::string &) const;
    const Vector2d &interpretaVector2d(const std::string &) const;
    const Segmento2d &interpretaSegmento2d(const std::string &) const;
    const Circulo2d &interpretaCirculo2d(const std::string &) const;
    const Poligono2d &interpretaPoligono2d(const std::string &) const;
    const PoligonoConAgujeros2d &interpretaPoligonoConAgujeros2d(const std::string &) const;
    const ListaPos2d &interpretaListaPos2d(const std::string &) const;
    const Polilinea2d &interpretaPolilinea2d(const std::string &) const;
    const ListaPos3d &interpretaListaPos3d(const std::string &) const;
    const Pos3d &interpretaPos3d(const std::string &) const;
    const Vector3d &interpretaVector3d(const std::string &) const;
    const Segmento3d &interpretaSegmento3d(const std::string &) const;
    const VDesliz2d &interpretaVDesliz2d(const std::string &) const;
    const VDesliz3d &interpretaVDesliz3d(const std::string &) const;
    const VFijo2d &interpretaVFijo2d(const std::string &) const;
    const VFijo3d &interpretaVFijo3d(const std::string &) const;
    const SVD3d &interpretaSVD3d(const std::string &) const;
    const Recta2d &interpretaRecta2d(const std::string &) const;
    const Recta3d &interpretaRecta3d(const std::string &) const;
    const Plano3d &interpretaPlano3d(const std::string &) const;
    const SemiEspacio3d &interpretaSemiEspacio3d(const std::string &) const;
    const Tetraedro3d &interpretaTetraedro3d(const std::string &) const;
    const BlockPyramid &interpretaBlockPyramid(const std::string &) const;
    const SisCooRect2d3d &interpretaSisCooRect2d3d(const std::string &) const;
    const Ref2d3d &interpretaRef2d3d(const std::string &) const;
    const Poliedro3d &interpretaPoliedro3d(const std::string &) const;

  };

#endif
