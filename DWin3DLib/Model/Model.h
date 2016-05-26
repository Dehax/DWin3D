#pragma once

#include "../DWin3DLib_global.h"
#include "Mesh.h"
#include "../Math/Matrix.h"
#include "../Utils/Utils.h"
#include <fstream>

class DWIN3DLIB_API Model {
public:
	Model();
	Model(const Model &model);
	explicit Model(const wchar_t *name, Mesh *mesh, ARGB color = RGBA(0, 0, 0, 255));
	explicit Model(const wchar_t *name, const wchar_t *filePath);
	~Model();

	Vec3f position() const;
	void setPosition(Vec3f position);
	Vec3f rotation() const;
	void setRotation(Vec3f rotation);
	Vec3f scale() const;
	void setScale(Vec3f scale);
	Vec3f pivot() const;
	void setPivot(Vec3f pivot);
	inline Mesh *mesh()
	{
		return m_mesh;
	}

	inline Matrix worldMatrix()
	{
		Matrix P = m_pivotMatrix;
		Matrix R = m_rotateMatrix;
		Matrix S = m_scaleMatrix;
		Matrix PI = m_pivotInverseMatrix;
		Matrix T = m_transformMatrix;

		return P * R * S * PI * T;
	}

	wchar_t *name() const;
	void setName(const wchar_t *name);
	inline ARGB color() const
	{
		return m_color;
	}
	void setColor(ARGB color);

	void setParameters(long double width, long double length, long double height, long double radius, long double lensWidth, long double lensMountLength, long double lensMountWidth, long double marginWidth, long double sideButtonsHeight, long double shutterButtonHeight, long double sideButtonsRadius, long double shutterButtonRadius);

	Model &operator=(const Model &model);

	friend std::wostream &operator<<(std::wostream &out, const Model &model);
	friend std::wistream &operator >> (std::wistream &in, Model &model);

private:
	static const int NUM_PARAMETERS = 12;
	void parseObjFile(const wchar_t *filePath);

	Mesh *m_mesh;
	ARGB m_color;

	long double m_parameters[NUM_PARAMETERS];

	// World
	Vec3f m_position;
	Vec3f m_rotation;
	Vec3f m_scale;
	Vec3f m_pivot;

	Matrix m_transformMatrix;
	Matrix m_rotateMatrix;
	Matrix m_scaleMatrix;
	Matrix m_pivotMatrix;
	Matrix m_pivotInverseMatrix;

	wchar_t *m_name;
};

std::wostream &operator<<(std::wostream &out, const Model &model);
std::wistream &operator >> (std::wistream &in, Model &model);
