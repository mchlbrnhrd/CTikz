/**
 * @file CTikz.cpp
 * @brief CTikz class
 * @author Michael Bernhard
 *
 * Created on 18. November 2017
 *
 * @details Class to create Tikz files (Tikz ist kein Zeichenprogram) out of C array or data vector.
 *   Pdf preview and latex code can also be generated.
 *
 */



#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "CTikz.hpp"
#include "CException.hpp"

// ========================================================================
// CTikz - constructor
// ========================================================================
CTikz::CTikz()
{
  clear_vd();
}


// ========================================================================
// CTikz - copy constructor
// ========================================================================
CTikz::CTikz(const CTikz& f_orig_c)
{
}


// ========================================================================
// ~CTikz - destructor
// ========================================================================
CTikz::~CTikz()
{
}


// ========================================================================
// clear all internal data and set default values
// ========================================================================
void CTikz::clear_vd()
{
  m_title_s = "";
  m_legend_v.clear();
  m_xLabel_s = "";
  m_yLabel_s = "";
  m_legendStyle_s = "draw=black,fill=white, legend cell align=left";
  m_width_s =  "10cm";
  m_height_s = "6cm";
  m_dataSet_v.clear();
  m_useAutoRangeX_b = true;
  m_useAutoRangeY_b = true;
  m_userdefinedMinX_d = 0;
  m_userdefinedMaxX_d = 0;
  m_userdefinedMinX_d = 0;
  m_userdefinedMaxY_d = 0;
  m_gridOnX_b = false;
  m_gridOnY_b = false;
  m_logOnX_b = false;
  m_logOnY_b = false;
  m_additionalsCommands_v.clear();
  m_additionalsCommandsAfterBeginTikzPicture_v.clear();
  m_secondAxisCode_s = "";
  m_additionalLatexCommands_s = "";
  m_author_s = "";
  m_info_s = "";
  m_id_s = m_createId_s();
  m_legendTitle_s = "";
  
  // set some default colors
  m_colorDefault_v.clear();
  m_colorDefault_v.push_back("ctikzColorBlue");
  m_colorDefault_v.push_back("ctikzColorRed");
  m_colorDefault_v.push_back("ctikzColorGreen");
  m_colorDefault_v.push_back("ctikzColorYellow");
}


// ========================================================================
// set title
// ========================================================================
void CTikz::setTitle_vd(const std::string& f_title_s)
{
  m_title_s = f_title_s;
}


// ========================================================================
// set legend; previous data are cleared
// ========================================================================
void CTikz::setLegend_vd(const std::string& f_legend_s)
{
  m_legend_v.clear();
  addLegend_vd(f_legend_s);
}


// ========================================================================
// add legend to list
// ========================================================================
void CTikz::addLegend_vd(const std::string& f_legend_s)
{
  if ("" != f_legend_s) {
    m_legend_v.push_back(f_legend_s);
  }
}


// ========================================================================
// set title of legend
// ========================================================================
void CTikz::setLegendTitle_vd(const std::string &f_legendTitle_s)
{
  m_legendTitle_s = f_legendTitle_s;
}


// ========================================================================
// set label of x axis
// ========================================================================
void CTikz::setXlabel_vd(const std::string& f_xLabel_s)
{
  m_xLabel_s = f_xLabel_s;
}


// ========================================================================
// set label of y axis
// ========================================================================
void CTikz::setYlabel_vd(const std::string& f_yLabel_s)
{
  m_yLabel_s = f_yLabel_s;
}


// ========================================================================
// set label for x and y axis
// ========================================================================
void CTikz::setLabel_vd(const std::string& f_xLabel_s,
                        const std::string& f_yLabel_s)
{
  setXlabel_vd(f_xLabel_s);
  setYlabel_vd(f_yLabel_s);
}


// ========================================================================
// set data via C array. f_size is size of array dataX and dataY.
// additional: comment, color, plot style and legend entry can be set
// ========================================================================
void CTikz::setData_vd(const double *f_dataX_pd,
                       const double *f_dataY_pd,
                       int f_size_i,
                       const std::string& f_comment_s,
                       const std::string& f_color_s,
                       const std::string& f_plotStyle_s,
                       const std::string& f_legend_s)
{
  m_dataSet_v.clear();
  m_legend_v.clear();
  addData_vd(f_dataX_pd, f_dataY_pd, f_size_i, f_comment_s, f_color_s, f_plotStyle_s, f_legend_s);
}


// ========================================================================
// set data via vector for x and vector for y data
// additional: comment, color, plot style and legend entry can be set
// ========================================================================
void CTikz::setData_vd(const std::vector<double>& f_dataX_v,
                       const std::vector<double>& f_dataY_v,
                       const std::string& f_comment_s,
                       const std::string& f_color_s,
                       const std::string& f_plotStyle_s,
                       const std::string& f_legend_s)
{
  m_dataSet_v.clear();
  m_legend_v.clear();
  addData_vd(f_dataX_v, f_dataY_v, f_comment_s, f_color_s, f_plotStyle_s, f_legend_s);
}


