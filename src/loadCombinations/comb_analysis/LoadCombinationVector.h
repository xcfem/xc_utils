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
//LoadCombinationVector.hxx
//Almacena las sumas correspondientes a cada una de las variaciones
//de una familia de acciones.

#ifndef LOADCOMBINATIONVECTOR_HXX
#define LOADCOMBINATIONVECTOR_HXX

#include "xc_utils/src/loadCombinations/actions/Accion.h"
#include "xc_basic/src/matrices/m_double.h"

namespace cmb_acc{
//! @ingroup CMBACC
//
//! @brief Cada elemento del vector es una combinación de acciones.
class LoadCombinationVector: public std::vector<Accion>, public EntCmd
  {
  private:
    bool Existe(const Accion &f) const;
    bool Nula(const double &tol) const;
    size_t CuentaNulas(const double &tol) const;
    size_t CuentaDistintas(const LoadCombinationVector &s2) const;
    const LoadCombinationVector &GetDistintas(const LoadCombinationVector &s2) const;
  protected:
    virtual bool procesa_comando(CmdStatus &status);
  public:
    //! @brief Constructor.
    LoadCombinationVector(const size_t &sz= 0)
      : std::vector<Accion>(sz), EntCmd() {}
    static LoadCombinationVector ProdCartesiano(const LoadCombinationVector &f1,const LoadCombinationVector &f2,const double &tol);
    static LoadCombinationVector Concat(const LoadCombinationVector &f1,const LoadCombinationVector &f2,const double &tol);
    void Numera(const std::string &prefijo= "H");
    const LoadCombinationVector &GetDistintas(void) const;
    const LoadCombinationVector &GetNoNulas(const double &tol) const;
    m_double getCoeficientes(const std::vector<std::string> &) const;
    void Print(std::ostream &os) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

std::ostream &operator<<(std::ostream &os,const LoadCombinationVector &vc);

} //fin namespace nmb_acc.

#endif
