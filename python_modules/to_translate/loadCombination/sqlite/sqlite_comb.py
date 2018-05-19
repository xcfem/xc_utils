# -*- coding: utf-8 -*-
# Crea una tabla con la descomposición de las combinaciones.
def SQLTcreaTablaComb(nmbDBase,nmbTabla):
  {
    nmbAccs= ""
    \pond_acciones
      {
        \for_each_accion
          {nmbAccs= (nmbAccs + " float," + sqlValue(getNombre))}
        nmbAccs= "("+copiaDesde(",",nmbAccs)+" float)" # Le quitamos la primera coma.
      }
    SQLTcreaTabla(nmbDBase,nmbTabla,nmbAccs){}
  }

def SQLTinsertCombs(nmbDBase,nmbTabla):
  {
    sqlCmd= ""  
    \for_each
      {
        sqlCmd= "insert into "+nmbTabla+ " ("+getDescomp.sqlNames+")"+" values ("+getDescomp.sqlValues+")"
        \sqlite{\nmbDBase{\execute_sql{sqlCmd}}}
      }
  }

# Define una tabla de combinaciones del tipo que se pasa como parámetro
def SQLTtablaCombs(nmbDBase,nmbTabla,nmbCombinaciones,offset):
  cont= offset
  SQLTcreaTabla(nmbDBase,nmbTablaComb,"(idComb INT, descomp STRING)"){}
    \combinaciones
      {
        \nmbCombinaciones
          {
            sqlQuery= 
            \for_each
              {
                sqlQuery= "insert into " + nmbTabla + " values ("+ sqlValue(int(cont)) + "," + sqlValue(getNombreExpandido) +")"
                \sqlite{\nmbDBase{\execute_sql{sqlQuery}}}
                cont= cont+1
              }
          }
      }
    return cont
  }


# Define una tabla de combinaciones del tipo que se pasa como parámetro
def SQLTtablaCombsULS(nmbDBase,nmbTabla,offset):
  {
    
    cont= offset
    SQLTcreaTabla(nmbDBase,nmbTabla,"(idComb INT, descomp STRING)"){}
    \combinaciones
      {
        \comb_elu_persistentes
          {
            \for_each
              {
                \sqlite{\nmbDBase{\execute_sql{"insert into " + nmbTabla + " values ("+ sqlValue(int(cont)) + ", " + sqlValue(getNombreExpandido) +")"}}}
                cont= cont+1
              }
          }
        \comb_elu_accidentales
          {
            \for_each
              {
                \sqlite{\nmbDBase{\execute_sql{"insert into " + nmbTabla + " values ("+ sqlValue(int(cont)) + ", " + sqlValue(getNombreExpandido) +")"}}}
                cont= cont+1
              }
          }
        \comb_elu_sismicas
          {
            \for_each
              {
                \sqlite{\nmbDBase{\execute_sql{"insert into " + nmbTabla + " values ("+ sqlValue(int(cont)) + ", " + sqlValue(getNombreExpandido) +")"}}}
                cont= cont+1
              }
          }
      }
    return cont
  }

# Crea una tabla de combinaciones en estado límite de servicio en situaciones poco frecuentes.
def SQLTtablaCombsSLSPF(nmbDBase,nmbTabla,offset):
  {
    
    cont= offset
    SQLTcreaTabla(nmbDBase,nmbTabla,"(idComb INT, descomp STRING)"){}
    \combinaciones
      {
        \comb_els_poco_frecuentes
          {
            \for_each
              {
                \sqlite{\nmbDBase{\execute_sql{"insert into " + nmbTabla + " values ("+ sqlValue(int(cont)) + ", " + sqlValue(getNombreExpandido) +")"}}}
                cont= cont+1
              }
          }
      }
    return cont
  }

# Crea una tabla de combinaciones en estado límite de servicio en situaciones frecuentes.
def SQLTtablaCombsSLSF(nmbDBase,nmbTabla,offset):
  {
    
    cont= offset
    SQLTcreaTabla(nmbDBase,nmbTabla,"(idComb INT, descomp STRING)"){}
    \combinaciones
      {
        \comb_els_frecuentes
          {
            \for_each
              {
                \sqlite{\nmbDBase{\execute_sql{"insert into " + nmbTabla + " values ("+ sqlValue(int(cont)) + ", " + sqlValue(getNombreExpandido) +")"}}}
                cont= cont+1
              }
          }
      }
    return cont
  }

# Crea una tabla de combinaciones en estado límite de servicio en situaciones cuasi_permanentes.
def SQLTtablaCombsSLSCP(nmbDBase,nmbTabla,offset):
  {
    
    cont= offset
    SQLTcreaTabla(nmbDBase,nmbTabla,"(idComb INT, descomp STRING)"){}
    \combinaciones
      {
        \comb_els_cuasi_permanentes
          {
            \for_each
              {
                \sqlite{\nmbDBase{\execute_sql{"insert into " + nmbTabla + " values ("+ sqlValue(int(cont)) + ", " + sqlValue(getNombreExpandido) +")"}}}
                cont= cont+1
              }
          }
      }
    return cont
  }
