#ifndef Ecosysteme_H_INCLUDED
#define Ecosysteme_H_INCLUDED
#include <vector>

/**************************************************************
    Ici sont propos�es 3 classes fondamentales
            Espece (=Sommet)
            Influence (=Ar�te ou Arc)
            Ecosysteme (=Ecosystemee)

    Les ar�tes et les sommets et le Ecosystemee qu'ils constituent
    "travaillent" �troitement ensemble : pour cette raison les
    Espece et Influence se d�clarent amis (friend) de Ecosysteme pour que
    ce dernier puisse librement acc�der aux membres (y compris
    protected ou private) de Espece et Influence.

    Ces Classes peuvent �tres compl�t�es. Il est �galement possible
    de les d�river mais il est malheureusement assez difficile
    de d�river le "triplet" des 3 classes en maintenant des relations
    coh�rentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute pr�f�rable, si possible,
    de "customiser" ces classes de base directement, sans h�ritage.

    Le mod�le propos� permet de repr�senter un Ecosystemee orient� �ventuellement
    pond�r�, les arcs portent une ou des informations suppl�mentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du Ecosystemee puisse �tre assez facilement
    lue et �crite en fichier, et b�n�ficie d'une bonne lisibilit� en cas de bugs...

    Chaque arc poss�de 2 attributs principaux (en plus de son �ventuelle pond�ration)
        -> m_e1 (indice du sommet de d�part de l'arc )
        -> m_to (indice du sommet d'arriv�e de l'arc )

    Chaque sommet poss�de 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs)
        -> m_out (liste des indices des arcs partant du sommet : acc�s aux successeurs)

    Cependant le probl�me des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entit� (un arc et/ou un sommet sont enlev�s du Ecosystemee) alors :

    - Soit il faut reprendre toute la num�rotation pour "boucher le trou"
      (par exemple on a supprim� le sommet n�4, le sommet n�5 devient le 4, 6 devient 5 etc...)
      ce qui pose des probl�mes de stabilit� et de coh�rence, et une difficult� � r�-introduire
      le(s) m�me(s) �l�ment supprim� (au m�me indice)

    - Soit on admet que la num�rotation des sommets et arcs n'est pas contigue, c�d qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La num�rotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet � des indices arbitraires (pas forc�ment contigus)

    C'est cette 2�me approche qui est propos�e ici : dans la classe Ecosystemee vous trouverez
        -> map<int, Influence>   m_Influences
        -> map<int, Espece> m_Espece    (le pluriel de Espece est vertices)

    Il faudra �tre attentif au fait que par rapport � un simple vecteur, le parcours des �l�ments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_Influences.size(); ++i) ...m_Influences[i]...
    et que les parcours � it�rateur ne donneront pas directement des Influence ou des Espece
    mais des pairs, l'objet d'int�r�t se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_Influences.begin(); it!=m_Influences.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_Influences) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associ�e � chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des Ecosystemees non repr�sent�s � l'�cran
    Imaginons par exemple qu'on doive g�n�rer 1000 permutations de Ecosystemees pour tester des
    combinaisons, on ne souhaite pas repr�senter Ecosystemeiquement ces 1000 Ecosystemees, et les
    interfaces p�sent lourd en ressource, avec cette organisation on est libre de r�server ou
    pas une interface de pr�sentation associ�e aux datas (d�couplage donn�es/interface)

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
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Espece;
    friend class InfluenceInterface;
    friend class Ecosysteme;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

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

        // Une boite pour le label pr�c�dent
        grman::WidgetText m_box_label_idx;

        // Un label indiquant le blaz du sommet
        grman::WidgetText m_label_blaz;

        // Une boite pour le label pr�c�dent
        grman::WidgetText m_box_label_blaz;

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        EspeceInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Espece
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Ecosysteme;
    friend class EspeceInterface;
    friend class Influence;
    friend class InfluenceInterface;

    private :
        /// liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs
       // std::vector<int> m_in;


        /// liste des indices des arcs partant du sommet : acc�s aux successeurs
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

        /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
       // double m_N;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<EspeceInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne pr�c�dente est en gros �quivalent � la ligne suivante :
        // EspeceInterface * m_interface = nullptr;


    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
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

        /// Espece �tant g�r� par Ecosysteme ce sera la m�thode update de Ecosysteme qui appellera
        /// le pre_update et post_update de Espece (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Ecosysteme::update dans le .cpp
        void pre_update();
        void post_update();
};



/***************************************************
                    Influence
****************************************************/

class InfluenceInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Influence;
    friend class Ecosysteme;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        // Le WidgetInfluence qui "contient" toute l'interface d'un arc
        grman::WidgetInfluence m_top_Influence;

        // Une boite pour englober les widgets de r�glage associ�s
        grman::WidgetBox m_box_Influence;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_coefficient;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_coefficient;



    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        InfluenceInterface(Espece& from, Espece& to);

};


class Influence
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Ecosysteme;
    friend class InfluenceInterface;

    private :
        /// indice du sommet de d�part de l'arc
        int m_e1; //m_from

        /// indice du sommet d'arriv�e de l'arc
        int m_e2; //m_to
//
//        /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
//        double m_weight;

        //coefficient d'influence
        float m_coefficient;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<InfluenceInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Influence (float coefficient=0, InfluenceInterface *interface=nullptr) :
            m_coefficient(coefficient), m_interface(interface)  {  }



        /// Influence �tant g�r� par Ecosysteme ce sera la m�thode update de Ecosysteme qui appellera
        /// le pre_update et post_update de Influence (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Ecosysteme::update dans le .cpp
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

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un Ecosystemee
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajout�s des boutons de contr�le etc...
        grman::WidgetBox m_tool_box;

        ///Bouton supprimer
        grman::WidgetCheckBox m_box_supprimer;

        ///Texte bouton supprimer
        grman::WidgetText m_text_supprimer;

        ///Bouton ajouter
        grman::WidgetCheckBox m_box_ajouter;

        ///texte bouton ajouter
        grman::WidgetText m_text_ajouter;


        // A compl�ter �ventuellement par des widgets de d�coration ou
        // d'�dition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        EcosystemeInterface(int x, int y, int w, int h);




};


class Ecosysteme
{


    private :

        std::vector<Influence*> vecInfluence;
        std::vector<Espece*>vecEspece;
        int m_nombre_espece;
        int m_nombre_influence;

        /// La "liste" des ar�tes
        std::map<int, Influence> m_Influences;

        /// La liste des sommets
        std::map<int, Espece> m_Espece;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<EcosystemeInterface> m_interface = nullptr;




    public:
        //Ecosysteme();
        ~Ecosysteme();
        /// Les constructeurs sont � compl�ter selon vos besoin...
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

        /// M�thode sp�ciale qui construit un Ecosystemee arbitraire (d�mo)
        /// Voir impl�mentation dans le .cpp
        /// Cette m�thode est � enlever et remplacer par un syst�me
        /// de chargement de fichiers par exemple.
        void make_example();
        void make_example2();


        /// La m�thode update � appeler dans la boucle de jeu pour les Ecosystemees avec interface
        void update();
};


#endif // Ecosysteme_H_INCLUDED
