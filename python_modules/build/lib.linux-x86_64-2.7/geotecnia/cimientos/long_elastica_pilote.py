import math
def longElasticaPiloteArcillas(Epilote,Ipilote,Eterreno,L):
    '''
    longElasticaPiloteArcillas(Epilote,Ipilote,Eterreno,L):
    Longitud elástica del pilote en arcilla
    '''
    LePA=math.pow(Epilote*Ipilote/(Eterreno/3.),0.25)
    if LePA>2*L:
        print "El pilote es demasiado corto para su longitud elástica."
    return(LePA)

def longEmpotramientoPiloteArcillas(Epilote,Ipilote,Eterreno,L):
    '''
    longEmpotramientoPiloteArcillas(Epilote,Ipilote,Eterreno,L): 
    Longitud de empotramiento del pilote en arcilla
    '''
    return(1.2*longElasticaPiloteArcillas(Epilote,Ipilote,Eterreno,L))
