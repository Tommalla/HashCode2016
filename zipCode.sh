#!/bin/bash

mkdir -p oldzips
mv *.zip oldzips/
zip `date +%s`.zip src/* Makefile
