#include "montantEnToutesLettres.h"
#include <cmath>
#include <iostream>

using namespace std;

string Unit(char n, bool base16 = false, bool hasTen = false);
string Ten(char n);
string Hundred(char n);
string ConvertNumberToText(int n);
short CharToShort(char n);

string montantEnToutesLettres(long double montant)
{
    double fractionalAmount; // Contenant de la fraction
    double integerAmount; // Contenant de l'entier
    string fractionalText;
    string integerText;
    string finalResult;

    // Arrondi à 2
    integerAmount = round(montant * 100.0) / 100.0;

    // Séparation de l'entier et de la fraction
    fractionalAmount = modf(integerAmount, &integerAmount);

    if (integerAmount)
        finalResult += ConvertNumberToText(integerAmount) + " francs";

    if (integerAmount && fractionalAmount)
        finalResult += " et ";

    if (fractionalAmount)
        finalResult += ConvertNumberToText((round(fractionalAmount * 100))) + " centimes.";

    return finalResult;

    //return "zero franc"s;
}

string ConvertNumberToText(int n)
{
    string numberToConvert = to_string(n); // Nombre à convertir en string
    string numberConverted = ""; // Nombre renvoyé en texte
    short numberLength = numberToConvert.size();

    for (int i = 0; i <= 2 - numberLength; ++i)
        numberToConvert = '0' + numberToConvert;

    // Détecte si base 16 (onze douze... seize) ou non et si dix ou non
    bool unitBase16 = (numberToConvert[1] == '1' && CharToShort(numberToConvert[2]) < 7 && CharToShort(numberToConvert[2]) != 0);
    bool hasTen = (numberToConvert[1] != '0');
    cout << boolalpha << hasTen << endl;
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
        return (int)n - '0'  == 1 ?  "cent" : Unit((char)(n)) + "-cents";
    else
        return "";
}

// Fonction convertissant les char en short
short CharToShort(char n)
{
    return (short)(n - '0');
}




