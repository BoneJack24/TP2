/**
 * \file ReseauAerien.h
 * \brief Gestion d'un réseau aérien.
 * \author Jacques Boisclair - matricule : 536830566
 * \version 0.1
 * \date mars 2023
 *
 *  Travail pratique numéro 2
 *
 */

#include "Graphe.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
#include <vector>
#include <map>


#ifndef _RESEAUAERIEN__H
#define _RESEAUAERIEN__H

namespace TP2
{

    struct Chemin
    {
        //listeVilles doit contenir la liste des villes formant le chemin
        //Le point de départ du chemin correspond à l'élément d'indice 0 du vecteur
        //le point d'arrivée correspond au dernier élément du vecteur.
        std::vector<std::string> listeVilles;

        float dureeTotale;		// Durée totale du vol du chemin en heures incluant le temps d'escale
        float coutTotal;		// Cout total en dollars du chemin entre la ville de départ et la ville de destination
        int nsTotal;			// Niveau de sécurité total du chemin
        bool reussi;			// Un booléen qui vaut true si chemin a été trouvé, false sinon
    };

    class ReseauAerien{

    public:

        // Constructeur
        ReseauAerien(std::string nomReseau, size_t nbVilles = 5);

        // Destructeur
        ~ReseauAerien();

        // Change la taille du réseau en utilisant un nombre de villes = nouvelleTaille
        void resize(size_t nouvelleTaille);

        //Surcharge de l'opérateur de sortie.
        //Ne touchez pas à cette fonction !
        friend std::ostream& operator<<(std::ostream& out, const ReseauAerien& g)
        {
            out << g.unReseau << std::endl;
            return out;
        }

        // Charger un réseau à partir d'un fichier texte en entrée (voir format du fichier dans l'énoncé du Tp).
        // Construit un réseau routier à partir d'une liste de villes ainsi que leurs liens.
        // fichierEntree est ouvert corectement.
        // fichierEntree n'est pas fermé par la fonction.
        // Exception logic_error si fichierEntree n'est pas ouvert correctement.
        void chargerReseau(std::ifstream & fichierEntree);

        // Retourne le plus court chemin selon l'algorithme de Dijkstra
        // origine et destination font partie du graphe
        // Exception std::logic_error si origine et/ou destination absent du réseau
        Chemin rechercheCheminDijkstra(const std::string &origine, const std::string &destination, bool dureeCout) const;

        // Retourne le plus court chemin selon l'algorithme Bellman-Ford
        // origine et destination font partie du graphe
        // 1 <= dureeCoutNiveau <= 3
        // Exception std::logic_error si dureeCoutNiveau hors limite
        // Exception std::logic_error si origine et/ou destination absent du réseau
        Chemin rechercheCheminBellManFord(const std::string &origine, const std::string &destination, int dureeCoutNiveau) const;

        //Vous pouvez ajoutez d'autres méthodes publiques si vous sentez leur nécessité

    private:
        Graphe unReseau;		// Le type ReseauAerien est composé d'un graphe
        std::string nomReseau;		// Le nom du reseau (exemple: Air Canada)

        // Vous pouvez définir des constantes ici.

        double m_infini = std::numeric_limits<double>::infinity();
        size_t m_nil = 999;
        //size_t p_distanceTemporaire = 0;

        /*
        // Initialisation d'une variable qui contient la ville source
        size_t m_villeSource;

        // Initialisation d'une variable qui contient la valeur de la ville solutionnée
        size_t m_villeSolutionne;

        // Initialisation d'une variable qui contient la valeur de la ville solutionnée
        bool m_dureeCout;

        //Vous pouvez ajoutez des méthodes privées si vous sentez leur nécessité
        struct Arcs
        {
            size_t p_arcsVilleSource;
            size_t p_arcsVilleDestination;
            size_t p_arcsPonderation;
            size_t p_arcsPrecedent;

            Arcs(size_t source, size_t destination, size_t ponderation, size_t precedent) : p_arcsVilleSource(source),
            p_arcsVilleDestination(destination), p_arcsPonderation(ponderation), p_arcsPrecedent(precedent) {};
        };

        // initialiser un vector<size_t, size_t>> p_arcsSolutionnés = T
        std::list<Arcs> m_lArcsSolutionnes; // contient le numéro des arcs solutionnés

        // initialiser un vector<size_t, size_t> p_arcsNonSolutionnés qui contient les arcs non solutionnés dans le
        // vecteur listeAdj de l'objet Graphe 'unReseau' du réseau aérien en traitement = Q
        std::list<Arcs> m_lArcsNonSolutionnes;

        // Initialiser un dictionnaire, dont la clé est le numéro associé à la ville et sa valeur est la distance
        // associée à la ville
        std::map<int, double> m_mDistanceVille;

        // Initialiser un dictionnaire, dont la clé est le numéro associé à la ville et sa valeur est le numéro de
        // la ville précédente associé à la clé
        std::map<size_t, size_t> m_mPrecedentVille;
        */

        //void ajouterValeursParDefaut(); // Méthode qui initialise les dictionnaires 'm_mDistanceVille' et 'm_mPrecedentVille'
                                        // à leurs valeurs par défaut.

        //void ajouterPonderations(size_t p_villeSource); // Méthode qui ajoute à la liste des arcs non solutionnés :
                                                        // 'm_lArcsNonSolutionnes', la ville source, de destination
                                                        // et la pondération entre celles-ci
    };

}//Fin du namespace

#endif
