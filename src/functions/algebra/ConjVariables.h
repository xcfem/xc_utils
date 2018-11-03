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
//ConjVariables.h

#ifndef CONJVARIABLES_H
#define CONJVARIABLES_H

#include "TablaVariables.h"
#include <set>
#include <vector>

class ConjVariables : public std::set<const Variable *>
  {
  public:
    typedef std::set<const Variable *> pset_CV;

    bool In(const Variable *var) const;
    bool In(const Variable &var) const;
    std::vector<std::string> getNombres(void) const;
  };

std::ostream &operator << (std::ostream &stream,const ConjVariables &cv);


#endif
