# Parallel Prims Algorithm
Parallel implementation of Prim's algorithm. This project was completed as part of a Design and Analysis of Algorithms course at PES University. The aim was to benchmark a parallel implementation of Prim's algorithm against a sequential implementation. Prim's algorithm finds the minimum spanning tree for a weighted, undirected graph. You can read more about it [here](https://en.wikipedia.org/wiki/Prim%27s_algorithm).

## Implementation
We have used [OpenMP](https://www.openmp.org/) for parallelizing a single function. The benchmarking is done by running both, the sequential and parallel implementations on the same random input of the specified size and using a timing function. To check for threading overheads, we have run the tests by forcing 2 and 4 threads. All tests were done on a computer with Intel(R) Core(TM) i5-7200U CPU (2.50GHz-2.70GHz). We used [this](https://github.com/Parth-31/Parallel-Prims-Algorithm-using-OpenMP) repository as a reference.
We also ran this benchmark on Google Colab.
The python file ```bench.py``` is used to collect data for different sized inputs. Use the Make file to build the code. Run the ```bench```  with an argument for the size of the graph to compare.

## Results
As expected, the parallel implementation runs faster. Threading overheads play a factor at smaller sized inputs. The outliers are possibly due to a CPU delay. Running it on Google Colab gave us interesting results.
The visualizations for the benchmark(s) can be found [here](https://drive.google.com/open?id=1uSUaDjEXLD_WGnJ_ae-afxxdIaBNn0rE). 
