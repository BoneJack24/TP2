/**
 * \file ReseauAerien.cpp
 * \brief Implémentattion de la classe ReseauAerien.
 * \author Jacques Boisclair - matricule : 536830566
 * \version 0.1
 * \date mars 2023
 *
 *  Travail pratique numéro 2
 *
 */

#include "ReseauAerien.h"
#include <sstream>
#include <fstream>
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{
    ReseauAerien::ReseauAerien(std::string nomReseau, size_t nbVilles) {
    }

    ReseauAerien::~ReseauAerien() {
    }


    void ReseauAerien::resize(size_t nouvelleTaille) {
    }

    // Méthode fournie
    /**
     * \fn void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
     * \brief Permet de charger le réseau à partir d'un fichier texte
     * \param[in] le fichier contenant l'information sur le réseau
     * \pre fichierEntree a déjà été ouvert
     * \post Le réseau a été chargé
     * \exception logic_error si le fichier n'est pas déjà ouvert
     */
    void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
    {
        //std::cout<<"ReseauAerien : Le programme débute la méthode 'chargerReseau'." << std::endl;
        if (!fichierEntree.is_open())
            throw std::logic_error("ReseauAerien::chargerReseau: Le fichier n'est pas ouvert !");

        std::string buff;
        getline(fichierEntree, nomReseau);
        nomReseau.erase(0, 15);

        int nbVilles;

        fichierEntree >> nbVilles;
        getline(fichierEntree, buff); //villes

        unReseau.resize(nbVilles);
        //std::cout<<"ReseauAerien : Le nombre de villes est : " << nbVilles << std::endl;
        //std::cout<<"ReseauAerien : Le nombre de sommets est : " << unReseau.getNombreSommets() << std::endl;

        getline(fichierEntree, buff); //Liste des villes

        size_t i = 0;

        getline(fichierEntree, buff); //Premiere ville

        while(buff != "Liste des trajets:")
        {
            std::string ville = buff;

            unReseau.nommer(i, ville);
            //std::cout<<"ReseauAerien : Le nom du sommet en évaluation est : "<<unReseau.getNomSommet(i)<<std::endl;

            getline(fichierEntree, buff);
            i++;
        }

        while(!fichierEntree.eof())
        {
            getline(fichierEntree, buff);
            std::string source = buff;
            //std::cout<<"ReseauAerien : Le nom de la source en évaluation est : "<<source<<std::endl;

            getline(fichierEntree, buff);
            std::string destination = buff;
            //std::cout<<"ReseauAerien : Le nom de la destination en évaluation est : "<<destination<<std::endl;

            getline(fichierEntree, buff);
            std::istringstream iss(buff);

            float duree;
            iss >> duree;
            //std::cout<<"ReseauAerien : La duree de l'arc est : "<<duree<<std::endl;

            float cout;
            iss >> cout;
            //std::cout<<"ReseauAerien : Le cout de l'arc est : "<<cout<<std::endl;

            int ns;
            iss >> ns;
            //std::cout<<"ReseauAerien : Le niveau de sécurité de l'arc est : "<<ns<<std::endl;

            //std::cout<<"ReseauAerien : Le nom de la source est : "<< source <<std::endl;
            //std::cout<<"ReseauAerien : Le numéro de la source est : "<<unReseau.getNumeroSommet(source)<<std::endl;

            unReseau.ajouterArc(unReseau.getNumeroSommet(source), unReseau.getNumeroSommet(destination), duree, cout, ns);
        }
    }

    Chemin ReseauAerien::rechercheCheminDijkstra(const std::string &origine, const std::string &destination, bool dureeCout) const
    {
        Chemin resultat;

        std::cout<<"La taille du graphe est : "<< unReseau.getNombreSommets() << std::endl;
        std::cout<<"Le nom de la ville d'origine est : "<< unReseau.getNumeroSommet(origine) << std::endl;
        std::cout<<"Le nom de la ville de destination est : "<< unReseau.getNumeroSommet(destination) << std::endl;
        // initialiser une structure de couple
        struct Couple
        {
            size_t p_source;
            size_t p_destination;

            Couple(size_t source, size_t destination) : p_source(destination), p_destination(destination) {};
        };

        // initialiser vector<type_t> p_distance et lui donner la taille du nombre de sommets et leur donner la valeur
        //  infinity ex float p_float = numeric_limits<float>::infinity(); Pourrairt essayer avec un size_t et pourrais
        //  l'assigner à une constante dans le .h = d(v)
        std::list<size_t> p_distances(unReseau.getNombreArcs(), m_infini);
        std::list<size_t>::const_iterator it;
        it = p_distances.begin();
        //std::cout<<"Le nombre d'arcs dans le graphe 'unRéseau' est : " << unReseau.getNombreArcs() << std::endl;
        std::cout<<"La taille de la liste 'p_distances' est : " << p_distances.size() << std::endl;
        p_distances.front() = 0;
        std::cout<<"La taille de la liste 'p_distances' est : " << p_distances.size() << std::endl;

        //std::cout<<"La valeur de la distance du 2ième élément dans le vecteur de distance est : " << p_distances.at(1) << std::endl;

        // initialiser vector<type_t> p_precedent et lui donner la taille du nombre de sommets et leur donner la valeur
        //  nil ou autre valeur (pas certain que 0 certain une bonne option); Pourrait essayer avec un size_t et pourrait
        //  l'assigner à une constante dans le .h *** Pas oublier que le 1er précedent est la ville source
        std::vector<size_t> p_precedents (unReseau.getNombreSommets(), m_zero);

        // initialiser un vector<size_t, size_t>> p_arcsSolutionnés = T
        std::vector<std::list<Couple>> p_arcsSolutionnes; // contient le numéro des arcs solutionnés

        // initialiser un vector<size_t, size_t> p_arcsNonSolutionnés qui contient les arcs non solutionnés dans le
        // vecteur listeAdj de l'objet Graphe 'unReseau' du réseau aérien en traitement = Q
        std::vector<std::list<Couple>> p_arcsNonSolutionnes;

        // initialisation d'un vecteur de type 'size_t' qui servira à contenir les sommets adjacents d'un sommet contenu
        // dans le vecteur listeAdj de l'objet Graphe 'unReseau' du réseau aérien en traitement .
        std::vector<size_t> p_sommetsAdjacents;

        // Boucle qui assigne chacun des arcs de l'objet Graphe 'unReseau' du réseau aérien en traitement dans le vecteur
        // 'p_arcsNonSolutionnes', contenant le type de la structure 'Couple'.
        for(size_t i = 0; i < unReseau.getNombreSommets(); ++i)
        {
            //std::cout<<"Le programme entre dans le boucle 'for' des assignations d'arcs." << std::endl;
            p_sommetsAdjacents = unReseau.listerSommetsAdjacents(i);
            //std::cout<<"Le programme vient d'assigner les arcs contenu dans le vecteur à la position " << i << " dans le vecteur 'p_sommetsAdjacents." << std::endl;
            Couple p_coupleTampon = {0,0};
            for(size_t j = 0; j < p_sommetsAdjacents.size(); ++j)
            {
                p_coupleTampon.p_source = i;
                std::cout<<"Le vecteur 'p_sommetsAdjacents' à la position " << j << " contient la valeur de la ville source : " << p_coupleTampon.p_source << std::endl;
                p_coupleTampon.p_destination = p_sommetsAdjacents.at(j);
                std::cout<<"Le vecteur 'p_sommetsAdjacents' à la position " << j << " contient la valeur de la ville destination : " << p_coupleTampon.p_destination << std::endl;
                p_arcsNonSolutionnes.push_back(p_coupleTampon);
            }
        }

        /*
        std::cout<<"La liste des arcs sont : " << std::endl;
        for(int i = 0; i < p_arcsNonSolutionnes.size(); ++i)
        {
            Couple p_coupleTampon = {0,0};
            p_coupleTampon = p_arcsNonSolutionnes.at(i);
            std::cout<<"Source : "<< p_coupleTampon.p_source << " Destination : " << p_coupleTampon.p_destination << std::endl;
        }
        */

        // Assigantion de variables qui serviront dans l'exécution de cette méthode
        // d(u) = distance qui contient la distance des villes de destinations (assigné à infini au départ),
        size_t p_distanceDestination;
        // d(u*) = distance de la ville source
        size_t p_distanceSource;
        // p(u) = numéro de la ville qui précède le chemin le plus court entre celle-ci et sa destination
        size_t p_precedent;
        // u = numéro de sommet de la destination
        size_t p_villeDestination;
        // u* = numéro de ville source
        size_t p_villeSource = unReseau.getNumeroSommet(origine);


        // *** enlever cet arc (u*) de Q

        // *** assigner cet arc dans T

        // p_distanceTemporaire = d(u*) + w(u*, u), w(u*, u) est le poids de l'arc entre les 2 villes. *** ce sera
        // soit la duree ou le cout selon si le booléen dureeCout est true (durée) ou false (cout)
        // besoin d'une méthode ou code qui cherche la pondération entre 2 arcs.

        TP2::Ponderations p_ponderation(0,0,0);
        size_t poids;
        std::vector<size_t> p_vecTampon;
        size_t p_distanceTemporaire = 0;
        while(p_arcsSolutionnes.size() <= unReseau.getNombreArcs()) // toute ville de destination (u), dans Q, qui est adjacent à la ville source (u*))
        {
            p_vecTampon = unReseau.listerSommetsAdjacents(p_villeSource); // ou le sommet de départ dans
            for(int i = 0; i < p_vecTampon.size(); ++i)
            {
                std::cout<<"La ville dans le vecteur 'p_vecTampon à l'index : "<< i << " est : " << p_vecTampon[i] << std::endl;
            }
            for(size_t i = 0; i < p_vecTampon.size(); ++i)
            {
                std::cout<<"Le numéro de la ville source à l'entrée de la boucle est : "<< p_villeSource << std::endl;
                p_villeDestination = p_vecTampon.at(i);
                std::cout<<"La ville de destination en évaluation dans la boucle est : " << p_villeDestination << std::endl;
                p_ponderation = unReseau.getPonderationsArc(p_villeSource,p_villeDestination);
                if(dureeCout == true)
                {
                    poids = p_ponderation.duree;
                }
                if(dureeCout == false)
                {
                    poids = p_ponderation.cout;
                }
                //Initialsation d'un vecteur temporaire contenant les poids entre les villes de destination d
                std::vector<float> p_vPoidsTemp;
                std::cout<<"Le poids de l'arc en évaluation est : " << poids << std::endl;
                std::advance(it, p_villeDestination);
                std::cout<<"La distance de la ville destination est : " << *it <<std::endl;
                p_distanceTemporaire = *it + poids;
                std::cout<<"La distance temporaire est : " << p_distanceTemporaire <<std::endl;
                std::cout<<"La distance de la ville source est : " << *it <<std::endl;
                std::cout<<"Est-ce que la distance temporaire est plus petite que la distance de la ville de destination : " << (p_distanceTemporaire < *it) << std::endl;
                if(p_distanceTemporaire < *it)
                {
                    it = p_distances.erase(it);
                    p_distances.insert(it, p_distanceTemporaire);
                    // p_distances.insert(it,p_distanceTemporaire);
                    std::cout<<"La distance de la ville de destination est maintenant : " << *it << std::endl;
                    p_precedents.at(p_villeDestination) = p_villeSource;
                    std::cout<<"La ville précédent la ville de destination est : " << p_precedents.at(p_villeDestination) << std::endl;
                }
                //Trouver l'index du poids le plus faible
                for()
            }
            Couple arcPlusCourtChemin(p_villeSource, p_villeDestination);

            // Assigantion de l'objet de la structure 'Couple' dont le plus court chemin a été trouvé dans le vecteur
            // de couple solutionné.
            p_arcsSolutionnes.push_back(p_arcsNonSolutionnes.at());
            // Enlever l'objet de la structure 'Couple' dont le plus court chemin a été trouvé dans le vecteur
            // de couple solutionné.
            p_arcsNonSolutionnes.erase(p_arcsNonSolutionnes.begin());
            p_distances.sort();
            break;
        }

        //      assigner à p_distanceTemporaire les valeurs
        //      if(p_distanceTemporaire < d(u))
        //      {
        //          d(u) = p_distanceTemporaire;
        //          p(u) = u*
        //      }



        /*
         p_distanceTemporaire = p_distanceSource + poids(arc u*, u);
         if(p_distanceTemporaire < p_distanceDestination)
         {
            p_distanceDestination = p_distanceTemporaire;
            p_precedent = p_villeSource;
         }
         */

        // Remplir le contenu de la structure Chemin


        return resultat;
    }

    Chemin ReseauAerien::rechercheCheminBellManFord(const std::string &origine, const std::string &destination, int dureeCoutNiveau) const
    {
        Chemin resultat;
        return resultat;
    }

}//Fin du namespace
