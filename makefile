main:
	g++ -std=c++20 main.cpp -o main.out

run:
	g++ -std=c++20 main.cpp -o main.out
	./main.out

test:
	g++ -std=c++20 test.cpp -o test.out
	./test.out
	
clean:
	rm -rf *.out
	rm -rf volume.txt
	rm *.o
