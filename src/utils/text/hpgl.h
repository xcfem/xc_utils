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
//hpgl.h
//Secuencias para programaci'on en HPGL de las impresoras HP.

#ifndef HPGL_H
#define HPGL_H

#include <iostream>

//Comandos de control de trabajo
inline void HPGLInitialize(std::ostream &os)
  { os << "IN;"; }
  
inline void HPGLSelectPen(std::ostream &os,short int pen)
  { os << "SP" << pen << ';'; }
  
inline void HPGLSetUserScaling(std::ostream &os,int x1,int x2,int y1,int y2)
  { os << "SC" << x1 << ',' << x2 << ',' << y1 << ',' << y2 << ';'; } 

//Movimiento de pluma.
inline void HPGLPenDown(std::ostream &os,int x,int y)
  { os << "PD" << x << ',' << y << ';'; }
inline void HPGLPenUp(std::ostream &os,int x,int y)
  { os << "PU" << x << ',' << y << ';'; }
inline void HPGLCircle(std::ostream &os,int r)
  { os << "CI" << r << ';'; }
  
//Modo
inline void HPGLPCLMode0(std::ostream &os)
//Entra en modo PCL empleando la posici'on previa
//del cursor HPGL.
  { os << char(27) << char(37) << char(48) << char(65); }
inline void HPGLPCLMode1(std::ostream &os)
//Entra en modo PCL empleando actual de la pluma HPGL2
  { os << char(27) << char(37) << char(49) << char(65); }
  
#endif
