# TechFix - Device Repair & Service Centre Management System
## TMF1434 Data Structure & Algorithms Project

---

## 📋 Project Overview

This is a comprehensive **Device Repair & Service Centre Management System** built in C++ that demonstrates:
- ✅ **Object-Oriented Programming** (Inheritance, Encapsulation, Polymorphism)
- ✅ **Custom Data Structures** (NO STL - all implemented from scratch)
- ✅ **Search Algorithms** (Linear Search & Binary Search)
- ✅ **Sorting Algorithms** (Quick Sort & Bubble Sort)
- ✅ **Complete CRUD Operations**
- ✅ **5 Pre-set Records** with realistic data

---

## 🏗️ System Architecture

### **Custom Data Structures Implemented:**

1. **ArrayList<T>** (Array-based List)
   - Used for: Spare Parts Inventory, Customer Management
   - Features: Dynamic resizing, random access
   - Time Complexity: O(1) access, O(n) insertion/deletion

2. **LinkedList<T>** (Singly Linked List)
   - Used for: Repair Jobs Management
   - Features: Dynamic memory, efficient insertion/deletion
   - Time Complexity: O(n) access, O(1) insertion at head

3. **Queue<T>** (FIFO - First In First Out)
   - Used for: Repair Tasks Management
   - Features: Strict FIFO ordering, no direct index access
   - Time Complexity: O(1) enqueue/dequeue

### **Object-Oriented Design:**

```
Person (Base Class)
  ↓
Customer (Derived Class)

RepairJob (Contains Queue<RepairTask>)
  ├── Customer
  ├── Queue<RepairTask>
  └── Device Information

SparePart (Inventory Item)

TechFixSystem (Main Management Class)
  ├── LinkedList<RepairJob>
  ├── ArrayList<SparePart>
  └── ArrayList<Customer>
```

---

## 🎯 Key Features

### **1. Repair Job Management**
- ✅ Add new repair jobs with customer selection
- ✅ Update job status and repair progress
- ✅ Delete repair jobs with confirmation
- ✅ View all active jobs in formatted table

### **2. Search Functionality**
- ✅ **Linear Search**: Works on unsorted data, O(n) complexity
- ✅ **Binary Search**: Requires sorted data, O(log n) complexity
- Both search algorithms are fully implemented and functional

### **3. Inventory Management**
- ✅ View all spare parts (Array-based list)
- ✅ Add new spare parts with auto-generated IDs
- ✅ Search inventory by part name or ID (Linear Search)
- ✅ Track quantity and pricing

### **4. Customer Management**
- ✅ View all registered customers
- ✅ Add new customers with auto-generated IDs
- ✅ Store contact information and email

### **5. Reporting & Sorting**
- ✅ **Active Job Routing & Task Report**
- ✅ Sort by Job ID (Quick Sort Algorithm)
- ✅ Sort by Repair Progress (Bubble Sort Algorithm)
- ✅ Professional formatted output

---

## 📊 Data Structures Justification

| Data Structure | Used For | Why? |
|---------------|----------|------|
| **LinkedList** | Repair Jobs | Frequent insertions/deletions, jobs can be added/removed dynamically |
| **ArrayList** | Inventory & Customers | Random access needed for searching, relatively stable data |
| **Queue** | Repair Tasks | Natural FIFO workflow - tasks are processed in order |

---

## 🔍 Algorithm Implementations

### **Search Algorithms:**

1. **Linear Search** (O(n))
   ```cpp
   // Used for: Job ID search, inventory search
   // Works on: Unsorted data
   // Average: n/2 comparisons
   ```

2. **Binary Search** (O(log n))
   ```cpp
   // Used for: Job ID search on sorted data
   // Requires: Sorted linked list
   // Average: log₂(n) comparisons
   ```

### **Sorting Algorithms:**

1. **Quick Sort** (O(n log n) average)
   ```cpp
   // Used for: Sorting by Job ID
   // Divide-and-conquer approach
   // In-place sorting, efficient for large datasets
   ```

2. **Bubble Sort** (O(n²))
   ```cpp
   // Used for: Sorting by Repair Progress
   // Simple implementation, good for small datasets
   // Stable sort, preserves relative order
   ```

---

## 🚀 Compilation & Execution

### **Option 1: Using Makefile (Recommended)**

```bash
# Build the project
make

# Clean build files
make clean

# Rebuild from scratch
make rebuild

# Build and run
make run

# Show help
make help
```

### **Option 2: Manual Compilation**

```bash
# Using g++
g++ -Wall -std=c++11 -c main.cpp
g++ -Wall -std=c++11 -c TechFix.cpp
g++ -Wall -std=c++11 -o TechFix main.o TechFix.o

# Run
./TechFix
```

### **Option 3: Embarcadero DevC++**

