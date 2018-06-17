#!/bin/bash

cd src;
make;
cp myshell ../bin;
make clean;
cd -
