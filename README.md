## Flattened AST proof of concept in cpp

WORK IN PROGRESS

## What is it

After hearing about flattened ASTs ([for example here](https://www.cs.cornell.edu/~asampson/blog/flattening.html)), I thought about implementing it in my [compiler](https://github.com/Vinz2008/C.) written in C++. The only problem was that I used class which are an arbitrary size, so I can't just use a vector, like in the article. So I started working on a proof of concept of the same principle, but that could work in cpp with oop.

## How it works

It has the same cache locality because it uses a Arena and has the same size reduction by using index to the arena. It also keeps type information with a wrapper type (Very useful to not just have a void* everywhere that would need to be cast or to specify a specific derived class to use)