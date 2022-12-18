// ###### Config options ################

#define PRINT_PATHS 1

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

#ifdef PRINT_PATHS
#include "ppm.h"
#endif

using namespace Asedio;

Vector3 cellCenterToPosition(int i, int j, float cellWidth, float cellHeight){ 
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0); 
}

float distance (Vector3 a, Vector3 b){
    return (sqrt(pow((a.x-b.x), 2) + pow((a.y-b.y), 2)));
}

bool noPertenece (std::vector<AStarNode*> vector, AStarNode* j){
    std::vector<AStarNode*>::iterator i;
    bool pertenece = false;
    for (i = vector.begin(); i != vector.end(); ++i){
        if ((*i) == j && !pertenece){
            pertenece = true;
            return pertenece;
        }
    }
    return pertenece;
}

bool condition (AStarNode* a, AStarNode* b){
    return (a->H > b->H);
}

void DEF_LIB_EXPORTED calculateAdditionalCost(float** additionalCost, int cellsWidth, int cellsHeight, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {

    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;
    List<Defense*>::iterator currentDefense = defenses.begin();
    float d, cost;
    Vector3 casilla;
    
    for(int i = 0 ; i < cellsHeight ; ++i) {
        for(int j = 0 ; j < cellsWidth ; ++j){
            while (currentDefense !=  defenses.end()){
                casilla = cellCenterToPosition(i, j, cellWidth, cellHeight);
                d = distance((*currentDefense)->position, casilla);
                if (d < (*currentDefense)->range){
                    cost = d*(*currentDefense)->range;
                } else {
                    cost = d;
                }
            ++currentDefense;
            }
        additionalCost[i][j] = cost;
        }
    }
}

void DEF_LIB_EXPORTED calculatePath(AStarNode* originNode, AStarNode* targetNode, int cellsWidth, int cellsHeight, float mapWidth, float mapHeight, float** additionalCost, std::list<Vector3> &path) {

    int nCellsWidth = mapWidth/cellsWidth, nCellsHeight = mapHeight/cellsHeight, maxIter = 100;
    std::vector<AStarNode*> opened;
    std::vector<AStarNode*> closed;
    AStarNode* cur = originNode;
    List<AStarNode*>::iterator j;
    bool found = false;

    //A* sacado de las diapositivas de la asignatura

    targetNode->parent = NULL;
    cur->G = 0;
    cur->H = distance(cur->position, targetNode->position) + additionalCost[(int)(cur->position.x/cellsWidth)][(int)(cur->position.y/cellsHeight)];
    cur->parent = NULL; 
    cur->F = cur->G + cur->H;
    opened.push_back(cur);
    std::make_heap(opened.begin(), opened.end(), condition);

    while(!found && !opened.empty()){
        cur = opened.back();
        opened.pop_back();
        closed.push_back(cur);
        if (cur == targetNode){
            found = true;
        } else {
            for (j = cur->adjacents.begin(); j != cur->adjacents.end(); ++j){
                if (!noPertenece(closed, (*j))){
                    if (!noPertenece(opened, (*j))){
                        (*j)->parent = cur;
                        (*j)->G = cur->G + distance(cur->position, (*j)->position);
                        (*j)->H = distance((*j)->position, targetNode->position) + additionalCost[(int)(*j)->position.x/cellsWidth][(int)(*j)->position.y/cellsHeight];
                        (*j)->F = (*j)->G + (*j)->H;
                        opened.push_back((*j));
                        std::make_heap(opened.begin(), opened.end(), condition);
                        std::sort_heap(opened.begin(), opened.end(), condition);
                    } else {
                        if ((*j)->G > cur->G + distance(cur->position, (*j)->position)){
                            (*j)->parent = cur;
                            (*j)->G = cur->G + distance(cur->position, (*j)->position);
                            (*j)->F = (*j)->G + (*j)->H;
                            std::make_heap(opened.begin(), opened.end(), condition);
                            std::sort_heap(opened.begin(), opened.end(), condition);
                        }
                    } 
                }
            }
        }
    }

    //Retorno de camino sacado de las diapositivas de la asignatura

    cur = targetNode;
    path.push_front(targetNode->position);
    while(cur->parent != originNode && targetNode->parent != NULL){
        cur = cur->parent;
        path.push_front(cur->position);
    }
}