/*
 * File:   CTikz.hpp
 * Author: Michael Bernhard
 *
 * Created on 18. November 2017
 */

#ifndef CTIKZ_HPP
#define	CTIKZ_HPP

#include <sstream>
#include <string>
#include <vector>
#include <utility>

typedef struct C_TIKZ_DataSet_st
{
  std::vector<std::pair<double, double> > data;
  std::string comment;
  std::string color;
  std::string plotStyle;
} gType_TIKZ_DataSet_st;

class CTikz {
public:
    CTikz();
    CTikz(const CTikz& orig);
    virtual ~CTikz();
    void clear();
  
    void setTitle(const std::string& title);
    std::string getTitle() const {
        return m_title;
    };
    
    void setLegend(const std::string& legend);
    std::vector<std::string> getLegend() const {
        return m_legend;
    };
    void addLegend(const std::string& legend);
    
    void setXlabel(const std::string& xlabel);
    std::string getXlabel() const {
        return m_xlabel;
    };
    
    void setYlabel(const std::string& ylabel);
    std::string getYlabel() const {
        return m_ylabel;
    }
    void setLabel(const std::string& xlabel, const std::string& ylabel);
  
  // set data
  // set data via C array. size is size of array dataX and dataY.
  void setData(const double *dataX,
               const double *dataY,
               int size,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  
    void setData(const std::vector<std::pair<double, double> >& data,
                 const std::string& f_comment_s="",
                 const std::string& f_color_s="",
                 const std::string& f_plotStype_s="",
                 const std::string& f_legend_s="");
  
  void setData(const std::vector<double>& dataX,
               const std::vector<double>& dataY,
               const std::string& f_comment_s="",
               const std::string& f_color_s="",
               const std::string& f_plotStype_s="",
               const std::string& f_legend_s="");
  
  void setData(const gType_TIKZ_DataSet_st& f_dataSet_st,
               const std::string& f_legend_s="");
  
  std::vector<gType_TIKZ_DataSet_st> getData() const {
    return m_dataSet_vst;
  }
  
  
    
    // add data via c array. size is size of array dataX and dataY.
    void addData(const double *dataX,
                 const double *dataY,
                 int size,
                 const std::string& f_comment_s="",
                 const std::string& f_color_s="",
                 const std::string& f_plotStype_s="",
                 const std::string& f_legend_s="");
        
    void addData(const std::vector<std::pair<double, double> >& data,
                 const std::string& f_comment_s="",
                 const std::string& f_color_s="",
                 const std::string& f_plotStype_s="",
                 const std::string& f_legend_s="");
  
    void addData(const std::vector<double>& dataX,
                 const std::vector<double>& dataY,
                 const std::string& f_comment_s="",
                 const std::string& f_color_s="",
                 const std::string& f_plotStype_s="",
                 const std::string& f_legend_s="");
  
  
  void addData(const gType_TIKZ_DataSet_st& f_dataSet_st,
               const std::string& f_legend_s="");
  
    
    void setLegendStyle(const std::string& legendStyle);
  
    std::string getLegendStyle() const {
        return m_legendStyle;
    }
    
    void setWidth(const std::string& width);
  
    std::string getWidth() const {
        return m_width;
    }
    
    void setHeight(const std::string& height);
  
    std::string getHeight() const {
        return m_height;
    }
  
  void setAdditionalSettings(const std::string& settings);
  void addAdditionalSettings(const std::string& settings);
  std::vector<std::string> getAdditionalSettings() const {
    return m_additionalSettings;
  }

  
  void setAdditionalCommands(const std::string& command);
  void addAdditionalCommands(const std::string& command);
  std::vector<std::string> getAdditionalCommands() const {
    return m_additionalsCommands;
  }

    
    void setAdditionalCommandsAfterBeginTikzePicture(const std::string& command);
    void addAdditionalCommandsAfterBeginTikzePicture(const std::string& command);
    std::vector<std::string> getAdditionalCommandsAfterBeginTikzePicture() const {
        return m_additionalsCommandsAfterBeginTikzPicture;
    }
    
    void addDataComment(const std::string& dataComment);
    
    void addNode(double posX, double posY, const std::string& text, const std::string& color="black", const std::string& anchor="center", double rotate=0, const std::string& font="small");
    
    void createTikzFile(const std::string& filename);
    void createTikzFileHist(const std::string& filename, int bins, double dataMin, double dataMax);
    
    void createTikzPdf(const std::string& filenameTikz);
    void createTikzPdfHist(const std::string& filename, int bins, double dataMin, double dataMax);
    
    void setRangeX(double minVal, double maxVal);
    void setRangeY(double minVal, double maxVal);
    
    void gridOn();
    void gridOff();
    
    void setLogX(bool on = true);
    void setLogY(bool on = true);
    
    // creates tikz-code which can used for a second axis in another CTikz object.
    void createSecondAxisCode(std::string & secondAxisCode);
    void setSecondAxisCode(const std::string& secondAxisCode);
    
    void setAdditionalLatexCommands(const std::string& additionalLatexCommands);
    void addAdditionalLatexCommands(const std::string& additionalLatexCommands);
    void setAuthor(const std::string& author);
    void setInfo(const std::string& info);
    
  void setLegendTitle(const std::string& legendTitle);
    
  
    
    
private: 
    // settings for tikz plot
    std::string m_title;
    std::vector<std::string> m_legend;
    std::string m_xlabel;
    std::string m_ylabel;
    std::string m_legendStyle;
    std::string m_legendTitle;
    std::string m_width;
    std::string m_height;
  
  std::vector<gType_TIKZ_DataSet_st> m_dataSet_vst;
  
  void m_setColorForNextDataSet(const std::string& color);
    // data
  /*  std::vector<std::vector<std::pair<double, double> > > m_data;
    std::vector<std::string> m_dataComment;
    std::vector<std::vector<double> > m_matrixData;
  */
    void m_createPdf(const std::string& filenameTikz);
    void m_createTikzFile(const std::string& filename,
                          bool createHist,
                          int bins = 0,
                          double dataMin = 0,
                          double dataMax = 0);
  std::string m_trimFilename(const std::string& filename);
  bool m_fileExist_bl(const std::string& f_filename_s);
  
  // helper functions
    double m_getMinX();
    double m_getMaxX();
    double m_getMinY();
    double m_getMaxY();
  
  
    bool m_useAutoRangeX;
    bool m_useAutoRangeY;  
    double m_userdefinedMinX;
    double m_userdefinedMaxX;
    double m_userdefinedMinY;
    double m_userdefinedMaxY;
  
    
    double m_gridOnX;
    double m_gridOnY;
    
    double m_logOnX;
    double m_logOnY;
  
    // some default colors
    std::vector<std::string> m_colorDefault;
   /* std::vector<std::string> m_color;
    std::vector<std::string> m_colorDefault;
    
    std::vector<std::string> m_addPlotStyle;
    */
    std::vector<std::string> m_additionalSettings;
    std::vector<std::string> m_additionalsCommands;
    std::vector<std::string> m_additionalsCommandsAfterBeginTikzPicture;
  
    std::string m_secondAxisCode;
    
    std::string m_additionalLatexCommands;
    std::string m_author;
    std::string m_info;
    std::string m_id;
    
    std::string m_createId();
};

#endif	/* CTIKZ_HPP */

 
