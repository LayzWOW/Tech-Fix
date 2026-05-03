#ifndef TECHFIX_H
#define TECHFIX_H

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>

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
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    
public:
    ArrayList(int initialCapacity = 10) {
        capacity = initialCapacity;
        size = 0;
        data = new T[capacity];
    }
    
    // Copy constructor
    ArrayList(const ArrayList& other) {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Assignment operator
    ArrayList& operator=(const ArrayList& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    ~ArrayList() {
        delete[] data;
    }
    
    void add(const T& item) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = item;
    }
    
    void removeAt(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
    
    T& get(int index) {
        return data[index];
    }
    
    const T& get(int index) const {
        return data[index];
    }
    
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    // For sorting support
    void swap(int i, int j) {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
};

// ----------------- LINKED LIST -----------------
template <typename T>
class Node {
public:
    T data;
    Node* next;
    
    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;
    
    // Deep copy helper
    void copyFrom(const LinkedList& other) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            add(current->data);
            current = current->next;
        }
    }
    
public:
    LinkedList() : head(nullptr), size(0) {}
    
    // Copy constructor
    LinkedList(const LinkedList& other) : head(nullptr), size(0) {
        copyFrom(other);
    }
    
    // Assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    
    ~LinkedList() {
        clear();
    }
    
    void add(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
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
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        size--;
    }
    
    T& get(int index) {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    const T& get(int index) const {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
    
    Node<T>* getHead() const {
        return head;
    }
};

// ----------------- QUEUE (FIFO - First In First Out) -----------------
template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;
    
    // Deep copy helper
    void copyFrom(const Queue& other) {
        Node<T>* current = other.front;
        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }
    
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    // Copy constructor
    Queue(const Queue& other) : front(nullptr), rear(nullptr), size(0) {
        copyFrom(other);
    }
    
    // Assignment operator
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    
    ~Queue() {
        clear();
    }
    
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
        if (front == nullptr) {
            throw runtime_error("Queue is empty!");
        }
        Node<T>* temp = front;
        T data = front->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return data;
    }
    
    T& peek() {
        if (front == nullptr) {
            throw runtime_error("Queue is empty!");
        }
        return front->data;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    int getSize() const {
        return size;
    }
    
    void clear() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        size = 0;
    }
    
    // View all items without removing them
    void viewAll() const {
        Node<T>* current = front;
        int index = 1;
        while (current != nullptr) {
            cout << index++ << ". " << current->data << endl;
            current = current->next;
        }
    }
};

// ============================================================================
// BUSINESS CLASSES (OOP with Inheritance, Encapsulation, Polymorphism)
// ============================================================================

// ----------------- BASE CLASS: PERSON (for Inheritance) -----------------
class Person {
protected:
    string name;
    string contactNumber;
    
public:
    Person() : name(""), contactNumber("") {}
    Person(string n, string contact) : name(n), contactNumber(contact) {}
    
    virtual ~Person() {}
    
    // Polymorphic method (virtual)
    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "Contact: " << contactNumber << endl;
    }
    
    // Getters (Encapsulation)
    string getName() const { return name; }
    string getContactNumber() const { return contactNumber; }
    
    // Setters
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
    
    void display() const override {
        cout << "Customer ID: " << customerId << endl;
        Person::display();
        cout << "Email: " << email << endl;
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
    
    void display() const {
        cout << taskName << " [" << status << "]";
    }
    
    // For Queue display
    friend ostream& operator<<(ostream& os, const RepairTask& task) {
        os << task.taskName << " [" << task.status << "]";
        return os;
    }
};

// ----------------- SPARE PART (for Array-based inventory) -----------------
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
        cout << left << setw(10) << partId
             << setw(30) << partName
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
    string jobStatus; // "Closed", "Ready for Pickup", "Pending", "In Progress"
    string repairProgress; // "Completed", "In Progress", "Pending"
    Queue<RepairTask> tasks; // Queue for repair tasks
    string dateCreated;
    
