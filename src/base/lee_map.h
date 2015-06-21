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
//lee_map.h

#ifndef LEE_MAP_HXX
#define LEE_MAP_HXX

#include "lee_cmd.h"
#include "CmdStatus.h"
#include "../nucleo/EntCmd.h"
#include <cassert>

//! @ingroup BASE
//
//! @brief Mapa de objetos.
template <class MAP>
class LeeMap: public EntCmd
  {
  public:
    typedef typename MAP::key_type key_type;
    typedef typename MAP::mapped_type mapped_type;
    typedef typename MAP::value_type value_type;

  private:
    MAP *mapa;
    std::string cmd_clave; //Comando que se emplea para la clave.
    std::string cmd_valor; //Comando que se emplea para el valor.
    key_type k;
    mapped_type v;
    bool leida_clave;
  protected:
    bool procesa_comando(CmdStatus &status)
      {
        const std::string cmd= deref_cmd(status.Cmd());
        if(verborrea>2)
          std::clog << "LeeMap; procesando comando: " << cmd << std::endl;
        if(cmd== cmd_clave)
	  {
            lee_cmd(k,status);
            leida_clave= true;
            return true;
          }
        else if(cmd== cmd_valor)
	  {
            lee_cmd(v,status);
            if(!leida_clave)
              {
		std::cerr << "LeeMap::procesa_comando: Se leyó el valor antes que la clave." << std::endl;
              }
            (*mapa)[k]= v;
            leida_clave= false;
            return true;
          }
        else
	  return EntCmd::procesa_comando(status);
      }
  public:
    LeeMap(MAP *m,const std::string &cc="clave",const std::string &cv="valor")
      : mapa(m), cmd_clave(cc), cmd_valor(cv), leida_clave(false) 
      { assert(mapa!=NULL); }
  };

template <class MAP>
void lee_map(MAP &m,CmdStatus &s,const std::string &cc="clave",const std::string &cv="valor")
  {
    LeeMap<MAP> e(&m,cc,cv);
    e.LeeCmd(s);
  }


#endif
