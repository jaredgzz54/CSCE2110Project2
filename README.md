# Project2
Project 2: Smart Campus Navigation and Facility Analytics System

Purpose:
A modular C++ program designed to load campus data, query facilities using a custom hash table, analyze building connectivity through an undirected graph and BFS, and manage department hierarchies via a general tree.

Build Instructions:
g++ -std=c++17 src/*.cpp -Iinclude -o campus

Run Instructions:
./campus               (loads data from default data/ directory)
./campus testdata/     (loads data from custom test directory)
