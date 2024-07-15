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
//    ofstream dataFile("Dat/linePlot between Avg and lower salary.dat");
//    for (int i = 1; i < df.size(); i++) {
//        dataFile << df[i][22] << " " << df[i][17] << "\n";
//    }
//
//    // Close the data file
//    dataFile.close();
//
//    // Gnuplot commands
//    // Output to PNG file and plot bar chart
//    system("gnuplot -e \"set terminal pngcairo size 800,600; "
//        "set output 'Visualization/linePlot between Avg and lower salary.png'; "
//        "set title 'Avg and lower salary'; "
//        "set ylabel 'Y Values'; "
//        "set xlabel 'X Values'; "
//        "plot 'Dat/linePlot between Avg and lower salary.dat' using 1:2 with lines title 'CLOSE';\"");
//
//    cout << "Line chart plotted as 'Visualization/linePlot between Avg and lower salary.png'" << endl;
//
//}
