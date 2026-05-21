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
    string get_surname();
    string get_phone();

    static void set_next_id(int id);

    virtual double get_discount() = 0;

    // Display funkcija
    virtual void display_info();
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
    int get_loyalty_points();
    void display_info() override;
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
    void display_info() override;
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
    string get_company_name();
    string get_tax_id();
    void display_info() override;
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
    vector<Customer *> getCustomers();
};
