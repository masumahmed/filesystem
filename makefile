main:
	g++ -std=c++20 main.cpp -o main.out
	./main.out
	
clean:
	rm -rf *.out
	rm -rf volume.txt
	rm *.o