// ========================================================================
// set data via vector with pair of double (x and y values)
// additional: comment, color, plot style and legend entry can be set
// ========================================================================
void CTikz::setData_vd(const std::vector<std::pair<double, double> >& f_data_v,
                       const std::string& f_comment_s,
                       const std::string& f_color_s,
                       const std::string& f_plotStyle_s,
                       const std::string& f_legend_s)
{
  m_dataSet_v.clear();
  m_legend_v.clear();
  addData_vd(f_data_v, f_comment_s, f_color_s, f_plotStyle_s, f_legend_s);
}


// ========================================================================
// set data using struct for data set entry
// additional: legend entry can be set
// ========================================================================
void CTikz::setData_vd(const gType_TIKZ_DataSetEntry_st& f_dataSetEntry_st,
                       const std::string& f_legend_s)
{
  m_dataSet_v.clear();
  m_dataSet_v.push_back(f_dataSetEntry_st);
  m_legend_v.clear();
  addLegend_vd(f_legend_s);
}


// ========================================================================
// add data via C array. size is size of array dataX and dataY.
// additional: comment, color, plot style and legend entry can be set
// ========================================================================
void CTikz::addData_vd(const double *f_dataX_pd,
                       const double *f_dataY_pd,
                       int f_size_i,
                       const std::string& f_comment_s,
                       const std::string& f_color_s,
                       const std::string& f_plotStyle_s,
                       const std::string& f_legend_s)
{
  if ((0 == f_dataX_pd) || (0 == f_dataY_pd)) {
    throw CException("Null pointer");
  }
  else
  {
    std::vector<std::pair<double, double> > l_tmp_v;
    for (int l_k_i = 0; l_k_i < f_size_i; ++l_k_i) {
      std::pair<double, double> l_dataEntry_c = std::make_pair(*f_dataX_pd, *f_dataY_pd);
      l_tmp_v.push_back(l_dataEntry_c);
      ++f_dataX_pd;
      ++f_dataY_pd;
    }
    addData_vd(l_tmp_v, f_comment_s, f_color_s, f_plotStyle_s, f_legend_s);
  }
}


// ========================================================================
// add data via vector for x and vector for y data
// additional: comment, color, plot style and legend entry can be set
// ========================================================================
void CTikz::addData_vd(const std::vector<double>& f_dataX_v,
                       const std::vector<double>& f_dataY_v,
                       const std::string& f_comment_s,
                       const std::string& f_color_s,
                       const std::string& f_plotStyle_s,
                       const std::string& f_legend_s) {
  std::vector<std::pair<double, double> > l_tmp_v;
  if (f_dataX_v.size() != f_dataY_v.size()) {
    std::stringstream l_msg_ss;
    l_msg_ss << "Data sizes must be the same. dataX.size()=" << f_dataX_v.size() << ", dataY.size()=" << f_dataY_v.size() << std::endl;
    throw CException(l_msg_ss);
  } else {
    for (size_t l_k_i = 0; l_k_i < f_dataX_v.size(); ++l_k_i) {
      std::pair<double, double> l_dataEntry_c = std::make_pair(f_dataX_v.at(l_k_i), f_dataY_v.at(l_k_i));
      l_tmp_v.push_back(l_dataEntry_c);
    }
  }
  addData_vd(l_tmp_v, f_comment_s, f_color_s, f_plotStyle_s, f_legend_s);
}


// ========================================================================
// add data via vector with pair of double (x and y values)
// additional: comment, color, plot style and legend entry can be set
// ========================================================================
void CTikz::addData_vd(const std::vector<std::pair<double, double> >& f_data_v,
                       const std::string& f_comment_s,
                       const std::string& f_color_s,
                       const std::string& f_plotStyle_s,
                       const std::string& f_legend_s)
{
  if (f_data_v.empty()) {
    throw CException("Empty data set.");
  } else {
    gType_TIKZ_DataSetEntry_st l_dataSetEntry_st;
    l_dataSetEntry_st.data_v = f_data_v;
    l_dataSetEntry_st.comment_s = f_comment_s;
    // default plot style is "solid"
    l_dataSetEntry_st.plotStyle_s=("" == f_plotStyle_s) ? "solid" : f_plotStyle_s;
    
    // when no color is given then use color from default list or black
    if ("" == f_color_s) {
      if (!m_colorDefault_v.empty()) {
        l_dataSetEntry_st.color_s = m_colorDefault_v.front();
        m_colorDefault_v.erase(m_colorDefault_v.begin());
      } else {
        l_dataSetEntry_st.color_s = "black";
      }
    } else {
      l_dataSetEntry_st.color_s = f_color_s;
    }
    
    m_dataSet_v.push_back(l_dataSetEntry_st);
    addLegend_vd(f_legend_s);
  }
}


