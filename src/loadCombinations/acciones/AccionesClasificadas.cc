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
//AccionesClasificadas.cxx

#include "AccionesClasificadas.h"
#include "xc_utils/src/loadCombinations/combinaciones/VectorCombinaciones.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! \fn cmb_acc::AccionesClasificadas::AccionesClasificadas(void)
//! @brief Constructor por defecto.
cmb_acc::AccionesClasificadas::AccionesClasificadas(const MapCoefsPsi &coefs)
  : G("Permanentes",GammaF(GammaFELU(1.0,1.5,1.0,1.0),GammaFELS(1.0,1.0))), //Coeficientes de ponderación por defecto 
                                                                            //para acciones permanentes.
    G_aster("Permanentes val. no cte."), 
    Q("Variables",GammaF(GammaFELU(0.0,1.6,0.0,1.0),GammaFELS(0.0,1.0))),
    A("Accidentales",GammaF(GammaFELU(0.0,0.0,1.0,1.0))),
    AS("Sísmicas",GammaF(GammaFELU(0.0,0.0,1.0,1.0))),
    coefs_psi(coefs)
  {
    G.set_owner(this);
    G_aster.set_owner(this);
    Q.set_owner(this);
    A.set_owner(this);
    AS.set_owner(this);
  }

//! @brief Lanza la ejecución del bloque de código que se pasa
//! como parámetro para cada una de las acciones del contenedor.
void cmb_acc::AccionesClasificadas::for_each_accion(CmdStatus &status,const std::string &bloque)
  {
    G.set_owner(this);
    G.for_each_accion(status,bloque);
    G_aster.set_owner(this);
    G_aster.for_each_accion(status,bloque);
    Q.set_owner(this);
    Q.for_each_accion(status,bloque);
    A.set_owner(this);
    A.for_each_accion(status,bloque);
    AS.set_owner(this);
    AS.for_each_accion(status,bloque);
  }

