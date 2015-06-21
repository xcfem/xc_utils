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
//EntradaComandos.h

#ifndef ENTRADACOMANDOS_HXX
#define ENTRADACOMANDOS_HXX

#include <iostream>
#include <stack>

//! @ingroup BASE
//
//! @brief Pila de archivos para entrada de comandos
class EntradaComandos
  {
  private:
    //Entrada de datos.
    std::istream *input_file; //!< Archivo del que se leen comandos.
    typedef std::stack<std::istream *> pila_streams_entrada;
    typedef std::stack<std::string> pila_archivos_entrada; //! Pila de nombres de archivo.
    pila_streams_entrada streams_entrada; //!< Pila de archivos de entrada.
    pila_archivos_entrada archivos_entrada; //!< Pila de nombres de archivo.

    //Gestión archivos entrada.
    friend class EntCmd;
    inline void SetArchivoEntradaActual(const std::string &archivo)
      { archivos_entrada.push(archivo); }
    inline void PopArchivoEntradaActual(void)
      { archivos_entrada.pop(); }
    void NuevoArchivoEntrada(const std::string &archivo);
    void CierraArchivoEntrada(void);
    void NuevoStringEntrada(const std::string &input,const std::string &nmb= "str");
    void CierraStringEntrada(void);

    friend class CmdStatus;
    std::string get_comando(void); //Sólo debe llamarla el metodo nuevo_comando de CmdStatus.
    std::string get_linea(void); //Sólo debe llamarla el metodo LeeCmd de EntCmd.

  public:
    EntradaComandos(std::istream *input=&std::cin,const std::string &str="console input");
    ~EntradaComandos(void);

    bool Ok(void) const;
    inline char peek(void) const
      { return input_file->peek(); }
    inline char GetChar(void) const
      { return input_file->get(); }
    inline const std::string &GetArchivoEntradaActual(void) const
      { return archivos_entrada.top(); }
    std::string getPosicionLecturaActual(void) const;
    size_t cuenta_lineas(void) const;
    std::string get_argumento(void) const;
    std::string get_bloque_comillas(bool &error) const;
    std::string get_bloque_parentesis(bool &error) const;
    std::string get_bloque_llaves(bool &error,const bool &ignora_esp= true) const;
    inline size_t get_size_streams_entrada(void) const
      { return streams_entrada.size(); }
    inline std::string nombre_archivo(void)
      { return get_argumento(); }
    void procesa_comentario(bool &error);
  };

#endif
