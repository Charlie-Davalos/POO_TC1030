/*
 * jugador.h
 *
 *  Created on: 10/Jun/2022
 *      Author: Carlos Davalos
 */

#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include "zombie.h" // clase zombie en biblioteca.h
using namespace std;

// Declaracion de Jugador que es clase abstracta
class Jugador{
//Declaracion de variables protected para usarlas en clases hijas
protected:
  int id;
  string username;
  int nivel;
  int vida;
  int num_ataques;

//Declaracion de metodos y constructor
public:
  Jugador(): id(0),username(""),nivel(0),vida(0),num_ataques(0){}; //constructor por defualt
  Jugador(int _id, string _username, int _nivel, int _vida, int _num_ataques);  //constructor

  int get_vidajug(){return vida;}
  void set_vida_jugador(int vid){vida=vid;};
  virtual int get_num_ataques(){return num_ataques;};
  virtual void muestra_atributos(); //polimorfismo
  virtual int usar_ataque(int, Zombie*,string) = 0;//funcion virtual pura (abstracta) será sobreescrita
  void grito_de_guerra();
  virtual string ataques(string)=0;
  virtual void recibe_danio(Zombie*);
};
//constructor
Jugador::Jugador(int _id, string _username, int _nivel, int _vida, int _num_ataques){
  id=_id;
  username=_username;
  nivel=_nivel;
  vida=_vida;
  num_ataques=_num_ataques;
}

/*
* recibe_danio permite que el zombie haga daño
* cuando el jugador se queda sin ataques
* recibe un apuntador tipo Zombie
* y a la vida del jugador le resta el daño del zombie
* Te da un ataque extra para poder ganarle al zombie
*/
void Jugador::recibe_danio(Zombie* zomb1){
    cout<<"te has quedado sin ataques! Turno del zombie:"<<endl;
    cout<<"   'CEREBROOOOO!!'   "<<endl;
    int vidajug;
    vidajug=vida-(zomb1->get_danioz());
    vida=vidajug; //nueva vida
    cout<<"---TE HAN HECHO "<<zomb1->get_danioz()<<" DE DAÑO!---\n";
    cout<<"\n";
    cout<< "Vida de "<<username<<": "<<vida<<endl;
    cout<<"Bonus! +1 Ataque!\n";
    num_ataques++;
}

/*
* muestra_atributos imprime los atributos de jugador
* como es virtual se comportar'a diferente en las hijas
*/
void Jugador::muestra_atributos(){
  cout << "Username: " << username << "\n";
  cout << "ID: " << id << "\n";
  cout << "Nivel: " << nivel<< "\n";
  cout << "Vida: " << vida << endl;
}

/*
* grito_de_guerra imprime una frase diferente en cada tipo de objeto
* (sobreescritura)
*/
void Jugador::grito_de_guerra(){
    cout<< "Hola!"<<endl;
}

//Declaracion objeto Guerrero que hereda de Jugador
class Guerrero : public Jugador{
private:
  int danioswing; //daño del swing de la espada
  int daniospin; //danio del spin de la espada
public:
    Guerrero():Jugador(0,"",0,0,0){}; //constructor por defualt
    //Constructor:
    Guerrero(int _id, string _username, int _nivel, int _vida=150, int _num_ataques=4,
        int _danioswing=10, int _daniospin=20):Jugador(_id, _username, _nivel, _vida, _num_ataques){
    danioswing = _danioswing;
    daniospin = _daniospin;
  }
    void muestra_atributos(); //polimorfismo
    int usar_ataque(int, Zombie*, string);
    void grito_de_guerra();
    string ataques(string username);
    int  get_num_ataques(){return num_ataques;};
};

/*
* muestra_atributos imprime los atributos de jugador (la manda a llamar)
* Además imprime los atributos de Guerrero
*/
void Guerrero::muestra_atributos(){
    Jugador::muestra_atributos(); //polimorfismo
    cout << "Ataques:" << endl;
    cout << "-Swing daño: "<< danioswing << endl;
    cout << "-Spin daño: " << daniospin << endl;
    cout << "Numero de Ataques: " << num_ataques<<endl;
}

/*
* ataques() es abstracta, por lo tanto es diferente en cada hija
* imprime los ataques disponibles
*/
string Guerrero::ataques(string username){
    cout<<"\n";
    return username + ", es tu turno, elige un ataque \n-Swing(1) \n-Spin(2)\n";
}

