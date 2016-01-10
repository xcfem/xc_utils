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
//vtkTakePhotoDefs.cc

#include "vtkTakePhotoDefs.h"

//! @brief Devuelve el formato del archivo a partir del entero que
//! se pasa como parámetro
sepFileFormat int_to_file_format(int f)
  {
    sepFileFormat retval= POSTSCRIPT;
    switch(f)
      {
      case 1:
        retval= POSTSCRIPT;
        break;
      case 2:
        retval= TIFF;
        break;
      case 3:
        retval= CGM;
        break;
      case 4: 
        retval= BMP;
        break;
      case 5:
        retval= VRML;
        break;
      default:
	std::cerr << f << " Unknow output format type\n";
      }
    return retval;
  }

//! @brief Devuelve el formato del archivo a partir del entero que
//! se pasa como parámetro
sepFileFormat string_to_file_format(const std::string &fmt_name)
  {
    sepFileFormat retval= POSTSCRIPT;
    if(fmt_name == "postscript")
      retval= POSTSCRIPT;
    else if(fmt_name == "tiff")
      retval=  TIFF;
    else if(fmt_name == "cgm")
      retval=  CGM;
    else if(fmt_name == "bmp")
      retval=  BMP;
    else if(fmt_name == "vrml")
      retval=  VRML;
    else
      std::cerr << fmt_name << " Unknow output format type\n";
    return retval;
  }
