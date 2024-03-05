#pragma once
#include "ComponentUpdate.h"
#include "../utils/Vector2D.h"

class Transform :
    public ComponentUpdate
{
public:
    Transform() : parent_(), globalAngle_(0), globalScale_(1, 1), relativeAngle_(0), isChild_(false),relativeScale_(1,1) {};
    ~Transform() {};

    void update() override;

    // A�ade un padre
    //
    void addParent(Transform* p);

    // Quitar un padre
    //
    void removeParent();

    // Posicion global
    // He quitao la referencia
    Vector2D getGlobalPos();

    // Escala global
    //
    Vector2D& getGlobalScale();

    // Rotacion global
    //
    float& getGlobalAngle();

    // Posicion relativa al padre
    //
    Vector2D& getRelativePos();

    // Escala relativa al padre
    //
    Vector2D& getRelativeScale();

    // Rotacion relativa al padre
    //
    float& getRelativeAngle();

    void setGlobalPos(Vector2D& v);
    void setGlobalAngle(float);

    Transform* getParent();
    
    Transform& operator+(const Transform& t);
    Transform& operator-(const Transform& t);
    Transform& operator=(const Transform& t);
private:
    Transform* parent_;

    bool isChild_;

    Vector2D globalPos_,
             globalScale_,
             relativePos_,
             relativeScale_,
             vel_;
    float globalAngle_,
          relativeAngle_;
};

