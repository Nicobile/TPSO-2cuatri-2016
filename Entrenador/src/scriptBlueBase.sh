#!/bin/bash

cd
cd nilotesteamos/tp-2016-2c-Ni-Lo-Testeamos/Entrenador/src

gcc Entrenador.c libSockets.c libSockets.h -o entrenador -lcommons -lfuse -lpthread

./entrenador Blue /home/nilotesteamos/mnt/01-base

