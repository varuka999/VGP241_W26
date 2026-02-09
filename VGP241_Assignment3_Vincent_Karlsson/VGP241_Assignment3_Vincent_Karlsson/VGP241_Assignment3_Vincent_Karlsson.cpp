#include <iostream>
#include <vector>

struct Vector3
{
    Vector3()
    {
        x = rand() % 100;
        y = rand() % 100;
        z = rand() % 100;
    }
    Vector3(int _x, int _y, int _z)
        : x(_x), y(_y), z(_z)
    {
    }

    int x = 0;
    int y = 0;
    int z = 0;
};

struct KDNode
{
    Vector3 mData;
    KDNode* mLeft = nullptr;
    KDNode* mRight = nullptr;
};

void DeleteKDTree(KDNode* node)
{
    if (node != nullptr)
    {
        DeleteKDTree(node->mLeft);
        DeleteKDTree(node->mRight);
        delete node;
        node = nullptr;
    }
}

float DistSquared(const Vector3& v0, const Vector3& v1)
{
    Vector3 diff;
    diff.x = v0.x - v1.x;
    diff.y = v0.y - v1.y;
    diff.z = v0.z - v1.z;

    return (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
}

KDNode* Closest(KDNode* n0, KDNode* n1, const Vector3& v)
{
    if (n0 == nullptr)
    {
        return n1;
    }

    if (n1 == nullptr)
    {
        return n0;
    }

    long d1 = DistSquared(n0->mData, v);
    long d2 = DistSquared(n1->mData, v);

    if (d1 < d2)
    {
        return n0;
    }
    else
    {
        return n1;
    }
}

KDNode* NearestNeighbor(const Vector3& v, KDNode* node, int k)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    KDNode* nextBranch = nullptr;
    KDNode* otherBranch = nullptr;

    if (k == 0)
    {
        if (v.x < node->mData.x)
        {
            nextBranch = node->mLeft;
            otherBranch = node->mRight;
        }
        else
        {
            nextBranch = node->mRight;
            otherBranch = node->mLeft;
        }
    }
    else if (k == 1)
    {
        if (v.y < node->mData.y)
        {
            nextBranch = node->mLeft;
            otherBranch = node->mRight;
        }
        else
        {
            nextBranch = node->mRight;
            otherBranch = node->mLeft;
        }
    }
    else if (k == 2)
    {
        if (v.z < node->mData.z)
        {
            nextBranch = node->mLeft;
            otherBranch = node->mRight;
        }
        else
        {
            nextBranch = node->mRight;
            otherBranch = node->mLeft;
        }
    }

    KDNode* temp = NearestNeighbor(v, nextBranch, (k + 1) % 3);
    KDNode* best = Closest(temp, node, v);

    float distSqr = DistSquared(v, best->mData);
    float planeDist = 0.0f;

    if (k == 0)
    {
        planeDist = v.x - node->mData.x;
    }
    else if (k == 1)
    {
        planeDist = v.y - node->mData.y;
    }
    else
    {
        planeDist = v.z - node->mData.z;
    }

    if (distSqr >= planeDist * planeDist)
    {
        temp = NearestNeighbor(v, otherBranch, (k + 1) % 3);
        best = Closest(temp, best, v);
    }

    return best;
}


