#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "Header Files/Data.h"
using namespace std;

int main() {
    //string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/Train.csv";
    //Data obj(filepath);
    //DataFrame df = obj.load(filepath);

    //// Open a file to write data for the bar chart
    //ofstream dataFile("BarPlot To Warehouse_block.dat");
    //map<string, int>m = obj.value_counts(df, "Warehouse_block");
    //for (auto pair : m) {
    //    dataFile << pair.first << " " << pair.second << "\n";

    //}

    //// Close the data file
    //dataFile.close();

    //// Gnuplot commands
    //// Output to PNG file and plot bar chart
    //system("gnuplot -e \"set terminal pngcairo size 800,600; "
    //    "set output 'BarPlot_To_Warehouse_block.png'; "
    //    "set style data histograms; "
    //    "set style fill solid; "
    //    "set boxwidth 0.8; "
    //    "set title 'Bar Chart Example'; "
    //    "set ylabel 'Values'; "
    //    "set xlabel 'Categories'; "
    //    "plot 'BarPlot To Warehouse_block.dat' using 2:xtic(1) title 'Bar Chart';\"");

    cout << "Bar chart plotted as 'BarPlot To Warehouse_block'" << endl;

}
