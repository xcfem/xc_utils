//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//OpndoConNombre.cc

#include "OpndoConNombre.h"
#include <iostream>

std::istream &operator>>(std::istream &is, OpndoConNombre &s)
  {
    if(is.eof()) return is;
    s.nombre= "";
    register char c; c= is.get();
    while(isalnum(c))
      {
        s.nombre+= c;
        if(is.eof()) break;
        c= is.get();
      }
    is.putback(c);
    return is;
  }
