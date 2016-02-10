#!/bin/bash

mkdir -p oldzips
mv *.zip oldzips/
zip `date +%H%M%S`.zip src/* Makefile
