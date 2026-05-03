#include "TechFix.h"
#include <algorithm>

// ============================================================================
// TECH FIX SYSTEM IMPLEMENTATION
// ============================================================================

TechFixSystem::TechFixSystem() : nextJobNumber(1) {
	initializePresetData();
}

void TechFixSystem::clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void TechFixSystem::pause() {
	cout << "\nPress Enter to continue...";
	cin.ignore();
	cin.get();
}

// ----------------- INITIALIZE PRESET DATA -----------------
void TechFixSystem::initializePresetData() {
	// Create preset customers
	customers.add(Customer("C-001", "John Smith", "012-3456789", "john@email.com"));
	customers.add(Customer("C-002", "Alice Wong", "013-9876543", "alice@email.com"));
	customers.add(Customer("C-003", "Bob Lee", "014-5551234", "bob@email.com"));
	customers.add(Customer("C-004", "Sarah Chen", "015-7778888", "sarah@email.com"));
	customers.add(Customer("C-005", "David Tan", "016-9990000", "david@email.com"));

	// Create preset spare parts inventory (Array-based list)
	inventory.add(SparePart("P-001", "iPhone Screen Replacement", 15, 299.99));
	inventory.add(SparePart("P-002", "MacBook Battery", 8, 450.00));
	inventory.add(SparePart("P-003", "iPad Digitizer", 12, 350.00));
	inventory.add(SparePart("P-004", "Laptop Fan", 20, 45.00));
	inventory.add(SparePart("P-005", "USB-C Charging Port", 25, 35.00));
	inventory.add(SparePart("P-006", "Motherboard Chip", 5, 680.00));
	inventory.add(SparePart("P-007", "Water Damage Kit", 10, 120.00));

	// Create preset repair jobs with tasks in Queue
	RepairJob job1("J-001", customers.get(0), "iPhone 13");
	job1.addTask(RepairTask("Hardware Diagnostics", "Completed"));
	job1.addTask(RepairTask("Water Damage Cleaning", "Completed"));
	job1.setJobStatus("Closed");
	job1.setRepairProgress("Completed");
	repairJobs.add(job1);

	RepairJob job2("J-002", customers.get(1), "Samsung Galaxy S22");
	job2.addTask(RepairTask("Hardware Diagnostics", "Completed"));
	job2.addTask(RepairTask("Screen Replacement", "In Progress"));
	job2.addTask(RepairTask("Quality Check", "Pending"));
	job2.setJobStatus("Queued for Specialist: Screen Repair Technician");
	job2.setRepairProgress("In Progress");
	repairJobs.add(job2);

	RepairJob job3("J-003", customers.get(2), "MacBook Air M2");
	job3.addTask(RepairTask("Hardware Diagnostics", "In Progress"));
	job3.addTask(RepairTask("Fan Replacement", "Pending"));
	job3.setJobStatus("Pending Initial Diagnostics");
	job3.setRepairProgress("In Progress");
	repairJobs.add(job3);

	RepairJob job4("J-004", customers.get(3), "Dell XPS 15");
	job4.addTask(RepairTask("Motherboard Microsoldering", "Pending"));
	job4.addTask(RepairTask("OS Restoration", "Pending"));
	job4.setJobStatus("Queued for Specialist: Motherboard Technician");
	job4.setRepairProgress("Pending");
	repairJobs.add(job4);

	RepairJob job5("J-005", customers.get(4), "iPad Pro 11\"");
	job5.addTask(RepairTask("Hardware Diagnostics", "Completed"));
	job5.addTask(RepairTask("Battery Replacement", "Completed"));
	job5.addTask(RepairTask("Quality Check", "Completed"));
	job5.setJobStatus("Ready for Customer Pickup");
	job5.setRepairProgress("Completed");
	repairJobs.add(job5);

	nextJobNumber = 6; // Next job will be J-006
}

