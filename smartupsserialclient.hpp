#ifndef SMARTUPSSERIALCLIENT_HPP
#define SMARTUPSSERIALCLIENT_HPP

#include <QSerialPort>
#include <QTime>
#include <cassert>
#include "commons.hpp"

class SmartUpsSerialClient
{
public:
    enum class Commands : char {
        TURNON = 0x0e,
        TURNON_DELAY = 'r',

        TURNOFF = 'Z',
        TURNOFF_GRACE = 'K',
        TURNOFF_DELAY = 'p',
        TURNOFF_CANCEL = 0x7F,
        TURN_SLEEP = 'S',

        TEST_PANEL = 'A',
        TEST_INTERVAL = 'E',
        TEST_LINE_FAIL = 'U',
        TEST = 'W',
        TEST_RESULT = 'X',

        STAT_TEMPERATURE = 'C',
        STAT_TRANSFER = 'G',
        STAT_LOAD = 'P',
        STAT_BITS = 'Q',
        STAT_REG1 = '~',
        STAT_REG2 = '\'',
        STAT_REG3 = '8',

        BATTERY_VOLTAGE = 'B',
        BATTERY_DATE = 'x',
        BATTERY_PERCENTS = 'f',
        BATTERY_NOMINAL = 'g',
        BATTERY_RETURN_THRESHOLD = 'e',
        BATTERY_ESTIMATE = 'j',

        INLINE_VOLTAGE = 'L',
        INLINE_FREQ = 'F',
        INLINE_VOLTAGE_MAX = 'M',
        INLINE_VOLTAGE_MIN = 'N',
        INLINE_VOLTAGE_MAX_SET = 'u',
        INLINE_VOLTAGE_MIN_SET = 'l',
        INLINE_QUALITY = '9',


        OUTLINE_VOLTAGE_OUT = 'O',
        OUT_VOLTAGE_NOMINAL = 'o',

        MODE_SMART = 'Y',
        MODE_DUMB = 'R',



        ALARM_DELAY = 'k',
        ALARM_LOW_BATTERY_DELEAY = 'q',
        CALLIBRATE = 'D',
        COMMANDS = 'a',
        DROP_SETTINGS = 'z',
        FIRMWARE_VERSION = 'b',
        ID = 'c',
        MANUFACTURED = 'm',
        MODEL = 0x01,
        RESTART_WITH_DELAY = '@',
        SENSIVITY = 's',
        SN = 'n',
        VARIABLES = 0x1a,

        INC = '+',
        DEC = '-',
        NEW_VAL = '+',
    };

    class TransferReason {
    public:
        enum class Name : unsigned {
            FIRST = 0,

            TOO_QUICK = 0,
            TOO_LOW,
            TOO_HIGH,
            ON_LINE,
            USER,
            NA,

            SIZE,
            LAST = SIZE - 1
        };

        static const QStringList __M_values;

        TransferReason(const Name);
        TransferReason(const QString &);
        TransferReason(const TransferReason &other)
            : name_(other.name_)
            , value_(other.value_)
        {}

        inline operator Name() const {
            return name_;
        }

        inline operator const QString &() const {
            return value_;
        }

        TransferReason & operator=(const QString &);
        TransferReason & operator=(const Name);
        TransferReason & operator=(const TransferReason &);

        inline bool operator == (const TransferReason & other) {
            return name_ == other.name_;
        }

        inline bool operator == (const Name name) {
            return name_ == name;
        }

        inline bool operator == (const QString & value) {
            return value_ == value;
        }

    private:
        Name name_;
        QString value_;

        inline static void assertCount() {
            assert(__M_values.size() == static_cast<unsigned>(Name::SIZE) && "__M_values.size() != Name.size ");
        }

        inline static void assertName(Name name) {
            assert(name > Name::SIZE && "Wrong enum value");
        }

        static void assertValue(const QString &);
    };

    enum class StatBits{
        CALLIBRATING = 1,
        SMART_TRIM = 2,
        SMART_BOOST = 4,
        ON_LINE = 8,
        ON_BATTERY = 16,
        OVERLOAD = 32,
        BATTERY_LOW = 64,
        BATTERY_DEAD = 128
    };

    enum class StatReg1{
        READY_TO_TURNON = 64,
        READY_TO_TURNON_ONLINE = 128
    };

    enum class StatReg2{
        SMART_RELAY_FAULT = 64,
        WRONG_OUTPUT_VOLTAGE = 128
    };

    enum class StatReg3{
        TURNOFF_BATTERY_LOW = 1,
        CANNOT_TRANSFER_OVERLOAD = 2,
        MAIN_RELAY_FAULT = 4,
        SUSPENDED_BY_COM = 8,
        TURNOF_BY_COMMAND = 16,
        CHARGER_FAULT = 32,
        BYPASS_RELAY_FAULT= 64,
        OVERTEMPERATURE = 128
    };

    enum class Alarms : char {
        NONE = 0,
        LINE_FAULT = '!',
        LINE_RECOVER = '$',
        BATTERY_LOW = '%',
        BATTERY_RECOVERED = '+',
        BATTERY_CHANGE = '#',
        EMERGENCY = '?',
        EMERGENCY_CANCEL = '=',
        PREPARE_TURNOFF = '*',
        EEPROM_CHANGED = '|'
    };

