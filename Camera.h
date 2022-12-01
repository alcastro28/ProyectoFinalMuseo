#ifndef __CAMERA_H__
#define __CAMERA_H__
class Camera{
public:
	Camera() { Init(); }
	~Camera(){}
	void Init();
	void Refresh();
	void colision(float CordX1,float CordX2, float CordZ1, float CordZ2, float CordY1, float CordY2);
	bool interaccion(float Cordx1, float Cordx2, float Cordz1, float Cordz2);
	void SetPos(float x, float y, float z);
    void GetPos(float &x, float &y, float &z);
    void GetDirectionVector(float &x, float &y, float &z);
	void SetYaw(float angle);
	void SetPitch(float angle);
	// Navegacion
	void Move(float incr);
	void Strafe(float incr);
	void Fly(float incr);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
    private:
	float m_x, m_y, m_z;   // Posición
    float m_lx, m_ly, m_lz; // Vector de dirección de donde estamos mirando
	float m_yaw, m_pitch; // Varios ángulos de rotación
	float m_strafe_lx, m_strafe_lz; // Siempre 90 grados al vector de dirección
};

#endif
