// ###### Config options ################

#define PRINT_DEFENSE_STRATEGY 1    // generate map images

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

#ifdef PRINT_DEFENSE_STRATEGY
#include "ppm.h"
#endif

#ifdef CUSTOM_RAND_GENERATOR
RAND_TYPE SimpleRandomGenerator::a;
#endif

using namespace Asedio;



Vector3 cellCenterToPosition (int i, int j, float cellWidth, float cellHeight){ 
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0); 
}
void positionToCell(const Vector3 pos, int &i_out, int &j_out, float cellWidth, float cellHeight){
    i_out = (int)(pos.y * 1.0f/cellHeight); 
    j_out = (int)(pos.x * 1.0f/cellWidth);
}

Vector3 vorazCentro (bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses, float radio);
Vector3 vorazDefensas(int rowC, int colC, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses, float radio);

float cellValue(int row, int col, bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    float value = 2000;
    int rowO, colO;
    Vector3 pos = cellCenterToPosition (nCellsWidth/2, nCellsHeight/2, cellWidth, cellHeight), posC = cellCenterToPosition (row, col, cellWidth, cellHeight);
    float distancia = sqrt(((pos.x - posC.x)*(pos.x - posC.x)) + ((pos.y - posC.y)*(pos.y - posC.y)));

    if (distancia < 10)
        return value;
    else
        value = 1000;   

	return value; // implemente aqui la funci�n que asigna valores a las celdas
}

float cellValueDefensas(int row, int col, int rowC, int colC, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses){
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    float value = 0, min = 20, i = 0;
    Vector3 pos =  cellCenterToPosition (row, col, cellWidth, cellHeight), posC = cellCenterToPosition (rowC, colC, cellWidth, cellHeight); 
    float distancia = sqrt(((pos.x - posC.x)*(pos.x - posC.x)) + ((pos.y - posC.y)*(pos.y - posC.y)));
    if  (distancia < min)
        value = 2000;
    else {
        while(min + i < mapWidth || min + i < mapHeight){
            if (distancia < min + i)
                return (1000 - i);
        i = i + 10;
        }
    }
    return value;
}

void DEF_LIB_EXPORTED placeDefenses(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, std::list<Object*> obstacles, std::list<Defense*> defenses) {
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 
    List<Defense*>::iterator currentDefense = defenses.begin();
    Vector3 posC = vorazCentro(freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses, (*currentDefense)->radio), pos;
    int maxAttemps = 1000, i_out, j_out;
    

    (*currentDefense)->position.x = posC.x;
    (*currentDefense)->position.y = posC.y;
    (*currentDefense)->position.z = 0;
    ++currentDefense;

    positionToCell(posC, i_out, j_out, cellWidth, cellHeight);
    while(currentDefense != defenses.end() && maxAttemps > 0) {
        pos = vorazDefensas(i_out, j_out, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses, (*currentDefense)->radio);
        (*currentDefense)->position.x = pos.x;
        (*currentDefense)->position.y = pos.y;
        (*currentDefense)->position.z = 0; 
        ++currentDefense;
    }

#ifdef PRINT_DEFENSE_STRATEGY

    float** cellValues = new float* [nCellsHeight]; 
    for(int i = 0; i < nCellsHeight; ++i) {
       cellValues[i] = new float[nCellsWidth];
       for(int j = 0; j < nCellsWidth; ++j) {
           cellValues[i][j] = ((int)(cellValue(i, j, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses))) % 256;
       }
    }
    dPrintMap("strategy.ppm", nCellsHeight, nCellsWidth, cellHeight, cellWidth, freeCells, cellValues, std::list<Defense*>(), true);

    for(int i = 0; i < nCellsHeight ; ++i)
        delete [] cellValues[i];
	delete [] cellValues;
	cellValues = NULL;

#endif
}

bool factibilidad (int fila, int columna, std::list<Object*> obstacles, std::list<Defense*> defenses, float mapWidth, float mapHeight, int nCellsWidth, int nCellsHeight, float radio){
    List<Object*>::iterator currentObstacles = obstacles.begin();
    List<Defense*>::iterator currentDefense = defenses.begin();

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    float distancia;

    Vector3 pos = cellCenterToPosition(fila, columna, cellWidth, cellHeight);
    int maxAttemps = 1000;

    if (pos.x+radio > mapWidth || pos.x-radio < 0 || pos.y+radio > mapHeight || pos.y-radio < 0)
        return 0;
    else{
        while(currentObstacles != obstacles.end() && maxAttemps > 0){
            distancia = sqrt(((*currentObstacles)->position.x - pos.x)*((*currentObstacles)->position.x - pos.x) + ((*currentObstacles)->position.y - pos.y)*((*currentObstacles)->position.y - pos.y));
            if (distancia < ((*currentObstacles)->radio + radio))
                return 0;
            ++currentObstacles;
        }
        while(currentDefense != defenses.end() && maxAttemps > 0){
            distancia = sqrt(((*currentDefense)->position.x - pos.x)*((*currentDefense)->position.x - pos.x) + ((*currentDefense)->position.y - pos.y)*((*currentDefense)->position.y - pos.y));
            if (distancia < ((*currentDefense)->radio + radio))
                return 0;
            ++currentDefense;
        }     
    }
    return 1;
}

Vector3 vorazCentro (bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses, float radio){
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 
    float cellValues[nCellsWidth][nCellsHeight];
    float maxValue = 0;
    Vector3 pos;

    for(int row = 0; row < nCellsWidth; row++){
        for(int col = 0; col < nCellsHeight; col++){
            cellValues[row][col] = 0;
            if(factibilidad(row, col, obstacles, defenses, mapWidth, mapHeight, nCellsWidth, nCellsHeight, radio) == 1){
                cellValues[row][col] = cellValue(row, col, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses);                
                if (cellValues[row][col] > maxValue){
                    maxValue = cellValues[row][col];
                    pos = cellCenterToPosition (row, col, cellWidth, cellHeight);
                }
            }
        }
    }
    return pos;
}

Vector3 vorazDefensas(int rowC, int colC, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses, float radio){
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 
    float cellValues[nCellsWidth][nCellsHeight];
    float maxValue = 0;
    Vector3 pos;

    for(int row = 0; row < nCellsWidth; row++){
        for(int col = 0; col < nCellsHeight; col++){
            cellValues[row][col] = 0;
            if(factibilidad(row, col, obstacles, defenses, mapWidth, mapHeight, nCellsWidth, nCellsHeight, radio) == 1){
                cellValues[row][col] = cellValueDefensas(row, col, rowC, colC, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses);                
                if (cellValues[row][col] > maxValue){
                    maxValue = cellValues[row][col];
                    pos = cellCenterToPosition(row, col, cellWidth, cellHeight);
                }
            }
        }
    }
    return pos;
}