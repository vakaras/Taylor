#!/bin/bash

dest="${1}"
lib="lmath"

echo "Paskirties vieta: „${dest}“."
echo "Kompiliuojama."
make
echo "Kopijuojama."
mkdir -p "${dest}/${lib}"
cp lmath.py "${dest}/${lib}/__init__.py"
cp build/lib.*/lmathcpp.so "${dest}/${lib}/"
echo "Sėkmingai įdiegta."
echo "Patikrinti ar veikia galite tokiu būdu:"
echo "$ export PYTHONPATH=\"${dest}:${PYTHONPATH}\""
echo "$ python"
echo ">>> from lmath import sin"
echo ">>> sin(1).asString(50)"
