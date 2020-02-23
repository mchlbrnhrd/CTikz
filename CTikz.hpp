/**
 * @file CTikz.hpp
 * @brief CTikz class
 * @author Michael Bernhard
 *
 * Created on 18. November 2017
 *
 * @details Class to create Tikz files (Tikz ist kein Zeichenprogram) out of C array or data vector.
 *   Pdf preview and latex code can also be generated.
 *
 */


#ifndef CTIKZ_HPP
#define	CTIKZ_HPP

#include <sstream>
#include <string>
#include <vector>
#include <utility>

typedef struct C_TIKZ_DataSetEntry_st
{
  std::vector<std::pair<double, double> > data_v;
  std::string comment_s;
  std::string color_s;
  std::string plotStyle_s;
} gType_TIKZ_DataSetEntry_st;


class CTikz {
public:
  
  // default constructor
  CTikz();
  
  // copy constructor
  CTikz(const CTikz& f_orig_c);
  
  // destructor
  virtual ~CTikz();
  
  // clear all internal values
  void clear_vd();
  
  // set data via C array. size is size of array dataX and dataY.
  // additional: comment, color, plot style and legend entry can be set
  void setData_vd(const double *f_dataX_pd,
                  const double *f_dataY_pd,
                  int f_size_i,
                  const std::string& f_comment_s="",
                  const std::string& f_color_s="",
                  const std::string& f_plotStyle_s="",
                  const std::string& f_legend_s="");
  
  // set data via vector for x and vector for y data
  // additional: comment, color, plot style and legend entry can be set
  void setData_vd(const std::vector<double>& f_dataX_v,
                  const std::vector<double>& f_dataY_v,
                  const std::string& f_comment_s="",
                  const std::string& f_color_s="",
                  const std::string& f_plotStyle_s="",
                  const std::string& f_legend_s="");
  
  // set data via vector with pair of double (x and y values)
  // additional: comment, color, plot style and legend entry can be set
  void setData_vd(const std::vector<std::pair<double, double> >& f_data_v,
                  const std::string& f_comment_s="",
                  const std::string& f_color_s="",
                  const std::string& f_plotStyle_s="",
                  const std::string& f_legend_s="");
  
  // set data using struct for data set entry
  // additional: legend entry can be set
  void setData_vd(const gType_TIKZ_DataSetEntry_st& f_dataSetEntry_st,
                  const std::string& f_legend_s="");
  
  // get data set
  std::vector<gType_TIKZ_DataSetEntry_st> v_getData() const
  {
    return m_dataSet_v;
  }
  
  // add data via C array. size is size of array dataX and dataY.
  // additional: comment, color, plot style and legend entry can be set
  void addData_vd(const double *f_dataX_pd,
                  const double *f_dataY_pd,
                  int f_size_i,
                  const std::string& f_comment_s="",
                  const std::string& f_color_s="",
                  const std::string& f_plotStyle_s="",
                  const std::string& f_legend_s="");
  
  // add data via vector for x and vector for y data
  // additional: comment, color, plot style and legend entry can be set
  void addData_vd(const std::vector<double>& f_dataX_v,
                  const std::vector<double>& f_dataY_v,
                  const std::string& f_comment_s="",
                  const std::string& f_color_s="",
                  const std::string& f_plotStyle_s="",
                  const std::string& f_legend_s="");
  
  // add data via vector with pair of double (x and y values)
  // additional: comment, color, plot style and legend entry can be set
  void addData_vd(const std::vector<std::pair<double, double> >& f_data_v,
                  const std::string& f_comment_s="",
                  const std::string& f_color_s="",
                  const std::string& f_plotStyle_s="",
                  const std::string& f_legend_s="");
  
  // add data using struct for data set entry
  // additional: legend entry can be set
  void addData_vd(const gType_TIKZ_DataSetEntry_st& f_dataSetEntry_st,
                  const std::string& f_legend_s="");
  
  // set title of plot
  void setTitle_vd(const std::string& f_title_s);
  
