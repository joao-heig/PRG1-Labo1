/* PROJET : PRG1-Labo-1
 * AUTEURS : Samuel Fernandez | João Ferreira
 * DESCRIPTION : Programme convertissant un nombre donné textuellement en français
 * DATE DE DÉBUT : 06.11.23
 * ÉCOLE : HEIG-VD
 */

#include "montantEnToutesLettres.h"
#include <cmath>

using namespace std;

string Unit(char n, bool base16 = false, bool hasTen = false);
string Ten(char n);
string Hundred(char n, bool onlyHundred = false);
string ConvertNumberToText(int n, bool continueNumber = false);
short CharToShort(char n);
string NumbersSeparationByThree(long long integerGroup, int i = 0, string result = "");

// Renvoie la totalité de la réponse sous forme textuelle
string montantEnToutesLettres(long double montant)
{
    double fractionalAmount;
    double integerAmount;
    string finalResult;

    const long double MAX_VALUE = 999999999999.99;
    const int ONE_MILLION = 1000000;

    // Gestion des erreurs en amont
    if (montant < 0)
        return "erreur : montant negatif";
    else if ((long long)montant > MAX_VALUE)
        return "erreur : montant trop grand";
    else if (montant == 0)
        return "zero franc";

    // SÉPARATION ENTIER/FRACTION
    montant = round(montant * 100.0) / 100.0;
    fractionalAmount = modf(montant, &integerAmount);

    // Création du texte
    finalResult = NumbersSeparationByThree(integerAmount);

    // Si divisable par 1mio, ajoute "de" au résultat
    if (integerAmount && (long long)montant % (long long)ONE_MILLION == 0)
        finalResult += " de";

    // Si au-dessus de 1, pluriel
    if (integerAmount)
        finalResult += integerAmount <= 1 ? " franc" : " francs";

    // Si franc et centime, ajoute "et
    if (integerAmount && fractionalAmount)
        finalResult += " et ";

    // Si centime
    if (fractionalAmount)
    {
        finalResult += ConvertNumberToText((round(fractionalAmount * 100)));
        finalResult += round(fractionalAmount * 100) <= 1 ? " centime" : " centimes";
    }

    return finalResult;
}

// Permet de séparer la partie entière en groupe de 3 chiffres
string NumbersSeparationByThree(long long integerGroup, int i, string result)
{
    const short THOUSAND_SEPARATOR = 1000;
    // Si le groupe est au-dessus de 0, continue, sinon renvoie le résultat
    if (integerGroup > 0)
    {
        // Si la conversion ne renvoie pas rien
        if(ConvertNumberToText(integerGroup % THOUSAND_SEPARATOR) != "")
        {
            switch (i)
            {
                case 1:
                    result = string("mille") + (result.empty() ? "" : "-") + result;
                    break;
                case 2:
                    result = string(integerGroup == 1 ?  "million" : "millions") + (result.empty() ? "" : "-") + result;
                    break;
                case 3:
                    result = string(integerGroup == 1 ?  "milliard" : "milliards") + (result.empty() ? "" : "-") + result;
                    break;
            }
        }

        if (!(i == 1 && integerGroup % THOUSAND_SEPARATOR == 1 ))
        {
            string temp = ConvertNumberToText(integerGroup % THOUSAND_SEPARATOR, i == 1);

            // Si temp n'est pas vide
            if (!temp.empty())
            {
                // Ajoute à result temp et un tiret si result est vide
                result = temp + (!result.empty() ? "-" : "") + result;
            }
        }
        // Récursive
        return NumbersSeparationByThree(integerGroup / THOUSAND_SEPARATOR, i + 1, result);
    }
    else
        return result;
}

// Convertit un groupe de 3 chiffres en texte
string ConvertNumberToText(int n, bool continueNumber)
{
    string numberToConvert = to_string(n); // Nombre à convertir en string
    string numberConverted = ""; // Nombre renvoyé en texte
    const short MAX_BASE_16 = 7;

    // Rajoute des 0 si besoin afin que le groupe de chiffres soit de 3
    while (numberToConvert.size() < 3)
        numberToConvert = '0' + numberToConvert;

    // Détecte si base 16 (onze douze... seize) ou non et si dix ou non
    bool unitBase16 = (numberToConvert[1] == '1' && CharToShort(numberToConvert[2]) < MAX_BASE_16 && CharToShort(numberToConvert[2]) != 0);
    bool hasTen = (numberToConvert[1] != '0');
    bool onlyHundred = (!continueNumber && (numberToConvert[1] == '0' || numberToConvert[2] == '0'));

    // Crée des variables pour vérifier si chaque chiffre est égal à '0'
    bool isZeroHundreds = (numberToConvert[0] == '0');
    bool isZeroTens = (numberToConvert[1] == '0');
    bool isZeroUnits = (numberToConvert[2] == '0');

    // Centaines
    if(!isZeroHundreds)
    {
        numberConverted += Hundred(numberToConvert[0], onlyHundred);
        // Si dizaine ou unité, ajout d'un tiret
        if (!isZeroTens || !isZeroUnits)
            numberConverted += '-';
    }

    // Dizaines
    if(!isZeroTens && !unitBase16)
    {
        numberConverted += Ten(numberToConvert[1]);
        // Si unité, ajout d'un tiret
        if (!isZeroUnits)
            numberConverted += '-';
    }

    // Unités
    if(!isZeroUnits)
        numberConverted += Unit(numberToConvert[2], unitBase16, hasTen);

    return numberConverted;
}

// Fonction écrivant les unités ou la base 16
string Unit(char n, bool base16, bool hasTen)
{
    if (!base16)
    {
        switch (n)
        {
            // s'il y a un décimal on écrit "et-un"
            case '1': return hasTen ? "et-un" : "un";
            case '2': return "deux"; break;
            case '3': return "trois"; break;
            case '4': return "quatre"; break;
            case '5': return "cinq"; break;
            case '6': return "six"; break;
            case '7': return "sept"; break;
            case '8': return "huit"; break;
            case '9': return "neuf"; break;
            default: return ""; break;
        }
    }
    // Base 16
    else
    {
        switch (n)
        {
            case '1': return "onze"; break;
            case '2': return "douze"; break;
            case '3': return "treize"; break;
            case '4': return "quatorze"; break;
            case '5': return "quinze"; break;
            case '6': return "seize"; break;
            default: return ""; break;
        }
    }
}

// Fonction écrivant les dizaines
// Renvoi un string
string Ten(char n)
{
    switch (n) {
        case '1': return "dix"; break;
        case '2': return "vingt"; break;
        case '3': return "trente"; break;
        case '4': return "quarante"; break;
        case '5': return "cinquante"; break;
        case '6': return "soixante"; break;
        case '7': return "septante"; break;
        case '8': return "huitante"; break;
        case '9': return "nonante"; break;
        default: return ""; break;
    }
}

// Fonction écrivant les centaines au pluriel ou non
string Hundred(char n, bool onlyHundred)
{
    if (n > 0)
        return (CharToShort(n) == 1) ? "cent" : (!onlyHundred ? Unit(n) + "-cent" : Unit(n) + "-cents");
    else
        return "";
}

// Fonction convertissant les char en short
short CharToShort(char n)
{
    return (short)(n - '0');
}




