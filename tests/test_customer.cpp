#include <iostream>
#include "../src/customer/customer.h"
 
using namespace std;
 
int main()
{
    cout << "\n=== CUSTOMER MODULE TEST ===\n" << endl;
 
    CustomerManager manager;
    Customer* vip = new VipCustomer("John", "Smith", "555-1234", 100);
    Customer* group = new GroupCustomer("Tech Company", "555-5678", 50);
    Customer* corp = new CorporateCustomer("Jane", "Doe", "555-9999", "Global Corp", "TAX-123456");
 
    manager.add_customer(vip);
    manager.add_customer(group);
    manager.add_customer(corp);
 
    // Test IDs
    cout << "TEST: ID Assignment" << endl;
    cout << "  VIP ID: " << vip->get_id() << " (expect: 1001)" << endl;
    cout << "  Group ID: " << group->get_id() << " (expect: 1002)" << endl;
    cout << "  Corp ID: " << corp->get_id() << " (expect: 1003)" << endl << endl;
 
    // Test Getters
    cout << "TEST: Getter Methods" << endl;
    cout << "  VIP Name: " << vip->get_name() << " (expect: John)" << endl;
    cout << "  VIP Phone: " << vip->get_phone() << " (expect: 555-1234)" << endl << endl;
 
    // Test Discounts
    cout << "TEST: Discounts" << endl;
    cout << "  VIP: " << vip->get_discount() << " (expect: 0.25)" << endl;
    cout << "  Group: " << group->get_discount() << " (expect: 0.15)" << endl;
    cout << "  Corp: " << corp->get_discount() << " (expect: 0.20)" << endl << endl;
 
    // Test Price Calculation
    cout << "TEST: Price Calculation ($100/night, 3 nights)" << endl;
    double base = 100.0;
    cout << "  VIP: $" << base * 3 * (1 - vip->get_discount()) << " (expect: $225)" << endl;
    cout << "  Group: $" << base * 3 * (1 - group->get_discount()) << " (expect: $255)" << endl;
    cout << "  Corp: $" << base * 3 * (1 - corp->get_discount()) << " (expect: $240)" << endl << endl;
 
    // Test Find
    cout << "TEST: Find Customer" << endl;
    cout << "  Find ID 1001: " << (manager.find_customer(1001) != nullptr ? "Found" : "Not found") << endl;
    cout << "  Find ID 9999: " << (manager.find_customer(9999) != nullptr ? "Found" : "Not found") << endl << endl;
 
    // Test Display
    cout << "TEST: Display All Customers" << endl;
    manager.list_all_customers();
 
    // Test VIP Points
    cout << "TEST: VIP Add Points" << endl;
    VipCustomer* vip_ptr = dynamic_cast<VipCustomer*>(vip);
    if (vip_ptr) {
        vip_ptr->add_points(50);
    }
 
    cout << "\n=== ALL TESTS COMPLETED ===\n" << endl;
    return 0;
}