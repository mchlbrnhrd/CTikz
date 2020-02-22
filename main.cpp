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
    const int l_Num_i = 100;

    // todo: show latex example files
    
    // ---------------------------------
    // --------- first example ---------
    // ----------------------------------
    std::cout << "run first example (using std::vector)" << std::endl;
    
    // example data x and y are stored in two vectors
    std::vector<double> l_exampleX_v;
    std::vector<double> l_exampleY_v;
    for (int x=-l_Num_i/2; x < l_Num_i/2; ++x) {
      int y = x * x;
      l_exampleX_v.push_back(x);
      l_exampleY_v.push_back(y);
    }
    CTikz tikz1;
    
    // add data
    tikz1.addData_vd(l_exampleX_v, l_exampleY_v);
    
    // create tikz and pdf file
    tikz1.createTikzPdf_vd("example1.tikz");
    
    
    // ----------------------------------
    // --------- second example ---------
    // ----------------------------------
    std::cout << "run second example (using C array)" << std::endl;
    
    // example data x and y are stored in two C arrays
    double dataX[l_Num_i];
    double dataY[l_Num_i];
    int index = 0;
    for (int x=-l_Num_i/2; x < l_Num_i/2; ++x) {
      int y = x * x;
      dataX[index] = x;
      dataY[index] = y;
      index++;
    }
    
    CTikz tikz2;
    
    // add data
    tikz2.addData_vd(dataX, dataY, l_Num_i);
    
    // create tikz and pdf file
    tikz2.createTikzPdf_vd("example2.tikz");
    
    
    // ----------------------------------
    // --------- third example ----------
    // ----------------------------------
    std::cout << "run third example (using std::vector and two data sets)" << std::endl;
    
    // data example A are stored into a vector which contains pairs of double for x and y
    std::vector<std::pair<double, double> > dataA;
    
    // data example B are stored into a vector which contains pairs of double for x and y
    std::vector<std::pair<double, double> > dataB;
    
    // fill data vectors
    for (int x=-l_Num_i/2; x<l_Num_i/2; ++x) {
      double yA = (double)x*x / (l_Num_i*l_Num_i/4.0);
      double yB = (double)x*x*x / (l_Num_i*l_Num_i*l_Num_i/8.0);
      dataA.push_back(std::make_pair(x, yA));
      dataB.push_back(std::make_pair(x, yB));
    }
    
    CTikz tikz3;
    
    // add all data
    tikz3.addData_vd(dataA, "dataA");
    tikz3.addData_vd(dataB, "dataB");
    
    // switch grid on
    tikz3.gridOn_vd();
    
    // set title, x label and y label
    tikz3.setTitle_vd("Third example");
    tikz3.setLabel_vd("x", "y");
    
    // set author and info text for tikz file
    tikz3.setAuthor_vd("Michael Bernhard");
    tikz3.setInfo_vd("some info text for tikz file");
    
    // create tikz and pdf file
    tikz3.createTikzPdf_vd("example3.tikz");
    
    
    
    // ----------------------------------
    // --------- fourth example ---------
    // ----------------------------------
    std::cout << "run fourth example (using std::vector, two data sets and additional settings)" << std::endl;
    
    
    CTikz tikz4;
    
    
    // add all data and specify user defined colors which are defined in your latex document
    // also change linestyle and marker and add comment in tikz file
    gType_TIKZ_DataSetEntry_st l_dataSetEntry_st;
    l_dataSetEntry_st.data_v = dataA;
    l_dataSetEntry_st.comment_s = "Comment for data A in tikz file";
    l_dataSetEntry_st.color_s = "myRed";
    l_dataSetEntry_st.plotStyle_s = "dashed, mark=square, mark options={solid}, mark repeat=10";
    
    tikz4.addData_vd(l_dataSetEntry_st, "dataA");
    
    l_dataSetEntry_st.data_v = dataB;
    l_dataSetEntry_st.comment_s = "Comment for data B in tikz file";
    l_dataSetEntry_st.color_s = "myBlue";
    l_dataSetEntry_st.plotStyle_s = "dotted, mark=*, mark options={solid}, mark repeat=10";
    tikz4.addData_vd(l_dataSetEntry_st, "dataB");
    
    // when creating pdf files out from this c++ program, then define the user defined colors
    tikz4.addAdditionalLatexCommands_vd("\\definecolor{myRed}{RGB}{220,30,30}");
    tikz4.addAdditionalLatexCommands_vd("\\definecolor{myGreen}{RGB}{20,200,30}");
    tikz4.addAdditionalLatexCommands_vd("\\definecolor{myBlue}{RGB}{20,30,210}");
    
    // switch grid on
    tikz4.gridOn_vd();
    
    // set title, x label and y label
    tikz4.setTitle_vd("Fourth example");
    // use your own latex abbreviations
    tikz4.setLabel_vd("$\\samplingfrequency$", "$\\snr$");
    
    // when creating pdf files out from this c++ program, then define your latex abbreviations
    tikz4.addAdditionalLatexCommands_vd("\\newcommand{\\samplingfrequency}[0]{f_\\mathrm{S}}");
    tikz4.addAdditionalLatexCommands_vd("\\newcommand{\\snr}[0]{\\gamma}");
    
    // set author and info text for tikz file
    tikz4.setAuthor_vd("Michael Bernhard");
    tikz4.setInfo_vd("some info text for tikz file");
    
    // modify legend (add title, draw out of diagram and without extra border)
    tikz4.setLegendTitle_vd("My legend title");
    tikz4.setLegendStyle_vd("draw=none");
    tikz4.addAdditionalSettings_vd("legend pos={outer north east}");
    
    // add some nodes
    tikz4.addNode_vd(10, -0.5, "nodeA", "myRed", "south");
    tikz4.addNode_vd(40, -0.5, "nodeB", "myGreen", "north");
    
    // create tikz and pdf file
    tikz4.createTikzPdf_vd("example4.tikz");
    
    
  } catch (CException & f_Exception_c) {
    std::cout << "Exception occured: " << f_Exception_c.what() << std::endl;
  } catch (std::exception& f_Exception_c) {
    std::cout << "std::exception occured: " << f_Exception_c.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception occured." << std::endl;
  }
  
  
  return 0;
}
