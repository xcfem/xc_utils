//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
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
//LeadingActionInfo.hxx
//Information about the leading action.

#ifndef LEADINGACTIONINFO_H
#define LEADINGACTIONINFO_H

#include "xc_utils/src/nucleo/EntCmd.h"

namespace cmb_acc{
class Action;

//! @ingroup CMBACC
//
//! @brief Information about the leading action.
class LeadingActionInfo: public EntCmd
  {
  private:
    short int index; //!< Index of leading variable action (-1 if none).

// representative_value_index= -1 -> characteristic value.
// representative_value_index= 0 -> combination value.
// representative_value_index= 1 -> frequent value.
// representative_value_index= 2 -> quasi-permanent value.

    short int leading_representative_value_index; //!< Index of the representative value for the leading action.
    short int general_representative_value_index; //!< Index of the representative value for the non leading actions.
  public:
    //! @brief Default constructor.
    LeadingActionInfo(const short int &i= -1, const short int &lrv= -1, const short int &grv= 0);

    //! @brief Return true if there is a leading action.
    inline bool leadingActionExists(void) const
      { return index>-1; }
    //! @brief Return true if the argument is the leading action index.
    inline bool isLeadingActionIndex(const short int &j) const
      { return (index==j); }
    inline short int getLeadingActionIndex(void) const
      { return index; }
    inline short int getLeadingRepresentativeValueIndex(void) const
      { return leading_representative_value_index; }
    inline short int getGeneralRepresentativeValueIndex(void) const
      { return general_representative_value_index; }
    void Print(std::ostream &os) const;
  };

 inline std::ostream &operator<<(std::ostream &os, const LeadingActionInfo &lai)
  {
    lai.Print(os);
    return os;
  }

} //fin namespace nmb_acc.

#endif
