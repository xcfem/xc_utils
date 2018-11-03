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
//tab_cod.hxx
//Utilidades para tablas de códigos.
#ifndef TAB_COD_H
#define TAB_COD_H

#include <string>

char latin1TOpc850ML(int c);

std::string latin1TOpc850ML(const std::string &s);

unsigned char pc8TOlatin1(int c);

std::string pc8TOlatin1(const std::string &);

std::string iso8859_1TOlatex(int c);
//Devuelve el codigo de las vocales con acento y la egne
//en LaTex a partir de su c'odigo en ASCII iso8859/1 Latin 1.

std::string iso8859_1TO_utf8(const std::string &);

#endif
