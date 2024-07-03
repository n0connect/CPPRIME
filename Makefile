# C++ derleyici
CXX = g++

# C++ derleme flag'leri
CXXFLAGS = -Wall -Wextra -O3 -march=native -flto -fopenmp -pthread

# GMP ve math kütüphaneleri
LIBS = -lgmpxx -lgmp

# Derlenecek programın adı
TARGET = out

# C++ kaynak dosyaları
SRCS_CPP = main.cpp ./src/primefile.cpp ./src/primealgorithm.cpp ./src/paralize.cpp

# C++ objeleri
OBJS_CPP = $(SRCS_CPP:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS_CPP)
	$(CXX) $(CXXFLAGS) $(OBJS_CPP) -o $(TARGET) $(LIBS)

# C++ dosyalarını derleme
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_CPP) $(TARGET)
