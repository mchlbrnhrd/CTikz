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
#include "CException.hpp"


int main(int argc, const char * argv[]) {
  
  try {
    std::cout << "CTikz example" << std::endl;
    
    // number of samples
    const int N = 100;

    // todo: show latex example files
    
    // ---------------------------------
    // --------- first example ---------
    // ----------------------------------
    std::cout << "run first example (using std::vector)" << std::endl;
    
    // example data x and y are stored in two vectors
    std::vector<double> exampleX;
    std::vector<double> exampleY;
    for (int x=-N/2; x < N/2; ++x) {
      int y = x * x;
      exampleX.push_back(x);
      exampleY.push_back(y);
    }
    CTikz tikz1;
    
    // add data
    tikz1.addData(exampleX, exampleY);
    
    // create tikz and pdf file
    tikz1.createTikzPdf("example1.tikz");
    
    
    // ----------------------------------
    // --------- second example ---------
    // ----------------------------------
    std::cout << "run second example (using C array)" << std::endl;
    
    // example data x and y are stored in two C arrays
    double dataX[N];
    double dataY[N];
    int index = 0;
    for (int x=-N/2; x < N/2; ++x) {
      int y = x * x;
      dataX[index] = x;
      dataY[index] = y;
      index++;
    }
    
    CTikz tikz2;
    
    // add data
    tikz2.addData(dataX, dataY, N);
    
    // create tikz and pdf file
    tikz2.createTikzPdf("example2.tikz");
    
    
    // ----------------------------------
    // --------- third example ----------
    // ----------------------------------
    std::cout << "run third example (using std::vector and two data sets)" << std::endl;
    
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
    
    CTikz tikz3;
    
    // add all data
    tikz3.addData(dataA, "dataA");
    tikz3.addData(dataB, "dataB");
    
    // switch grid on
    tikz3.gridOn();
    
    // set title, x label and y label
    tikz3.setTitle("Third example");
    tikz3.setLabel("x", "y");
    
    // set author and info text for tikz file
    tikz3.setAuthor("Michael Bernhard");
    tikz3.setInfo("some info text for tikz file");
    
    // create tikz and pdf file
    tikz3.createTikzPdf("example3.tikz");
    
    
    
    // ----------------------------------
    // --------- fourth example ---------
    // ----------------------------------
    std::cout << "run fourth example (using std::vector, two data sets and additional settings)" << std::endl;
    
    
    CTikz tikz4;
    
    
    // add all data and specify user defined colors which are defined in your latex document
    // also change linestyle and marker and add comment in tikz file
    gType_TIKZ_DataSet_st l_dataSet_st;
    l_dataSet_st.data = dataA;
    l_dataSet_st.comment = "Comment for data A in tikz file";
    l_dataSet_st.color = "myRed";
    l_dataSet_st.plotStyle = "dashed, mark=square, mark options={solid}, mark repeat=10";
    
    tikz4.addData(l_dataSet_st, "dataA");
    
    l_dataSet_st.data = dataB;
    l_dataSet_st.comment = "Comment for data B in tikz file";
    l_dataSet_st.color = "myBlue";
    l_dataSet_st.plotStyle = "dotted, mark=*, mark options={solid}, mark repeat=10";
    tikz4.addData(l_dataSet_st, "dataB");
    
    // when creating pdf files out from this c++ program, then define the user defined colors
    tikz4.addAdditionalLatexCommands("\\definecolor{myRed}{RGB}{220,30,30}");
    tikz4.addAdditionalLatexCommands("\\definecolor{myGreen}{RGB}{20,200,30}");
    tikz4.addAdditionalLatexCommands("\\definecolor{myBlue}{RGB}{20,30,210}");
    
    // switch grid on
    tikz4.gridOn();
    
    // set title, x label and y label
    tikz4.setTitle("Fourth example");
    // use your own latex abbreviations
    tikz4.setLabel("$\\samplingfrequency$", "$\\snr$");
    
    // when creating pdf files out from this c++ program, then define your latex abbreviations
    tikz4.addAdditionalLatexCommands("\\newcommand{\\samplingfrequency}[0]{f_\\mathrm{S}}");
    tikz4.addAdditionalLatexCommands("\\newcommand{\\snr}[0]{\\gamma}");
    
    // set author and info text for tikz file
    tikz4.setAuthor("Michael Bernhard");
    tikz4.setInfo("some info text for tikz file");
    
    // modify legend (add title, draw out of diagram and without extra border)
    tikz4.setLegendTitle("My legend title");
    tikz4.setLegendStyle("draw=none");
    tikz4.addAdditionalSettings("legend pos={outer north east}");
    
    // add some nodes
    tikz4.addNode(10, -0.5, "nodeA", "myRed", "south");
    tikz4.addNode(40, -0.5, "nodeB", "myGreen", "north");
    
    // create tikz and pdf file
    tikz4.createTikzPdf("example4.tikz");
    
    
  } catch (CException & f_Exception) {
    std::cout << "Exception occured: " << f_Exception.what() << std::endl;
  } catch (std::exception& f_Exception) {
    std::cout << "std::exception occured: " << f_Exception.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception occured." << std::endl;
  }
  
  
  return 0;
}
