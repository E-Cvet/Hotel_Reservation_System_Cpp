#include <iostream>
#include "customer.h"
using namespace std;

int Customer::nextId = 1001;

Customer::Customer(string n, string s, string p)
{
    customer_id = nextId;
    nextId++;
    name = n;
    surname = s;
    phone = p;
}

Customer::~Customer() {}

int Customer::get_id()
{
    return customer_id;
}

string Customer::get_name()
{
    return name;
}

string Customer::get_surname()
{
    return surname;
}

string Customer::get_phone()
{
    return phone;
}

void Customer::set_next_id(int id)
{
    nextId = id;
}

void Customer::display_info()
{
    cout << "\n--- Customer Information ---" << endl;
    cout << "ID: " << customer_id << endl;
    cout << "Name: " << name << " " << surname << endl;
    cout << "Phone: " << phone << endl;
}

VipCustomer::VipCustomer(string n, string s, string p, int points)
    : Customer(n, s, p)
{
    loyalty_points = points;
}

VipCustomer::~VipCustomer() {}

double VipCustomer::get_discount()
{
    return 0.25;
}

int VipCustomer::get_loyalty_points()
{
    return loyalty_points;
}

void VipCustomer::display_info()
{
    cout << "\n--- VIP CUSTOMER ---" << endl;
    cout << "ID: " << get_id() << endl;
    cout << "Name: " << get_name() << endl;
    cout << "Phone: " << get_phone() << endl;
    cout << "Type: VIP" << endl;
    cout << "Loyalty Points: " << loyalty_points << endl;
    cout << "Discount: 25%" << endl;
}

void VipCustomer::add_points(int points)
{
    loyalty_points = loyalty_points + points;
    cout << "Added " << points << " points. Total: " << loyalty_points << endl;
}

GroupCustomer::GroupCustomer(string name, string phone, int size)
    : Customer(name, "", phone)
{
    groupSize = size;
}

GroupCustomer::~GroupCustomer() {}

double GroupCustomer::get_discount()
{
    return 0.15;
}

void GroupCustomer::display_info()
{
    cout << "\n--- GROUP CUSTOMER ---" << endl;
    cout << "ID: " << get_id() << endl;
    cout << "Organization: " << get_name() << endl;
    cout << "Phone: " << get_phone() << endl;
    cout << "Type: Group" << endl;
    cout << "Group Size: " << groupSize << endl;
    cout << "Discount: 15%" << endl;
}

int GroupCustomer::get_group_size()
{
    return groupSize;
}

CorporateCustomer::CorporateCustomer(string n, string s, string p, string company, string tax)
    : Customer(n, s, p)
{
    company_name = company;
    tax_id = tax;
}

CorporateCustomer::~CorporateCustomer() {}

double CorporateCustomer::get_discount()
{
    return 0.20;
}

string CorporateCustomer::get_company_name()
{
    return company_name;
}

string CorporateCustomer::get_tax_id()
{
    return tax_id;
}

void CorporateCustomer::display_info()
{
    cout << "\n--- CORPORATE CUSTOMER ---" << endl;
    cout << "ID: " << get_id() << endl;
    cout << "Manager: " << get_name() << endl;
    cout << "Phone: " << get_phone() << endl;
    cout << "Company: " << company_name << endl;
    cout << "Tax ID: " << tax_id << endl;
    cout << "Type: Corporate" << endl;
    cout << "Discount: 20%" << endl;
}

CustomerManager::CustomerManager() {}

CustomerManager::~CustomerManager()
{
    for (int i = 0; i < customers.size(); i++)
    {
        delete customers[i];
    }
    customers.clear();
}

void CustomerManager::add_customer(Customer *c)
{
    customers.push_back(c);
}

Customer *CustomerManager::find_customer(int id)
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i]->get_id() == id)
        {
            return customers[i];
        }
    }
    return NULL;
}

void CustomerManager::list_all_customers()
{
    cout << "\n====== ALL CUSTOMERS ======" << endl;

    if (customers.size() == 0)
    {
        cout << "No customers in the system" << endl;
        return;
    }

    for (int i = 0; i < customers.size(); i++)
    {
        cout << "\n[Customer " << (i + 1) << "]" << endl;
        customers[i]->display_info();
    }

    cout << "\n============================" << endl;
}

vector<Customer *> CustomerManager::getCustomers()
{
    return customers;
}
