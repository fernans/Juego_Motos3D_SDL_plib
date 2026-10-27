class moto
{
    private:
    ssgTransform *transform;
    sgCoord trans;
    sgVec3 velocidad;

    public:
    moto (char *filename);
    ~moto();

    ssgTransform *getTransform();

    sgCoord getTrans();
    void Avanzar(float v);
    void Avanzar();
    void Retroceder();
    void Lateral(float v);
    void Subir(float v);
    void AvanzarVec3(sgVec3 v);

    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setXYZ(float x,float y,float z);

    float getX();
    float getY();
    float getZ();
    float getH();
    float getP();
    float getR();

    void setH(float h);
    void setP(float p);
    void setR(float r);
    void setHPR(float h,float p,float r);

    void setVelocidad(sgVec3 v);
    void getVelocidad(sgVec3 v);
};
