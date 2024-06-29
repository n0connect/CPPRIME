CC = gcc       # C derleyici
CXX = g++      # C++ derleyici
CFLAGS = -Wall -Wextra -g -lgmp -lm -Wunused-function  # C derleme flag'leri
CXXFLAGS = -Wall -Wextra -g -lgmp -lm -Wunused-function # C++ derleme flag'leri

TARGET = out   # Derlenecek programın adı

SRCS_C = main.cpp   # C dosyaları
SRCS_CPP = ./src/primefile.cpp ./src/primealgorithm.cpp   # C++ dosyaları

OBJS_C = $(SRCS_C:.c=.o)     # C objeleri
OBJS_CPP = $(SRCS_CPP:.cpp=.o)  # C++ objeleri

all: $(TARGET)

$(TARGET): $(OBJS_C) $(OBJS_CPP)
	$(CXX) $(CXXFLAGS) $(OBJS_C) $(OBJS_CPP) -o $(TARGET)

# C dosyalarını derleme
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# C++ dosyalarını derleme
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_C) $(OBJS_CPP) $(TARGET)
