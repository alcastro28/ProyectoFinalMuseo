#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Camera.h"
#include <iostream>
void Camera::Init(){
	m_yaw = 0.0;
	m_pitch = 0.0;
	SetPos(0, 17,0);
}
void Camera::Refresh(){
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);
	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(m_x, m_y, m_z, m_x + m_lx, m_y + m_ly, m_z + m_lz, 0.0,1.0,0.0);
	printf("Camera: %f %f %f Direction vector: %f %f %f\n", m_x, m_y, m_z, m_lx, m_ly, m_lz);
	if(m_y<=5.0)
    {
         m_y=5;
    }
}
void Camera::colision(float CordX1, float CordX2, float CordZ1, float CordZ2,float CordY1, float CordY2){
  if((m_z>=CordZ1&&m_z<=CordZ2)&&(m_x>=CordX1 && m_x<=CordX2)&&(m_y>=CordY1&&m_y<=CordY2))
  {
    if(m_x>=CordX1)
    {
        if(m_x<=CordX1+1 && (m_z>=CordZ1 && m_z<=CordZ2)&&(m_y>=CordY1 && m_y<=CordY2))
        {
            m_x=CordX1;
        }
    }
    if(m_x<=CordX2)
    {
        if(m_x>=CordX2-1 && (m_z>=CordZ1 && m_z<=CordZ2)&&(m_y>=CordY1 && m_y<=CordY2))
        {
            m_x=CordX2;
        }
    }
    if(m_z>=CordZ1)
    {
        if(m_z<=CordZ1+1 && (m_x>=CordX1 && m_x<=CordX2)&&(m_y>=CordY1 && m_y<=CordY2))
        {
            m_z=CordZ1;
        }
    }
    if(m_z<=CordZ2)
    {
        if(m_z>=CordZ2-1 && (m_x>=CordX1 && m_x<=CordX2)&&(m_y>=CordY1 && m_y<=CordY2))
        {
            m_z=CordZ2;
        }
    }
    if(m_y>=CordY1)
    {
        if(m_y<=CordY1+1 && (m_x>=CordX1 && m_x<=CordX2)&& (m_z>=CordZ1 && m_z<=CordZ2))
        {
            m_y=CordY1;
        }
    }
    if(m_y<=CordY2)
    {
        if(m_y>=CordY2-1 && (m_x>=CordX1 && m_x<=CordX2)&& (m_z>=CordZ1 && m_z<=CordZ2))
        {
            m_y=CordY2;
        }
    }
    //printf("colison");
  }
}
bool Camera::interaccion(float Cordx1, float Cordx2, float Cordz1, float Cordz2){
    if((m_z>=Cordz1&& m_z<=Cordz2)&&(m_x>=Cordx1 && m_x<=Cordx2))    {
        //printf("colison");
        return true;
    }
    else{
        return false;
    }
}
void Camera::SetPos(float x, float y, float z){
	m_x = x;
	m_y = y;
	m_z =z;
	Refresh();
}
void Camera::GetPos(float &x, float &y, float &z){
    x = m_x;
    y = m_y;
    z = m_z;
}
void Camera::GetDirectionVector(float &x, float &y, float &z){
    x = m_lx;
    y = m_ly;
    z = m_lz;
}
void Camera::Move(float incr){
    float lx = cos(m_yaw)*cos(m_pitch);
    float ly = sin(m_pitch);
    float lz = sin(m_yaw)*cos(m_pitch);
	m_x = m_x + incr*lx;
	m_y = m_y + incr*ly;
	m_z = m_z + incr*lz;
	Refresh();
}
void Camera::Strafe(float incr){
	m_x = m_x + incr*m_strafe_lx;
	m_z = m_z + incr*m_strafe_lz;
	Refresh();
}
void Camera::Fly(float incr){
	m_y = m_y + incr;
	Refresh();
}

void Camera::RotateYaw(float angle){
	m_yaw += angle;
	Refresh();
}
void Camera::RotatePitch(float angle){
    const float limit = 89.0 * M_PI / 180.0;
	m_pitch += angle;
    if(m_pitch < -limit)
        m_pitch = -limit;
    if(m_pitch > limit)
        m_pitch = limit;
	Refresh();
}
void Camera::SetYaw(float angle){
	m_yaw = angle;
	Refresh();
}
void Camera::SetPitch(float angle){
    m_pitch = angle;
    Refresh();
}

