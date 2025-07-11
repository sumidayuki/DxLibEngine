#include "GeometryUtility.h"
#include "SystemList.h"

void GeometryUtility::CalculateFrustumPlanes(const Matrix4x4& worldToProjectionMatrix, Plane planes[6])
{
    ExtractPlanes(planes, worldToProjectionMatrix);
}


void GeometryUtility::CalculateFrustumPlanes(World& world, Transform& transform, Camera& camera,Plane planes[6])
{
    const Matrix4x4& view = world.GetSystem<CameraSystem>()->GetWorldToCameraMatrix(transform, world);
    const Matrix4x4& proj = world.GetSystem<CameraSystem>()->GetProjectionMatrix(camera);
    CalculateFrustumPlanes(view * proj, planes);
}

void GeometryUtility::ExtractPlanes(Plane planes[6], const Matrix4x4& worldToProjectionMatrix)
{
    // 参考: https://www.gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf

    // 引数名が長いので参照変数で短くしたい
    const Matrix4x4& m = worldToProjectionMatrix;

    struct UnnormalizedPlane
    {
        Vector3 normal;
        float distance;
    };

    // 正規化されていない平面 (Direct3D用)
    const UnnormalizedPlane unnormalizedPlanes[6] =
    {
        { Vector3(m._14 + m._11, m._24 + m._21, m._34 + m._31), m._44 + m._41 },  // Left
        { Vector3(m._14 - m._11, m._24 - m._21, m._34 - m._31), m._44 - m._41 },  // Right
        { Vector3(m._14 + m._12, m._24 + m._22, m._34 + m._32), m._44 + m._42 },  // Down
        { Vector3(m._14 - m._12, m._24 - m._22, m._34 - m._32), m._44 - m._42 },  // Up
        { Vector3(m._13,         m._23,         m._33), m._43         },  // Near
        { Vector3(m._14 - m._13, m._24 - m._23, m._34 - m._33), m._44 - m._43 },  // Far
    };

    // 平面の正規化
    for (int i = 0; i < 6; i++)
    {
        // ノルムの逆数
        const float reciprocal = 1.0f / unnormalizedPlanes[i].normal.Magnitude();
        planes[i] = Plane(unnormalizedPlanes[i].normal * reciprocal, unnormalizedPlanes[i].distance * reciprocal);
    }
}

