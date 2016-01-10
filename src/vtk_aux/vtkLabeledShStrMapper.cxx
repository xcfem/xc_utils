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
//vtkLabeledShStrMapper.cxx

#include "vtkLabeledShStrMapper.h"

#include "vtkExecutive.h"
#include "vtkInformation.h"
#include "vtkActor2D.h"
#include "vtkDataArray.h"
#include "vtkDataSet.h"
#include "vtkShStrArray.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkTextMapper.h"
#include "vtkTextProperty.h"
#include <assert.h>

vtkCxxRevisionMacro(vtkLabeledShStrMapper, "$Revision: 1.40 $")
vtkStandardNewMacro(vtkLabeledShStrMapper)

vtkCxxSetObjectMacro(vtkLabeledShStrMapper,LabelTextProperty,vtkTextProperty)

//----------------------------------------------------------------------------
// Creates a new label mapper

vtkLabeledShStrMapper::vtkLabeledShStrMapper()
{
  this->Input = NULL;

  this->FieldDataArray = 0;
 
  this->NLabels() = 0;
  this->NLabelsAlloc() = 50;

  this->TextMappers = new vtkTextMapper * [this->NLabelsAlloc()];
  for (int i=0; i<this->NLabelsAlloc(); i++)
    {
    this->TextMappers[i] = vtkTextMapper::New();
    }

  this->LabelTextProperty = vtkTextProperty::New();
  this->LabelTextProperty->SetFontSize(12);
  this->LabelTextProperty->SetBold(1);
  this->LabelTextProperty->SetItalic(1);
  this->LabelTextProperty->SetShadow(1);
  this->LabelTextProperty->SetFontFamilyToArial();
}

//----------------------------------------------------------------------------
vtkLabeledShStrMapper::~vtkLabeledShStrMapper()
  {
    if(this->TextMappers != NULL )
      {
        for (int i=0; i < this->NLabelsAlloc(); i++)
          { this->TextMappers[i]->Delete(); }
        delete [] this->TextMappers;
      }
    this->SetLabelTextProperty(NULL);
  }

//----------------------------------------------------------------------------
void vtkLabeledShStrMapper::SetInput(vtkDataSet *input)
  {
    if (input)
      { this->SetInputConnection(0, input->GetProducerPort()); }
    else
      { this->SetInputConnection(0, 0); } // Setting a NULL input removes the connection.
  }

//----------------------------------------------------------------------------
// Specify the input data or filter.
vtkDataSet *vtkLabeledShStrMapper::GetInput()
  { return vtkDataSet::SafeDownCast(this->GetExecutive()->GetInputData(0, 0)); }

//----------------------------------------------------------------------------
// Release any graphics resources that are being consumed by this mapper.
void vtkLabeledShStrMapper::ReleaseGraphicsResources(vtkWindow *win)
  {
    if(this->TextMappers != NULL )
      {
        for (int i=0; i < this->NLabelsAlloc(); i++)
          { this->TextMappers[i]->ReleaseGraphicsResources(win); }
      }
  }

//----------------------------------------------------------------------------
void vtkLabeledShStrMapper::RenderOverlay(vtkViewport *viewport, 
                                         vtkActor2D *actor)
  {
    int i;
    double x[3];
    vtkDataSet *input=this->GetInput();

    if(!input)
      {
        vtkErrorMacro(<<"Need input data to render labels");
        return;
      }
    for(i=0; i<this->NLabels(); i++)
      {
        input->GetPoint(i,x);
        actor->GetPositionCoordinate()->SetCoordinateSystemToWorld();
        actor->GetPositionCoordinate()->SetValue(x);
        this->TextMappers[i]->RenderOverlay(viewport, actor);
      }
  }

//----------------------------------------------------------------------------
void vtkLabeledShStrMapper::RenderOpaqueGeometry(vtkViewport *viewport, 
                                                vtkActor2D *actor)
  {
    int i,numComp = 0, pointIdLabels;
    double x[3];
    vtkDataSet *input=this->GetInput();

    if(!input)
      {
        vtkErrorMacro(<<"Need input data to render labels");
        return;
      }

    vtkPointData *pd=input->GetPointData();
    vtkTextProperty *tprop = this->LabelTextProperty;
    if(!tprop)
      {
        vtkErrorMacro(<<"Need text property to render labels");
        return;
      }

    input->Update();

    // Check to see whether we have to rebuild everything
    if ( this->GetMTime() > this->BuildTime || 
         input->GetMTime() > this->BuildTime ||
         tprop->GetMTime() > this->BuildTime)
      {
        vtkDebugMacro(<<"Rebuilding labels");

        // figure out what to label, and if we can label it
        pointIdLabels = 0;

        int arrayNum = (this->FieldDataArray < pd->GetNumberOfArrays() ?
                        this->FieldDataArray : pd->GetNumberOfArrays() - 1);
        vtkDataArray *data = pd->GetArray(arrayNum);

        // determine number of components and check input
        if(pointIdLabels)
          {
            ;
          }
        else
          if(data)
            {
              numComp = data->GetNumberOfComponents();
              assert(numComp==1);
            }
          else
            {
              vtkErrorMacro(<<"Need input data to render labels");
              return;
            }

        this->NLabels() = input->GetNumberOfPoints();
        if(this->NLabels() > this->NLabelsAlloc() )
          {
            // delete old stuff
            for (i=0; i < this->NLabelsAlloc(); i++)
              { this->TextMappers[i]->Delete(); }
            delete [] this->TextMappers;

            this->NLabelsAlloc() = this->NLabels();
            this->TextMappers = new vtkTextMapper * [this->NLabelsAlloc()];
            for(i=0; i<this->NLabelsAlloc(); i++)
              { this->TextMappers[i] = vtkTextMapper::New(); }
          }//if we have to allocate new text mappers
    
        for (i=0; i < this->NLabels(); i++)
          {
            const double tmp= data->GetComponent(i,0);
            const std::string str= vtkShStrArray::dbl_to_str(tmp);
            this->TextMappers[i]->SetInput(str.c_str());
            this->TextMappers[i]->SetTextProperty(tprop);
          }

        this->BuildTime.Modified();
      }

    for (i=0; i<this->NLabels(); i++)
      {
        input->GetPoint(i,x);
        actor->GetPositionCoordinate()->SetCoordinateSystemToWorld();
        actor->GetPositionCoordinate()->SetValue(x);
        this->TextMappers[i]->RenderOpaqueGeometry(viewport, actor);
      }
  }

//----------------------------------------------------------------------------
int vtkLabeledShStrMapper::FillInputPortInformation(int vtkNotUsed( port ), vtkInformation* info)
  {
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkShStrArray");
    return 1;
  }

//----------------------------------------------------------------------------
void vtkLabeledShStrMapper::PrintSelf(ostream& os, vtkIndent indent)
  {
    this->Superclass::PrintSelf(os,indent);

    if( this->Input )
      { os << indent << "Input: (" << this->Input << ")\n"; }
    else
      { os << indent << "Input: (none)\n"; }

    if(this->LabelTextProperty)
      {
        os << indent << "Label Text Property:\n";
        this->LabelTextProperty->PrintSelf(os,indent.GetNextIndent());
      }
    else
      { os << indent << "Label Text Property: (none)\n"; }

    os << indent << "Label Mode: ";
    os << "Label Strs\n";

    os << indent << "Field Data Array: " << this->FieldDataArray << "\n";
  }
