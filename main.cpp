/**
 * @file main.cpp
 * @brief example using CTikz class
 * @author Michael Bernhard
 *
 * Created on 18. November 2017
 *
 * @details Four examples how CTikz class can be used. Make sure latex is installed.
 *
 */

#include <iostream>
#include <vector>
#include "CTikz.hpp"
#include "CException.hpp"

// 1. example uses C array
void m_example1_vd(const int f_NumSamples_i);

// 2. example uses std::vector
void m_example2_vd(const int f_NumSamples_i);

// 3. example uses std::vector and std::pair and two data sets
void m_example3_vd(const int f_NumSamples_i);

// 4. example uses std::vector, std::pair, two data sets
// and additional settings (legend, nodes)
void m_example4_vd(const int f_NumSamples_i);


// ========================================================================
// main function
// ========================================================================
int main(int argc, const char * argv[]) {
  
  try {
    std::cout << "CTikz example" << std::endl;
    
    // number of samples
    const int l_NumSamples_i = 100;

    // run first example
    m_example1_vd(l_NumSamples_i);
    
    // run second example
    m_example2_vd(l_NumSamples_i);
    
    // run third example
    m_example3_vd(l_NumSamples_i);
    
    // run fourth example
    m_example4_vd(l_NumSamples_i);
    
  } catch (CException & f_Exception_c) {
    std::cout << "Exception occured: " << f_Exception_c.what() << std::endl;
  } catch (std::exception& f_Exception_c) {
    std::cout << "std::exception occured: " << f_Exception_c.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception occured." << std::endl;
  }
  
  return 0;
}

// ========================================================================
// 1. example uses C array
// ========================================================================
void m_example1_vd(const int f_NumSamples_i)
{
  std::cout << "run first example (using C array)" << std::endl;
  
  // example data x and y are stored in two C arrays
  double l_dataX_pd[f_NumSamples_i];
  double l_dataY_pd[f_NumSamples_i];
  int l_index_i = 0;
  for (int x=-f_NumSamples_i/2; x < f_NumSamples_i/2; ++x) {
    int y = x * x;
    l_dataX_pd[l_index_i] = x;
    l_dataY_pd[l_index_i] = y;
    ++l_index_i;
  }
  
  CTikz l_tikz_c;
  
  // add data
  l_tikz_c.addData_vd(l_dataX_pd, l_dataY_pd, f_NumSamples_i);
  
  // create tikz and pdf file
  l_tikz_c.createTikzPdf_vd("example1.tikz");
}


// ========================================================================
// 2. example uses std::vector
// ========================================================================
void m_example2_vd(const int f_NumSamples_i)
{
  std::cout << "run second example (using std::vector)" << std::endl;
  
  // example data x and y are stored in two vectors
  std::vector<double> l_exampleX_v;
  std::vector<double> l_exampleY_v;
  for (int x=-f_NumSamples_i/2; x < f_NumSamples_i/2; ++x) {
    int y = x * x;
    l_exampleX_v.push_back(x);
    l_exampleY_v.push_back(y);
  }
  CTikz l_tikz_c;
  
  // add data
  l_tikz_c.addData_vd(l_exampleX_v, l_exampleY_v);
  
  // create tikz and pdf file
  l_tikz_c.createTikzPdf_vd("example2.tikz");
}


// ========================================================================
// 3. example uses std::vector and std::pair and two data sets
// ========================================================================
void m_example3_vd(const int f_NumSamples_i)
{
  std::cout << "run third example (using std::vector and two data sets)" << std::endl;
  
  // data example A are stored into a vector which contains pairs of double for x and y
  std::vector<std::pair<double, double> > l_dataA_v;
  
  // data example B are stored into a vector which contains pairs of double for x and y
  std::vector<std::pair<double, double> > l_dataB_v;
  
  // fill data vectors
  for (int x=-f_NumSamples_i/2; x<f_NumSamples_i/2; ++x) {
    double yA = (double)x*x / (f_NumSamples_i*f_NumSamples_i/4.0);
    double yB = (double)x*x*x / (f_NumSamples_i*f_NumSamples_i*f_NumSamples_i/8.0);
    l_dataA_v.push_back(std::make_pair(x, yA));
    l_dataB_v.push_back(std::make_pair(x, yB));
  }
  
  CTikz l_tikz_c;
  
  // add all data
  l_tikz_c.addData_vd(l_dataA_v, "dataA");
  l_tikz_c.addData_vd(l_dataB_v, "dataB");
  
  // switch grid on
  l_tikz_c.gridOn_vd();
  
  // set title, x label and y label
  l_tikz_c.setTitle_vd("Third example");
  l_tikz_c.setLabel_vd("x", "y");
  
  // set author and info text for tikz file
  l_tikz_c.setAuthor_vd("Michael Bernhard");
  l_tikz_c.setInfo_vd("some info text for tikz file");
  
  // create tikz and pdf file
  l_tikz_c.createTikzPdf_vd("example3.tikz");
}


