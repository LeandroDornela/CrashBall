#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::~Camera()
{
    //dtor
}

void Camera::Orthogonal(float width, float height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera::Orthographic(float width, float height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(10.0, (GLfloat)width/(GLfloat)height, 1.0, 1100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 1000, 1, 0, 0, 0, 1, 0, 0);
}

void Camera::Perspective(float width, float height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLfloat)width/(GLfloat)height, 1.0, 5000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    RotateCamera();
    gluLookAt(eye[0], eye[1], eye[2], foc[0], foc[1], foc[2], up[0],  up[1],   up[2]);
}

void Camera::fixAngle(float *angle)
{
    if(*angle > 360) *angle = 1.0f;
    if(*angle < 0)   *angle = 359.0f;
}

void Camera::RotatePoint(float *in, float *out, float pitch, float yaw)
{
	float xt = in[0], yt = in[1], zt = in[2];
	float x, y, z;

	// Rotation in 'y' axis
    x = zt * sin(yaw) + xt * cos(yaw);
	y = yt;
	z = zt * cos(yaw) - xt * sin(yaw);

	// Rotation in 'x' axis
    out[0] = x;
    out[1] = y * cos(pitch) - z * sin(pitch);
    out[2] = y * sin(pitch) + z * cos(pitch);
}

void Camera::RotateCamera()
{
    float r_pitch = M_PI * m_pitch / 180;
    float r_yaw   = M_PI * m_yaw / 180;

	// Rotate eye vector
	RotatePoint(EyeInitial, eye, r_pitch, r_yaw);

	// Rotate up vector
	RotatePoint(upInitial, up, r_pitch, r_yaw);
}

void Camera::cameraMotion(int x, int y)
{
    if(!yawLock) 	rotationX += (float) (x - last_x);
    if(!pitchLock)	rotationY += (float) (y - last_y);

    last_x = x;
    last_y = y;

    fixAngle(&rotationX);
    fixAngle(&rotationY);

    m_yaw   = rotationX;
    m_pitch = rotationY;
}

void Camera::cameraClick(int button)
{
    switch(button){
       case 4:
            mod++;
            if(mod>400){ mod=400; }
            else{
                EyeInitial[0]= EyeInitial[0] - dist_nx;
                EyeInitial[1]= EyeInitial[1] - dist_ny;
                EyeInitial[2]= EyeInitial[2] - dist_nz;
            }

        break;
        case 3:
            mod--;
            if(mod<20){ mod=20; }
            else{
                EyeInitial[0]= EyeInitial[0] + dist_nx;
                EyeInitial[1]= EyeInitial[1] + dist_ny;
                EyeInitial[2]= EyeInitial[2] + dist_nz;
            }
        break;
   }
}

void Camera::cameraKeyboard(unsigned char key)
{
    switch(tolower(key)){
       case '+':
            mod++;
            if(mod>300){ mod=300; }
            else{
                EyeInitial[0]= EyeInitial[0] - dist_nx;
                EyeInitial[1]= EyeInitial[1] - dist_ny;
                EyeInitial[2]= EyeInitial[2] - dist_nz;
            }

        break;
        case '-':
            mod--;
            if(mod<20){ mod=20; }
            else{
                EyeInitial[0]= EyeInitial[0] + dist_nx;
                EyeInitial[1]= EyeInitial[1] + dist_ny;
                EyeInitial[2]= EyeInitial[2] + dist_nz;
            }
        break;
        case 'y':
                yawLock = !yawLock;
        break;
        case 'p' :
                pitchLock = !pitchLock;
        break;
   }
}
