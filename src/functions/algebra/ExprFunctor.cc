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
//ExprFunctor.cc

#include "ExprFunctor.h"
#include "Rama.h"

void FctorBorra::operator()(Rama *r) const
  { r->Borra(); }

void FctorOpera::operator()(Rama *r) const
  { r->Opera(r); }

void FctorOperaToNum::operator()(Rama *r) const
  {
    if(r->EsToNum()) //Es operador ToNum;
      {
        register FctorOpera f;
        RecorrePostorden(r,f);
      }
  }

void FctorAsigna::operator()(Rama *r) const
  { r->Asigna(po,p); }

void FctorGetVariables::operator()(Rama *r) const
   { r->GetVariables(cvar); }
