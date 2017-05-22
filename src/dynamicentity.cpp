#include "include/dynamicentity.h"
#include "include/player.h"
#include "include/cube.h"
#include <QTextStream>

DynamicEntity::DynamicEntity(qreal x, qreal y, qreal w, qreal h,
                             qreal mass,
                             const QColor color, bool collidable) :
    Entity::Entity(x, y, w, h, color, collidable),
    _inAir(true),
    _mass(mass),
    _vx(0),
    _vy(0),
    _ch(0)
{

}

void DynamicEntity::setVx(qreal vx)
{
    _vx = vx;
}

void DynamicEntity::setVy(qreal vy)
{
    _vy = vy;
}

void DynamicEntity::setCh(double c)
{
    _ch = c;
}

double DynamicEntity::getCh() const
{
    return _ch;
}

void DynamicEntity::applyForce(qreal ix, qreal iy)
{
    _vx += (ix / _mass);
    if (_vx > 6)
        _vx = 6;
    if (_vx < -6)
        _vx =- 6;
    _vy += (iy / _mass);
}

void DynamicEntity::applyGravity(qreal g)
{
    applyForce(0, g);    
}
void DynamicEntity::move(int id){
    QTextStream out(stdout);
    //out<<_vx<<"  "<<_vy<<endl;
    int vx = (int)_vx;
    int vy = (int)_vy;
    if(_vy<0.2&&_vy>0)_vy=-_vy;
    int c1 = _vx>0?1:-1;
    int c2 = _vy>0?1:-1;
    double ch1=2;
    if(_vx*c1>=1)ch1=1/(_vx*c1);
    double ch2=2;
    if(_vy*c2>=1)ch2=1/(_vy*c2);
    if(getCh()==0){
        double min=ch1<ch2?ch1:ch2;
        setCh(min);
        return;
    }
    if(getCh()>=1) return;
    double trych1=0;
    double trych2=0;
    while(trych1<getCh()) trych1+=ch1;
    while(trych2<getCh()) trych2+=ch2;
    if(trych1==getCh()){
        //out<<_vx;
        moveBy(c1, 0);
        int ignoredCollisions = 0;
        auto collidingObjects = collidingItems();
        foreach (QGraphicsItem *item, collidingObjects){
            if (!((Entity*)item)->collidable())
                ignoredCollisions++;
            if(typeid(*item) == typeid(Cube)){
                //out<<"dynamic";
                ((DynamicEntity*)item)->applyForce(_vx*_mass/3,0);
            }
        }
        if(!id&&collidingObjects.size() == ignoredCollisions){
            moveBy(-2*c1,0);
            foreach (QGraphicsItem *item, collidingObjects){
                if (!((Entity*)item)->collidable())
                    ignoredCollisions++;
                if(typeid(*item) == typeid(Cube)){
                    out<<"dynamic";
                    ((DynamicEntity*)item)->applyForce(_vx*_mass/3,0);
                    ((DynamicEntity*)item)->setCh(this->getCh());
                }
            }
            moveBy(2*c1,0);
        }
        if (collidingObjects.size() > ignoredCollisions) {
            if(id||!((Player*)this)->go()){
            moveBy(-c1,0);
            _vx = 0;
            }
        }
        trych1+=ch1;
    }
    if(trych2==getCh()){
        _inAir=true;
        moveBy(0, c2);
        int ignoredCollisions = 0;
        auto collidingObjects = collidingItems();
        foreach (QGraphicsItem *item, collidingObjects)
            if (!((Entity*)item)->collidable())
                ignoredCollisions++;

        if (collidingObjects.size() > ignoredCollisions) {
            if(id||!((Player*)this)->go()){
            if(c2==c2*c2)_inAir=false;
            moveBy(0,-c2);
            if(c2*_vy>0)_vy = 0;
            else setCh(0);

            }
        }
       qreal frictionCoef = 0.1;
        if (collidingItems().size() == 0&&trych2==ch2)
            applyForce(-_vx * frictionCoef, 0);

        trych2+=ch2;
    }
    double min = trych1<trych2?trych1:trych2;
    setCh(min);
    /*
    for(int i = 1; i <= vy; i++) {
        moveBy(0, 1);

        int ignoredCollisions = 0;
        auto collidingObjects = collidingItems();
        foreach (QGraphicsItem *item, collidingObjects)
            if (!((Entity*)item)->collidable())
                ignoredCollisions++;

        if (collidingObjects.size() > ignoredCollisions) {
            moveBy(0, -1);
            _vy = 0;
            //_y += i;
            break;
        }
    }
    */
}
