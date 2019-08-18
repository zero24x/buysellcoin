#!/bin/sh

# Let's compile Buysellcoin daemon


cd src/leveldb
make libleveldb.a libmemenv.a
cd ..
make -f makefile.unix
strip buysellcoind
