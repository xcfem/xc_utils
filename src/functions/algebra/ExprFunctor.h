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
//ExprFunctor.h

#ifndef EXPRFUNCTOR_H
#define EXPRFUNCTOR_H

class Rama;

class ExprFunctor
  {
  public:
    virtual void operator()(Rama *r) const= 0;
    inline virtual ~ExprFunctor(void) {}
  };

class FctorBorra : public ExprFunctor
  {
  public:
    virtual void operator()(Rama *r) const;
  };

class FctorOpera : public ExprFunctor
  {
  public:
    virtual void operator()(Rama *r) const;
  };

class FctorOperaToNum : public ExprFunctor
  {
  public:
    virtual void operator()(Rama *r) const;
  };

class Operando;
class FctorAsigna : public ExprFunctor
  {
    Operando *po;
    const Rama *p;
  public:
    FctorAsigna(Operando *pop,const Rama *pr): po(pop),p(pr) {}
    virtual void operator()(Rama *r) const;
  };
class ConjVariables;
class FctorGetVariables : public ExprFunctor
  {
    ConjVariables &cvar;
  public:
    FctorGetVariables(ConjVariables &cv): cvar(cv) {}
    virtual void operator()(Rama *r) const;
  };


#endif




