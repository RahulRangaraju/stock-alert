stocks: main.cpp stock.cpp analysis.cpp menu.cpp stock.h analysis.h menu.h
	g++ -std=c++20 -Wall -Wextra -Wconversion main.cpp stock.cpp analysis.cpp menu.cpp -o stocks

run: stocks
	./stocks

clean:
	rm -f stocks
