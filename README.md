# match2d
A little C++ program to locate occurences of binary square matrices (the patterns) in larger binary square matrices. The algorithm is an extension of Aho-Corasick to 2D. The program takes as input two numbers n and m where n is the dimension of the large matrix and m is the dimension of the pattern-matrix (m <= n). The program then reads n lines each containing a binary string of length n, then it reads m lines each containing a binary string of length m. The program outputs where the mxm matrix occurs as a sub-matrix of the nxn matrix.

Sample input/output:

input:
<code>
12 2
101110111011
111010111011
110110111011
101110111010
101110111010
101110111010
101110111010
111010111011
111010111011
111010111011
111010111011
111010111011
11
10
</code>

output:
<code>
match at (2,0)
match at (1,1)
match at (0,2)
match at (6,2)
match at (2,10)
</code>
