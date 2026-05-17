#include <iostream>
#include "../src/reservation/reservation.h"
using namespace std;

// inicijaliziranje na customer ID
int Customer::nextId = 1001;

//CUSTOMER KLASA

// Konstruktor za klasa Customer(zema vrednosti od customer.h)
Customer::Customer(string n, string s, string p) {
    cout << "Constructor called for Customer" << endl;
    customer_id = nextId;
    nextId++;
    name = n;
    surname = s;
    phone = p;
}

// Destruktor
Customer::~Customer() {
    cout << "Destructor called for Customer ID: " << customer_id << endl;
}

// get_id() funkcija
int Customer::get_id() {
    return customer_id;
}

// get_name() funkcija
string Customer::get_name() {
    return name;
}

// get_phone() funkcija
string Customer::get_phone() {
    return phone;
}

// display_info() funkcija
void Customer::display_info() {
    cout << "\n--- Customer Information ---" << endl;
    cout << "ID: " << customer_id << endl;
    cout << "Name: " << name << " " << surname << endl;
    cout << "Phone: " << phone << endl;
}

//VIPCUSTOMER KLASA

// Konstruktor za VipCustomer
VipCustomer::VipCustomer(string n, string s, string p, int points) 
    : Customer(n, s, p) {
    cout << "Constructor called for VipCustomer" << endl;
    loyalty_points = points;
}

// Destruktor
VipCustomer::~VipCustomer() {
    cout << "Destructor called for VipCustomer ID: " << get_id() << endl;
}

// get_discount() funkcija
double VipCustomer::get_discount() {
    return 0.25;  // 25% discount
}

// display_info() funkcija (override)
void VipCustomer::display_info() {
    cout << "\n--- VIP CUSTOMER ---" << endl;
    cout << "ID: " << get_id() << endl;
    cout << "Name: " << get_name() << endl;
    cout << "Phone: " << get_phone() << endl;
    cout << "Type: VIP" << endl;
    cout << "Loyalty Points: " << loyalty_points << endl;
    cout << "Discount: 25%" << endl;
}

// add_points() funkcija
void VipCustomer::add_points(int points) {
    loyalty_points = loyalty_points + points;
    cout << "Added " << points << " points. Total: " << loyalty_points << endl;
}

//GROUPCUSTOMER KLASA

// Konstruktor za GroupCustomer
GroupCustomer::GroupCustomer(string name, string phone, int size) 
    : Customer(name, "", phone) {
    cout << "Constructor called for GroupCustomer" << endl;
    groupSize = size;
}

// Destruktor
GroupCustomer::~GroupCustomer() {
    cout << "Destructor called for GroupCustomer ID: " << get_id() << endl;
}

// get_discount() funkcija
double GroupCustomer::get_discount() {
    return 0.15;  // 15% popust
}

// display_info() funkcija (override)
void GroupCustomer::display_info() {
    cout << "\n--- GROUP CUSTOMER ---" << endl;
    cout << "ID: " << get_id() << endl;
    cout << "Organization: " << get_name() << endl;
    cout << "Phone: " << get_phone() << endl;
    cout << "Type: Group" << endl;
    cout << "Group Size: " << groupSize << endl;
    cout << "Discount: 15%" << endl;
}

// get_group_size() funkcija
int GroupCustomer::get_group_size() {
    return groupSize;
}

//CORPORATECUSTOMER KLASA

// Konstruktor za CorporateCustomer
CorporateCustomer::CorporateCustomer(string n, string s, string p, string company, string tax) 
    : Customer(n, s, p) {
    cout << "Constructor called for CorporateCustomer" << endl;
    company_name = company;
    tax_id = tax;
}

// Destruktor
CorporateCustomer::~CorporateCustomer() {
    cout << "Destructor called for CorporateCustomer ID: " << get_id() << endl;
}

// get_discount() funkcija
double CorporateCustomer::get_discount() {
    return 0.20;  // 20% discount
}

// display_info() funkcija (override)
void CorporateCustomer::display_info() {
    cout << "\n--- CORPORATE CUSTOMER ---" << endl;
    cout << "ID: " << get_id() << endl;
    cout << "Manager: " << get_name() << endl;
    cout << "Phone: " << get_phone() << endl;
    cout << "Company: " << company_name << endl;
    cout << "Tax ID: " << tax_id << endl;
    cout << "Type: Corporate" << endl;
    cout << "Discount: 20%" << endl;
}

//CUSTOMERMANAGER KLASA

// Konstruktor
CustomerManager::CustomerManager() {
    cout << "CustomerManager created" << endl;
}

// Destruktor
CustomerManager::~CustomerManager() {
    cout << "Destroying CustomerManager..." << endl;
    
    // Gi brise site Customers za osloboduvanje prostor
    for (int i = 0; i < customers.size(); i++) {
        delete customers[i];
    }
    customers.clear();
    cout << "All customers deleted" << endl;
}

// add_customer() funkcija
void CustomerManager::add_customer(Customer* c) {
    customers.push_back(c);
    cout << "Customer added successfully! ID: " << c->get_id() << endl;
}

// find_customer() funkcija
Customer* CustomerManager::find_customer(int id) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i]->get_id() == id) {
            return customers[i];
        }
    }
    return NULL;  // Vraka NULL ako nema rezultat
}

// list_all_customers() funkcija
void CustomerManager::list_all_customers() {
    cout << "\n====== ALL CUSTOMERS ======" << endl;
    
    if (customers.size() == 0) {
        cout << "No customers in the system" << endl;
        return;
    }
    
    for (int i = 0; i < customers.size(); i++) {
        cout << "\n[Customer " << (i + 1) << "]" << endl;
        customers[i]->display_info();
    }
    
    cout << "\n============================" << endl;
}