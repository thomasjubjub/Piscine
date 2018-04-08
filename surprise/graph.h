#ifndef Ecosysteme_H_INCLUDED
#define Ecosysteme_H_INCLUDED
#include <vector>

/**************************************************************
    Ici sont proposées 3 classes fondamentales
            Espece (=Sommet)
            Influence (=Arête ou Arc)
            Ecosysteme (=Ecosystemee)

    Les arêtes et les sommets et le Ecosystemee qu'ils constituent
    "travaillent" étroitement ensemble : pour cette raison les
    Espece et Influence se déclarent amis (friend) de Ecosysteme pour que
    ce dernier puisse librement accéder aux membres (y compris
    protected ou private) de Espece et Influence.

    Ces Classes peuvent êtres complétées. Il est également possible
    de les dériver mais il est malheureusement assez difficile
    de dériver le "triplet" des 3 classes en maintenant des relations
    cohérentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute préférable, si possible,
    de "customiser" ces classes de base directement, sans héritage.

    Le modèle proposé permet de représenter un Ecosystemee orienté éventuellement
    pondéré, les arcs portent une ou des informations supplémentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du Ecosystemee puisse être assez facilement
    lue et écrite en fichier, et bénéficie d'une bonne lisibilité en cas de bugs...

    Chaque arc possède 2 attributs principaux (en plus de son éventuelle pondération)
        -> m_e1 (indice du sommet de départ de l'arc )
        -> m_to (indice du sommet d'arrivée de l'arc )

    Chaque sommet possède 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : accès aux prédécesseurs)
        -> m_out (liste des indices des arcs partant du sommet : accès aux successeurs)

    Cependant le problème des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entité (un arc et/ou un sommet sont enlevés du Ecosystemee) alors :

    - Soit il faut reprendre toute la numérotation pour "boucher le trou"
      (par exemple on a supprimé le sommet n°4, le sommet n°5 devient le 4, 6 devient 5 etc...)
      ce qui pose des problèmes de stabilité et de cohérence, et une difficulté à ré-introduire
      le(s) même(s) élément supprimé (au même indice)

    - Soit on admet que la numérotation des sommets et arcs n'est pas contigue, càd qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La numérotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet à des indices arbitraires (pas forcément contigus)

    C'est cette 2ème approche qui est proposée ici : dans la classe Ecosystemee vous trouverez
        -> map<int, Influence>   m_Influences
        -> map<int, Espece> m_Espece    (le pluriel de Espece est vertices)

    Il faudra être attentif au fait que par rapport à un simple vecteur, le parcours des éléments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_Influences.size(); ++i) ...m_Influences[i]...
    et que les parcours à itérateur ne donneront pas directement des Influence ou des Espece
    mais des pairs, l'objet d'intérêt se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_Influences.begin(); it!=m_Influences.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_Influences) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associée à chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des Ecosystemees non représentés à l'écran
    Imaginons par exemple qu'on doive générer 1000 permutations de Ecosystemees pour tester des
    combinaisons, on ne souhaite pas représenter Ecosystemeiquement ces 1000 Ecosystemees, et les
    interfaces pèsent lourd en ressource, avec cette organisation on est libre de réserver ou
    pas une interface de présentation associée aux datas (découplage données/interface)

***********************************************************************************************/

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "grman/grman.h"
#include "grman/widget.h"

/***************************************************
                    Espece
****************************************************/

class EspeceInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Espece;
    friend class InfluenceInterface;
    friend class Ecosysteme;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        ///mettre attributs AL

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // Un slider de visualisation/modification de la valeur du sommet
        grman::WidgetVSlider m_slider_value; ///modif nombre d'individus

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value; ///nombre d'individus

        // Une image de "remplissage"
        grman::WidgetImage m_img;

        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        // Une boite pour le label précédent
        grman::WidgetText m_box_label_idx;

        // Un label indiquant le blaz du sommet
        grman::WidgetText m_label_blaz;

        // Une boite pour le label précédent
        grman::WidgetText m_box_label_blaz;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        EspeceInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Espece
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Ecosysteme;
    friend class EspeceInterface;
    friend class Influence;
    friend class InfluenceInterface;

    private :
        /// liste des indices des arcs arrivant au sommet : accès aux prédécesseurs
       // std::vector<int> m_in;


        /// liste des indices des arcs partant du sommet : accès aux successeurs
       // std::vector<int> m_out;

    std::string m_nom;
    int m_K; //nombre maximum
    int m_N; //nombre actuel
    float m_r; //rythme de croissance
    int m_posX;
    int m_posY;
    std:: string m_pic_name;
    bool marque=false;
    int successeur=0;
    int predecesseur=0;

        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...
       // double m_N;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<EspeceInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne précédente est en gros équivalent à la ligne suivante :
        // EspeceInterface * m_interface = nullptr;


    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Espece (int N, EspeceInterface *interface=nullptr) :
            m_N(N), m_interface(interface)  {  }

        ///Constructeurs/Destructeurs
        Espece();
        ~Espece();
        Espece(std:: string nom, int N, float r, int K, EspeceInterface *interface=nullptr):
            m_N(N), m_nom(nom), m_r (r), m_K(K), m_interface (interface) {}

        std::string getnom(){return m_nom;};
        int getN(){return m_N;};
        float getr(){return m_r;};
        int getK(){return m_K;};

        /// Espece étant géré par Ecosysteme ce sera la méthode update de Ecosysteme qui appellera
        /// le pre_update et post_update de Espece (pas directement la boucle de jeu)
        /// Voir l'implémentation Ecosysteme::update dans le .cpp
        void pre_update();
        void post_update();
};



