#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

void addContact(vector<Contact>& contacts);
void viewContacts(const vector<Contact>& contacts);
void editContact(vector<Contact>& contacts);
void deleteContact(vector<Contact>& contacts);
void saveContacts(const vector<Contact>& contacts);
void loadContacts(vector<Contact>& contacts);
void displayMenu();

int main() {
    vector<Contact> contacts;
    loadContacts(contacts);

    char choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case '1': addContact(contacts); break;
            case '2': viewContacts(contacts); break;
            case '3': editContact(contacts); break;
            case '4': deleteContact(contacts); break;
            case '5': saveContacts(contacts); break;
            case '6': cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl; break;
        }
    } while (choice != '6');

    return 0;
}

void displayMenu() {
    cout << "\nContact Management System\n";
    cout << "1. Add Contact\n";
    cout << "2. View Contacts\n";
    cout << "3. Edit Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Save Contacts\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newContact.name);
    cout << "Enter phone: ";
    getline(cin, newContact.phone);
    cout << "Enter email: ";
    getline(cin, newContact.email);
    contacts.push_back(newContact);
    cout << "Contact added successfully!" << endl;
}

void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available." << endl;
        return;
    }

    cout << "\nContact List:\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". " << contacts[i].name << " | " << contacts[i].phone << " | " << contacts[i].email << endl;
    }
}

void editContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available to edit." << endl;
        return;
    }

    viewContacts(contacts);
    cout << "Enter the contact number to edit: ";
    size_t index;
    cin >> index;
    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    --index;  // Convert to zero-based index
    cout << "Editing contact: " << contacts[index].name << endl;
    cout << "Enter new name (leave empty to keep current): ";
    cin.ignore();
    string name;
    getline(cin, name);
    if (!name.empty()) {
        contacts[index].name = name;
    }
    cout << "Enter new phone (leave empty to keep current): ";
    string phone;
    getline(cin, phone);
    if (!phone.empty()) {
        contacts[index].phone = phone;
    }
    cout << "Enter new email (leave empty to keep current): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        contacts[index].email = email;
    }
    cout << "Contact updated successfully!" << endl;
}

void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available to delete." << endl;
        return;
    }

    viewContacts(contacts);
    cout << "Enter the contact number to delete: ";
    size_t index;
    cin >> index;
    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    --index;  // Convert to zero-based index
    contacts.erase(contacts.begin() + index);
    cout << "Contact deleted successfully!" << endl;
}

void saveContacts(const vector<Contact>& contacts) {
    ofstream outFile("contacts.txt");
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (const auto& contact : contacts) {
        outFile << contact.name << '\n' << contact.phone << '\n' << contact.email << '\n';
    }

    outFile.close();
    cout << "Contacts saved successfully!" << endl;
}

void loadContacts(vector<Contact>& contacts) {
    ifstream inFile("contacts.txt");
    if (!inFile) {
        return;  // No contacts to load
    }

    Contact contact;
    while (getline(inFile, contact.name) && getline(inFile, contact.phone) && getline(inFile, contact.email)) {
        contacts.push_back(contact);
    }

    inFile.close();
}
