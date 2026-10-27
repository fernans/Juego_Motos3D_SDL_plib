#include <plib\ul.h>
#include <plib\sg.h>
#include <plib\ssg.h>

#include "moto.h"

    moto::moto (char *filename) {
        trans=(sgCoord){{0,0,0},{0,0,0}};
        sgSetVec3(velocidad,0,0,0);
        transform = new ssgTransform(&trans);
        ssgEntity *modelo = ssgLoad3ds(filename,NULL);
        modelo->setName("modelo:moto");
        transform->addKid(modelo);
        transform->setName("transform:moto");
    }

    moto::~moto() {
        ssgDeRefDelete(transform);
    }

    ssgTransform *moto::getTransform() {
        return transform;
    }

    sgCoord moto::getTrans() {
        return trans;
    }
    void moto::setX(float x) {
        trans.xyz[0]=x;
        transform->setTransform(&trans);
    }
    void moto::setY(float y) {
        trans.xyz[1]=y;
        transform->setTransform(&trans);
    }
    void moto::setZ(float z) {
        trans.xyz[2]=z;
        transform->setTransform(&trans);
    }
    void moto::setXYZ(float x,float y,float z) {
        sgSetVec3(trans.xyz,x,y,z);
        transform->setTransform(&trans);
    }

    float moto::getX() {return trans.xyz[0];}
    float moto::getY() {return trans.xyz[1];}
    float moto::getZ() {return trans.xyz[2];}
    float moto::getH() {return trans.hpr[0];}
    float moto::getP() {return trans.hpr[1];}
    float moto::getR() {return trans.hpr[2];}

    void moto::setH(float h) {
        trans.hpr[0]=h;
        transform->setTransform(&trans);
    }
    void moto::setP(float p) {
        trans.hpr[1]=p;
        transform->setTransform(&trans);
    }
    void moto::setR(float r) {
        trans.hpr[2]=r;
        transform->setTransform(&trans);
    }
    void moto::setHPR(float h,float p,float r) {
        sgSetVec3(trans.hpr,h,p,r);
        transform->setTransform(&trans);
    }

    void moto::Avanzar(float v) {
        sgVec3 velo={0,v,0};
        AvanzarVec3(velo);
    }
    void moto::Avanzar() {
        AvanzarVec3(velocidad);
    }
    void moto::Retroceder() {
        sgVec3 temp;
        sgNegateVec3(temp,velocidad);
        AvanzarVec3(temp);
    }
    void moto::Lateral(float v) {
        sgVec3 velo={v,0,0};
        AvanzarVec3(velo);
    }
    void moto::Subir(float v) {
        sgVec3 velo={0,0,v};
        AvanzarVec3(velo);
    }

    void moto::AvanzarVec3(sgVec3 velo) {
        sgMat4 temp;
        sgMakeCoordMat4(temp,(sgVec3){0,0,0},trans.hpr);
        sgVec3 dist;
        sgXformVec3(dist,velo,temp);
        sgAddVec3(trans.xyz,dist);
        transform->setTransform(&trans);
    }

    void moto::setVelocidad(sgVec3 v) {
        sgCopyVec3(velocidad,v);
    }

    void moto::getVelocidad(sgVec3 v) {
        sgCopyVec3(v,velocidad);
    }
