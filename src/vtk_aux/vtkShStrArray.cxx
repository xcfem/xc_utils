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
//vtkShStrArray.cxx

#include "vtkShStrArray.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkShStrArray, "$Revision: 0.1 $")
vtkStandardNewMacro(vtkShStrArray)

vtkShStrArray::str_dbl::str_dbl(const double &dd)
  :d(dd) {}

vtkShStrArray::str_dbl::str_dbl(const std::string &src)
  : d(0.0)
  {
    const size_t sz= std::min(src.length(),bytes_str-1);
    size_t i= 0;
    for(;i<sz;i++)
      c[i]= src[i];
    c[i]= '\0';
  }

vtkShStrArray::str_dbl::str_dbl(const char &car)
  : d(0.0)
  {
    c[0]= car;
    c[1]= '\0';
  }

std::string vtkShStrArray::str_dbl::get_string(void) const
  { return std::string(c); }

//----------------------------------------------------------------------------
vtkShStrArray::vtkShStrArray(vtkIdType numComp)
  : vtkDoubleArray(numComp)
  {}

//----------------------------------------------------------------------------
vtkShStrArray::~vtkShStrArray(void)
  {}


std::string vtkShStrArray::dbl_to_str(const double &d)
  {
    str_dbl tmp(d);
    return tmp.get_string();
  }

// Description:
// Get the data at a particular index.
std::string vtkShStrArray::GetValue(vtkIdType id)
  { return dbl_to_str(vtkDoubleArray::GetValue(id)); }

  // Description:
  // Set the data at a particular index. Does not do range checking. Make sure
  // you use the method SetNumberOfValues() before inserting data.
void vtkShStrArray::SetValue(vtkIdType id, const std::string &value)
  {
    str_dbl tmp(value);
    vtkDoubleArray::SetValue(id, tmp.d);
  }

// Description:
// Insert data at a specified position in the array.
void vtkShStrArray::InsertValue(vtkIdType id,const std::string &f)
  {
    str_dbl tmp(f);
    vtkDoubleArray::InsertValue(id, tmp.d);
  }

// Description:
// Insert data at the end of the array. Return its location in the array.
vtkIdType vtkShStrArray::InsertNextValue(const std::string &f)
  {
    str_dbl tmp(f);
    return vtkDoubleArray::InsertNextValue(tmp.d);
  }

//----------------------------------------------------------------------------
void vtkShStrArray::PrintSelf(ostream& os, vtkIndent indent)
  { vtkDoubleArray::PrintSelf(os,indent); }
