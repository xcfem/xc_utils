#!/bin/sh
ERT="\\033[1;32m"
NORMAL="\\033[0;39m"
ROUGE="\\033[1;31m"
ROSE="\\033[1;35m"
BLEU="\\033[1;34m"
BLANC="\\033[0;02m"
BLANCLAIR="\\033[1;08m"
JAUNE="\\033[1;33m"
CYAN="\\033[1;36m"

echo ""

#Misc
echo "$BLEU" "Misc. tests." "$NORMAL"
python ./python_tests/test_evalPy.py
python ./python_tests/test_execPy.py
python ./python_tests/miscUtils/testStairCaseFunction.py


#Soil mechanics
echo "$BLEU" "Soil mechanics." "$NORMAL"
python ./python_tests/soil_mechanics/test_mononobe_okabe.py
python ./python_tests/soil_mechanics/test_coulomb.py
python ./python_tests/soil_mechanics/test_janssen_limited_backfill_widht.py
python ./python_tests/soil_mechanics/test_rankine.py
python ./python_tests/soil_mechanics/test_brinch_hansen01.py
python ./python_tests/soil_mechanics/test_brinch_hansen02.py
python ./python_tests/soil_mechanics/test_stratified_soil.py
python ./python_tests/soil_mechanics/test_boussinesq.py

#Test de combinaciones.
echo "$BLEU" "Geometry tests." "$NORMAL"
python ./python_tests/geom/test_coosys_01.py
python ./python_tests/geom/test_refsys3d3d_01.py
python ./python_tests/geom/test_refsys2d3d_01.py
python ./python_tests/geom/prueba_polilinea2d_01.py
python ./python_tests/geom/test_polyline2d_02.py
python ./python_tests/geom/test_polyline3d_01.py
python ./python_tests/geom/pruebaPos3d01.py
python ./python_tests/geom/prueba_recta2d_01.py
python ./python_tests/geom/test_line2d_intersection.py
python ./python_tests/geom/prueba_vdesliz3d_03.py
python ./python_tests/geom/prueba_list_pos2d_01.py
python ./python_tests/geom/prueba_segment2d_01.py
python ./python_tests/geom/prueba_vector3d_01.py
python ./python_tests/geom/prueba_vector2d_02.py
#python ./python_tests/geom/prueba_semiespacio3d_02.py
python ./python_tests/geom/pruebaPos2d01.py
python ./python_tests/geom/prueba_recta3d_01.py
python ./python_tests/geom/prueba_vdesliz3d_02.py
#python ./python_tests/geom/prueba_semiespacio3d_04.py
python ./python_tests/geom/circle2d_test_01.py
python ./python_tests/geom/circle2d_test_02.py
#python ./python_tests/geom/prueba_semiespacio3d_01.py
python ./python_tests/geom/prueba_vdesliz3d_01.py
python ./python_tests/geom/plane_test_01.py
python ./python_tests/geom/plane_test_02.py
python ./python_tests/geom/plane_test_03.py
#python ./python_tests/geom/plane_test_04.py
python ./python_tests/geom/plane_test_05.py
python ./python_tests/geom/test3dPoly.py
python ./python_tests/geom/prueba_vector2d_01.py
python ./python_tests/geom/prueba_segment2d_02.py
python ./python_tests/geom/polygon2D_test_2d_01.py
python ./python_tests/geom/polygon2D_test_2d_02.py
python ./python_tests/geom/polygon2D_test_2d_03.py
python ./python_tests/geom/polygon2D_test_2d_04.py
python ./python_tests/geom/polygon2D_test_2d_05.py
python ./python_tests/geom/polygon2D_test_2d_06.py
python ./python_tests/geom/polygon2D_test_2d_07.py
python ./python_tests/geom/polygon2D_test_2d_08.py
python ./python_tests/geom/polygon2D_test_2d_09.py
python ./python_tests/geom/prueba_vector3d_02.py
python ./python_tests/geom/svd2d_test_01.py
python ./python_tests/geom/svd2d_test_02.py
python ./python_tests/geom/prueba_svd3d_01.py
python ./python_tests/geom/prueba_svd3d_02.py
#python ./python_tests/geom/prueba_semiespacio3d_03.py
python ./python_tests/geom/test_angle_vector3d_01.py
python ./python_tests/geom/test_2drotation_01.py
python ./python_tests/geom/test_principal_axes_of_inertia2D_01.py

#VTK
#python ./python_tests/vtk/plot_cone.py

#Load combinations test.
echo "$BLEU" "Load combination tests." "$NORMAL"
#python ./python_tests/loadCombinations/testLoadCombinations.py
python ./python_tests/loadCombinations/test_esclavas_00.py
python ./python_tests/loadCombinations/test_accidentales.py
python ./python_tests/loadCombinations/test_iap11.py
