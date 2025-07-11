#include "EnemyVSystem.h"

void EnemyVSystem::Start(ComponentManager& cm, World& world)
{
	m_transformSystem = world.GetSystem<TransformSystem>();
}

void EnemyVSystem::Update(ComponentManager& cm, World& world)
{
	View<EnemySpawnInfo> view(cm);

	for (auto [entity, info] : view)
	{
        // フォーメーションがVでないならこのfor文を抜けます。
		if (info.formation != Formation::V) continue;

        info.timer += Time::GetDeltaTime();

        // タイマーがクールダウンを超えているかつ生成数が既定の生成数を超えていない時
        if (info.timer >= info.coolDown && info.times > 0)
        {
            // 左右に2体ずつ出す
            for (int i = 0; i < 2; ++i)
            {
                int dir = (i == 0) ? -1 : 1; // 左 or 右
                Vector3 offset = Vector3(dir * 75 * info.times, 100 * info.times, 0);
                Vector3 spawnPos = info.position + offset;

                Entity* enemy = world.CreateWithSprite(info.texture, Rect(0, 0, 128, 128), Vector2(0.5f, 0.5f), 1.0f, nullptr, spawnPos, Quaternion(0, 0, 0, 1));
                world.AddComponent<Enemy>(*enemy, Enemy{ .formation = info.formation });
				world.AddComponent<CircleCollider2D>(*enemy, CircleCollider2D{ .radius = 30 });
				world.AddComponent<Status>(*enemy, Status{ .life = 1 });
            }
            info.times--;
            info.timer = 0.0f;
        }

		if (info.times == 0)
		{
			world.DestoryEntity(entity);
		}
	}
}
