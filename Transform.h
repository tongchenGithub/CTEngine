#ifndef __Transform_H__
#define __Transform_H__
// �����tsf

#include "3DMath.h"

class Transform
{
public:
	void init(int width, int height);
	void update();	// ����MVP
	void apply(Vector& b, const Vector& a);	// MVP*a = b
	void applyMV(Vector& b, const Vector& a);	// MV*a = b
	void homogenize(Vector& b, const Vector& a); // ��һ�����õ���Ļ����
	int checkCvv(const Vector& v);			// ���CVV�ü�
	int checkBackCulling(const Vector& v);	// ��鱳���޳�

	void setWorld(const Matrix& m);
	void setView(const Matrix& m);

private:
	Matrix world;		// �������
	Matrix view;		// �ӿھ���
	Matrix projection;	// ͸�Ӿ���
	Matrix transform;	// �仯����
	float width, height; // screen
};
#endif