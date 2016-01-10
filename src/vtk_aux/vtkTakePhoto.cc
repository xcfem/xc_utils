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
#include "vtkTakePhoto.h"
#include <vtkWindowToImageFilter.h>
#include <vtkBMPWriter.h>
#include <vtkCGMWriter.h>
#include <vtkTIFFWriter.h>
#include <vtkPostScriptWriter.h>
#include <vtkVRMLExporter.h>
#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTakePhoto)

//! @brief Constructor por defecto.
vtkTakePhoto::vtkTakePhoto(void)
  : name("vtkFileSnapshot"),renWin(NULL),
   w2if(NULL),format(POSTSCRIPT)
  {
    w2if= vtkWindowToImageFilter::New();
    w2if->Register(this);
    w2if->Delete();
  }

//! @brief Destructor.
vtkTakePhoto::~vtkTakePhoto(void) 
  { if(w2if) w2if->UnRegister(this); }


void vtkTakePhoto::SetRenderWindow(vtkRenderWindow *aren)
  {
    if(this->renWin != aren)
      {
        // to avoid destructor recursion
        vtkRenderWindow *temp = this->renWin;
        this->renWin = aren;
        if(temp)
          { temp->UnRegister(this); }
        if(this->renWin)
          {
            this->renWin->Register(this);
          }
      }
  }


void vtkTakePhoto::SetFileName(const std::string &nmb)
  { name= nmb; }

//! @brief Establece el formato del archivo de salida
void vtkTakePhoto::SetFileFormat(int f)
  { SetFileFormat(int_to_file_format(f)); }

//! @brief Establece el formato del archivo de salida
void vtkTakePhoto::SetFileFormat(const std::string &fmt_name)
  { SetFileFormat(string_to_file_format(fmt_name)); }

//! @brief Escribe el archivo.
bool vtkTakePhoto::Write(void)
  {
    if(!renWin)
      {
	std::cerr << "Unable to write output file " << this->name
                  << "first call function vtkTakePhoto::SetInput\n";
        return false;
      }  
    w2if->SetInput(renWin);
    switch(this->format)
      {
        case POSTSCRIPT:
          {
            vtkPostScriptWriter *psw = vtkPostScriptWriter::New();
            psw->SetInput(w2if->GetOutput());
            psw->SetFileName(name.c_str());
            psw->Write();
            psw->Delete();
            break;
          }
        case TIFF:
          {
            vtkTIFFWriter *tiffw = vtkTIFFWriter::New();
            tiffw->SetInput(w2if->GetOutput());
            tiffw->SetFileName(name.c_str());
            tiffw->Write();
            tiffw->Delete();
            break;
          }
        case CGM:
          {
	    std::cerr << __FILE__ << " CGM Writer not implemented yet !\n";
            return false;
       
            //vtkCGMWriter *cgmw = vtkCGMWriter::New();
            //cgmw->SetInput(this->cube);
            //cgmw->SetFileName(name.c_str());
            //cgmw->Write();
            //cgmw->Delete();
            // break; 
         }
       case BMP:
         {
           vtkBMPWriter *bmpw = vtkBMPWriter::New();
           bmpw->SetInput(w2if->GetOutput());
           bmpw->SetFileName(name.c_str());
           bmpw->Write();
           bmpw->Delete();
           break;
         }
       case VRML:
         {
           vtkVRMLExporter *vrmlw = vtkVRMLExporter::New();
           vrmlw->SetInput(this->renWin);
           vrmlw->SetFileName(name.c_str());
           vrmlw->Write();
           vrmlw->Delete();
           break;
         }
       default:
	 std::cerr << __FILE__ << " Unknow file format\n";
         return false;
       }
     return true;
  }
