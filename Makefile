stocks: stocks.cpp
	g++ -std=c++20 -Wall -Wextra -Wconversion stocks.cpp -o stocks

run: stocks
	./stocks

clean:
	rm -f stocks
