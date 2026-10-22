stocks: main.cpp stock.cpp analysis.cpp menu.cpp settings.cpp stock.h analysis.h menu.h settings.h
	g++ -std=c++20 -Wall -Wextra -Wconversion main.cpp stock.cpp analysis.cpp menu.cpp settings.cpp -o stocks

run: stocks
	./stocks

clean:
	rm -f stocks
