#!/bin/bash
g++ trie.cpp -o trie

./trie

dot -Tsvg Trie.dot > img.svg

open img.svg

# you can choose to retain any of these files
rm trie Trie.dot 
