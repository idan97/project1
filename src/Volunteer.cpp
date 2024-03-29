#include "../include/Volunteer.h"

Volunteer::Volunteer(int id, const string &name) : completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(id), name(name) {}

int Volunteer::getId() const
{
    return id;
}

const string &Volunteer::getName() const
{
    return name;
}

int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
}

bool Volunteer::isBusy() const
{
    return activeOrderId != NO_ORDER;
}

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown)
    : Volunteer(id, name), coolDown(coolDown), timeLeft(0) {}

CollectorVolunteer ::CollectorVolunteer(const CollectorVolunteer &other)
    : Volunteer(other.getId(), other.getName()), coolDown(other.getCoolDown()), timeLeft(other.getTimeLeft()) {}

CollectorVolunteer *CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this);
}

void CollectorVolunteer::step()
{
    if (decreaseCoolDown())
    {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown()
{
    timeLeft--;
    return timeLeft == 0;
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return true; // always true for CollectorVolunteer
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy();
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    timeLeft = coolDown;
}

string CollectorVolunteer::toString() const
{
    std::string info = "VolunteerID: " + std::to_string(getId()) + "\n";
    if (isBusy())
    {
        info += "isBusy: True\n";
        info += "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
        info += "TimeLeft: " + std::to_string(getTimeLeft()) + "\n";
    }
    else
    {
        info += "isBusy: False\n";
        info += "OrderID: None\n";
        info += "TimeLeft: None\n";
    }
    info += "OrdersLeft: No Limit \n";
    return info;
}

string CollectorVolunteer::getVolunteerType() const
{
    return "Collector";
}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown, int maxOrders)
    : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(const LimitedCollectorVolunteer &other)
    : CollectorVolunteer(other.getId(), other.getName(), other.getCoolDown()), maxOrders(other.getMaxOrders()), ordersLeft(other.getNumOrdersLeft()) {}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return CollectorVolunteer::canTakeOrder(order) && ordersLeft > 0;
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    CollectorVolunteer::acceptOrder(order);
    ordersLeft--;
}

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const
{
    std::string info = "VolunteerID: " + std::to_string(getId()) + "\n";
    if (isBusy())
    {
        info += "isBusy: True\n";
        info += "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
        info += "TimeLeft: " + std::to_string(getTimeLeft()) + "\n";
    }
    else
    {
        info += "isBusy: False\n";
        info += "OrderID: None\n";
        info += "TimeLeft: None\n";
    }
    info += "OrdersLeft:" + std::to_string(getNumOrdersLeft()) + "\n";
    return info;
}

string LimitedCollectorVolunteer::getVolunteerType() const
{
    return "LimitedCollector";
}

DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep)
    : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0) {}

DriverVolunteer::DriverVolunteer(const DriverVolunteer &other)
    : Volunteer(other.getId(), other.getName()), maxDistance(other.getMaxDistance()), distancePerStep(other.getDistancePerStep()), distanceLeft(other.getDistanceLeft()) {}
DriverVolunteer *DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
}

int DriverVolunteer::getDistanceLeft() const
{
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const
{
    return maxDistance;
}

int DriverVolunteer::getDistancePerStep() const
{
    return distancePerStep;
}

bool DriverVolunteer::decreaseDistanceLeft()
{

    distanceLeft -= distancePerStep;
    if (distanceLeft < 0)
    {
        distanceLeft = 0;
    }

    return distanceLeft <= 0;
}

bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() && order.getDistance() <= maxDistance;
}

void DriverVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    distanceLeft = order.getDistance();
}

void DriverVolunteer::step()
{
    if (decreaseDistanceLeft())
    {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

string DriverVolunteer::toString() const
{
    std::string info = "VolunteerID: " + std::to_string(getId()) + "\n";
    if (isBusy())
    {
        info += "isBusy: True\n";
        info += "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
        info += "TimeLeft: " + std::to_string(getDistanceLeft()) + "\n";
    }
    else
    {
        info += "isBusy: False\n";
        info += "OrderID: None\n";
        info += "TimeLeft: None\n";
    }
    info += "OrdersLeft: No Limit \n";
    return info;
}

string DriverVolunteer::getVolunteerType() const
{
    return "Driver";
}

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders)
    : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedDriverVolunteer::LimitedDriverVolunteer(const LimitedDriverVolunteer &other)
    : DriverVolunteer(other.getId(), other.getName(), other.getMaxDistance(), other.getDistancePerStep()), maxOrders(other.getMaxOrders()), ordersLeft(other.getNumOrdersLeft()) {}

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return DriverVolunteer::canTakeOrder(order) && hasOrdersLeft();
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    DriverVolunteer::acceptOrder(order);
    ordersLeft--;
}

string LimitedDriverVolunteer::toString() const
{
    std::string info = "VolunteerID: " + std::to_string(getId()) + "\n";
    if (isBusy())
    {
        info += "isBusy: True\n";
        info += "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
        info += "TimeLeft: " + std::to_string(getDistanceLeft()) + "\n";
    }
    else
    {
        info += "isBusy: False\n";
        info += "OrderID: None\n";
        info += "TimeLeft: None\n";
    }
    info += "OrdersLeft :" + std::to_string(getNumOrdersLeft()) + "\n";
    return info;
}

string LimitedDriverVolunteer::getVolunteerType() const
{
    return "LimitedDriver";
}
