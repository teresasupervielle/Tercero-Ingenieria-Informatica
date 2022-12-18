// ###### Config options ################



// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "cronometro.h"

using namespace Asedio;  

struct Ordenacion{
    float valor;
    int row;
    int col;
};

using namespace Asedio;

Vector3 cellCenterToPosition (int i, int j, float cellWidth, float cellHeight){ 
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0); 
}

void ordenacion_fusion (Ordenacion orden[], int i, int j, int N);
void fusion (Ordenacion orden[], int i, int k, int j, int N);

/*void ordenacion_rapida (Ordenacion orden[], int i, int j, int N);
int pivote (Ordenacion orden[], int i, int j, int N);

bool criterio(Ordenacion o, Ordenacion o2);*/

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

float defaultCellValue(int row, int col, bool** freeCells, int nCellsWidth, int nCellsHeight
    , float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {
    	
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    Vector3 cellPosition((col * cellWidth) + cellWidth * 0.5f, (row * cellHeight) + cellHeight * 0.5f, 0);
    	
    float val = 0;
    for (List<Object*>::iterator it=obstacles.begin(); it != obstacles.end(); ++it) {
	    val += _distance(cellPosition, (*it)->position);
    }

    return val;
}

void DEF_LIB_EXPORTED placeDefenses3(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , List<Object*> obstacles, List<Defense*> defenses) {

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 
    //float cellValues[nCellsWidth][nCellsHeight];
    float max = 0;
    List<Defense*>::iterator currentDefense = defenses.begin();
    Vector3 pos;
    const int N = nCellsWidth*nCellsHeight;
    Ordenacion orden[N];
    int prow, pcol, i=0, j=N-1;
    //const double e_abs = 0.01, e_rel = 0.001; 

    /*for(int row = 0; row < nCellsWidth; row++){
        for(int col = 0; col < nCellsHeight; col++){
            cellValues[row][col] = defaultCellValue(row, col, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses);
        }
    }

	cronometro c;
    long int r = 0;
    c.activar();
    do {	
        while(currentDefense != defenses.end()){
            for(int row = 0; row < nCellsWidth; row++){
                for(int col = 0; col < nCellsHeight; col++){
                    if (cellValues[row][col] > max && factibilidad(row, col, obstacles, defenses, mapWidth, mapHeight, nCellsWidth, nCellsHeight, (*currentDefense)->radio) == 1){
                        max = cellValues[row][col];
                        prow = row;
                        pcol = col;
                    }
                }
            }

            pos = cellCenterToPosition (prow, pcol, cellWidth, cellHeight);
            (*currentDefense)->position.x = pos.x;
            (*currentDefense)->position.y = pos.y;
            (*currentDefense)->position.z = 0;
            cellValues[prow][pcol] = -1;
            max = 0;
            ++currentDefense;
		}		
		++r;
    } while(c.tiempo() < e_abs / e_rel + e_abs);
    c.parar();

    i=0;*/

    //Llenado del vector

    for(int row = 0; row < nCellsWidth; row++){
        for(int col = 0; col < nCellsHeight; col++){
            orden[i].col = col;
            orden[i].row = row;
            orden[i].valor = defaultCellValue(row, col, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses);
            i++;
        }
    }

    i=0;

    /*cronometro c2;
    long int r2 = 0;
    c2.activar();
    do{*/
        ordenacion_fusion(orden, i, j, N);

        i = 0;
        while(currentDefense != defenses.end() && i <= N){
            if(factibilidad(orden[i].row, orden[i].col, obstacles, defenses, mapWidth, mapHeight, nCellsWidth, nCellsHeight, (*currentDefense)->radio) == 1){
                pos = cellCenterToPosition (orden[i].row, orden[i].col, cellWidth, cellHeight);
                (*currentDefense)->position.x = pos.x;
                (*currentDefense)->position.y = pos.y;
                (*currentDefense)->position.z = 0;
                ++currentDefense;
            }
            i++;
        }
        /*++r2;
    }while(c2.tiempo() < e_abs / e_rel + e_abs);
    c2.parar();

    i = 0;
    j = N-1;

    //Llenado del vector
    for(int row = 0; row < nCellsWidth; row++){
        for(int col = 0; col < nCellsHeight; col++){
            orden[i].col = col;
            orden[i].row = row;
            orden[i].valor = defaultCellValue(row, col, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses);
            i++;
        }
    }

    i=0;

    cronometro c3;
    long int r3 = 0;
    c3.activar();
    do{
        ordenacion_rapida(orden, i, j, N);

        i = 0;
        while(currentDefense != defenses.end() && i <= N){
            if(factibilidad(orden[i].row, orden[i].col, obstacles, defenses, mapWidth, mapHeight, nCellsWidth, nCellsHeight, (*currentDefense)->radio) == 1){
                pos = cellCenterToPosition (orden[i].row, orden[i].col, cellWidth, cellHeight);
                (*currentDefense)->position.x = pos.x;
                (*currentDefense)->position.y = pos.y;
                (*currentDefense)->position.z = 0;
                ++currentDefense;
            }
            i++;
        }   
        ++r3;
    }while(c3.tiempo() < e_abs / e_rel + e_abs);
    c3.parar();

    i=0;

    //Llenado del vector
    for(int row = 0; row < nCellsWidth; row++){
        for(int col = 0; col < nCellsHeight; col++){
            orden[i].col = col;
            orden[i].row = row;
            orden[i].valor = defaultCellValue(row, col, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses);
            i++;
        }
    }

    cronometro c4;
    long int r4 = 0;
    c4.activar();
    do{
        std::vector<Ordenacion> ordenMon(orden,orden+N);

        std::make_heap (ordenMon.begin(),ordenMon.end(), criterio);
        std::sort_heap (ordenMon.begin(),ordenMon.end(), criterio);
        
        i = 0;
        while(currentDefense != defenses.end() && i <= N){
            if(factibilidad (ordenMon[i].row, ordenMon[i].col, obstacles, defenses, mapWidth, mapHeight, nCellsWidth, nCellsHeight, (*currentDefense)->radio) == 1){
                pos = cellCenterToPosition (ordenMon[i].row, ordenMon[i].col, cellWidth, cellHeight);
                (*currentDefense)->position.x = pos.x;
                (*currentDefense)->position.y = pos.y;
                (*currentDefense)->position.z = 0;
                ++currentDefense;
            }
            i++;
        } 
        ++r4;
    }while(c4.tiempo() < e_abs / e_rel + e_abs);
    c4.parar();
    std::cout << (nCellsWidth * nCellsHeight) << '\t' << c.tiempo() / r << '\t' << c2.tiempo() / r2 << '\t' << c3.tiempo() / r3 << '\t' << c4.tiempo() / r4 << std::endl;
    */
}

//ORDENACION FUSION

void ordenacion_fusion (Ordenacion orden[], int i, int j, int N){
    if (i<j){
        int k=(i+j)/2;
        ordenacion_fusion(orden, i, k, N);
        ordenacion_fusion(orden, k + 1, j, N);
        fusion(orden, i, k, j, N);
    }
}

void fusion(Ordenacion orden[], int i, int k, int j, int N){
    int n = j-i+1, p = i, q = k+1;
    Ordenacion aux[N];
    for (int a = 0; a <= n; a++){
        if (p <= k && (q > j || orden[p].valor >= orden[q].valor)){
            aux[a] = orden[p];
            p++;
        } else {
            aux[a] = orden[q];
            q++;
        }
    }
    for (int a = 0; a <= n; a++){
        orden[i+a]=aux[a];
    }
}

/*
//ORDENACION RAPIDA

void ordenacion_rapida (Ordenacion orden[], int i, int j, int N){
    if (i<j){
        int p = pivote(orden, i, j, N);
        ordenacion_rapida(orden, i, p-1, N);
        ordenacion_rapida(orden, p + 1, j, N);
    }
}

int pivote (Ordenacion orden[], int i, int j, int N){
	int p = i; 
    Ordenacion x = orden[i];
	for (int k= i+1; k<=j; k++){
		if (orden[k].valor>x.valor){
			p++;
			std::swap(orden[p], orden[k]);	
		}
	}
	orden[i]=orden[p];
	orden[p]=x;
	
	return p;
}

//MONTICULO

bool criterio(Ordenacion o, Ordenacion o2){
	return (o.valor > o2.valor);
}
*/