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
//print_trace.cc

#include "print_trace.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

#ifdef HAVE_EXECINFO_H
#include <execinfo.h>

void print_trace(void)
  {
    void *array[10];
    char **strings;
     
    const size_t size= backtrace(array, 10);
    strings = backtrace_symbols(array, size);
     
    std::cerr << "Obtained " << size << " stack frames.\n";
     
    for(size_t i = 0; i < size; i++)
      std::cerr << strings[i] << std::endl;
     
    free (strings);
  }
#else
void print_trace(void)
  { std::cerr << "print_trace no implementada en este sistema." << std::endl; }
#endif
