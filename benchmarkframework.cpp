#include "benchmarkframework.h"

qint32 DirectCall::counter = 0;

qint32 SignalSlotCall::counter = 0;

BenchmarkFrameWork::BenchmarkFrameWork(QObject *parent) : QObject(parent)
{

}

BenchmarkFrameWork::~BenchmarkFrameWork()
{

}

