#include "smartupsserialclient.hpp"
#include <cassert>
#include <stdexcept>


void SmartUpsSerialClient::TransferReason::assertValue(const QString & value) {
    if ( !__M_values.contains(value) )
        throw std::invalid_argument(std::string("COM_UNKNOWN_VALUE '") + value.toStdString() + "'");
}

SmartUpsSerialClient::TransferReason::TransferReason(const Name name) {
    assertCount();
    assertName(name);
    name_ = name;
    value_ = __M_values[static_cast<unsigned>(name)];
}

SmartUpsSerialClient::TransferReason::TransferReason(const QString &value) {
    assertCount();
    assertValue(value);
    name_ = static_cast<Name>(__M_values.indexOf(value));
    value_ = value;
}

SmartUpsSerialClient::TransferReason & SmartUpsSerialClient::TransferReason::operator=(const QString &value) {
    assertCount();
    assertValue(value);
    name_ = static_cast<Name>(__M_values.indexOf(value));
    value_ = value;
    return *this;
}
SmartUpsSerialClient::TransferReason & SmartUpsSerialClient::TransferReason::operator=(const Name name) {
    assertCount();
    assertName(name);
    name_ = name;
    value_ = __M_values[static_cast<unsigned>(name)];
    return *this;
}
SmartUpsSerialClient::TransferReason & SmartUpsSerialClient::TransferReason::operator=(const TransferReason &other) {
    if (&other != this) {
        name_ = other.name_;
        value_ = other.value_;
    }
    return *this;
}


const QStringList SmartUpsSerialClient::TransferReason::__M_values = {
    "R",
    "L",
    "H",
    "O",
    "S",
    "NA"
};

const std::string SmartUpsSerialClient::__M_alarm_chars = "!$%+#?=*|";
const std::string SmartUpsSerialClient::__M_design_chars = "DMAI4";
const QString SmartUpsSerialClient::__M_variables = "uleosqpkrE";


