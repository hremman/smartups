#ifndef SMARTUPSSERIALCLIENT_HPP
#define SMARTUPSSERIALCLIENT_HPP

#include <QSerialPort>

class SmartUpsSerialClient
{
public:
    enum class Commands : char {
        TURN_ON = 0x0e,
        TURN_OF = 'Z',
        TURN_ON_DELAY = 'r',

        TURN_OF_GRACE = 'K',
        TURN_SLEEP = 'S',
        TURN_OFF_DELAY = 'p',
        TURN_OFF_CANCEL = 0x7F,

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

    enum class TransferReason : char{
        TOO_QUICK = 'R',
        TOO_LOW = 'L',
        TOO_HIGH = 'H',
        ON_LINE = 'O',
        USER = 'S',
        NA ????
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

    };

    enum class StatReg2{

    };

    enum class StatReg3{

    };



public:
    SmartUpsSerialClient();


};

#endif // SMARTUPSSERIALCLIENT_HPP
