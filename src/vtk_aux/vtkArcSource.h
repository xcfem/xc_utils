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
//vtkArcSource.h
// vtkArcSource is a source object that creates a single
// n-sided polyline inscribed in an arc of circle.

#ifndef __vtkArcSource_h
#define __vtkArcSource_h

#include "vtkRegularPolygonSource.h"

class VTK_GRAPHICS_EXPORT vtkArcSource : public vtkRegularPolygonSource 
  {
  protected:
    double InitAng;
    double FinalAng;
    double Px[3]; //Vector unitario en la dirección del eje x.

    void GetNormal(double v[3]);
    bool checkPx(void);
  public:
    // Description:
    // Standard methods for instantiation, obtaining type and printing instance values.
    static vtkArcSource *New();
    void PrintSelf(ostream& os, vtkIndent indent);

    // Description:
    // Set/Get the initAng of the polyline. By default, the radius is set to 0.5.
    vtkSetMacro(InitAng,double);
    vtkGetMacro(InitAng,double);

    // Description:
    // Set/Get the finalAng of the polyline. By default, the radius is set to 0.5.
    vtkSetMacro(FinalAng,double);
    vtkGetMacro(FinalAng,double);

    void SetPx(double v[3]);
    void SetPx(const double &v0,const double &v1,const double &v2);
  protected:
    vtkArcSource();
    ~vtkArcSource() {}

    void SearchPlaneVector(const double n[3]);
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  private:
    vtkArcSource(const vtkArcSource&);  // Not implemented.
    void operator=(const vtkArcSource&);  // Not implemented.
  };

#endif
