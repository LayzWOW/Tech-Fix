#include "TechFix.h"

// ============================================================================
// TECHFIX SYSTEM IMPLEMENTATION
// ============================================================================

TechFixSystem::TechFixSystem()
    : nextJobNumber(6), nextCustomerNum(6), nextPartNum(8) {
    initializePresetData();
}

// ── Utility ──────────────────────────────────────────────────────────────────

void TechFixSystem::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TechFixSystem::pause() {
    cout << "\n  Press Enter to continue...";
    cin.get();
}

// ── Pre-set Data ─────────────────────────────────────────────────────────────

void TechFixSystem::initializePresetData() {
    // 5 preset customers (stored in ArrayList)
    customers.add(Customer("C-001", "John Smith",  "012-3456789", "john@email.com"));
    customers.add(Customer("C-002", "Alice Wong",  "013-9876543", "alice@email.com"));
    customers.add(Customer("C-003", "Bob Lee",     "014-5551234", "bob@email.com"));
    customers.add(Customer("C-004", "Sarah Chen",  "015-7778888", "sarah@email.com"));
    customers.add(Customer("C-005", "David Tan",   "016-9990000", "david@email.com"));

    // 7 preset spare parts (stored in ArrayList — array-based list)
    inventory.add(SparePart("P-001", "iPhone Screen Replacement", 15, 299.99));
    inventory.add(SparePart("P-002", "MacBook Battery",           8,  450.00));
    inventory.add(SparePart("P-003", "iPad Digitizer",            12, 350.00));
    inventory.add(SparePart("P-004", "Laptop Fan",                20,  45.00));
    inventory.add(SparePart("P-005", "USB-C Charging Port",       25,  35.00));
    inventory.add(SparePart("P-006", "Motherboard Chip",           5, 680.00));
    inventory.add(SparePart("P-007", "Water Damage Kit",          10, 120.00));

    // 5 preset repair jobs (stored in LinkedList — linked list)
    // These match Figure-1 in the project spec exactly
    RepairJob job1("J-001", customers.get(0), "iPhone 13");
    job1.addTask(RepairTask("Hardware Diagnostics",  "Completed"));
    job1.addTask(RepairTask("Water Damage Cleaning", "Completed"));
    job1.setJobStatus("Closed");
    job1.setRepairProgress("Completed");
    repairJobs.add(job1);

    RepairJob job2("J-002", customers.get(1), "Samsung Galaxy S22");
    job2.addTask(RepairTask("Hardware Diagnostics", "Completed"));
    job2.addTask(RepairTask("Screen Replacement",   "In Progress"));
    job2.addTask(RepairTask("Quality Check",         "Pending"));
    job2.setJobStatus("Queued for Specialist: Screen Repair Technician");
    job2.setRepairProgress("In Progress");
    repairJobs.add(job2);

    RepairJob job3("J-003", customers.get(2), "MacBook Air M2");
    job3.addTask(RepairTask("Hardware Diagnostics", "In Progress"));
    job3.addTask(RepairTask("Fan Replacement",       "Pending"));
    job3.setJobStatus("Pending Initial Diagnostics");
    job3.setRepairProgress("In Progress");
    repairJobs.add(job3);

    RepairJob job4("J-004", customers.get(3), "Dell XPS 15");
    job4.addTask(RepairTask("Motherboard Microsoldering", "Pending"));
    job4.addTask(RepairTask("OS Restoration",              "Pending"));
    job4.setJobStatus("Queued for Specialist: Motherboard Technician");
    job4.setRepairProgress("Pending");
    repairJobs.add(job4);

    RepairJob job5("J-005", customers.get(4), "iPad Pro 11\"");
    job5.addTask(RepairTask("Hardware Diagnostics", "Completed"));
    job5.addTask(RepairTask("Battery Replacement",   "Completed"));
    job5.addTask(RepairTask("Quality Check",          "Completed"));
    job5.setJobStatus("Ready for Customer Pickup");
    job5.setRepairProgress("Completed");
    repairJobs.add(job5);

    // Pre-load device intake Queue (FIFO) with 3 incoming device job IDs
    deviceQueue.enqueue("J-002");
    deviceQueue.enqueue("J-004");
    deviceQueue.enqueue("J-003");

    // Pre-load urgent Stack (LIFO) — J-004 was flagged last, so it's on top
    urgentStack.push("J-002");
    urgentStack.push("J-004");
}

// ── Main Menu & Run Loop ──────────────────────────────────────────────────────

void TechFixSystem::displayMainMenu() {
    cout << "\n" << string(70, '=') << endl;
    cout << "          TECHFIX - DEVICE REPAIR & SERVICE CENTRE SYSTEM" << endl;
    cout << string(70, '=') << endl;
    cout << "   REPAIR JOBS" << endl;
    cout << "   1. Add New Repair Job" << endl;
    cout << "   2. Update Repair Job" << endl;
    cout << "   3. Delete Repair Job" << endl;
    cout << "   4. View All Repair Jobs" << endl;
    cout << "   5. Search Repair Job" << endl;
    cout << string(70, '-') << endl;
    cout << "   DATA MANAGEMENT" << endl;
    cout << "   6. Manage Spare Parts Inventory" << endl;
    cout << "   7. Manage Customers" << endl;
    cout << string(70, '-') << endl;
    cout << "   QUEUE & STACK OPERATIONS" << endl;
    cout << "   8. Device Intake Queue  [FIFO - incoming devices]" << endl;
    cout << "   9. Urgent Repairs Stack [LIFO - priority jobs]" << endl;
    cout << string(70, '-') << endl;
    cout << "  10. View Active Job Routing & Task Report" << endl;
    cout << "   0. Exit" << endl;
    cout << string(70, '=') << endl;
    cout << "  Enter your choice: ";
}

