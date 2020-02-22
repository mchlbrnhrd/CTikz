/* 
 * File:   CTikz.cpp
 * Author: Michael Bernhard
 *
 * Created on 18. November 2017
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "CTikz.hpp"
#include "CException.hpp"

// constructor
CTikz::CTikz() {
  clear();
}

// copy constructor
CTikz::CTikz(const CTikz& orig) {
}

// destructor
CTikz::~CTikz() {
}


// clear
void CTikz::clear() {
  m_title = "";
  m_legend.clear();
  m_xlabel = "";
  m_ylabel = "";
  m_legendStyle = "draw=black,fill=white, legend cell align=left";
  m_width =  "10cm";
  m_height = "6cm";
  m_dataSet_vst.clear();
 // m_matrixData.clear();
  m_useAutoRangeX = true;
  m_useAutoRangeY = true;
  m_userdefinedMinX = 0;
  m_userdefinedMaxX = 0;
  m_userdefinedMinX = 0;
  m_userdefinedMaxY = 0;
  m_gridOnX = false;
  m_gridOnY = false;
  m_logOnX = false;
  m_logOnY = false;
  m_additionalsCommands.clear();
  m_additionalsCommandsAfterBeginTikzPicture.clear();
  m_secondAxisCode = "";
  m_additionalLatexCommands = "";
  m_author = "";
  m_info = "";
  m_id = m_createId();
  m_legendTitle = "";
  
  m_dataSet_vst.clear();
  
  // set some default colors
  m_colorDefault.clear();
  m_colorDefault.push_back("ctikzColorBlue");
  m_colorDefault.push_back("ctikzColorRed");
  m_colorDefault.push_back("ctikzColorGreen");
  m_colorDefault.push_back("ctikzColorYellow");
}

void CTikz::setTitle(const std::string& title) {
  m_title = title;
}

void CTikz::setLegend(const std::string& legend) {
  m_legend.clear();
  addLegend(legend);
}

void CTikz::addLegend(const std::string& legend) {
  if ("" != legend) {
    m_legend.push_back(legend);
  }
}

void CTikz::setXlabel(const std::string& xlabel) {
  m_xlabel = xlabel;
}

void CTikz::setYlabel(const std::string& ylabel) {
  m_ylabel = ylabel;
}

void CTikz::setLabel(const std::string& xlabel, const std::string& ylabel) {
  setXlabel(xlabel);
  setYlabel(ylabel);
}

// set data via C array. size is size of array dataX and dataY.
void CTikz::setData(
                    const double *dataX,
                    const double *dataY,
                    int size,
                    const std::string& f_comment_s,
                    const std::string& f_color_s,
                    const std::string& f_plotStype_s,
                    const std::string& f_legend_s) {
  m_dataSet_vst.clear();
  m_legend.clear();
  addData(dataX, dataY, size, f_comment_s, f_color_s, f_plotStype_s, f_legend_s);
}

void CTikz::setData(const std::vector<std::pair<double, double> >& data,
                    const std::string& f_comment_s,
                    const std::string& f_color_s,
                    const std::string& f_plotStype_s,
                    const std::string& f_legend_s) {
  m_dataSet_vst.clear();
  m_legend.clear();
  addData(data, f_comment_s, f_color_s, f_plotStype_s, f_legend_s);
}

void CTikz::setData(const std::vector<double>& dataX,
                    const std::vector<double>& dataY,
                    const std::string& f_comment_s,
                    const std::string& f_color_s,
                    const std::string& f_plotStype_s,
                    const std::string& f_legend_s) {
  m_dataSet_vst.clear();
  m_legend.clear();
  addData(dataX, dataY, f_comment_s, f_color_s, f_plotStype_s, f_legend_s);
}


void CTikz::setData(const gType_TIKZ_DataSet_st& f_dataSet_st,
             const std::string& f_legend_s)
{
  m_dataSet_vst.clear();
  m_dataSet_vst.push_back(f_dataSet_st);
  m_legend.clear();
  addLegend(f_legend_s);
}


void CTikz::addData(const std::vector<std::pair<double, double> >& data,
                    const std::string& f_comment_s,
                    const std::string& f_color_s,
                    const std::string& f_plotStype_s,
                    const std::string& f_legend_s)
{
  if (data.empty()) {
    throw CException("Empty data set.");
  } else {
    gType_TIKZ_DataSet_st l_dataSet_st;
    l_dataSet_st.data = data;
    l_dataSet_st.comment = f_comment_s;
    // default plot style is "solid"
    l_dataSet_st.plotStyle=(f_plotStype_s == "") ? "solid" : f_plotStype_s;

    // when no color is given then use color from default list or black
    if ("" == f_color_s) {
      if (!m_colorDefault.empty()) {
        l_dataSet_st.color = m_colorDefault.front();
        m_colorDefault.erase(m_colorDefault.begin());
      } else {
        l_dataSet_st.color = "black";
      }
    } else {
      l_dataSet_st.color = f_color_s;
    }
    
    m_dataSet_vst.push_back(l_dataSet_st);
    addLegend(f_legend_s);
  }
}

// add data via C array. size is size of array dataX and dataY.
void CTikz::addData(const double *dataX,
                    const double *dataY,
                    int size,
                    const std::string& f_comment_s,
                    const std::string& f_color_s,
                    const std::string& f_plotStype_s,
                    const std::string& f_legend_s) {
  if ((0 == dataX) || (0 == dataY)) {
    throw CException("Null pointer");
  }
  else
  {
    std::vector<std::pair<double, double> > tmp;
    for (int k = 0; k < size; ++k) {
      std::pair<double, double> dataEntry = std::make_pair(*dataX, *dataY);
      tmp.push_back(dataEntry);
      dataX++;
      dataY++;
    }
    addData(tmp, f_comment_s, f_color_s, f_plotStype_s, f_legend_s);
  }
}


void CTikz::addData(const std::vector<double>& dataX,
                    const std::vector<double>& dataY,
                    const std::string& f_comment_s,
                    const std::string& f_color_s,
                    const std::string& f_plotStype_s,
                    const std::string& f_legend_s) {
  std::vector<std::pair<double, double> > tmp;
  if (dataX.size() != dataY.size()) {
    std::stringstream msg;
    msg << "Data sizes must be the same. dataX.size()=" << dataX.size() << ", dataY.size()=" << dataY.size() << std::endl;
    throw CException(msg);
  } else {
    for (size_t k = 0; k < dataX.size(); ++k) {
      std::pair<double, double> dataEntry = std::make_pair(dataX.at(k), dataY.at(k));
      tmp.push_back(dataEntry);
    }
  }
  addData(tmp, f_comment_s, f_color_s, f_plotStype_s, f_legend_s);
}

void CTikz::addData(const gType_TIKZ_DataSet_st& f_dataSet_st,
                    const std::string& f_legend_s)
{
  m_dataSet_vst.push_back(f_dataSet_st);
  addLegend(f_legend_s);
}


void CTikz::setLegendStyle(const std::string& legendStyle) {
  m_legendStyle = legendStyle;
}

void CTikz::setWidth(const std::string& width) {
  m_width = width;
}

void CTikz::setHeight(const std::string& height) {
  m_height = height;
}

void CTikz::createTikzFile(const std::string& filename) {
  const bool l_createHist_bl = false;
  m_createTikzFile(filename, l_createHist_bl);
}

void CTikz::createTikzFileHist(const std::string& filename, int bins, double dataMin, double dataMax) {
  const bool l_createHist_bl = true;
  m_createTikzFile(filename, l_createHist_bl, bins, dataMin, dataMax);
}

void CTikz::m_createTikzFile(const std::string& filename,
                           bool createHist,
                           int bins /* = 0 */,
                           double dataMin /* = 0 */ ,
                           double dataMax /* = 0 */)
{
  if (m_fileExist_bl(filename)) {
    std::stringstream l_Msg_ss;
    l_Msg_ss << "File \"" << filename << "\" already exists.";
    throw CException(l_Msg_ss.str());
  }
  std::stringstream ss;
  ss << "% file automatically generated by CTikz" << std::endl;
  ss << "% author: " << m_author << std::endl;
  ss << "% " << std::endl;
  ss << "% info: " << m_info << std::endl;
  ss << "% " << std::endl;
  ss << "\\begin{tikzpicture}" << std::endl;
  for (std::vector<std::string>::iterator it = m_additionalsCommandsAfterBeginTikzPicture.begin(); it != m_additionalsCommandsAfterBeginTikzPicture.end(); ++it) {
    ss << *it << std::endl;
  }
  ss << "\\begin{axis}[" << std::endl;
  ss << ">=latex," << std::endl;
  ss << "width=" << m_width << "," << std::endl;
  ss << "height=" << m_height << "," << std::endl;
  ss << "scale only axis," << std::endl;
  ss << "xmin=" << m_getMinX() << "," << std::endl;
  ss << "xmax=" << m_getMaxX() << "," << std::endl;
  ss << "xlabel={" << m_xlabel << "}," << std::endl;
  if (m_gridOnX) {
    ss << "xmajorgrids," << std::endl;
  }
  if (m_logOnX) {
    ss << "xmode=log,log basis x=10," << std::endl;
  }
  if (!createHist) { // normal mode
      ss << "ymin=" << m_getMinY() << "," << std::endl;
      ss << "ymax=" << m_getMaxY() << "," << std::endl;
  }
  ss << "ylabel={" << m_ylabel << "}," << std::endl;
  if (createHist) { // histogram mode
    ss << "ymin=0," << std::endl;
    ss << "ybar," << std::endl;
  }
  if (m_gridOnY) {
    ss << "ymajorgrids," << std::endl;
  }
  if (m_logOnY) {
    ss << "ymode=log,log basis y=10," << std::endl;
  }
  ss << "title={" << m_title << "}," << std::endl;
  for (std::vector<std::string>::const_iterator settings = m_additionalSettings.begin();
       settings != m_additionalSettings.end(); ++settings) {
    ss << *settings << "," << std::endl;
  }
  ss << "legend style={" << m_legendStyle << "}" << std::endl;
  ss << "]" << std::endl;
  if (m_legendTitle != "") {
    ss << "\\addlegendimage{empty legend}" << std::endl;
  }
  bool legendTitleSet = false;
  int l_legendIdx_i = 0;
  int l_IdCtr_i = 0;
  for (std::vector<gType_TIKZ_DataSet_st>::const_iterator dataSet = m_dataSet_vst.begin(); dataSet != m_dataSet_vst.end(); ++dataSet) {
      if (!createHist) { // normal mode
        ss << "\\addplot [color=" << dataSet->color << ",";
      } else { // histogram mode
        ss << "\\addplot+ [color=" << dataSet->color << ",";
        ss << " ,hist={" << std::endl;
        ss << "    density," << std::endl;
        ss << "    bins=" << bins << "," << std::endl;
        ss << "    data min=" << dataMin << "," << std::endl;
        ss << "    data max=" << dataMax << std::endl;
        ss << " },";
      }
      ss << dataSet->plotStyle << "]" << std::endl;
      if ("" != dataSet->comment) {
        ss << "% " << dataSet->comment << std::endl;
      }
      ss << "  table[row sep=crcr]{%" << std::endl;
      for (std::vector<std::pair<double, double> >::const_iterator data = dataSet->data.begin();
           data != dataSet->data.end();
           ++data) {
        ss << data->first << "\t" << data->second << "\\\\" << std::endl;
      }
      ss << "};" << std::endl;
      ss << "\\label{addPlotLabel_" << m_id << "_" << l_IdCtr_i++ << "}" << std::endl;
      if (m_legendTitle != "" && !legendTitleSet) {
        ss << "\\addlegendentry{\\hspace{-.6cm}" << m_legendTitle << "};" << std::endl;
        legendTitleSet = true;
      }
      if (l_legendIdx_i < m_legend.size()) {
        ss << "\\addlegendentry{" << m_legend.at(l_legendIdx_i) << "};" << std::endl;
        ++l_legendIdx_i;
      }
    }

  ss << std::endl;
  for (std::vector<std::string>::iterator commands = m_additionalsCommands.begin(); commands != m_additionalsCommands.end(); ++commands) {
    ss << *commands << std::endl;
  }
  ss << std::endl;
  ss << "\\end{axis}" << std::endl;
  // insert second axis
  ss << m_secondAxisCode;
  ss << "\\end{tikzpicture}%" << std::endl;
  
  std::ofstream ofs;
  ofs.open(filename.c_str());
  if (ofs) {
    ofs << ss.str();
  }
  ofs.close();
  
}


