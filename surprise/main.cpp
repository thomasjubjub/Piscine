#include "grman/grman.h"
#include <iostream>

#include "Graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets Ecosystemeiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de Ecosystemee
    //Ecosysteme g;
    int demande;

    /// On declare notre ecosysteme
    Ecosysteme eco1;


    ///demande à l'utilisateur l'ecosysteme qu'il souhaite
//    std::cout<<"Choisissez le systeme 1, 2 ou 3"<<std::endl;
//    std::cin>>demande;


    std::string nom_syst="Eco1";
    eco1.Charger_Fichier(nom_syst);
    eco1.charger_coords("sauvegarde3.txt");
    eco1.Ajouter_Espece();
    //eco1.Supprimer_Espece();
    eco1.ecosysteme1();
    std::string nomfichier="matriceadj1";
    std::vector<int>c(6,0);
    //eco1.Recherche_forte_connexite(nomfichier, c);
    eco1.Recherche_toutes_CFC(nomfichier, c);

   // eco1.sauvegarde_coords("sauvegarde.txt");

//    eco1.sauvegarde_coords("sauvegarde.txt");
//    eco1.Sauvegarder_Fichier("Eco1.txt");



//
//    else if(demande==2)
//        {
//    std::string nom_syst="Eco2";
//    eco1.Charger_Fichier(nom_syst);
//    eco1.ecosysteme1();
//        }
//
//    else if(demande==3)
//        {
//    std::string nom_syst="Eco3";
//    eco1.Charger_Fichier(nom_syst);
//    eco1.ecosysteme1();
//        }






//    eco1.Ajouter_Espece();
//    eco1.Supprimer_Espece();
//
//    eco1.sauvegarde_coords();
//    eco1.Sauvegarder_Fichier();
//    eco1.Affichage_ecosyst();







    while ( !key[KEY_ESC] )
    {

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets

        eco1.update();


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

    }


//    std::cout<<"quel Ecosystemee ?";
//    std::cin>>demande;
//    if(demande==1)
  //  g.make_example2();
//
//    else if (demande==2)
//        g.make_example2();

//    /// Vous gardez la main sur la "boucle de jeu"
//    /// ( contrairement à des frameworks plus avancés )
//    while ( !key[KEY_ESC] )
//    {
//        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
//        g.update();
//
//        /// Mise à jour générale (clavier/souris/buffer etc...)
//        grman::mettre_a_jour();
//
//    }

    grman::fermer_allegro();



    return 0;
}
END_OF_MAIN();


