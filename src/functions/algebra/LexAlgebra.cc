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
//LexAlgebra.cc


#include "LexAlgebra.h"
#include "VarExpr.h"

LexAlgebra::LexAlgebra(void)
  : Lexico(), expresiones() {}

VarExpr *LexAlgebra::CalcDirExpr(const std::string &nmb)
  { return expresiones.CalcDir(nmb); }

OpndoConNombre *LexAlgebra::NuevaVar(const Variable &v)
  {
    //Si existía como expresión advertimos del problema:
    TablaExpresiones::const_iterator i= expresiones.find(v.getName());
    if(i!=expresiones.end())
      std::cerr << "¡Ojo! la variable: '" << v.getName() 
           << "' ya existe como expresión." << std::endl;
    //La agregamos a la tabla de expresiones.
    return vars.Nueva(v);
  }

OpndoConNombre *LexAlgebra::NuevaExpr(const VarExpr &v)
  {
    //Si existía como variable advertimos del problema:
    TablaVariables::const_iterator i= vars.find(v.getName());
    if(i!=vars.end())
      std::cerr << "¡Ojo! la expresión: '" << v.getName() 
           << "' ya existe como variable." << std::endl;
    //Si realmente es nueva, la agregamos a la tabla de expresiones.
    TablaExpresiones::iterator j= expresiones.find(v.getName());
    OpndoConNombre *retval= NULL;
    if(j==expresiones.end())
      retval= expresiones.Nueva(v);
    else
      retval= &((*j).second);
    return retval;
  }

void LexAlgebra::AsignaExpr(const std::string &palabra,const ExprAlgebra &e)
  { expresiones[palabra].AsignaExpr(e); }


