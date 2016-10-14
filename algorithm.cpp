#include "stdafx.h"
#include "algorithm.h"
#include <liblogger/liblogger.h>
#include <liblogger/file_logger.h>

using namespace std;

uint32_t g_weightMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = 
{{1,1,1},
{1,1,1},
{1,0,1}
};
PATH_INFO_S g_path;

void initPathInfo(void)
{
    memset(&g_path, 0, sizeof(PATH_INFO_S));
}

void printPath(void)
{
    uint32_t i;

    LogInfo("Path:");

    for (i = 0; i < g_path.length; i++)
    {
        LogInfo("(x:%u, y:%u)<-", g_path.pathTo[i].x, g_path.pathTo[i].y);
    }

    return;
}

uint32_t heuristic(POSITION_S* pos, POSITION_S* goal)
{
    uint32_t absX = 0;
    uint32_t absY = 0;

    if (pos->x >= goal->x)
    {
        absX = pos->x - goal->x;
    }
    else
    {
        absX = goal->x - pos->x;
    }

    if (pos->y >= goal->y)
    {
        absY = pos->y - goal->y;
    }
    else
    {
        absY = goal->y - pos->y;
    }

    return absX + absY;
}

void setAStarNode(ASTAR_NODE_INFO_S* node, uint32_t g, uint32_t h, 
                                ASTAR_TABLE_TYPE_E tableType, POSITION_S* pre)
{
    node->g = g;
    node->h = h;
    node->f = g + h;
    node->parent.x = pre->x;
    node->parent.y = pre->y;
    node->tableType = tableType;
    return;
}

bool isArrived(POSITION_S* curPos, POSITION_S* goal)
{
    return (curPos->x == goal->x) && (curPos->y == goal->y);
}

int32_t getUpNeighber(POSITION_S* curPos, POSITION_S*neighber)
{
    if (0 == curPos->y)
    {
        return RETURN_ERROR;
    }

    neighber->x = curPos->x;
    neighber->y = curPos->y - 1;
    return RETURN_OK;
}

int32_t getDownNeighber(POSITION_S* curPos, POSITION_S*neighber)
{
    if ((MAX_MAP_SIZE - 1) <= curPos->y)
    {
        return RETURN_ERROR;
    }

    neighber->x = curPos->x;
    neighber->y = curPos->y + 1;
    return RETURN_OK;
}

int32_t getLeftNeighber(POSITION_S* curPos, POSITION_S*neighber)
{
    if (0 == curPos->x)
    {
        return RETURN_ERROR;
    }

    neighber->x = curPos->x - 1;
    neighber->y = curPos->y;
    return RETURN_OK;
}

int32_t getRightNeighber(POSITION_S* curPos, POSITION_S*neighber)
{
    if ((MAX_MAP_SIZE - 1) <= curPos->x)
    {
        return RETURN_ERROR;
    }

    neighber->x = curPos->x + 1;
    neighber->y = curPos->y;
    return RETURN_OK;
}

uint32_t getNeighbers(POSITION_S*curPos, POSITION_S neighbers[MAX_NEIGHBER_NUM])
{
    POSITION_S neighber;
    uint32_t num = 0;
    int32_t ret = RETURN_OK;

    ret = getUpNeighber(curPos, &neighber);
    if (RETURN_OK == ret)
    {
        neighbers[num] = neighber;
        num++;
    }

    ret = getDownNeighber(curPos, &neighber);
    if (RETURN_OK == ret)
    {
        neighbers[num] = neighber;
        num++;
    }

    ret = getLeftNeighber(curPos, &neighber);
    if (RETURN_OK == ret)
    {
        neighbers[num] = neighber;
        num++;
    }

    ret = getRightNeighber(curPos, &neighber);
    if (RETURN_OK == ret)
    {
        neighbers[num] = neighber;
        num++;
    }

    return num;
}