KDNode* Insert(const Vector3& v, KDNode* prev, int k)
{
    if (prev == nullptr)
    {
        KDNode* newNode = new KDNode();
        newNode->mData = v;

        return newNode;
    }

    if (prev->mData.x == v.x && prev->mData.y == v.y && prev->mData.z == v.z)
    {
        std::cout << "[ERROR] Node Already Added!!!\n";
        return prev;
    }

    if (k == 0)
    {
        if (v.x < prev->mData.x)
        {
            prev->mLeft = Insert(v, prev->mLeft, (k + 1) % 3);
        }
        else
        {
            prev->mRight = Insert(v, prev->mRight, (k + 1) % 3);
        }
    }
    else if (k == 1)
    {
        if (v.y < prev->mData.y)
        {
            prev->mLeft = Insert(v, prev->mLeft, (k + 1) % 3);
        }
        else
        {
            prev->mRight = Insert(v, prev->mRight, (k + 1) % 3);
        }
    }
    else if (k == 2) // 3rd dimension
    {
        if (v.z < prev->mData.z)
        {
            prev->mLeft = Insert(v, prev->mLeft, (k + 1) % 3);
        }
        else
        {
            prev->mRight = Insert(v, prev->mRight, (k + 1) % 3);
        }
    }
    else
    {
        std::cout << "[ERROR] dimension not set up\n";
    }

    return prev;
}

Vector3 Minimum(const Vector3& a, const Vector3& b, const Vector3& c, int dim)
{
    float aDimValue = (dim == 0) ? a.x : (dim == 1) ? a.y : a.z;
    float bDimValue = (dim == 0) ? b.x : (dim == 1) ? b.y : b.z;
    float cDimValue = (dim == 0) ? c.x : (dim == 1) ? c.y : c.z;

    if (aDimValue < bDimValue && aDimValue < cDimValue)
    {
        return a;
    }
    else if (bDimValue < aDimValue && bDimValue < cDimValue)
    {
        return b;
    }

    return c;
}

Vector3 FindMin(KDNode* node, int dim, int k)
{
    if (node == nullptr)
    {
        Vector3 invalid;
        invalid.x = INT_MAX;
        invalid.y = INT_MAX;
        invalid.z = INT_MAX;

        return invalid;
    }

    if (k == dim)
    {
        if (node->mLeft == nullptr)
        {
            return node->mData;
        }
        else
        {
            return FindMin(node->mLeft, dim, (k + 1) % 3);
        }
    }
    else
    {
        return Minimum(FindMin(node->mLeft, dim, (k + 1) % 3),
            FindMin(node->mRight, dim, (k + 1) % 3),
            node->mData,
            dim);
    }
}

void PrintRange(const Vector3& center, float radius, KDNode* node, int k)
{
    if (node == nullptr)
    {
        return;
    }

    // check if rhe node is within radius
    float distSqr = DistSquared(center, node->mData);
    if (distSqr <= radius * radius)
    {
        std::cout << "(" << node->mData.x << ", " << node->mData.y << ", " << node->mData.z << ")\n";
    }

    float distance = 0.0f;

    if (k == 0)
    {
        distance = center.x - node->mData.x;

        if (distance <= radius)
        {
            PrintRange(center, radius, node->mLeft, (k + 1) % 3);
        }

        if (-distance <= radius)
        {
            PrintRange(center, radius, node->mRight, (k + 1) % 3);
        }
    }
    else if (k == 1)
    {
        distance = center.y - node->mData.y;

        if (distance <= radius)
        {
            PrintRange(center, radius, node->mLeft, (k + 1) % 3);
        }

        if (-distance <= radius)
        {
            PrintRange(center, radius, node->mRight, (k + 1) % 3);
        }
    }
    else if (k == 2)
    {
        distance = center.z - node->mData.z;

        if (distance <= radius)
        {
            PrintRange(center, radius, node->mLeft, (k + 1) % 3);
        }

        if (-distance <= radius)
        {
            PrintRange(center, radius, node->mRight, (k + 1) % 3);
        }
    }
}

enum class PickupType
{
    Invalid = 0,
    Health,
    WeaponAmmo,
    Coins,
    Upgrade,
    SpecialItem,
    Count,
};

class Pickup
{
public:
    Pickup(PickupType pickupType, const Vector3& pos)
        : mType(pickupType), mPosition(pos)
    {
        mName = SetName();
    }

    PickupType GetType() const
    {
        return mType;
    }

    std::string GetName() const
    {
        return mName;
    }

