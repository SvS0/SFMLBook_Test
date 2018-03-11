#include <ParallelTask.hpp>

ParallelTask::ParallelTask()
: mThread(&ParallelTask::runTask, this)
, mFinished(false) { }


void ParallelTask::execute()
{
    mFinished = false;
    mElapsedTime.restart();
    mThread.launch();
}

bool ParallelTask::isFinished()
{
    sf::Lock lock(mMutex);
    return mFinished;
}

float ParallelTask::getCompletion()
{
    sf::Lock lock(mMutex);

    return mElapsedTime.getElapsedTime().asSeconds() / 0.1f;
}
void ParallelTask::runTask()
{
    //dummy task
    bool ended = false;
    while(!ended)
    {
        sf::Lock lock(mMutex);
        if(mElapsedTime.getElapsedTime().asSeconds() >= 10.f)
            ended = true;
    }

    {
        sf::Lock lock(mMutex);
        mFinished = true;
    }
}