void CTikz::createSecondAxisCode(std::string &secondAxisCode) {
  std::stringstream ss;
  ss << "\\begin{axis}[" << std::endl;
  ss << "yticklabel pos=right," << std::endl;
  ss << "xtick=\\empty," << std::endl;
  ss << "axis y line=right," << std::endl;
  ss << "y axis line style=-," << std::endl;
  ss << "width=" << m_width << "," << std::endl;
  ss << "height=" << m_height << "," << std::endl;
  ss << "scale only axis," << std::endl;
  ss << "xmin=" << m_getMinX() << "," << std::endl;
  ss << "xmax=" << m_getMaxX() << "," << std::endl;
  ss << "ylabel={" << m_ylabel << "}," << std::endl;
  if (m_gridOnX) ss << "xmajorgrids," << std::endl;
  if (m_logOnX) ss << "xmode=log,log basis x=10," << std::endl;
  ss << "ymin=" << m_getMinY() << "," << std::endl;
  ss << "ymax=" << m_getMaxY() << "," << std::endl;
  if (m_gridOnY) ss << "ymajorgrids," << std::endl;
  if (m_logOnY) ss << "ymode=log,log basis y=10," << std::endl;
  for (std::vector<std::string>::const_iterator settings = m_additionalSettings.begin();
       settings != m_additionalSettings.end(); ++settings) {
    ss << *settings << "," << std::endl;
  }
  ss << "legend style={" << m_legendStyle << "}" << std::endl;
  ss << "]" << std::endl;
  for (std::size_t k=0; k < m_legend.size() - m_dataSet_vst.size(); ++k) {
    ss << "\\addlegendimage{/pgfplots/refstyle=addPlotLabel_" << m_id << "_" << k << "}" << std::endl;
    ss << "\\addlegendentry{" << m_legend.at(k) << "};" << std::endl;
  }
  std::size_t l_legendIdx_i = m_dataSet_vst.size();
  for (std::vector<gType_TIKZ_DataSet_st>::const_iterator dataSet = m_dataSet_vst.begin(); dataSet != m_dataSet_vst.end(); ++dataSet) {
    ss << "\\addplot [color=" << dataSet->color<< "," << dataSet->plotStyle << "]" << std::endl;
    ss << "  table[row sep=crcr]{%" << std::endl;
    for (std::vector<std::pair<double, double> >::const_iterator data = dataSet->data.begin();
         data != dataSet->data.end();
         ++data) {
      ss << data->first << "\t" << data->second << "\\\\" << std::endl;
    }
    ss << "};" << std::endl;
    if (l_legendIdx_i < m_legend.size()) {
      ss << "\\addlegendentry{" << m_legend.at(l_legendIdx_i) << "};" << std::endl;
      ++l_legendIdx_i;
    }
  }
  ss << std::endl;
  for (std::vector<std::string>::iterator command = m_additionalsCommands.begin(); command != m_additionalsCommands.end(); ++command) {
    ss << *command << std::endl;
  }
  ss << std::endl;
  ss << "\\end{axis}" << std::endl;
  secondAxisCode = ss.str();
}