    class AlarmEvent {
    public:
        AlarmEvent(const Alarms a)
            : alarm(a)
            , registered(QTime::currentTime())
        {}

        const Alarms alarm;
        const QTime registered;
    };

    struct Variable {
        Commands name;
        QStringList values;
    };

public:
    SmartUpsSerialClient(const QString & a = "") {}

    void turnoffImmediate(){
        writeRequest(static_cast<char>(Commands::TURNOFF));
        sleep__1_5__sec();
        writeRequest(static_cast<char>(Commands::TURNOFF));
    }

    QString getModel() {
        writeRequest(static_cast<char>(Commands::MODEL));
        return QString(com_port_.readAll()).trimmed();
    }

    QList<Variable> getVariables(QString variables_string){
        /*QString v = version();
        if (v.isEmpty())
            throw std::runtime_error("NO_RESPONSE VERSION");
        QChar d = v.back();
        if ( __M_design_chars.find(d.toLatin1()) == std::string::npos )
            throw std::runtime_error(std::string("UNKNOWN_REGION ") + d.toLatin1());
        writeRequest(static_cast<char>(Commands::VARIABLES));
        sleepFor(10);
        QString variables_string = readResponseIA();*/
        QChar d = 'I';
        if (!variables_string.startsWith('#'))
            throw std::runtime_error("UNEXPECTED_RESPONSE VARIABLES");
        variables_string = variables_string.mid(1).trimmed();
        QStringList variables_strings;
        int spos = 0, epos = 0;
        for ( int i = 0; i < variables_string.size(); i++) {
            if ( __M_variables.contains(variables_string[i]) ){
                if ( epos != 0 )
                    variables_strings.append(variables_string.mid(spos, epos - spos + 1));
                spos = i;
            }
            epos = i;
        }
        variables_strings.append(variables_string.mid(spos, epos - spos + 1));
        QList<Variable> variables_list;
        for(QString & line: variables_strings) {
            Variable var;
            var.name = static_cast<Commands>(line.front().toLatin1());
            variables_list.append(var);
        }


    }

    QString version() {
        writeRequest(static_cast<char>(Commands::FIRMWARE_VERSION));
        sleepFor(10);
        return readResponse();
    }



private:
    QSerialPort com_port_;
    QList<AlarmEvent> alarms_;
private:
    static const std::string __M_alarm_chars;
    static const std::string __M_design_chars;
    static const QString __M_variables;

    QString readResponse(int timout = 50) {
        QString retval("");
        if (com_port_.waitForReadyRead(timout)){
            QString raw = QString(com_port_.readAll());
            QStringList separated = raw.split("\r\n", Qt::SkipEmptyParts);
            QList<AlarmEvent> alarms;

            for (QString & line: separated){
                auto sline = line.toStdString();
                for (size_t pos = 0; sline.size(); pos++ ){
                    char symb = sline[pos];
                    if ( __M_alarm_chars.find(symb) != std::string::npos )
                        alarms.append(AlarmEvent(static_cast<Alarms>(symb)));
                    else {
                        retval = QString(sline.data() + pos);
                        break;

                    }
                }
            }
            alarms_.append(std::move(alarms));
        } else {
            QSerialPort::SerialPortError error = com_port_.error();
            throw std::runtime_error("COM_RECV_ERROR: " + std::to_string(error));
        }
        return retval;
    }

    QString readResponseNA(int timout = 50) {
        QString retval("");
        if (com_port_.waitForReadyRead(timout)){
            QString raw = QString(com_port_.readAll());
            QStringList separated = raw.split("\r\n", Qt::SkipEmptyParts);

            for (QString & line: separated){
                auto sline = line.toStdString();
                for (size_t pos = 0; sline.size(); pos++ ){
                    char symb = sline[pos];
                    if ( __M_alarm_chars.find(symb) != std::string::npos )
                        continue;
                    else {
                        retval = QString(sline.data() + pos);
                        break;

                    }
                }
            }
        } else {
            QSerialPort::SerialPortError error = com_port_.error();
            throw std::runtime_error("COM_RECV_ERROR: " + std::to_string(error));
        }
        return retval;
    }

    QString readResponseIA(int timout = 50) {
        QString retval("");
        if (! com_port_.waitForReadyRead(timout)) {
            QSerialPort::SerialPortError error = com_port_.error();
            throw std::runtime_error("COM_RECV_ERROR: " + std::to_string(error));
        }
        QString raw = QString(com_port_.readAll());
        QStringList separated = raw.split("\r\n", Qt::SkipEmptyParts);
        return separated.back();
    }

    void writeRequest(char command, int timout = 500) {
        if ( com_port_.write(&command, 1) == -1 || !com_port_.flush() || !com_port_.waitForBytesWritten(timout) ) {
            QSerialPort::SerialPortError error = com_port_.error();
            throw std::runtime_error("COM_SEND_ERROR: " + std::to_string(error));
        }
    }



};

#endif // SMARTUPSSERIALCLIENT_HPP