// ========================================================================
// 4. example uses std::vector, std::pair, two data sets
// and additional settings (legend, nodes)
// ========================================================================
void m_example4_vd(const int f_NumSamples_i)
{
  std::cout << "run fourth example (using std::vector, two data sets and additional settings)" << std::endl;
  
  // data example A are stored into a vector which contains pairs of double for x and y
  std::vector<std::pair<double, double> > l_dataA_v;
  
  // data example B are stored into a vector which contains pairs of double for x and y
  std::vector<std::pair<double, double> > l_dataB_v;
  
  // fill data vectors
  for (int x=-f_NumSamples_i/2; x<f_NumSamples_i/2; ++x) {
    double yA = (double)x*x / (f_NumSamples_i*f_NumSamples_i/4.0);
    double yB = (double)x*x*x / (f_NumSamples_i*f_NumSamples_i*f_NumSamples_i/8.0);
    l_dataA_v.push_back(std::make_pair(x, yA));
    l_dataB_v.push_back(std::make_pair(x, yB));
  }
  
  CTikz l_tikz_c;
  
  // add all data and specify user defined colors which are defined in your latex document
  // also change linestyle and marker and add comment in tikz file
  // define first data set entry
  gType_TIKZ_DataSetEntry_st l_dataSetEntry_st;
  l_dataSetEntry_st.data_v = l_dataA_v;
  l_dataSetEntry_st.comment_s = "Comment for data A in tikz file.";
  l_dataSetEntry_st.color_s = "myRed";
  l_dataSetEntry_st.plotStyle_s = "dashed, mark=square, mark options={solid}, mark repeat=10";
  
  // add first data set entry
  l_tikz_c.addData_vd(l_dataSetEntry_st, "dataA");
  
  // define second data set entry
  l_dataSetEntry_st.data_v = l_dataB_v;
  l_dataSetEntry_st.comment_s = "Comment for data B in tikz file";
  l_dataSetEntry_st.color_s = "myBlue";
  l_dataSetEntry_st.plotStyle_s = "dotted, mark=*, mark options={solid}, mark repeat=10";
  
  // add second data set entry
  l_tikz_c.addData_vd(l_dataSetEntry_st, "dataB");
  
  // when creating pdf files out from this c++ program, then define the user defined colors
  l_tikz_c.addAdditionalLatexCommands_vd("\\definecolor{myRed}{RGB}{220,30,30}");
  l_tikz_c.addAdditionalLatexCommands_vd("\\definecolor{myGreen}{RGB}{20,200,30}");
  l_tikz_c.addAdditionalLatexCommands_vd("\\definecolor{myBlue}{RGB}{20,30,210}");
  
  // switch grid on
  l_tikz_c.gridOn_vd();
  
  // set title,
  l_tikz_c.setTitle_vd("Fourth example");
  
  //  set x label and y label, use your own latex abbreviations
  l_tikz_c.setLabel_vd("$\\samplingfrequency$", "$\\snr$");
  
  // when creating pdf files out from this c++ program, then define your latex abbreviations
  l_tikz_c.addAdditionalLatexCommands_vd("\\newcommand{\\samplingfrequency}[0]{f_\\mathrm{S}}");
  l_tikz_c.addAdditionalLatexCommands_vd("\\newcommand{\\snr}[0]{\\gamma}");
  
  // set author and info text for tikz file
  l_tikz_c.setAuthor_vd("Michael Bernhard");
  l_tikz_c.setInfo_vd("some info text for tikz file");
  
  // modify legend (add title, draw out of diagram and without extra border)
  l_tikz_c.setLegendTitle_vd("My legend title");
  l_tikz_c.setLegendStyle_vd("draw=none");
  l_tikz_c.addAdditionalSettings_vd("legend pos={outer north east}");
  
  // add some nodes
  l_tikz_c.addNode_vd(10, -0.5, "nodeA", "myRed", "south");
  l_tikz_c.addNode_vd(40, -0.5, "nodeB", "myGreen", "north");
  
  // create tikz and pdf file
  l_tikz_c.createTikzPdf_vd("example4.tikz");
}


// ========================================================================
// naming convention
// prefix:
//   l  : local variable
//   f  : function/method variable
//   m  : private member of class
//      : without prefix: public member of class
//
// postfix
//   b  : bool
//   c  : class
//   d  : double
//   f  : float
//   i  : int
//   s  : std::string
//   st : struct
//   ss : std::stringstream
//   v  : vector
//   vd : void
//
//   p  : pointer
//   it : iterator
//
// ========================================================================
