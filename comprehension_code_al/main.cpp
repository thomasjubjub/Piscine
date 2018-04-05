#include "grman/grman.h"
#include <iostream>

#include "Graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets Ecosystemeiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de Ecosystemee
    Ecosysteme g;
    int demande;

//    std::cout<<"quel Ecosystemee ?";
//    std::cin>>demande;
//    if(demande==1)
    g.make_example2();
//
//    else if (demande==2)
//        g.make_example2();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