void TechFixSystem::run() {
    int choice;
    bool running = true;

    while (running) {
        displayMainMenu();

        // Validated input — reject non-integers
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "\n  [ERROR] Invalid input! Please enter a number.\n";
            pause();
            clearScreen();
            continue;
        }
        clearInputBuffer();
        clearScreen();

        switch (choice) {
            case 1:  addRepairJob();       break;
            case 2:  updateRepairJob();    break;
            case 3:  deleteRepairJob();    break;
            case 4:  viewAllRepairJobs();  break;
            case 5:  searchMenu();         break;
            case 6:  manageInventory();    break;
            case 7:  manageCustomers();    break;
            case 8:  manageDeviceQueue();  break;
            case 9:  manageUrgentStack();  break;
            case 10: viewSummaryReport();  break;
            case 0:
                cout << "\n  Thank you for using TechFix System! Goodbye, have a nice day!\n" << endl;
                running = false;
                break;
            default:
                cout << "\n  [ERROR] Invalid choice! Please enter 0-10.\n";
                pause();
                clearScreen();
        }
    }
}

// ============================================================================
// REPAIR JOB CRUD
// ============================================================================

void TechFixSystem::addRepairJob() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  ADD NEW REPAIR JOB" << endl;
    cout << string(65, '=') << endl;

    if (customers.isEmpty()) {
        cout << "\n  [ERROR] No customers found. Please add a customer first.\n";
        pause();
        return;
    }

    // Show customer list
    cout << "\n  Available Customers:" << endl;
    cout << string(65, '-') << endl;
    cout << left << setw(6) << "  No." << setw(12) << "ID"
         << setw(22) << "Name" << "Contact" << endl;
    cout << string(65, '-') << endl;
    for (int i = 0; i < customers.getSize(); i++) {
        cout << "  " << left << setw(4) << (i + 1)
             << setw(12) << customers.get(i).getCustomerId()
             << setw(22) << customers.get(i).getName()
             << customers.get(i).getContactNumber() << endl;
    }
    cout << string(65, '-') << endl;

    int custChoice = getIntInput("\n  Select customer number (1-" +
        to_string(customers.getSize()) + "): ", 1, customers.getSize());
    Customer selectedCustomer = customers.get(custChoice - 1);

    string deviceModel = getStringInput("  Enter device model (e.g., iPhone 14 Pro): ");

    // Mark as urgent?
    cout << "  Flag as URGENT? (y/n): ";
    char urgentFlag;
    cin >> urgentFlag;
    clearInputBuffer();
    bool isUrgent = (urgentFlag == 'y' || urgentFlag == 'Y');

    // Add repair tasks
    string jobId = generateJobId();
    RepairJob newJob(jobId, selectedCustomer, deviceModel);
    newJob.setIsUrgent(isUrgent);

    cout << "\n  Add Repair Tasks (type 'done' to finish):" << endl;
    int taskCount = 0;
    while (taskCount < 10) {
        cout << "  Task " << (taskCount + 1) << ": ";
        string taskName;
        getline(cin, taskName);
        if (taskName == "done" || taskName == "DONE") break;
        if (taskName.empty()) { cout << "  [!] Task name cannot be empty.\n"; continue; }
        newJob.addTask(RepairTask(taskName, "Pending"));
        taskCount++;
    }

    if (taskCount == 0) {
        cout << "  [INFO] No tasks entered — adding default 'Hardware Diagnostics'.\n";
        newJob.addTask(RepairTask("Hardware Diagnostics", "Pending"));
    }

    repairJobs.add(newJob);

    // Auto-enqueue into device intake Queue (FIFO)
    deviceQueue.enqueue(jobId);

    // Auto-push to urgent Stack if flagged
    if (isUrgent) urgentStack.push(jobId);

    cout << "\n  [SUCCESS] Repair job " << jobId << " created!" << endl;
    cout << "  Device  : " << deviceModel << endl;
    cout << "  Customer: " << selectedCustomer.getName() << endl;
    cout << "  Tasks   : " << taskCount << " added" << endl;
    cout << "  Queued in device intake queue." << endl;
    if (isUrgent) cout << "  Pushed onto urgent stack." << endl;

    pause();
    clearScreen();
}

