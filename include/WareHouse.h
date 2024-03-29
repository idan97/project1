#pragma once
#include <string>
#include <vector>

#include "Order.h"
#include "Customer.h"
#include "Action.h"
#include "Volunteer.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.

class WareHouse
{

public:
    WareHouse(const string &configFilePath);
    WareHouse(const WareHouse &other);            // copy constructor
    WareHouse(WareHouse &&other);                 // move constructor
    WareHouse &operator=(const WareHouse &other); // copy assignment operator
    WareHouse &operator=(WareHouse &&other);      // move assignment operator
    ~WareHouse();                                 // destructor
    void start();
    void addOrder(Order *order);
    bool addOrderByCustomer(int customerId);
    void addAction(BaseAction *action);
    Customer &getCustomer(int customerId) const;
    Volunteer &getVolunteer(int volunteerId) const;
    Order &getOrder(int orderId) const;
    void addCustomer(const string &name, const string &type, int distance, int maxOrders);
    const vector<BaseAction *> &getActions() const;
    void close();
    void open();
    int getOrderCounter() const;
    int getCustomerCounter() const;
    int getVolunteerCounter() const;
    void setOpenStatus(bool status);
    static Order emptyOrder;                         // For returning a null order
    static SoldierCustomer emptyCustomer;            // For returning a null customer
    static CollectorVolunteer emptyVolunteer;        // For returning a null volunteer
    void printAllOrders();                           // added by me
    string buildOrderInfo(const Order &order) const; // added by me
    void clearWareHouse();                           // added by me
    vector<Order *> &getPendingOrders();
    vector<Order *> &getInProcessOrders();
    vector<Order *> &getCompletedOrders();
    vector<Volunteer *> &getVolunteers();
    void readFirstInput();                     // added by me
    void processUserInput();                   // added by me
    void removeVolunteer(int volunteerId);     // added by me
    void eraseOrderFromInProcess(int orderId); // added by me

private:
    bool isOpen;
    int customerCounter;  // For assigning unique customer IDs
    int volunteerCounter; // For assigning unique volunteer IDs
    int orderCounter;     // For assigning unique order IDs
    string configFilePath;
    vector<Customer *> customers;
    vector<Volunteer *> volunteers;
    vector<Order *> pendingOrders;
    vector<Order *> inProcessOrders;
    vector<Order *> completedOrders;
    vector<BaseAction *> actionsLog;
};