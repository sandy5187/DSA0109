#include <iostream>
#include <string>

// --- PREDICTION CODE ---
struct Logger {
    std::string n;
    Logger(const std::string& s) : n(s) { std::cout << '+' << n << ' '; }
    Logger(const Logger& o) : n(o.n + "c") { std::cout << "copy" << n << ' '; }
    ~Logger() { std::cout << '-' << n << ' '; }
};

void use(Logger) {
    std::cout << "use ";
}

void runPredictionSection() {
    std::cout << "--- 1. PREDICT THE OUTPUT SECTION (Logger Lifecycle) ---\n";
    Logger a("A");
    {
        Logger b("B");
    }
    use(a);
    Logger* p = new Logger("P");
    delete p;
    std::cout << "end ";
}

// --- DYNAMIC CONSTRUCTOR AND DESTRUCTOR: AUDITORIUM SEAT MAP ---
class Auditorium {
private:
    std::string eventName;
    int rows;
    int cols;
    char** seatMap; // 2D dynamic array

public:
    // Dynamic constructor allocating 2D array
    Auditorium(const std::string& name, int r, int c)
        : eventName(name), rows(r), cols(c), seatMap(nullptr) {
        if (rows > 0 && cols > 0) {
            seatMap = new char*[rows];
            for (int i = 0; i < rows; ++i) {
                seatMap[i] = new char[cols];
                for (int j = 0; j < cols; ++j) {
                    seatMap[i][j] = '.'; // '.' indicates available seat
                }
            }
        }
        std::cout << "[Auditorium Constructor: Allocated " << rows << "x" << cols 
                  << " seat map for '" << eventName << "']\n";
    }

    // Destructor releasing dynamic allocations
    ~Auditorium() {
        if (seatMap != nullptr) {
            for (int i = 0; i < rows; ++i) {
                delete[] seatMap[i];
            }
            delete[] seatMap;
        }
        std::cout << "[Auditorium Destructor: Released all memory for '" 
                  << eventName << "']\n";
    }

    bool bookSeat(int r, int c) {
        if (r >= 0 && r < rows && c >= 0 && c < cols && seatMap[r][c] == '.') {
            seatMap[r][c] = 'X'; // 'X' indicates booked
            return true;
        }
        return false;
    }

    bool cancelSeat(int r, int c) {
        if (r >= 0 && r < rows && c >= 0 && c < cols && seatMap[r][c] == 'X') {
            seatMap[r][c] = '.';
            return true;
        }
        return false;
    }

    void display() const {
        std::cout << "\nSeat Map for " << eventName << " (" << rows << " rows, " << cols << " cols):\n";
        for (int i = 0; i < rows; ++i) {
            std::cout << "Row " << (i + 1) << ": ";
            for (int j = 0; j < cols; ++j) {
                std::cout << seatMap[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};

int main() {
    std::cout << "=== Q3: DYNAMIC CONSTRUCTORS AND DESTRUCTORS ===\n\n";

    runPredictionSection();
    std::cout << "\n\n--- 2. AUDITORIUM SEAT MAP DYNAMIC ALLOCATION & LIFECYCLE ---\n";
    {
        Auditorium hall("Tech Symposium", 3, 4);
        hall.bookSeat(0, 0);
        hall.bookSeat(0, 1);
        hall.bookSeat(1, 2);
        hall.display();

        std::cout << "\nCancelling seat (0, 1)...\n";
        hall.cancelSeat(0, 1);
        hall.display();
    } // hall goes out of scope here; destructor releases 2D array automatically

    return 0;
}