void CTikz::createTikzPdf(const std::string& filenameTikz) {
  createTikzFile(filenameTikz);
  
  m_createPdf(filenameTikz);
}

void CTikz::createTikzPdfHist(const std::string& filenameTikz, int bins, double dataMin, double dataMax) {
  createTikzFileHist(filenameTikz, bins, dataMin, dataMax);
  
  m_createPdf(filenameTikz);
}

void CTikz::m_createPdf(const std::string& filenameTikz)
{
  std::string filenameTex = filenameTikz;
  filenameTex += ".latex.tex";
  if (m_fileExist_bl(filenameTex)) {
    std::stringstream l_Msg_ss;
    l_Msg_ss << "File \"" << filenameTex << "\" already exists.";
    throw CException(l_Msg_ss.str());
  }
  // determine directory/path
  std::string::size_type found = filenameTikz.rfind("/");
  std::string path ="./";
  if (found!=std::string::npos) {
    path = filenameTikz.substr(0, found+1);
    //std::stringstream cmd;
    //cmd << "cd " << path;
    //std::system(cmd.str().c_str());
    //std::string filenameTikzTmp = filenameTikz.substr(found+1);
  }
  std::cout << "path: " << path << std::endl;
  
  
  
  std::ofstream ofs;
  ofs.open(filenameTex.c_str());
  if (ofs) {
    ofs << "\\documentclass[tikz,border=10pt]{standalone}" << std::endl;
    ofs << "\\usepackage{pgfplots}" << std::endl;
    ofs << "\\usepackage{tikz}" << std::endl;
    ofs << "\\usepackage{units}" << std::endl;
    ofs << "\\usepackage[latin9]{inputenc}" << std::endl;
    ofs << "\\usepackage[T1]{fontenc}" << std::endl;
    ofs << std::endl;
    
    // add user defined colors to additionLatexCommands, here some default colors
    // user defined colors are colors which are used in the tikz file and which have to
    // be defined when creating a pdf file with this class CTikz
    ofs << "\\definecolor{ctikzColorBlue}{RGB}{0,150,230}" << std::endl;
    ofs << "\\definecolor{ctikzColorRed}{RGB}{250,30,0}" << std::endl;
    ofs << "\\definecolor{ctikzColorGreen}{RGB}{100,200,60}" << std::endl;
    ofs << "\\definecolor{ctikzColorYellow}{RGB}{250,210,0}" << std::endl;
    
    // add user defined definitions, symbols etc. to additionalLatexCommands, here an example as default
    // user defined definitions or symbols are definitions which are used in the tikz file. But they
    // have to be definied in additionalLatexCommand to make it possible to create a pdf file with
    // this class CTikz
    ofs << "\\newcommand{\\ctikzSamplingFrequency}[0]{f_\\mathrm{S}}" << std::endl;
    ofs << "\\newcommand{\\ctikzLineStyleExample}[0]{dashed}%" << std::endl;
    
    ofs << std::endl;
    ofs << m_additionalLatexCommands;
    ofs << std::endl;
    ofs << "\\begin{document}" << std::endl;
    ofs << "  \\input{" << m_trimFilename(filenameTikz) << "}" << std::endl;
    ofs << "\\end{document}" << std::endl;
  }
  ofs.close();
  
  std::stringstream ss;
  ss << "pdflatex ";
  ss << "--output-directory " << path;
  ss << " " << m_trimFilename(filenameTex);
  ss << " >/dev/null;";
  ss << "pdflatex ";
  ss << "--output-directory " << path;
  ss << " " << m_trimFilename(filenameTex);
  ss << " >/dev/null";
  std::system(ss.str().c_str());
  
  //std::remove(filenameTex.c_str());
  
  std::string filenameAux = filenameTikz;
  filenameAux += ".latex.aux";
  std::remove(filenameAux.c_str());
  
  std::string filenameLog = filenameTikz;
  filenameLog += ".latex.log";
  std::remove(filenameLog.c_str());
}

