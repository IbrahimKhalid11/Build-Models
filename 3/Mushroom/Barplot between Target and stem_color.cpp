//#include <iostream>
//#include "Data.h"
//using namespace std;
//
//int main() {
//    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/mushroom_cleaned.csv";
//    Data obj(filepath);
//    DataFrame df = obj.load(filepath);
//
//    // Open a file to write data for the bar chart
//    ofstream dataFile("Dat/Barplot between Target and stem_color.dat");
//    map<string, map<string, int>>m;
//
//    for (int j = 1; j < df.size(); j++) {
//        string stem_color = df[j][6];
//        string Target = df[j][8];
//        m[stem_color][Target]++;
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
//    system("gnuplot -e \"set terminal pngcairo size 800,600; "
//        "set output 'Visualization/Barplot between Target and stem_color.png'; "
//        "set style data histograms; "
//        "set style fill solid; "
//        "set boxwidth 0.8; "
//        "set title 'Bar Chart Example'; "
//        "set ylabel 'Values'; "
//        "set xlabel 'Target and stem_color'; "
//        "plot 'Dat/Barplot between Target and stem_color.dat' using 2:xtic(1) title 'Bar Chart';\"");
//
//    cout << "Bar chart plotted as 'BarPlot To Target and stem_color'" << endl;
//
//}
