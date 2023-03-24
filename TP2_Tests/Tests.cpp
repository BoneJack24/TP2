//
// Created by Jacques Boisclair on 2023-03-07.
//

#include <iostream>
#include "Graphe.h"
#include "ReseauAerien.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Graphe, constructeur_nothrow)
{
EXPECT_NO_THROW(TP2::Graphe gr;) ;
}

TEST(Graphe, constructeur_nbrDeSommets)
{
TP2::Graphe gr1;
EXPECT_EQ(10, gr1.getNombreSommets()) ;
}

TEST(Graphe, resize)
{
TP2::Graphe gr1;
gr1.resize(20);
EXPECT_EQ(20, gr1.getNombreSommets()) ;
EXPECT_NE(10, gr1.getNombreSommets()) ;
}

TEST(Graphe, nommer)
{
TP2::Graphe gr1(1);
gr1.nommer(0, "S1");
EXPECT_EQ("S1", gr1.getNomSommet(0)) ;
EXPECT_NE("S2", gr1.getNomSommet(0)) ;
EXPECT_ANY_THROW(gr1.getNomSommet(1)) ;
}

TEST(Graphe, nommerSommetTropGrand)
{
TP2::Graphe gr1(1);
EXPECT_THROW(gr1.nommer(2, "S3"), std::logic_error) ;
}