void TechFixSystem::updateRepairJob() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  UPDATE REPAIR JOB" << endl;
    cout << string(65, '=') << endl;

    if (repairJobs.isEmpty()) {
        cout << "\n  [ERROR] No repair jobs available.\n";
        pause();
        return;
    }

    string jobId = getStringInput("  Enter Job ID to update (e.g., J-001): ");

    // Linear search to find the job
    int index = linearSearchJobById(jobId);
    if (index == -1) {
        cout << "\n  [ERROR] Job ID '" << jobId << "' not found!\n";
        pause();
        return;
    }

    RepairJob& job = repairJobs.get(index);
    job.displayFull();

    cout << "\n  What would you like to update?" << endl;
    cout << "  1. Job Status" << endl;
    cout << "  2. Repair Progress" << endl;
    cout << "  3. Add a New Task" << endl;
    cout << "  4. Mark Next Pending Task as Completed" << endl;
    cout << "  5. Toggle Urgent Flag" << endl;
    cout << "  6. Cancel" << endl;

    int choice = getIntInput("  Choice: ", 1, 6);

    switch (choice) {
        case 1: {
            cout << "\n  Status options:" << endl;
            cout << "  1. Pending Initial Diagnostics" << endl;
            cout << "  2. Queued for Specialist" << endl;
            cout << "  3. In Progress" << endl;
            cout << "  4. Ready for Customer Pickup" << endl;
            cout << "  5. Closed" << endl;
            int sc = getIntInput("  Select status: ", 1, 5);
            string statuses[] = {
                "Pending Initial Diagnostics",
                "Queued for Specialist",
                "In Progress",
                "Ready for Customer Pickup",
                "Closed"
            };
            if (sc == 2) {
                string note = getStringInput("  Enter specialist name (e.g., Screen Repair Technician): ");
                job.setJobStatus("Queued for Specialist: " + note);
            } else {
                job.setJobStatus(statuses[sc - 1]);
            }
            cout << "  [SUCCESS] Job status updated.\n";
            break;
        }
        case 2: {
            cout << "\n  Progress options:" << endl;
            cout << "  1. Pending" << endl;
            cout << "  2. In Progress" << endl;
            cout << "  3. Completed" << endl;
            int pc = getIntInput("  Select progress: ", 1, 3);
            string progresses[] = {"Pending", "In Progress", "Completed"};
            job.setRepairProgress(progresses[pc - 1]);
            cout << "  [SUCCESS] Repair progress updated.\n";
            break;
        }
        case 3: {
            string taskName = getStringInput("  Enter new task name: ");
            job.addTask(RepairTask(taskName, "Pending"));
            cout << "  [SUCCESS] Task '" << taskName << "' added.\n";
            break;
        }
        case 4: {
            // Find and mark the first pending task as completed
            LinkedList<RepairTask>& tasks = job.getTasks();
            bool marked = false;
            for (int i = 0; i < tasks.getSize(); i++) {
                if (tasks.get(i).getStatus() == "Pending") {
                    tasks.get(i).setStatus("Completed");
                    cout << "  [SUCCESS] Task '" << tasks.get(i).getTaskName()
                         << "' marked as Completed.\n";
                    marked = true;
                    break;
                }
            }
            if (!marked) cout << "  [INFO] All tasks are already completed!\n";
            // Auto-update repair progress based on task states
            int totalTasks = tasks.getSize();
            int doneTasks  = 0;
            for (int i = 0; i < totalTasks; i++)
                if (tasks.get(i).getStatus() == "Completed") doneTasks++;
            if (doneTasks == 0)          job.setRepairProgress("Pending");
            else if (doneTasks == totalTasks) job.setRepairProgress("Completed");
            else                         job.setRepairProgress("In Progress");
            break;
        }
        case 5: {
            bool cur = job.getIsUrgent();
            job.setIsUrgent(!cur);
            if (!cur) {
                urgentStack.push(job.getJobId());
                cout << "  [SUCCESS] Job flagged as URGENT and pushed onto urgent stack.\n";
            } else {
                cout << "  [SUCCESS] Urgent flag removed.\n";
            }
            break;
        }
        case 6:
            cout << "  Update cancelled.\n";
            break;
    }

    pause();
    clearScreen();
}

void TechFixSystem::deleteRepairJob() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  DELETE REPAIR JOB" << endl;
    cout << string(65, '=') << endl;

    if (repairJobs.isEmpty()) {
        cout << "\n  [ERROR] No repair jobs available.\n";
        pause();
        return;
    }

    string jobId = getStringInput("  Enter Job ID to delete (e.g., J-001): ");

    int index = linearSearchJobById(jobId);
    if (index == -1) {
        cout << "\n  [ERROR] Job ID '" << jobId << "' not found!\n";
        pause();
        return;
    }

    repairJobs.get(index).displayFull();

    cout << "\n  Are you sure you want to delete job " << jobId << "? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
        repairJobs.removeAt(index);
        cout << "\n  [SUCCESS] Repair job " << jobId << " deleted.\n";
    } else {
        cout << "  Deletion cancelled.\n";
    }

    pause();
    clearScreen();
}

void TechFixSystem::viewAllRepairJobs() {
    cout << "\n" << string(90, '=') << endl;
    cout << "  ALL REPAIR JOBS  (" << repairJobs.getSize() << " total)" << endl;
    cout << string(90, '=') << endl;

    if (repairJobs.isEmpty()) {
        cout << "  (No repair jobs found)\n";
    } else {
        cout << left
             << setw(8)  << "  Job ID"
             << setw(6)  << "Urg"
             << setw(22) << "Device"
             << setw(20) << "Customer"
             << setw(16) << "Progress"
             << "Tasks" << endl;
        cout << string(90, '-') << endl;

        for (int i = 0; i < repairJobs.getSize(); i++) {
            const RepairJob& job = repairJobs.get(i);
            cout << "  " << left
                 << setw(6)  << job.getJobId()
                 << setw(6)  << (job.getIsUrgent() ? "[!!!]" : "     ")
                 << setw(22) << job.getDeviceModel().substr(0, 20)
                 << setw(20) << job.getCustomer().getName().substr(0, 18)
                 << setw(16) << job.getRepairProgress()
                 << job.getTasks().getSize() << " task(s)" << endl;
        }
    }

    cout << string(90, '=') << endl;
    pause();
    clearScreen();
}

