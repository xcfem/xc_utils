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
//Ref.h

#ifndef REF_H
#define REF_H

#include "../ProtoGeom.h"

//! @ingroup GEOM
//
//! @defgroup SisRef Sistemas de referencia.
//
//! @ingroup SisRef
//! 
//! @brief Clase base para los sistemas de referencia.
//!  
template<class SC>
class Ref : public ProtoGeom
  {
  public:
    typedef typename SC::VGlobal VGlobal; //!< Dimensión del vector global.
    typedef typename SC::DGlobal DGlobal; //!< Dimensión de la dirección global.
    typedef typename SC::PGlobal PGlobal; //!< Dimensión dle punto global.
    typedef typename SC::VLocal VLocal; //!< Dimensión del vector local.
    typedef typename SC::PLocal PLocal; //!< Dimensión del punto local.
    
  protected:
    PGlobal org; //!< Origen del sistema de coordenadas.
    SC trf;  //!< Ejes del sistem de coordenadas transformacion local --> global.

  public:
    Ref(void): org(), trf() {}
    Ref(const Ref &otro)
      : org(otro.org), trf(otro.trf) {}
    Ref(const PGlobal &o, const SC &sc=SC())
      : org(o), trf(sc) {}
    Ref(const PGlobal &o,const VGlobal &vX)
      : org(o), trf(vX) {}
    Ref(const PGlobal &o,const DGlobal &dirX)
      : org(o), trf(dirX.GetVector()) {}
    Ref(const PGlobal &o,const PGlobal &p)
      : org(o), trf(o,p) {}
    Ref &operator =(const Ref &otro)
      {
        trf= otro.trf;
        org= otro.org;
        return *this;
      }
    PGlobal &Org(void)
      { return org; }
    const PGlobal &Org(void) const
      { return org; }
    void PutOrg(const PGlobal &p)
      { org= p; }
    SC &Trf(void)
      { return trf; }
    const SC &Trf(void) const
      { return trf; }
    VGlobal GetVDirEje(const size_t &i) const
      { return trf.GetVDirEje(i); }
    PGlobal GetPosGlobal(const PLocal &p) const;
    VGlobal GetCooGlobales(const VLocal &v) const;
    PLocal GetPosLocal(const PGlobal &p) const;
    VLocal GetCooLocales(const VGlobal &v) const;
    friend bool operator ==(const Ref<SC> &a,const Ref<SC> &b)
      {
        if (a.org != b.org) return false;
        if (a.trf != b.trf) return false;
        return true;
      }
    friend std::ostream &operator<<(std::ostream &os,const Ref<SC> &r)
      {
        os << "origen= " << r.org << " transformación= " << r.trf;
        return os;
      }
    virtual ~Ref(void)
      {}
  };

//! @brief Devuelve la posicion del punto p expresado en locales expresada en coordenadas globales.
template<class SC>
typename Ref<SC>::PGlobal Ref<SC>::GetPosGlobal(const PLocal &p) const
  {
    PGlobal retval= org + GetCooGlobales(p-PLocal());
    return retval;
  }

//! @brief Devuelve el vector v expresado en locales expresado en coordenadas globales.
template<class SC>
typename Ref<SC>::VGlobal Ref<SC>::GetCooGlobales(const VLocal &v) const
  { return trf.GetCooGlobales(v); }

//! @brief Devuelve la posicion del punto p expresado en globales expresada en coordenadas locales.
template<class SC>
typename Ref<SC>::PLocal Ref<SC>::GetPosLocal(const PGlobal &p) const
  {
    VLocal v= GetCooLocales(p-org);
    return PLocal(PLocal()+v);
  }

//! @brief Devuelve el vector v expresado en globales expresado en coordenadas locales.
template<class SC>
typename Ref<SC>::VLocal Ref<SC>::GetCooLocales(const VGlobal &v) const
  { return trf.GetCooLocales(v); }

#endif






