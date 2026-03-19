#pragma once

enum Stats
{
    Health,
    Attack,
    Defense,
    Stamina,
    Speed,
};

enum class StatsA6
{
    Health = 0,
    Attack,
    Speed,
    AttackCount,
};

enum ItemType
{
    Null = -1,
    SmallPotion,
	MediumPotion,
	LargePotion,
    FireBall,
	IceBall,
	ThunderBall,
    WaterBall,
    Count,
};