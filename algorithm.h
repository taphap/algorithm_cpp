#pragma once

#define MAX_MAP_SIZE (3)
#define MAX_NEIGHBER_NUM (4)
#define RETURN_OK (0)
#define RETURN_ERROR (1)
#define MAX_WEIGHT (100)

typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct tagPOSTION_S
{
    uint32_t x;
    uint32_t y;
} POSITION_S;

typedef enum tagASTAR_TABLE_TYPE_E
{
    INIT = 0,
    OPEN,
    CLOSE
} ASTAR_TABLE_TYPE_E;

typedef struct tagASTAR_NODE_INFO_S
{
    POSITION_S pos;
    POSITION_S parent;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    ASTAR_TABLE_TYPE_E tableType;
} ASTAR_NODE_INFO_S;

typedef struct tagPATH_INFO_S
{
    uint32_t length;
    POSITION_S pathTo[MAX_MAP_SIZE*MAX_MAP_SIZE];
} PATH_INFO_S;

typedef uint32_t(*heuristicFunc)(POSITION_S* pos, POSITION_S* goal);

uint32_t heuristic(POSITION_S* pos, POSITION_S* goal);

void AStarSearch(POSITION_S* start, POSITION_S* goal,
    uint32_t(*heuristicFunc)(POSITION_S* pos, POSITION_S* goal));
void initPathInfo(void);
void printPath(void);