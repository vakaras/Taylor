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
