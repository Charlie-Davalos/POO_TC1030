/*
 * zombie.h
 *
 *  Created on: 10/Jun/2022
 *      Author: Carlos Davalos
 */

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
using namespace std;

class Zombie{

//variables del objeto
private:
  int vida;
  int danioz;

//funciones
public:
  Zombie(int vid=100,int dan=10){
    vida=vid;
    danioz=dan;
}
  int get_vidaZombie();
  void set_vidaZombie(int);
  int get_danioz(){return danioz;}
  void set_danioz(int dan){danioz=dan;}
};




//devuelve la vida del zombie
int Zombie::get_vidaZombie(){
    return vida;
}

//le da un nuevo valor a la vida del zombie
void Zombie::set_vidaZombie(int vid){
    vida=vid;
}

#endif