double CTikz::m_getMinX() {
  double minVal;
  if (m_useAutoRangeX) {
    if (0 == m_dataSet_vst.size()) {
      throw CException("CTikz::getMinX(): data set size is 0");
    }
    if (0 == m_dataSet_vst.begin()->data.size()) {
      throw CException("CTikz::getMinX(): data size is 0.");
    }
    minVal = m_dataSet_vst.begin()->data.begin()->first;
    for (std::vector<gType_TIKZ_DataSet_st>::const_iterator dataSet = m_dataSet_vst.begin();
         dataSet != m_dataSet_vst.end();
         ++dataSet) {
      for (std::vector<std::pair<double, double> >::const_iterator data = dataSet->data.begin();
           data != dataSet->data.end();
           ++data) {
        if (data->first < minVal) {
          minVal = data->first;
        }
      }
    }
  } else {
    minVal = m_userdefinedMinX;
  }
  return minVal;
}

double CTikz::m_getMaxX() {
  double maxVal;
  if (m_useAutoRangeX) {
    if (0 == m_dataSet_vst.size()) {
      throw CException("CTikz::getMaxX(): data set size is 0");
    }
    if (0 == m_dataSet_vst.begin()->data.size()) {
      throw CException("CTikz::getMaxX(): data size is 0.");
    }
    maxVal = m_dataSet_vst.begin()->data.begin()->first;
    for (std::vector<gType_TIKZ_DataSet_st>::const_iterator dataSet = m_dataSet_vst.begin();
         dataSet != m_dataSet_vst.end();
         ++dataSet) {
      for (std::vector<std::pair<double, double> >::const_iterator data = dataSet->data.begin();
           data != dataSet->data.end();
           ++data) {
        if (data->first > maxVal) {
          maxVal = data->first;
        }
      }
    }
  } else {
    maxVal = m_userdefinedMaxX;
  }
  return maxVal;
}

