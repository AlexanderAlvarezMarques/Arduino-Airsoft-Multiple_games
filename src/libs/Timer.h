#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class Timer {

private:
    
    long lastTimeStamp;
    int updateAt; // Variable to store when to update lastTimeStamp (in seconds)
    bool isPaused;

public:
    
    Timer();
    
    void start(int _updateAt);
    
    void pause();
    
    void resume();
    
    void stop();
    
    long getInterval();
    
    int getIntervalInSeconds();
    
    int getIntervalInMinutes();
};

#endif // TIMER_H_INCLUDED
