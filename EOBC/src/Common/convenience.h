#ifndef CONVENIENCE_H
#define CONVENIENCE_H

#include <QRect>

/**
 * This Class will only have static convenience functions
 * to help the developers avoid code repetition for
 * simple, generic tasks.
 *
 * @todo Traceability?
 */
class Convenience
{
public:
    static QRect getCenterForSize(int width, int height);

private:
    Convenience();
};

#endif // CONVENIENCE_H
