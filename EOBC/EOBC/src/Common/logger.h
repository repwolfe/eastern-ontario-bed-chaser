#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QTextStream>

/**
 * @brief Logger class used for debugging and error checking.
 *
 * Easy to use, static functions to output to a log file.
 * It has different message priorities, ERROR, DEBUG and INFO
 *
 * This class is used to log error states, useful information, and Debuging messages
 */
class Logger
{
public:
    enum LogType {
        ERROR,
        DEBUG,
        INFO
    };

    static void errorMessage(std::string className, std::string callingFunction, std::string message);
    static void errorMessage(std::string className, std::string callingFunction, std::string message, QString var);
    static void debugMessage(std::string className, std::string callingFunction, std::string message);
    static void debugMessage(std::string className, std::string callingFunction, std::string message, QString var);
    static void infoMessage(std::string className, std::string callingFunction, std::string message);
    static void infoMessage(std::string className, std::string callingFunction, std::string message, QString var);

private:
    Logger();   // No instantiation of this class
    static void _log(std::string className, std::string callingFunction, std::string errorMessage, LogType type);

    static const QString OUTPUT_FILE;
    static const bool LOGGING_ON;
    static const char* errorString;
    static const char* debugString;
    static const char* infoString;
};

#endif // LOGGER_H
