#include <iostream> //biblioteca para cin/cout
#include "jugador.h" //clase jugador en biblioteca .h
using namespace std;

int main() {
  int opcion;
  string username;
  int id;
  int clase;
  Zombie *zomb1 = new Zombie();
//Menu inicial que se mostrara a jugador 
  cout << "===== Bienvenido =====" << endl;
  cout << "-Jugar(1)" << endl;
  cout << "-Salir(2)" << endl;
  cout<< "-->";
  cin >> opcion;

  while(opcion!=1 and opcion!=2){
    cout<<"Por favor ingrese 1 o 2: ";
    cin >> opcion;
  }
  if (opcion==1){
    cout<<"Ingrese su Username: ";
    cin>>username;
    cout<<"Ingrese su ID: ";
    cin>>id;
    cout<<"Elija su tipo de jugador \n-Guerrero(1)";
    cout<<"-->";
    cin>>clase;
    cout<<"\n";
    while(clase!=1 and clase!=2){
        cout<<"Por favor ingrese 1 o 2: ";
        cin >> clase;
    }
    cout<<"========================\n";

    Jugador* jug1;
    if (clase==1){
        jug1 = new Guerrero(id, username, 1);
    }

    cout<<"========== Empieza el juego! =========="<<endl;
    cout<<"== Aparecieron Zombies! Destruyelos =="<<endl;

    while ((zomb1->get_vidaZombie())>0 && (jug1->get_num_ataques())>0){
        cout << jug1->ataques(username);
        cout<<"-->";
        int ataque;
        cin>>ataque;
        while(ataque!=1 and ataque!=2){
          cout<<"Por favor ingrese 1 o 2: ";
          cin >> ataque;
        }
        cout<<"\n";
        jug1->usar_ataque(ataque,zomb1,username);
        while ((jug1->get_num_ataques())==0 && (zomb1->get_vidaZombie())>0){
            jug1->recibe_danio(zomb1);
        }
    }

    cout<<"\nHas eliminado a los zombies! Bien hecho!"<<"\n";

  }
  else if (opcion==2){
    void exit();
  }
  return 0;
}