public:
    RepairJob() : jobId(""), deviceModel(""), 
                  jobStatus("Pending"), repairProgress("Pending") {
        dateCreated = getCurrentDateTime();
    }
    
    RepairJob(string id, Customer cust, string device)
        : jobId(id), customer(cust), deviceModel(device),
          jobStatus("Pending"), repairProgress("Pending") {
        dateCreated = getCurrentDateTime();
    }
    
    // Get current date/time
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
    Queue<RepairTask>& getTasks() { return tasks; }
    const Queue<RepairTask>& getTasks() const { return tasks; }
    
    // Setters
    void setJobId(string id) { jobId = id; }
    void setCustomer(Customer cust) { customer = cust; }
    void setDeviceModel(string device) { deviceModel = device; }
    void setJobStatus(string status) { jobStatus = status; }
    void setRepairProgress(string progress) { repairProgress = progress; }
    
    void addTask(const RepairTask& task) {
        tasks.enqueue(task);
        updateRepairProgress();
    }
    
    void updateRepairProgress() {
        // Simple logic: if queue is empty, completed; otherwise check
        if (tasks.isEmpty()) {
            repairProgress = "Completed";
            jobStatus = "Closed";
        } else {
            repairProgress = "In Progress";
            jobStatus = "In Progress";
        }
    }
    
    void displayFull() const {
        cout << "\n" << string(60, '=') << endl;
        cout << "REPAIR JOB DETAILS" << endl;
        cout << string(60, '=') << endl;
        cout << "Job ID: " << jobId << endl;
        cout << "Device: " << deviceModel << endl;
        cout << "Status: " << jobStatus << endl;
        cout << "Repair Progress: " << repairProgress << endl;
        cout << "Date Created: " << dateCreated << endl;
        cout << "\nCustomer Information:" << endl;
        cout << string(60, '-') << endl;
        customer.display();
        cout << "\nRepair Tasks:" << endl;
        cout << string(60, '-') << endl;
        if (tasks.isEmpty()) {
            cout << "No tasks in queue (All completed)" << endl;
        } else {
            tasks.viewAll();
        }
        cout << string(60, '=') << endl;
    }
    
    void displaySummary() const {
        cout << left << setw(8) << jobId
             << setw(20) << deviceModel
             << setw(25) << jobStatus
             << setw(15) << repairProgress;
        
        // Display task count
        cout << setw(8) << tasks.getSize() << " tasks";
    }
};

// ============================================================================
// TECH FIX SYSTEM (Main Management Class)
// ============================================================================
class TechFixSystem {
private:
    LinkedList<RepairJob> repairJobs;     // Linked List for repair jobs
    ArrayList<SparePart> inventory;       // Array-based list for inventory
    ArrayList<Customer> customers;        // Array-based list for customers
    int nextJobNumber;
    
    // Helper methods
    string generateJobId() {
        char buffer[10];
        sprintf(buffer, "J-%03d", nextJobNumber++);
        return string(buffer);
    }
    
    string generateCustomerId(int num) {
        char buffer[10];
        sprintf(buffer, "C-%03d", num);
        return string(buffer);
    }
    
    string generatePartId(int num) {
        char buffer[10];
        sprintf(buffer, "P-%03d", num);
        return string(buffer);
    }
    
public:
    TechFixSystem();
    ~TechFixSystem() {}
    
    // Main menu functions
    void displayMainMenu();
    void run();
    
    // Data Management
    void addRepairJob();
    void updateRepairJob();
    void deleteRepairJob();
    void viewAllRepairJobs();
    
    // Search functions (Linear & Binary)
    void searchRepairJob();
    int linearSearchByJobId(string jobId);
    int binarySearchByJobId(string jobId);
    
    // Inventory management
    void manageInventory();
    void viewInventory();
    void addSparePart();
    void searchInventory();
    
    // Customer management
    void manageCustomers();
    void viewAllCustomers();
    void addCustomer();
    
    // Sorting and Reports
    void viewSummaryReport();
    void sortByJobId(int left, int right);  // Quick Sort
    void sortByRepairProgress();
    
    // Utility
    void initializePresetData();
    void clearScreen();
    void pause();
};

#endif // TECHFIX_H
