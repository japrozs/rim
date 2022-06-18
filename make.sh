#! /bin/sh

echo $ clang -Wall -Wextra -pedantic main.c rim.c -o out/main
clang -Wall -Wextra -pedantic main.c rim.c -o out/main
rm -rf out/*.dSYM