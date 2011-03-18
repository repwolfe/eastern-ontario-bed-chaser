#include "logger.h"
#include <QDate>
#include <QTime>
#include <QFile>
#include <QTextStream>

const QString Logger::OUTPUT_FILE = "logfile.log";
const char* Logger::errorString = "!!!! ERROR MESSAGE called";
const char* Logger::debugString = "~~~~ DEBUG MESSAGE called";
const char* Logger::infoString = "@@@@ INFO MESSAGE called";

Logger::Logger(std::string className, std::string callingFunction, std::string errorMessage, LogType type)
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
