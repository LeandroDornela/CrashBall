#ifndef CAMERA_H
#define CAMERA_H
#include "GL/glut.h"
#include "math.h"
#include "ctype.h"


class Camera
{
    public:
        Camera();
        virtual ~Camera();
        void Orthogonal(float width, float height);
        void Orthographic(float width, float height);
        void Perspective(float width, float height);
        void fixAngle(float *angle);
        void RotatePoint(float *in, float *out, float pitch, float yaw);
        void RotateCamera();
        void cameraMotion(int x, int y);
        void cameraKeyboard(unsigned char key);
        void cameraClick(int button);
        float *GetCameraPosition() { return eye; };

    protected:

    private:
        float rotationX = 0.0;
        float rotationY = 0.0;
        int last_x;
        int last_y;
        float m_yaw;
        float m_pitch;

        float eye_x = 0.0f;
        float eye_y = 230.0f;
        float eye_z = -230.0f;

        float foc_x = 0.0f;
        float foc_y = 0.0f;
        float foc_z = 0.0f;

        //vetor que aponta do olho pro foco
        float dist_x = foc_x - eye_x;
        float dist_y = foc_y - eye_y;
        float dist_z = foc_z - eye_z;

        float mod = sqrt( pow(dist_x, 2) + pow(dist_y, 2) + pow(dist_z, 2));

        //mesmo vetor normalizado que será usando no zoom
        float dist_nx = dist_x / mod;
        float dist_ny = dist_y / mod;
        float dist_nz = dist_z / mod;

        bool yawLock = false;
        bool pitchLock = false;
        // Initial Position
        float EyeInitial[3] = {eye_x, eye_y, eye_z};
        float upInitial[3]  = {0.0f, 1.0f, 0.0f};
        float foc[3]        = {foc_x, foc_y, foc_z};
        // Rotated Position
        float eye[3];
        float up[3];
};

#endif // CAMERA_H
