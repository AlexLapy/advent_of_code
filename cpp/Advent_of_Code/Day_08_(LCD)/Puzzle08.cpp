#include "Puzzle08.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>



// 493
void Puzzle08::PrintSolutionA()
{
	std::cout << FindUniqueNumbers() << '\n';
}

// 1010460
void Puzzle08::PrintSolutionB()
{
	std::cout << SumOffAllOutputs() << '\n';
}

Puzzle08::Puzzle08()
	: Input(Utilities::ReadAllLinesInFile("input_08.txt"))
{
}

int Puzzle08::FindUniqueNumbers()
{
    std::vector<std::string> In;
    std::vector<std::string> Out;

    for (auto line : Input)
    {
    In.push_back(Utilities::SplitString(line, "|")[0]);
    Out.push_back(Utilities::SplitString(line, "|")[1]);
    }


    int UniqueNubers = 0;
    for (auto line : Out)
    {
        auto Splited = Utilities::SplitString(line, " ");
        for (auto segments : Splited)
        {
            if (segments.size() == 2 | segments.size() == 3 |
                segments.size() == 4 | segments.size() == 7 )
            {
                ++UniqueNubers;
            }
        }
    }

    
    return UniqueNubers;
}


// Maps segments to be ON to display number
const std::unordered_map<std::string, int> SegmentsToDigits =
{
	{ "abcefg",  0 },
	{ "cf",      1 },
	{ "acdeg",   2 },
	{ "acdfg",   3 },
	{ "bcdf",    4 },
	{ "abdfg",   5 },
	{ "abdefg",  6 },
	{ "acf",     7 },
	{ "abcdefg", 8 },
	{ "abcdfg" , 9 }
};

// Maps number of segments to possible pattern with that many segmetns
const std::unordered_map<int, std::set<char>> PatternSignalLenghtToPossibleSegment =
{
	{ 2, std::set<char> { 'c', 'f' }},
	{ 3, std::set<char> { 'a', 'c', 'f' }},
	{ 4, std::set<char> { 'b', 'c', 'd', 'f' }},
	{ 5, std::set<char> { 'a', 'b', 'c', 'd', 'e', 'f', 'g' }},
	{ 6, std::set<char> { 'a', 'b', 'c', 'd', 'e', 'f', 'g' }},
	{ 7, std::set<char> { 'a', 'b', 'c', 'd', 'e', 'f', 'g' }},
};

//   c  f
// a c  f
//  bcd f
// a cde g
// a cd fg
// ab d fg
// ab defg
// abc efg 
// abcd fg 
// abcdefg
// 8687497  sums

// Map total references to a given scrambled segment to the possible unscrambled segments
const std::unordered_map<int, std::set<char>> TotalSegmentReferencesToPossibleSegment =
{
	{ 4, std::set<char> { 'e' }},
	{ 6, std::set<char> { 'b' }},
	{ 7, std::set<char> { 'd', 'g' }},
	{ 8, std::set<char> { 'a', 'c' }},
	{ 9, std::set<char> { 'f' }},
};



