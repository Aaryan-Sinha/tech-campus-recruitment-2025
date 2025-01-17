
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <vector>
#include <chrono>

namespace fs = std::filesystem;


// Function to extract logs for a specific date
void extractLogs(const std::string& filePath, const std::string& date, const std::string& outputDir) {
    std::ifstream inputFile(filePath, std::ios::in);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    // Ensure output directory exists
    if (!fs::exists(outputDir)) {
        fs::create_directories(outputDir);
    }

    std::string outputFilePath = outputDir + "/output_" + date + ".txt";
    std::ofstream outputFile(outputFilePath, std::ios::out);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create output file " << outputFilePath << std::endl;
        return;
    }

    std::string line;
    size_t lineCount = 0; // For logging purposes
    auto startTime = std::chrono::high_resolution_clock::now();

    while (std::getline(inputFile, line)) {
        if (line.rfind(date, 0) == 0) { // Check if the line starts with the date
            outputFile << line << "\n";
            ++lineCount;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    std::cout << "Extraction completed. " << lineCount << " lines written to " << outputFilePath << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds." << std::endl;

    inputFile.close();
    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <log_file_path> <YYYY-MM-DD>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    std::string date = argv[2];
    std::string outputDir = "output";

    extractLogs(filePath, date, outputDir);

    return 0;
}
