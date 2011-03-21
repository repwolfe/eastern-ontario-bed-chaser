#ifndef CONVENIENCE_H
#define CONVENIENCE_H

#include <QRect>

class Convenience
{
public:
    static QRect getCenterForSize(int width, int height);

private:
    Convenience();
};

#endif // CONVENIENCE_H
