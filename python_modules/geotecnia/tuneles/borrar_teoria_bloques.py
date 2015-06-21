# -*- coding: utf-8 -*-

# Macros útiles para teoría de bloques (ver Goodman & Shi, Block theory and its application to rock engineering 1985)

import geom
import math

def calcPlanoBuzamiento(alpha,beta,p):
    '''
    Devuelve el plano de buzamiento definido por:
    alpha: Ángulo de buzamiento.
    beta: Dirección del buzamiento.
    p: Punto por el que pasa el plano
    '''
    A=math.sin(alpha)*math.sin(beta)
    B=math.sin(alpha)*math.cos(beta)
    C=math.cos(alpha)
    D=-(A*p.x+B*p.y+C*p.z)

    retval=geom.Plano3d(geom.EcuacionGeneralPlano3d(A,B,C,D))
    return retval

#este módulo no está terminado
