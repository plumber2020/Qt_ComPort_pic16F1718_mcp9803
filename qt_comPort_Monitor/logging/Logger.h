#pragma once

// Логирование событий Qt https://evileg.com/ru/post/154/
// https://github.com/VelazcoJD/QtLogging

/* including into: MAIN
 *
#include "Logger.h"
int main(int argc, char *argv[])
{
    Logger::init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    bool state = a.exec();

    Logger::clean();
    return state;
}
*/
/* including into: *.CPP

    qDebug() <<     "myDebug Log!";
    qInfo() <<      "myInfo Log!";
    qWarning() <<   "myWarning Log!";
    qCritical() <<  "myCritical Log!";
    qFatal(         "myFatal Log!");

*/

#include <QDebug>
#include <QFile>
#include <QHash>

class Logger {
private:
	/// @brief The file object where logs are written to.
	static QFile* logFile;

	/// @brief Whether the logger has being initialized.
	static bool isInit;

	/// @brief The different type of contexts.
	static QHash<QtMsgType, QString> contextNames;

public:
	/// @brief Initializes the logger.
    static void init(int redirectIndex = -1);

	/// @brief Cleans up the logger.
	static void clean();

	/// @brief The function which handles the logging of text.
    static void messageNullput(QtMsgType, const QMessageLogContext &, const QString &);
	static void messageOutput(QtMsgType type, const QMessageLogContext& context,
		const QString& msg);
};
