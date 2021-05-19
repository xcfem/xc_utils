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

START=$(date +%s.%N)

#Misc
echo "$BLEU" "Misc. tests." "$NORMAL"
python ./python_tests/test_evalPy.py
python ./python_tests/test_execPy.py
python ./python_tests/miscUtils/testStairCaseFunction.py
python ./python_tests/miscUtils/test_linear_interpolation.py
python ./python_tests/miscUtils/test_remove_accents.py


#Geometry.
echo "$BLEU" "Geometry tests." "$NORMAL"
echo "$BLEU" "  Vectors." "$NORMAL"
python ./python_tests/geom/vector2d_test_01.py
python ./python_tests/geom/vector2d_test_02.py
python ./python_tests/geom/vector3d_test_01.py
python ./python_tests/geom/vector3d_test_02.py
python ./python_tests/geom/vector3d_angle_test_01.py
echo "$BLEU" "  Points." "$NORMAL"
python ./python_tests/geom/pos2d_test_01.py
python ./python_tests/geom/pos3d_test_01.py
python ./python_tests/geom/pos3d_list_test_01.py
echo "$BLEU" "  Lines, rays and segments." "$NORMAL"
python ./python_tests/geom/line2d_test_01.py
python ./python_tests/geom/line3d_test_01.py
python ./python_tests/geom/line2d_intersection_test.py
python ./python_tests/geom/segment2d_test_01.py
python ./python_tests/geom/segment2d_test_02.py
python ./python_tests/geom/line_segment_intersection_test.py
python ./python_tests/geom/segment3d_test_01.py
python ./python_tests/geom/segment3d_test_02.py
python ./python_tests/geom/ray2d_test.py
echo "$BLEU" "  Polylines." "$NORMAL"
python ./python_tests/geom/pos2d_list_test_01.py
python ./python_tests/geom/polyline2d_test_01.py
python ./python_tests/geom/polyline2d_test_02.py
python ./python_tests/geom/polyline3d_test_01.py
python ./python_tests/geom/polyline3d_test_02.py
echo "$BLEU" "  Polygons." "$NORMAL"
python ./python_tests/geom/polygon2D_test_2d_01.py
python ./python_tests/geom/polygon2D_test_2d_02.py
python ./python_tests/geom/polygon2D_test_2d_03.py
python ./python_tests/geom/polygon2D_test_2d_04.py
python ./python_tests/geom/polygon2D_test_2d_05.py
python ./python_tests/geom/polygon2D_test_2d_06.py
python ./python_tests/geom/polygon2D_test_2d_07.py
python ./python_tests/geom/polygon2D_test_2d_08.py
python ./python_tests/geom/polygon2D_test_2d_09.py
python ./python_tests/geom/polygon2D_test_2d_10.py
python ./python_tests/geom/polygon2D_test_2d_11.py
python ./python_tests/geom/polygon3D_test_01.py
python ./python_tests/geom/polygon3D_test_02.py
python ./python_tests/geom/polygon3D_test_03.py
python ./python_tests/geom/polygon3D_test_04.py
echo "$BLEU" "  Alpha shapes." "$NORMAL"
python ./python_tests/geom/basic_alpha_shape2d_test.py
echo "$BLEU" "  Circles." "$NORMAL"
python ./python_tests/geom/circle2d_test_01.py
python ./python_tests/geom/circle2d_test_02.py
echo "$BLEU" "  Sliding vectors." "$NORMAL"
python ./python_tests/geom/sliding_vector_3d_test_01.py
python ./python_tests/geom/sliding_vector_3d_test_02.py
python ./python_tests/geom/sliding_vector_3d_test_03.py
python ./python_tests/geom/sliding_vectors_system_2d_test_01.py
python ./python_tests/geom/sliding_vectors_system_2d_test_02.py
python ./python_tests/geom/sliding_vectors_system_2d_test_03.py
python ./python_tests/geom/sliding_vectors_system_2d_test_04.py
python ./python_tests/geom/sliding_vectors_system_2d_test_05.py
python ./python_tests/geom/sliding_vectors_system_3d_test_01.py
python ./python_tests/geom/sliding_vectors_system_3d_test_02.py
python ./python_tests/geom/sliding_vectors_system_3d_test_03.py
python ./python_tests/geom/sliding_vectors_system_3d_test_04.py
python ./python_tests/geom/sliding_vectors_system_3d_test_05.py
echo "$BLEU" "  Planes." "$NORMAL"
python ./python_tests/geom/plane_test_01.py
python ./python_tests/geom/plane_test_02.py
python ./python_tests/geom/plane_test_03.py
#python ./python_tests/geom/plane_test_04.py
python ./python_tests/geom/plane_test_05.py
# echo "$BLEU" "  3D half spaces." "$NORMAL"
# python ./python_tests/geom/halfspace3d_test_01.py
# python ./python_tests/geom/halfspace3d_test_02.py
# python ./python_tests/geom/halfspace3d_test_03.py
# python ./python_tests/geom/halfspace3d_test_04.py
echo "$BLEU" "  Reference systems." "$NORMAL"
python ./python_tests/geom/coosys_test_01.py
python ./python_tests/geom/refsys3d3d_test_01.py
python ./python_tests/geom/refsys2d3d_test_01.py
echo "$BLEU" "  Transformations." "$NORMAL"
python ./python_tests/geom/rotation2d_test_01.py
echo "$BLEU" "  Mechanical properties." "$NORMAL"
python ./python_tests/geom/principal_axes_of_inertia_2d_test_01.py
echo "$BLEU" "  DXF reading." "$NORMAL"
python ./python_tests/geom/ezdxf_test_01.py

#VTK
#python ./python_tests/vtk/plot_cone.py

END=$(date +%s.%N)
DIFF=$(echo "$END - $START" | bc)
echo $DIFF seconds
NT=$(grep -c '^python' $0)
echo ${NT} tests
Q=$(echo "$DIFF / $NT" | bc -l)
echo $Q seconds/test