  // get title of plot
  std::string getTitle_s() const
  {
    return m_title_s;
  };
  
  // set label for x axis of plot
  void setXlabel_vd(const std::string& f_xLabel_s);
  
  // get label for x axis of plot
  std::string getXlabel_s() const
  {
    return m_xLabel_s;
  };
  
  // set label for y axis of plot
  void setYlabel_vd(const std::string& f_yLabel_s);
  
  // get label for y axis of plot
  std::string getYlabel_s() const
  {
    return m_yLabel_s;
  }
  
  // set label for x and for y axis of plot
  void setLabel_vd(const std::string& f_xLabel_s,
                   const std::string& f_yLabel_s);
  
  // set legend of plot
  void setLegend_vd(const std::string& f_legend_s);
  
  // get legend of plot
  std::vector<std::string> getLegend_v() const
  {
    return m_legend_v;
  };
  
  // add additional legend entry of plot
  void addLegend_vd(const std::string& f_legend_s);
  
  // set style of legend of plot
  void setLegendStyle_vd(const std::string& f_legendStyle_s);
  
  // get style of legend
  std::string getLegendStyle_s() const
  {
    return m_legendStyle_s;
  }
  
  // set title of legend
  void setLegendTitle_vd(const std::string& f_legendTitle_s);
  
  // set width of plot
  void setWidth_vd(const std::string& f_width_s);
  
  // get width of plot
  std::string getWidth_s() const
  {
    return m_width_s;
  }
  
  // set hight of plot
  void setHeight_vd(const std::string& f_height_s);
  
  // get height of plot
  std::string getHeight_s() const
  {
    return m_height_s;
  }
  
  // set range for x axis of plot
  void setRangeX_vd(double f_minVal_d, double f_maxVal_d);
  
  // set range for y axis of plot
  void setRangeY_vd(double f_minVal_d, double f_maxVal_d);
  
  // switch on grid of plot
  void gridOn_vd();
  
  // switch off grid of plot
  void gridOff_vd();
  
  // set on or off log scale of plot for x axis
  void setLogX_vd(bool f_on_b = true);
  
  // set on or off log scale of plot for y axis
  void setLogY_vd(bool b_on_b = true);
  
  // set additional settings for tikz file
  void setAdditionalSettings_vd(const std::string& f_settings_s);
  
  // add additional settings for tikz file
  void addAdditionalSettings_vd(const std::string& f_settings_s);
  
  // get additional settings for tikz file
  std::vector<std::string> getAdditionalSettings_v() const {
    return m_additionalSettings_v;
  }
  
  // set additional commands for tikz file
  void setAdditionalCommands_vd(const std::string& f_command_s);
  
  // add additional commands for tikz file
  void addAdditionalCommands_vd(const std::string& f_command_s);
  
  // get additianl commands for tikz file
  std::vector<std::string> getAdditionalCommands_v() const {
    return m_additionalsCommands_v;
  }
  
  // set additianl commands which are inserted after beginning of tikz picture
  void setAdditionalCommandsAfterBeginTikzePicture_vd(const std::string& f_command_s);
  
  // add additional commands which are inserted after beginning of tikz picture
  void addAdditionalCommandsAfterBeginTikzePicture_vd(const std::string& f_command_s);
  
  // get additional commands which are inserted after beginning of tikz picture
  std::vector<std::string> getAdditionalCommandsAfterBeginTikzePicture_v() const {
    return m_additionalsCommandsAfterBeginTikzPicture_v;
  }
  
  // add node in plot
  void addNode_vd(double f_posX_d,
                  double f_posY_d,
                  const std::string& f_text_s,
                  const std::string& f_color_s="black",
                  const std::string& f_anchor_s="center",
                  double f_rotate_d=0,
                  const std::string& f_font_s="small");
  
  // create tikz file
  void createTikzFile_vd(const std::string& f_filename_s);
  
  // create tikz file as histogram graphics
  void createTikzFileHist_vd(const std::string& f_filename_s,
                             int f_bins_i,
                             double f_dataMin_d,
                             double f_dataMax_d);
  