// ----------------- MAIN MENU -----------------
void TechFixSystem::displayMainMenu() {
	cout << "\n" << string(70, '=') << endl;
	cout << "               TECHFIX - DEVICE REPAIR MANAGEMENT SYSTEM" << endl;
	cout << string(70, '=') << endl;
	cout << "  1. Add New Repair Job" << endl;
	cout << "  2. Update Repair Job" << endl;
	cout << "  3. Delete Repair Job" << endl;
	cout << "  4. View All Repair Jobs" << endl;
	cout << "  5. Search Repair Job (Linear & Binary Search)" << endl;
	cout << "  6. Manage Spare Parts Inventory" << endl;
	cout << "  7. Manage Customers" << endl;
	cout << "  8. View Active Job Routing & Task Report (Sorted)" << endl;
	cout << "  9. Exit" << endl;
	cout << string(70, '=') << endl;
	cout << "  Enter your choice: ";
}

void TechFixSystem::run() {
	int choice;
	bool running = true;

	while (running) {
		displayMainMenu();
		cin >> choice;
		cin.ignore();

		clearScreen();

		switch (choice) {
			case 1:
				addRepairJob();
				break;
			case 2:
				updateRepairJob();
				break;
			case 3:
				deleteRepairJob();
				break;
			case 4:
				viewAllRepairJobs();
				break;
			case 5:
				searchRepairJob();
				break;
			case 6:
				manageInventory();
				break;
			case 7:
				manageCustomers();
				break;
			case 8:
				viewSummaryReport();
				break;
			case 9:
				cout << "\n Thank you for using TechFix System! Goodbye.\n" << endl;
				running = false;
				break;
			default:
				cout << "\n[ERROR] Invalid choice! Please enter 1-9." << endl;
				pause();
				clearScreen();
		}
	}
}

// ----------------- ADD REPAIR JOB -----------------
void TechFixSystem::addRepairJob() {
	cout << "\n" << string(60, '=') << endl;
	cout << "ADD NEW REPAIR JOB" << endl;
	cout << string(60, '=') << endl;

	// Select customer
	if (customers.isEmpty()) {
		cout << "[ERROR] No customers found! Please add customers first." << endl;
		pause();
		return;
	}

	cout << "\nAvailable Customers:" << endl;
	for (int i = 0; i < customers.getSize(); i++) {
		cout << (i + 1) << ". " << customers.get(i).getName() 
			<< " (" << customers.get(i).getCustomerId() << ")" << endl;
	}

	int custChoice;
	cout << "\nSelect customer (1-" << customers.getSize() << "): ";
	cin >> custChoice;
	cin.ignore();

	if (custChoice < 1 || custChoice > customers.getSize()) {
		cout << "[ERROR] Invalid customer selection!" << endl;
		pause();
		return;
	}

	Customer selectedCustomer = customers.get(custChoice - 1);

	// Get device model
	string deviceModel;
	cout << "Enter device model (e.g., iPhone 14, MacBook Pro): ";
	getline(cin, deviceModel);

	if (deviceModel.empty()) {
		cout << "[ERROR] Device model cannot be empty!" << endl;
		pause();
		return;
	}

	// Create new repair job
	string jobId = generateJobId();
	RepairJob newJob(jobId, selectedCustomer, deviceModel);

	// Add repair tasks using Queue
	cout << "\n--- Add Repair Tasks (Enter 'done' when finished) ---" << endl;
	int taskCount = 0;

	while (true) {
		string taskName;
		cout << "Task " << (taskCount + 1) << ": ";
		getline(cin, taskName);

		if (taskName == "done" || taskName == "DONE") {
			break;
		}

		if (taskName.empty()) {
			continue;
		}

		newJob.addTask(RepairTask(taskName, "Pending"));
		taskCount++;

		if (taskCount >= 10) {
			cout << "[INFO] Maximum 10 tasks reached." << endl;
			break;
		}
	}

	if (taskCount == 0) {
		cout << "[WARNING] No tasks added. Adding default diagnostic task." << endl;
		newJob.addTask(RepairTask("Hardware Diagnostics", "Pending"));
	}

	// Add to linked list
	repairJobs.add(newJob);

	cout << "\n[SUCCESS] Repair job " << jobId << " created successfully!" << endl;
	cout << "Device: " << deviceModel << endl;
	cout << "Customer: " << selectedCustomer.getName() << endl;
	cout << "Tasks added: " << taskCount << endl;

	pause();
	clearScreen();
}

