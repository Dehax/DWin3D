#include "Model.h"
#include "ModelsFactory.h"

Model::Model()
{
	m_mesh = nullptr;
	m_name = nullptr;
}

Model::Model(const Model &model)
{
	m_mesh = new Mesh(*model.m_mesh);
	m_color = model.m_color;

	m_position = model.m_position;
	m_rotation = model.m_rotation;
	m_scale = model.m_scale;
	m_pivot = model.m_pivot;

	m_transformMatrix = model.m_transformMatrix;
	m_rotateMatrix = model.m_rotateMatrix;
	m_scaleMatrix = model.m_scaleMatrix;
	m_pivotMatrix = model.m_pivotMatrix;
	m_pivotInverseMatrix = model.m_pivotInverseMatrix;

	m_name = model.m_name;

	for (int i = 0; i < NUM_PARAMETERS; i++) {
		m_parameters[i] = model.m_parameters[i];
	}
}

Model::Model(const wchar_t *name, Mesh *mesh, ARGB color)
	: m_mesh(mesh), m_color(color), m_name(nullptr)
{
	setName(name);

	m_position = Vec3f(0.0L, 0.0L, 0.0L);
	m_rotation = Vec3f(0.0L, 0.0L, 0.0L);
	m_scale = Vec3f(1.0L, 1.0L, 1.0L);
	m_pivot = Vec3f(0.0L, 0.0L, 0.0L);

	m_pivotMatrix = Matrix(/*4, 4, */true);
	m_pivotInverseMatrix = Matrix(/*4, 4, */true);
	m_transformMatrix = Matrix(/*4, 4, */true);
	m_rotateMatrix = Matrix(/*4, 4, */true);
	m_scaleMatrix = Matrix(/*4, 4, */true);
}

Model::Model(const wchar_t *name, const wchar_t *filePath)
	: m_mesh(new Mesh()), m_name(nullptr)
{
	setName(name);

	m_position = Vec3f(0.0L, 0.0L, 0.0L);
	m_rotation = Vec3f(0.0L, 0.0L, 0.0L);
	m_scale = Vec3f(1.0L, 1.0L, 1.0L);
	m_pivot = Vec3f(0.0L, 0.0L, 0.0L);

	m_pivotMatrix = Matrix(/*4, 4, */true);
	m_pivotInverseMatrix = Matrix(/*4, 4, */true);
	m_transformMatrix = Matrix(/*4, 4, */true);
	m_rotateMatrix = Matrix(/*4, 4, */true);
	m_scaleMatrix = Matrix(/*4, 4, */true);

	parseObjFile(filePath);

	m_color = RGBA((int)(std::rand() % 255), (int)(std::rand() % 255), (int)(std::rand() % 255), 255);
}

Model::~Model()
{
	if (m_mesh != nullptr) {
		delete m_mesh;
		m_mesh = nullptr;
	}
}

Vec3f Model::position() const
{
	return m_position;
}

void Model::setPosition(Vec3f position)
{
	m_position = position;

	m_transformMatrix = Matrix::transform(position);
}

Vec3f Model::rotation() const
{
	return m_rotation;
}

void Model::setRotation(Vec3f rotation)
{
	m_rotation = rotation;

	m_rotateMatrix = Matrix::rotation(rotation);
}

Vec3f Model::scale() const
{
	return m_scale;
}

void Model::setScale(Vec3f scale)
{
	m_scale = scale;

	m_scaleMatrix = Matrix::scale(scale);
}

Vec3f Model::pivot() const
{
	return m_pivot;
}

void Model::setPivot(Vec3f pivot)
{
	m_pivot = pivot;
}

wchar_t *Model::name() const
{
	return m_name;
}

void Model::setName(const wchar_t *name)
{
	size_t length = wcslen(name);

	if (m_name != nullptr) {
		delete[] m_name;
	}

	m_name = new wchar_t[length + 1];

	wcscpy_s(m_name, length + 1, name);
}

//ARGB Model::color() const
//{
//    return m_color;
//}

void Model::setColor(ARGB color)
{
	m_color = color;
}

