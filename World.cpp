//
//  World.cpp
//  
//
//  Created by Antoni Garí Romagosa on 14/11/15.
//
//

#include "World.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

World::World() {
    //LIST OF ITEMS
    //Keys
    Item mansionKeys = Item(1, "llavero", "Manojo de llaves de la mansión", "Una colección de llaves de toda la mansión. Otorgada por Maurice Van Laaden");
    //Utilities
    Item matches = Item(10, "cerillas", "Una caja de cerillas", "Parece que esten algo deteriorados");
    Item shovel = Item(11, "pala", "Pala de jardineria", "Una vieja pala oxidada con restos de manchas marrones en el extremo");
    //Information
    Item book1 = Item(30, "libro1", "Diario personal polvoriento", "Titulado: Los viajes y diarios de Brandon Van Laaden\nEncuadernado en cuero de aspecto muy caram e impreso en papel de alto gramaje.");
    
    
    //LOCALIZATIONS
    //Verja
    puertaHierro.set("Puerta de hierro", "La puerta de hierro de la verja, de unos 2,4m de altura, está completamente oxidada pero encierra los misterios de la finca de la mansión");
    puertaHierro.setDirection('n',&estatua);
    puertaHierro.addItem(shovel);

    //Estatua
    estatua.set("Estatua del marino", "Una figura de mármol, de pie sobre un pequeño pedestal y representa a un hombre vestido con el atuendo tipico de los marinos de Nueva Inglaterra. Sus manos aferran un timón y a sus pies hay un áncora.\nUna gastada inscripción en el pedestal reza: \"Nuestro padre, Erich Van Laaden, 1762-1848\"");
    estatua.setDirection('s',&puertaHierro);
    estatua.setDirection('n',&puertaCasa);

    //Puerta de la casa
    puertaCasa.set("Porche", "Estás en el porche. Frente tuyo hay una enorme puerta de doble hoja, de roble. Tiene un aspecto imponente");
    puertaCasa.setDirection('s',&estatua);
    puertaCasa.setDirection('n',&recibidor);
    
    //Recibidor
    recibidor.set("Recibidor", "Estás en la entrada de la casa. Por todas partes no hay sino capas de polvo y grandes telarañas, que cruzan arcadas y cuelgan de lámparas y muebles. Te llega un tremendo olor a cerrado que impregna toda la estructura, un olor rancio que contiene una empalagosa humedad poco natural. Frente tuyo hay una escalinata de madera pulida que lleva hacia arriba. A uno y otro lado del recibidor se abren arcadas a través de las que podéis ver otras habitaciones, decoradas con muebles y cuadros.");
    recibidor.setDirection('u',&primerPiso);
    recibidor.setDirection('w',&salon);
    recibidor.setDirection('e',&salita);

    //Salon
    salon.set("Salón","Lo primero que se ve aquí es la chimenea central que domina la pared Oeste, donde caben troncos de hasta 1,80m de longitud, y donde un hombre normal podría andar por el interior casi sin agacharse. El paramento es de una sola pieza de madera trabajada a mano, de color completamente negro, y sobre la que hay cierta cantidad de pequeños objetos, en la misma madera. Las paredes están paneladas hasta media altura en madera pintada de blanco, y a partir de allí están empapeladas con motivos florales desvaídos, con zonas que empiezan a pelarse.\nEl suelo está cubierto casi por completo por varias alfombras de gran tamaño, y de las paredes cuelgan multitud de retratos al óleo, destacando especialmente el mayor de todos, que es un paisaje de otoño situado encima de la chimenea. Hay dos grupos principales de muebles, uno a cada lado de la habitación, dominado cada uno de ellos por un enorme sofá, e incluyendo cierto numero de sillas más pequeñas y mesas. Un gran piano vertical se encuentra junto a la chimenea, y por el resto de la habitación hay diversas sillas. En las mesas hay una serie de lámparas, y otras cuelgan de las paredes.");
    salon.setDirection('e',&recibidor);
    
    //Salita
    salita.set("Salita","");
    salita.setDirection('w',&recibidor);
    
    //Primer piso
    primerPiso.set("Primer piso","");
    primerPiso.setDirection('d',&recibidor);

   
    //Player stats
    this->finished = false;
    actual = &puertaHierro;
    items.push_back(mansionKeys);
}

