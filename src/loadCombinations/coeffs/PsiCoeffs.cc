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
//PsiCoeffs.cxx

#include "PsiCoeffs.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

//! @brief Lee el objeto desde archivo.
bool cmb_acc::PsiCoeffs::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(PsiCoeffs) Procesando comando: " << cmd << std::endl;
    if(cmd == "psi_0")
      {
        psi_0= status.GetFloat();
        return true;
      }
    else if(cmd == "psi_1")
      {
        psi_1= status.GetFloat();
        return true;
      }
    else if(cmd == "psi_2")
      {
        psi_2= status.GetFloat();
        return true;
      }
    else if(cmd == "vectorPsi")
      {
	std::vector<double> tmp= convert_to_vector_double(interpretaVectorAny(status.GetString()));
        if(tmp.size()>2)
          {
            psi_0= tmp[0];
            psi_1= tmp[1];
            psi_2= tmp[2];
          }
        else
	  std::cerr << "(PsiCoeffs) Procesando comando: " << cmd
                    << " se esperaba un vector de dimensión 3.\n";
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve el coeficiente cuyo índice se pasa como parámetro.
const double &cmb_acc::PsiCoeffs::getPsi(short int r) const
  {
    switch(r)
      {
      case(0):
        return psi_0;
      case(1):
        return psi_1;
      case(2):
        return psi_2;
      default:
	std::cerr << "cmb_acc::PsiCoeffs::getPsi índice: " << r << " fuera de rango (0..2)." << std::endl;
        return psi_0;
      }
  }

//! @brief Devuelve la propiedad del objeto cuyo código se pasa
//! como parámetro.
any_const_ptr cmb_acc::PsiCoeffs::GetProp(const std::string &cod) const
  {
    if(cod == "psi_0")
      return any_const_ptr(psi_0);
    else if(cod == "psi_1")
      return any_const_ptr(psi_1);
    else if(cod == "psi_2")
      return any_const_ptr(psi_2);
    else
      return EntCmd::GetProp(cod);
  }
