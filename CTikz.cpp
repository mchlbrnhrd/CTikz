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

CTikz::CTikz() {
    clear();
}

CTikz::CTikz(const CTikz& orig) {
}

CTikz::~CTikz() {
}

void CTikz::clear() {
    m_title = "";
    m_legend.clear();
    m_xlabel = "";
    m_ylabel = "";
    m_legendStyle = "draw=black,fill=white, legend cell align=left";
    m_width =  "9.899cm";
    m_height = "6.118cm";
    m_data.clear();
    m_matrixData.clear();
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
    m_additionalSettings.clear();
    m_addPlotStyle.clear();
    m_additionalsCommands.clear();
    m_additionalsCommandsAfterBeginTikzPicture.clear();
    m_secondAxisCode = "";
    m_additionalLatexCommands = "";
    m_author = "";
    m_info = "";
    m_id = createId();
    m_legendTitle = "";
    
    m_color.clear();
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
    m_legend.push_back(legend);
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

void CTikz::setData(const std::vector<std::pair<double, double> >& data) {
    m_data.clear();
    addData(data);
}

void CTikz::setData(const std::vector<double>& dataX, const std::vector<double>& dataY) {
    m_data.clear();
    addData(dataX, dataY);
}

void CTikz::setData(const std::vector<std::pair<double,double> >& data, const std::string& legend) {
    setData(data);
    setLegend(legend);
}

void CTikz::setData(const std::vector<double>& dataX, const std::vector<double>& dataY, const std::string& legend) {
    setData(dataX, dataY);
    setLegend(legend);
}

void CTikz::setData(const std::vector<std::pair<double, double> > &data, const std::string &legend, const std::string &color) {
    setColorForNextDataSet(color);
    setData(data);
    setLegend(legend);
}

void CTikz::setData(const std::vector<double> &dataX, const std::vector<double> &dataY, const std::string &legend, const std::string &color) {
    setColorForNextDataSet(color);
    setData(dataX, dataY);
    setLegend(legend);
}

void CTikz::setColorForNextDataSet(const std::string &color) {
    m_colorDefault.insert(m_colorDefault.begin(), color);
}

void CTikz::addData(const std::vector<std::pair<double, double> >& data) {
    if (!data.empty()) {
        m_data.push_back(data);
        if (!m_colorDefault.empty()) {
            m_color.push_back(m_colorDefault.front());
            m_colorDefault.erase(m_colorDefault.begin());
        } else {
            m_color.push_back("black");
        }
    }
}

void CTikz::addData(const std::vector<std::pair<double,double> >& data, const std::string& legend) {
    addData(data);
    addLegend(legend);
}

void CTikz::addData(const std::vector<std::pair<double, double> > &data, const std::string &legend, const std::string &color) {
    setColorForNextDataSet(color);
    addData(data);
    addLegend(legend);
}

void CTikz::addData(const std::vector<double>& dataX, const std::vector<double>& dataY) {
    std::vector<std::pair<double, double> > tmp;
    if (dataX.size() == dataY.size()) {
        for (size_t k = 0; k < dataX.size(); ++k) {
            std::pair<double, double> dataEntry = std::make_pair(dataX.at(k), dataY.at(k));
            tmp.push_back(dataEntry);
        }
    } else {
        std::stringstream msg;
        msg << "Data sizes must be the same. dataX.size()=" << dataX.size() << ", dataY.size()=" << dataY.size() << std::endl;
        throw CException(msg);
    }
    addData(tmp);
}

void CTikz::addData(const std::vector<double>& dataX, const std::vector<double>& dataY, const std::string& legend) {
    addData(dataX, dataY);
    addLegend(legend);
}

void CTikz::addData(const std::vector<double> &dataX, const std::vector<double> &dataY, const std::string &legend, const std::string &color) {
    setColorForNextDataSet(color);
    addData(dataX, dataY);
    addLegend(legend);
}

void CTikz::addMatrixData(const std::vector<std::vector<double> > &data)
{
    m_matrixData = data;
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
    createTikzFile(filename, false);
}

void CTikz::createTikzFileHist(const std::string& filename, int bins, double dataMin, double dataMax) {
    createTikzFile(filename, true, bins, dataMin, dataMax);
}

void CTikz::createTikzFile(const std::string& filename,
                           bool createHist,
                           int bins /* = 0 */,
                           double dataMin /* = 0 */ ,
                           double dataMax /* = 0 */)
{
    if (m_addPlotStyle.size() == 0) { // default is "solid"
        m_addPlotStyle.push_back("solid");
    }
    // if some addPlotStyles are missing, take the latest one for
    // the missing one
    if (m_addPlotStyle.size() < m_data.size()) {
        for (std::size_t k = m_addPlotStyle.size();
             k < m_data.size();
             ++k) {
            m_addPlotStyle.push_back(m_addPlotStyle.back());
        }
    }
    if (m_color.size() < m_data.size()) {
        for (std::size_t k=m_color.size(); k < m_data.size();++k) {
            m_color.push_back(m_color.back());
        }
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
    if (!m_data.empty()) {
        ss << "xmin=" << getMinX() << "," << std::endl;
        ss << "xmax=" << getMaxX() << "," << std::endl;
    }
    ss << "xlabel={" << m_xlabel << "}," << std::endl;
    if (m_gridOnX) ss << "xmajorgrids," << std::endl;
    if (m_logOnX) ss << "xmode=log,log basis x=10," << std::endl;
    if (!createHist) { // normal mode
        if (!m_data.empty()) {
            ss << "ymin=" << getMinY() << "," << std::endl;
            ss << "ymax=" << getMaxY() << "," << std::endl;
        }
    }
    ss << "ylabel={" << m_ylabel << "}," << std::endl;
    if (createHist) { // histogram mode
        ss << "ymin=0," << std::endl;
        ss << "ybar," << std::endl;
    }
    if (m_gridOnY) ss << "ymajorgrids," << std::endl;
    if (m_logOnY) ss << "ymode=log,log basis y=10," << std::endl;
    ss << "title={" << m_title << "}," << std::endl;
    for (std::vector<std::string>::const_iterator iter = m_additionalSettings.begin();
         iter != m_additionalSettings.end(); ++iter) {
        ss << *iter << "," << std::endl;
    }
    ss << "legend style={" << m_legendStyle << "}" << std::endl;
    ss << "]" << std::endl;
    if (m_legendTitle != "") {
        ss << "\\addlegendimage{empty legend}" << std::endl;
    }
    bool legendTitleSet = false;
    if (!m_data.empty()) {
        for (std::size_t k = 0; k < m_data.size(); ++k) {
            if (!createHist) { // normal mode
                ss << "\\addplot [color=" << m_color.at(k) << ",";
            } else { // histogram mode
                ss << "\\addplot+ [color=" << m_color.at(k) << ",";
                ss << " ,hist={" << std::endl;
                ss << "    density," << std::endl;
                ss << "    bins=" << bins << "," << std::endl;
                ss << "    data min=" << dataMin << "," << std::endl;
                ss << "    data max=" << dataMax << std::endl;
                ss << " },";
            }
            ss << m_addPlotStyle.at(k) << "]" << std::endl;
            if (k < m_dataComment.size()) {
                ss << "% " << m_dataComment.at(k) << std::endl;
            }
            ss << "  table[row sep=crcr]{%" << std::endl;
            for (std::vector<std::pair<double, double> >::const_iterator iter = m_data.at(k).begin();
                 iter != m_data.at(k).end();
                 ++iter) {
                ss << iter->first << "\t" << iter->second << "\\\\" << std::endl;
            }
            ss << "};" << std::endl;
            ss << "\\label{addPlotLabel_" << m_id << "_" << k << "}" << std::endl;
            if (m_legendTitle != "" && !legendTitleSet) {
                ss << "\\addlegendentry{\\hspace{-.6cm}" << m_legendTitle << "};" << std::endl;
                legendTitleSet = true;
            }
            if (k < m_legend.size()) {
                ss << "\\addlegendentry{" << m_legend.at(k) << "};" << std::endl;
            }
        }
    } else {
        if (!createHist) { // normal mode
            if (!m_matrixData.empty()) {
                ss << "\\addplot [" << m_addPlotStyle.at(0) << "]" << std::endl;
                ss << " coordinates{"<< std::endl;
                for (int row=0; row < m_matrixData.size(); ++row) {
                    for (int col=0; col < m_matrixData.at(row).size(); ++col) {
                        ss << "(" << col << "," << row << ") [" << m_matrixData.at(row).at(col) << "]" << std::endl;
                    }
                    ss << std::endl;
                }
                ss << "};" << std::endl;
            }
        }
    }
    ss << std::endl;
    for (std::vector<std::string>::iterator it = m_additionalsCommands.begin(); it != m_additionalsCommands.end(); ++it) {
        ss << *it << std::endl;
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
    //ss << "axis x line=none," << std::endl;
    ss << "axis y line=right," << std::endl;
    ss << "y axis line style=-," << std::endl;
    ss << "width=" << m_width << "," << std::endl;
    ss << "height=" << m_height << "," << std::endl;
    ss << "scale only axis," << std::endl;
    ss << "xmin=" << getMinX() << "," << std::endl;
    ss << "xmax=" << getMaxX() << "," << std::endl;
    //ss << "xlabel={" << m_xlabel << "}," << std::endl;
    ss << "ylabel={" << m_ylabel << "}," << std::endl;
    if (m_gridOnX) ss << "xmajorgrids," << std::endl;
    if (m_logOnX) ss << "xmode=log,log basis x=10," << std::endl;
    ss << "ymin=" << getMinY() << "," << std::endl;
    ss << "ymax=" << getMaxY() << "," << std::endl;
    if (m_gridOnY) ss << "ymajorgrids," << std::endl;
    if (m_logOnY) ss << "ymode=log,log basis y=10," << std::endl;
    for (std::vector<std::string>::const_iterator iter = m_additionalSettings.begin();
         iter != m_additionalSettings.end(); ++iter) {
        ss << *iter << "," << std::endl;
    }
    ss << "legend style={" << m_legendStyle << "}" << std::endl;
    ss << "]" << std::endl;
    for (int k=0; k < m_legend.size() - m_data.size(); ++k) {
         ss << "\\addlegendimage{/pgfplots/refstyle=addPlotLabel_" << m_id << "_" << k << "}" << std::endl;
         ss << "\\addlegendentry{" << m_legend.at(k) << "};" << std::endl;
    }
    for (std::size_t k = 0; k < m_data.size(); ++k) {
        ss << "\\addplot [color=" << m_color.at(k) << "," << m_addPlotStyle.at(k) << "]" << std::endl;
        ss << "  table[row sep=crcr]{%" << std::endl;
        for (std::vector<std::pair<double, double> >::const_iterator iter = m_data.at(k).begin();
             iter != m_data.at(k).end();
             ++iter) {
            ss << iter->first << "\t" << iter->second << "\\\\" << std::endl;
        }
        ss << "};" << std::endl;
        if (k+m_legend.size()-m_data.size() < m_legend.size()) {
            ss << "\\addlegendentry{" << m_legend.at(k+m_legend.size()-m_data.size()) << "};" << std::endl;
        }
    }
    ss << std::endl;
    for (std::vector<std::string>::iterator it = m_additionalsCommands.begin(); it != m_additionalsCommands.end(); ++it) {
        ss << *it << std::endl;
    }
    ss << std::endl;
    ss << "\\end{axis}" << std::endl;
    secondAxisCode = ss.str();
}

void CTikz::createTikzPdf(const std::string& filenameTikz) {
    createTikzFile(filenameTikz);
    
    createPdf(filenameTikz);
}

void CTikz::createTikzPdfHist(const std::string& filenameTikz, int bins, double dataMin, double dataMax) {
    createTikzFileHist(filenameTikz, bins, dataMin, dataMax);
    
    createPdf(filenameTikz);
}

void CTikz::createPdf(const std::string& filenameTikz)
{
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
    
    std::string filenameTex = filenameTikz;
    filenameTex += ".latex.tex";
    
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
        ofs << "  \\input{" << trimFilename(filenameTikz) << "}" << std::endl;
        ofs << "\\end{document}" << std::endl;
    }
    ofs.close();
    
    std::stringstream ss;
    // ss << "cd " << path << ";";
    ss << "pdflatex ";
    ss << "--output-directory " << path;
    ss << " " << trimFilename(filenameTex);
    ss << " >/dev/null;";
    ss << "pdflatex ";
    ss << "--output-directory " << path;
    ss << " " << trimFilename(filenameTex);
    ss << " >/dev/null";
    std::system(ss.str().c_str());
    
    std::remove(filenameTex.c_str());
    
    std::string filenameAux = filenameTikz;
    filenameAux += ".latex.aux";
    std::remove(filenameAux.c_str());
    
    std::string filenameLog = filenameTikz;
    filenameLog += ".latex.log";
    std::remove(filenameLog.c_str());
}

double CTikz::getMinX() {
    double minVal;
    if (m_useAutoRangeX) {
        if (m_data.size() == 0) throw CException("CTikz::getMinX(): m_data.size() = 0.");
        if (m_data.begin()->size() == 0) throw CException("CTikz::getMinX(): m_data.begin()->size() = 0.");
        minVal = m_data.begin()->begin()->first;
        for (std::vector<std::vector<std::pair<double, double> > >::const_iterator iter = m_data.begin();
                iter != m_data.end();
                ++iter) {
            for (std::vector<std::pair<double, double> >::const_iterator iter2 = iter->begin();
                    iter2 != iter->end();
                    ++iter2) {
                if (iter2->first < minVal) minVal = iter2->first;
            }
        }
    } else {
        minVal = m_userdefinedMinX;
    }
    return minVal;
}

double CTikz::getMaxX() {
    double maxVal;
    if (m_useAutoRangeX) {
        if (m_data.size() == 0) throw CException("CTikz::getMaxX(): m_data.size() = 0.");
        if (m_data.begin()->size() == 0) throw CException("CTikz::getMaxX(): m_data.begin()->size() = 0.");
        maxVal = m_data.begin()->begin()->first;
        for (std::vector<std::vector<std::pair<double, double> > >::const_iterator iter = m_data.begin();
                iter != m_data.end();
                ++iter) {
            for (std::vector<std::pair<double, double> >::const_iterator iter2 = iter->begin();
                    iter2 != iter->end();
                    ++iter2) {
                if (iter2->first > maxVal) maxVal = iter2->first;
            }
        }
    } else {
        maxVal = m_userdefinedMaxX;
    }
    return maxVal;
}

double CTikz::getMinY() {
    double minVal;
    if (m_useAutoRangeY) {
        minVal = m_data.begin()->begin()->second;
        for (std::vector<std::vector<std::pair<double, double> > >::const_iterator iter = m_data.begin();
                iter != m_data.end();
                ++iter) {
            for (std::vector<std::pair<double, double> >::const_iterator iter2 = iter->begin();
                    iter2 != iter->end();
                    ++iter2) {
                if (iter2->second < minVal) minVal = iter2->second;
            }
        }
    } else {
        minVal = m_userdefinedMinY;
    }
    return minVal;
}

double CTikz::getMaxY() {
    double maxVal;
    if (m_useAutoRangeY) {
        maxVal = m_data.begin()->begin()->second;
        for (std::vector<std::vector<std::pair<double, double> > >::const_iterator iter = m_data.begin();
                iter != m_data.end();
                ++iter) {
            for (std::vector<std::pair<double, double> >::const_iterator iter2 = iter->begin();
                    iter2 != iter->end();
                    ++iter2) {
                if (iter2->second > maxVal) maxVal = iter2->second;
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

void CTikz::setAddPlotStyle(const std::string& addPlotStyle) {
    m_addPlotStyle.clear();
    addAddPlotStyle(addPlotStyle);
}

void CTikz::addAddPlotStyle(const std::string& addPlotStyle) {
    m_addPlotStyle.push_back(addPlotStyle);
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

void CTikz::addDataComment(const std::string &dataComment) {
    m_dataComment.push_back(dataComment);
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

void CTikz::setAuthor(const std::string &author)
{
    m_author = author;
}

void CTikz::setInfo(const std::string &info)
{
    m_info = info;
}

std::string CTikz::createId()
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

std::string CTikz::trimFilename(const std::string &filename) {
    std::string f = filename;
    std::size_t pos = filename.rfind("/");
    if (pos !=std::string::npos) {
        f = filename.substr(pos+1);
    } else {
        f = filename;
    }
    return f;
}