// ========================================================================
// add data using struct for data set entry
// additional: legend entry can be set
// ========================================================================
void CTikz::addData_vd(const gType_TIKZ_DataSetEntry_st& f_dataSetEntry_st,
                       const std::string& f_legend_s)
{
  m_dataSet_v.push_back(f_dataSetEntry_st);
  addLegend_vd(f_legend_s);
}



// ========================================================================
// set style for legend
// ========================================================================
void CTikz::setLegendStyle_vd(const std::string& f_legendStyle_s)
{
  m_legendStyle_s = f_legendStyle_s;
}


// ========================================================================
// set width of plot
// ========================================================================
void CTikz::setWidth_vd(const std::string& f_width_s)
{
  m_width_s = f_width_s;
}


// ========================================================================
// set height of plot
// ========================================================================
void CTikz::setHeight_vd(const std::string& f_height_s)
{
  m_height_s = f_height_s;
}


// ========================================================================
// create tikz file
// ========================================================================
void CTikz::createTikzFile_vd(const std::string& f_filename_s)
{
  const bool l_createHist_b = false;
  m_createTikzFile_vd(f_filename_s, l_createHist_b);
}


// ========================================================================
// create tikz file as histogram graphics
// ========================================================================
void CTikz::createTikzFileHist_vd(const std::string& f_filename_s,
                                  int f_bins_i,
                                  double f_dataMin_d,
                                  double f_dataMax_d)
{
  const bool l_createHist_b = true;
  m_createTikzFile_vd(f_filename_s, l_createHist_b, f_bins_i, f_dataMin_d, f_dataMax_d);
}

// ========================================================================
// creates tikz code which can used for a second axis in another CTikz object.
// ========================================================================
void CTikz::createSecondAxisCode_vd(std::string& f_secondAxisCode_s)
{
  std::stringstream l_Code_ss;
  l_Code_ss << "\\begin{axis}[" << std::endl;
  l_Code_ss << "yticklabel pos=right," << std::endl;
  l_Code_ss << "xtick=\\empty," << std::endl;
  l_Code_ss << "axis y line=right," << std::endl;
  l_Code_ss << "y axis line style=-," << std::endl;
  l_Code_ss << "width=" << m_width_s << "," << std::endl;
  l_Code_ss << "height=" << m_height_s << "," << std::endl;
  l_Code_ss << "scale only axis," << std::endl;
  l_Code_ss << "xmin=" << m_getMinX_d() << "," << std::endl;
  l_Code_ss << "xmax=" << m_getMaxX_d() << "," << std::endl;
  l_Code_ss << "ylabel={" << m_yLabel_s << "}," << std::endl;
  if (m_gridOnX_b) {
    l_Code_ss << "xmajorgrids," << std::endl;
  }
  if (m_logOnX_b) {
    l_Code_ss << "xmode=log,log basis x=10," << std::endl;
  }
  l_Code_ss << "ymin=" << m_getMinY_d() << "," << std::endl;
  l_Code_ss << "ymax=" << m_getMaxY_d() << "," << std::endl;
  if (m_gridOnY_b) {
    l_Code_ss << "ymajorgrids," << std::endl;
  }
  if (m_logOnY_b) {
    l_Code_ss << "ymode=log,log basis y=10," << std::endl;
  }
  for (std::vector<std::string>::const_iterator l_settings_it = m_additionalSettings_v.begin();
       l_settings_it != m_additionalSettings_v.end(); ++l_settings_it) {
    l_Code_ss << *l_settings_it << "," << std::endl;
  }
  l_Code_ss << "legend style={" << m_legendStyle_s << "}" << std::endl;
  l_Code_ss << "]" << std::endl;
  for (std::size_t l_k_i=0; l_k_i < m_legend_v.size() - m_dataSet_v.size(); ++l_k_i) {
    l_Code_ss << "\\addlegendimage{/pgfplots/refstyle=addPlotLabel_" << m_id_s << "_" << l_k_i << "}" << std::endl;
    l_Code_ss << "\\addlegendentry{" << m_legend_v.at(l_k_i) << "};" << std::endl;
  }
  std::size_t l_legendIdx_i = m_dataSet_v.size();
  for (std::vector<gType_TIKZ_DataSetEntry_st>::const_iterator l_dataSetEntry_it = m_dataSet_v.begin(); l_dataSetEntry_it != m_dataSet_v.end(); ++l_dataSetEntry_it) {
    l_Code_ss << "\\addplot [color=" << l_dataSetEntry_it->color_s<< "," << l_dataSetEntry_it->plotStyle_s << "]" << std::endl;
    l_Code_ss << "  table[row sep=crcr]{%" << std::endl;
    for (std::vector<std::pair<double, double> >::const_iterator l_data_it = l_dataSetEntry_it->data_v.begin();
         l_data_it != l_dataSetEntry_it->data_v.end();
         ++l_data_it) {
      l_Code_ss << l_data_it->first << "\t" << l_data_it->second << "\\\\" << std::endl;
    }
    l_Code_ss << "};" << std::endl;
    if (l_legendIdx_i < m_legend_v.size()) {
      l_Code_ss << "\\addlegendentry{" << m_legend_v.at(l_legendIdx_i) << "};" << std::endl;
      ++l_legendIdx_i;
    }
  }
  l_Code_ss << std::endl;
  for (std::vector<std::string>::iterator l_command_it = m_additionalsCommands_v.begin(); l_command_it != m_additionalsCommands_v.end(); ++l_command_it) {
    l_Code_ss << *l_command_it << std::endl;
  }
  l_Code_ss << std::endl;
  l_Code_ss << "\\end{axis}" << std::endl;
  f_secondAxisCode_s = l_Code_ss.str();
}


