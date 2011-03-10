#ifndef BED_H
#define BED_H

class Bed
{
public:
    enum CareType {
        ACC,
        CCC,
        LTC
    };

    Bed(CareType caretype);



private:
    CareType _caretype;
};

#endif // BED_H
