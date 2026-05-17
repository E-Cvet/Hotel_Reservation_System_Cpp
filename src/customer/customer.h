#include <iostream>
#include <vector>
using namespace std;


// Deklaracija za glavnata klasa CUSTOMER
class Customer {
private:
    // Privatni data members
    int customer_id;
    string name;
    string surname;
    string phone;
    static int nextId;  // Staticen member - delen so site objekti

public:
    // Konstruktor
    Customer(string n, string s, string p);
    
    // Destruktor
    ~Customer();
    
    // Get funckcii
    int get_id();
    string get_name();
    string get_phone();
    
    // Display funkcija
    void display_info();
};

//VIPCUSTOMER KLASA

class VipCustomer : public Customer {
private:
    int loyalty_points;  // extra member

public:
    // Konstruktor
    VipCustomer(string n, string s, string p, int points);
    
    // Destruktor
    ~VipCustomer();
    
    // extra funkcii koi se potrebni
    double get_discount();  // vraka 0.25 (popust)
    void display_info();    // Override parent's display
    void add_points(int points);
};

//GROUPCUSTOMER KLASA

class GroupCustomer : public Customer {
private:
    int groupSize;  // extra member

public:
    //Konstruktor
    GroupCustomer(string name, string phone, int size);
    
    // Destruktor
    ~GroupCustomer();
    
    // extra funkcii koi se potrebni
    double get_discount();  // vraka 0.15
    void display_info();    // Override parent's display
    int get_group_size();
};

// CORPORATECUSTOMER KLASA

class CorporateCustomer : public Customer {
private:
    string company_name;  // extra member
    string tax_id;      // extra member

public:
    //Konstruktor
    CorporateCustomer(string n, string s, string p, string company, string tax);
    
    // Destruktor
    ~CorporateCustomer();
    
    // extra funkcii koi se potrebni
    double get_discount();  // vraka 0.20
    void display_info();    // Override parent's display
};

// CUSTOMERMANAGER KLASA

class CustomerManager {
private:
    vector<Customer*> customers;  // Vektor za zacuvuvanje na pointeri od Customer

public:
    //Konstruktor
    CustomerManager();
    
    // Destruktor
    ~CustomerManager();
    
    // Funkcii
    void add_customer(Customer* c);
    Customer* find_customer(int id);
    void list_all_customers();
};