double CTikz::m_getMinY() {
  double minVal;
  if (m_useAutoRangeY) {
    if (0 == m_dataSet_vst.size()) {
      throw CException("CTikz::getMinY(): data set size is 0");
    }
    if (0 == m_dataSet_vst.begin()->data.size()) {
      throw CException("CTikz::getMinY(): data size is 0.");
    }
    minVal = m_dataSet_vst.begin()->data.begin()->second;
    for (std::vector<gType_TIKZ_DataSet_st>::const_iterator dataSet = m_dataSet_vst.begin();
         dataSet != m_dataSet_vst.end();
         ++dataSet) {
      for (std::vector<std::pair<double, double> >::const_iterator data = dataSet->data.begin();
           data != dataSet->data.end();
           ++data) {
        if (data->second < minVal) {
          minVal = data->second;
        }
      }
    }
  } else {
    minVal = m_userdefinedMinY;
  }
  return minVal;
}

double CTikz::m_getMaxY() {
  double maxVal;
  if (m_useAutoRangeY) {
    if (0 == m_dataSet_vst.size()) {
      throw CException("CTikz::getMaxY(): data set size is 0");
    }
    if (0 == m_dataSet_vst.begin()->data.size()) {
      throw CException("CTikz::getMaxY(): data size is 0.");
    }
    maxVal = m_dataSet_vst.begin()->data.begin()->second;
    for (std::vector<gType_TIKZ_DataSet_st>::const_iterator dataSet = m_dataSet_vst.begin();
         dataSet != m_dataSet_vst.end();
         ++dataSet) {
      for (std::vector<std::pair<double, double> >::const_iterator data = dataSet->data.begin();
           data != dataSet->data.end();
           ++data) {
        if (data->second > maxVal) {
          maxVal = data->second;
        }
      }
    }
  } else {
    maxVal = m_userdefinedMaxY;
  }
  return maxVal;
}