// ============================================================================
// SEARCH MENU (Linear + Binary)
// ============================================================================

void TechFixSystem::searchMenu() {
    int choice;

    while (true) {
        cout << "\n" << string(65, '=') << endl;
        cout << "  SEARCH MENU" << endl;
        cout << string(65, '=') << endl;
        cout << "  1. Linear Search — Job by Job ID" << endl;
        cout << "  2. Binary Search — Part by Part ID (inventory, sorted)" << endl;
        cout << "  3. Linear Search — Part by Name (partial match)" << endl;
        cout << "  4. Back to Main Menu" << endl;
        cout << string(65, '=') << endl;

        choice = getIntInput("  Choice: ", 1, 4);
        if (choice == 4) { clearScreen(); return; }
        clearScreen();

        if (choice == 1) {
            // LINEAR SEARCH on repair jobs LinkedList by Job ID
            cout << "\n" << string(65, '=') << endl;
            cout << "  LINEAR SEARCH — Repair Job by Job ID" << endl;
            cout << "  (Scans each node in the linked list sequentially)" << endl;
            cout << string(65, '=') << endl;

            string jobId = getStringInput("  Enter Job ID (e.g., J-003): ");

            cout << "\n  Searching";
            int index = -1;
            for (int i = 0; i < repairJobs.getSize(); i++) {
                cout << "." << flush;
                if (repairJobs.get(i).getJobId() == jobId) {
                    index = i;
                    break;
                }
            }
            cout << endl;

            if (index != -1) {
                cout << "\n  [FOUND] Job at position " << (index + 1)
                     << " after " << (index + 1) << " comparison(s).\n";
                repairJobs.get(index).displayFull();
            } else {
                cout << "\n  [NOT FOUND] No job with ID '" << jobId << "'.\n";
            }

        } else if (choice == 2) {
            // BINARY SEARCH on inventory ArrayList by Part ID (sorted array)
            cout << "\n" << string(65, '=') << endl;
            cout << "  BINARY SEARCH — Spare Part by Part ID" << endl;
            cout << "  (Sorts inventory by ID first, then binary searches)" << endl;
            cout << string(65, '=') << endl;

            if (inventory.isEmpty()) {
                cout << "\n  [ERROR] Inventory is empty.\n";
                pause();
                clearScreen();
                continue;
            }

            string partId = getStringInput("  Enter Part ID (e.g., P-004): ");

            // Sort inventory by ID first (insertion sort)
            sortInventoryById();
            cout << "\n  [INFO] Inventory sorted by Part ID." << endl;

            // Binary search
            int index = binarySearchPartById(partId);

            if (index != -1) {
                cout << "\n  [FOUND] Part found!\n";
                cout << string(65, '-') << endl;
                inventory.get(index).display();
            } else {
                cout << "\n  [NOT FOUND] No part with ID '" << partId << "'.\n";
            }

        } else if (choice == 3) {
            // LINEAR SEARCH on inventory by part name (partial)
            cout << "\n" << string(65, '=') << endl;
            cout << "  LINEAR SEARCH — Spare Part by Name" << endl;
            cout << "  (Partial, case-insensitive name match)" << endl;
            cout << string(65, '=') << endl;

            string name = getStringInput("  Enter part name keyword: ");
            int index = linearSearchPartByName(name);

            if (index != -1) {
                cout << "\n  [FOUND] Matching part:\n";
                cout << string(65, '-') << endl;
                inventory.get(index).display();
            } else {
                cout << "\n  [NOT FOUND] No part matching '" << name << "'.\n";
            }
        }

        pause();
        clearScreen();
    }
}

// ============================================================================
// INVENTORY MANAGEMENT (Array-Based List)
// ============================================================================

void TechFixSystem::manageInventory() {
    int choice;
    while (true) {
        cout << "\n" << string(65, '=') << endl;
        cout << "  SPARE PARTS INVENTORY  (Array-Based List)" << endl;
        cout << string(65, '=') << endl;
        cout << "  1. View All Parts" << endl;
        cout << "  2. Add New Part" << endl;
        cout << "  3. Update Part" << endl;
        cout << "  4. Delete Part" << endl;
        cout << "  5. Search Parts" << endl;
        cout << "  6. Back to Main Menu" << endl;
        cout << string(65, '=') << endl;

        choice = getIntInput("  Choice: ", 1, 6);
        if (choice == 6) { clearScreen(); return; }
        clearScreen();

        switch (choice) {
            case 1: viewInventory();     break;
            case 2: addSparePart();      break;
            case 3: updateSparePart();   break;
            case 4: deleteSparePart();   break;
            case 5: searchInventory();   break;
        }
    }
}

