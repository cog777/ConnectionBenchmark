#ifndef BENCHMARKFRAMEWORK_H
#define BENCHMARKFRAMEWORK_H

#include <QObject>
#include <QTime>
#include <QDebug>
#include <QScopedPointer>
#include <QSharedPointer>


const qint32 ITERATION_NUMBER = 1000000;

class DirectCall
{
public:
	void fnc()
	{
		++counter;
	}

	static qint32 counter;
};

class SignalSlotCall : public QObject
{
	Q_OBJECT
public slots:
	void fnc()
	{
	}
public:
	static qint32 counter;

};



class BenchmarkFrameWork : public QObject
{
	Q_OBJECT
public:
	explicit BenchmarkFrameWork(QObject *parent = 0);
	~BenchmarkFrameWork();

signals:
	void callFnc();

public slots:
	void startBenchmark()
	{
		qDebug() << "Iteration number: " << ITERATION_NUMBER;
		QTime timer;
		{
			DirectCall dc[ITERATION_NUMBER / 1000];

			qDebug() << "***STATIC***";
			timer.start();
			for (qint32 j = 0; j < 1000; ++j)
			for (qint32 idx = 0; idx < ITERATION_NUMBER / 1000; ++idx)
			{
				dc[idx].fnc();
			}

			qDebug() << "Elapsed time in ms: " << timer.elapsed();
		}
		{
			DirectCall *dc[ITERATION_NUMBER];
			for (qint32 idx = 0; idx < ITERATION_NUMBER; ++idx)
			{
				dc[idx] = new DirectCall;
			}

			qDebug() << "***DYNAMIC***";
			timer.restart();
			for (qint32 idx = 0; idx < ITERATION_NUMBER; ++idx)
			{
				dc[idx]->fnc();
			}

			qDebug() << "Elapsed time in ms: " << timer.elapsed();

			for (qint32 idx = 0; idx < ITERATION_NUMBER; ++idx)
			{
				delete dc[idx];
			}

		}
		{
			QScopedPointer<DirectCall> dc[ITERATION_NUMBER];
			for (qint32 idx = 0; idx < ITERATION_NUMBER; ++idx)
			{
				dc[idx].reset(new DirectCall);
			}

			qDebug() << "***QScopedPointer***";
			timer.restart();
			for (qint32 idx = 0; idx < ITERATION_NUMBER; ++idx)
			{
				dc[idx]->fnc();
			}

			qDebug() << "Elapsed time in ms: " << timer.elapsed();

		}
		{
			QSharedPointer<DirectCall>* dc = new QSharedPointer<DirectCall>[ITERATION_NUMBER];
			for (qint32 idx = 0; idx < ITERATION_NUMBER; ++idx)
			{
				dc[idx] = QSharedPointer<DirectCall>(new DirectCall);
			}

			qDebug() << "***QSharedPointer***";
			timer.restart();
			for (qint32 idx = 0; idx < ITERATION_NUMBER; ++idx)
			{
				dc[idx]->fnc();
			}

			qDebug() << "Elapsed time in ms: " << timer.elapsed();
			delete[] dc;
		}

		{
			SignalSlotCall dc[ITERATION_NUMBER / 1000];

			qDebug() << "***Direct connection*** Only " << ITERATION_NUMBER / 1000 << " iteration";

			for (qint32 idx = 0; idx < ITERATION_NUMBER / 1000; ++idx)
			{
				connect(this, SIGNAL(callFnc()), &dc[idx], SLOT(fnc()), Qt::DirectConnection);
			}

			timer.restart();

			for (qint32 idx = 0; idx < ITERATION_NUMBER / 1000; ++idx)
			{
				callFnc();
			}


			qDebug() << "Elapsed time in ms: " << timer.elapsed();
		}

		{
			SignalSlotCall dc[ITERATION_NUMBER / 1000];

			qDebug() << "***Queued connection*** Only " << ITERATION_NUMBER / 1000 << " iteration";

			for (qint32 idx = 0; idx < ITERATION_NUMBER / 1000; ++idx)
			{
				connect(this, SIGNAL(callFnc()), &dc[idx], SLOT(fnc()), Qt::QueuedConnection);
			}

			timer.restart();

			for (qint32 idx = 0; idx < ITERATION_NUMBER / 1000; ++idx)
			{
				callFnc();
			}


			qDebug() << "Elapsed time in ms: " << timer.elapsed();
		}



	}
};

#endif // BENCHMARKFRAMEWORK_H