void CTikz::setRangeX(double minVal, double maxVal) {
  m_userdefinedMinX = minVal;
  m_userdefinedMaxX = maxVal;
  m_useAutoRangeX = false;
}

void CTikz::setRangeY(double minVal, double maxVal) {
  m_userdefinedMinY = minVal;
  m_userdefinedMaxY = maxVal;
  m_useAutoRangeY = false;
}

void CTikz::setAdditionalSettings(const std::string& settings) {
  m_additionalSettings.clear();
  addAdditionalSettings(settings);
}

void CTikz::addAdditionalSettings(const std::string& settings) {
  m_additionalSettings.push_back(settings);
}

void CTikz::setAdditionalCommands(const std::string &command) {
  m_additionalsCommands.clear();
  addAdditionalCommands(command);
}

void CTikz::addAdditionalCommands(const std::string &command) {
  m_additionalsCommands.push_back(command);
}

void CTikz::setAdditionalCommandsAfterBeginTikzePicture(const std::string &command) {
  m_additionalsCommandsAfterBeginTikzPicture.clear();
  addAdditionalCommandsAfterBeginTikzePicture(command);
}

void CTikz::addAdditionalCommandsAfterBeginTikzePicture(const std::string &command){
  m_additionalsCommandsAfterBeginTikzPicture.push_back(command);
}


