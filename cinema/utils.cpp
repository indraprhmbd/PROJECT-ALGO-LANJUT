#include "utils.h"
#include <fstream>
void appendTicketToFile(const std::string& content) {
    std::ofstream file("ticket_history.txt", std::ios::app);
    if (file.is_open()) {
        file << content << "\n";
        file.close();
    }
}