#include <QCoreApplication>
#include "benchmarkframework.h"

#include <QTimer>


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTimer timer;
	BenchmarkFrameWork bfw;
	QObject::connect(&timer, SIGNAL(timeout()), &bfw, SLOT(startBenchmark()));
	timer.setSingleShot(true);
	timer.start(0);

	return a.exec();
}
