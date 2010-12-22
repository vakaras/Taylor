.PHONY: build

build: 
	python setup.py build

link: 
	ln -s build/lib.linux-x86_64-2.6/*.so .

test: 
	python test.py 