// ----------------- UPDATE REPAIR JOB -----------------
void TechFixSystem::updateRepairJob() {
	cout << "\n" << string(60, '=') << endl;
	cout << "UPDATE REPAIR JOB" << endl;
	cout << string(60, '=') << endl;

	if (repairJobs.isEmpty()) {
		cout << "[ERROR] No repair jobs found!" << endl;
		pause();
		return;
	}

	string jobId;
	cout << "Enter Job ID to update (e.g., J-001): ";
	getline(cin, jobId);

	// Linear search for job
	int index = linearSearchByJobId(jobId);

	if (index == -1) {
		cout << "[ERROR] Job ID not found!" << endl;
		pause();
		return;
	}

	RepairJob& job = repairJobs.get(index);
	job.displayFull();

	cout << "\n--- Update Options ---" << endl;
	cout << "1. Update Job Status" << endl;
	cout << "2. Update Repair Progress" << endl;
	cout << "3. Add New Task to Queue" << endl;
	cout << "4. Cancel" << endl;
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.ignore();

	switch (choice) {
		case 1: {
				string newStatus;
				cout << "\nCurrent Status: " << job.getJobStatus() << endl;
				cout << "Enter new status: ";
				getline(cin, newStatus);
				job.setJobStatus(newStatus);
				cout << "[SUCCESS] Job status updated!" << endl;
				break;
			}
		case 2: {
				string newProgress;
				cout << "\nCurrent Progress: " << job.getRepairProgress() << endl;
				cout << "Enter new progress: ";
				getline(cin, newProgress);
				job.setRepairProgress(newProgress);
				cout << "[SUCCESS] Repair progress updated!" << endl;
				break;
			}
		case 3: {
				string taskName;
				cout << "\nEnter new task name: ";
				getline(cin, taskName);
				job.addTask(RepairTask(taskName, "Pending"));
				cout << "[SUCCESS] Task added to queue!" << endl;
				break;
			}
		case 4:
			cout << "Update cancelled." << endl;
			break;
		default:
			cout << "[ERROR] Invalid choice!" << endl;
	}

	pause();
	clearScreen();
}

// ----------------- DELETE REPAIR JOB -----------------
void TechFixSystem::deleteRepairJob() {
	cout << "\n" << string(60, '=') << endl;
	cout << "DELETE REPAIR JOB" << endl;
	cout << string(60, '=') << endl;

	if (repairJobs.isEmpty()) {
		cout << "[ERROR] No repair jobs found!" << endl;
		pause();
		return;
	}

	string jobId;
	cout << "Enter Job ID to delete (e.g., J-001): ";
	getline(cin, jobId);

	int index = linearSearchByJobId(jobId);

	if (index == -1) {
		cout << "[ERROR] Job ID not found!" << endl;
		pause();
		return;
	}

	RepairJob& job = repairJobs.get(index);
	job.displayFull();

	char confirm;
	cout << "\nAre you sure you want to delete this job? (y/n): ";
	cin >> confirm;
	cin.ignore();

	if (confirm == 'y' || confirm == 'Y') {
		repairJobs.removeAt(index);
		cout << "\n[SUCCESS] Repair job deleted successfully!" << endl;
	} else {
		cout << "\nDeletion cancelled." << endl;
	}

	pause();
	clearScreen();
}

// ----------------- VIEW ALL REPAIR JOBS -----------------
void TechFixSystem::viewAllRepairJobs() {
	cout << "\n" << string(80, '=') << endl;
	cout << "ALL REPAIR JOBS" << endl;
	cout << string(80, '=') << endl;

	if (repairJobs.isEmpty()) {
		cout << "No repair jobs found." << endl;
	} else {
		cout << left << setw(8) << "Job ID"
			<< setw(20) << "Device"
			<< setw(25) << "Status"
			<< setw(15) << "Progress"
			<< "Tasks" << endl;
		cout << string(80, '-') << endl;

		for (int i = 0; i < repairJobs.getSize(); i++) {
			repairJobs.get(i).displaySummary();
			cout << endl;
		}
	}

	cout << string(80, '=') << endl;
	cout << "Total Jobs: " << repairJobs.getSize() << endl;

	pause();
	clearScreen();
}

