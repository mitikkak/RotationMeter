#include <LiquidCrystal.h>
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

class Message
{
public:
    Message(): separator('|')
    {}
    void push(const int item)
    {
        m += item;
        m += separator;
    }
    void final(const int item)
    {
        m += item;
    }
    operator String() const {return m;}

private:
    String const separator;
    String m;

};

const int RS = 4;
const int ENABLE = 3;
const int D4 = 5;
const int D5 = 6;
const int D6 = 7;
const int D7 = 8;
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

const int hallSensor = A1;

void setup() {
  lcd.begin(16, 2);
  lcd.print("RotationMeter");
  pinMode(hallSensor, INPUT);
  lcd.setCursor(0, 1);
  Serial.begin(9600);
}

unsigned long prevTimeLcdRefreshed = 0;
unsigned long const lcdRefreshRate = 1000;
int times = 0;

Rotation rotation;

void loop() {
  times++;
  unsigned long const timeNow = millis();
  const int value = analogRead(hallSensor);
  rotation.inputSensorValue(value);
  unsigned long const deltaTime = timeNow-prevTimeLcdRefreshed;
  if (deltaTime >= lcdRefreshRate)
  {
      prevTimeLcdRefreshed = timeNow;
      lcd.clear();
      Message m1;
      Message m2;
      m2.push(rotation.times());
      m1.push(rotation.perMinute(deltaTime));
      m2.push(rotation.lowest());
      m2.final(rotation.highest());
      lcd.print(m1);
      Serial.println(rotation.highest());
      lcd.setCursor(0, 1);
      lcd.print(m2);
      times = 0;
      rotation.init();


  }
}

