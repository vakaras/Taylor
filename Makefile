.PHONY: build prog

build: 
	python setup.py build

link: 
	ln -s build/lib.*/*.so .

test: 
	python test.py 

prog: clean
	g++ -g main.cpp -lmpfr -lgmp -o prog

clean:
	rm -f prog

latex:
	rm -rf doc/lmath
	mkdir -p doc/lmath
	cp lmath.py doc/lmath/__init__.py
	cp build/lib.*/lmathcpp.so doc/lmath/
