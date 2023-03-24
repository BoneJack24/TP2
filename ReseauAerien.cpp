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

        // Condition première
        if(origine == destination)
        {
            return resultat;
        }
        // Initialisation d'une variable qui contient la ville source
        size_t m_villeSource;

        // Initialisation d'une variable qui contient la valeur de la ville solutionnée
        size_t m_villeSolutionne;

        // Initialisation d'une variable qui contiendra la valeur de la ville source
        //size_t p_villeSource;

        //Vous pouvez ajoutez des méthodes privées si vous sentez leur nécessité
        struct Arcs
        {
            size_t p_arcsVilleSource;
            size_t p_arcsVilleDestination;
            float p_arcsPonderation;
            size_t p_arcsPrecedent;

            Arcs(size_t source, size_t destination, float ponderation, size_t precedent) : p_arcsVilleSource(source),
                                                                                            p_arcsVilleDestination(destination), p_arcsPonderation(ponderation), p_arcsPrecedent(precedent) {};
        };

        struct triPond
        {
            bool operator()(Arcs lhs, Arcs rhs) {return lhs.p_arcsPonderation< rhs.p_arcsPonderation;}
        };

        // initialiser un vector<size_t, size_t>> p_arcsSolutionnés = T
        std::list<Arcs> m_lArcsSolutionnes; // contient le numéro des arcs solutionnés

        // initialiser un vector<size_t, size_t> p_arcsNonSolutionnés qui contient les arcs non solutionnés dans le
        // vecteur listeAdj de l'objet Graphe 'unReseau' du réseau aérien en traitement = Q
        std::list<Arcs> m_lArcsNonSolutionnes;

        // Initialiser un dictionnaire, dont la clé est le numéro associé à la ville et sa valeur est la distance
        // associée à la ville
        std::map<size_t, double> m_mDistanceVille;

        // Initialiser un dictionnaire, dont la clé est le numéro associé à la ville et sa valeur est le numéro de
        // la ville précédente associé à la clé
        std::map<size_t, size_t> m_mPrecedentVille;



        // SECTION ASSIGNATION VALEURS PAR DÉFAUT
        size_t p_nombresSommets;
        p_nombresSommets = unReseau.getNombreSommets();
        //std::cout<<"Le réseau possède " << p_nombresSommets << " sommets." << std::endl;
        for(int i = 0; i < p_nombresSommets; ++i)
        {
            // 1-)  Ajouter la valeur de chaque sommet à la clé de chacun des 2 dictionnaires.
            // 2-)  a-) Ajouter la valeur de la variable 'm_infini' à chacune des clés du dictionnaire 'm_mDistanceVille'.
            //      b-) Ajouter la valeur de la variable 'm_zero' à chacune des clés du dictionnaire 'm_mPrecedentVille'.
            m_mDistanceVille.insert(std::pair<int, double>(i, m_infini));
            m_mPrecedentVille.insert(std::pair<int, size_t>(i, m_nil));
        }

        //std::cout<<"La valeur de la la distance pour la ville " << unReseau.getNomSommet(0) << " est : " << m_mDistanceVille.at(0) << std::endl;
        //std::cout<<"La valeur de la la distance pour la ville " << unReseau.getNomSommet(0) << " est : " << m_mPrecedentVille.at(0) << std::endl;
        //std::cout<<"La valeur de la la distance pour la ville " << unReseau.getNomSommet(4) << " est : " << m_mDistanceVille.at(4) << std::endl;
        //std::cout<<"La valeur de la la distance pour la ville " << unReseau.getNomSommet(4) << " est : " << m_mPrecedentVille.at(4) << std::endl;
        //std::cout<<"La valeur de la la distance pour la ville " << unReseau.getNomSommet(16) << " est : " << m_mDistanceVille.at(16) << std::endl;
        //std::cout<<"La valeur de la la distance pour la ville " << unReseau.getNomSommet(16) << " est : " << m_mPrecedentVille.at(16) << std::endl;



        // JE SUIS RENDU ICI

        // 1-) a-)  Donner à la variable p_villeSource la valeur de la ville source (celle qui est dans la variable
        //          'm_villeSolutionne'). DOIT ÊTRE CELLE PASSÉ EN PARAMÈTRE D'ENTRÉE

        // Assignation de la ville source via l'assignation de départ de la ville solutionné à la ville d'origine

        m_villeSource = unReseau.getNumeroSommet(origine);

        // Assignation de la distance 0 à la ville source dans le dictionnaire des distances 'm_mDistanceVille'
        m_mDistanceVille.at(m_villeSource) = 0;

        // un objet de la structure Ponderations qui contiendra le poids de l'arc en évaluation
        Ponderations p_ponderationTemporaire = {0,0,0};

        // valeur temporaire de la ponderation de type size_t p_pondTemporaire
        float p_pondTemporaire;

        // 1-) b-)  creer un objet temporaire vide de la structure Arcs p_ArcTemporaire
        Arcs p_ArcTemporaire = {0,0,0,0,};

        // 1-) c-)  Créer un vecteur temporaire de type 'size_t' qui contiendra les sommets adjacents à la ville source
        //          en évaluation
        std::vector<size_t> p_vSommetsAdjacentsTemporaire;
        // 2-) a-)  Une boucle 'for' qui passe au travers chacun des sommets adjacents à 'p_villeSource' avec une
        //          condition

        // Itérateur pour le dictionnaire 'm_mPrecedentVille'
        std::map<size_t, size_t>::iterator it_m;

        // Paramètre contenant la valeur correspondant à la ville solutionnée
        m_villeSolutionne = m_villeSource;

        // Paramètre contenant la valeur de la ville de destination temporaire
        size_t p_villeDestinationTemp = unReseau.getNumeroSommet(destination);

        // Paramètre contenant la valeur du nombre de sommet adjacent à la ville destination en évaluation
        std::vector<size_t> p_nbrSommetsVilleDestinationTemp;

        while(m_villeSolutionne != unReseau.getNumeroSommet(destination))
        {
            std::cout<<"Le programme est au début de la boucle while et la ville solutionnee en évaluation est : " << unReseau.getNomSommet(m_villeSolutionne) << std::endl;
            m_villeSource = m_villeSolutionne;
            std::cout<<"Le programme est au début de la boucle while et la ville source en évaluation est : " << unReseau.getNomSommet(m_villeSource) << std::endl;
            std::cout<<"Est-ce que la ville solutionné est égale à la ville de destination? " << (m_villeSolutionne == unReseau.getNumeroSommet(destination)) << std::endl;
            std::cout<<"La ville solutionné est maintenant " << unReseau.getNomSommet(m_villeSolutionne) << std::endl;
            //m_villeSource =  m_villeSolutionne;
            std::cout<<"La ville source est maintenant " << unReseau.getNomSommet(m_villeSource) << std::endl;
            std::cout<<"Le numéro de la ville source est maintenant " << m_villeSource << std::endl;
            std::cout<<"Est-ce que la liste des arcs non solutionnés est vide ? " << (m_lArcsNonSolutionnes.size() == 0) << std::endl;
            p_vSommetsAdjacentsTemporaire = unReseau.listerSommetsAdjacents(m_villeSource);
            std::cout<<"Est-ce que le vecteur des sommets adjacents est vide ? " << (p_vSommetsAdjacentsTemporaire.size() == 0) << std::endl;
            if((p_vSommetsAdjacentsTemporaire.size() == 0) && (m_lArcsNonSolutionnes.size() == 0))
            {
                resultat.reussi = false;
                return resultat;
            }

            // Boucle qui passe au-travers chaque arc entre la ville source en évaluation et ses villes adjacentes pour
            // asssigner les distances à celles-ci selon les pondérations
            for(int i = 0; i < p_vSommetsAdjacentsTemporaire.size(); ++i)
            {
                // Initialisation d'une variable qui contiendra la valeur du poids entre les 2 villes en évaluation et
                // initialisation d'une variable 'p_poidsTemporaire', de type 'float' et ensuite lui assigner la
                // pondération entre les 2 villes en évaluation

                //std::cout<<"Le programme est ici." << std::endl;
                float p_poidsTemporaire;
                p_ponderationTemporaire = unReseau.getPonderationsArc(m_villeSource,p_vSommetsAdjacentsTemporaire.at(i));
                if(dureeCout == true) { p_poidsTemporaire = p_ponderationTemporaire.duree;};
                std::cout<<"La valeur de la variable p_ponderationTemporaire.duree est : "<< p_ponderationTemporaire.duree << std::endl;
                if(dureeCout == false) { p_poidsTemporaire = p_ponderationTemporaire.cout;};
                std::cout<<"La valeur de la variable p_ponderationTemporaire.cout est : "<< p_ponderationTemporaire.cout << std::endl;
                //std::cout<<"Le programme est là." << std::endl;

                // 2-) b-)  assigner la valeur de la variable p_villeSource à la variable de l'objet temporaire
                //          p_ArcTemporaire.p_arcsVilleSource
                p_ArcTemporaire.p_arcsVilleSource = m_villeSource;

                // 2-) c-)  assigner la valeur de la ville de destination, qui se trouve dans le vecteur temporaire
                //          p_vSommetsAdjacentsTemporaire à la positon de l'itérateur 'i', à la variable de l'objet
                //          temporaire p_ArcTemporaire.p_arcsVilleDestination
                p_ArcTemporaire.p_arcsVilleDestination = p_vSommetsAdjacentsTemporaire.at(i);
                p_villeDestinationTemp = p_vSommetsAdjacentsTemporaire.at(i);
                p_nbrSommetsVilleDestinationTemp = unReseau.listerSommetsAdjacents(p_villeDestinationTemp);
                std::cout<<"La ville de destination assigné à p_villeDestinationTemp est : " << p_villeDestinationTemp << std::endl;

                // Condition pour arrêter le programme car il n'y aura pas de chemin possible
                std::cout<<std::endl;
                std::cout<<" LE PROGRAMME ENTRE DANS LA PARTIE ÉVALUATION DES CONDITIONS POUR AVISER QU'IL N'Y PAS DE CHEMIN POSSIBLE" << std::endl;
                if(m_lArcsNonSolutionnes.size() <= 1)
                {
                    std::cout<<"La distance de la ville de destination finale est : " << m_mDistanceVille.at(unReseau.getNumeroSommet(destination)) << std::endl;
                    std::cout<<"La ville de destination en évaluation est : " << unReseau.getNomSommet(p_villeDestinationTemp) << std::endl;
                    // Si au départ la ville de destination n'a pas d'arc = pas de chemin
                    std::cout<<"Est-ce que la ville source a seulement 1 sommet adjacent? " << (p_vSommetsAdjacentsTemporaire.size() == 1) << std::endl;
                    std::cout<<"Est-ce que la ville de destination en évaluation ne possède aucun sommet adjacent? " << (p_nbrSommetsVilleDestinationTemp.size() == 0) << std::endl;
                    std::cout<<"Est-ce que la ville de destination est la ville finale de destination ? " << (p_villeDestinationTemp != unReseau.getNumeroSommet(destination)) << std::endl;
                    std::cout<<"La ville source est : " << unReseau.getNomSommet(p_ArcTemporaire.p_arcsVilleSource) <<std::endl;
                    std::cout<<"Est-ce que la ville precedent de la ville source est la ville de destination ? " <<  (m_mPrecedentVille.at(p_ArcTemporaire.p_arcsVilleSource) == p_ArcTemporaire.p_arcsVilleDestination) << std::endl;
                    std::cout<<"et cette ville se nomme : " << m_mPrecedentVille.at(p_ArcTemporaire.p_arcsVilleSource) << std::endl;
                    std::cout<<"La ville de destination est : " << unReseau.getNomSommet(p_ArcTemporaire.p_arcsVilleDestination) <<std::endl;
                    std::cout<<"Est-ce que la ville precedent de la ville destination est la ville source ? " <<  (m_mPrecedentVille.at(p_ArcTemporaire.p_arcsVilleDestination) == m_villeSource) << std::endl;
                    std::cout<<"et cette ville se nomme : " << m_mPrecedentVille.at(p_ArcTemporaire.p_arcsVilleDestination) << std::endl;
                    if(p_vSommetsAdjacentsTemporaire.size() == 0)
                    {
                        resultat.reussi = false;
                        return resultat;
                    }
                    if((p_vSommetsAdjacentsTemporaire.size() == 1) && (p_nbrSommetsVilleDestinationTemp.size() == 0) && (p_villeDestinationTemp != unReseau.getNumeroSommet(destination)))
                    {
                        resultat.reussi = false;
                        return resultat;
                    }
                }
                std::cout<<std::endl;
                //std::cout<<"Le programme va assigner la pondération à la variable 'p_pondTemporaire'." << std::endl;
                //std::cout<<"La valeur de la variable p_pondTemporaire est : " << p_poidsTemporaire << std::endl;
                //std::cout<<"La valeur de la variable m_villeSource est : " << m_villeSource << std::endl;
                // 2-) d-)  assigner la valeur de p_pondTemporaire : valeur de la distance de la ville source + la pondération
                //          entre les 2 villes en évaluation
                p_pondTemporaire = m_mDistanceVille.at(m_villeSource) + p_poidsTemporaire;
                std::cout<<"La distance de la ville source est : "<< m_mDistanceVille.at(m_villeSource) << std::endl;
                std::cout<<"La variable 'p_pondTemporaire' contient la valeur : " << p_pondTemporaire << std::endl;
                std::cout<<"La valeur du sommet adjacent en évaluation est : " << p_vSommetsAdjacentsTemporaire.at(i) << std::endl;
                std::cout<<"La valeur de la distance à ce sommet est : " << m_mDistanceVille.at(p_vSommetsAdjacentsTemporaire.at(i)) << std::endl;
                // 2-) e-)  condition : si la valeur dans la variable 'p_pondTemporaire' est plus grande que la distance de la
                //          ville de destination :
                if(p_pondTemporaire < m_mDistanceVille.at(p_vSommetsAdjacentsTemporaire.at(i)))
                {
                    // 1-) assigner la valeur contenu dans la variable 'p_pondTemporaire' à la variable de l'objet temporaire
                    // p_ArcTemporaire.p_arcsPonderation
                    p_ArcTemporaire.p_arcsPonderation = p_pondTemporaire;
                    //std::cout<<"La ponderation entre l'arc entre ces 2 sommets est : " << p_ArcTemporaire.p_arcsPonderation << std::endl;
                    // 2-) ajouter la valeur de la variable 'p_pondTemporaire' dans le dictionnaire des distances 'm_mDistanceVille'
                    //std::cout<<"La ville de destination assignée à la valeur de p_arcsVilleDestination dans l'arc temporaire est : " << p_ArcTemporaire.p_arcsVilleDestination << std::endl;
                    //std::cout<<"La valeur à l'endroit : m_mDistanceVille.at(p_villeDestinationTemp) est : " << m_mDistanceVille.at(p_ArcTemporaire.p_arcsVilleDestination) << std::endl;
                    m_mDistanceVille.at(p_villeDestinationTemp) = p_pondTemporaire;
                    // 3-) ajouter l'objet temporaire p_ArcTemporaire dans la liste 'm_lArcsNonSolutionnes' via un push_back
                    m_lArcsNonSolutionnes.push_back(p_ArcTemporaire);
                    //std::cout<<"La taille de la liste des arcs non solutionnés est : "<< m_lArcsNonSolutionnes.size() << std::endl;
                }
            }

            std::cout<<"Le programme est à la sortie de la boucle 'for'." << std::endl;

            //std::cout<<"la ville de source est : " << m_lArcsNonSolutionnes.begin()->p_arcsVilleSource << std::endl;
            //std::cout<<"la ville de destination est : " << m_lArcsNonSolutionnes.begin()->p_arcsVilleDestination << std::endl;
            //std::cout<<"la ponderation est : " << m_lArcsNonSolutionnes.begin()->p_arcsPonderation << std::endl;

            if(m_lArcsNonSolutionnes.size() == 0)
            {
                resultat.reussi = false;
                return resultat;
            }

            // Trier la liste des arcs non solutionnés
            m_lArcsNonSolutionnes.sort(triPond());

            std::cout<<"Le tri a été effectué."<<std::endl;

            std::list<Arcs>::const_iterator it;
            std::cout<<"L'itérateur a été assigné."<<std::endl;
            std::cout<<"La taille du dictionnaire est : " << m_lArcsNonSolutionnes.size() <<std::endl;

            for(it = m_lArcsNonSolutionnes.begin(); it != m_lArcsNonSolutionnes.end(); ++it)
            {
                std::cout<<"Le programme est dans la boucle for pour imprimer les valeurs dans l'objet de la structure Arcs stocké dans la liste des arcs" << std::endl;
                p_ArcTemporaire = *it;
                std::cout<<"Ville Source : " << unReseau.getNomSommet(p_ArcTemporaire.p_arcsVilleSource) << std::endl;
                std::cout<<"Ville Destination : " << unReseau.getNomSommet(p_ArcTemporaire.p_arcsVilleDestination) << std::endl;
                std::cout<<"Ponderation : " << p_ArcTemporaire.p_arcsPonderation << std::endl;
            }


            //std::cout<<"Le programme est à la sortie du tri de la liste des arcs." << std::endl;

            // Confirmer la ville source, dans le dictionnaire 'm_mPrecedentVille', de la ville de destination du
            // premier arc dans la liste des arcs non solutionnés 'm_lArcsNonSolutionnes'
            //std::cout<<"la ville de source est : " << m_lArcsNonSolutionnes.begin()->p_arcsVilleSource << std::endl;
            //std::cout<<"la ville de destination est : " << m_lArcsNonSolutionnes.begin()->p_arcsVilleDestination << std::endl;
            //std::cout<<"la ponderation est : " << m_lArcsNonSolutionnes.begin()->p_arcsPonderation << std::endl;
            m_mPrecedentVille.at(m_lArcsNonSolutionnes.begin()->p_arcsVilleDestination) = m_lArcsNonSolutionnes.begin()->p_arcsVilleSource;
            std::cout<<"Le programme vient de confirmer la ville source " << unReseau.getNomSommet(m_mPrecedentVille.at(m_lArcsNonSolutionnes.begin()->p_arcsVilleDestination)) << " comme precedent de la ville de destination " <<  unReseau.getNomSommet(m_lArcsNonSolutionnes.begin()->p_arcsVilleDestination) <<std::endl;

            // Assignation de la ville de destination du plus court chemin (1er arc dans la liste) à la variable 'm_villeSolutionne'
            m_villeSolutionne = m_lArcsNonSolutionnes.begin()->p_arcsVilleDestination;

            // copier le premier élément dans la liste non solutonné à la liste solutionné

            it = m_lArcsNonSolutionnes.begin();
            p_ArcTemporaire = *it;
            m_lArcsSolutionnes.push_back(p_ArcTemporaire);

            // enlever le premier élément dans la liste non solutonné
            m_lArcsNonSolutionnes.pop_front();

            std::cout<<"La ville solutionnee avant la boucle while est : " << unReseau.getNomSommet(m_villeSolutionne) << std::endl;
            //refaire la boucle
        }


        for(it_m = m_mPrecedentVille.begin(); it_m != m_mPrecedentVille.end(); ++it_m)
        {
            std::cout<<"Ville : "<< unReseau.getNomSommet(it_m->first) << ". Precedent : " << it_m->second << std::endl;
        }

        std::cout<<std::endl;
        std::cout<<"LE PROGRAMME EST DANS LA SECTION CHEMIN"<<std::endl;
        resultat.listeVilles.push_back(destination);
        std::cout<<"La ville " << resultat.listeVilles.at(0) << " a été ajouté au vecteur listeVilles" << std::endl;
        std::cout<<"La ville de destination a été ajoutée au vecteur 'listeVilles de l'objet resultat" << std::endl;
        int compteur = m_mPrecedentVille.size();
        std::cout<<"La taille du dictionnaire m_mPrecedentVille est : " << compteur << std::endl;
        std::string p_villeRecherchee = destination;
        size_t p_numVilleDestination;
        while((resultat.listeVilles.at(0) != origine) || (compteur == 0))
        {
            std::cout<<"Le numéro de la ville de destination est : " << unReseau.getNumeroSommet(destination) << std::endl;
            for (it_m = m_mPrecedentVille.begin(); it_m != m_mPrecedentVille.end(); ++it_m)
            {
                //std::cout<<"La destination à la position actuelle de l'itérateur " << unReseau.getNomSommet(it_m->first) << " est " << it_m->second << std::endl;
                if ((it_m->first == unReseau.getNumeroSommet(p_villeRecherchee)) && (it_m->second < m_mPrecedentVille.size()))
                {
                    std::cout<<"Un élément a été trouvé. Son numéro de sommet est :  "<< it_m->second << std::endl;
                    p_numVilleDestination = it_m->second;
                    resultat.listeVilles.insert(resultat.listeVilles.begin(),unReseau.getNomSommet(it_m->second));
                    std::cout<<resultat.listeVilles.at(0)<<std::endl;
                    std::cout<<resultat.listeVilles.at(1)<<std::endl;
                    p_villeRecherchee = unReseau.getNomSommet(p_numVilleDestination);
                    std::cout<<"La ville recherchée est : " << p_villeRecherchee <<std::endl;
                }
            }
            compteur -=1;
        }
        if(resultat.listeVilles.size() == 1)
        {
            resultat.reussi = false;
        }
        if(compteur != 0)
        {
            resultat.reussi = true;
            if(dureeCout == true)
            {
                resultat.dureeTotale = m_mDistanceVille.at(unReseau.getNumeroSommet(destination));
            }
            if(dureeCout == false)
            {
                resultat.coutTotal = m_mDistanceVille.at(unReseau.getNumeroSommet(destination));
            }
        }
        return resultat;
    }

    Chemin ReseauAerien::rechercheCheminBellManFord(const std::string &origine, const std::string &destination, int dureeCoutNiveau) const
    {
        Chemin resultat;
        return resultat;
    }

    /*
    void ReseauAerien::ajouterValeursParDefaut()
    {
        // Selon le nombre de sommets
        size_t p_nombresSommets;
        p_nombresSommets = unReseau.getNombreSommets();
        for(int i = 0; i < p_nombresSommets; ++i)
        {
            // 1-)  Ajouter la valeur de chaque sommet à la clé de chacun des 2 dictionnaires.
            // 2-)  a-) Ajouter la valeur de la variable 'm_infini' à chacune des clés du dictionnaire 'm_mDistanceVille'.
            //      b-) Ajouter la valeur de la variable 'm_zero' à chacune des clés du dictionnaire 'm_mPrecedentVille'.
            m_mDistanceVille[0] = m_infini;
            //m_mPrecedentVille.at(i) = m_zero;
        }
    }
     */

    /*
    // Méthode implanté pour crèer des objets de la structure Arc contenant les informations pour chacun des arcs du
    // graphe 'unReseau'.
    void ReseauAerien::ajouterPonderations(size_t p_villeSource)
    {
        // ***  La valeur de la ville source dans le paramètre size_t p_villeSource doit être assigner avant cette
        //      fonction. Elle doit contenir la valeur dans la variable 'm_villeSolutionne' au début de cette fonction.
        //      NE PAS OUBLIER DE CONVERTIR LE PARAMÈTRE D'ENTRÉE 'origine' EN NOMBRE DE TYPE SIZE_T. ***
        //      NE PAS OUBLIER D'ASSIGNER LA VALEUR DU BOOLÉEN 'dureeCout' A LA VARIABLR 'm_dureeCout' AVANT D'ENTRÉE
        //      DANS CETTE FONCTION. ***
        // valeur de la ville de destination dans un paramètre size_t p_villeDestination
        // valeur de la pondération dans un paramètre size_t p_ponderation
        // un objet Poinderations qui contiendra le poids de l'arc en évaluation
        Ponderations p_ponderationTemporaire = {0,0,0};
        // valeur temporaire de la ponderation de type size_t p_pondTemporaire
        size_t p_pondTemporaire;
        // vecteur temporaire d'une liste contenu dans le vecteur de liste 'listeAdj' de la classe Graphe 'p_vSommetsAdjacents'

        // Étapes de la fonction
        // 1-) a-)  creer un objet temporaire vide de la structure Arcs p_ArcTemporaire
        Arcs p_ArcTemporaire = {0,0,0,0,};
        // 1-) b-)  Donner à la variable p_villeSource la valeur de la ville source (celle qui est dans la variable
        //          'm_villeSolutionne'). DOIT ÊTRE CELLE PASSÉ EN PARAMÈTRE D'ENTRÉE
        // 1-) c-)  Créer un vecteur temporaire de type 'size_t' qui contiendra les sommets adjacents à la ville source
        //          en évaluation
        std::vector<size_t> p_vSommetsAdjacentsTemporaire = unReseau.listerSommetsAdjacents(p_villeSource);
        // 2-) a-)  Une boucle 'for' qui passe au travers chacun des sommets adjacents à 'p_villeSource' avec une
        //          condition
        for(int i = 0; i < p_vSommetsAdjacentsTemporaire.size(); ++i)
        {
            // Initialisation d'une variable qui contiendra la valeur du poids entre les 2 villes en évaluation et
            // initialisation d'une variable 'p_poidsTemporaire', de type 'float' et ensuite lui assigner la
            // pondération entre les 2 villes en évaluation
            float p_poidsTemporaire;
            p_ponderationTemporaire = unReseau.getPonderationsArc(m_villeSource,p_vSommetsAdjacentsTemporaire.at(i));
            if(m_dureeCout == true) { p_poidsTemporaire = p_ponderationTemporaire.duree;};
            if(m_dureeCout == true) { p_poidsTemporaire = p_ponderationTemporaire.cout;};

            // 2-) b-)  assigner la valeur de la variable p_villeSource à la variable de l'objet temporaire
            //          p_ArcTemporaire.p_arcsVilleSource
            p_ArcTemporaire.p_arcsVilleSource = p_villeSource;

            // 2-) c-)  assigner la valeur de la ville de destination, qui se trouve dans le vecteur temporaire
            //          p_vSommetsAdjacentsTemporaire à la positon de l'itérateur 'i', à la variable de l'objet
            //          temporaire p_ArcTemporaire.p_arcsVilleDestination
            p_ArcTemporaire.p_arcsVilleDestination = p_vSommetsAdjacentsTemporaire.at(i);

            // 2-) d-)  assigner la valeur de p_pondTemporaire : valeur de la distance de la ville source + la pondération
            //          entre les 2 villes en évaluation
            p_pondTemporaire = m_mDistanceVille.at(p_vSommetsAdjacentsTemporaire.at(m_villeSource)) + p_poidsTemporaire;

            // 2-) e-)  condition : si la valeur dans la variable 'p_pondTemporaire' est plus grande que la distance de la
            //          ville de destination :
            if(p_pondTemporaire > m_mDistanceVille.at(p_vSommetsAdjacentsTemporaire.at(i)))
            {
                // 1-) assigner la valeur contenu dans la variable 'p_pondTemporaire' à la variable de l'objet temporaire
                // p_ArcTemporaire.p_arcsPonderation
                p_ArcTemporaire.p_arcsPonderation = p_pondTemporaire;
                // 2-) ajouter l'objet temporaire p_ArcTemporaire dans la liste 'm_lArcsNonSolutionnes' via un push_back
                m_lArcsNonSolutionnes.push_back(p_ArcTemporaire);
            }
        }
    }
     */

}//Fin du namespace
