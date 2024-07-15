//#include <iostream>
//#include "Data.h"
//using namespace std;
//
//int main() {
//    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/Thyroid_Diff.csv";
//    Data obj(filepath);
//    DataFrame df = obj.load(filepath);
//
//    // Open a file to write data for the bar chart
//    ofstream dataFile("Dat/Barplot between Gender and Focality.dat");
//    map<string, map<string, int>>m;
//
//    for (int j = 1; j < df.size(); j++) {
//        string Focality = df[j][9];
//        string gender = df[j][1];
//        m[Focality][gender]++;
//    }
//    
//    for (const auto& outerPair : m) {
//        for (const auto& innerPair : outerPair.second) {
//            dataFile << outerPair.first << "_" << innerPair.first << " " << innerPair.second << "\n";
//        }
//    }
//
//    // Close the data file
//    dataFile.close();
//
//    // Gnuplot commands
//    // Output to PNG file and plot bar chart
//system("gnuplot -e \"set terminal pngcairo size 800,600; "
//        "set output 'Visualization/Barplot between Gender and Focality.png'; "
//        "set style data histograms; "
//        "set style fill solid; "
//        "set boxwidth 0.8; "
//        "set title 'Bar Chart Example'; "
//        "set ylabel 'Values'; "
//        "set xlabel 'Focality and Gender'; "
//        "plot 'Dat/Barplot between Gender and Focality.dat' using 2:xtic(1) title 'Bar Chart';\"");
//
//    cout << "Bar chart plotted as 'BarPlot To Gender and Focality'" << endl;
//
//}
