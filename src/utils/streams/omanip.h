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
//omanip.h

#ifndef OMANIP_H
#define OMANIP_H

#include<ostream>
#include<iomanip>


template <class TP>
class omanip
 {
 public:
   std::ostream& (*_f)(std::ostream&, TP);
   TP _a;
   omanip(std::ostream& (*f)(std::ostream&, TP), TP a) : _f(f), _a(a) {}
   //friend std::ostream& operator<< <>(std::ostream& o, const omanip<TP>& m);
 };

template <class TP>
inline std::ostream& operator<<(std::ostream& o, const omanip<TP>& m)
  { return (*m._f)(o, m._a); }

inline std::ostream &endl_msdos(std::ostream &os)
  { return os << char(13) << char(10); }

#endif