/*
* usar_ataque es abstracta y sirve para hacerle daño al zombie
* dependiendo el parametro que elija el usuario será el daño que se utilice
* toma la vida del zombie, le resta el daño elegido y la sobreescribe
* Se le resta un ataque al jugador cada vez que se mande a llamar
*/
int Guerrero::usar_ataque(int ataque, Zombie* zomb1, string username){
    int vidaZombie;
    int dani;
    if (ataque==1){
        dani=danioswing;
        cout<<username<<" USED SWING!\n"<<"---HICISTE 10 DE DAÑO!---\n"<<endl;
    }
    else if (ataque==2){
        dani=daniospin;
        cout<<username<<" USED SPIN!\n"<<"---HICISTE 20 DE DAÑO!---\n"<<endl;
    }
    vidaZombie=(zomb1->get_vidaZombie())-dani;//100-danio (vida pasada)
    if (vidaZombie<0){
        vidaZombie=0;
    }
    zomb1->set_vidaZombie(vidaZombie);//vidazombie=80 o 70
    cout << "vida zombie: " << zomb1->get_vidaZombie()<<endl;//imprime la nueva vida
    num_ataques=num_ataques-1;
    cout<<"Ataques Restantes: "<<num_ataques<<endl;
    cout<<"\n-----------------------\n";
    //delete zomb1;
    return(vidaZombie);
}

void Guerrero::grito_de_guerra(){
    cout<< "Por Narniaaaaaaaaa!!!!"<<endl;
}

//Declaracion objeto Arquero que hereda de Jugador
class Arquero : public Jugador{
private:
  int danioflecha; //danio de felchazo normal
  int danioflechafuego; //danio de flechazo de fuego
public:
    Arquero():Jugador(0,"",0,0,0){}; //constructor por defualt
    //Constructor:
    Arquero(int _id, string _username, int _nivel, int _vida=100, int _num_ataques=4,
      int _danioflecha=20, int _danioflechafuego=30):Jugador(_id, _username, _nivel, _vida, _num_ataques){
    danioflecha = _danioflecha;
    danioflechafuego = _danioflechafuego;
  }
  void grito_de_guerra();
  void muestra_atributos();
  int usar_ataque(int, Zombie*, string);
  string ataques(string username);
  int get_num_ataques(){return num_ataques;};
};

/*
* muestra_atributos es polimorfica
* imprime atributos de jugador y los de arquero
*/
void Arquero::muestra_atributos(){
    Jugador::muestra_atributos();
    cout << "Ataques:" << endl;
    cout << "-Flecha (normal) daño: "<< danioflecha << endl;
    cout << "-Flecha de Fuego daño: " << danioflechafuego << endl;
    cout << "Numero de Ataques: " << num_ataques<<endl;
}

/*
* ataques
*/
string Arquero::ataques(string username){
    cout<<"\n";
    return username + ", es tu turno, elige un ataque \n-Flechas(1) \n-Flechas de fuego(2)\n";
}

/*
* usar_ataque es abstracta y sirve para hacerle daño al zombie
*
* toma la vida del zombie, le resta el daño elegido y la sobreescribe
* Se le resta un ataque al jugador cada vez que se mande a llamar
*/
int Arquero::usar_ataque(int ataque, Zombie* zomb1, string username){
    int vidaZombie;
    int dani;
    if (ataque==1){
        dani=danioflecha;
        cout<<username<<" USED FLECHAS!\n"<<"---HICISTE 20 DE DAÑO!---\n"<<endl;
    }
    else if (ataque==2){
        dani=danioflechafuego;
        cout<<username<<" USED FLECHAS FUEGO!\n"<<"---HICISTE 30 DE DAÑO!---\n"<<endl;
    }
    vidaZombie=(zomb1->get_vidaZombie())-dani;//100-danio (vida pasada)
    if (vidaZombie<0){
        vidaZombie=0;
    }
    zomb1->set_vidaZombie(vidaZombie);//vidazombie=80 o 70
    cout << "vida zombie: " << zomb1->get_vidaZombie()<<endl;//imprime la nueva vida
    num_ataques=num_ataques-1;
    cout<<"Ataques Restantes: "<<num_ataques<<endl;
    cout<<"\n-----------------------\n";
    //delete zomb1;
    return(vidaZombie);
}

void Arquero::grito_de_guerra(){
    cout<< "Que lluevan flechas!!"<<endl;
}

#endif
    