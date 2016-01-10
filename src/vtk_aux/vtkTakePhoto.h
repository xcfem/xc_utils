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

 //Modificado LCPT 10-2006.


#ifndef VTK_TAKEPHOTO_H
#define VTK_TAKEPHOTO_H

#include<vtkRenderWindow.h>
#include"vtkTakePhotoDefs.h"
 
class vtkWindowToImageFilter;

//! @brief This class is intended to write images
//! in differents formats, VRML, BMP, POSTSCRIPT/
//! also contain the information of the name of the output
//! file. 
class vtkTakePhoto: public vtkObject
  {
  private:
    std::string name;  
    vtkRenderWindow *renWin;
    vtkWindowToImageFilter *w2if;
    sepFileFormat format;

    vtkTakePhoto(const vtkTakePhoto &otro); //Not implemented.
    vtkTakePhoto &operator=(const vtkTakePhoto &otro); //Not implemented.
  public :
    vtkTakePhoto(void);
    static vtkTakePhoto* New();
    ~vtkTakePhoto(void);

    // void SetInput(vtkStructuredPoints *);
    void SetRenderWindow(vtkRenderWindow *);
    void SetFileName(const std::string &name);
    void SetFileFormat(sepFileFormat f)
      {this->format=f;}
    void SetFileFormat(int f);
    void SetFileFormat(const std::string &);
    bool Write(void);
  };

#endif