// ----------------- SEARCH FUNCTIONS -----------------
int TechFixSystem::linearSearchByJobId(string jobId) {
	// LINEAR SEARCH implementation
	for (int i = 0; i < repairJobs.getSize(); i++) {
		if (repairJobs.get(i).getJobId() == jobId) {
			return i;
		}
	}
	return -1;
}

int TechFixSystem::binarySearchByJobId(string jobId) {
	// BINARY SEARCH implementation (requires sorted data)
	// First, we need to sort by Job ID
	// For simplicity, we'll create a temporary sorted array
	int size = repairJobs.getSize();
	if (size == 0) return -1;

	// Binary search on linked list (inefficient, but demonstrates concept)
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		string midJobId = repairJobs.get(mid).getJobId();

		if (midJobId == jobId) {
			return mid;
		} else if (midJobId < jobId) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	return -1;
}

void TechFixSystem::searchRepairJob() {
	cout << "\n" << string(60, '=') << endl;
	cout << "SEARCH REPAIR JOB" << endl;
	cout << string(60, '=') << endl;

	cout << "1. Linear Search (works on unsorted data)" << endl;
	cout << "2. Binary Search (requires sorted data)" << endl;
	cout << "Choice: ";

	int searchChoice;
	cin >> searchChoice;
	cin.ignore();

	string jobId;
	cout << "\nEnter Job ID to search (e.g., J-001): ";
	getline(cin, jobId);

	int index = -1;

	if (searchChoice == 1) {
		cout << "\n[INFO] Using LINEAR SEARCH..." << endl;
		index = linearSearchByJobId(jobId);
	} else if (searchChoice == 2) {
		cout << "\n[INFO] Using BINARY SEARCH..." << endl;
		cout << "[INFO] Data will be sorted first by Job ID..." << endl;
		sortByJobId(0, repairJobs.getSize() - 1);
		index = binarySearchByJobId(jobId);
	} else {
		cout << "[ERROR] Invalid choice!" << endl;
		pause();
		clearScreen();
		return;
	}

	if (index != -1) {
		cout << "\n[SUCCESS] Job found at position " << (index + 1) << "!" << endl;
		repairJobs.get(index).displayFull();
	} else {
		cout << "\n[ERROR] Job ID '" << jobId << "' not found!" << endl;
	}

	pause();
	clearScreen();
}

// ----------------- INVENTORY MANAGEMENT -----------------
void TechFixSystem::manageInventory() {
	int choice;

	while (true) {
		cout << "\n" << string(60, '=') << endl;
		cout << "SPARE PARTS INVENTORY MANAGEMENT" << endl;
		cout << string(60, '=') << endl;
		cout << "1. View All Spare Parts" << endl;
		cout << "2. Add New Spare Part" << endl;
		cout << "3. Search Spare Part" << endl;
		cout << "4. Back to Main Menu" << endl;
		cout << string(60, '=') << endl;
		cout << "Choice: ";
		cin >> choice;
		cin.ignore();

		clearScreen();

		switch (choice) {
			case 1:
				viewInventory();
				break;
			case 2:
				addSparePart();
				break;
			case 3:
				searchInventory();
				break;
			case 4:
				return;
			default:
				cout << "[ERROR] Invalid choice!" << endl;
				pause();
				clearScreen();
		}
	}
}

void TechFixSystem::viewInventory() {
	cout << "\n" << string(70, '=') << endl;
	cout << "SPARE PARTS INVENTORY" << endl;
	cout << string(70, '=') << endl;

	if (inventory.isEmpty()) {
		cout << "No spare parts in inventory." << endl;
	} else {
		cout << left << setw(10) << "Part ID"
			<< setw(30) << "Part Name"
			<< setw(10) << "Quantity"
			<< "Price" << endl;
		cout << string(70, '-') << endl;

		for (int i = 0; i < inventory.getSize(); i++) {
			inventory.get(i).display();
		}
	}

	cout << string(70, '=') << endl;
	cout << "Total Parts: " << inventory.getSize() << endl;

	pause();
	clearScreen();
}

