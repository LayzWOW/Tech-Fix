#ifndef TECHFIX_H
#define TECHFIX_H

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

// ============================================================================
// CUSTOM DATA STRUCTURES (NO STL ALLOWED)
// ============================================================================

// ----------------- ARRAY-BASED LIST -----------------
template <typename T>
class ArrayList {
private:
    T* data;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
    }

public:
    ArrayList(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        data = new T[capacity];
    }

    ArrayList(const ArrayList& other) : capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
    }

    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }

    ~ArrayList() { delete[] data; }

    void add(const T& item) {
        if (size >= capacity) resize();
        data[size++] = item;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index; i < size - 1; i++) data[i] = data[i + 1];
        size--;
    }

    T& get(int index) { return data[index]; }
    const T& get(int index) const { return data[index]; }
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    void swap(int i, int j) {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
};

// ----------------- LINKED LIST NODE -----------------
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
};

// ----------------- LINKED LIST -----------------
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

    void copyFrom(const LinkedList& other) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            add(current->data);
            current = current->next;
        }
    }

public:
    LinkedList() : head(nullptr), size(0) {}

    LinkedList(const LinkedList& other) : head(nullptr), size(0) { copyFrom(other); }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) { clear(); copyFrom(other); }
        return *this;
    }

    ~LinkedList() { clear(); }

    void add(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) current = current->next;
            current->next = newNode;
        }
        size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size || head == nullptr) return;
        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; i++) current = current->next;
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        size--;
    }

    T& get(int index) {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        return current->data;
    }

    const T& get(int index) const {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        return current->data;
    }

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    Node<T>* getHead() const { return head; }
};

// ----------------- QUEUE (FIFO - First In First Out) -----------------
// Used for: incoming device intake waitlist (system-level)
template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;

    void copyFrom(const Queue& other) {
        Node<T>* current = other.front;
        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    Queue(const Queue& other) : front(nullptr), rear(nullptr), size(0) { copyFrom(other); }

    Queue& operator=(const Queue& other) {
        if (this != &other) { clear(); copyFrom(other); }
        return *this;
    }

    ~Queue() { clear(); }

    // FIFO: enqueue to rear, dequeue from front — NO direct index access
    void enqueue(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue() {
        if (front == nullptr) throw runtime_error("[ERROR] Queue is empty!");
        Node<T>* temp = front;
        T data = front->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        size--;
        return data;
    }

    T& peek() {
        if (front == nullptr) throw runtime_error("[ERROR] Queue is empty!");
        return front->data;
    }

    bool isEmpty() const { return front == nullptr; }
    int getSize() const { return size; }

    void clear() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        size = 0;
    }

    // View all without removing (for display only)
    void viewAll() const {
        Node<T>* current = front;
        int index = 1;
        while (current != nullptr) {
            cout << "  " << index++ << ". " << current->data << endl;
            current = current->next;
        }
    }
};

// ----------------- STACK (LIFO - Last In First Out) -----------------
// Used for: urgent/priority repair jobs — most recently flagged is processed first
template <typename T>
class Stack {
private:
    Node<T>* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    Stack(const Stack& other) : top(nullptr), size(0) {
        // Reverse copy to preserve LIFO order
        if (other.top == nullptr) return;
        ArrayList<T> temp;
        Node<T>* cur = other.top;
        while (cur) { temp.add(cur->data); cur = cur->next; }
        for (int i = temp.getSize() - 1; i >= 0; i--) push(temp.get(i));
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            Stack tmp(other);
            top = tmp.top;
            size = tmp.size;
            tmp.top = nullptr;
            tmp.size = 0;
        }
        return *this;
    }

    ~Stack() { clear(); }

    // LIFO: push/pop from top — NO direct index access
    void push(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        newNode->next = top;
        top = newNode;
        size++;
    }

    T pop() {
        if (top == nullptr) throw runtime_error("[ERROR] Stack is empty!");
        Node<T>* temp = top;
        T data = top->data;
        top = top->next;
        delete temp;
        size--;
        return data;
    }

    T& peek() {
        if (top == nullptr) throw runtime_error("[ERROR] Stack is empty!");
        return top->data;
    }

    bool isEmpty() const { return top == nullptr; }
    int getSize() const { return size; }

    void clear() {
        while (top != nullptr) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }

    void viewAll() const {
        Node<T>* current = top;
        int index = 1;
        while (current != nullptr) {
            cout << "  " << index++ << ". " << current->data << endl;
            current = current->next;
        }
    }
};

