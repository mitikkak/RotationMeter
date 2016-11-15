#define LOWEST_INIT_VALUE 10000
#define STATE_HIGH 1
#define STATE_LOW 0
#define CALIBRATION_THRESHOLD 50
#define HIGH_THRESHOLD 450
#define LOW_THRESHOLD 400
class Rotation
{
    int _highest;
    int _lowest;
    int _times;
    bool _calibrated;
    int state;
public:
    Rotation()
    {
        init();
        initCalibration();
    }
    void inputSensorValue(const int value)
    {

        //if (!_calibrated)
        {
            calibrate(value);
        }
        //if (_calibrated)
        {
            if (state == STATE_LOW)
            {
                if (exceedsHigh(value))
                {
                    state = STATE_HIGH;

                }
            }
            else
            {
                if (exceedsLow(value))
                {
                    state = STATE_LOW;
                    _times++;
                }

            }
        }
    }
    bool calibrated() const
    {
        return _calibrated;
    }
    void calibrate(const int value)
    {
        _highest = (value > _highest) ? value : _highest;
        _lowest = (value < _lowest) ? value : _lowest;
        //if (_highest > (_lowest + CALIBRATION_THRESHOLD))
        {
        //    _calibrated = true;
        }
    }

    int times() const
    {
        return _times;
    }
    int perMinute(unsigned long deltaTime) const
    {
        if (deltaTime == 0) deltaTime = 1;
        return ((unsigned long) _times*60*1000)/deltaTime;
    }
    void initCalibration()
    {
        _calibrated = false;
    }
    void init()
    {
        _calibrated = false;
        _times = 0;
        _highest = 0;
        _lowest = LOWEST_INIT_VALUE;
        state = STATE_HIGH;
    }
    int highest() const
    {
        return _highest;
    }
    int lowest() const
    {
        return _lowest;
    }
    void set(int const v)
    {
        _times = v;
    }

private:
    bool exceedsHigh(const int value)
    {
        return (value >= (HIGH_THRESHOLD));
        //return (value > (_highest+_lowest)>>1);
    }
    bool exceedsLow(const int value)
    {
        return (value <= (LOW_THRESHOLD));
        //return (value > (_highest+_lowest)>>1);
    }

};