1. Create new project (Console Application)
2. Add all .cpp and .h files to project
3. Build & Run (F11)

---

## 📁 File Structure

```
TechFix/
├── TechFix.h         # Header file with class declarations
├── TechFix.cpp       # Implementation of all functions
├── main.cpp          # Entry point
├── Makefile          # Build automation
└── README.txt        # This file
```

---

## 🎮 How to Use the System

### **Main Menu Options:**

1. **Add New Repair Job**
   - Select customer from list
   - Enter device model
   - Add repair tasks (type 'done' when finished)
   - Job ID auto-generated (J-001, J-002, etc.)

2. **Update Repair Job**
   - Enter Job ID to update
   - Choose: Update status, progress, or add tasks
   - Changes saved immediately

3. **Delete Repair Job**
   - Enter Job ID to delete
   - Confirmation required
   - Permanent deletion

4. **View All Repair Jobs**
   - Displays all jobs in table format
   - Shows: Job ID, Device, Status, Progress, Task count

5. **Search Repair Job**
   - Choose Linear or Binary Search
   - Enter Job ID
   - Shows full job details if found

6. **Manage Spare Parts Inventory**
   - View all parts
   - Add new parts
   - Search by name or ID

7. **Manage Customers**
   - View all customers
   - Add new customers
   - Auto-generated customer IDs

8. **View Summary Report**
   - Sort by Job ID (Quick Sort)
   - Sort by Repair Progress (Bubble Sort)
   - Professional formatted output

9. **Exit**
   - Clean program termination

---

## 📝 Pre-set Data (5+ Records)

### **Customers (5):**
- C-001: John Smith
- C-002: Alice Wong
- C-003: Bob Lee
- C-004: Sarah Chen
- C-005: David Tan

### **Repair Jobs (5):**
- J-001: iPhone 13 (Closed - Completed)
- J-002: Samsung Galaxy S22 (In Progress)
- J-003: MacBook Air M2 (Pending)
- J-004: Dell XPS 15 (Queued)
- J-005: iPad Pro 11" (Ready for Pickup)

### **Spare Parts (7):**
- P-001: iPhone Screen Replacement (RM 299.99)
- P-002: MacBook Battery (RM 450.00)
- P-003: iPad Digitizer (RM 350.00)
- P-004: Laptop Fan (RM 45.00)
- P-005: USB-C Charging Port (RM 35.00)
- P-006: Motherboard Chip (RM 680.00)
- P-007: Water Damage Kit (RM 120.00)

---

## ✅ Project Requirements Met

| Requirement | Implementation | ✓ |
|------------|----------------|---|
| Array-based list | ArrayList (Inventory, Customers) | ✅ |
| Linked List | LinkedList (Repair Jobs) | ✅ |
| Stack OR Queue | Queue (Repair Tasks - FIFO) | ✅ |
| Linear Search | Job search, Inventory search | ✅ |
| Binary Search | Job search on sorted data | ✅ |
| Sorting Algorithm | Quick Sort, Bubble Sort | ✅ |
| OOP - Inheritance | Person → Customer | ✅ |
| OOP - Encapsulation | Private members, getters/setters | ✅ |
| OOP - Polymorphism | Virtual display() method | ✅ |
| CRUD Operations | Add, Update, Delete, View | ✅ |
| Pre-set Data | 5+ records each entity | ✅ |
| Input Validation | Range checks, empty validation | ✅ |
| No STL | All data structures custom-built | ✅ |

---

## 🔧 Technical Details

### **Memory Management:**
- ✅ Proper copy constructors for deep copying
- ✅ Assignment operators implemented
- ✅ No memory leaks (all dynamically allocated memory freed)
- ✅ Proper destructor cleanup

### **Input Validation:**
- ✅ Range checks for menu selections
- ✅ Empty string validation
- ✅ Numeric validation for quantities and prices
- ✅ Confirmation for destructive operations

### **Code Quality:**
- ✅ Comprehensive comments
- ✅ Consistent naming conventions
- ✅ Proper indentation
- ✅ Modular design
- ✅ Error handling

---

## 🎓 Learning Outcomes

This project demonstrates:
1. **Data Structure Design**: Choosing appropriate structures for different scenarios
2. **Algorithm Analysis**: Understanding time/space complexity trade-offs
3. **OOP Principles**: Practical application of inheritance, encapsulation, polymorphism
4. **Memory Management**: Proper handling of dynamic memory in C++
5. **Software Design**: Creating maintainable, extensible code

---

## 📞 Support

For questions or issues:
1. Review this README
2. Check code comments in source files
3. Verify all files are present
4. Ensure C++11 or later compiler

---

## 📄 License

This project is created for educational purposes as part of TMF1434 course requirements.

---

**Built with ❤️ for Data Structures & Algorithms**

*Last Updated: April 2026*
# Tech-Fix