// ============================================================================
// BUSINESS CLASSES (OOP: Inheritance, Encapsulation, Polymorphism)
// ============================================================================

// ----------------- BASE CLASS: PERSON (Inheritance base) -----------------
class Person {
protected:
    string name;
    string contactNumber;

public:
    Person() : name(""), contactNumber("") {}
    Person(string n, string contact) : name(n), contactNumber(contact) {}
    virtual ~Person() {}

    // Polymorphic method (overridden in derived classes)
    virtual void display() const {
        cout << left << setw(18) << "  Name" << ": " << name << endl;
        cout << left << setw(18) << "  Contact" << ": " << contactNumber << endl;
    }

    string getName() const { return name; }
    string getContactNumber() const { return contactNumber; }
    void setName(string n) { name = n; }
    void setContactNumber(string contact) { contactNumber = contact; }
};

// ----------------- CUSTOMER (Derived from Person) -----------------
class Customer : public Person {
private:
    string customerId;
    string email;

public:
    Customer() : Person(), customerId(""), email("") {}
    Customer(string id, string n, string contact, string e)
        : Person(n, contact), customerId(id), email(e) {}

    // Polymorphic override
    void display() const override {
        cout << left << setw(18) << "  Customer ID" << ": " << customerId << endl;
        Person::display();
        cout << left << setw(18) << "  Email" << ": " << email << endl;
    }

    string getCustomerId() const { return customerId; }
    string getEmail() const { return email; }
    void setCustomerId(string id) { customerId = id; }
    void setEmail(string e) { email = e; }
};

// ----------------- REPAIR TASK -----------------
class RepairTask {
private:
    string taskName;
    string status; // "Pending", "In Progress", "Completed"

public:
    RepairTask() : taskName(""), status("Pending") {}
    RepairTask(string name) : taskName(name), status("Pending") {}
    RepairTask(string name, string s) : taskName(name), status(s) {}

    string getTaskName() const { return taskName; }
    string getStatus() const { return status; }
    void setTaskName(string name) { taskName = name; }
    void setStatus(string s) { status = s; }

    void display() const { cout << "    - " << taskName << " [" << status << "]" << endl; }

    // For Queue/Stack display
    friend ostream& operator<<(ostream& os, const RepairTask& task) {
        os << task.taskName << " [" << task.status << "]";
        return os;
    }
};

// ----------------- SPARE PART (Array-based inventory) -----------------
class SparePart {
private:
    string partId;
    string partName;
    int quantity;
    double price;

public:
    SparePart() : partId(""), partName(""), quantity(0), price(0.0) {}
    SparePart(string id, string name, int qty, double p)
        : partId(id), partName(name), quantity(qty), price(p) {}

    string getPartId() const { return partId; }
    string getPartName() const { return partName; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    void setPartId(string id) { partId = id; }
    void setPartName(string name) { partName = name; }
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(double p) { price = p; }

    void display() const {
        cout << left
             << setw(10) << partId
             << setw(32) << partName
             << setw(10) << quantity
             << "RM " << fixed << setprecision(2) << price << endl;
    }
};

// ----------------- REPAIR JOB (Main Entity) -----------------
class RepairJob {
private:
    string jobId;
    Customer customer;
    string deviceModel;
    string jobStatus;
    string repairProgress;
    LinkedList<RepairTask> tasks; // Linked List for repair task steps
    string dateCreated;
    bool isUrgent;

public:
    RepairJob() : jobId(""), deviceModel(""),
                  jobStatus("Pending Initial Diagnostics"),
                  repairProgress("Pending"), isUrgent(false) {
        dateCreated = getCurrentDateTime();
    }

    RepairJob(string id, Customer cust, string device)
        : jobId(id), customer(cust), deviceModel(device),
          jobStatus("Pending Initial Diagnostics"),
          repairProgress("Pending"), isUrgent(false) {
        dateCreated = getCurrentDateTime();
    }

    static string getCurrentDateTime() {
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
        return string(buffer);
    }

    // Getters
    string getJobId() const { return jobId; }
    Customer getCustomer() const { return customer; }
    string getDeviceModel() const { return deviceModel; }
    string getJobStatus() const { return jobStatus; }
    string getRepairProgress() const { return repairProgress; }
    string getDateCreated() const { return dateCreated; }
    bool getIsUrgent() const { return isUrgent; }
    LinkedList<RepairTask>& getTasks() { return tasks; }
    const LinkedList<RepairTask>& getTasks() const { return tasks; }