/***************************************************
                    Influence
****************************************************/

class InfluenceInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Influence;
    friend class Ecosysteme;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // Le WidgetInfluence qui "contient" toute l'interface d'un arc
        grman::WidgetInfluence m_top_Influence;

        // Une boite pour englober les widgets de réglage associés
        grman::WidgetBox m_box_Influence;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_coefficient;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_coefficient;



    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        InfluenceInterface(Espece& from, Espece& to);

};


class Influence
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Ecosysteme;
    friend class InfluenceInterface;

    private :
        /// indice du sommet de départ de l'arc
        int m_e1; //m_from

        /// indice du sommet d'arrivée de l'arc
        int m_e2; //m_to
//
//        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...
//        double m_weight;

        //coefficient d'influence
        float m_coefficient;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<InfluenceInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Influence (float coefficient=0, InfluenceInterface *interface=nullptr) :
            m_coefficient(coefficient), m_interface(interface)  {  }



        /// Influence étant géré par Ecosysteme ce sera la méthode update de Ecosysteme qui appellera
        /// le pre_update et post_update de Influence (pas directement la boucle de jeu)
        /// Voir l'implémentation Ecosysteme::update dans le .cpp
        void pre_update();
        void post_update();

        //Influence();
        ~Influence();
        Influence(int e1, int e2, float coef);
};




/***************************************************
                    Ecosysteme
****************************************************/

class EcosystemeInterface
{
    friend class Ecosysteme;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un Ecosystemee
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajoutés les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajoutés des boutons de contrôle etc...
        grman::WidgetBox m_tool_box;

        ///Bouton supprimer
        grman::WidgetCheckBox m_box_supprimer;

        ///Texte bouton supprimer
        grman::WidgetText m_text_supprimer;

        ///Bouton ajouter
        grman::WidgetCheckBox m_box_ajouter;

        ///texte bouton ajouter
        grman::WidgetText m_text_ajouter;


        // A compléter éventuellement par des widgets de décoration ou
        // d'édition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        EcosystemeInterface(int x, int y, int w, int h);




};


class Ecosysteme
{


    private :

        std::vector<Influence*> vecInfluence;
        std::vector<Espece*>vecEspece;
        int m_nombre_espece;
        int m_nombre_influence;

        /// La "liste" des arêtes
        std::map<int, Influence> m_Influences;

        /// La liste des sommets
        std::map<int, Espece> m_Espece;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<EcosystemeInterface> m_interface = nullptr;




    public:
        //Ecosysteme();
        ~Ecosysteme();
        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Ecosysteme (EcosystemeInterface *interface=nullptr) :
            m_interface(interface)  {  }


        void Charger_Fichier(std::string nom_fichier);
        void Sauvegarder_Fichier( std::string nom_fichier);


        void Affichage_ecosyst();
        void ecosysteme1();

        void Supprimer_Espece ();
        void Ajouter_Espece ();

        std::vector<int> Recherche_forte_connexite(std::string nomfichier, std::vector<int>c, int sommet);
        std::vector<std::vector<int>> Recherche_toutes_CFC(std::string nomfichier, std::vector<int>c);



        void sauvegarde_coords(std::string blaz);
        void charger_coords(std:: string blaz);

        void add_interfaced_Espece(int idx, int value, int x, int y, std::string pic_name="", int pic_idx=0 );
        void add_interfaced_Influence(int idx, int vert1, int vert2, float weight);

        /// Méthode spéciale qui construit un Ecosystemee arbitraire (démo)
        /// Voir implémentation dans le .cpp
        /// Cette méthode est à enlever et remplacer par un système
        /// de chargement de fichiers par exemple.
        void make_example();
        void make_example2();


        /// La méthode update à appeler dans la boucle de jeu pour les Ecosystemees avec interface
        void update();
};


#endif // Ecosysteme_H_INCLUDED
