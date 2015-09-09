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
//RelAcciones.hxx

#ifndef RELACCIONES_H
#define RELACCIONES_H

#include "xc_utils/src/nucleo/EntCmd.h"

//! \namespace<cmb_acc>
//! Rutinas para generar combinaciones de acciones.
namespace cmb_acc{

class VectorCombinaciones;

//! @ingroup CMBACC
//
//! @brief Relaciones de una acción con el resto.
class RelAcciones: public EntCmd
  {
  public:
    typedef std::deque<std::string> dq_string;
    typedef dq_string::iterator iterator;
    typedef dq_string::const_iterator const_iterator;

    static std::string limpia(const std::string &str);
    static std::deque<std::string> get_sumandos_combinacion(const std::string &str);
    static std::deque<std::string> get_nmb_acciones_combinacion(const std::string &str);
  private:
    dq_string incompatibles; //!< Expresiones regulares verdaderas para acciones incompatibles con ésta.
    dq_string maestras; //!< Expresiones regulares verdaderas para acciones de las que ésta es esclava.
    bool nodet; //!< Verdadero si la acción no puede ser determinante.
    bool contiene_incomp; //!< Verdadero si la combinación contiene acciones incompatibles.

    std::string nombres(const dq_string &) const;
    void concat_incompatibles(const dq_string &);
    void concat_maestras(const dq_string &);
    bool match(const std::string &,const dq_string &) const;
    bool match_any(const dq_string &,const dq_string &) const;
    bool match_all(const dq_string &,const dq_string &) const;

  protected:
    virtual bool procesa_comando(CmdStatus &status);

  public:
    RelAcciones(void);

    //! @brief Agrega a la lista de incompatibles la expresión regular que se pasa como parámetro.
    inline void AgregaIncompatible(const std::string &str)
      { incompatibles.push_back(str); }
    //! @brief Agrega a la lista de maestras la expresión regular que se pasa como parámetro.
    inline void AgregaMaestra(const std::string &str)
      { maestras.push_back(str); }
    inline bool NoDeterminante(void) const
      { return nodet; }
    void setNoDeterminante(const bool &b)
      { nodet= b; }

    bool matchIncompatibles(const dq_string &) const;
    bool incompatible(const std::string &) const;

    bool esclavaDe(const std::string &) const;
    bool esEsclava(void) const
      { return !maestras.empty(); }
    bool tieneHuerfanas(void) const
      { return !maestras.empty(); }
    void updateMaestras(const std::string &nmb);

    inline void setContieneIncomp(bool b)
      { contiene_incomp= b; }
    //! @brief Devuelve verdadero si esta combinación contiene acciones incompatibles entre sí.
    inline bool contieneIncomp(void) const
      { return contiene_incomp; }

    void concat(const RelAcciones &otra);

    std::string nombresIncompatibles(void) const;
    std::string nombresMaestras(void) const;
    void Print(std::ostream &os) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

std::ostream &operator<<(std::ostream &os,const RelAcciones &acc);

const VectorCombinaciones &getCompatibles(const VectorCombinaciones &);
const VectorCombinaciones &filtraCombsEsclavasHuerfanas(const VectorCombinaciones &);

} //fin namespace nmb_acc.

#endif