void World::action(string sentence) {
    string copySentence = sentence;
    int position = copySentence.find(' ');
    string verb = copySentence.substr(0,position);
    transform(verb.begin(), verb.end(), verb.begin(), ::tolower);

    copySentence = copySentence.substr(position + 1, copySentence.length());
    position = copySentence.find(' ');
    string argument = copySentence.substr(0,position);
    transform(argument.begin(), argument.end(), argument.begin(), ::tolower);
    
    if (verb == "go") {
        if ((argument == "north")||(argument == "n")||(argument == "west")||(argument == "w")||(argument == "south")||(argument == "s")||(argument == "east")||(argument == "e")||(argument == "up")||(argument == "u")||(argument == "down")||(argument == "d")) {
            
            Area *aux = actual->goArea(argument.at(0)); //First character
            if (aux != NULL) {
                actual = aux;
                actualArea();
            } else {
                cout << "No se puede ir en esa dirección" << endl;
            }
        } else {
            cout << "No es una dirección valida" << endl;
        }
        
    } else if ((verb == "inventory") || (verb == "i")) {
        list<Item>::iterator i;
        cout << "En tu inventario tienes: " << endl;
        for (i = items.begin(); i != items.end(); ++i) {
            cout << i->getName() << " [" << i->getShortName() << "]" << endl;
        }
        
    } else if ((verb == "take") || (verb == "pick")) {
        Item itemAux = actual->getItem(argument);
        if (itemAux.getId() != 0) {
            cout << "Has cogido: " << itemAux.getName() << endl;
            items.push_back(itemAux);
            actual->deleteItem(itemAux.getId());
        }
        
    } else if (verb == "drop") {
        list<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i) {
            if(i->getShortName() == argument) {
                cout << "Has tirado: " << i->getName() << endl;
                
                //Add item to the Area
                Item aux = Item();
                aux = Item(i->getId(), i->getShortName(), i->getName(), i->getDescription());
                actual->addItem(aux);
                
                //Erase item from your inventory
                items.erase(i);
            } else cout << "No tienes esto en tu inventario" << endl;
        }
    } else if (verb == "investigate") {
        Item itemAux = actual->getItem(argument);
        if (itemAux.getId() != 0) {
            cout << "Observas con detenimiento " << itemAux.getName() << endl;
            cout << itemAux.getDescription() << endl;
        }
        
    } else if (verb == "observe") {
        list<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i) {
            if(i->getShortName() == argument) {
                cout << "Observas con detenimiento " << i->getName() << endl;
                cout << i->getDescription() << endl;
            }
            else cout << "No tienes esto en tu inventario" << endl;
        }
    
    } else if (sentence == "where i am"){
        cout << "Te encuentras en: ";
        actualArea();
    
    } else if (sentence == "help") {
        cout << "Las ordenes que puedes usar son: " << endl;
        cout << ">go [direction]: Para ir en una determinada dirección" << endl;
        cout << ">take [item]: Te permite coger un objeto de una habitación" << endl;
        cout << ">drop [item]: Te permite soltar un objeto en una habitación" << endl;
        cout << ">investigate [item]: Para observar algo del escenario" << endl;
        cout << ">observe [item]: Para observar un item en tu invetario" << endl;
        cout << ">inventory: Puedes listar las cosas que llevas encima" << endl;
        cout << ">where i am: Te recuerda en que habitación te encuentras" << endl;
        cout << ">escape: Decides que ya tienes suficiente información sobre deshacer el embrujo y te marchas a contarle al señor Maurice como hay que hacerlo" << endl;
        
    } else if ((sentence == "end") || (sentence == "escape")) {
        finished = true;
    
    } else {
        cout << "No es una orden valida" << endl;
    }
}

void World::actualArea() {
    actual->printArea();
}


bool World::isFinished() {
    return finished;
}

void World::introduction() {
    cout << "Te llamas Vincent Coleman, eres un investigador privado de Arkham.\n\nAunque antaño tenias mucho trabajo, ultimamente no te llegan casi casos.\n\nUn dia en tu oficina, mientras ojeas la revista Occult Review, encuentras un artículo titulado Casas encantada de Ohio y Michigan, escrito por Arthur Lampkin de Toledo (Ohío).\n\nEl artículo cita seis casas diferentes, todas ellas con reputación de estar encantadas, señalando los hallazgos del autor. Una de ellas, situada cerca de Grand Rapids (Michigan), propiedad de un tal Maurice Van Laaden, tiene más de cien años de antiguedad y lleva encantada tanto tiempo como el actual propietario puede recordar.\n\nMaurice desea vender la casa y los muebles pero le ha sido imposible debido a la nefasta reputación de ésta y por esto ha ofrecido un 10% del precio de venta como recompensa a la persona capaz de exorcizar el edificio. El edificio consta de planta y dos pisos y pertenece a un estilo muy común en Nueva Inglaterra y está repleta de antiguedades caras y objetos de arte que reportarían excelentes beneficios.\n\nFacilmente contactas con el editor del artículo y a través de él con Maurice Van Laaden en Grand Rapids\n\nDespues de formalizar los tramites para concretar el trabajo, Maurice Van Laaden te lleva hasta la casa. Viajando hacia el norte desde Grand Rapids, por la carretera estatal, Maurice empieza a aminorar la velocidad, como si no estuviera seguro de dónde está. Tras conducir así durante unos doscientos metros, gira a la izquierda y toma con cuidado un camino de tierra estrecho y lleno de rodadas, por el que apenas podrían cruzarse dos coches y que avanza serpenteando colina arriba, a través de un terreno al que dieron forma antiguos glaciares. Los altísimos robles y arces forman un arco sobre el camino, tapando el sol, y se nota una fuerte humedad\n\nMaurice aminora la velocidad hasta casi detenerse al llegar a una zona particularmente baja, en la que el agua de una reciente tormenta ha formado un estanque cenagoso que cruza el paso. El coche parece como si fuera a rascar el suelo mientras Maurice conduce lentamente a través de los baches que tapa el charco, hasta que al final gira lentamente a la izquierda y vuelve a terreno seco al mismo tiempo que aparece a la vista la mansión Van Laaden.\n\nRecortada contra el cielo gris, la mansión, que consta de planta y dos pisos, se agazapa tras una verja de hierro rodeada por árboles muertos y moribundos, y de la que los últimos restos de pintura cayeron, arrastrados por los duros inviernos de Michigan, hace ya años. Tiene los postigos cerrados ante el mundo exterior y el poco acogedor camino hasta la puerta principal está lleno de hierba alta. En profundo contraste, la estatua de mármol blanco que representa a un viejo marino, completo con timón y áncora, se alza a medio camino entre la vieja casa y la oxidada verja de hierro qye rodea la propiedad. \n\nMaurice te ofrece las llaves de la mansión y se despide.\n\n";
    
}
    
void World::end() {
    cout << "FIN" << endl;
}