// ========================================================================
// // create tikz file and PDF file as preview with corresponding latex file
// ========================================================================
void CTikz::createTikzPdf_vd(const std::string& f_filenameTikz_s)
{
  createTikzFile_vd(f_filenameTikz_s);
  
  m_createPdf_vd(f_filenameTikz_s);
}


// ========================================================================
// create tikz file and PDF file as preview with corresponding latex file
// graphics is generated as histogram// ========================================================================
void CTikz::createTikzPdfHist_vd(const std::string& f_filenameTikz_s,
                                 int f_bins_i,
                                 double f_dataMin_d,
                                 double f_dataMax_d)
{
  createTikzFileHist_vd(f_filenameTikz_s, f_bins_i, f_dataMin_d, f_dataMax_d);
  
  m_createPdf_vd(f_filenameTikz_s);
}


// ========================================================================
// set range for x axis of plot
// ========================================================================
void CTikz::setRangeX_vd(double f_minVal_d, double f_maxVal_d)
{
  m_userdefinedMinX_d = f_minVal_d;
  m_userdefinedMaxX_d = f_maxVal_d;
  m_useAutoRangeX_b = false;
}


// ========================================================================
// set range for y axis of plot
// ========================================================================
void CTikz::setRangeY_vd(double f_minVal_d, double f_maxVal_d)
{
  m_userdefinedMinY_d = f_minVal_d;
  m_userdefinedMaxY_d = f_maxVal_d;
  m_useAutoRangeY_b = false;
}


// ========================================================================
// set additional settings for tikz file (old settings are cleared)
// ========================================================================
void CTikz::setAdditionalSettings_vd(const std::string& f_settings_s)
{
  m_additionalSettings_v.clear();
  addAdditionalSettings_vd(f_settings_s);
}


// ========================================================================
// add additional settings for tikz file
// ========================================================================
void CTikz::addAdditionalSettings_vd(const std::string& f_settings_s)
{
  m_additionalSettings_v.push_back(f_settings_s);
}


// ========================================================================
// set additional commands for tikz file (old settings are cleared)
// ========================================================================
void CTikz::setAdditionalCommands_vd(const std::string& f_command_s)
{
  m_additionalsCommands_v.clear();
  addAdditionalCommands_vd(f_command_s);
}


// ========================================================================
// add additional commands for tikz file
// ========================================================================
void CTikz::addAdditionalCommands_vd(const std::string &f_command_s)
{
  m_additionalsCommands_v.push_back(f_command_s);
}


// ========================================================================
// // set additianl commands which are inserted after beginning of tikz picture
// (old settings are cleared)
// ========================================================================
void CTikz::setAdditionalCommandsAfterBeginTikzePicture_vd(const std::string& f_command_s)
{
  m_additionalsCommandsAfterBeginTikzPicture_v.clear();
  addAdditionalCommandsAfterBeginTikzePicture_vd(f_command_s);
}


// ========================================================================
// // add additianl commands which are inserted after beginning of tikz picture
// ========================================================================
void CTikz::addAdditionalCommandsAfterBeginTikzePicture_vd(const std::string &f_command_s)
{
  m_additionalsCommandsAfterBeginTikzPicture_v.push_back(f_command_s);
}


// ========================================================================
// add node in plot
// ========================================================================
void CTikz::addNode_vd(double f_posX_d,
                       double f_posY_d,
                       const std::string& f_text_s,
                       const std::string& f_color_s,
                       const std::string& f_anchor_s,
                       double f_rotate_d,
                       const std::string& f_font_s)
{
  std::stringstream l_command_ss;
  l_command_ss << "\\node at (axis cs:" << f_posX_d << "," << f_posY_d << ") ";
  l_command_ss << "[text=" << f_color_s << ",anchor=" << f_anchor_s << ",rotate=";
  l_command_ss << f_rotate_d << ",font=\\" << f_font_s << "] {" << f_text_s << "};";
  addAdditionalCommands_vd(l_command_ss.str());
}