void TechFixSystem::viewInventory() {
    cout << "\n" << string(70, '=') << endl;
    cout << "  SPARE PARTS INVENTORY  (" << inventory.getSize() << " parts)" << endl;
    cout << string(70, '=') << endl;

    if (inventory.isEmpty()) {
        cout << "  (No parts in inventory)\n";
    } else {
        cout << left
             << setw(10) << "  Part ID"
             << setw(32) << "Part Name"
             << setw(10) << "Qty"
             << "Unit Price" << endl;
        cout << string(70, '-') << endl;
        for (int i = 0; i < inventory.getSize(); i++) {
            cout << "  ";
            inventory.get(i).display();
        }
    }

    cout << string(70, '=') << endl;
    pause();
    clearScreen();
}

void TechFixSystem::addSparePart() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  ADD NEW SPARE PART" << endl;
    cout << string(65, '=') << endl;

    string name  = getStringInput("  Part name: ");
    int    qty   = getIntInput("  Quantity: ", 0, 9999);
    double price = getDoubleInput("  Unit price (RM): ", 0.0);

    string partId = generatePartId();
    inventory.add(SparePart(partId, name, qty, price));

    cout << "\n  [SUCCESS] Part " << partId << " added to inventory.\n";
    pause();
    clearScreen();
}

void TechFixSystem::updateSparePart() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  UPDATE SPARE PART" << endl;
    cout << string(65, '=') << endl;

    if (inventory.isEmpty()) {
        cout << "\n  [ERROR] Inventory is empty.\n";
        pause();
        return;
    }

    string partId = getStringInput("  Enter Part ID to update (e.g., P-002): ");
    sortInventoryById();
    int index = binarySearchPartById(partId);

    if (index == -1) {
        cout << "\n  [ERROR] Part ID '" << partId << "' not found.\n";
        pause();
        return;
    }

    SparePart& part = inventory.get(index);
    cout << "\n  Current details:\n";
    part.display();

    cout << "\n  What to update?" << endl;
    cout << "  1. Part Name" << endl;
    cout << "  2. Quantity" << endl;
    cout << "  3. Unit Price" << endl;
    cout << "  4. Cancel" << endl;

    int choice = getIntInput("  Choice: ", 1, 4);
    switch (choice) {
        case 1: {
            string newName = getStringInput("  New part name: ");
            part.setPartName(newName);
            cout << "  [SUCCESS] Part name updated.\n";
            break;
        }
        case 2: {
            int newQty = getIntInput("  New quantity: ", 0, 9999);
            part.setQuantity(newQty);
            cout << "  [SUCCESS] Quantity updated.\n";
            break;
        }
        case 3: {
            double newPrice = getDoubleInput("  New unit price (RM): ", 0.0);
            part.setPrice(newPrice);
            cout << "  [SUCCESS] Price updated.\n";
            break;
        }
        case 4:
            cout << "  Update cancelled.\n";
            break;
    }

    pause();
    clearScreen();
}

void TechFixSystem::deleteSparePart() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  DELETE SPARE PART" << endl;
    cout << string(65, '=') << endl;

    if (inventory.isEmpty()) {
        cout << "\n  [ERROR] Inventory is empty.\n";
        pause();
        return;
    }

    string partId = getStringInput("  Enter Part ID to delete (e.g., P-005): ");
    sortInventoryById();
    int index = binarySearchPartById(partId);

    if (index == -1) {
        cout << "\n  [ERROR] Part ID '" << partId << "' not found.\n";
        pause();
        return;
    }

    cout << "\n  Part to delete:\n";
    inventory.get(index).display();

    cout << "\n  Confirm delete? (y/n): ";
    char c;
    cin >> c;
    clearInputBuffer();

    if (c == 'y' || c == 'Y') {
        inventory.removeAt(index);
        cout << "\n  [SUCCESS] Part " << partId << " deleted.\n";
    } else {
        cout << "  Deletion cancelled.\n";
    }

    pause();
    clearScreen();
}

void TechFixSystem::searchInventory() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  SEARCH INVENTORY" << endl;
    cout << string(65, '=') << endl;
    cout << "  1. Binary Search by Part ID" << endl;
    cout << "  2. Linear Search by Part Name" << endl;
    cout << "  3. Cancel" << endl;

    int choice = getIntInput("  Choice: ", 1, 3);
    if (choice == 3) { clearScreen(); return; }

    if (choice == 1) {
        string pid = getStringInput("  Enter Part ID: ");
        sortInventoryById();
        int idx = binarySearchPartById(pid);
        if (idx != -1) { cout << "  [FOUND]\n"; inventory.get(idx).display(); }
        else             cout << "  [NOT FOUND] No part with ID '" << pid << "'.\n";
    } else {
        string name = getStringInput("  Enter part name keyword: ");
        int idx = linearSearchPartByName(name);
        if (idx != -1) { cout << "  [FOUND]\n"; inventory.get(idx).display(); }
        else             cout << "  [NOT FOUND] No part matching '" << name << "'.\n";
    }

    pause();
    clearScreen();
}

// ============================================================================
// CUSTOMER MANAGEMENT (Array-Based List)
// ============================================================================

