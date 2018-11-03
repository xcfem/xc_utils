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
//ProtoExpresion.h

#ifndef PROTOEXPRESION_H
#define PROTOEXPRESION_H

#include <string>

class Lexico;
class LexAlgebra;
class Operando;
class OpndoConNombre;
class Segnal;
class Variable;

class ProtoExpresion
  {
  protected:
    static LexAlgebra *ptr_lex;

    static Segnal *CalcularDireccion(const std::string &nmb);
  public:
    ProtoExpresion(void);
    static LexAlgebra &CreaLexico(void);
    static Lexico &Lex(void);
    static LexAlgebra &LexA(void);
    static bool TieneLexico(void);
    static OpndoConNombre *NuevaVar(const Variable &v);
    static OpndoConNombre *NuevaVar(const std::string &palabra);
    static Variable *CalcDirVar(const std::string &nmb);
    static void Asigna(const std::string &palabra,const double &d);
    static void DesAsigna(const std::string &palabra);
  };

#endif
