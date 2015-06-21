# -*- coding: utf-8 -*-
print "\\section{",caption," Análisis cinemático de cuñas y bloques.}\n"
print "\\begin{center}\n"
print "\\begin{tabular}{|l|c|c|}\n"
print "\\hline\n"
print "Familia & Buzamiento & Dir. buzamiento\\\\\n"
print "\\hline\n"
print "P1 &", rad2deg(alpha1)," & ",rad2deg(beta1),"\\\\\n"
print "P2 &", rad2deg(alpha2)," & ",rad2deg(beta2),"\\\\\n"
print "P3 &", rad2deg(alpha3)," & ",rad2deg(beta3),"\\\\\n"
print "\\hline\n"
print "\\multicolumn{3}{|l|}{Eje del túnel: ",vectorEjeTunel,"}\\\\\n"
print "\\hline\n"
print "\\end{tabular}\n"
print "\\end{center}\n"
\JP000{ \procesaAnguloPoliedrico("JP000",nmbTun){} }
\JP001{ \procesaAnguloPoliedrico("JP001",nmbTun){} }
\JP010{ \procesaAnguloPoliedrico("JP010",nmbTun){} }
\JP011{ \procesaAnguloPoliedrico("JP011",nmbTun){} }
\JP100{ \procesaAnguloPoliedrico("JP100",nmbTun){} }
\JP101{ \procesaAnguloPoliedrico("JP101",nmbTun){} }
\JP110{ \procesaAnguloPoliedrico("JP110",nmbTun){} }
\JP111{ \procesaAnguloPoliedrico("JP111",nmbTun){} }
