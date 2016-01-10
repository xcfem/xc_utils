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
//vtkLabeledShStrMapper.h
//Modificación de vtkLabeledDataMapper para mostrar cadenas
//de caracteres cortas (han de caber en el espacio de un double).

#ifndef __vtkLabeledShStrMapper_h
#define __vtkLabeledShStrMapper_h

#include "vtkMapper2D.h"

class vtkDataSet;
class vtkTextMapper;
class vtkTextProperty;

class VTK_RENDERING_EXPORT vtkLabeledShStrMapper : public vtkMapper2D
{
public:
  // Description:
  // Instantiate object with %%-#6.3g label format. By default, point ids
  // are labeled.
  static vtkLabeledShStrMapper *New();

  vtkTypeRevisionMacro(vtkLabeledShStrMapper,vtkMapper2D);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // Set/Get the field data array to label. This instance variable is
  // only applicable if field data is labeled.
  vtkSetClampMacro(FieldDataArray,int,0,VTK_LARGE_INTEGER);
  vtkGetMacro(FieldDataArray,int);

  // Description:
  // Set the input dataset to the mapper. This mapper handles any type of data.
  virtual void SetInput(vtkDataSet*);
  vtkDataSet *GetInput();

  // Description:
  // Set/Get the text property.
  virtual void SetLabelTextProperty(vtkTextProperty *p);
  vtkGetObjectMacro(LabelTextProperty,vtkTextProperty);

  // Description:
  // Draw the text to the screen at each input point.
  void RenderOpaqueGeometry(vtkViewport* viewport, vtkActor2D* actor);
  void RenderOverlay(vtkViewport* viewport, vtkActor2D* actor);

  // Description:
  // Release any graphics resources that are being consumed by this actor.
  virtual void ReleaseGraphicsResources(vtkWindow *);


protected:
  vtkLabeledShStrMapper();
  ~vtkLabeledShStrMapper();

  vtkDataSet *Input;
  vtkTextProperty *LabelTextProperty;

  int   FieldDataArray;

  vtkTimeStamp BuildTime;

  inline int &NLabels()
    { return NumberOfLabels; }
  inline int &NLabelsAlloc()
    { return NumberOfLabelsAllocated; }

private:
  int NumberOfLabels;
  int NumberOfLabelsAllocated;
  vtkTextMapper **TextMappers;

  virtual int FillInputPortInformation(int, vtkInformation*);

private:
  vtkLabeledShStrMapper(const vtkLabeledShStrMapper&);  // Not implemented.
  void operator=(const vtkLabeledShStrMapper&);  // Not implemented.

public:
  inline const int &NLabels() const
    { return NumberOfLabels; }
  inline const int &NLabelsAlloc() const
    { return NumberOfLabelsAllocated; }

};

#endif

