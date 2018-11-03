//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//ProtoExpresion.cc
#include "LexAlgebra.h"
#include "ProtoExpr.h"
#include <cassert>

LexAlgebra *ProtoExpresion::ptr_lex= NULL;

//!@brief Constructor.
ProtoExpresion::ProtoExpresion(void)
  {}

//! @brief Devuelve una referencia al léxico.
Lexico &ProtoExpresion::Lex(void)
  { return *ptr_lex; }

//! @brief Devuelve una referencia al léxico.
LexAlgebra &ProtoExpresion::LexA(void)
  { return *ptr_lex; }

//! @brief Devuelve una referencia al léxico.
LexAlgebra &ProtoExpresion::CreaLexico(void)
  {
    if(!ptr_lex)
      {
        ptr_lex= new LexAlgebra;
        assert(ptr_lex);
      }
    return *ptr_lex;
  }

bool ProtoExpresion::TieneLexico(void)
  { return (ptr_lex!=NULL); }

//! @brief Devuelve un puntero a la variable cuyo nombre se pasa como parámetro.
Variable *ProtoExpresion::CalcDirVar(const std::string &nmb)
  { return ptr_lex->CalcDirVar(nmb); }
//! @brief Crea la variable cuyo nombre se pasa como parámetro.
OpndoConNombre *ProtoExpresion::NuevaVar(const Variable &v)
  { return ptr_lex->NuevaVar(v); }
//! @brief Crea la variable cuyo nombre se pasa como parámetro.
OpndoConNombre *ProtoExpresion::NuevaVar(const std::string &palabra)
  { return ptr_lex->NuevaVar(Variable(palabra)); }

//! @brief Devuelve un puntero a la señal cuyo nombre se pasa como parámetro.
Segnal *ProtoExpresion::CalcularDireccion(const std::string &nmb)
  { return ptr_lex->CalcularDireccion(nmb); }

//! @brief Asigna a la variable de nombre 'palabra' el valor que se pasa como parámetro.
void ProtoExpresion::Asigna(const std::string &palabra,const double &d)
  { ptr_lex->Asigna(palabra,d); }
//! @brief Elimina la asignación a la variable cuyo nombre se pasa como parámetro.
void ProtoExpresion::DesAsigna(const std::string &palabra)
  { ptr_lex->DesAsigna(palabra); }
