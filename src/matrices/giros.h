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
//Giros.h
//Functions that create rotation matrices.

#ifndef GIROS_H
#define GIROS_H

#include "ZMatrix.h"

//En dos dimensiones.
ZMatrix<double> Giro2D(double ang);

//En tres dimensiones
ZMatrix<double> GiroX(double ang);
ZMatrix<double> GiroY(double ang);
ZMatrix<double> GiroZ(double ang);
ZMatrix<double> GiroXYZ(double rx,double ry,double rz);


#endif
