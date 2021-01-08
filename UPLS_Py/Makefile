release:
	make clean
	cmake -B build -DCMAKE_BUILD_TYPE=Release
	cd build && make &&	make install
debug:
	make clean
	cmake -B build -DCMAKE_BUILD_TYPE=Debug
	cd build && make &&	make install
clean:
	rm -rf lib
	rm -rf build