// ========================================================================
// set on or off log scale of plot for x axis: default: on=true
// ========================================================================
void CTikz::setLogX_vd(bool f_on_b)
{
  m_logOnX_b = f_on_b;
}


// ========================================================================
// set on or off log scale of plot for y axis: default: on=true
// ========================================================================
void CTikz::setLogY_vd(bool f_on_b)
{
  m_logOnY_b = f_on_b;
}


// ========================================================================
// switch on grid of plot
// ========================================================================
void CTikz::gridOn_vd() {
  m_gridOnX_b = true;
  m_gridOnY_b = true;
}


// ========================================================================
// switch off grid of plot
// ========================================================================
void CTikz::gridOff_vd() {
  m_gridOnX_b = false;
  m_gridOnY_b = false;
}


// ========================================================================
// set code for second axis
// ========================================================================
void CTikz::setSecondAxisCode_vd(const std::string& f_secondAxisCode_s)
{
  m_secondAxisCode_s = f_secondAxisCode_s;
}


// ========================================================================
// set addional cammands which are only used for PDF preview generation, i.e. for latex code
// (old latex commands are cleared)
// ========================================================================
void CTikz::setAdditionalLatexCommands_vd(const std::string& f_additionalLatexCommands_s)
{
  m_additionalLatexCommands_s = f_additionalLatexCommands_s;
}


// ========================================================================
// add addional cammands which are only used for PDF preview generation, i.e. for latex code
// ========================================================================
void CTikz::addAdditionalLatexCommands_vd(const std::string& f_additionalLatexCommands_s)
{
  m_additionalLatexCommands_s += "\n";
  m_additionalLatexCommands_s += f_additionalLatexCommands_s;
}


// ========================================================================
// set author into tikz file
// ========================================================================
void CTikz::setAuthor_vd(const std::string& f_author_s)
{
  m_author_s = f_author_s;
}


// ========================================================================
// set info into tikz file
// ========================================================================
void CTikz::setInfo_vd(const std::string& f_info_s)
{
  m_info_s = f_info_s;
}