void TechFixSystem::manageCustomers() {
    int choice;
    while (true) {
        cout << "\n" << string(65, '=') << endl;
        cout << "  CUSTOMER MANAGEMENT  (Array-Based List)" << endl;
        cout << string(65, '=') << endl;
        cout << "  1. View All Customers" << endl;
        cout << "  2. Add Customer" << endl;
        cout << "  3. Update Customer" << endl;
        cout << "  4. Delete Customer" << endl;
        cout << "  5. Back to Main Menu" << endl;
        cout << string(65, '=') << endl;

        choice = getIntInput("  Choice: ", 1, 5);
        if (choice == 5) { clearScreen(); return; }
        clearScreen();

        switch (choice) {
            case 1: viewAllCustomers(); break;
            case 2: addCustomer();      break;
            case 3: updateCustomer();   break;
            case 4: deleteCustomer();   break;
        }
    }
}

void TechFixSystem::viewAllCustomers() {
    cout << "\n" << string(70, '=') << endl;
    cout << "  ALL CUSTOMERS  (" << customers.getSize() << " total)" << endl;
    cout << string(70, '=') << endl;

    if (customers.isEmpty()) {
        cout << "  (No customers found)\n";
    } else {
        cout << left
             << setw(12) << "  ID"
             << setw(22) << "Name"
             << setw(18) << "Contact"
             << "Email" << endl;
        cout << string(70, '-') << endl;
        for (int i = 0; i < customers.getSize(); i++) {
            const Customer& c = customers.get(i);
            cout << "  " << left
                 << setw(10) << c.getCustomerId()
                 << setw(22) << c.getName()
                 << setw(18) << c.getContactNumber()
                 << c.getEmail() << endl;
        }
    }

    cout << string(70, '=') << endl;
    pause();
    clearScreen();
}

void TechFixSystem::addCustomer() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  ADD NEW CUSTOMER" << endl;
    cout << string(65, '=') << endl;

    string name    = getStringInput("  Full name: ");
    string contact = getStringInput("  Contact number: ");
    string email   = getStringInput("  Email address: ");

    string cid = generateCustomerId();
    customers.add(Customer(cid, name, contact, email));

    cout << "\n  [SUCCESS] Customer " << cid << " (" << name << ") added.\n";
    pause();
    clearScreen();
}

void TechFixSystem::updateCustomer() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  UPDATE CUSTOMER" << endl;
    cout << string(65, '=') << endl;

    if (customers.isEmpty()) {
        cout << "\n  [ERROR] No customers found.\n";
        pause();
        return;
    }

    string cid = getStringInput("  Enter Customer ID to update (e.g., C-002): ");

    // Linear search on customer array
    int found = -1;
    for (int i = 0; i < customers.getSize(); i++) {
        if (customers.get(i).getCustomerId() == cid) { found = i; break; }
    }

    if (found == -1) {
        cout << "\n  [ERROR] Customer ID '" << cid << "' not found.\n";
        pause();
        return;
    }

    Customer& c = customers.get(found);
    cout << "\n  Current details:\n";
    c.display();

    cout << "\n  What to update?" << endl;
    cout << "  1. Name" << endl;
    cout << "  2. Contact Number" << endl;
    cout << "  3. Email" << endl;
    cout << "  4. Cancel" << endl;

    int choice = getIntInput("  Choice: ", 1, 4);
    switch (choice) {
        case 1: c.setName(getStringInput("  New name: "));                  cout << "  [SUCCESS] Name updated.\n";    break;
        case 2: c.setContactNumber(getStringInput("  New contact: "));      cout << "  [SUCCESS] Contact updated.\n"; break;
        case 3: c.setEmail(getStringInput("  New email: "));                cout << "  [SUCCESS] Email updated.\n";   break;
        case 4: cout << "  Update cancelled.\n"; break;
    }

    pause();
    clearScreen();
}

void TechFixSystem::deleteCustomer() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  DELETE CUSTOMER" << endl;
    cout << string(65, '=') << endl;

    if (customers.isEmpty()) {
        cout << "\n  [ERROR] No customers found.\n";
        pause();
        return;
    }

    string cid = getStringInput("  Enter Customer ID to delete (e.g., C-003): ");

    int found = -1;
    for (int i = 0; i < customers.getSize(); i++) {
        if (customers.get(i).getCustomerId() == cid) { found = i; break; }
    }

    if (found == -1) {
        cout << "\n  [ERROR] Customer ID '" << cid << "' not found.\n";
        pause();
        return;
    }

    customers.get(found).display();

    cout << "\n  Confirm delete customer " << cid << "? (y/n): ";
    char c;
    cin >> c;
    clearInputBuffer();

    if (c == 'y' || c == 'Y') {
        customers.removeAt(found);
        cout << "\n  [SUCCESS] Customer " << cid << " deleted.\n";
    } else {
        cout << "  Deletion cancelled.\n";
    }

    pause();
    clearScreen();
}

// ============================================================================
// DEVICE INTAKE QUEUE (FIFO — First In, First Out)
// Simulates the incoming device waitlist: devices are processed in arrival order
// ============================================================================

