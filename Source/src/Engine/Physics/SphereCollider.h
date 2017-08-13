#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H
#include "Collider.h"


class SphereCollider : public Collider
{
    public:
        SphereCollider(GameObject *object,float radius, float relativeX, float relativeY, float relativeZ);
        virtual ~SphereCollider();
        float Getradius() { return radius; }
        void Setradius(float val) { radius = val; }
        bool CollidesWithPlane(GameObject *object);
        bool CollidesWithCube(GameObject *object);
        float dotProduct(float x1, float y1, float x2, float y2);
        bool CollidesWithSphere(GameObject *object);
        bool Collides(GameObject *object);
        void Move(float x, float y, float z);
        void DrawCollider();

    protected:

    private:
        float radius;
};

#endif // SPHERECOLLIDER_H
