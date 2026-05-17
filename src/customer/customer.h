#pragma once
#include <iostream>
#include <vector>

using namespace std;

/*
    Info to whoever is in charge of Customer.
    The protected attributes of Customer can be whatever you want. That is for you to decide.
    Please leave the public methods as they are, as they are needed in other functionalities.
    Why the public functions are needed:

    Customer(string name, string surname, string phone) - Constructor, this is how the object
            is created. Every customer should have a name, surname and phone number by which
            they will be identified in the system.
    virtual double get_discount() - Every child Customer that you create should implement this
            function. It returns the discount that that type of customer receives on the price
            per night. Example: 0.2 means 20% off. This is used in Reservation to calculate
            the final price.
    virtual void display_info() - Every child Customer that you create should implement this
            function to display information about that specific customer.
    int get_id() - Returns the unique ID of the customer, used in Reservation to look up
            who is making the booking.
    string get_name() - Returns the name of the customer.
    string get_phone() - Returns the phone number of the customer.

    The two classes VipCustomer and GroupCustomer are just examples of possible customer types.
    You are free to change the internal attributes and the discount logic however you like.
    What you must not change is get_discount() and display_info() — these must be implemented
    in every subclass as the rest of the system depends on them.

    CustomerManager:
    Same goes for here, the private attributes can be changed completely.
    Please do not change the public method signatures, this is why they are needed:
    void add_customer(Customer* customer) - Adds a customer to the system. Used in main.
    Customer* find_customer(int id) - Looks up a customer by their ID. Used in Reservation
            to find who is making a booking.
    void list_all_customers() - Prints all customers in the system. Used in main.
*/

class Customer {
protected:
    int customer_id;
    string name;
    string surname;
    string phone;
    static int nextId;

public:
    Customer(string name, string surname, string phone);

    virtual double get_discount() = 0;  // pure virtual — Customer is abstract
    virtual void display_info() = 0;

    int get_id();
    string get_name();
    string get_phone();

    virtual ~Customer() = default;
};

/* These are some examples of VIP customers, they don't have to be like this. */
class VipCustomer : public Customer {
    int loyalty_points;

public:
    VipCustomer(string name, string surname, string phone, int loyalty_points = 0);

    double get_discount() override;
    void display_info() override;
    void add_points(int points);
};

class GroupCustomer : public Customer {
    int groupSize;

public:
    GroupCustomer(string name, string phone, int groupSize);

    double get_discount() override;
    void display_info() override;
    void get_group_size();
};

// ── CustomerManager ───────────────────────────────────────

class CustomerManager {
    vector<Customer*> customers;

public:
    void add_customer(Customer* customer);
    Customer* find_customer(int id);
    void list_all_customers();
    ~CustomerManager();
};