TEST(Graphe, ajouterArc)
{
TP2::Graphe gr1(3);
gr1.nommer(0, "S1");
gr1.nommer(1, "S2");
gr1.nommer(2, "S3");
EXPECT_EQ(3, gr1.getNombreSommets());

gr1.ajouterArc(0,0,100,200,-3);
EXPECT_EQ(1, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_FALSE(gr1.arcExiste(0,1));
EXPECT_FALSE(gr1.arcExiste(0,2));
EXPECT_FALSE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

gr1.ajouterArc(0,1,125,225,-2);
EXPECT_EQ(2, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_FALSE(gr1.arcExiste(0,2));
EXPECT_FALSE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

gr1.ajouterArc(0,2,150,250,-1);
EXPECT_EQ(3, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_FALSE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

gr1.ajouterArc(1,0,175,275,-1);
EXPECT_EQ(4, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

EXPECT_NO_THROW(gr1.ajouterArc(1,1,200,300,0));
EXPECT_EQ(5, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

gr1.ajouterArc(1,2,225,325,1);
EXPECT_EQ(6, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_TRUE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

gr1.ajouterArc(2,0,250,350,2);
EXPECT_EQ(7, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_TRUE(gr1.arcExiste(1,2));
EXPECT_TRUE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

gr1.ajouterArc(2,1,275,375,2);
EXPECT_EQ(8, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_TRUE(gr1.arcExiste(1,2));
EXPECT_TRUE(gr1.arcExiste(2,0));
EXPECT_TRUE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

gr1.ajouterArc(2,2,300,400,3);
EXPECT_EQ(9, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_TRUE(gr1.arcExiste(1,2));
EXPECT_TRUE(gr1.arcExiste(2,0));
EXPECT_TRUE(gr1.arcExiste(2,1));
EXPECT_TRUE(gr1.arcExiste(2,2));

EXPECT_THROW(gr1.ajouterArc(0,0,200,300,4), std::logic_error);
EXPECT_THROW(gr1.ajouterArc(1,0,200,300,4), std::logic_error);
EXPECT_THROW(gr1.ajouterArc(2,2,200,300,4), std::logic_error);

EXPECT_NO_THROW(gr1.enleverArc(1,2));
EXPECT_EQ(8, gr1.getNombreArcs());
EXPECT_NO_THROW(gr1.enleverArc(0,1));
EXPECT_EQ(7, gr1.getNombreArcs());
EXPECT_NO_THROW(gr1.enleverArc(2,1));
EXPECT_EQ(6, gr1.getNombreArcs());

gr1.ajouterArc(1,2,275,375,2);
gr1.ajouterArc(0,1,125,225,-2);
gr1.ajouterArc(2,1,225,325,1);

EXPECT_EQ(9, gr1.getNombreArcs());
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_TRUE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_TRUE(gr1.arcExiste(1,2));
EXPECT_TRUE(gr1.arcExiste(2,0));
EXPECT_TRUE(gr1.arcExiste(2,1));
EXPECT_TRUE(gr1.arcExiste(2,2));
}

TEST(Graphe, enleverArc)
{
TP2::Graphe gr1(3);
gr1.nommer(0, "S1");
gr1.nommer(1, "S2");
gr1.nommer(2, "S3");
EXPECT_EQ(3, gr1.getNombreSommets());

//Validation qu'il n'y a aucun arc
EXPECT_FALSE(gr1.arcExiste(0,0));
EXPECT_FALSE(gr1.arcExiste(0,1));
EXPECT_FALSE(gr1.arcExiste(0,2));
EXPECT_FALSE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

// Ajout d'arcs et validation si le nombre d'arc s'ajoute au paramètre membre nbArcs
EXPECT_EQ(0,gr1.getNombreArcs());
gr1.ajouterArc(0,0,200,300,0);
EXPECT_EQ(1,gr1.getNombreArcs());
gr1.ajouterArc(0,2,100,200,3);
EXPECT_EQ(2,gr1.getNombreArcs());
gr1.ajouterArc(1,0,175,275,4);
EXPECT_EQ(3,gr1.getNombreArcs());
gr1.ajouterArc(1,1,150,250,5);
EXPECT_EQ(4,gr1.getNombreArcs());
gr1.ajouterArc(2,2,125,220,-3);
EXPECT_EQ(5,gr1.getNombreArcs());
// Validation si les arcs entre chaque sommets existent ou pas
EXPECT_TRUE(gr1.arcExiste(0,0));
EXPECT_FALSE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_TRUE(gr1.arcExiste(2,2));

// Validation d'enlever les arcs
EXPECT_THROW(gr1.enleverArc(0,1), std::logic_error);
EXPECT_THROW(gr1.enleverArc(1,2), std::logic_error);
EXPECT_THROW(gr1.enleverArc(2,0), std::logic_error);
EXPECT_THROW(gr1.enleverArc(2,1), std::logic_error);
EXPECT_NO_THROW(gr1.enleverArc(0,0));
EXPECT_NO_THROW(gr1.enleverArc(2,2));
EXPECT_EQ(3,gr1.getNombreArcs());

EXPECT_FALSE(gr1.arcExiste(0,0));
EXPECT_FALSE(gr1.arcExiste(0,1));
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_TRUE(gr1.arcExiste(1,0));
EXPECT_TRUE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

// Validation en enlevant les arcs restants
EXPECT_NO_THROW(gr1.enleverArc(0,2));
EXPECT_NO_THROW(gr1.enleverArc(1,0));
EXPECT_NO_THROW(gr1.enleverArc(1,1));
EXPECT_EQ(0,gr1.getNombreArcs());

EXPECT_FALSE(gr1.arcExiste(0,0));
EXPECT_FALSE(gr1.arcExiste(0,1));
EXPECT_FALSE(gr1.arcExiste(0,2));
EXPECT_FALSE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

// Validation de rajout et d'enlever ces arcs
EXPECT_EQ(0,gr1.getNombreArcs());
gr1.ajouterArc(0,1,200,300,0);
EXPECT_EQ(1,gr1.getNombreArcs());
gr1.ajouterArc(1,2,100,200,3);
EXPECT_EQ(2,gr1.getNombreArcs());
gr1.ajouterArc(2,0,100,200,3);
EXPECT_EQ(3,gr1.getNombreArcs());
gr1.ajouterArc(2,1,100,200,3);
EXPECT_EQ(4,gr1.getNombreArcs());

gr1.enleverArc(2,0);
EXPECT_EQ(3,gr1.getNombreArcs());
gr1.enleverArc(0,1);
EXPECT_EQ(2,gr1.getNombreArcs());
gr1.enleverArc(1,2);
EXPECT_EQ(1,gr1.getNombreArcs());
gr1.enleverArc(2,1);
EXPECT_EQ(0,gr1.getNombreArcs());

EXPECT_FALSE(gr1.arcExiste(0,0));
EXPECT_FALSE(gr1.arcExiste(0,1));
EXPECT_FALSE(gr1.arcExiste(0,2));
EXPECT_FALSE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

EXPECT_EQ(3, gr1.getNombreSommets());
}

TEST(Graphe, arcExiste)
{
TP2::Graphe gr1(3);
gr1.nommer(0, "S1");
gr1.nommer(1, "S2");
gr1.nommer(2, "S3");
EXPECT_EQ(3, gr1.getNombreSommets());
EXPECT_NE(2, gr1.getNombreSommets());

// Vérification qu'aucun arc existe entre les sommets
EXPECT_FALSE(gr1.arcExiste(0,0));
EXPECT_FALSE(gr1.arcExiste(0,1));
EXPECT_FALSE(gr1.arcExiste(0,2));
EXPECT_FALSE(gr1.arcExiste(1,0));
EXPECT_FALSE(gr1.arcExiste(1,1));
EXPECT_FALSE(gr1.arcExiste(1,2));
EXPECT_FALSE(gr1.arcExiste(2,0));
EXPECT_FALSE(gr1.arcExiste(2,1));
EXPECT_FALSE(gr1.arcExiste(2,2));

// Vérification que tous les arcs possible sont bels et bien dans la liste
gr1.ajouterArc(0,0,25,125,-3);
EXPECT_TRUE(gr1.arcExiste(0,0));
gr1.ajouterArc(0,1,50,150,-2);
EXPECT_TRUE(gr1.arcExiste(0,1));
gr1.ajouterArc(0,2,75,175,4-1);
EXPECT_TRUE(gr1.arcExiste(0,2));
EXPECT_EQ(3, gr1.getNombreArcs());
EXPECT_NE(1, gr1.getNombreArcs());

gr1.ajouterArc(1,0,100,200,0);
EXPECT_TRUE(gr1.arcExiste(1,0));
gr1.ajouterArc(1,1,125,225,0);
EXPECT_TRUE(gr1.arcExiste(1,1));
gr1.ajouterArc(1,2,150,250,1);
EXPECT_TRUE(gr1.arcExiste(1,2));
EXPECT_EQ(6, gr1.getNombreArcs());
EXPECT_NE(3, gr1.getNombreArcs());

gr1.ajouterArc(2,0,175,275,2);
EXPECT_TRUE(gr1.arcExiste(2,0));
gr1.ajouterArc(2,1,200,300,3);
EXPECT_TRUE(gr1.arcExiste(2,1));
gr1.ajouterArc(2,2,225,325,4);
EXPECT_TRUE(gr1.arcExiste(2,2));
EXPECT_EQ(9, gr1.getNombreArcs());
EXPECT_NE(4, gr1.getNombreArcs());

// Vérification que des arcs dont la source ou la destination ne sont pas inclus dans la liste des sommets.
EXPECT_THROW(gr1.arcExiste(0,3), std::logic_error);
EXPECT_THROW(gr1.arcExiste(3,2), std::logic_error);
EXPECT_THROW(gr1.arcExiste(-1,3), std::logic_error);
EXPECT_THROW(gr1.arcExiste(100,50), std::logic_error);
}

TEST(Graphe, listerSommetsAdjacents)
{
TP2::Graphe gr1(3);
gr1.nommer(0, "S1");
gr1.nommer(1, "S2");
gr1.nommer(2, "S3");
EXPECT_EQ(3, gr1.getNombreSommets());
EXPECT_NE(2, gr1.getNombreSommets());
EXPECT_EQ(0,gr1.getNombreArcs());

// Ajout des arcs entre le sommet 0 et les 3 autres destinations
gr1.ajouterArc(0,0,200,300,0);
EXPECT_EQ(1,gr1.getNombreArcs());
gr1.ajouterArc(0,1,200,300,0);
EXPECT_EQ(2,gr1.getNombreArcs());
gr1.ajouterArc(0,2,100,200,3);
EXPECT_EQ(3,gr1.getNombreArcs());

// Ajout des arcs entre le sommet 1 et les 3 autres destinations
gr1.ajouterArc(1,0,200,300,0);
EXPECT_EQ(4,gr1.getNombreArcs());
gr1.ajouterArc(1,1,200,300,0);
EXPECT_EQ(5,gr1.getNombreArcs());
gr1.ajouterArc(1,2,100,200,3);
EXPECT_EQ(6,gr1.getNombreArcs());
// Ajout des arcs entre le sommet 2 et les 3 autres destinations

gr1.ajouterArc(2,0,200,300,0);
EXPECT_EQ(7,gr1.getNombreArcs());
gr1.ajouterArc(2,1,200,300,0);
EXPECT_EQ(8,gr1.getNombreArcs());
gr1.ajouterArc(2,2,100,200,3);
EXPECT_EQ(9,gr1.getNombreArcs());

// Validation des sommets adjacents de chacun des sommets (0,1,2)
std::vector<size_t> p_vTest0 = {0,1,2};
std::vector<size_t> p_vTest1 = {0,1,2};
std::vector<size_t> p_vTest2 = {0,1,2};
EXPECT_EQ(p_vTest0, gr1.listerSommetsAdjacents(0));
EXPECT_EQ(p_vTest1, gr1.listerSommetsAdjacents(1));
EXPECT_EQ(p_vTest2, gr1.listerSommetsAdjacents(2));

gr1.enleverArc(0,0);
EXPECT_EQ(8,gr1.getNombreArcs());
std::vector<size_t> p_vTest0modifier = {1,2};
EXPECT_EQ(p_vTest0modifier, gr1.listerSommetsAdjacents(0));

gr1.enleverArc(1,1);
EXPECT_EQ(7,gr1.getNombreArcs());
std::vector<size_t> p_vTest1modifier = {0,2};
EXPECT_EQ(p_vTest1modifier, gr1.listerSommetsAdjacents(1));

EXPECT_NO_THROW(gr1.enleverArc(2,2));
EXPECT_EQ(6,gr1.getNombreArcs());
std::vector<size_t> p_vTest2modifier = {0,1};
EXPECT_EQ(p_vTest2modifier, gr1.listerSommetsAdjacents(2));

EXPECT_THROW(gr1.enleverArc(3,4), std::logic_error);
}


TEST(Graphe, accesseur_nomSommet)
{
TP2::Graphe gr1(2);
EXPECT_EQ(2,gr1.getNombreSommets());
gr1.nommer(0,"S0");


EXPECT_EQ("S0", gr1.getNomSommet(0)) ;
EXPECT_NE("S1", gr1.getNomSommet(0)) ;
EXPECT_EQ("", gr1.getNomSommet(1)) ;
EXPECT_NE("S0", gr1.getNomSommet(1)) ;


EXPECT_NO_THROW(gr1.getNomSommet(0));
EXPECT_NO_THROW(gr1.getNomSommet(1));
EXPECT_THROW(gr1.getNomSommet(2), std::logic_error);
EXPECT_THROW(gr1.getNomSommet(20), std::logic_error);

}

TEST(Graphe, accesseur_numeroSommet)
{
TP2::Graphe gr1(3);
gr1.nommer(0, "S1");
gr1.nommer(1, "S2");
gr1.nommer(2, "S3");

EXPECT_EQ(0,gr1.getNumeroSommet("S1"));
EXPECT_NE(1,gr1.getNumeroSommet("S1"));
EXPECT_EQ(1,gr1.getNumeroSommet("S2"));
EXPECT_NE(2,gr1.getNumeroSommet("S2"));
EXPECT_EQ(2,gr1.getNumeroSommet("S3"));
EXPECT_NE(3,gr1.getNumeroSommet("S3"));


EXPECT_THROW(gr1.getNumeroSommet("S4"), std::logic_error);
EXPECT_NO_THROW(gr1.getNumeroSommet("S1"));
EXPECT_THROW(gr1.getNumeroSommet("0"), std::logic_error);
EXPECT_NO_THROW(gr1.getNumeroSommet("S2"));
EXPECT_THROW(gr1.getNumeroSommet("#?&#$#4"), std::logic_error);
EXPECT_NO_THROW(gr1.getNumeroSommet("S3"));
}

TEST(Graphe, accesseur_nombrSommets)
{
TP2::Graphe gr1(0);
EXPECT_EQ(0, gr1.getNombreSommets()) ;
TP2::Graphe gr2(20);
EXPECT_EQ(20, gr2.getNombreSommets()) ;
EXPECT_NE(20, gr1.getNombreSommets()) ;
}

TEST(Graphe, accesseur_nombreArc)
{
TP2::Graphe gr1(3);
gr1.nommer(0, "S1");
gr1.nommer(1, "S2");
gr1.nommer(2, "S3");

gr1.ajouterArc(0,1,100,200,3);
gr1.ajouterArc(1,2,150,250,5);
EXPECT_EQ(2,gr1.getNombreArcs());
EXPECT_NE(1,gr1.getNombreArcs());
EXPECT_NE(3,gr1.getNombreArcs());

gr1.enleverArc(0,1);
EXPECT_EQ(1,gr1.getNombreArcs());
EXPECT_NE(2,gr1.getNombreArcs());
EXPECT_NE(3,gr1.getNombreArcs());
EXPECT_NE(0,gr1.getNombreArcs());
}


TEST(Graphe, accesseur_PonderationsArc)
{
TP2::Graphe gr1(3);
gr1.nommer(0, "S1");
gr1.nommer(1, "S2");
gr1.nommer(2, "S3");

gr1.ajouterArc(0,0,100,200,3);
gr1.ajouterArc(0,1,150,250,-5);
EXPECT_EQ(2,gr1.getNombreArcs());
EXPECT_NE(1,gr1.getNombreArcs());
EXPECT_NE(3,gr1.getNombreArcs());

gr1.getPonderationsArc(0,0);
EXPECT_EQ(100, gr1.getPonderationsArc(0,0).duree);
EXPECT_EQ(200, gr1.getPonderationsArc(0,0).cout);
EXPECT_EQ(3, gr1.getPonderationsArc(0,0).ns);

gr1.getPonderationsArc(0,1);
EXPECT_EQ(150, gr1.getPonderationsArc(0,1).duree);
EXPECT_EQ(250, gr1.getPonderationsArc(0,1).cout);
EXPECT_EQ(-5, gr1.getPonderationsArc(0,1).ns);

}

TEST(ReseauAerien, ajouterPonderations)
{
    TP2::ReseauAerien unReseau("Test", 5);

    //unReseau.ajouterPonderations(0);
}