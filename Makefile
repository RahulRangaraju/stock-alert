stocks: main.cpp stock.cpp analysis.cpp stock.h analysis.h
	g++ -std=c++20 -Wall -Wextra -Wconversion main.cpp stock.cpp analysis.cpp -o stocks

run: stocks
	./stocks

clean:
	rm -f stocks
