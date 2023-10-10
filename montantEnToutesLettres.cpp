#include "montantEnToutesLettres.h"
#include <cmath>
#include <iostream>

// A FAIRE
// GERER LES TIRETS
// BLOQUER NOMBRES NEGATIFS/ TROP GRANDS/ INVALIDES AVEC LE TYPE D'ERREUR
// GERER LE 0
// OPTIMISER
using namespace std;

string Unit(char n, bool base16 = false, bool hasTen = false);
string Ten(char n);
string Hundred(char n);
string ConvertNumberToText(int n, bool continueNumber = false);
short CharToShort(char n);
string NumbersSeparationByThree(double n);


string montantEnToutesLettres(long double montant)
{
    double fractionalAmount; // Contenant de la fraction
    double integerAmount; // Contenant de l'entier
    string fractionalText;
    string integerText;
    string finalResult;

    // Arrondi à 2
    montant = round(montant * 100.0) / 100.0;

    // Séparation de l'entier et de la fraction
    fractionalAmount = modf(montant, &integerAmount);

    finalResult = NumbersSeparationByThree(integerAmount);

    if (integerAmount)
        finalResult += " francs";

    if (integerAmount && fractionalAmount)
        finalResult += " et ";

    if (fractionalAmount)
        finalResult += ConvertNumberToText((round(fractionalAmount * 100))) + " centimes.";

    return finalResult;

    //return "zero franc"s;
}

// TOUJOURS PROBLEME TIRET

// Écrit du texte pour chaque groupe de 3 nombres, et ajoute le préfixe (mille, millions, milliards, etc...)
string NumbersSeparationByThree(double n)
{
    // Variable contenant les différents groupes
    long long integerGroup = n;
    short numberType = 0; // 1 = mille, 2 = millions 3 = billions
    string result;

    // Ajoute l'écriture et les préfixes (mille/million/milliard)
    for (int i = 0; integerGroup > 0; i++)
    {
        if(ConvertNumberToText(integerGroup % 1000) != "")
        {
            // Suivant la valeur de i, ajoute mille/million/milliard
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


        // Si supérieur ou égal à 1, écrit du texte && gère les exceptions de mille
        if (integerGroup >= 1 && !(i == 1 && integerGroup % 1000 == 1 ))
            result = ConvertNumberToText(integerGroup % 1000, integerGroup >= 1) + (!result.empty() ? "-" : "") + result;

        integerGroup /= 1000; // Division par 1000

    }

    return result;
}



string ConvertNumberToText(int n, bool continueNumber)
{
    string numberToConvert = to_string(n); // Nombre à convertir en string
    string numberConverted = ""; // Nombre renvoyé en texte
    short numberLength = numberToConvert.size();

    for (int i = 0; i <= 2 - numberLength; ++i)
        numberToConvert = '0' + numberToConvert;

    // Détecte si base 16 (onze douze... seize) ou non et si dix ou non
    bool unitBase16 = (numberToConvert[1] == '1' && CharToShort(numberToConvert[2]) < 7 && CharToShort(numberToConvert[2]) != 0);
    bool hasTen = (numberToConvert[1] != '0');

    // Centaines
    if(numberToConvert[0] != '0')
    {
        numberConverted += Hundred(numberToConvert[0]);

        // Si dizaine ou unité, ajout d'un tiret
        if (numberToConvert[1] != '0' || numberToConvert[2] != '0')
            numberConverted += '-';
    }

    // Dizaines
    if(numberToConvert[1] != '0' && !unitBase16)
    {
        numberConverted += Ten(numberToConvert[1]);

        // Si unité, ajout d'un tiret
        if (numberToConvert[2] != '0')
            numberConverted += '-';
    }

    // Unités
    if(numberToConvert[2] != '0')
        numberConverted += Unit(numberToConvert[2], unitBase16, hasTen);

    if (continueNumber)
        numberToConvert += '-';

    return numberConverted;
}

// Fonction écrivant les unités ou la base 16
// Renvoi un string
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

// Fonction écrivant les centaines
// Renvoi un string
string Hundred(char n)
{
    if (n > 0)
        return (int)n - '0'  == 1 ?  "cent" : Unit(n) + "-cents";
    else
        return "";
}

// Fonction convertissant les char en short
short CharToShort(char n)
{
    return (short)(n - '0');
}




