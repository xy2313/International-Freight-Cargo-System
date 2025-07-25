#include <string>
#include "Shipment.h"

using namespace std;

Shipment::Shipment(string id, string dest, string time)
    : id(id), destination(dest), time(time) {
}