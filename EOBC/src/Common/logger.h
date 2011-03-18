#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QTextStream>

/**
 * Logger class used for debugging and error checking
 * Easy to use, when created it will output to a log file.
 * It has different message priorities.
 *
 * @todo what to do about traceability
 */
class Logger
{
public:
    enum LogType {
        ERROR,
        DEBUG,
        INFO
    };

    Logger(char* callingFunction, char* errorMessage, LogType type);

    static const QString OUTPUT_FILE;
    static const char* errorString;
    static const char* debugString;
    static const char* infoString;

private:

};

#endif // LOGGER_H
