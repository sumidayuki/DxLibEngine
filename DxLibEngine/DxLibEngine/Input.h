#pragma once

/// <summary>
/// Inputを扱うコンポーネントです。
/// </summary>
struct Input
{
	bool moveUp;		// 上方向
	bool moveDown;		// 下方向
	bool moveLeft;		// 左方向
	bool moveRight;		// 右方向
	bool shot;			// ショット

	float horizontal;
	float vartical;
	Vector3 direction;
};