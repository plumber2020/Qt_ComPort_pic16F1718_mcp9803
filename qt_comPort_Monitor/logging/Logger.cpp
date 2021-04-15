#include "Logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QObject>

QFile* Logger::logFile = Q_NULLPTR;
bool Logger::isInit = false;
QHash<QtMsgType, QString> Logger::contextNames = {
    {QtMsgType::QtDebugMsg,		"DBG"},
    {QtMsgType::QtInfoMsg,		"INF"},
    {QtMsgType::QtWarningMsg,	"WRN"},
    {QtMsgType::QtCriticalMsg,	"CRT"},
    {QtMsgType::QtFatalMsg,		"FTL"}
};

void Logger::init(int redirectIndex) {
    if (isInit || redirectIndex<0) { return; }

    switch (redirectIndex) {
    case 0:
        qInstallMessageHandler(Logger::messageNullput);
        break;
    case 1:
    // Create log file
        logFile = new QFile("./logging/debug.log");
        logFile->open(QIODevice::Append | QIODevice::Text);
    // Redirect logs to messageOutput
        qInstallMessageHandler(Logger::messageOutput);
    // Clear file contents
        logFile->resize(0);
        break;
    }
	
	Logger::isInit = true;
}

void Logger::clean() {
	if (logFile != Q_NULLPTR) {
		logFile->close();
		delete logFile;
	}
}

void Logger::messageNullput(QtMsgType, const QMessageLogContext&, const QString&) {}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {

    QString log = QObject::tr("%1 | %2 | %3 | %4 | %5 | %6\n")
    .arg(
        QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"),
        Logger::contextNames.value(type),
        QString(context.line),
        QString(context.file).
                    section('\\', -1),			// File name without file path
        QString(context.function).
                    section('(', -2, -2).		// Function name only
                    section(' ', -1).
                    section(':', -1),
        msg);

	logFile->write(log.toLocal8Bit());
	logFile->flush();
}
