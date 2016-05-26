#pragma once

#include "DWin3DLib_global.h"
#include "IViewport.h"
#include "Scene.h"
#include "Camera.h"
#include "Utils/Utils.h"
#include "Math/Vec3i.h"
#include "Math/Vec3f.h"
#include "Math/Vec4f.h"

class DWIN3DLIB_API DehaxGL
{
    
public:
    explicit DehaxGL(IViewport *viewport);
    ~DehaxGL();
    
    enum RenderMode { Wireframe = 0x1, Solid = 0x2, Both = Wireframe | Solid };
    void render(const DehaxGL::RenderMode &renderMode);
    
    void loadScene(const wchar_t *sceneFilePath);
    
    void setViewportSize(const int &width, const int &height);
    void toggleAxisRender();
    
    Camera &camera() const;
    Scene &scene() const;
    
private:
    void renderModel(Model &model, const RenderMode &renderMode);
    void drawFace(Vec3f &v1, Vec3f &v2, Vec3f &v3, const ARGB &triangleColor, const ARGB &edgeColor, int *zBuffer, const RenderMode &renderMode, bool backfaceCulling);
    void drawTriangle(Vec3i &t0, Vec3i &t1, Vec3i &t2, const ARGB &color, int *zBuffer);
    void drawLine(Vec3i &from, Vec3i &to, const ARGB &color);
    Vec3i calculateScreenCoordinates(const Vec3f &v);
    Matrix calculateVertexMatrix(const Matrix &world) const;
    
    IViewport *m_viewport;
    Scene *m_scene;
    Camera *m_camera;
    int *m_zBuffer;
    int m_width;
    int m_height;
    bool m_renderAxis;
};
