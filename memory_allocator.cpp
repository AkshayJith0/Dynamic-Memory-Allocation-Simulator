
#include <iostream>
using namespace std;

class Block {
public:
    int startAddress;
    int size;
    bool isFree;
    int processId;
    Block* next;

    Block(int start, int sz, bool free, int pid = -1) {
        startAddress = start;
        size = sz;
        isFree = free;
        processId = pid;
        next = nullptr;
    }
};

class MemoryManager {
private:
    Block* head;
    int totalMemory;

public:
    MemoryManager(int totalSize) {
        totalMemory = totalSize;

        head = new Block(0, totalSize, true);
    }

    void allocateFirstFit(int size, int pid) {
        if (size <= 0) {
            cout << "Allocation Failed! Requested size must be greater than 0.\n";
            return;
        }
        if (pid < 0) {
            cout << "Allocation Failed! Invalid process ID.\n";
            return;
        }

        Block* temp = head;

        while (temp != nullptr) {
            if (temp->isFree && temp->size >= size) {
                splitBlock(temp, size, pid);
                cout << "Allocated " << size << " units to Process " << pid
                     << " using FIRST-FIT at address " << temp->startAddress << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Allocation Failed! No suitable block found (First-Fit).\n";
    }

    void allocateBestFit(int size, int pid) {
        if (size <= 0) {
            cout << "Allocation Failed! Requested size must be greater than 0.\n";
            return;
        }
        if (pid < 0) {
            cout << "Allocation Failed! Invalid process ID.\n";
            return;
        }

        Block* temp = head;
        Block* bestBlock = nullptr;

        while (temp != nullptr) {
            if (temp->isFree && temp->size >= size) {

                if (bestBlock == nullptr || temp->size < bestBlock->size) {
                    bestBlock = temp;
                }
            }
            temp = temp->next;
        }

        if (bestBlock != nullptr) {
            splitBlock(bestBlock, size, pid);
            cout << "Allocated " << size << " units to Process " << pid
                 << " using BEST-FIT at address " << bestBlock->startAddress << endl;
        } else {
            cout << "Allocation Failed! No suitable block found (Best-Fit).\n";
        }
    }

    void splitBlock(Block* block, int size, int pid) {
        if (block->size > size) {

            Block* newBlock = new Block(block->startAddress + size,
                                          block->size - size,
                                          true);
            newBlock->next = block->next;
            block->next = newBlock;
        }
        block->size = size;
        block->isFree = false;
        block->processId = pid;
    }

    void freeMemory(int pid) {
        if (pid < 0) {
            cout << "Process ID must be non-negative.\n";
            return;
        }

        Block* temp = head;
        bool found = false;

        while (temp != nullptr) {
            if (!temp->isFree && temp->processId == pid) {
                temp->isFree = true;
                temp->processId = -1;
                found = true;
                cout << "Freed memory of Process " << pid << endl;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "Process " << pid << " not found in memory.\n";
            return;
        }

        mergeFreeBlocks();
    }

    void mergeFreeBlocks() {
        Block* temp = head;

        while (temp != nullptr && temp->next != nullptr) {
            if (temp->isFree && temp->next->isFree) {
                Block* toDelete = temp->next;
                temp->size += toDelete->size;
                temp->next = toDelete->next;
                delete toDelete;

            } else {
                temp = temp->next;
            }
        }
    }

    void displayMemory() {
        Block* temp = head;
        cout << "\n--------- MEMORY MAP ---------\n";
        while (temp != nullptr) {
            cout << "[Addr: " << temp->startAddress
                 << " | Size: " << temp->size
                 << " | ";
            if (temp->isFree) {
                cout << "FREE";
            } else {
                cout << "USED by P" << temp->processId;
            }
            cout << "]\n";
            temp = temp->next;
        }
        cout << "-------------------------------\n";
    }

    void showFragmentation() {
        Block* temp = head;
        int freeBlocks = 0;
        int totalFree = 0;

        while (temp != nullptr) {
            if (temp->isFree) {
                freeBlocks++;
                totalFree += temp->size;
            }
            temp = temp->next;
        }

        cout << "\nTotal Free Memory : " << totalFree << " units\n";
        cout << "Free Blocks Count  : " << freeBlocks << "\n";
        cout << "(More free blocks scattered around = more fragmentation)\n";
    }

    ~MemoryManager() {

        Block* temp = head;
        while (temp != nullptr) {
            Block* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
};

int main() {
    int totalSize;
    cout << "Enter total memory size (e.g. 1000): ";
    cin >> totalSize;

    if (totalSize <= 0) {
        cout << "Invalid total memory size. Exiting.\n";
        return 1;
    }

    MemoryManager memory(totalSize);

    int choice;
    do {
        cout << "\n===== DYNAMIC MEMORY ALLOCATION SIMULATOR =====\n";
        cout << "1. Allocate Memory (First-Fit)\n";
        cout << "2. Allocate Memory (Best-Fit)\n";
        cout << "3. Free Memory\n";
        cout << "4. Display Memory Map\n";
        cout << "5. Show Fragmentation Info\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int size, pid;

        switch (choice) {
            case 1:
                cout << "Enter process ID: ";
                cin >> pid;
                cout << "Enter size required: ";
                cin >> size;
                memory.allocateFirstFit(size, pid);
                break;

            case 2:
                cout << "Enter process ID: ";
                cin >> pid;
                cout << "Enter size required: ";
                cin >> size;
                memory.allocateBestFit(size, pid);
                break;

            case 3:
                cout << "Enter process ID to free: ";
                cin >> pid;
                memory.freeMemory(pid);
                break;

            case 4:
                memory.displayMemory();
                break;

            case 5:
                memory.showFragmentation();
                break;

            case 6:
                cout << "Exiting simulator. Bye!\n";
                break;

            default:
                cout << "Invalid choice, try again.\n";
        }

    } while (choice != 6);

    return 0;
}