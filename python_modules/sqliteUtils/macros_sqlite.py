# -*- coding: utf-8 -*-
import sqlite3 as sqlite

# Crea una base de datos con el nombre que se pasa como parámetro.
def SQLTcreaDBase(nmbDBase):
  conn = sqlite.connect(nmbDBase)

# Abra una base de datos que ya existe con el nombre que se pasa como parámetro.
def SQLTabreDBase(nmbDBase):
  conn = sqlite.connect(nmbDBase)

# Crea una tabla con el nombre y la definición que se pasan como parámetro.
def SQLTcreaTabla(nmbDBase,nmbTabla,defTabla):
 conn = sqlite.connect(nmbDBase)
 c= conn.cursor()
 c.execute("create table "+nmbTabla+" "+defTabla)

def SQLTborraTabla(nmbDBase,nmbTabla):
 conn = sqlite.connect(nmbDBase)
 c= conn.cursor()
 c.execute("drop table if exists '"+nmbTabla+"'")

def SQLTexisteTabla(nmbDBase,tablename):
  retval= False
  conn= sqlite.connect(nmbDBase)
  dbcur= conn.cursor()
  query= "SELECT count(*) FROM sqlite_master WHERE type='table' AND name= '"+tablename+ "';"
  dbcur.execute(query)
  if dbcur.fetchone()[0] == 1:
    retval= True
  dbcur.close()
  return retval
