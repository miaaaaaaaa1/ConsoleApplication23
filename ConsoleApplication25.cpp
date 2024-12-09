#include <iostream>
#include <queue>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

struct PrintJob {
    string clientName; 
    int priority;     
    string document;  

    bool operator<(const PrintJob& other) const {
        return priority > other.priority;
    }
};

struct PrintStatistics {
    string clientName; 
    string document;  
    time_t printTime; 
};

class PrinterQueue {
private:
    priority_queue<PrintJob> printQueue; 
    queue<PrintStatistics> statsQueue; 

public:
    void addPrintJob(const string& clientName, int priority, const string& document) {
        printQueue.push({ clientName, priority, document });
        cout << "Task from client '" << clientName << "' added to priority queue " << priority << ".\n";
    }

    void processPrintJob() {
        if (printQueue.empty()) {
            cout << "The print queue is empty. There are no tasks to run.\n";
            return;
        }

        PrintJob job = printQueue.top();
        printQueue.pop();

        cout << "Print document '" << job.document << "' client '" << job.clientName << "'.\n";

        PrintStatistics stats = { job.clientName, job.document, time(nullptr) };
        statsQueue.push(stats);
    }

    void printStatistics() const {
        if (statsQueue.empty()) {
            cout << "Statistics are empty. Tasks have not been completed yet.\n";
            return;
        }

        cout << "Print statistics:\n";
        cout << left << setw(15) << "Client" << setw(20) << "Document" << setw(25) << "Print time\n";
        cout << string(60, '-') << "\n";

        queue<PrintStatistics> tempQueue = statsQueue; 
        while (!tempQueue.empty()) {
            PrintStatistics stats = tempQueue.front();
            tempQueue.pop();

            char buffer[26];
            ctime_r(&stats.printTime, buffer);
            buffer[strlen(buffer) - 1] = '\0';

            cout << left << setw(15) << stats.clientName << setw(20) << stats.document << setw(25) << buffer << "\n";
        }
    }
};

int main() {
    PrinterQueue printerQueue;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add print task\n";
        cout << "2. Execute print task\n";
        cout << "3. Show print statistics\n";
        cout << "4. Log out\n";
        cout << "Select an action: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string clientName, document;
            int priority;
            cout << "Enter customer name: ";
            cin >> clientName;
            cout << "Enter the priority (lower the number, higher the priority): ";
            cin >> priority;
            cout << "Enter the document name: ";
            cin >> document;

            printerQueue.addPrintJob(clientName, priority, document);
            break;
        }
        case 2:
            printerQueue.processPrintJob();
            break;
        case 3:
            printerQueue.printStatistics();
            break;
        case 4:
            cout << "Exit the program.\n";
            break;
        default:
            cout << "Incorrect choice. Try again.\n";
        }
    } while (choice != 4);
}