bool isClosed(POSITION_S* pos, 
    ASTAR_NODE_INFO_S AStarMap[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    return AStarMap[pos->x][pos->y].tableType == CLOSE;
}

bool isOpen(POSITION_S* pos,
    ASTAR_NODE_INFO_S AStarMap[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    return AStarMap[pos->x][pos->y].tableType == OPEN;
}

uint32_t getRealCost(POSITION_S* pos)
{
    return g_weightMap[pos->x][pos->y];
}

ASTAR_NODE_INFO_S* getAStarNode(POSITION_S* pos,
    ASTAR_NODE_INFO_S AStarMap[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    return &(AStarMap[pos->x][pos->y]);
}

ASTAR_NODE_INFO_S* findMinF(ASTAR_NODE_INFO_S AStarMap[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t minF = MAX_WEIGHT;
    uint32_t minX = 0;
    uint32_t minY = 0;

    for (i = 0; i < MAX_MAP_SIZE; i++)
    {
        for (j = 0; j < MAX_MAP_SIZE; j++)
        {
            if ((OPEN == AStarMap[i][j].tableType) && (minF > AStarMap[i][j].f))
            {
                minX = i;
                minY = j;
                minF = AStarMap[i][j].f;
            }
        }
    }

    return &(AStarMap[minX][minY]);
}

bool isSelfPosition(POSITION_S* aPos, POSITION_S* bPos)
{
    return ((aPos->x == bPos->x) && (aPos->y == bPos->y));
}

void getShortestPath(POSITION_S* goal, PATH_INFO_S* path, 
    ASTAR_NODE_INFO_S AStarMap[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    uint32_t length = 0;
    POSITION_S pos;
    
    pos.x = goal->x;
    pos.y = goal->y;

    while (!isSelfPosition(&(AStarMap[pos.x][pos.y].parent), &pos))
    {
        path->pathTo[path->length] = pos;
        path->length++;
        pos = AStarMap[pos.x][pos.y].parent;
    }

    return;
}

void initAStarMap(ASTAR_NODE_INFO_S AStarMap[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    uint32_t i;
    uint32_t j;

    for (i = 0; i < MAX_MAP_SIZE; i++)
    {
        for (j = 0; j < MAX_MAP_SIZE; j++)
        {
            AStarMap[i][j].pos.x = i;
            AStarMap[i][j].pos.y = j;
            AStarMap[i][j].parent = AStarMap[i][j].pos;
        }
    }
}

void AStarSearch(POSITION_S* start, POSITION_S* goal, 
        uint32_t(*heuristicFunc)(POSITION_S* pos, POSITION_S* goal))
{
    uint32_t i;
    uint32_t h;
    uint32_t g;
    uint32_t f;
    uint32_t neighberNum = 0;
    uint32_t openNum = 0;
    POSITION_S neighbers[MAX_NEIGHBER_NUM];
    ASTAR_NODE_INFO_S AStarMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
    ASTAR_NODE_INFO_S* curNode;
    ASTAR_NODE_INFO_S* nextNode;
    
    memset(AStarMap, 0, sizeof(AStarMap));
    initAStarMap(AStarMap);

    /* 将起始节点加入open表 */
    curNode = getAStarNode(start, AStarMap);
    setAStarNode(curNode, 0, 0, OPEN, start);
    openNum++;

    while (0 != openNum)
    {
        /* 检查是否已经到达目标位置 */
        curNode = findMinF(AStarMap);
        if (isArrived(&(curNode->pos), goal))
        {
            getShortestPath(goal, &g_path, AStarMap);
            break;
        }

        /* 将权重最小节点加入close表 */
        AStarMap[curNode->pos.x][curNode->pos.y].tableType = CLOSE;
        openNum--;

        /* 遍历所有邻居判断是否应该加入open表 */
        neighberNum = getNeighbers(&(curNode->pos), neighbers);
        for (i = 0; i < neighberNum; i++)
        {
            /* 已经close的节点跳过 */
            if (isClosed(&neighbers[i], AStarMap))
            {
                continue;
            }

            /* 计算新节点的g和h */
            g = getRealCost(&neighbers[i]);
            h = heuristicFunc(&neighbers[i], goal);
            f = g + h;

            nextNode = getAStarNode(&neighbers[i], AStarMap);
            /* 邻居节点已经在open列表中 */
            if (isOpen(&neighbers[i], AStarMap))
            {
                /* 如果新的路径更短选新的 */
                if (g < nextNode->g)
                {
                    setAStarNode(nextNode, g, h, OPEN, &(curNode->pos));
                    openNum++;
                }
                continue;
            }

            /* 邻居节点未在open表中，新添加 */
            setAStarNode(nextNode, g, h, OPEN, &(curNode->pos));
            openNum++;
        }
    }
}