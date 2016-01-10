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
//vtkShStrArray.h

#ifndef vtkShStrArray_h
#define vtkShStrArray_h

#include "vtkDoubleArray.h"

const size_t bytes_str= sizeof(double);

class VTK_COMMON_EXPORT vtkShStrArray : public vtkDoubleArray
  {
private:
  //ETX
  vtkShStrArray(const vtkShStrArray&) {}  // Not implemented.
  void operator=(const vtkShStrArray&) {}  // Not implemented.

  union str_dbl
    {
      char c[bytes_str];
      double d;
      str_dbl(const double &dd= 0.0);
      str_dbl(const std::string &);
      str_dbl(const char &);
      std::string get_string(void) const;
    };

  // Description:
  // Set the tuple value at the ith location in the array.
  void SetTupleValue(vtkIdType i, const double *) {} //No implementada.

  // Description:
  // Insert (memory allocation performed) the tuple into the ith location
  // in the array.
  void InsertTupleValue(vtkIdType i, const double* ) {} //No implementada.

  // Description:
  // This method lets the user specify data to be held by the array.  The
  // array argument is a pointer to the data.  size is the size of
  // the array supplied by the user.  Set save to 1 to keep the class
  // from deleting the array when it cleans up or reallocates memory.
  // The class uses the actual array provided; it does not copy the data
  // from the suppled array.
  void SetArray(double* array, vtkIdType size, int save)
    { vtkDoubleArray::SetArray(array, size, save); }

public:
  static vtkShStrArray *New();
  vtkTypeRevisionMacro(vtkShStrArray,vtkDoubleArray);

  static std::string dbl_to_str(const double &d);


  void PrintSelf(ostream& os, vtkIndent indent);



  // Description:
  // Get the data at a particular index.
  std::string GetValue(vtkIdType id);

  // Description:
  // Set the data at a particular index. Does not do range checking. Make sure
  // you use the method SetNumberOfValues() before inserting data.
  void SetValue(vtkIdType id, const std::string &value);

  // Description:
  // Insert data at a specified position in the array.
  void InsertValue(vtkIdType id,const std::string &);

  // Description:
  // Insert data at the end of the array. Return its location in the array.
  vtkIdType InsertNextValue(const std::string &);


protected:
  vtkShStrArray(vtkIdType numComp=1);
  ~vtkShStrArray(void);

};

#endif
