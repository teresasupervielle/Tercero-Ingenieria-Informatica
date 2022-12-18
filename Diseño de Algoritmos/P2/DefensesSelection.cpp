// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

using namespace Asedio;

float valor (Defense* defensa){return(defensa->damage/defensa->attacksPerSecond)*defensa->dispersion;}

void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, std::list<int> &selectedIDs, float mapWidth, float mapHeight, std::list<Object*> obstacles) {

    int defensas=defenses.size()-1, i=0, j=0;

    //comprar la primera defensa (defensa 0)
    std::list<Defense*>::iterator it = defenses.begin();
    selectedIDs.push_back((*it)->id);
    ases-=(*it)->cost;
    ++it;

    float** tabla = new float* [defensas];//tabla(defensas x ases) para TSR
    for(i = 0; i < defensas; ++i)
       tabla[i] = new float[ases];
    
    int* coste = new int [defensas]; //vector(defensas) para costes

    for (i=0; i<defensas; i++){
        coste[i]=(*it)->cost;
        ++it;
    } //rellenar vector sin la defensa 0  

    it=defenses.begin();
    ++it;

    //rellenar tabla TSR
    for (j=0; j<ases; j++){
        if (j<coste[0])
            tabla[0][j] = 0;
        else
            tabla[0][j] = valor((*it));
    }

    ++it;

    for (i=1; i<defensas; i++){
        for (j=0; j<ases; j++){
            if(j<coste[i])
                tabla[i][j]=tabla[i-1][j];
            else
                tabla[i][j]=std::max(tabla[i-1][j], (tabla[i-1][j-coste[i]]+valor((*it))));
        }
        ++it;
    }
    
    //busqueda de solucion
    j--;

    for(i = defensas-1; i>0; i--){
        if(tabla[i][j] != tabla[i-1][j]){
            selectedIDs.push_back(i+1);
            j -= coste[i];
        }
    }

    if(i == 0 && coste[i] <= j){
        selectedIDs.push_back(i+1);
        j -= coste[i];
    }
}

