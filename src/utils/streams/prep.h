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
//prep.h
//Preprocessing functions.

#ifndef PREP_H
#define PREP_H

#include <iostream>
#include <string>

void quita_comentarios(std::istream &,std::ostream &);
int busca_y_sust1(std::istream &,const std::string &,std::ostream &,const std::string &);
int busca_y_sust(std::istream &,const std::string &,std::ostream &,const std::string &);

std::string get_bloque_comillas(std::istream &, bool &error);
std::string get_bloque_parentesis(std::istream &,bool &error);
std::string get_bloque_llaves(std::istream &is,bool &error,const bool &ignora_esp);

#endif