//! \fn cmb_acc::AccionesClasificadas::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::AccionesClasificadas::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(AccionesClasificadas) Procesando comando: " << cmd << std::endl;
    if(cmd == "permanentes")
      {
        G.set_owner(this);
        G.LeeCmd(status);
        return true;
      }
    else if(cmd == "permanentes_nc")
      {
        G_aster.set_owner(this);
        G_aster.LeeCmd(status);
        return true;
      }
    else if(cmd == "variables")
      {
        Q.set_owner(this);
        Q.LeeCmd(status);
        return true;
      }
    else if(cmd == "accidentales")
      {
        A.set_owner(this);
        A.LeeCmd(status);
        return true;
      }
    else if(cmd == "sismicas")
      {
        AS.set_owner(this);
        AS.LeeCmd(status);
        return true;
      }
    else if(cmd == "for_each")
      {
        const std::string bloque= status.GetBloque();
        G.set_owner(this);
        G.EjecutaBloque(status,bloque,G.GetNombre()+":for_each");
        G_aster.set_owner(this);
        G_aster.EjecutaBloque(status,bloque,G_aster.GetNombre()+":for_each");
        Q.set_owner(this);
        Q.EjecutaBloque(status,bloque,Q.GetNombre()+":for_each");
        A.set_owner(this);
        A.EjecutaBloque(status,bloque,A.GetNombre()+":for_each");
        AS.set_owner(this);
        AS.EjecutaBloque(status,bloque,AS.GetNombre()+":for_each");
        return true;
      }
    else if(cmd == "for_each_accion")
      {
        for_each_accion(status,status.GetBloque());
        return true;
      }
    else if(cmd == "coefs_psi")
      {
        coefs_psi.LeeCmd(status);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Inserta la acción en la familia que se indica en la cadena de caracteres.
cmb_acc::VRAccion &cmb_acc::AccionesClasificadas::inserta(const std::string &familia,const Accion &acc,const std::string &nmb_coefs_psi,const std::string &subfamilia)
  {
    if(familia=="permanentes")
      return G.inserta(acc,nmb_coefs_psi);
    else if(familia=="permanentes_nc")
      return G_aster.inserta(subfamilia,acc,nmb_coefs_psi);
    else if(familia=="variables")
      return Q.inserta(acc,nmb_coefs_psi);
    else if(familia=="accidentales")
      return A.inserta(acc,nmb_coefs_psi);
    else if(familia=="sismicas")
      return AS.inserta(acc,nmb_coefs_psi);
    else
      {
        std::cerr << "AccionesClasificadas::inserta; load family: '"
                  << familia << "' not found. Added to variable loads.\n";
        return Q.inserta(acc,nmb_coefs_psi);
      }
  }

//! @brief Devuelve el conjunto de acciones permanentes.
const cmb_acc::FamiliaAcciones &cmb_acc::AccionesClasificadas::getAccionesPermanentes(void) const
  { return G; }

//! @brief Asigna el conjunto de acciones permanentes.
void cmb_acc::AccionesClasificadas::setAccionesPermanentes(const FamiliaAcciones &g)
  { G= g; }

//! @brief Devuelve el conjunto de acciones permanentes de valor no constante.
const cmb_acc::MapFamiliasAcc &cmb_acc::AccionesClasificadas::getAccionesPermanentesNC(void) const
  { return G_aster; }

//! @brief Asigna el conjunto de acciones permanentes de valor no constante.
void cmb_acc::AccionesClasificadas::setAccionesPermanentesNC(const MapFamiliasAcc &mfa)
  { G_aster= mfa; }

//! @brief Devuelve el conjunto de acciones variables.
const cmb_acc::FamiliaAcciones &cmb_acc::AccionesClasificadas::getAccionesVariables(void) const
  { return Q; }

//! @brief Devuelve el conjunto de acciones variables.
void cmb_acc::AccionesClasificadas::setAccionesVariables(const FamiliaAcciones &fa)
  { Q= fa; }

//! @brief Devuelve el conjunto de acciones accidentales.
const cmb_acc::FamiliaAcciones &cmb_acc::AccionesClasificadas::getAccionesAccidentales(void) const
  { return A; }

//! @brief Asigna el conjunto de acciones accidentales.
void cmb_acc::AccionesClasificadas::setAccionesAccidentales(const FamiliaAcciones &fa)
  { A= fa; }

//! @brief Devuelve el conjunto de acciones sísmicas.
const cmb_acc::FamiliaAcciones &cmb_acc::AccionesClasificadas::getAccionesSismicas(void) const
  { return AS; }

//! @brief Asigna el conjunto de acciones sísmicas.
void cmb_acc::AccionesClasificadas::setAccionesSismicas(const FamiliaAcciones &fa)
  { AS= fa; }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesG(const bool &elu,const bool &sit_accidental) const
//! @brief Devuelve las combinaciones que se forman con las acciones permanentes.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesG(const bool &elu,const bool &sit_accidental) const
  { return G.GetCombinaciones(elu,sit_accidental,-1); } //Las permanentes siempre con valor característico.

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesG_aster(const bool &elu,const bool &sit_accidental) const
//! @brief Devuelve las combinaciones que se forman con las acciones permanentes de valor no constante.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesG_aster(const bool &elu,const bool &sit_accidental) const
  { return G_aster.GetCombinaciones(elu,sit_accidental); } 

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesQ(const bool &elu,const bool &sit_accidental,short int r,int d,short int rr) const
//! @brief Devuelve las combinaciones que se forman con las acciones variables.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
//! @param r: Valor representativo a emplear para el caso general.
//! - r= -1 -> valor característico.
//! - r= 0 -> valor de combinación.
//! - r= 1 -> valor frecuente.
//! - r= 2 -> valor cuasipermanente.
//! @param d: Índice de la acción determinante (si no hay acción determinante d=-1).
//! @param rr: Valor representativo a emplear para la acción determinante.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesQ(const bool &elu,const bool &sit_accidental,short int r,int d,short int rr) const
  { return Q.GetCombinaciones(elu,sit_accidental,r,d,rr); }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesA(short int r,int d,short int rr) const
//! @brief Devuelve las combinaciones que se forman con las acciones accidentales.
//! @param r: Valor representativo a emplear para el caso general.
//! - r= -1 -> valor característico.
//! - r= 0 -> valor de combinación.
//! - r= 1 -> valor frecuente.
//! - r= 2 -> valor cuasipermanente.
//! @param d: Índice de la acción determinante (si no hay acción determinante d=-1).
//! @param rr: Valor representativo a emplear para la acción determinante.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesA(short int r,int d,short int rr) const
  { return A.GetCombinaciones(true,true,r,d,rr); }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesAS(short int r,int d,short int rr) const
//! @brief Devuelve las combinaciones que se forman con las acciones sísmicas.
//! @param r: Valor representativo a emplear para el caso general.
//! - r= -1 -> valor característico.
//! - r= 0 -> valor de combinación.
//! - r= 1 -> valor frecuente.
//! - r= 2 -> valor cuasipermanente.
//! @param d: Índice de la acción determinante (si no hay acción determinante d=-1).
//! @param rr: Valor representativo a emplear para la acción determinante.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombinacionesAS(short int r,int d,short int rr) const
  { return AS.GetCombinaciones(true,true,r,d,rr); }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetPermanentes(const bool &elu,const bool &sit_accidental) const
//! @brief Devuelve las combinaciones correspondientes a acciones permanentes y permanentes de valor no constante.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetPermanentes(const bool &elu,const bool &sit_accidental) const
  {
    VectorCombinaciones retval;
    if(!G.Vacia()) //Hay acciones permanentes.
      {
        retval= GetCombinacionesG(elu,sit_accidental);
      }
    if(!G_aster.Vacia()) //Hay acciones permanentes de valor no constante.
      {
        const VectorCombinaciones SG_aster= GetCombinacionesG_aster(elu,sit_accidental);
        retval= VectorCombinaciones::ProdCartesiano(retval,SG_aster,Accion::zero);
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles
                                                                   // o esclavas huérfanas.
    return retval;
  }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetVariables(const VectorCombinaciones &permanentes,const bool &elu,const bool &sit_accidental,const short int &v) const
//! @brief Devuelve las combinaciones que corresponden a acciones permanentes (incluso no constantes) y variables.
//! @param permanentes: Combinaciones de las acciones permanentes obtenidas mediante cmb_acc::AccionesClasificadas::GetPermanentes.
//! @param elu: Verdadero si las combinaciones corresponden a estados límite últimos.
//! @param sit_accidental: Verdadero si las combinaciones corresponden a situación accidental.
//! @param v: Valor representativo a considerar para la acción determinante.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetVariables(const VectorCombinaciones &permanentes,const bool &elu,const bool &sit_accidental,const short int &v) const
  {
    VectorCombinaciones retval; //Inicializa con acciones permanentes.
    if(!Q.Vacia()) //Hay acciones variables.
      {
        const size_t nq= Q.getNumAcciones();
        VectorCombinaciones SQ;
        for(size_t i=0;i<nq;i++) //i: Índice de la acción determinante.
          {
            if(verborrea>1) std::clog << std::endl << "    Obteniendo combinaciones de acciones variables con acción determinante: " << i << " ...";
            VectorCombinaciones temp= GetCombinacionesQ(elu,sit_accidental,v,i,v-1); //Acción determinante con valor v
                                                                                     //resto con valor v-1.
            SQ= VectorCombinaciones::Concat(SQ,temp,Accion::zero);
            if(verborrea>1) std::clog << "hecho." << std::endl;
          }
        retval= VectorCombinaciones::ProdCartesiano(permanentes,SQ,Accion::zero);
        if(elu) retval= VectorCombinaciones::Concat(permanentes,retval,Accion::zero); //Si ELU consideramos también las cargas permanentes SOLAS.
      }
    else //No hay acciones variables.
      retval= permanentes;
    retval= getCompatibles(retval); //Filtramos las combinaciones que contienen acciones incompatibles
                                                                   // o esclavas huérfanas.
    return retval;
  }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetAccSis(const VectorCombinaciones &previas,const FamiliaAcciones &Acc) const
//! @brief Devuelve las combinaciones correspondientes en situaciones accidentales o sísmicas.
//! @param previas: Combinaciones de las acciones permanentes y variables obtenidas mediante cmb_acc::AccionesClasificadas::GetVariables.
//! @param Acc: Familia de acciones accidentales o sísmicas.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetAccSis(const VectorCombinaciones &previas,const FamiliaAcciones &Acc) const
  {
    VectorCombinaciones retval(previas);
    if(!Acc.Vacia()) //Existen acciones accidentales o sísmicas.
      {
        const size_t na= Acc.getNumAcciones();
        VectorCombinaciones SA;
        for(size_t i=0;i<na;i++) //i: Índice de la acción accidental o sísmica.
          {
            VectorCombinaciones temp= Acc.GetCombinaciones(true,true,0,i,-1); //Acción accidental o sísmica i con valor característico
                                                                              //resto con valor de combinación (QUE DEBE SER NULO).
            SA= VectorCombinaciones::Concat(SA,temp,Accion::zero);
          }
        retval= VectorCombinaciones::ProdCartesiano(retval,SA,Accion::zero);
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles.
    return retval;
  }



//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetPersistentesOTransit(void) const
//! @brief Devuelve las combinaciones correspondientes a estados límite últimos en situaciones persistentes o transitorias.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetPersistentesOTransit(void) const
  {
    if(verborrea>1) std::clog << "Obteniendo combinaciones de acciones para ELU en situaciones persistentes o transitorias..." << std::endl; 
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    VectorCombinaciones retval= GetPermanentes(true,false); //ELU, situación no accidental.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,true,false,0);//ELU, acción determinante con valor característico
                                              //resto con valor de combinación.
    if(verborrea>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::AccionesClasificadas::GetAccidentales(void) const
//! @brief Devuelve las combinaciones correspondientes a  estados límite últimos en situaciones accidentales.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetAccidentales(void) const
  {
    VectorCombinaciones retval;
    if(A.Vacia()) return retval; //No hay acciones accidentales.
    if(verborrea>1) std::clog << "Obteniendo combinaciones de acciones para ELU en situaciones accidentales..." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    retval= GetPermanentes(true,true); //ELU, situación accidental.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,true,true,2); //ELU, acción determinante con valor frecuente
                                              //resto con valor de cuasipermanente.
    if(verborrea>1) std::clog << "  hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones accidentales...";
    retval= GetAccSis(retval,A);
    if(verborrea>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    return retval;
  }


//! \fn cmb_acc::AccionesClasificadas::GetSismicas(void) const
//! @brief Devuelve las combinaciones correspondientes a  estados límite últimos en situaciones sísmicas.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetSismicas(void) const
  {
    VectorCombinaciones retval;
    if(AS.Vacia()) return retval; //No hay acciones sismicas.
    if(verborrea>1) std::clog << "Obteniendo combinaciones de acciones para ELU en situaciones sísmicas..." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    retval= GetPermanentes(true,true); //ELU, situación accidental.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    if(!Q.Vacia()) //Hay acciones variables.
      {
        VectorCombinaciones SQ= GetCombinacionesQ(true,true,2); //ELU, todas con valor cuasipermanente.
        retval= VectorCombinaciones::ProdCartesiano(retval,SQ,Accion::zero);
      }
    if(verborrea>1) std::clog << "  hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones sísmicas...";
    retval= GetAccSis(retval,AS);
    if(verborrea>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::AccionesClasificadas::GetCombELU(void) const
//! @brief Devuelve las combinaciones correspondientes a todas las situaciones de ESTADO LIMITE ÚLTIMO.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombELU(void) const
  {
    VectorCombinaciones retval= GetPersistentesOTransit(); //Situaciones persistentes o transitorias.
    VectorCombinaciones accidentales= GetAccidentales();
    retval= VectorCombinaciones::Concat(retval,accidentales,0.0);
    VectorCombinaciones sismicas= GetSismicas();
    retval= VectorCombinaciones::Concat(retval,sismicas,0.0);
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "  Calculadas " << retval.size() << " combinaciones ELU." << std::endl;
    retval.Numera("H-ELU-");
    return retval;
  }

//Estados límite de servicio.


//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetPocoFrecuentes(void) const
//! @brief Devuelve las combinaciones correspondientes a situaciones poco frecuentes en ESTADO LIMITE DE SERVICIO.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetPocoFrecuentes(void) const
  {
    if(verborrea>1) std::clog << "Obteniendo combinaciones de acciones para ELS en situaciones persistentes o transitorias..." << std::endl; 
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    VectorCombinaciones retval= GetPermanentes(false,false); //ELS, situación no accidental (obviamente).
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,0);//ELS, acción determinante con valor característico
                                               //resto con valor de combinación.
    if(verborrea>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetFrecuentes(void) const
//! @brief Devuelve las combinaciones correspondientes a situaciones persistentes o transitorias.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetFrecuentes(void) const
  {
    if(verborrea>1) std::clog << "Obteniendo combinaciones de acciones para ELS en situaciones persistentes o transitorias..." << std::endl; 
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    VectorCombinaciones retval= GetPermanentes(false,false); //ELS, situación no accidental (obviamente).
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,1);//ELS, acción determinante con valor frecuente
                                               //resto con valor de cuasipermanente. 
    if(verborrea>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCuasiPermanentes(void) const
//! @brief Devuelve las combinaciones correspondientes a situaciones persistentes o transitorias.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCuasiPermanentes(void) const
  {
    if(verborrea>1) std::clog << "Obteniendo combinaciones de acciones para ELS en situaciones persistentes o transitorias..." << std::endl; 
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones permanentes...";
    VectorCombinaciones retval= GetPermanentes(false,false); //ELS, situación no accidental.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "  Obteniendo combinaciones de acciones variables...";
    retval= GetVariables(retval,false,false,2);//ELS, todas con valor cuasipermanente.
    if(verborrea>1) std::clog << "  Filtrando combinaciones con acciones incompatibles...";
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    if(verborrea>1) std::clog << "hecho." << std::endl;
    return retval;
  }

//! \fn cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombELS(void) const
//! @brief Devuelve las combinaciones correspondientes a todas las situaciones de ESTADO LIMITE DE SERVICIO.
cmb_acc::VectorCombinaciones cmb_acc::AccionesClasificadas::GetCombELS(void) const
  {
    VectorCombinaciones retval= GetPocoFrecuentes(); //Combinaciones poco frecuentes.
    VectorCombinaciones frecuente= GetFrecuentes();
    retval= VectorCombinaciones::Concat(retval,frecuente,0.0);
    VectorCombinaciones cp= GetCuasiPermanentes();
    retval= VectorCombinaciones::Concat(retval,cp,0.0);
    retval= filtraCombsEsclavasHuerfanas(getCompatibles(retval)); //Filtramos las que contienen acciones incompatibles.
    if(verborrea>1) std::clog << "  Calculadas " << retval.size() << " combinaciones ELS." << std::endl;
    retval.Numera("H-ELS-");
    return retval;
  }

//! \fn any_const_ptr cmb_acc::AccionesClasificadas::GetProp(const std::string &cod) const
//! @brief Devuelve la propiedad del objeto cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::AccionesClasificadas::GetProp(const std::string &cod) const
  {
    if(cod == "permanentes")
      return any_const_ptr(&G);
    else if(cod == "permanentes_nc")
      return any_const_ptr(&G_aster);
    else if(cod == "variables")
      return any_const_ptr(&Q);
    else if(cod == "accidentales")
      return any_const_ptr(&A);
    else if(cod == "sismicas")
      return any_const_ptr(&AS);
    else
      return EntCmd::GetProp(cod);
  }
