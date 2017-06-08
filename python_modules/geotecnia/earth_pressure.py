# -*- coding: utf-8 -*-
from __future__ import division
import FrictionalSoil as fs
import math

'''earth_pressure.py: earth pressures for retaining structures.'''

__author__= "Luis C. Pérez Tato (LCPT)"
__copyright__= "Copyright 2016, LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"

# From Wikipedia:



class RankineSoil(fs.FrictionalSoil):
  '''From Wikipedia: Rankine's theory, developed in 1857, is a stress field solution that predicts active and passive earth pressure. It assumes that the soil is cohesionless, the wall is frictionless, the soil-wall interface is vertical, the failure surface on which the soil moves is planar, and the resultant force is angled parallel to the backfill surface. The equations for active and passive lateral earth pressure coefficients are given below. Note that φ is the angle of shearing resistance of the soil and the backfill is inclined at angle β to the horizontal.

  :ivar phi:    internal friction angle of the soil
  :ivar beta:   angle of backfill with horizontal
  '''
  def __init__(self,phi,beta= 0.0,rho= 2100.0):
    super(RankineSoil,self).__init__(phi,rho)
    self.beta= beta
  def Ka(self):
    '''Returns Rankine's active earth pressure coefficient.'''
    cBeta= math.cos(self.beta)
    cPhi= math.cos(self.phi)
    r= math.sqrt(cBeta**2-cPhi**2)
    return cBeta*(cBeta-r)/(cBeta+r)
  def Kp(self):
    '''Returns Rankine's passive earth pressure coefficient.'''
    cBeta= math.cos(self.beta)
    cPhi= math.cos(self.phi)
    r= math.sqrt(cBeta**2-cPhi**2)
    return cBeta*(cBeta+r)/(cBeta-r)

# Empujes según Coulomb.
# La teoría de Coulomb es válida si la superficie de terreno contenido es plana y la superficie de contacto con el muro también es plana.
# Expresiones tomadas del libro de Calavera "Muros de contención y muros de sótano", capítulo 3

# Coeficientes de empuje.

def ka_coulomb(a,b,fi,d):
    '''
    ka_coulomb(a,b,fi,d):
    Devuelve el coeficiente de empuje activo según la teoría de Coulomb 
    a partir de:
    a:  Angulo del trasdós del muro con la vertical (en radianes).
    b:  Angulo de la superficie del terreno contenido, con la horizontal (en radianes).
    fi: Angulo de rozamiento interno del terreno (en radianes).
    d:  Angulo entre la línea de acción del empuje activo y la normal a la superficie
        del muro. (rozamiento tierras - fabrica) (en radianes).
    Jiménez Salas, Geotecnia y Cimientos página 682 
    '''
    num= 1.0/math.cos(a)*math.cos(fi-a)
    r1=math.sqrt(math.cos(a+d))
    r2=math.sqrt(math.sin(fi+d)*math.sin(fi-b)/math.cos(b-a))
    return (math.pow((num/(r1+r2)),2))

def kah_coulomb(a,b,fi,d):
    '''
    Devuelve la componente horizontal del coeficiente de empuje activo
    según la teoría de Coulomb a partir de:
    a:  Angulo del trasdós del muro con la vertical (en radianes).
    b:  Angulo de la superficie del terreno contenido, con la horizontal (en radianes).
    fi: Angulo de rozamiento interno del terreno (en radianes).
    d:  Angulo entre la línea de acción del empuje activo y la normal
        a la superficie del muro. (rozamiento tierras - fabrica) (en radianes).
    '''
    return (ka_coulomb(a,b,fi,d)*math.cos(a+d))

def kav_coulomb(a,b,fi,d):
    '''
    kav_coulomb(a,b,fi,d):
    Devuelve la componente vertical del coeficiente de empuje activo
    según la teoría de Coulomb a partir de:
    a:  Angulo del trasdós del muro con la vertical (en radianes).
    b:  Angulo de la superficie del terreno contenido, con la horizontal (en radianes).
    fi: Angulo de rozamiento interno del terreno (en radianes).
    d:  Angulo entre la línea de acción del empuje activo y la normal
        a la superficie del muro. (rozamiento tierras - fabrica) (en radianes).
    '''
    return (ka_coulomb(a,b,fi,d)*math.sin(a,d))


#Empujes unitarios debidos a cargas sobre el terreno.

def ep_coulomb(a,b,fi,d,p):
    '''
    ep_coulomb(a,b,fi,d,p):
    Devuelve el empuje unitario producido por una sobrecarga uniforme p que actúa
    sobre la superficie del terreno contenido.
    según la teoría de Coulomb a partir de:
    a:  Angulo del trasdós del muro con la vertical (en radianes).
    b:  Angulo de la superficie del terreno contenido, con la horizontal (en radianes).
    fi: Angulo de rozamiento interno del terreno (en radianes).
    d:  Angulo entre la línea de acción del empuje activo y la normal
        a la superficie del muro. (rozamiento tierras - fabrica) (en radianes).
    p: Sobrecarga uniforme.
    '''
    return(ka_coulomb(a,b,fi,d)*p*math.cos(a)/float(math.cos(b-a)))


def eql_coulomb(x,H,z,ql):
    '''
    Devuelve el empuje unitario producido por una sobrecarga lineal ql que actúa
    sobre una recta paralela a la coronación del muro sobre la superficie del terreno contenido.
    a partir de:
    x:  Distancia entre la coronación del trasdós y la línea de aplicación de
              la carga.
    H:  Profundidad del extremo inferior del trasdós.
    z:  Profundidad del punto en el que se obtiene el empuje.
    ql: Valor de la sobrecarga lineal.
    '''
    m=x/float(H)
    n=z/float(H)
    if m<=0.4:
        return(0.2*m/float(math.pow((0.16+n*n),2))*ql/float(H))
    else:
        return(1.28*m**2*n/float((m**2+n**2)**2)*ql/float(H))
                


def eqp_coulomb(x,H,z,qp):
    '''
    eqp_coulomb(x,H,z,qp):
    Devuelve el empuje unitario producido por una sobrecarga puntual qp, vertical, que actúa
    sobre la superficie del terreno y está contenida en el plano vertical de la sección del muro
    sobre la que se calcula el empuje, a partir de:
    x:  Distancia desde la coronación del trasdós al punto de aplicación de
              la carga.
    H:  Profundidad del extremo inferior del trasdós.
    z:  Profundidad del punto en el que se obtiene el empuje.
    qp: carga puntual
    '''
    m=x/float(H)
    nz/float(H)
    if m<=0.4:
        return(0.28*n**2/float(math.pow((0.16+n**2),3))*qp/float(H**2))
    else:
        return(1.77*m**2*n**2/float(math.pow((m**2+n**2),3))*qp/float(H**2))

