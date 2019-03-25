//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.  
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
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
    typedef typename SC::VGlobal VGlobal; //!< Dimension of the global vector.
    typedef typename SC::DGlobal DGlobal; //!< Dimension of the global direction.
    typedef typename SC::PGlobal PGlobal; //!< Dimension of the global point.
    typedef typename SC::VLocal VLocal; //!< Dimension of the local vector.
    typedef typename SC::PLocal PLocal; //!< Dimension of the local point.
    
  protected:
    PGlobal org; //!< Origin of the coordinate system.
    SC trf;  //!< local --> global coordinate system axis transformation.

  public:
    Ref(void): org(), trf() {}
    Ref(const PGlobal &o, const SC &sc=SC())
      : org(o), trf(sc) {}
    Ref(const PGlobal &o,const VGlobal &vX)
      : org(o), trf(vX) {}
    Ref(const PGlobal &o,const DGlobal &dirX)
      : org(o), trf(dirX.GetVector()) {}
    Ref(const PGlobal &o,const PGlobal &p)
      : org(o), trf(o,p) {}
    PGlobal &Org(void)
      { return org; }
    const PGlobal &Org(void) const
      { return org; }
    void setOrg(const PGlobal &p)
      { org= p; }
    SC &Trf(void)
      { return trf; }
    const SC &Trf(void) const
      { return trf; }
    void setTrf(const SC &t)
      { trf= t; }
    VGlobal getAxisVDir(const size_t &i) const
      { return trf.getAxisVDir(i); }
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

//! @brief Return the position of the point p (expressed in local coordinates)
//! expresssed in global coordinates.
template<class SC>
typename Ref<SC>::PGlobal Ref<SC>::GetPosGlobal(const PLocal &p) const
  {
    PGlobal retval= org + GetCooGlobales(p-PLocal());
    return retval;
  }

//! @brief Return el vector v expresado en locales expresado en coordenadas globales.
template<class SC>
typename Ref<SC>::VGlobal Ref<SC>::GetCooGlobales(const VLocal &v) const
  { return trf.GetCooGlobales(v); }

//! @brief Return the position of the point p (expressed in global coordinates)
//! expresssed in local coordinates.
template<class SC>
typename Ref<SC>::PLocal Ref<SC>::GetPosLocal(const PGlobal &p) const
  {
    VLocal v= GetCooLocales(p-org);
    return PLocal(PLocal()+v);
  }

//! @brief Return el vector v expresado en globales expresado en coordenadas locales.
template<class SC>
typename Ref<SC>::VLocal Ref<SC>::GetCooLocales(const VGlobal &v) const
  { return trf.GetCooLocales(v); }

#endif






