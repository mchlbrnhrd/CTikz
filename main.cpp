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
    
    
    
    
    // --------- third example ---------
    std::cout << "run third example" << std::endl;
    
    
    CTikz tikz3;
    
    
    // add all data and secify user defined colors which are defined in your latex document
    // also change linestyle and marker and add comment in tikz file
    tikz3.addData(dataA, "dataA", "myRed");
    tikz3.addAddPlotStyle("dashed,mark=square, mark options={solid}, mark repeat=10");
    tikz3.addDataComment("Comment for data A in tikz file");
    
    tikz3.addData(dataB, "dataB", "myBlue");
    tikz3.addAddPlotStyle("dotted,mark=*, mark options={solid}, mark repeat=10");
    tikz3.addDataComment("Comment for data B in tikz file");
    
    // when creating pdf files out from this c++ program, then define the user defined colors
    tikz3.addAdditionalLatexCommands("\\definecolor{myRed}{RGB}{220,30,30}");
    tikz3.addAdditionalLatexCommands("\\definecolor{myGreen}{RGB}{20,200,30}");
    tikz3.addAdditionalLatexCommands("\\definecolor{myBlue}{RGB}{20,30,210}");
    
    
    
    // switch grid on
    tikz3.gridOn();
    
    
    
    // set title, x label and y label
    tikz3.setTitle("Third example");
    // use your own latex abbreviations
    tikz3.setLabel("$\\samplingfrequency$", "$\\snr$");
    
    // when creating pdf files out from this c++ program, then define your latex abbreviations
    tikz3.addAdditionalLatexCommands("\\newcommand{\\samplingfrequency}[0]{f_\\mathrm{S}}");
    tikz3.addAdditionalLatexCommands("\\newcommand{\\snr}[0]{\\gamma}");
    
    
    
    // set author and info text for tikz file
    tikz3.setAuthor("Michael Bernhard");
    tikz3.setInfo("some info text for tikz file");
    
    
    
    // modify legend (add title, draw out of diagram and without extra border)
    tikz3.setLegendTitle("My legend title");
    tikz3.setLegendStyle("draw=none");
    tikz3.addAdditionalSettings("legend pos={outer north east}");
    

    
    // add some nodes
    tikz3.addNode(10, -0.5, "nodeA", "myRed", "south");
    tikz3.addNode(40, -0.5, "nodeB", "myGreen", "north");
    
    
    
    // create tikz and pdf file
    tikz3.createTikzPdf("third.tikz");
    
    
    
    
    return 0;
}
