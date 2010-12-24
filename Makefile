.PHONY: build prog

build: 
	python setup.py build

link: 
	ln -s build/lib.linux-x86_64-2.6/*.so .

test: 
	python test.py 

prog: clean
	g++ -g main.cpp -lmpfr -lgmp -o prog

clean:
	rm -f prog
