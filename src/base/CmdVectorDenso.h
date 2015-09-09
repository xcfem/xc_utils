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
//CmdVectorDenso.h

#ifndef CMD_VECTOR_DENSO_H
#define CMD_VECTOR_DENSO_H

#include "CmdVectorBase.h"
#include "xc_basic/src/matrices/m_double.h"
#include "xc_basic/src/matrices/m_sizet.h"

//! @ingroup BASE
//
//!  \brief Vector denso que se lee desde archivo.
//!  
class CmdVectorDenso: public m_double, public CmdVectorBase
  {
  protected:
    static int get_componente(const std::string &str);
    virtual bool procesa_comando(CmdStatus &status);
  public:
    //! @brief Constructor por defecto.
    CmdVectorDenso(const size_t &fls=1,const double &d=0.0)
      : m_double(fls,1,d), CmdVectorBase() {}
    //! @brief Constructor.
      CmdVectorDenso(const m_double &m): m_double(m), CmdVectorBase() {}
    //! @brief Devuelve el elemento cuya fila se pasa como parámetro.
    virtual inline double &at(const size_t &f)
      { return m_double::at(f); }
    //! @brief Devuelve el elemento cuya fila se pasa como parámetro.
    virtual inline const double &at(const size_t &f) const
      { return m_double::at(f); }
    //! @brief Chequea el índice que se le pasa como parámetro.
    inline bool CheckIndice0(const size_t &i) const
      { return m_double::CheckIndices(i+1,1); }
    //! @brief Devuelve el elemento cuya fila se pasa como parámetro.
    inline virtual double &operator()(const size_t &f)
      { return m_double::operator()(f,1); }
    //! @brief Devuelve el elemento cuya fila se pasa como parámetro.
    inline virtual const double &operator()(const size_t &f) const
      { return m_double::operator()(f,1); }
    CmdVectorDenso operator()(const m_sizet &indices) const;
    //! Coloca el vector que se pasa como parámetro, sobre éste,
    //! comenzando en la fila f1.
    inline void PutSubVector(int f1, const CmdVectorDenso &v)
      { m_double::PutCaja(f1,1,v); }
    //! Devuelve el vector formado por los elementos de éste
    //! comprendidos entre las filas f1 y f2.
    inline CmdVectorDenso GetSubVector(int f1, int f2) const
      { return m_double::GetCaja(f1,1,f2,1); }
    //! @brief Suma sobre sí mismo.
    inline CmdVectorDenso &operator+=(const CmdVectorDenso &v)
      {
        m_double::operator+=(v);
        return *this;
      }
    //! @brief Devuelve la suma de los vectores.
    inline friend CmdVectorDenso operator+(const CmdVectorDenso &v1, const CmdVectorDenso &v2)
      {
        CmdVectorDenso retval(v1);
        retval+=v2;
        return retval;
      }
    friend void set_comp_vector(CmdVectorDenso &vector,const std::string &cmd,CmdStatus &status);
    //! @brief Imprime el vector.
    inline virtual void Print(std::ostream &os)
      { os << (const m_double &)*this; }
    any_const_ptr GetProp(const std::string &) const;
    //! @brief Destructor.
    virtual ~CmdVectorDenso(void) {}
  };

CmdVectorDenso operator*(const double &d,const CmdVectorDenso &v);
CmdVectorDenso operator*(const CmdVectorDenso &v,const double &d);

#endif