// ========================================================================
//  create tikz file (used for histogram and non histogram)
// ========================================================================
void CTikz::m_createTikzFile_vd(const std::string& f_filename_s,
                                bool f_createHist_b,
                                int f_bins_i /* = 0 */,
                                double f_dataMin_d /* = 0 */ ,
                                double f_dataMax_d /* = 0 */)
{
  if (m_fileExist_b(f_filename_s)) {
    std::stringstream l_msg_ss;
    l_msg_ss << "File \"" << f_filename_s << "\" already exists.";
    throw CException(l_msg_ss.str());
  }
  std::stringstream l_tikz_ss;
  l_tikz_ss << "% file automatically generated by CTikz" << std::endl;
  l_tikz_ss << "% author: " << m_author_s << std::endl;
  l_tikz_ss << "% " << std::endl;
  l_tikz_ss << "% info: " << m_info_s << std::endl;
  l_tikz_ss << "% " << std::endl;
  l_tikz_ss << "\\begin{tikzpicture}" << std::endl;
  for (std::vector<std::string>::iterator l_cmd_it = m_additionalsCommandsAfterBeginTikzPicture_v.begin(); l_cmd_it != m_additionalsCommandsAfterBeginTikzPicture_v.end(); ++l_cmd_it) {
    l_tikz_ss << *l_cmd_it << std::endl;
  }
  l_tikz_ss << "\\begin{axis}[" << std::endl;
  l_tikz_ss << ">=latex," << std::endl;
  l_tikz_ss << "width=" << m_width_s << "," << std::endl;
  l_tikz_ss << "height=" << m_height_s << "," << std::endl;
  l_tikz_ss << "scale only axis," << std::endl;
  l_tikz_ss << "xmin=" << m_getMinX_d() << "," << std::endl;
  l_tikz_ss << "xmax=" << m_getMaxX_d() << "," << std::endl;
  l_tikz_ss << "xlabel={" << m_xLabel_s << "}," << std::endl;
  if (m_gridOnX_b) {
    l_tikz_ss << "xmajorgrids," << std::endl;
  }
  if (m_logOnX_b) {
    l_tikz_ss << "xmode=log,log basis x=10," << std::endl;
  }
  if (!f_createHist_b) { // normal mode
    l_tikz_ss << "ymin=" << m_getMinY_d() << "," << std::endl;
    l_tikz_ss << "ymax=" << m_getMaxY_d() << "," << std::endl;
  }
  l_tikz_ss << "ylabel={" << m_yLabel_s << "}," << std::endl;
  if (f_createHist_b) { // histogram mode
    l_tikz_ss << "ymin=0," << std::endl;
    l_tikz_ss << "ybar," << std::endl;
  }
  if (m_gridOnY_b) {
    l_tikz_ss << "ymajorgrids," << std::endl;
  }
  if (m_logOnY_b) {
    l_tikz_ss << "ymode=log,log basis y=10," << std::endl;
  }
  l_tikz_ss << "title={" << m_title_s << "}," << std::endl;
  for (std::vector<std::string>::const_iterator l_settings_it = m_additionalSettings_v.begin();
       l_settings_it != m_additionalSettings_v.end(); ++l_settings_it) {
    l_tikz_ss << *l_settings_it << "," << std::endl;
  }
  l_tikz_ss << "legend style={" << m_legendStyle_s << "}" << std::endl;
  l_tikz_ss << "]" << std::endl;
  if ("" != m_legendTitle_s) {
    l_tikz_ss << "\\addlegendimage{empty legend}" << std::endl;
  }
  bool l_legendTitleSet_b = false;
  int l_legendIdx_i = 0;
  int l_IdCtr_i = 0;
  for (std::vector<gType_TIKZ_DataSetEntry_st>::const_iterator l_dataSetEntry_it = m_dataSet_v.begin(); l_dataSetEntry_it != m_dataSet_v.end(); ++l_dataSetEntry_it) {
    if (!f_createHist_b) { // normal mode
      l_tikz_ss << "\\addplot [color=" << l_dataSetEntry_it->color_s << ",";
    } else { // histogram mode
      l_tikz_ss << "\\addplot+ [color=" << l_dataSetEntry_it->color_s << ",";
      l_tikz_ss << " ,hist={" << std::endl;
      l_tikz_ss << "    density," << std::endl;
      l_tikz_ss << "    bins=" << f_bins_i << "," << std::endl;
      l_tikz_ss << "    data min=" << f_dataMin_d << "," << std::endl;
      l_tikz_ss << "    data max=" << f_dataMax_d << std::endl;
      l_tikz_ss << " },";
    }
    l_tikz_ss << l_dataSetEntry_it->plotStyle_s << "]" << std::endl;
    if ("" != l_dataSetEntry_it->comment_s) {
      l_tikz_ss << "% " << l_dataSetEntry_it->comment_s << std::endl;
    }
    l_tikz_ss << "  table[row sep=crcr]{%" << std::endl;
    for (std::vector<std::pair<double, double> >::const_iterator l_data_it = l_dataSetEntry_it->data_v.begin();
         l_data_it != l_dataSetEntry_it->data_v.end();
         ++l_data_it) {
      l_tikz_ss << l_data_it->first << "\t" << l_data_it->second << "\\\\" << std::endl;
    }
    l_tikz_ss << "};" << std::endl;
    l_tikz_ss << "\\label{addPlotLabel_" << m_id_s << "_" << l_IdCtr_i++ << "}" << std::endl;
    if ("" != m_legendTitle_s && !l_legendTitleSet_b) {
      l_tikz_ss << "\\addlegendentry{\\hspace{-.6cm}" << m_legendTitle_s << "};" << std::endl;
      l_legendTitleSet_b = true;
    }
    if (l_legendIdx_i < m_legend_v.size()) {
      l_tikz_ss << "\\addlegendentry{" << m_legend_v.at(l_legendIdx_i) << "};" << std::endl;
      ++l_legendIdx_i;
    }
  }
  
  l_tikz_ss << std::endl;
  for (std::vector<std::string>::iterator l_commands_it = m_additionalsCommands_v.begin(); l_commands_it != m_additionalsCommands_v.end(); ++l_commands_it) {
    l_tikz_ss << *l_commands_it << std::endl;
  }
  l_tikz_ss << std::endl;
  l_tikz_ss << "\\end{axis}" << std::endl;
  // insert second axis
  l_tikz_ss << m_secondAxisCode_s;
  l_tikz_ss << "\\end{tikzpicture}%" << std::endl;
  
  std::ofstream l_file_c;
  l_file_c.open(f_filename_s.c_str());
  if (l_file_c) {
    l_file_c << l_tikz_ss.str();
  } else {
    std::stringstream l_msg_ss;
    l_msg_ss << "Cannot write into file \"" << f_filename_s << "\".";
    throw CException(l_msg_ss.str());
  }
  l_file_c.close();
}


