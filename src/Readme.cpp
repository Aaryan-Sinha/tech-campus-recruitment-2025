#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;

// Function to extract logs for a specific date
void extractLogs(const std::string& filePath, const std::string& date, const std::string& outputDir) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    // Ensure output directory exists
    if (!fs::exists(outputDir)) {
        if (!fs::create_directories(outputDir)) {
            std::cerr << "Error: Could not create output directory " << outputDir << std::endl;
            return;
        }
    }

    std::string outputFilePath = outputDir + "/output_" + date + ".txt";
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create output file " << outputFilePath << std::endl;
        return;
    }

    std::string line;
    size_t lineCount = 0;  // To track the number of matched lines
    auto startTime = std::chrono::high_resolution_clock::now();

    // Read each line and check if it starts with the given date
    while (std::getline(inputFile, line)) {
        if (line.rfind(date, 0) == 0) {  // Line starts with the date
            outputFile << line << "\n";
            ++lineCount;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    std::cout << "Extraction completed. " << lineCount << " lines written to " << outputFilePath << std::endl;
    std::cout << "Time taken: " << elapsedTime.count() << " seconds." << std::endl;

    inputFile.close();
    outputFile.close();
}

// Main function to handle command-line arguments
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

