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
//python_interface.h

#ifndef python_interface_h
#define python_interface_h

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/docstring_options.hpp>
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos3d.h"
#include "xc_utils/src/geom/pos_vec/TritrizPos2d.h"
#include "xc_utils/src/geom/pos_vec/TritrizPos3d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/func_por_puntos/FuncPorPuntosR_R.h"
#include "xc_utils/src/geom/d1/func_por_puntos/FuncPorPuntosR2_R.h"
#include "xc_utils/src/geom/d2/BND2d.h"
#include "xc_utils/src/geom/d2/Superficie2d.h"
#include "xc_utils/src/geom/d2/Semiplano2d.h"
#include "xc_utils/src/geom/d2/Circulo2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/SupPoligonal2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Triangulo2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Cuadrado2d.h"
#include "xc_utils/src/geom/d1/Polilinea2d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/PoligonoConAgujeros2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/bool_op_poligono2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz2d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz3d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/SemiRecta3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d3/BND3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"
#include "xc_utils/src/geom/d1/Polilinea3d.h"
//#include "xc_utils/src/geom/d3/Solido3d.h"
#include "xc_utils/src/geom/d2/Superficie3d.h"
#include "xc_utils/src/geom/d2/EcuacionGeneralPlano3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d2/Triangulo3d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Cuadrilatero2d.h"
#include "xc_utils/src/geom/d2/Rejilla2d.h"
#include "xc_utils/src/geom/pos_vec/SVD2d.h"
#include "xc_utils/src/geom/pos_vec/SVD3d.h"
#include "xc_utils/src/geom/sis_ref/EjesPrincInercia2d.h"
#include "xc_utils/src/geom/sis_ref/Ref1d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref1d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref3d3d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/geom/trf/Escalado2d.h"
#include "xc_utils/src/geom/trf/Escalado3d.h"
#include "xc_utils/src/geom/trf/Identidad2d.h"
#include "xc_utils/src/geom/trf/Identidad3d.h"
#include "xc_utils/src/geom/trf/Reflexion2d.h"
#include "xc_utils/src/geom/trf/Reflexion3d.h"
#include "xc_utils/src/geom/trf/Revolucion3d.h"
#include "xc_utils/src/geom/trf/Rotacion2d.h"
#include "xc_utils/src/geom/trf/Rotacion3d.h"
#include "xc_utils/src/geom/trf/Traslacion2d.h"
#include "xc_utils/src/geom/trf/Traslacion3d.h"

typedef std::deque<Pos2d> dq_pos2d;
typedef PoliPos<Pos2d> poliPos2d;
typedef std::deque<Pos3d> dq_pos3d;
typedef PoliPos<Pos3d> poliPos3d;

std::list<Poligono2d> from_python_list(boost::python::list &);
boost::python::list to_python_list(const std::list<Poligono2d> &);

//! @brief Devuelve el resultado de repartir el área común entre los 
//! polígonos de la lista mediante la técnica de Voronoi.
boost::python::list python_particiona(boost::python::list &);
boost::python::list python_recorta(boost::python::list &, const Poligono2d &);

#endif