// ========================================================================
// create PDF file
// ========================================================================
void CTikz::m_createPdf_vd(const std::string& f_filenameTikz_s)
{
  std::string l_filenameBase_s = f_filenameTikz_s;
  std::string::size_type l_found_i = l_filenameBase_s.rfind(".");
  if (std::string::npos != l_found_i) {
    l_filenameBase_s = l_filenameBase_s.substr(0, l_found_i);
  }
  std::string l_filenameTex_s = l_filenameBase_s;
  l_filenameTex_s += ".tex";
  if (m_fileExist_b(l_filenameTex_s)) {
    std::stringstream l_msg_ss;
    l_msg_ss << "File \"" << l_filenameTex_s << "\" already exists.";
    throw CException(l_msg_ss.str());
  }
  // determine directory/path
  l_found_i = f_filenameTikz_s.rfind("/");
  std::string l_path_s ="./";
  if (std::string::npos != l_found_i) {
    l_path_s = f_filenameTikz_s.substr(0, l_found_i+1);
  }
  
  std::ofstream l_file_c;
  l_file_c.open(l_filenameTex_s.c_str());
  if (l_file_c) {
    l_file_c << "% file automatically generated by CTikz" << std::endl;
    l_file_c << "% author: " << m_author_s << std::endl;
    l_file_c << "\\documentclass[tikz,border=10pt]{standalone}" << std::endl;
    l_file_c << "\\usepackage{pgfplots}" << std::endl;
    l_file_c << "\\usepackage{tikz}" << std::endl;
    l_file_c << "\\usepackage{units}" << std::endl;
    l_file_c << "\\usepackage[latin9]{inputenc}" << std::endl;
    l_file_c << "\\usepackage[T1]{fontenc}" << std::endl;
    l_file_c << std::endl;
    
    // add user defined colors to additionLatexCommands, here some default colors
    // user defined colors are colors which are used in the tikz file and which have to
    // be defined when creating a pdf file with this class CTikz
    l_file_c << "\\definecolor{ctikzColorBlue}{RGB}{0,150,230}" << std::endl;
    l_file_c << "\\definecolor{ctikzColorRed}{RGB}{250,30,0}" << std::endl;
    l_file_c << "\\definecolor{ctikzColorGreen}{RGB}{100,200,60}" << std::endl;
    l_file_c << "\\definecolor{ctikzColorYellow}{RGB}{250,210,0}" << std::endl;
    
    // add user defined definitions, symbols etc. to additionalLatexCommands, here an example as default
    // user defined definitions or symbols are definitions which are used in the tikz file. But they
    // have to be definied in additionalLatexCommand to make it possible to create a pdf file with
    // this class CTikz
    l_file_c << "\\newcommand{\\ctikzSamplingFrequency}[0]{f_\\mathrm{S}}" << std::endl;
    l_file_c << "\\newcommand{\\ctikzLineStyleExample}[0]{dashed}" << std::endl;
    
    l_file_c << std::endl;
    l_file_c << m_additionalLatexCommands_s;
    l_file_c << std::endl;
    l_file_c << "\\begin{document}" << std::endl;
    l_file_c << "  \\input{" << m_trimFilename_s(f_filenameTikz_s) << "}" << std::endl;
    l_file_c << "\\end{document}" << std::endl;
  } else {
    std::stringstream l_msg_ss;
    l_msg_ss << "Cannot write into file \"" << l_filenameTex_s << "\".";
    throw CException(l_msg_ss.str());
  }
  l_file_c.close();
  
  std::stringstream l_Cmd_ss;
  l_Cmd_ss << "pdflatex ";
  l_Cmd_ss << "--output-directory " << l_path_s;
  l_Cmd_ss << " " << m_trimFilename_s(l_filenameTex_s);
  l_Cmd_ss << " >/dev/null;";
  l_Cmd_ss << "pdflatex ";
  l_Cmd_ss << "--output-directory " << l_path_s;
  l_Cmd_ss << " " << m_trimFilename_s(l_filenameTex_s);
  l_Cmd_ss << " >/dev/null";
  std::system(l_Cmd_ss.str().c_str());
  
  // remove aux file which was generated by latex
  std::string l_filenameAux_s = l_filenameBase_s;
  l_filenameAux_s += ".aux";
  std::remove(l_filenameAux_s.c_str());
  
  // remove log file which was generated by latex
  std::string l_filenameLog_s = l_filenameBase_s;
  l_filenameLog_s += ".log";
  std::remove(l_filenameLog_s.c_str());
}


// ========================================================================
// get minimum x value
// ========================================================================
double CTikz::m_getMinX_d()
{
  double l_minVal_d;
  if (m_useAutoRangeX_b) {
    if (0 == m_dataSet_v.size()) {
      throw CException("CTikz::getMinX(): data set size is 0");
    }
    if (0 == m_dataSet_v.begin()->data_v.size()) {
      throw CException("CTikz::getMinX(): data size is 0.");
    }
    l_minVal_d = m_dataSet_v.begin()->data_v.begin()->first;
    for (std::vector<gType_TIKZ_DataSetEntry_st>::const_iterator l_dataSetEntry_it = m_dataSet_v.begin();
         l_dataSetEntry_it != m_dataSet_v.end();
         ++l_dataSetEntry_it) {
      for (std::vector<std::pair<double, double> >::const_iterator l_data_it = l_dataSetEntry_it->data_v.begin();
           l_data_it != l_dataSetEntry_it->data_v.end();
           ++l_data_it) {
        if (l_data_it->first < l_minVal_d) {
          l_minVal_d = l_data_it->first;
        }
      }
    }
  } else {
    l_minVal_d = m_userdefinedMinX_d;
  }
  return l_minVal_d;
}


