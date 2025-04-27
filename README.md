# bin_packing_parallel

Executing Bin Packing Problem in parallel with OpenMP in C++.

The program reads the text file and determines the minimum number of containers needed to store all of the boxes based on the algorithm used (**First Fit** and **Next fit** in *parallel* - **First Fit Decreasing**, **First Fit** and **Next fit** in *sequential*). Each algorithm has its own time complexity and performance. 

I was unable to use **First Fit** Decreasing in *parallel* since it is pointless to sort the boxes just to randomly select them at the end (each threat will select a box at a different position).  

**First Fit** performed the best in *parallel* with 201 containers compared to **Next fit** with 210 containers.

## Set up

1. Follow [C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp) installation process
2. After compiling the code, make this change in `tasks.json`. Convert `-g` to `-fopenmp` inside of `"args"`
```
"args": [..., "-g", ...] --> "args": [..., "-fopenmp", ...] 
``` 
3. Compile and run the code, either through the `Run and Debug` option on the side panel in vscode or the terminal. 

## References:

- https://www.tutorialspoint.com/bin-packing-problem-minimize-number-of-used-bins-in-cplusplus