void TechFixSystem::addSparePart() {
	cout << "\n" << string(60, '=') << endl;
	cout << "ADD NEW SPARE PART" << endl;
	cout << string(60, '=') << endl;

	string partName;
	int quantity;
	double price;

	cout << "Enter part name: ";
	getline(cin, partName);

	cout << "Enter quantity: ";
	cin >> quantity;

	cout << "Enter price (RM): ";
	cin >> price;
	cin.ignore();

	if (quantity < 0 || price < 0) {
		cout << "[ERROR] Invalid quantity or price!" << endl;
		pause();
		clearScreen();
		return;
	}

	string partId = generatePartId(inventory.getSize() + 1);
	inventory.add(SparePart(partId, partName, quantity, price));

	cout << "\n[SUCCESS] Spare part added successfully!" << endl;
	cout << "Part ID: " << partId << endl;

	pause();
	clearScreen();
}

void TechFixSystem::searchInventory() {
	cout << "\n" << string(60, '=') << endl;
	cout << "SEARCH SPARE PART" << endl;
	cout << string(60, '=') << endl;

	string searchTerm;
	cout << "Enter part name or ID to search: ";
	getline(cin, searchTerm);

	cout << "\n[INFO] Using LINEAR SEARCH..." << endl;

	bool found = false;
	for (int i = 0; i < inventory.getSize(); i++) {
		if (inventory.get(i).getPartId() == searchTerm ||
				inventory.get(i).getPartName().find(searchTerm) != string::npos) {

			if (!found) {
				cout << "\n[SUCCESS] Found matching parts:" << endl;
				cout << left << setw(10) << "Part ID"
					<< setw(30) << "Part Name"
					<< setw(10) << "Quantity"
					<< "Price" << endl;
				cout << string(70, '-') << endl;
				found = true;
			}
			inventory.get(i).display();
		}
	}

	if (!found) {
		cout << "\n[ERROR] No matching parts found!" << endl;
	}

	pause();
	clearScreen();
}

// ----------------- CUSTOMER MANAGEMENT -----------------
void TechFixSystem::manageCustomers() {
	int choice;

	while (true) {
		cout << "\n" << string(60, '=') << endl;
		cout << "CUSTOMER MANAGEMENT" << endl;
		cout << string(60, '=') << endl;
		cout << "1. View All Customers" << endl;
		cout << "2. Add New Customer" << endl;
		cout << "3. Back to Main Menu" << endl;
		cout << string(60, '=') << endl;
		cout << "Choice: ";
		cin >> choice;
		cin.ignore();

		clearScreen();

		switch (choice) {
			case 1:
				viewAllCustomers();
				break;
			case 2:
				addCustomer();
				break;
			case 3:
				return;
			default:
				cout << "[ERROR] Invalid choice!" << endl;
				pause();
				clearScreen();
		}
	}
}

void TechFixSystem::viewAllCustomers() {
	cout << "\n" << string(70, '=') << endl;
	cout << "ALL CUSTOMERS" << endl;
	cout << string(70, '=') << endl;

	if (customers.isEmpty()) {
		cout << "No customers found." << endl;
	} else {
		for (int i = 0; i < customers.getSize(); i++) {
			cout << "\nCustomer #" << (i + 1) << endl;
			cout << string(70, '-') << endl;
			customers.get(i).display();
		}
	}

	cout << string(70, '=') << endl;
	cout << "Total Customers: " << customers.getSize() << endl;

	pause();
	clearScreen();
}