// ========================================================================
// get maximum x value
// ========================================================================
double CTikz::m_getMaxX_d()
{
  double l_maxVal_d;
  if (m_useAutoRangeX_b) {
    if (0 == m_dataSet_v.size()) {
      throw CException("CTikz::getMaxX(): data set size is 0");
    }
    if (0 == m_dataSet_v.begin()->data_v.size()) {
      throw CException("CTikz::getMaxX(): data size is 0.");
    }
    l_maxVal_d = m_dataSet_v.begin()->data_v.begin()->first;
    for (std::vector<gType_TIKZ_DataSetEntry_st>::const_iterator l_dataSetEntry_it = m_dataSet_v.begin();
         l_dataSetEntry_it != m_dataSet_v.end();
         ++l_dataSetEntry_it) {
      for (std::vector<std::pair<double, double> >::const_iterator l_data_it = l_dataSetEntry_it->data_v.begin();
           l_data_it != l_dataSetEntry_it->data_v.end();
           ++l_data_it) {
        if (l_data_it->first > l_maxVal_d) {
          l_maxVal_d = l_data_it->first;
        }
      }
    }
  } else {
    l_maxVal_d = m_userdefinedMaxX_d;
  }
  return l_maxVal_d;
}


// ========================================================================
// get minimum y value
// ========================================================================
double CTikz::m_getMinY_d()
{
  double l_minVal_d;
  if (m_useAutoRangeY_b) {
    if (0 == m_dataSet_v.size()) {
      throw CException("CTikz::getMinY(): data set size is 0");
    }
    if (0 == m_dataSet_v.begin()->data_v.size()) {
      throw CException("CTikz::getMinY(): data size is 0.");
    }
    l_minVal_d = m_dataSet_v.begin()->data_v.begin()->second;
    for (std::vector<gType_TIKZ_DataSetEntry_st>::const_iterator l_dataSetEntry_it = m_dataSet_v.begin();
         l_dataSetEntry_it != m_dataSet_v.end();
         ++l_dataSetEntry_it) {
      for (std::vector<std::pair<double, double> >::const_iterator l_data_it = l_dataSetEntry_it->data_v.begin();
           l_data_it != l_dataSetEntry_it->data_v.end();
           ++l_data_it) {
        if (l_data_it->second < l_minVal_d) {
          l_minVal_d = l_data_it->second;
        }
      }
    }
  } else {
    l_minVal_d = m_userdefinedMinY_d;
  }
  return l_minVal_d;
}


// ========================================================================
// get maximum y value
// ========================================================================
double CTikz::m_getMaxY_d() {
  double l_maxVal_d;
  if (m_useAutoRangeY_b) {
    if (0 == m_dataSet_v.size()) {
      throw CException("CTikz::getMaxY(): data set size is 0");
    }
    if (0 == m_dataSet_v.begin()->data_v.size()) {
      throw CException("CTikz::getMaxY(): data size is 0.");
    }
    l_maxVal_d = m_dataSet_v.begin()->data_v.begin()->second;
    for (std::vector<gType_TIKZ_DataSetEntry_st>::const_iterator l_dataSetEntry_it = m_dataSet_v.begin();
         l_dataSetEntry_it != m_dataSet_v.end();
         ++l_dataSetEntry_it) {
      for (std::vector<std::pair<double, double> >::const_iterator l_data_it = l_dataSetEntry_it->data_v.begin();
           l_data_it != l_dataSetEntry_it->data_v.end();
           ++l_data_it) {
        if (l_data_it->second > l_maxVal_d) {
          l_maxVal_d = l_data_it->second;
        }
      }
    }
  } else {
    l_maxVal_d = m_userdefinedMaxY_d;
  }
  return l_maxVal_d;
}


// ========================================================================
// create ID
// ========================================================================
std::string CTikz::m_createId_s()
{
  srand(unsigned(time(0)));
  std::ostringstream l_tmp_ss;
  if (!(l_tmp_ss << (rand() % 100000000))) {
    throw CException("CTikz::int2str: conversion to std::string failed.");
  }
  return l_tmp_ss.str();
}


// ========================================================================
// trim file name
// ========================================================================
std::string CTikz::m_trimFilename_s(const std::string &f_filename_s)
{
  std::string l_retFilename_s = f_filename_s;
  std::size_t l_pos_i = f_filename_s.rfind("/");
  if (l_pos_i !=std::string::npos) {
    l_retFilename_s = f_filename_s.substr(l_pos_i+1);
  } else {
    l_retFilename_s = f_filename_s;
  }
  return l_retFilename_s;
}


// ========================================================================
// check if file exists
// ========================================================================
bool CTikz::m_fileExist_b(const std::string& f_filename_s)
{
  std::ifstream l_file_c(f_filename_s.c_str());
  return l_file_c.good();
}
