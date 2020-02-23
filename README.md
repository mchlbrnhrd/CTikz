# CTikz
When writing thesis or paper in LaTeX and you have done data analysis in C++ or don't like the default Matlab graphics then CTikz can be used to create TikZ files for your LaTeX document. This C++ class CTikz creates TikZ files and as preview a pdf of the graphic. It is suitable to create charts out of a C data array (*double x[10]*) or data vector (*std::vector\<double\> x*) from C++. 

## Example picture
![example picture](/doc/second.tikz.latex.png)

## Code
```C++
CTikz tikz;
const int N = 100;
double x[N];
double y[N];
// ...
tikz.addData(x, y, N);
tikz.createTikzPdf("example.tikz");
```

Complete examples in [main.cpp](main.cpp).
## How to start

1. clone project and change directory
```
> git clone https://github.com/mchlbrnhrd/CTikz
> cd CTikz
```

2. compile
```
> make
```

3. execute test code:
```
> cd bin
> ./CTikzApp
```

Four example tikz files will be created with corresponding pdf files.