void TechFixSystem::manageDeviceQueue() {
    int choice;
    while (true) {
        cout << "\n" << string(65, '=') << endl;
        cout << "  DEVICE INTAKE QUEUE  [FIFO — First In, First Out]" << endl;
        cout << "  Incoming devices are queued and processed in arrival order." << endl;
        cout << string(65, '=') << endl;
        cout << "  Queue size: " << deviceQueue.getSize() << " device(s) waiting\n" << endl;
        cout << "  1. View Queue (current waiting devices)" << endl;
        cout << "  2. Process Next Device (Dequeue)" << endl;
        cout << "  3. Back to Main Menu" << endl;
        cout << string(65, '=') << endl;

        choice = getIntInput("  Choice: ", 1, 3);
        if (choice == 3) { clearScreen(); return; }
        clearScreen();

        if (choice == 1) {
            // View the queue without removing anything
            cout << "\n" << string(65, '=') << endl;
            cout << "  WAITING DEVICES IN QUEUE (front → rear)" << endl;
            cout << string(65, '=') << endl;

            if (deviceQueue.isEmpty()) {
                cout << "  (Queue is empty — no devices waiting)\n";
            } else {
                cout << left << setw(6) << "  Pos"
                     << setw(10) << "Job ID"
                     << setw(22) << "Device"
                     << setw(20) << "Customer"
                     << "Status" << endl;
                cout << string(65, '-') << endl;

                // We need to walk the queue without destroying it
                // Build a temp copy to iterate
                Queue<string> tempQ = deviceQueue;
                int pos = 1;
                while (!tempQ.isEmpty()) {
                    string jid = tempQ.dequeue();
                    int idx = linearSearchJobById(jid);
                    cout << "  " << left << setw(4) << pos++;
                    if (idx != -1) {
                        const RepairJob& job = repairJobs.get(idx);
                        cout << setw(10) << job.getJobId()
                             << setw(22) << job.getDeviceModel().substr(0, 20)
                             << setw(20) << job.getCustomer().getName().substr(0, 18)
                             << job.getJobStatus() << endl;
                    } else {
                        cout << setw(10) << jid << "(job no longer exists)\n";
                    }
                }
            }
            cout << string(65, '=') << endl;
            pause();
            clearScreen();

        } else if (choice == 2) {
            // Dequeue the next device and process it
            if (deviceQueue.isEmpty()) {
                cout << "\n  [INFO] Queue is empty! No devices to process.\n";
                pause();
                clearScreen();
                continue;
            }

            string jid = deviceQueue.dequeue();
            cout << "\n  [DEQUEUED] Processing device for Job: " << jid << endl;
            cout << string(65, '-') << endl;

            int idx = linearSearchJobById(jid);
            if (idx != -1) {
                RepairJob& job = repairJobs.get(idx);
                job.displayFull();
                // Auto-update status to In Progress
                if (job.getJobStatus() == "Pending Initial Diagnostics") {
                    job.setJobStatus("In Progress");
                    job.setRepairProgress("In Progress");
                    cout << "\n  [AUTO] Job status updated to 'In Progress'.\n";
                }
                cout << "\n  Remaining in queue: " << deviceQueue.getSize() << endl;
            } else {
                cout << "  [WARN] Job " << jid << " no longer exists in system.\n";
            }

            pause();
            clearScreen();
        }
    }
}

// ============================================================================
// URGENT REPAIRS STACK (LIFO — Last In, First Out)
// Most recently flagged urgent job is always processed first
// ============================================================================

void TechFixSystem::manageUrgentStack() {
    int choice;
    while (true) {
        cout << "\n" << string(65, '=') << endl;
        cout << "  URGENT REPAIRS STACK  [LIFO — Last In, First Out]" << endl;
        cout << "  Most recently flagged urgent job is on top and processed first." << endl;
        cout << string(65, '=') << endl;
        cout << "  Stack size: " << urgentStack.getSize() << " urgent job(s)\n" << endl;
        cout << "  1. View Urgent Stack" << endl;
        cout << "  2. Push Job onto Urgent Stack" << endl;
        cout << "  3. Process Top Urgent Job (Pop)" << endl;
        cout << "  4. Peek Top Job" << endl;
        cout << "  5. Back to Main Menu" << endl;
        cout << string(65, '=') << endl;

        choice = getIntInput("  Choice: ", 1, 5);
        if (choice == 5) { clearScreen(); return; }
        clearScreen();

        if (choice == 1) {
            cout << "\n" << string(65, '=') << endl;
            cout << "  URGENT STACK (top → bottom)" << endl;
            cout << string(65, '=') << endl;

            if (urgentStack.isEmpty()) {
                cout << "  (Stack is empty via no urgent jobs)\n";
            } else {
                // Walk stack without destroying it using copy
                Stack<string> tempS = urgentStack;
                int pos = 1;
                while (!tempS.isEmpty()) {
                    string jid = tempS.pop();
                    int idx = linearSearchJobById(jid);
                    cout << "  [" << pos++ << "] Job: " << jid;
                    if (idx != -1) {
                        const RepairJob& job = repairJobs.get(idx);
                        cout << "  |  " << job.getDeviceModel()
                             << "  |  " << job.getCustomer().getName()
                             << "  |  " << job.getRepairProgress();
                    } else {
                        cout << "  (no longer in system)";
                    }
                    cout << endl;
                }
            }
            cout << string(65, '=') << endl;
            pause();
            clearScreen();

        } else if (choice == 2) {
            // Push a job onto the urgent stack
            if (repairJobs.isEmpty()) {
                cout << "\n  [ERROR] No repair jobs exist.\n";
                pause();
                clearScreen();
                continue;
            }

            string jid = getStringInput("  Enter Job ID to flag as urgent: ");
            int idx = linearSearchJobById(jid);

            if (idx == -1) {
                cout << "\n  [ERROR] Job ID '" << jid << "' not found.\n";
            } else {
                repairJobs.get(idx).setIsUrgent(true);
                urgentStack.push(jid);
                cout << "\n  [SUCCESS] Job " << jid << " pushed onto urgent stack.\n";
            }

            pause();
            clearScreen();

        } else if (choice == 3) {
            // Pop the top urgent job and process it
            if (urgentStack.isEmpty()) {
                cout << "\n  [INFO] Stack is empty. No urgent jobs to process.\n";
                pause();
                clearScreen();
                continue;
            }

            string jid = urgentStack.pop();
            cout << "\n  [POPPED] Processing urgent job: " << jid << endl;
            cout << string(65, '-') << endl;

            int idx = linearSearchJobById(jid);
            if (idx != -1) {
                RepairJob& job = repairJobs.get(idx);
                job.displayFull();
                job.setIsUrgent(false);
                job.setJobStatus("In Progress");
                cout << "\n  [AUTO] Urgent flag cleared. Status set to 'In Progress'.\n";
                cout << "  Remaining urgent jobs: " << urgentStack.getSize() << endl;
            } else {
                cout << "  [WARN] Job " << jid << " no longer exists in system.\n";
            }

            pause();
            clearScreen();

        } else if (choice == 4) {
            // Peek top — no removal
            if (urgentStack.isEmpty()) {
                cout << "\n  [INFO] Stack is empty.\n";
            } else {
                string jid = urgentStack.peek();
                cout << "\n  [TOP OF STACK] Job: " << jid << endl;
                int idx = linearSearchJobById(jid);
                if (idx != -1) repairJobs.get(idx).displayFull();
                else cout << "  (job no longer in system)\n";
            }
            pause();
            clearScreen();
        }
    }
}

