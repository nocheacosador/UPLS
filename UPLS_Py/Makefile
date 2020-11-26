all:
	make clean
	cmake -B build -DCMAKE_CXX_FLAGS=-fPIC
	cd build && make &&	make install
clean:
	rm -rf lib
	rm -rf build