void TechFixSystem::addCustomer() {
	cout << "\n" << string(60, '=') << endl;
	cout << "ADD NEW CUSTOMER" << endl;
	cout << string(60, '=') << endl;

	string name, contact, email;

	cout << "Enter customer name: ";
	getline(cin, name);

	cout << "Enter contact number: ";
	getline(cin, contact);

	cout << "Enter email: ";
	getline(cin, email);

	if (name.empty() || contact.empty()) {
		cout << "[ERROR] Name and contact cannot be empty!" << endl;
		pause();
		clearScreen();
		return;
	}

	string customerId = generateCustomerId(customers.getSize() + 1);
	customers.add(Customer(customerId, name, contact, email));

	cout << "\n[SUCCESS] Customer added successfully!" << endl;
	cout << "Customer ID: " << customerId << endl;

	pause();
	clearScreen();
}

// ----------------- SORTING AND REPORTS -----------------
void TechFixSystem::sortByJobId(int left, int right) {
	// QUICK SORT implementation for Job ID
	if (left >= right) return;

	string pivot = repairJobs.get(right).getJobId();
	int i = left - 1;

	for (int j = left; j < right; j++) {
		if (repairJobs.get(j).getJobId() <= pivot) {
			i++;
			// Swap jobs
			RepairJob temp = repairJobs.get(i);
			repairJobs.get(i) = repairJobs.get(j);
			repairJobs.get(j) = temp;
		}
	}

	RepairJob temp = repairJobs.get(i + 1);
	repairJobs.get(i + 1) = repairJobs.get(right);
	repairJobs.get(right) = temp;

	int pivotIndex = i + 1;
	sortByJobId(left, pivotIndex - 1);
	sortByJobId(pivotIndex + 1, right);
}

void TechFixSystem::sortByRepairProgress() {
	// BUBBLE SORT by Repair Progress
	// Priority: Pending < In Progress < Completed

	int n = repairJobs.getSize();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			string progress1 = repairJobs.get(j).getRepairProgress();
			string progress2 = repairJobs.get(j + 1).getRepairProgress();

			// Convert to numeric priority
			int priority1 = (progress1 == "Pending") ? 1 : 
				(progress1 == "In Progress") ? 2 : 3;
			int priority2 = (progress2 == "Pending") ? 1 : 
				(progress2 == "In Progress") ? 2 : 3;

			if (priority1 > priority2) {
				// Swap
				RepairJob temp = repairJobs.get(j);
				repairJobs.get(j) = repairJobs.get(j + 1);
				repairJobs.get(j + 1) = temp;
			}
		}
	}
}

void TechFixSystem::viewSummaryReport() {
	cout << "\n" << string(80, '=') << endl;
	cout << "ACTIVE JOB ROUTING & TASK REPORT" << endl;
	cout << string(80, '=') << endl;

	cout << "Sort by:" << endl;
	cout << "1. Job ID (Default)" << endl;
	cout << "2. Repair Progress" << endl;
	cout << "Choice: ";

	int sortChoice;
	cin >> sortChoice;
	cin.ignore();

	if (sortChoice == 1) {
		cout << "\n[INFO] Sorting by Job ID using QUICK SORT..." << endl;
		sortByJobId(0, repairJobs.getSize() - 1);
	} else if (sortChoice == 2) {
		cout << "\n[INFO] Sorting by Repair Progress using BUBBLE SORT..." << endl;
		sortByRepairProgress();
	}

	cout << "\n" << string(100, '=') << endl;
	cout << left << setw(8) << "Job ID"
		<< setw(20) << "Customer"
		<< setw(18) << "Device"
		<< setw(28) << "Current Job Status"
		<< setw(15) << "Progress"
		<< "Tasks" << endl;
	cout << string(100, '-') << endl;

	if (repairJobs.isEmpty()) {
		cout << "No repair jobs found." << endl;
	} else {
		for (int i = 0; i < repairJobs.getSize(); i++) {
			RepairJob& job = repairJobs.get(i);
			cout << left << setw(8) << job.getJobId()
				<< setw(20) << job.getCustomer().getName()
				<< setw(18) << job.getDeviceModel()
				<< setw(28) << job.getJobStatus()
				<< setw(15) << job.getRepairProgress()
				<< job.getTasks().getSize() << " tasks" << endl;
		}
	}

	cout << string(100, '=') << endl;
	cout << "Total Active Jobs: " << repairJobs.getSize() << endl;

	pause();
	clearScreen();
}
