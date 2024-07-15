//#include <iostream>
//#include "Data.h"
//using namespace std;
//
//int main() {
//    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/Salary.csv";
//    Data obj(filepath);
//    DataFrame df = obj.load(filepath);
//
//    // Open a file to write data for the bar chart
//    ofstream dataFile("Dat/BarPlot To Degree.dat");
//    map<string, int>m = obj.value_counts(df, "Degree");
//    for (auto pair : m) {
//        dataFile << pair.first << " " << pair.second << "\n";
//
//    }
//
//    // Close the data file
//    dataFile.close();
//
//    // Gnuplot commands
//    // Output to PNG file and plot bar chart
//     system("gnuplot -e \"set terminal pngcairo size 1200,1000; "
//    "set output 'Visualization/BarPlot_To_Degree.png'; "
//        "set style data histograms; "
//        "set style fill solid; "
//        "set boxwidth 0.8; "
//        "set title 'Bar Chart Example'; "
//        "set ylabel 'Values'; "
//        "set xlabel 'Categories'; "
//        "plot 'Dat/BarPlot To Degree.dat' using 2:xtic(1) title 'Bar Chart';\"");
//
//    cout << "Bar chart plotted as 'BarPlot To Degree'" << endl;
//
//}
//
