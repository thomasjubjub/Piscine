#include "Graph.h"
#include <fstream>
#include <string>

/***************************************************
                    Espece
****************************************************/

Espece :: Espece ()
{

}

Espece::~Espece()
{

}




/// Le constructeur met en place les éléments de l'interface
EspeceInterface::EspeceInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y); //x et y sont utiles pour la sauvegarde des positions
    m_top_box.set_dim(130, 100); //pas toucher
    m_top_box.set_moveable(); //declaration en true ce qui permet de bouger les widget

    ///Slider VALUE !!!
    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child(m_label_value);
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    m_top_box.add_child( m_box_label_blaz );
    m_box_label_blaz.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);
//    m_box_label_blaz.set_dim(30,12);
//    m_box_label_blaz.set_bg_color(BLANC);
    m_label_blaz.setcolor(BLANC);
    m_box_label_blaz.add_child(m_label_blaz);
    m_label_blaz.set_message(pic_name);

}


/// Gestion du Espece avant l'appel à l'interface
void Espece::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_N vers le slider associé
    m_interface->m_slider_value.set_value(m_N);

    /// Copier la valeur locale de la donnée m_N vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_N) );
}


/// Gestion du Espece après l'appel à l'interface
void Espece::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_N locale
    m_N = m_interface->m_slider_value.get_value();
}



/***************************************************
                    Influence
****************************************************/
/// Constucteurs
//Influence::Influence()
//{
//
//}

Influence::~Influence()
{

}


Influence::Influence(int e1, int e2, float coef)
{
    m_e1=e1;
    m_e2=e2;
    m_coefficient=(coef);
}
/// Le constructeur met en place les éléments de l'interface
InfluenceInterface::InfluenceInterface(Espece& from, Espece& to)
{
    // Le WidgetInfluence de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating InfluenceInterface between vertices having no interface" << std::endl;
        throw "Bad InfluenceInterface instanciation";
    }
    m_top_Influence.attach_from(from.m_interface->m_top_box);
    m_top_Influence.attach_to(to.m_interface->m_top_box);
    m_top_Influence.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_Influence.add_child(m_box_Influence);
    m_box_Influence.set_dim(24,60);
    m_box_Influence.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_Influence.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_Influence.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Influence avant l'appel à l'interface
void Influence::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Influence après l'appel à l'interface
void Influence::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}




/***************************************************
                    Ecosysteme
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Ecosystemee


/*Ecosysteme::Ecosysteme()
{

}*/

Ecosysteme::~Ecosysteme()
{

}

void Ecosysteme::Charger_Fichier(std::string nom_fichier)
{
    std::string extension = nom_fichier + ".txt";

    int e1, e2, n, K;
    float r,coef;
    std::string nom;
    std::string lala;
    std::ifstream fichier(extension.c_str(), std::ios::in);

    if(fichier)
    {
        do
        {
            fichier >> m_nombre_espece;

            for(int i=0; i<m_nombre_espece; i++)
            {
                fichier >> nom >> n >> r >> K;
                vecEspece.push_back(new Espece(nom, n, r, K));
            }


            fichier >> m_nombre_influence;

            for(int i=0; i<m_nombre_influence; i++)
            {
                fichier >> e1 >> e2 >> coef;
                vecInfluence.push_back(new Influence(e1, e2, coef));
            }

        }
        while (fichier.good());
    }

}

void Ecosysteme :: Affichage_ecosyst()
{
    for (int i = 0; i<vecEspece.size (); i++)
    {
        std::cout << vecEspece [i]->m_nom << "  " << vecEspece [i]->m_N << "  " <<vecEspece [i]->m_r << "  " << vecEspece [i]->m_K << std::endl;
    }

    for (int i=0; i< vecInfluence.size(); i++)
    {
        std::cout << vecInfluence [i]->m_e1 << "  " << vecInfluence [i]->m_e2 << "  et le coef " << vecInfluence [i]->m_coefficient << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}



EcosystemeInterface::EcosystemeInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}


/// Méthode spéciale qui construit un Ecosystemee arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos Ecosystemees soient construits
/// "à la main" dans le code comme ça.
void Ecosysteme::sauvergarde_coords( std::string blaz)
{
    std::ofstream save (blaz.c_str(), std::ios::in | std::ios::trunc);

    save<<m_vertices.size()<<std::endl;


    for(int i=0; i<m_vertices.size(); i++)
    {

    save << m_vertices[i].m_N <<" "<< m_vertices[i].m_interface->m_top_box.get_posx() << " " << m_vertices[i].m_interface->m_top_box.get_posx() <<" "<< m_vertices[i].m_interface->m_img.get_pic_name()+"jpg.g" << std::endl;

    }

}

