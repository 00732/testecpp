#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "GnuPlotGraph.hh"

using namespace std;

void postscript2jpeg(const char *filename)
{
    char command[512];
    snprintf(command, sizeof(command), "gs -sDEVICE=jpeg -dJPEGQ=100 -dNOPAUSE -dBATCH -dSAFER -r300 -sOutputFile=%s.jpg %s.ps", filename, filename);
    if (system(command) != 0) {
        cerr << "Error: failed to convert postscript to jpeg" << endl;
    }
    return;
}

void script_gnuplot(const char *filename, double minx, double maxx, double miny, double maxy)
{
    ofstream fp;
    string str = filename;
    str += ".plt";
    const char *file = str.c_str();

    fp.open(file);
    if (!fp.is_open()) {
        cerr << "Error: failed to open gnuplot script file" << endl;
        return;
    }

    fp << "#!/usr/bin/gnuplot" << endl;
    fp << "reset" << endl;
    fp << "set title \"r/GM\"" << endl;
    fp << "set xlabel \"r/GM\"" << endl;
    fp << "set ylabel \"r/GM\"" << endl;
    fp << "set size ratio -1" << endl;
    fp << "unset key" << endl;
    fp << "unset xtics" << endl;
    fp << "unset ytics" << endl;
    fp << "set xtics format \" \"" << endl;
    fp << "set ytics format \" \"" << endl;
    fp << "set xrange [" << minx << ":" << maxx << "]" << endl;
    fp << "set yrange [" << miny << ":" << maxy << "]" << endl;
    fp << "set style line 1 lt 1 lc rgb \"#0c0887\"" << endl;
    fp << "set object 1 circle at 0,0 size 1.0 fillcolor rgb \"black\" linewidth 1 dashtype 3" << endl;
    fp << "plot \"" << filename << ".dat\" using ($1):($2) w l ls 1" << endl;
    fp << "set terminal postscript landscape enhanced color dashed linewidth 1 \"Helvetica\" 14" << endl;
    fp << "set output  \"" << filename  << ".ps\"" << endl;
    fp << "replot" << endl;
    fp << "unset output" << endl;
    fp << "unset terminal" << endl;

    fp.close();
    return;
}

void generate_gnuplot_script(const char *filename, const char *data_filename)
{
    ifstream fp;
    string str = data_filename;
    str += ".dat";
    const char *file = str.c_str();

    fp.open(file);
    if (!fp.is_open()) {
        cerr << "Error: failed to open data file" << endl;
        return;
    }

    double minx, maxx, miny, maxy;
    fp >>
