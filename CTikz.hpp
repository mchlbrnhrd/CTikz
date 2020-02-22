/*
 * File:   CTikz.hpp
 * Author: Michael Bernhard
 *
 * Created on 18. November 2017
 *
 * Description:
 *   Class to create Tikz files (Tikz ist kein Zeichenprogram) out of C array or data vector.
 *   Pdf preview and latex code can also be generated.
 */

#ifndef CTIKZ_HPP
#define	CTIKZ_HPP

#include <sstream>
#include <string>
#include <vector>
#include <utility>

typedef struct C_TIKZ_DataSetEntry_st
{
  std::vector<std::pair<double, double> > data;
  std::string comment;
  std::string color;
  std::string plotStyle;
} gType_TIKZ_DataSetEntry_st;


class CTikz {
public:
  
  // default constructor
  CTikz();
  
  // copy constructor
  CTikz(const CTikz& orig);
  
  // destructor
  virtual ~CTikz();
  
  // clear all internal values
  void clear();
  
  // set data via C array. size is size of array dataX and dataY.
  // additional: comment, color, plot style and legend entry can be set
  void setData(const double *dataX,
               const double *dataY,
               int size,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  // set data via vector for x and vector for y data
  // additional: comment, color, plot style and legend entry can be set
  void setData(const std::vector<double>& dataX,
               const std::vector<double>& dataY,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  // set data via vector with pair of double (x and y values)
  // additional: comment, color, plot style and legend entry can be set
  void setData(const std::vector<std::pair<double, double> >& data,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  // set data using struct for data set entry
  // additional: legend entry can be set
  void setData(const gType_TIKZ_DataSetEntry_st& f_dataSetEntry_st,
               const std::string& f_legend_s="");
  
  // get data set
  std::vector<gType_TIKZ_DataSetEntry_st> getData() const
  {
    return m_dataSet_vst;
  }
  
  // add data via C array. size is size of array dataX and dataY.
  // additional: comment, color, plot style and legend entry can be set
  void addData(const double *dataX,
               const double *dataY,
               int size,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  // add data via vector for x and vector for y data
  // additional: comment, color, plot style and legend entry can be set
  void addData(const std::vector<double>& dataX,
               const std::vector<double>& dataY,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  // add data via vector with pair of double (x and y values)
  // additional: comment, color, plot style and legend entry can be set
  void addData(const std::vector<std::pair<double, double> >& data,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  // add data using struct for data set entry
  // additional: legend entry can be set
  void addData(const gType_TIKZ_DataSetEntry_st& f_dataSetEntry_st,
               const std::string& f_legend_s="");
  
  // set title of plot
  void setTitle(const std::string& title);
  
  // get title of plot
  std::string getTitle() const
  {
    return m_title;
  };
  
  // set label for x axis of plot
  void setXlabel(const std::string& xlabel);
  
  // get label for x axis of plot
  std::string getXlabel() const
  {
    return m_xlabel;
  };
  
  // set label for y axis of plot
  void setYlabel(const std::string& ylabel);
  
  // get label for y axis of plot
  std::string getYlabel() const
  {
    return m_ylabel;
  }
  
  // set label for x and for y axis of plot
  void setLabel(const std::string& xlabel, const std::string& ylabel);
  
  // set legend of plot
  void setLegend(const std::string& legend);
  
  // get legend of plot
  std::vector<std::string> getLegend() const
  {
    return m_legend;
  };
  
  // add additional legend entry of plot
  void addLegend(const std::string& legend);
  
  // set style of legend of plot
  void setLegendStyle(const std::string& legendStyle);
  
  // get style of legend
  std::string getLegendStyle() const
  {
    return m_legendStyle;
  }
  
  // set title of legend
  void setLegendTitle(const std::string& legendTitle);
  
  // set width of plot
  void setWidth(const std::string& width);
  
  // get width of plot
  std::string getWidth() const
  {
    return m_width;
  }
  
  // set hight of plot
  void setHeight(const std::string& height);
  
  // get height of plot
  std::string getHeight() const
  {
    return m_height;
  }
  
  // set range for x axis of plot
  void setRangeX(double minVal, double maxVal);
  
  // set range for y axis of plot
  void setRangeY(double minVal, double maxVal);
  
  // switch on grid of plot
  void gridOn();
  
  // switch off grid of plot
  void gridOff();
  
  // set on or off log scale of plot for x axis
  void setLogX(bool on = true);
  
  // set on or off log scale of plot for y axis
  void setLogY(bool on = true);
  
  // set additional settings for tikz file
  void setAdditionalSettings(const std::string& settings);
  
  // add additional settings for tikz file
  void addAdditionalSettings(const std::string& settings);
  
  // get additional settings for tikz file
  std::vector<std::string> getAdditionalSettings() const {
    return m_additionalSettings;
  }
  
  // set additional commands for tikz file
  void setAdditionalCommands(const std::string& command);
  
  // add additional commands for tikz file
  void addAdditionalCommands(const std::string& command);
  
  // get additianl commands for tikz file
  std::vector<std::string> getAdditionalCommands() const {
    return m_additionalsCommands;
  }
  
  // set additianl commands which are inserted after beginning of tikz picture
  void setAdditionalCommandsAfterBeginTikzePicture(const std::string& command);
  
  // add additional commands which are inserted after beginning of tikz picture
  void addAdditionalCommandsAfterBeginTikzePicture(const std::string& command);
  
  // get additional commands which are inserted after beginning of tikz picture
  std::vector<std::string> getAdditionalCommandsAfterBeginTikzePicture() const {
    return m_additionalsCommandsAfterBeginTikzPicture;
  }
  
  // add node in plot
  void addNode(double posX,
               double posY,
               const std::string& text,
               const std::string& color="black",
               const std::string& anchor="center",
               double rotate=0,
               const std::string& font="small");
  
  // create tikz file
  void createTikzFile(const std::string& filename);
  
  // create tikz file as histogram graphics
  void createTikzFileHist(const std::string& filename,
                          int bins,
                          double dataMin,
                          double dataMax);
  
  // create tikz file and PDF file as preview with corresponding latex file
  void createTikzPdf(const std::string& filenameTikz);
  
  // create tikz file and PDF file as preview with corresponding latex file
  // graphics is generated as histogram
  void createTikzPdfHist(const std::string& filename, int bins, double dataMin, double dataMax);
  
  // creates tikz code which can used for a second axis in another CTikz object.
  void createSecondAxisCode(std::string & secondAxisCode);
  
  // set code for second axis of plot
  void setSecondAxisCode(const std::string& secondAxisCode);
  
  // set addional cammands which are only used for PDF preview generation, i.e. for latex code
  void setAdditionalLatexCommands(const std::string& additionalLatexCommands);
  
  // add addional cammands which are only used for PDF preview generation, i.e. for latex code
  void addAdditionalLatexCommands(const std::string& additionalLatexCommands);
  
  // set author into tikz file
  void setAuthor(const std::string& author);
  
  // set additional info into tikz file
  void setInfo(const std::string& info);
  
  
private:
  
  // data set means all data
  std::vector<gType_TIKZ_DataSetEntry_st> m_dataSet_vst;
  
  // settings for tikz plot
  std::string m_title; // title of plot
  std::vector<std::string> m_legend; // legend entries of plot
  std::string m_xlabel; // label for x axis
  std::string m_ylabel; // label for y axis
  std::string m_legendStyle; // style of legend
  std::string m_legendTitle; // title of legend
  std::string m_width; // with of plot
  std::string m_height; // hight of plot
  bool m_gridOnX; // grid active in x direction
  bool m_gridOnY; // grid active in y direction
  bool m_logOnX; // log scale of x axis
  bool m_logOnY; // log scale of y axis
  bool m_useAutoRangeX; // auto determined range of x axis
  bool m_useAutoRangeY; // auto determined range of y axis
  double m_userdefinedMinX; // user defined minimum value for x axis
  double m_userdefinedMaxX; // user defined maximum value for x axis
  double m_userdefinedMinY; // user defined minimum value for y axis
  double m_userdefinedMaxY; // user defined maximum value for y axis
 
  std::vector<std::string> m_colorDefault; // keeps default colors
  
  std::vector<std::string> m_additionalSettings; // additional settings for tikz file
  std::vector<std::string> m_additionalsCommands; // additional commands for tikz file
  std::vector<std::string> m_additionalsCommandsAfterBeginTikzPicture; // additional commands for tikz file after beginning of picture
  
  std::string m_secondAxisCode; // code for second axis
  
  std::string m_additionalLatexCommands; // addtional commands for latex
  std::string m_author; // author written into tikz file
  std::string m_info; // info written into tikz file
  std::string m_id; // ID for plots
  
  // create PDF file
  void m_createPdf(const std::string& filenameTikz);
  
  // create tikz file
  void m_createTikzFile(const std::string& filename,
                        bool createHist,
                        int bins = 0,
                        double dataMin = 0,
                        double dataMax = 0);

  // helper functions
  double m_getMinX(); // get minimum x value
  double m_getMaxX(); // get maximum x value
  double m_getMinY(); // get minimum y value
  double m_getMaxY(); // get maximum y value

  std::string m_createId(); // create ID
  
  bool m_fileExist_bl(const std::string& f_filename_s); // check if file exists
  
  std::string m_trimFilename(const std::string& filename); // trim file name
};

#endif	/* CTIKZ_HPP */


