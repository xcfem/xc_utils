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
//LexAlgebra.h

#ifndef LEXALGEBRA_H
#define LEXALGEBRA_H

#include "Lexico.h"
#include "TablaExpresiones.h"

class VarExpr;


//! @brief Léxico para expresiones algebraicas.
class LexAlgebra : public Lexico
  {
  private:
    friend class ExprAlgebra;
    TablaExpresiones expresiones;
    inline ExprAlgebra GetExpresion(const std::string &nmb)
      { return CalcDirExpr(nmb)->GetExpr(); }
  public:
    LexAlgebra(void);
    inline bool EsExpresion(const std::string &nmb)
      { return (expresiones.find(nmb)!=expresiones.end()); }
    virtual VarExpr *CalcDirExpr(const std::string &nmb);
    inline virtual Variable *CalcDirVar(const std::string &nmb)
      {
        Variable *retval= CalcDirExpr(nmb);
        if(!retval)
         retval= vars.CalcDir(nmb);
        return retval;
      }
    OpndoConNombre *NuevaVar(const Variable &v);
    inline OpndoConNombre *NuevaVar(const std::string &palabra)
      { return NuevaVar(Variable(palabra)); }
    OpndoConNombre *NuevaExpr(const VarExpr &v);
    inline OpndoConNombre *NuevaExpr(const std::string &palabra)
      { return NuevaExpr(VarExpr(palabra)); }
    void AsignaExpr(const std::string &palabra,const ExprAlgebra &e);
 };
#endif