    Vector3 GetPosition() const
    {
        return mPosition;
    }

private:
    PickupType mType;
    std::string mName;
    Vector3 mPosition;

    std::string SetName()
    {
        switch (mType)
        {
        case PickupType::Health:
            return "Health";
        case PickupType::WeaponAmmo:
            return "WeaponAmmo";
        case PickupType::Coins:
            return "Coins";
        case PickupType::Upgrade:
            return "Upgrade";
        case PickupType::SpecialItem:
            return "SpecialItem";
        default:
            return "Invalid";
        }
    }
};

class PickupManager
{
public:
    ~PickupManager()
    {
        DeleteKDTree(mRoot);
        mRoot = nullptr;
    }

    void AddItem(PickupType pickupType, const Vector3& pos)
    {
        Pickup newPickup(pickupType, pos);
        mPickups.push_back(newPickup);

        KDNode* newNode = Insert(pos, mRoot, 0);
        if (mRoot == nullptr)
        {
            mRoot = newNode;
        }

        std::cout << "(" << newPickup.GetName() << ": " << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    }

    const Pickup* GetClosestsPickup(const Vector3& pos)
    {
        if (mRoot == nullptr)
        {
            return nullptr;
        }

        KDNode* closestNode = NearestNeighbor(pos, mRoot, 0);
        if (closestNode == nullptr)
        {
            return nullptr;
        }

        for (size_t i = 0; i < mPickups.size(); ++i)
        {
            const Vector3& pickupPos = mPickups[i].GetPosition();

            if (pickupPos.x == closestNode->mData.x &&
                pickupPos.y == closestNode->mData.y &&
                pickupPos.z == closestNode->mData.z)
            {
                return &mPickups[i];
            }
        }

        return nullptr;
    }

    void ObtainPickupsInRange(const Vector3& pos, float range, PickupType pickupType)
    {
        float rangeSqr = range * range;

        for (size_t i = 0; i < mPickups.size(); ++i)
        {
            const Pickup& pickup = mPickups[i];

            if (pickupType != PickupType::Invalid)
            {
                if (pickup.GetType() != pickupType)
                {
                    continue;
                }
            }

            float distSqr = DistSquared(pos, pickup.GetPosition());
            if (distSqr <= rangeSqr)
            {
                const Vector3& p = pickup.GetPosition();
                std::cout << pickup.GetName() << ": (" << p.x << ", " << p.y << ", " << p.z << ")\n";
            }
        }
    }
private:
    std::vector<Pickup> mPickups;
    KDNode* mRoot = nullptr;
};

int main()
{
    srand(time(NULL));
    PickupManager pickupManager;
    Vector3 player = Vector3(rand() % 50, rand() % 50, rand() % 50);

    std::cout << "All Item Positions:\n";
    for (int i = 0; i < 100; ++i)
    {
        int typeInt = 1 + (rand() % ((int)PickupType::Count - 1));
        Vector3 pos = Vector3();
        pickupManager.AddItem((PickupType)typeInt, pos);
    }

    std::cout << "\n";
    std::cout << "Player positon: " << player.x << ", " << player.y << ", " << player.z << "\n\n";

    // Scenario 1
    std::cout << "All items within 10.0f:\n";

    pickupManager.ObtainPickupsInRange(player, 10.0f, PickupType::Invalid);
    std::cout << "\n";

    // Scenario 2
    std::cout << "All Health items within 50.0f:\n";

    pickupManager.ObtainPickupsInRange(player, 50.0f, PickupType::Health);
    std::cout << "\n";

    // Scenario 3
    std::cout << "Closest item to the player:\n";

    const Pickup* closest = pickupManager.GetClosestsPickup(player);
    if (closest != nullptr)
    {
        const Vector3& p = closest->GetPosition();
        std::cout << closest->GetName() << ": (" << p.x << ", " << p.y << ", " << p.z << ")\n";
    }
}