void CTikz::addNode(double posX, double posY, const std::string &text, const std::string& color, const std::string& anchor, double rotate, const std::string& font) {
  std::stringstream command;
  command << "\\node at (axis cs:" << posX << "," << posY << ") ";
  command << "[text=" << color << ",anchor=" << anchor << ",rotate=" << rotate << ",font=\\" << font << "] {" << text << "};";
  addAdditionalCommands(command.str());
}

void CTikz::setLogX(bool on) {
  m_logOnX = on;
}

void CTikz::setLogY(bool on) {
  m_logOnY = on;
}

void CTikz::gridOn() {
  m_gridOnX = true;
  m_gridOnY = true;
}

void CTikz::gridOff() {
  m_gridOnX = false;
  m_gridOnY = false;
}

void CTikz::setSecondAxisCode(const std::string &secondAxisCode)
{
  m_secondAxisCode = secondAxisCode;
}

void CTikz::setAdditionalLatexCommands(const std::string &additionalLatexCommands)
{
  m_additionalLatexCommands = additionalLatexCommands;
}

void CTikz::addAdditionalLatexCommands(const std::string &additionalLatexCommands)
{
  m_additionalLatexCommands += "\n";
  m_additionalLatexCommands += additionalLatexCommands;
}

void CTikz::setAuthor(const std::string &author)
{
  m_author = author;
}

void CTikz::setInfo(const std::string &info)
{
  m_info = info;
}

std::string CTikz::m_createId()
{
  srand(unsigned(time(0)));
  std::ostringstream o;
  if (!(o << (rand() % 100000000))) {
    throw CException("CTikz::int2str: conversion to std::string failed.");
  }
  return o.str();
}


void CTikz::setLegendTitle(const std::string &legendTitle)
{
  m_legendTitle = legendTitle;
}

std::string CTikz::m_trimFilename(const std::string &filename) {
  std::string f = filename;
  std::size_t pos = filename.rfind("/");
  if (pos !=std::string::npos) {
    f = filename.substr(pos+1);
  } else {
    f = filename;
  }
  return f;
}

bool CTikz::m_fileExist_bl(const std::string& f_filename_s)
{
  std::ifstream l_file(f_filename_s.c_str());
  return l_file.good();
}

void CTikz::m_setColorForNextDataSet(const std::string &color) {
  m_colorDefault.insert(m_colorDefault.begin(), color);
}
