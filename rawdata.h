#ifndef RAWDATA_H
#define RAWDATA_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QDebug>

class RawData : public QObject
{
        Q_OBJECT
public:
        struct s_options{
                int min_sum, max_sum;
        };
        explicit RawData(QString filename,s_options opt, QObject *parent = nullptr);

signals:

protected:
        const unsigned int X1 = 5;
        const unsigned int X2 = 1;
        const unsigned int Y1 = 7;
        const unsigned int Y2 = 3;


        struct raw_data{
                int code;
                int value;
                uint16_t raw;
        };

        struct four_data{
                int x1,x2,y1,y2;
                bool correct;
        };

        static int IndexFromCode(int code);

public:
        QVector<raw_data> vRawData;
        QVector<four_data> vFourData;

};

#endif // RAWDATA_H