void Model::setParameters(long double width, long double length, long double height, long double radius, long double lensWidth, long double lensMountLength, long double lensMountWidth, long double marginWidth, long double sideButtonsHeight, long double shutterButtonHeight, long double sideButtonsRadius, long double shutterButtonRadius)
{
	m_parameters[0] = width;
	m_parameters[1] = length;
	m_parameters[2] = height;
	m_parameters[3] = radius;
	m_parameters[4] = lensWidth;
	m_parameters[5] = lensMountLength;
	m_parameters[6] = lensMountWidth;
	m_parameters[7] = marginWidth;
	m_parameters[8] = sideButtonsHeight;
	m_parameters[9] = shutterButtonHeight;
	m_parameters[10] = sideButtonsRadius;
	m_parameters[11] = shutterButtonRadius;
}

Model &Model::operator=(const Model &model)
{
	if (this != &model) {
		if (m_mesh != nullptr) {
			delete m_mesh;
		}

		m_mesh = new Mesh(*model.m_mesh);
		m_color = model.m_color;

		m_position = model.m_position;
		m_rotation = model.m_rotation;
		m_scale = model.m_scale;
		m_pivot = model.m_pivot;

		m_transformMatrix = model.m_transformMatrix;
		m_rotateMatrix = model.m_rotateMatrix;
		m_scaleMatrix = model.m_scaleMatrix;
		m_pivotMatrix = model.m_pivotMatrix;
		m_pivotInverseMatrix = model.m_pivotInverseMatrix;

		m_name = model.m_name;

		for (int i = 0; i < NUM_PARAMETERS; i++) {
			m_parameters[i] = model.m_parameters[i];
		}
	}

	return *this;
}

void Model::parseObjFile(const wchar_t *filePath)
{
	std::wifstream modelFile(filePath);

	if (!modelFile.fail()) {
		std::wstring line;
		wchar_t type[4];
		std::wstring vertex;

		while (!modelFile.eof()) {
			modelFile >> type;

			if (type[0] == L'v') {
				long double x;
				long double y;
				long double z;

				modelFile >> x >> y >> z;

				Vertex vertex(x, y, z);
				m_mesh->addVertex(vertex);
			} else if (type[0] == L'f') {
				int v1, v2, v3;

				std::getline(modelFile, line);

				std::wistringstream stream(line);
				stream >> vertex;
				v1 = wcstol(vertex.substr(0U, vertex.find_first_of(L'\\')).c_str(), nullptr, 10);
				stream >> vertex;
				v2 = wcstol(vertex.substr(0U, vertex.find_first_of(L'\\')).c_str(), nullptr, 10);
				stream >> vertex;
				v3 = wcstol(vertex.substr(0U, vertex.find_first_of(L'\\')).c_str(), nullptr, 10);

				Face face(v1, v2, v3);
				m_mesh->addFace(face);
			}
		}

		modelFile.close();
	}
}

std::wostream &operator<<(std::wostream &out, const Model &model)
{
	char blank = ' ';
	wchar_t *name = model.m_name;
	ARGB color = model.color();
	Vec3f pivot = model.m_pivot;
	Vec3f position = model.m_position;
	Vec3f rotation = model.m_rotation;
	Vec3f scale = model.m_scale;

	out << name << std::endl;
	out << color << std::endl;

	for (int i = 0; i < Model::NUM_PARAMETERS - 1; i++) {
		out << (double)model.m_parameters[i] << blank;
	}

	out << (double)model.m_parameters[Model::NUM_PARAMETERS - 1] << std::endl;

	out << pivot << std::endl;
	out << position << std::endl;
	out << rotation << std::endl;
	out << scale << std::endl;

	return out;
}

std::wistream &operator >> (std::wistream &in, Model &model)
{
	std::wstring name;
	ARGB color;
	double parameters[Model::NUM_PARAMETERS];
	Vec3f pivot, position, rotation, scale;

	std::getline(in, name);
	in >> color;

	for (int i = 0; i < Model::NUM_PARAMETERS; i++) {
		in >> parameters[i];
	}

	in >> pivot >> position >> rotation >> scale;

	model = ModelsFactory::camera(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], parameters[5], parameters[6], parameters[7], parameters[8], parameters[9], parameters[10], parameters[11]);
	model.setName(name.c_str());
	model.setColor(color);
	model.setPivot(pivot);
	model.setPosition(position);
	model.setRotation(rotation);
	model.setScale(scale);

	return in;
}
