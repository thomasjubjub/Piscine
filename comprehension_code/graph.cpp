#include "graph.h"
#include <fstream>
#include <string>

/***************************************************
                    Espece
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EspeceInterface::EspeceInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y); //x et y sont utiles pour la sauvegarde des positions
    m_top_box.set_dim(130, 100); //pas toucher
    m_top_box.set_moveable(); //declaration en true ce qui permet de bouger les widget

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
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

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Espece après l'appel à l'interface
void Espece::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
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
    m_coefficient=(1/coef);
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
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
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


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::sauvergarde_coords( std::string blaz)
{
    std::ofstream save (blaz.c_str(), std::ios::in | std::ios::trunc);

    save<<m_vertices.size()<<std::endl;


    for(int i=0; i<m_vertices.size(); i++)
    {

    save << m_vertices[i].m_value <<" "<< m_vertices[i].m_interface->m_top_box.get_posx() << " " << m_vertices[i].m_interface->m_top_box.get_posx() <<" "<< m_vertices[i].m_interface->m_img.get_pic_name()+"jpg.g" << std::endl;

    }

}
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

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

void Graph::make_example2()
{

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

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

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
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
             Graph::sauvergarde_coords("sauvegarde.txt");
        }


    for (auto &elt : m_Influences)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_Espece(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
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
void Graph::add_interfaced_Influence(int idx, int id_vert1, int id_vert2, double weight)
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

