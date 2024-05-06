#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <set>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;
namespace fs = filesystem;

// Function to store the offline printers to output at the end.
set<string> downPrinter(string offline) {
    set<string> downPrinters;
    fs::path p(offline);
    //getting only the filename and not the path. 
    string filename = p.filename().stem().string();
    downPrinters.insert(filename);
    return downPrinters;
}

int main() {
    // Getting the time for log creation
    time_t currentTime;
    time(&currentTime);
    struct tm localTime;
    localtime_s(&localTime, &currentTime);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d_%H-%M", &localTime);
    string currentDate = buffer;

    // Creating the log file
    string directoryPath = "C:\\Users\\logan\\Documents\\IPtest\\logs\\";
    string logName = "Network_Diagnostic_" + currentDate + ".txt";
    string logPath = directoryPath + logName;
    ofstream outputFile(logPath);

    // Path to IP folder
    string path = "C:\\Users\\logan\\Documents\\IPtest\\ips";

    // Extra variable initialization
    vector<string> fileLoc;
    set<string> down;
    ifstream myFile;
    string fileContent;

    // Bad Cases:
    string dhu = "Destination host unreachable.";
    string rto = "Request timed out.";
    string noFind = "Ping request could not find host";
    string noComplete = "Ping request could not be completed";
    string gf = "General failure.";

    // Exhaust every file. Push every file into a vector.
    for (const auto& entry : fs::directory_iterator(path)) {
        fs::path outfilename = entry.path();
        string outfilename_str = outfilename.string();

        fileLoc.push_back(outfilename_str);

    }
    //For every file in fileLoc, ping the file content. 
    for (int i = 0; i < fileLoc.size(); i++) {
        myFile.open(fileLoc.at(i));
        if (myFile.is_open()) {
            myFile >> fileContent;
            string cmd = "PING " + fileContent;
            FILE* pipe = _popen(cmd.c_str(), "r"); // Open the command as a pipe
            if (!pipe) {
                cout << "Failed to run command." << endl;
                return 1;
            }
            char buffer[128];
            while (fgets(buffer, 128, pipe) != NULL) {
                cout << buffer; // Output the result to console
                outputFile << buffer; // Write the result to log file
                string line = buffer;
                //find the bad cases
                if (line.find(dhu) != string::npos || line.find(rto) != string::npos ||
                    line.find(noFind) != string::npos || line.find(noComplete) != string::npos ||
                    line.find(gf) != string::npos) {
                    cout << "Unresponsive Printer: " << fileLoc.at(i) << endl;
                    outputFile << "Unresponsive Printer: " << fileLoc.at(i) << endl;
                    // Append the offline printer to the down set
                    set<string> offline = downPrinter(fileLoc.at(i));
                    down.insert(offline.begin(), offline.end());
                }
            }

        }
        else {
            cout << "Was not able to open file: " << fileLoc.at(i);
        }
        myFile.close();
    }
    outputFile.close(); // Close log file
    if (down.size() == 0) {
        cout << endl << endl << endl << "All printers are up and running!";
    }
    else {
        cout << endl << endl << endl << "All unresponsive printers:\n";
        for (const auto& printer : down) {
            cout << printer << endl;
        }
    }

    system("pause");
    return 0;
}