int Puzzle08::SumOffAllOutputs()
{
    // Variable pour la reponse finale
    int SumOfOutputs = 0; 

    // Declare un dictionaire avec key=char et value=set{}
    // Permet de trouver la 'vrai' valeur du caractere (les fils sont mixer)
    std::unordered_map<char, std::set<char>> InitialScrambledSegmentsToPossibleSegment;
    for (char CurrentSegment = 'a'; CurrentSegment <= 'g'; ++CurrentSegment)
    {
        InitialScrambledSegmentsToPossibleSegment[CurrentSegment] = 
                                    std::set<char>{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
    }


    // Main loop
    // Pour chaque ligne, on trouve les bonnes combinaisons et trouve le output
    for (const std::string& Line : Input)
    {
        // On Separe les input des output
        std::vector<std::string> SplitLine = Utilities::SplitString(Line, " | ");

        // On commence avec les input
        std::vector<std::string> ScrambledPatternSignals = Utilities::SplitString(SplitLine[0], " ");

        // On cree une copy du premier dictionnaire (pas tres utile)
        std::unordered_map<char, std::set<char>> ScrambledSegmentsToPossibleSegments = 
                                                    InitialScrambledSegmentsToPossibleSegment;
        
        /*
            Premier   algo: On "prune", selon la longueur de la combinaison
            Deuxieme  algo: On "prune", selon le nombre total de reference que peut avoir un caratere
            Troisieme algo: On "prune", selon ce que l'on connais ( a=g et b=f|g --> b=f)
        */
        PruneUsingPatternSignalLenght(ScrambledSegmentsToPossibleSegments, ScrambledPatternSignals);
        PruneUsingTotalSegmentReference(ScrambledSegmentsToPossibleSegments, ScrambledPatternSignals);
        PruneUsingKnownSegment(ScrambledSegmentsToPossibleSegments);

        // On cree un dictionaire ayant key=TrueChar value=FakeChar
        std::unordered_map<char, char> ScrambledSegmentsToSegments;
        for (char Segment = 'a'; Segment <= 'g'; ++Segment)
        {
            // On cree un set ayant le Fakechar
            const std::set<char>& PossibleSegments = ScrambledSegmentsToPossibleSegments[Segment];
            // *var.begin() == var[0]
            // On ajoute le FakeChar a la key du TrueChar
            ScrambledSegmentsToSegments[Segment] = *PossibleSegments.begin(); 
        }

        // On s'occupe maintenant de la deuxieme partie --> le output
        std::vector<std::string> ScrambledOutputs = Utilities::SplitString(SplitLine[1], " ");

        // Declare un vecteur de string "Global" Outputs
        std::vector<std::string> Outputs;
        // On boucle tous les combinaisons d'output (4)
        for (const std::string& ScrambledOutput: ScrambledOutputs)
        {
            // On declare un string "InScope" Output
            std::string Output;
            // On boucle tous les carateres de la combinaison
            for (char Segment : ScrambledOutput)
            {   
                // On ajoute les vrais caracteres dans Output
                Output += ScrambledSegmentsToSegments.at(Segment);
            }
            // On tri les caracteres afin de comparer a notre premier set "SegmentsToDigits"
            std::sort(Output.begin(), Output.end());

            // On ajoute la Vrai combinaison trier dans Outputs
            Outputs.push_back(Output);

        }



        // On declare une variable temporaire pour compter la valeur du CurrentOutput
        int CurrentOutputValue = 0;

        // On boucle toutes les ombinaisons dans le vecteur Outputs 
        for (const std::string &Output: Outputs)
        {
            // On utilise le set "SegmentsToDigits" afin de trouver la valeur selon la combinaison
            int CurrrentDigit = SegmentsToDigits.at(Output);

            // On multiplie par 10 car on veut pas aditionner, mais plutot concactener "123" et non "6"
            CurrentOutputValue = CurrentOutputValue * 10 + CurrrentDigit;
        }

        // On Ajoute chaques outputs concatener pour avoir une somme finale
        SumOfOutputs += CurrentOutputValue;
    }

    return SumOfOutputs;

}

void Puzzle08::PruneUsingPatternSignalLenght(
    std::unordered_map<char, std::set<char>>& ScrambledSegmentsToPossibleSegments,
    std::vector<std::string> ScrambledPatternSignals)
{
    // Pout toute les combinaison en input
    for (const std::string& ScrambledPatternSignal : ScrambledPatternSignals)
    {   
        // On regarde la longueur de la combinaison
        int PatternSignalLenght = static_cast<int>(ScrambledPatternSignal.size());
        // On boucle toute les caractere de la combinaison
        for (char ScrambledSegment : ScrambledPatternSignal)
        {   
            // On cree un set (avec pointeur, donc pas une copy)
            // La valeur du set est la valeur de la key--> qui est le caratere en cours de verification
            // Donc { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } , au depart
            std::set<char>& PossibleSegments = ScrambledSegmentsToPossibleSegments[ScrambledSegment];

            // Selon la longueur du segment, on peut (si 2,3,4) "pruner" notre dictionaire finale 
            PossibleSegments = Intersection(PossibleSegments, PatternSignalLenghtToPossibleSegment.at(PatternSignalLenght));

        }
    }
}

void Puzzle08::PruneUsingTotalSegmentReference(
    std::unordered_map<char, std::set<char>>& ScrambledSegmentsToPossibleSegments,
    std::vector<std::string> ScrambledPatternSignals)
{
    // On cree un dictionnaire key=char et value=int
    std::unordered_map<char, int> SegmentToCount;

    // On boucle tous les combinaison dans le input
    for (const std::string& ScrambledPatternSignal : ScrambledPatternSignals)
    {
        // On boucle tous les caracteres
        for (char ScrambledSegment : ScrambledPatternSignal)
        {
        // if not found
        if (SegmentToCount.find(ScrambledSegment) == SegmentToCount.end())
        {
            // On ajoute la key
            SegmentToCount.emplace(ScrambledSegment, 0);
        }
        // Dans tous les cas on augmente le compteur
        ++SegmentToCount[ScrambledSegment];
        }
    }

    // On a donc un dictionnaire avec tous les caracteres et leur nombre de reference

    // On boucle de 'a' a 'g'
    for (char Segment = 'a'; Segment <= 'g'; ++Segment)
    {   
        // On regarde le nombre de reference de la lettre
        int SegmentCount = SegmentToCount.at(Segment);

        // On cree un set (avec pointeur, donc pas une copy)
        // La valeur du set est la valeur de la key --> qui est le caratere en cours de verification
        // Donc { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } , au depart
        std::set<char>& PossibleSegments = ScrambledSegmentsToPossibleSegments[Segment];

        // Selon le nombre de reference du segment, on peut "pruner" notre dictionaire finale 
        PossibleSegments = Intersection(PossibleSegments, TotalSegmentReferencesToPossibleSegment.at(SegmentCount));
    }
}

void Puzzle08::PruneUsingKnownSegment(
    std::unordered_map<char, std::set<char>> &ScrambledSegmentsToPossibleSegments)
{
    // On boucle de 'a' a 'g'
    for (char Segment = 'a'; Segment <= 'g'; ++Segment)
    {
        // On cree un set (avec pointeur, donc pas une copy)
        // La valeur du set est la valeur de la key --> qui est le caratere en cours de verification
        // Donc { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } , au depart
        std::set<char> &PossibleSegments = ScrambledSegmentsToPossibleSegments[Segment];

        // Si on a pas encore trouver la vrai valeur du segment on continue a boucler
        if (PossibleSegments.size() != 1)
        {
            continue;
        }

        // Si on connais la vrai valeur, on la note
        char SolvedSegment = *PossibleSegments.begin();

        // On boucle de 'a' a 'g'
        for (char SegmentToRemovePossibility = 'a'; SegmentToRemovePossibility <= 'g'; ++SegmentToRemovePossibility)
        {
            // On continue si cest le segment qu'on connais
            if (Segment == SegmentToRemovePossibility)
			{
				continue;
			}

           // On enleve la lettre dans tous les autres cas
           ScrambledSegmentsToPossibleSegments[SegmentToRemovePossibility].erase(SolvedSegment); 
        }
    }
}



std::set<char> Puzzle08::Intersection(const std::set<char> &Left, const std::set<char> &Right)
{
    // Cree un set temporaire
    std::set<char> Result;
    // On garde seulement les caractere present dans les 2 sets
    // Le premier etant notre set final
    // Le deuxieme etant l<une des trois sets de comparaison
    std::set_intersection(Left.begin(), Left.end(), 
                          Right.begin(), Right.end(),
                          std::inserter(Result, Result.begin()));
    return Result;
}