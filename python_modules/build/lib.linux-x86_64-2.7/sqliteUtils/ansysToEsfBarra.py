# -*- coding: utf-8 -*-
from sqliteUtils import macros_sqlite

def ansysToEsfBarra(nmbArch,nmbDBase,nmbTabla):
  '''Importa el listado de esfuerzos en barras de ansys que se pasa como parámetro
   nmbArchivo: Nombre del archivo que contiene el listado.
   nmbDBase: Nombre de la base de datos donde se guardará la tabla.
   nmbTabla: Nombre de la tabla que contendrá los esfuerzos.'''

  macros_sqlite.SQLTcreaTabla(nmbDBase,nmbTabla,"(ACCION string,ELEM integer,AXIL double,Q_1 double,Q_2 double,M_1 double,M_2 double,TORSOR double)")

  fieldwidths = (0,8,9,20,21,32,33,44,45,56,57,68,69,80)
  fmtstring = ''.join('%ds' % f for f in fieldwidths)
  fieldstruct = struct.Struct(fmtstring)
  parse = fieldstruct.unpack_from

  con= sqlite.connect(nmbDBase)
  cur= con.cursor()

  listado.open(nmbArch,"r")
  for line in listado:
    str1= line
    str1SB= qBlancos(str1)
    if(strlen(str1)>0):
      if(regExpMatch(".*Accion.*",str1)):
        nmbAccion= copiaDesde(" ",copiaHasta(":",str1SB))
      else:
        if(regExpMatch("[0-9]+.*",str1SB)):
          lst=csv2list(fixedWidth2Csv(str1))
          cur.execute_sql("insert into "+nmbTabla+" values('"+nmbAccion+"',"+lst.sqlValues+")")
  listado.close()

def ansysExtractElem(nmbDBase,nmbTablaEsf,nmbTablaElem):
  '''Crea una tabla con los números de elemento contenidos en el listado
   nmbDBase: Nombre de la base de datos donde se guardará la tabla.
   nmbTablaEsf: Nombre de la tabla que contiene los esfuerzos.
   nmbTableElem: Nombre de la tabla que contendrá los índices de elemento.'''
  macros_sqlite.SQLTcreaTabla(nmbDBase,nmbTablaElem,"(ELEM integer)")

  con= sqlite.connect(nmbDBase)
  cur= con.cursor()
  cur.execute("insert into "+nmbTablaElem+ " select distinct ELEM from " + nmbTablaEsf )

def ansysCreaElem(nmbDBase,nmbTablaElem,nmbSeccion):
  '''Crea los elementos a partir de la tabla creada anteriormente
   nmbDBase: Nombre de la base de datos donde se guardará la tabla.
   nmbTableElem: Nombre de la tabla que contiene los índices de elemento.
   nmbSeccion: Nombre de la sección que se asigna a cada elemento.'''
  con= sqlite.connect(nmbDBase)
  cur= con.cursor()

  i= 1
  cur.execute("select * from " + nmbTablaElem)
  while True:
    row= cur.fetchone()
    if row == None:
      break
    else:
      nuevoZeroLengthSeccFibras(nmbSeccion,i,row("ELEM"))
      i+= 2

