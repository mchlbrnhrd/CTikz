//
//  main.cpp
//  CTikzApplication
//
//  Created by Michael on 31.10.17.
//  Copyright © 2017 ___MICHAEL_BERNHARD___. All rights reserved.
//

#include <iostream>
#include <vector>
#include "CTikz.hpp"

int main(int argc, const char * argv[]) {

    std::cout << "CTikz example" << std::endl;
    
    
    // --------- first example ---------
    std::cout << "run first example" << std::endl;
    
    // example data x and y are stored in two vectors
    std::vector<double> exampleX;
    std::vector<double> exampleY;
    const int N = 100;
    for (int x=-N/2; x < N/2; ++x) {
        int y = x * x;
        exampleX.push_back(x);
        exampleY.push_back(y);
    }
    
    CTikz tikzA;
    
    // add data
    tikzA.addData(exampleX, exampleY);
    
    // create tikz and pdf file
    tikzA.createTikzPdf("example.tikz");
    
    
    
    
    
    // --------- second example ---------
    std::cout << "run second example" << std::endl;
    
    // data example A are stored into a vector which contains pairs of double for x and y
    std::vector<std::pair<double, double> > dataA;
    
    // data example B are stored into a vector which contains pairs of double for x and y
    std::vector<std::pair<double, double> > dataB;
    
    // fill data vectors
    for (int x=-N/2; x<N/2; ++x) {
        double yA = (double)x*x / (N*N/4.0);
        double yB = (double)x*x*x / (N*N*N/8.0);
        dataA.push_back(std::make_pair(x, yA));
        dataB.push_back(std::make_pair(x, yB));
    }
    
    CTikz tikz2;
    
    // add all data
    tikz2.addData(dataA, "dataA");
    tikz2.addData(dataB, "dataB");
    
    // switch grid on
    tikz2.gridOn();
    
    // set title, x label and y label
    tikz2.setTitle("Second example");
    tikz2.setLabel("x", "y");
    
    // set author and info text for tikz file
    tikz2.setAuthor("Michael Bernhard");
    tikz2.setInfo("some info text for tikz file");
    
    // create tikz and pdf file
    tikz2.createTikzPdf("second.tikz");
    
    
    
    
    
    
    
    return 0;
}
