/**
* \file Graphe.cpp
* \brief Implémentation d'un graphe orienté.
* \author Jacques Boisclair - matricule : 536830566
* \version 0.5
* \date mars 2023
*
*  Travail pratique numéro 2
*
*/

#include "Graphe.h"

//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{

    Graphe::Graphe(size_t nbSommets) : nbSommets(nbSommets), nbArcs(0)
    {
        sommets.resize(nbSommets);
    }

    Graphe::~Graphe() {}

    /**
     * \fn          resize
     * \brief       méthode qui assigne la taille au vecteur 'sommets'.
     * @param[in]   nouvelleTaille, de type 'type_t' qui contient la taille qui sera assigné au vecteur 'sommets'
     *
     *      Méthode qui assigne la taille du vecteur contenant les sommets d'un graphe.
     */
    void Graphe::resize(size_t nouvelleTaille)
    {
        sommets.resize(nouvelleTaille);
        nbSommets = nouvelleTaille;
    }

    /**
     * \fn              nommer
     * \brief           donne un nom à un sommet en utlisant son numéro (indice dans le vector).
     * @param[in]       sommet de type "size_t" contenant l'indice dans le vecteur.
     * @param[in]       nom de type "const string" contenant le nom du sommet à inscrire à l'indice dans le vecteur.
     *
     *      Inscrit le nom du sommet dans le vecteur 'sommets', de l'objet de la classe, à l'indice de celui-ci, qui est
     *      donné en paramètre d'entrée. Si l'indice du sommet est supérieur ou égal au membre 'nbSommetsException',
     *      contenant la valeur du nombre de sommets présentement dans le vecteur, une erreur de type "logic_error" est
     *      spoulevée.
     */
    void Graphe::nommer(size_t sommet, const std::string& nom)
    {
        //std::cout<<"Le sommet en paramètre d'entrée est : "<<sommet<<" ,et le nombre des sommets dans le vecteur est : "<<sommets.size()<<std::endl;
        if(sommet >= nbSommets)
        {
            throw std::logic_error("Le sommet est plus grand que le nombre de sommets contenable dans le vecteur");
        }
        else
        {
            sommets.at(sommet) = nom;
        }
    }

    /**
     * \fn          ajouterArc
     * \brief       méthode qui ajoute, dans un graphe, un arc entre 2 sommets ainsi que son poids.
     * @param[in]   source, de type "size_t" qui contient la valeur du sommet de départ.
     * @param[in]   destination, de type "size_t" qui contient la valeur du sommet de destination.
     * @param[in]   duree, de type "float" qui contient la durée en temps du trajet entre le sommet de départ et celui
     *              de destination.
     * @param[in]   cout, de type "float" qui contient le cout du trajet entre le sommet de départ et celui de
     *              destination.
     * @param[in]   ns, de type "int" qui contient le niveau de sécurité entre le sommet de départ et celui de
     *              destination.
     *
     *          Méthode qui insére sous forme de liste dans un vecteur ('listeAdj'), un arc contenant, (1) valeur de la
     *          ville de départ (source = # de sommet), (2) valeur de la ville de destination (destination = # de sommet),
     *          (3) la durée en temps du trajet entre les 2 villes (duree), (4) le coût du trajet entre les 2 villes (cout)
     *          et (5) le niveau de sécurité pour voyager entre celles-ci. Avant l'insertion la méthode vérifie si les
     *          villes existes (sommets) dans le vecteur ('sommets') de celles-ci ainsi que si l'arc existe déjà via
     *          la méthode 'arcExiste'. Si c'est le cas, dans une ou l'autre des options une erreur de type "logic_error"
     *          est lancée.
     */
    void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout, int ns)
    {
        if(source >= nbSommets)
        {
            throw std::logic_error("ajouterArc : Le sommet source est plus grand que le nombre de sommets contenable dans le vecteur");
        }
        if(destination >= nbSommets)
        {
            throw std::logic_error("ajouterArc : Le sommet destination est plus grand que le nombre de sommets contenable dans le vecteur");
        }
        if(arcExiste(source, destination))
        {
            throw std::logic_error("ajouterArc: L'arc passé en paramètre existe déjà");
        }
        else
        {
            listesAdj.resize(nbArcs+1);
            Ponderations p_ponderations = {duree, cout, ns};
            Arc p_arc = {destination, p_ponderations };
            listesAdj.at(source).push_back(p_arc);
            nbArcs +=1;
        }
    }

    /**
     * \fn          enleverArc
     * \brief       Méthode qui supprime, dans un graphe, un arc entre 2 sommets.
     * @param[in]   source, de type "size_t" qui contient la valeur du sommet de départ.
     * @param[in]   destination, de type "size_t" qui contient la valeur du sommet de destination.
     *
     *      Méthode qui supprime un arc et son poids, dans une liste contenu dans un vecteur ('listesAdj'). Avant la
     *      suppression la méthode vérifie si les villes existes (sommets) dans le vecteur ('sommets') de celles-ci
     *      ainsi que si l'arc existe déjà via la méthode 'arcExiste'. Si c'est le cas, dans une ou l'autre des options
     *      une erreur de type "logic_error" est lancée.
     */
    void Graphe::enleverArc(size_t source, size_t destination)
    {
        if(source >= nbSommets)
        {
            throw std::logic_error("enleverArc : Le sommet source est plus grand que le nombre de sommets contenable dans le vecteur");
        }
        if(destination >= nbSommets)
        {
            throw std::logic_error("enleverArc : Le sommet destination est plus grand que le nombre de sommets contenable dans le vecteur");
        }
        if(!arcExiste(source, destination))
        {
            throw std::logic_error("L'arc passé en paramètre n'existe pas");
        }
        else
        {
            std::list<Arc>:: iterator it;
            Ponderations p_pond = {0,0,0};
            Arc p_arc(0, p_pond);
            for(it = listesAdj.at(source).begin(); it != listesAdj.at(source).end(); ++it)
            {
                p_arc = *it;
                if(p_arc.destination == destination)
                {
                    it = listesAdj.at(source).erase(it);
                    nbArcs -= 1;
                }
            }
        }
    }

    bool Graphe::arcExiste(size_t source, size_t destination) const
    {
        if (source >= nbSommets)
        {
            throw std::logic_error("arcExiste: Le sommet source est plus grand que le nombre de sommets contenable dans le vecteur.");
        }
        if (destination >= nbSommets)
        {
            throw std::logic_error("arcExiste: Le sommet destination est plus grand que le nombre de sommets contenable dans le vecteur.");
        }
        else
        {
            if (listesAdj.size() > 0)
            {
                std::list<Arc>::const_iterator it;
                Ponderations p_pond = {0, 0, 0};
                Arc p_arc(0, p_pond);

                if(source > listesAdj.size()-1)
                {
                    return false;
                }
                for(it = listesAdj.at(source).begin(); it != listesAdj.at(source).end(); ++it)
                {
                    p_arc = *it;
                    if(p_arc.destination == destination)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    /**
     * \fn          listerSommetsAdjacents
     * \brief       méthode qui retourne la liste de successeurs d'un sommet.
     * @param[in]   sommet, de type 'size_t, qui contien la valeur d'un sommet.
     * @return[out] v, vecteur contenant les sommets adjacents au sommet passé en paramètre.
     *
     *
     */
    std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const
    {
        std::vector<size_t> v;
        if(sommet >= nbSommets)
        {
            throw std::logic_error("listerSommetsAdjacents : Le sommet est plus grand que le nombre de sommets contenable dans le vecteur");
        }
        std::list<Arc>::const_iterator it;
        Ponderations p_pond = {0,0,0};
        Arc p_arc(0, p_pond);
        for(it = listesAdj.at(sommet).begin(); it != listesAdj.at(sommet).end(); ++it)
        {
            p_arc = *it;
            v.push_back(p_arc.destination);
        }
        return v;
    }

    /**
     * \fn          getNomSommet
     * \brief       Méthode qui retourne le nom du sommet correspondant au sommet passé en paramètre.
     * @param[in]   sommet, de type 'size_t', contenant la valeur du sommet dont on veut trouver son nom.
     * @return[out] nom du sommet, de type 'string', conteant le nom du sommet passé en paramètre.
     *
     *      Méthode qui retourne le nom de la ville associé au sommet passé en paramètre.
     */
    std::string Graphe::getNomSommet(size_t sommet) const
    {
        if(sommet >= nbSommets)
        {
            throw std::logic_error("getNomSommet : Le sommet est plus grand que le nombre de sommets contenable dans le vecteur");
        }
        return sommets.at(sommet);
    }

    /**
     * \fn          getNumeroSommet
     * \brief       Méthode qui retourne le sommet correspondant à son nom, qui est passé en paramètre de la méthode.
     * @param[in]   nom, de type 'string', qui contient le nom du sommet recherché.
     * @return[out] sommet, de type 'size_t' qui correspond au sommet (nombre) dont le nom est passé en paramètre de la
     *              méthode
     *
     *          Méthode qui retourne le nombre correspondant au sommet qui correspond au nom de la ville qui est passé
     *          en paramètre dans la méthode.
     */
    size_t Graphe::getNumeroSommet(const std::string& nom) const
    {
        for(size_t i = 0; i < sommets.size(); ++i)
        {
            if(sommets.at(i) == nom)
            {
                return i;
            }
        }

        throw std::logic_error("getNumeroSommet : Ce nom de sommet n'existe pas dans la liste des sommets");
    }

    /**
     * \fn          getNombreSommets
     * \brief       Méthode qui retorune le nombre de sommets ajouter au graphe et contenu dans le paramètre interne
     *              'nbSommets'
     * @return[out] nbSommets, de type size_t, qui contient le nombre de sommets ajouter au graphe.
     *
     *      Méthode qui retourne le nombre de villes ajouter dans le graphe.
     */
    int Graphe::getNombreSommets() const
    {
        //std::cout<<"Le nombre de sommets dans le vecteur est : "<<nbSommets<<std::endl;
        return nbSommets;
    }

    /**
     * \fn          getNombreArcs
     * \brief       Méthode qui retourne le nombre d'arcs ajouter entre les sommets.
     * @return[out] la taille du vecteur, contenant les arcs entre les sommets.
     *
     *      Méthode qui retourne le nombre de trajets total entre les villes où il y a du transport aérien.
     */
    int Graphe::getNombreArcs() const
    {
        return nbArcs;
    }

    /**
     * \fn          getPonderationsArc
     * \brief       Méthode qui retourne les pondérations d'un arc.
     * @param[in]   source, de type 'size_t', qui contient la valeur du sommet source d'un arc.
     * @param[in]   destination, de type 'size_t', qui contient la valeur du sommet de la destination d'un arc.
     * @return
     */
    Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const
    {
        if (source >= nbSommets)
        {
            throw std::logic_error("arcExiste: Le sommet source est plus grand que le nombre de sommets contenable dans le vecteur.");
        }
        if (destination >= nbSommets)
        {
            throw std::logic_error("arcExiste: Le sommet destination est plus grand que le nombre de sommets contenable dans le vecteur.");
        }
        if(!arcExiste(source, destination))
        {
            throw std::logic_error("L'arc passé en paramètre n'existe pas");
        }
        else
        {
            if (listesAdj.size() > 0)
            {
                std::list<Arc>::const_iterator it;
                Ponderations poids = {0, 0, 0};
                Arc p_arc(0, poids);

                for(it = listesAdj.at(source).begin(); it != listesAdj.at(source).end(); ++it)
                {
                    p_arc = *it;
                    if(p_arc.destination == destination)
                    {
                        return p_arc.poids;
                    }
                }
            }
        }
        return listesAdj[source].begin()->poids;
    }

}//Fin du namespace
