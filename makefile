CXX = g++
CXX_ARGS = -g --std=c++20
INCLUDE_DIR = .

lesshtml: main.o config_parser.o html_parser.o
	$(CXX) $(CXX_ARGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXX_ARGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm *.o

all: lesshtml
