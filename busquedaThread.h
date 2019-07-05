//
// Created by alejandro on 7/5/19.
//
#include <vector>
#include <thread>
#include <future>
#include <iostream>

#ifndef PC4_BUSQUEDATHREAD_H
#define PC4_BUSQUEDATHREAD_H

using namespace std;

template <typename T>
void buscarP(int start, int stop, vector<T>& items,promise<T> prms){
    T temp = items[0];
    for(int index = start; index<stop;index++){

        if (items[index]>temp){

            temp=items[index];

        }
    }
    prms.set_value(temp);

}

template <typename T>
T buscar(vector<T> miVector){


    T resultado;
    unsigned int NUM_THREADS;
    unsigned int start;
    unsigned int stop;

    NUM_THREADS = (miVector.size() < std::thread::hardware_concurrency())?miVector.size():std::thread::hardware_concurrency();

    std::vector<std::future<T>> ftrs;
    std::vector<std::promise<T>> prms(NUM_THREADS);
    std::vector<std::thread> hilos;

    int extra = miVector.size()%NUM_THREADS;

    for(int i = 0;i<NUM_THREADS;i++) {

        start = miVector.size()*i/NUM_THREADS;


        if(i<extra) {
            stop = start + miVector.size()/NUM_THREADS + 1;
        }else{
            stop = start + (miVector.size() / NUM_THREADS);
        }


        ftrs.emplace_back(prms[i].get_future());

        hilos.emplace_back(buscarP<T>, start, stop, ref(miVector), move(prms[i]));

    }

    for(auto& i:hilos){
        i.join();
    }

    T temp;
    for(auto i = 0;i < ftrs.size(); ++i){
        if(i==0){
            resultado=ftrs[i].get();
        }
        else{
            temp = ftrs[i].get();
            if(resultado<temp){
                resultado=temp;
            }
        }

    }


    return resultado;
}
#endif //PC4_BUSQUEDATHREAD_H
