# Percolation
This repo contains the code for the study of percolation on a 2D wall. Our percolation model is quite simple: given a M * N binary matrix, we have to determine whether the fluid can get to the bottom of the wall. We assume that the fluid can only move vertically or horizontally to neighbouting cells with positive value. Moreover, the fluid starts at the top of the wall along its entire length.

For a given binary matrix, we determine if the liquid can percolate with 3 different algorithmic techniques: Depth First Search, Breadth First Search and by using the Union Find data structure for connected components.

Furthermore, for a given matrix size M * N, we carry out statistical tests to estimate the probability of percolation, assuming that each cell of the wall is distributed as a Bernoulli random variable with p = 0.5. 

Finally, for a given matrix size M * N, we compute the exact probability of percolation, by testing out model all possible binary matrices with size M * N. These matrices are generated with backtracking. For this last idea, developed in the file *simulate.cpp*, we must keep in mind that the number of binary matrices of size M * N is 2^(M * N), which makes the runtime of this program exponential in the size of the matrices.

