//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//PStream.h

#ifndef PSTREAM_H
#define PSTREAM_H

#include <iostream.h>
#include <map.h>
#include <String.h>

template <class T>
class PStream : public _IO_istream_withassign
  {
  public:
    typedef map<String,T *,less<String> > mapa_claves;
  private:
    mapa_claves mapa;
  public:
    PStream(void) : _IO_istream_withassign() {}
    PStream &operator=(istream &is)
      {
	_IO_istream_withassign::operator=(is);
        return *this;
      }
    void Registra(const String &str,const T *p)
      { mapa[str]= p->clon(); }
    T *ClaseDato(void)
      {
        String str;
	(_IO_istream_withassign &)(*this) >> str;
        mapa_claves::const_iterator i= mapa.find(str);
        if(i == mapa.end())
          {
            cerr << "La clase " << str << " no est'a registrada." << endl;
            return NULL;
          }
        return (*i).second;
      }
    void Save(ostream &os) const
      {
        mapa_claves::const_iterator i;
        for(i= mapa.begin();i!=mapa.end();i++)
          os << ' ' << (*i).first;
      }
  };

#endif