  // create tikz file and PDF file as preview with corresponding latex file
  void createTikzPdf_vd(const std::string& f_filenameTikz_s);
  
  // create tikz file and PDF file as preview with corresponding latex file
  // graphics is generated as histogram
  void createTikzPdfHist_vd(const std::string& f_filename_s,
                            int f_bins_i,
                            double f_dataMin_d,
                            double f_dataMax_d);
  
  // creates tikz code which can used for a second axis in another CTikz object.
  void createSecondAxisCode_vd(std::string& f_secondAxisCode_s);
  
  // set code for second axis of plot
  void setSecondAxisCode_vd(const std::string& f_secondAxisCode_s);
  
  // set addional cammands which are only used for PDF preview generation, i.e. for latex code
  void setAdditionalLatexCommands_vd(const std::string& f_additionalLatexCommands_s);
  
  // add addional cammands which are only used for PDF preview generation, i.e. for latex code
  void addAdditionalLatexCommands_vd(const std::string& f_additionalLatexCommands_s);
  
  // set author into tikz file
  void setAuthor_vd(const std::string& f_author_s);
  
  // set additional info into tikz file
  void setInfo_vd(const std::string& f_info_s);
  
  
private:
  
  // data set means all data
  std::vector<gType_TIKZ_DataSetEntry_st> m_dataSet_v;
  
  // settings for tikz plot
  std::string m_title_s; // title of plot
  std::vector<std::string> m_legend_v; // legend entries of plot
  std::string m_xLabel_s; // label for x axis
  std::string m_yLabel_s; // label for y axis
  std::string m_legendStyle_s; // style of legend
  std::string m_legendTitle_s; // title of legend
  std::string m_width_s; // with of plot
  std::string m_height_s; // hight of plot
  bool m_gridOnX_b; // grid active in x direction
  bool m_gridOnY_b; // grid active in y direction
  bool m_logOnX_b; // log scale of x axis
  bool m_logOnY_b; // log scale of y axis
  bool m_useAutoRangeX_b; // auto determined range of x axis
  bool m_useAutoRangeY_b; // auto determined range of y axis
  double m_userdefinedMinX_d; // user defined minimum value for x axis
  double m_userdefinedMaxX_d; // user defined maximum value for x axis
  double m_userdefinedMinY_d; // user defined minimum value for y axis
  double m_userdefinedMaxY_d; // user defined maximum value for y axis
 
  std::vector<std::string> m_colorDefault_v; // keeps default colors
  
  std::vector<std::string> m_additionalSettings_v; // additional settings for tikz file
  std::vector<std::string> m_additionalsCommands_v; // additional commands for tikz file
  std::vector<std::string> m_additionalsCommandsAfterBeginTikzPicture_v; // additional commands for tikz file after beginning of picture
  
  std::string m_secondAxisCode_s; // code for second axis
  
  std::string m_additionalLatexCommands_s; // addtional commands for latex
  std::string m_author_s; // author written into tikz file
  std::string m_info_s; // info written into tikz file
  std::string m_id_s; // ID for plots
  
  // create PDF file
  void m_createPdf_vd(const std::string& f_filenameTikz_s);
  
  // create tikz file
  void m_createTikzFile_vd(const std::string& f_filename_s,
                           bool f_createHist_b,
                           int f_bins_i = 0,
                           double f_dataMin_d = 0,
                           double f_dataMax_d = 0);

  // helper functions
  double m_getMinX_d(); // get minimum x value
  double m_getMaxX_d(); // get maximum x value
  double m_getMinY_d(); // get minimum y value
  double m_getMaxY_d(); // get maximum y value

  std::string m_createId_s(); // create ID
  
  bool m_fileExist_b(const std::string& f_filename_s); // check if file exists
  
  std::string m_trimFilename_s(const std::string& f_filename_s); // trim file name
};

#endif	/* CTIKZ_HPP */

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
