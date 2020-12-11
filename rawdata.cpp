#include "rawdata.h"

RawData::RawData(QString filename, s_options opt, QObject *parent) : QObject(parent)
{
        QFile f(filename);
        f.open(QIODevice::ReadOnly);

        int s_size = sizeof(raw_data);
        raw_data rd;
        four_data fd;

        while(!f.atEnd()){
                f.read((char *)&rd,s_size);
                vRawData.append(rd);
        }

        int values[4] = {-1,-1,-1,-1};
        for(int i=3;i<vRawData.size();i+=4){
                fd.correct = true;
                values[IndexFromCode(vRawData.at(i-3).code)] = vRawData.at(i-3).value;
                values[IndexFromCode(vRawData.at(i-2).code)] = vRawData.at(i-2).value;
                values[IndexFromCode(vRawData.at(i-1).code)] = vRawData.at(i-1).value;
                values[IndexFromCode(vRawData.at(i).code)] = vRawData.at(i).value;

                fd.y1 = values[IndexFromCode(Y1)];
                fd.x1 = values[IndexFromCode(X1)];
                fd.y2 = values[IndexFromCode(Y2)];
                fd.x2 = values[IndexFromCode(X2)];

                if(fd.x1+fd.x2 > opt.max_sum || fd.x1+fd.x2 < opt.min_sum) fd.correct = false;
                if(fd.y1+fd.y2 > opt.max_sum || fd.y1+fd.y2 < opt.min_sum) fd.correct = false;
                for(int j=0;j<4;j++) if(values[j]<0) fd.correct = false;
                vFourData.append(fd);
        }

        f.close();
}

int RawData::IndexFromCode(int code){
        switch(code){
        case 5: //x1
                return 0;
                break;
        case 1: //x2
                return 1;
                break;
        case 7: //y1
                return 2;
                break;
        case 3: //y2
                return 3;
                break;
        default:
                return 0;
                break;
        }
        return 0;
}
