#include "logger.h"
#include <QDate>
#include <QTime>
#include <QFile>
#include <QTextStream>

const QString Logger::OUTPUT_FILE = "logfile.log";
const char* Logger::errorString = "!!!! ERROR MESSAGE called";
const char* Logger::debugString = "~~~~ DEBUG MESSAGE called";
const char* Logger::infoString = "@@@@ INFO MESSAGE called";

/**
 * Generate an Error message to the log file
 *
 * @param className the class that called this function
 * @param callingFunction the function that called this
 * @param message the error message
 */
void Logger::errorMessage(std::string className, std::string callingFunction, std::string message)
{
    Logger::_log(className, callingFunction, message, Logger::ERROR);
}

/**
 * Generate a Debug message to the log file
 *
 * @param className the class that called this function
 * @param callingFunction the function that called this
 * @param message the debug message
 */
void Logger::debugMessage(std::string className, std::string callingFunction, std::string message)
{
    Logger::_log(className, callingFunction, message, Logger::DEBUG);
}

/**
 * Generate an Info message to the log file
 *
 * @param className the class that called this function
 * @param callingFunction the function that called this
 * @param message the info message
 */
void Logger::infoMessage(std::string className, std::string callingFunction, std::string message)
{
    Logger::_log(className, callingFunction, message, Logger::INFO);
}

/**
 * Generate different types of messages to the log file
 *
 * @param className the class that called this function
 * @param callingFunction the function that called this
 * @param errorMessage the message
 * @param type the type of message to generate
 */
void Logger::_log(std::string className, std::string callingFunction, std::string errorMessage, LogType type)
{
    QFile file(OUTPUT_FILE);
    if (file.open(QIODevice::Append))
    {
        QTextStream stream(&file);

        stream << "\n---------------------------------------------------------------\n";
        stream << "On " << QDate::currentDate().toString("ddd MMMM d yyyy") << ": " << QTime::currentTime().toString("h:m:ss ap") << "\n";

        switch (type)
        {
        case Logger::DEBUG:
            stream << debugString;
            break;
        case Logger::ERROR:
            stream << errorString;
            break;
        case Logger::INFO:
            stream << infoString;
            break;
        }
        stream << " from function: " << className.c_str() << "::" << callingFunction.c_str() << "\n";
        stream << "Message:\n";
        stream << errorMessage.c_str();
        stream << "\n---------------------------------------------------------------\n";
    }
}
