# CTikz
C++ class CTikz to create TikZ file which can be used for latex. It is suitable to create charts out of a data array or data vector from C++.

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

## How to start

1. clone project
```
> git clone https://github.com/mchlbrnhrd/CTikz
```

2. compile
```
> make
```

3. execute test code:
```
> ./CTikzApp
```

Four example tikz files will be created with corresponding pdf files.
