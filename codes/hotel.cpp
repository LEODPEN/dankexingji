#include "hotel.h"

Hotel::Hotel(QString hotelName,enumLoc Location,QString Tel,double Point):
    hotelName(hotelName),Location(Location),Tel(Tel),Point(Point)
{
    this->Point=Point;
    cusTotal=0;
}
Hotel::Hotel(QString hotelName, QString location, QString Tel,double Point,int cusNum):
    hotelName(hotelName),Tel(Tel),Point(Point)
{
    cusTotal=cusNum;
    if(location=="海淀区")Location=Haidian;
    if(location=="西城区")Location=Xicheng;
    if(location=="东城区")Location=Dongcheng;
    if(location=="丰台区")Location=Fengtai;
    if(location=="朝阳区")Location=Chaoyang;
}


double Hotel::getPoint()
{ return Point;}
void Hotel::setPoint(double point)
{ Point=point;}
void Hotel::get5()
{   cusTotal++;
    this->Point=(Point*(cusTotal-1)+5.0)/cusTotal;
}
void Hotel::get4()
{
    cusTotal++;
    this->Point=(Point*(cusTotal-1)+4.0)/cusTotal;
}
void Hotel::get3()
{
    cusTotal++;
    this->Point=(Point*(cusTotal-1)+3.0)/cusTotal;
}
void Hotel::get2()
{
    cusTotal++;
    this->Point=(Point*(cusTotal-1)+2.0)/cusTotal;
}
void Hotel::get1()
{
    cusTotal++;
    this->Point=(Point*(cusTotal-1)+1.0)/cusTotal;
}


QString Hotel::showHName()
{return hotelName;}
QString Hotel::showLocation()
{
    switch (Location)
  { case Haidian:return(QString(QStringLiteral("海淀区")));
    case Xicheng:return(QString(QStringLiteral("西城区")));
    case Dongcheng:return(QString(QStringLiteral("东城区")));
    case Fengtai:return(QString(QStringLiteral("丰台区")));
    case Chaoyang:return(QString(QStringLiteral("朝阳区")));
    default:return QString();
  }
}
QString Hotel::showTel()
{return Tel;}

QString Hotel::showPoint()
{
    return QString::number(Point,'f',1);
}
