//----------------------------------------------------------------------------
//  biblioteca vtk_aux; utilidades construidas sobre VTK (<http://www.vtk.org>)
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
                                                                // -*- C++ -*-
/*****************************************************************************/
/*                                                                           */
/* (c) Copyright 2001                                                        */
/*     Stanford Exploration Project, SEP.                                    */    
/*     Numerica Ltda, Bucaramanga, Colombia.                                 */
/*     All left reserved.                                                    */
/*                                                                           */
/*     See http://www.stanford.edu/ for further details.                     */
/*                                                                           */
/*****************************************************************************/
/* Elkin Rafael Arroyo Negrete, Numerica Ltda, ERAN */

#ifndef CUBE_DEFS_IS_INCLUDED
#define CUBE_DEFS_IS_INCLUDED

#include<iostream>

typedef enum
  {
    POSTSCRIPT= 1,
    TIFF= 2,
    CGM= 3,
    BMP= 4,
    VRML= 5  
  } sepFileFormat;// Format to save images

sepFileFormat int_to_file_format(int );
sepFileFormat string_to_file_format(const std::string &);

#endif // CUBE_DEFS_IS_INCLUDED
