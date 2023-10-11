/* PROJET : PRG1-Labo-1
 * AUTEURS : Samuel Fernandez | João Ferreira
 * DESCRIPTION : Programme convertissant un nombre donné textuellement en français
 * DATE DE DÉBUT : 06.11.23
 * ÉCOLE : HEIG-VD
 */

#ifndef MONTANT_EN_TOUTES_LETTRES_H
#define MONTANT_EN_TOUTES_LETTRES_H

#include <string>

// Traduit des nombres reels en en toutes lettres
// 'montant' est un reel compris entre 0 et 999'999'999'999.99
// retourne une chaine de caracteres indiquant le montant
// en francs et centimes ou "erreur : " si le montant est
// hors intervalle

std::string montantEnToutesLettres(long double montant);

#endif