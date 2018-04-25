# -*- coding: utf-8 -*-
P1= 
P1= calcPlanoBuzamiento(alpha1,beta1,p)
P2= 
P2= calcPlanoBuzamiento(alpha2,beta2,p)
P3= 
P3= calcPlanoBuzamiento(alpha3,beta3,p)

# Tunnel axis
tunnelAxisVector= [sin(axisBeta),cos(axisBeta),0]
vectorITunel= cross([0,0,1],tunnelAxisVector)
vectorJTunel= cross(tunnelAxisVector,vectorITunel)
tunnelAxis= 
\tunnelAxis
  {
    \setOrg{p}
    \axis{\setVectoresIJ{[vectorITunel,vectorJTunel]}}
  }

'''Define los semiespacios superiores e inferiores
   correspondientes a los planos P1,P2 y P3'''
P1L= 
\P1L{\setPlano{P1}}
P1U= 
\P1U{\setPlano{P1} \swap{}}

P2L= 
\P2L{\setPlano{P2}}
P2U= 
\P2U{\setPlano{P2} \swap{}}

P3L= 
\P3L{\setPlano{P3}}
P3U= 
\P3U{\setPlano{P3} \swap{}}
