#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#ifndef CATCH_CONFIG_MAIN
#define UNIT_TEST

using namespace std;

template <typename T>
void buscarP(T item, int start, int stop, vector<T>& items,promise<int> prms){
    for(int index = start; index<stop;index++){
        if (items[index]==item){
            prms.set_value(index);
            break;
        }
        if(index==stop-1){
            prms.set_value(-1);
        }

    }

}

template <typename T>
int buscar(vector<T> miVector, T busqueda){


    int resultado;
    unsigned int NUM_THREADS;


    NUM_THREADS = (miVector.size()<std::thread::hardware_concurrency())?miVector.size():std::thread::hardware_concurrency();

    std::vector<std::future<int>> ftrs;
    std::vector<std::promise<int>> prms(NUM_THREADS);
    std::vector<std::thread> hilos;


    for(int i = 0;i<NUM_THREADS;i++) {

        ftrs.emplace_back(prms[i].get_future());

        hilos.emplace_back(buscarP<int>, busqueda, miVector.size()*i/NUM_THREADS, (miVector.size()/NUM_THREADS)*(i+1), ref(miVector), move(prms[i]));

    }

    for(auto& i:hilos){
        i.join();
    }

    for(auto& i: ftrs){
        resultado = i.get();
        if(resultado>=0){
            cout<<"Encontrado.\n";
            break;
        }

    }


    return resultado;
}


int main() {

//    int busqueda;
//    int resultado;
//    unsigned int NUM_THREADS;
//
//
//
//    NUM_THREADS = (miVector.size()<std::thread::hardware_concurrency())?miVector.size():std::thread::hardware_concurrency();
//
//    std::vector<std::future<int>> ftrs;
//    std::vector<std::promise<int>> prms(NUM_THREADS);
//    std::vector<std::thread> hilos;
//
//
//    cin>>busqueda;
//
//    for(int i = 0;i<NUM_THREADS;i++) {
//
//        ftrs.emplace_back(prms[i].get_future());
//
//        hilos.emplace_back(buscarP<int>, busqueda, miVector.size()*i/NUM_THREADS, (miVector.size()/NUM_THREADS)*(i+1), ref(miVector), move(prms[i]));
//
//    }
//
//    for(auto& i:hilos){
//        i.join();
//    }
//
//    for(auto& i: ftrs){
//        resultado = i.get();
//        if(resultado>=0){
//            cout<<"Encontrado.\n";
//            break;
//        }
//
//    }
//
//
//    cout<<resultado;


//    vector<int> miVector = {1,2,3,4,5,6,7,8};
//    cout<<buscar(miVector,4);
//
//
//    return 0;
}

#endif