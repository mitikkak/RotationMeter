#ifndef MESSAGE_H
#define MESSAGE_H

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

#endif // MESSAGE_H