    // Setters
    void setJobId(string id) { jobId = id; }
    void setCustomer(Customer cust) { customer = cust; }
    void setDeviceModel(string device) { deviceModel = device; }
    void setJobStatus(string status) { jobStatus = status; }
    void setRepairProgress(string progress) { repairProgress = progress; }
    void setIsUrgent(bool u) { isUrgent = u; }

    void addTask(const RepairTask& task) {
        tasks.add(task);
    }

    // Build a comma-separated task summary string
    string getTasksString() const {
        if (tasks.isEmpty()) return "(No tasks)";
        string result = "";
        for (int i = 0; i < tasks.getSize(); i++) {
            if (i > 0) result += ", ";
            result += tasks.get(i).getTaskName();
        }
        return result;
    }

    void displayFull() const {
        cout << "\n" << string(65, '=') << endl;
        cout << "  REPAIR JOB DETAILS" << endl;
        cout << string(65, '=') << endl;
        cout << left << setw(22) << "  Job ID" << ": " << jobId << (isUrgent ? "  [!! URGENT !!]" : "") << endl;
        cout << left << setw(22) << "  Device Model" << ": " << deviceModel << endl;
        cout << left << setw(22) << "  Job Status" << ": " << jobStatus << endl;
        cout << left << setw(22) << "  Repair Progress" << ": " << repairProgress << endl;
        cout << left << setw(22) << "  Date Created" << ": " << dateCreated << endl;
        cout << "\n  Customer Information:" << endl;
        cout << string(65, '-') << endl;
        customer.display();
        cout << "\n  Repair Tasks (" << tasks.getSize() << " total):" << endl;
        cout << string(65, '-') << endl;
        if (tasks.isEmpty()) {
            cout << "  (No tasks assigned)" << endl;
        } else {
            for (int i = 0; i < tasks.getSize(); i++) {
                tasks.get(i).display();
            }
        }
        cout << string(65, '=') << endl;
    }

    void displaySummary() const {
        string urgentTag = isUrgent ? "[URG]" : "     ";
        cout << left
             << setw(8)  << jobId
             << setw(6)  << urgentTag
             << setw(20) << deviceModel
             << setw(32) << jobStatus
             << setw(14) << repairProgress
             << tasks.getSize() << " task(s)";
    }
};

// ============================================================================
// TECHFIX SYSTEM (Main Management Class)
// ============================================================================
class TechFixSystem {
private:
    LinkedList<RepairJob>  repairJobs;   // LINKED LIST — stores all repair jobs
    ArrayList<SparePart>   inventory;    // ARRAY-BASED LIST — spare parts inventory
    ArrayList<Customer>    customers;    // ARRAY-BASED LIST — customer records
    Queue<string>          deviceQueue;  // QUEUE (FIFO) — incoming device intake waitlist
    Stack<string>          urgentStack;  // STACK (LIFO) — urgent repair jobs, newest first

    int nextJobNumber;
    int nextCustomerNum;
    int nextPartNum;

    // ── ID generators ───────────────────────────────────────────────────────
    string generateJobId() {
        char buffer[10];
        sprintf(buffer, "J-%03d", nextJobNumber++);
        return string(buffer);
    }
    string generateCustomerId() {
        char buffer[10];
        sprintf(buffer, "C-%03d", nextCustomerNum++);
        return string(buffer);
    }
    string generatePartId() {
        char buffer[10];
        sprintf(buffer, "P-%03d", nextPartNum++);
        return string(buffer);
    }

    // ── Input helpers (validation) ────────────────────────────────────────
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int getIntInput(const string& prompt, int minVal, int maxVal) {
        int val;
        while (true) {
            cout << prompt;
            if (cin >> val && val >= minVal && val <= maxVal) {
                clearInputBuffer();
                return val;
            }
            cout << "  [ERROR] Please enter a number between " << minVal << " and " << maxVal << ".\n";
            clearInputBuffer();
        }
    }

    string getStringInput(const string& prompt) {
        string val;
        while (true) {
            cout << prompt;
            getline(cin, val);
            if (!val.empty()) return val;
            cout << "  [ERROR] Input cannot be empty. Try again.\n";
        }
    }