void Ecosysteme::ecosysteme1()
{
    m_interface = std::make_shared<EcosystemeInterface>(50, 0, 750, 600);
    for (int i=0; i<vecEspece.size(); i++)
    {
        if (vecEspece[i]->m_N >0)
        {
    add_interfaced_Espece(i, vecEspece[i]->m_N, 50+(i*50), 50+(i*50), (vecEspece[i]->m_nom)+".jpg");
     }
    }

    for (int i=0; i<vecInfluence.size(); i++)
    {
        if ((vecEspece[vecInfluence[i]->m_e1]-> m_N > 0) && (vecEspece[vecInfluence[i]->m_e2]->m_N >0 ))
        {
        add_interfaced_Influence(i, vecInfluence[i]->m_e1, vecInfluence[i]->m_e2, vecInfluence[i]->m_coefficient);
        }
    }

}


void Ecosysteme :: Supprimer_Espece ()
{
    std::vector <Espece*> :: iterator it;
    std::string Espece_sup;
    std:: cout << "Quel animal veux-tu supprimer:" << std::endl;
    std::cin >> Espece_sup ;

    for (it=vecEspece.begin(); it!= vecEspece.end();it++ )
    {
        if ((*it)->m_nom == Espece_sup )
        {
            (*it)->m_N = 0;
        }
    }
}



///Domi: sauvegarder données fichier, Thomas chargement des dernières coordonnées

void Ecosysteme::make_example()
{
    m_interface = std::make_shared<EcosystemeInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new EcosystemeInterface(50, 0, 750, 600);

    ///include fichier
    ///lire fichier
    ///boucle for
    ///completer add_interface_Influence/Espece

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_Espece(0, 0.0, 200, 100, "requin.jpg");
    add_interfaced_Espece(1, 60.0, 400, 100, "thon.jpg");
    add_interfaced_Espece(2,  50.0, 200, 300, "maquereau.jpg");


    add_interfaced_Espece(3,  0.0, 400, 300, "clown4.jpg");
//    add_interfaced_Espece(4,  100.0, 600, 300, "clown5.jpg");
//    add_interfaced_Espece(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
//    add_interfaced_Espece(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
//    add_interfaced_Espece(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_Influence(0, 1, 2, 50.0);
    add_interfaced_Influence(1, 0, 1, 50.0);
    add_interfaced_Influence(2, 1, 3, 75.0);
//    add_interfaced_Influence(3, 4, 1, 25.0);
//    add_interfaced_Influence(4, 6, 3, 25.0);
//    add_interfaced_Influence(5, 7, 3, 25.0);
//    add_interfaced_Influence(6, 3, 4, 0.0);
    add_interfaced_Influence(7, 2, 0, 100.0);
//    add_interfaced_Influence(8, 5, 2, 20.0);
//    add_interfaced_Influence(9, 3, 7, 80.0);
}

void Ecosysteme::make_example2()
{

    m_interface = std::make_shared<EcosystemeInterface>(50, 0, 750, 600);

     add_interfaced_Espece(0, 0.0, 200, 100, "lion.jpg");
     add_interfaced_Espece(1, 0.0, 300, 100, "zebre.jpg");
     add_interfaced_Espece(2, 0.0, 400, 100, "elephant.jpg");
     add_interfaced_Espece(3, 0.0, 200, 200, "arbre.jpg");
     add_interfaced_Espece(4, 0.0, 200, 300, "bacterie.jpg");


     add_interfaced_Influence(0, 0, 2, 50.0);
     add_interfaced_Influence(7, 0, 1, 50.0);
     add_interfaced_Influence(1, 1, 3, 50.0);
     add_interfaced_Influence(2, 2, 3, 50.0);
     add_interfaced_Influence(3, 4, 2, 50.0);
     add_interfaced_Influence(4, 4, 1, 50.0);
     add_interfaced_Influence(5, 4, 3, 50.0);
     add_interfaced_Influence(6, 4, 0, 50.0);

}

/// La méthode update à appeler dans la boucle de jeu pour les Ecosystemees avec interface
void Ecosysteme::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_Influences)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

        if(key[KEY_S])
        {
             Ecosysteme::sauvergarde_coords("sauvegarde.txt");
        }


    for (auto &elt : m_Influences)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Ecosysteme::add_interfaced_Espece(int idx, int value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding Espece at idx=" << idx << " already used..." << std::endl;
        throw "Error adding Espece";
    }
    // Création d'une interface de sommet
    EspeceInterface *vi = new EspeceInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Espece(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Ecosysteme::add_interfaced_Influence(int idx, int id_vert1, int id_vert2, float weight)
{
    if ( m_Influences.find(idx)!=m_Influences.end() )
    {
        std::cerr << "Error adding Influence at idx=" << idx << " already used..." << std::endl;
        throw "Error adding Influence";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding Influence idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding Influence";
    }

    InfluenceInterface *ei = new InfluenceInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_Influence);
    m_Influences[idx] = Influence(weight, ei);
}