// ============================================================================
// SUMMARY REPORT — Active Job Routing & Task Report (Matches Figure-1)
// ============================================================================

void TechFixSystem::viewSummaryReport() {
    cout << "\n" << string(65, '=') << endl;
    cout << "  ACTIVE JOB ROUTING & TASK REPORT" << endl;
    cout << string(65, '=') << endl;
    cout << "  Sort by:" << endl;
    cout << "  1. Job ID (default) via Quick Sort" << endl;
    cout << "  2. Repair Progress  via Bubble Sort" << endl;
    cout << string(65, '=') << endl;

    int sortChoice = getIntInput("  Choice: ", 1, 2);
    clearScreen();

    if (sortChoice == 1) {
        cout << "\n  [INFO] Sorting by Job ID using QUICK SORT...\n";
        quickSortByJobId(0, repairJobs.getSize() - 1);
    } else {
        cout << "\n  [INFO] Sorting by Repair Progress using BUBBLE SORT...\n";
        bubbleSortByProgress();
    }

    // Column widths matching Figure-1
    const int W_JOB      = 8;
    const int W_CUST     = 16;
    const int W_DEVICE   = 20;
    const int W_STATUS   = 42;
    const int W_PROGRESS = 16;
    const int TOTAL      = W_JOB + W_CUST + W_DEVICE + W_STATUS + W_PROGRESS + 4;

    cout << "\n" << string(TOTAL, '=') << endl;
    cout << "  TECHFIX — ACTIVE JOB ROUTING & TASK REPORT" << endl;
    if (sortChoice == 1)
        cout << "  Sorted by: Job ID (Quick Sort)" << endl;
    else
        cout << "  Sorted by: Repair Progress (Bubble Sort)" << endl;
    cout << string(TOTAL, '=') << endl;

    cout << left
         << setw(W_JOB)      << "Job ID"
         << setw(W_CUST)     << "Customer"
         << setw(W_DEVICE)   << "Device"
         << setw(W_STATUS)   << "Current Job Status"
         << setw(W_PROGRESS) << "Progress"
         << "Repair Tasks" << endl;
    cout << string(TOTAL, '-') << endl;

    if (repairJobs.isEmpty()) {
        cout << "  (No repair jobs)\n";
    } else {
        for (int i = 0; i < repairJobs.getSize(); i++) {
            const RepairJob& job = repairJobs.get(i);

            // Truncate long strings so columns don't break
            string jid     = job.getJobId();
            string cust    = job.getCustomer().getName();
            string device  = job.getDeviceModel();
            string status  = job.getJobStatus();
            string prog    = job.getRepairProgress();
            string tasks   = job.getTasksString();

            if (cust.size()   > (size_t)(W_CUST   - 1)) cust   = cust.substr(0, W_CUST - 2)   + ".";
            if (device.size() > (size_t)(W_DEVICE - 1)) device = device.substr(0, W_DEVICE - 2) + ".";
            if (status.size() > (size_t)(W_STATUS - 1)) status = status.substr(0, W_STATUS - 2) + ".";

            cout << left
                 << setw(W_JOB)      << jid
                 << setw(W_CUST)     << cust
                 << setw(W_DEVICE)   << device
                 << setw(W_STATUS)   << status
                 << setw(W_PROGRESS) << prog
                 << tasks << endl;
        }
    }

    cout << string(TOTAL, '=') << endl;
    cout << "  Total Jobs: " << repairJobs.getSize() << endl;
    cout << string(TOTAL, '=') << endl;

    pause();
    clearScreen();
}