    double getDoubleInput(const string& prompt, double minVal = 0.0) {
        double val;
        while (true) {
            cout << prompt;
            if (cin >> val && val >= minVal) {
                clearInputBuffer();
                return val;
            }
            cout << "  [ERROR] Please enter a valid number >= " << minVal << ".\n";
            clearInputBuffer();
        }
    }

    // ── Search helpers ────────────────────────────────────────────────────
    // LINEAR SEARCH: used on unsorted/linked list data by job ID
    int linearSearchJobById(const string& jobId) {
        for (int i = 0; i < repairJobs.getSize(); i++) {
            if (repairJobs.get(i).getJobId() == jobId) return i;
        }
        return -1;
    }

    // LINEAR SEARCH: used on inventory by part name (partial match)
    int linearSearchPartByName(const string& name) {
        for (int i = 0; i < inventory.getSize(); i++) {
            string partName = inventory.get(i).getPartName();
            // Case-insensitive partial match
            string lowerPart = partName, lowerSearch = name;
            for (char& c : lowerPart) c = tolower(c);
            for (char& c : lowerSearch) c = tolower(c);
            if (lowerPart.find(lowerSearch) != string::npos) return i;
        }
        return -1;
    }

    // BINARY SEARCH: inventory sorted by Part ID — O(log n) search
    // Inventory ArrayList stays sorted by partId after each insertion sort
    void sortInventoryById() {
        // Insertion sort to keep sorted for binary search
        for (int i = 1; i < inventory.getSize(); i++) {
            SparePart key = inventory.get(i);
            int j = i - 1;
            while (j >= 0 && inventory.get(j).getPartId() > key.getPartId()) {
                inventory.get(j + 1) = inventory.get(j);
                j--;
            }
            inventory.get(j + 1) = key;
        }
    }

    int binarySearchPartById(const string& partId) {
        int left = 0, right = inventory.getSize() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            string midId = inventory.get(mid).getPartId();
            if (midId == partId) return mid;
            else if (midId < partId) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    // ── Sorting ────────────────────────────────────────────────────────────
    // QUICK SORT on LinkedList by Job ID (default sort)
    void quickSortByJobId(int left, int right) {
        if (left >= right) return;
        string pivot = repairJobs.get(right).getJobId();
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (repairJobs.get(j).getJobId() <= pivot) {
                i++;
                RepairJob temp = repairJobs.get(i);
                repairJobs.get(i) = repairJobs.get(j);
                repairJobs.get(j) = temp;
            }
        }
        RepairJob temp = repairJobs.get(i + 1);
        repairJobs.get(i + 1) = repairJobs.get(right);
        repairJobs.get(right) = temp;
        int pivotIdx = i + 1;
        quickSortByJobId(left, pivotIdx - 1);
        quickSortByJobId(pivotIdx + 1, right);
    }

    // BUBBLE SORT on LinkedList by Repair Progress
    // Priority order: Pending(1) < In Progress(2) < Completed(3)
    void bubbleSortByProgress() {
        int n = repairJobs.getSize();
        auto progressRank = [](const string& p) -> int {
            if (p == "Pending") return 1;
            if (p == "In Progress") return 2;
            return 3; // Completed
        };
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (progressRank(repairJobs.get(j).getRepairProgress()) >
                    progressRank(repairJobs.get(j + 1).getRepairProgress())) {
                    RepairJob temp = repairJobs.get(j);
                    repairJobs.get(j) = repairJobs.get(j + 1);
                    repairJobs.get(j + 1) = temp;
                }
            }
        }
    }

public:
    TechFixSystem();
    ~TechFixSystem() {}

    void displayMainMenu();
    void run();

    // Repair Job CRUD
    void addRepairJob();
    void updateRepairJob();
    void deleteRepairJob();
    void viewAllRepairJobs();

    // Search
    void searchMenu();

    // Inventory CRUD
    void manageInventory();
    void viewInventory();
    void addSparePart();
    void updateSparePart();
    void deleteSparePart();
    void searchInventory();

    // Customer CRUD
    void manageCustomers();
    void viewAllCustomers();
    void addCustomer();
    void updateCustomer();
    void deleteCustomer();

    // Queue operations (FIFO device intake)
    void manageDeviceQueue();

    // Stack operations (LIFO urgent jobs)
    void manageUrgentStack();

    // Report
    void viewSummaryReport();

    // Utility
    void initializePresetData();
    void clearScreen();
    void pause();
};

#endif // TECHFIX_H
