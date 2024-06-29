#!/bin/bash

# Derleme komutu
make all

# Derlemenin başarılı olup olmadığını kontrol et
if [ $? -eq 0 ]; then
    echo "-----------------------"
    echo "Build succeeded."
    echo "Running the program..."
    echo "-----------------------"
    echo " "
    # Programı çalıştır, bellek sızıntısını test et (valgrind)
    ./out
else
    echo "Build failed."
fi
