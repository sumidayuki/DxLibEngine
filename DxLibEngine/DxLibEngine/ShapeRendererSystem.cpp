#include "ShapeRendererSystem.h"

void ShapeRendererSystem::Draw(ComponentManager& cm, World& world)
{
	View<Box, Transform> boxView(cm);

	// squaresをentityとsquareに分解して探索します。
	for (auto [entity, box, transform] : boxView)
	{
		if (!box.isActive) continue;
		DrawBox(transform.position.x, transform.position.y, transform.position.x + (int)box.x, transform.position.y + (int)box.y, GetColor(box.r, box.g, box.b), TRUE);
	}

	View<Circle, Transform> circleView(cm);

	// circlesをentityとcircleに分解して探索します。
	for (auto [entity, circle, transform] : circleView)
	{
		if (!circle.isActive) continue;
		DrawCircle(transform.position.x, transform.position.y, circle.radius, GetColor(circle.r, circle.g, circle.b), TRUE);
	}

	View<Triangle, Transform> triangleView(cm);

	// trianglesをentityとtriangleに分解して探索します。
	for (auto [entity, triangle, transform] : triangleView)
	{
		if (triangle.isActive) continue;
		DrawTriangle
		(
			(int)triangle.x1 + transform.position.x, (int)triangle.y1 + transform.position.y,
			(int)triangle.x2 + transform.position.x, (int)triangle.y2 + transform.position.y,
			(int)triangle.x3 + transform.position.x, (int)triangle.y3 + transform.position.y,
			GetColor(triangle.r, triangle.g, triangle.b),
			TRUE
		);
	}
}
