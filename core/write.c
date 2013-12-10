
#include <stdio.h>

#include "write.h"
#include "base.h"
#include "master.h"

int waiting_loop()
{
  char inst;
  if ((inst = getchar()) != '\n')
    while (getchar() != '\n');
  return(inst);
}

void print_help()
{
  format_output ("        GUESS: Make another guess, same as before, using the\n",0);
  format_output ("               score from previous guesses to make deductions.\n",0);
  printf ("               You have %d chances to find the right code.\n\n",MAX_TRY);
  format_output ("        REFRESH: Shows all your previous guesses and scores.\n\n",0);
  format_output ("        QUIT: You don't want to play anymore.  Remember, the code\n",0);
  format_output ("              will not be revealed if you quit.\n\n",0);
  format_output ("        PRINT: Display a local help.\n\n",0);
}

void print_instructions_gb()
{
  skipline(2);
  format_output ("                    Instructions for Master Mind\n\n",0);
  format_output ("OBJECT: To match the four color code set by your opponent, using\n",0);
  format_output ("        clues from previous guesses.\n\n",0);
  format_output ("METHOD: Begin by telling the computer whether you wish to guess,\n",0);
  format_output ("        or to create the code which it will guess.  It is usually\n",0);
  format_output ("        more interesting to be the guesser, but I wanted you to \n",0);
  format_output ("        have the option.\n\n",0);
  format_output ("        First, we will cover how to play if you are guessing:\n\n",0);
  format_output ("        You will be asked to specify whether you want 'coaching'.\n",0);
  format_output ("        This means, the computer will tell you whether your guess\n",0);
  format_output ("        is inconsistent with information from previous guesses (it\n",0);
  format_output ("        is considered inconsistent if it cannot be the correct\n",0);
  format_output ("        code, and you could deduce this).\n\n",0);
  
  rest();
  format_output ("        You will then be asked for your first guess.  A guess is\n",0);
  format_output ("        a set of four colors, separated by at least one space. \n",0);
  format_output ("        The valid colors are:\n\n",0);
  format_output ("            black    blue    green    red    white    yellow\n\n",0);
  format_output ("        Note that these spellings must be used exactly.  If you\n",0);
  format_output ("        make a mistake the machine will let you know, and give\n",0);
  format_output ("        another chance.\n\n",0);
  format_output ("        The machine will then return your score for that guess.\n",0);
  format_output ("        Score is given in black and white pegs (b and w).  A black\n",0);
  format_output ("        score peg means that one of your guessed colors is in the\n",0);
  format_output ("        correct place.  A white score peg means that one of your\n",0);
  format_output ("        guessed colors appears in the correct code, but not in\n",0);
  format_output ("        the same location. (If you have selected coaching, that\n",0);
  format_output ("        will occur at this time also.)\n\n",0);
  format_output ("        You will now be given a choice of 'guess, refresh, \n",0);
  format_output ("        or quit'.  Enter your choice.  Either first letter or the\n",0);
  format_output ("        entire word is okay, case is ignored.  If you just hit\n",0);
  format_output ("        return, this is taken as meaning 'guess'.\n",0);
  
  rest();
  print_help();
  skipline(2);
  
  rest();
  format_output ("        Now we will consider how to play if you wish to make up\n",0);
  format_output ("        the code and have the computer guess:\n\n",0);
  format_output ("        You will be asked whether you want the computer to double check\n",0);
  format_output ("        your scoring of its guesses.  If you desire this, each \n",0);
  format_output ("        time you give the computer a score, it score the guess\n",0);
  format_output ("        itself.  If the two scores are different, it will inform\n",0);
  format_output ("        you of your mistake, and the score it generates will re-\n",0);
  format_output ("        place the one you gave.  If you wish your scores checked,\n",0);
  format_output ("        you must enter the correct code, so that the computer has\n",0);
  format_output ("        data to check the scores you give.  Don't worry, I haven't\n",0);
  format_output ("        designed this game to cheat.  The code you enter will be\n",0);
  format_output ("        ignored when the computer makes its guess.\n\n",0);
  format_output ("        If you do not want double checking, you can refuse it.\n",0);
  format_output ("        In this case, any valid score you give will be accepted.\n",0);
  format_output ("        The default value for checking is 'yes'.\n",0);
  format_output ("        The computer will now make its first guess.  You will be\n",0);
  format_output ("        asked for the number of black pegs the guess receives (for\n",0);
  format_output ("        each instance of the right color in the right position),\n",0);
  format_output ("        up to four.  If you do not give a valid answer (0-4), you\n",0);
  format_output ("        will be queried until you do.\n",0);
  
  rest();
  skipline(2);
  format_output ("        If you give three or four black pegs, it is not possible\n",0);
  format_output ("        for any white pegs to be given.  Otherwise, you will be\n",0);
  format_output ("        asked for the number of white pegs until you give a valid\n",0);
  format_output ("        valid answer, zero to (4 - blacks).\n\n",0);
  format_output ("        At this point, if you requested it, your scoring will be\n",0);
  format_output ("        checked by the computer.\n\n",0);
  format_output ("        The computer will continue to guess in this manner, making\n",0);
  format_output ("        certain that each guess is consistent with all previous\n",0);
  format_output ("        information, until it receives a score of four black pegs.\n",0);
  format_output ("        This will generally take from four to seven guesses, but\n",0);
  format_output ("        the machine has been known to get lucky, and break the \n",0);
  format_output ("        code on the second guess.  If at any point the computer\n",0);
  format_output ("        has exhausted all possible guesses, and found none to be\n",0);
  format_output ("        consistent with the information you have given, it will \n",0);
  format_output ("        report this error and end the game.\n\n",0);
  format_output ("        Good luck, and enjoy Master Mind!\n\n",0);
  rest();
}

void print_instructions_fr()
{
  skipline(2);
  format_output("                   Regles du jeu de Master Mind\n\n",0);
  format_output("BUT     : \n",0);
  format_output("          Deviner une combinaison de 4 couleurs choisie par votre adversaire, \n",0);
  format_output("        en utilisant les resultats de vos precedantes tentatives.\n\n",0);
  format_output("METHODE : \n",0);
  format_output("          Tout d'abord, comment jouer a Mastermind :\n\n",0);
  format_output("          Vous devez tout d'abord choisir entre \n",0);
  format_output("                 -1- Deviner des couleurs proposees par la machine. \n",0);
  format_output("                 -2- Proposer a la machine une combinaison de couleurs\n",0);
  format_output("                     qu'elle devra decouvrir.\n\n",0);
  format_output("          1-Comment deviner une sequence de couleurs proposees par la machine ?\n",0);
  format_output("        La machine peut vous indiquer si votre choix est coherent avec les resul-\n",0);
  format_output("        tats issus des precedantes tentatives (un choix est incoherent si il \n",0);
  format_output("        contredit les resultats deja obtenus).\n\n",0);
  
  rest();
  format_output("          On vous demandera votre premier choix.Un choix est une combinaison\n",0);
  format_output("        de quatre couleurs,separees par au moins un blanc. \n",0);
  format_output("          Les six couleurs possibles sont :\n\n",0);
  format_output("            black    blue    green    red    white    yellow\n\n",0);
  format_output("          Chaque couleur devra etre ecrite en entier.Si une erreur est faite \n",0);
  format_output("        la machine vous le faira savoir, et vous donnera une nouvelle chance.\n",0);
  format_output("        Vos resultats seront alors affiches.\n",0);
  format_output("          Le score s'inscrira par l'intermediaire de batonnets blancs et noirs \n",0);
  format_output("        (b et n).Un batonnet noir signifie qu'une des couleurs choisie est a la\n",0);
  format_output("        bonne place.\n",0);
  format_output("          Un batonnet blanc signifie qu'une couleur choisie appartient a la combi-\n",0);
  format_output("        naison gagnante, mais est proposee a la mauvaise place.\n\n",0);
  format_output("          Vous aurez alors le choix entre 'guess, print, refresh ou quit'.Pour \n",0);
  format_output("        donner votre choix, la premiere lettre suffit.Les majuscules sont ignorees. \n",0);
  format_output("        Un simple retour chariot signifie 'guess'.\n \n",0);
  
  rest();
  format_output("        GUESS : Faire un autre choix de couleurs.\n",0);
  printf("                Vous avez %d chances pour trouver la bonne combinaison.\n\n",MAX_TRY);
  format_output("        PRINT : Affiche une aide locale.\n",0);
  format_output("        REFRESH : Affiche vos precedantes tentatives ainsi que leurs score.\n\n",0);
  format_output("        QUIT   : Vous ne voulez plus jouer.Le code ne sera pas revele\n",0);
  format_output("                si vous abandonnez.\n\n",0);
  
  rest();
  format_output("          2-Considerons maintenant le cas ou vous proposez la sequence de couleur a\n",0);
  format_output("        la machine.\n\n",0);
  format_output("          On vous demandera si vous desirez une verification de vos reponses par la \n",0);
  format_output("        la machine.Dans ce cas, chacune de vos reponses sera suivie du score calcule \n",0);
  format_output("        par la machine.Si ces 2 scores sont differents, la machine le signale et rem-\n",0);
  format_output("        place le mauvais score par le bon.\n",0);
  format_output("        ne vous inquietez pas, je n'ai pas concu ce jeu pour tricher, les couleurs que\n",0);
  format_output("        vous proposez ne sont pas connues da la machine quand elle propose une combinai-\n",0);
  format_output("        son.Si vous refusez cette aide, vos scores seront toujours acceptes.Pour chaque\n",0);
  format_output("        proposition de la machine, vous devez donner le nombre de batonnets noirs (bonne\n",0);
  format_output("        couleur et bonne place) correspondants.On vous redemandera la reponse si celle-ci\n",0);
  format_output("        se revele incorrecte (non comprise entre 0 et 4 ).\n",0);
  
  rest();
  skipline(2);
  format_output("          Si vous repondez par 3 ou 4 batonnets noirs, il ne sera alors pas possible de\n",0);
  format_output("        repondre avec des batonnets blancs.Dans les autres cas, on vous demandera le nombre\n",0);
  format_output("        de batonnets blancs.\n\n",0);
  format_output("          Vous pouvez toujours demander la verification du score par la machine.\n\n",0);
  format_output("          La machine trouve la bonne combinaison en environ sept essais.Si d'aventure\n",0);
  format_output("        elle ne trouve plus de combinaison a proposer coherente avec vos reponses.Elle\n",0);
  format_output("        signalera l'anomalie et mettra fin au jeu.\n",0);
  
  rest();
  format_output("        Bonne chance, et amusez-vous avec Master Mind!\n\n",0);

  rest();
}

int instruction()
{
    char inst;
    char lang;
    int ok = 0;
    
    format_output("Would you like instructions, y/n [default is n]-> ",0);
    inst = waiting_loop();
    if (inst != 'y' && inst != 'Y')
    {
      ok = 1;
      return(ok);
    }
    format_output("In which language,e(nglish)/f(rench)/i(talian)/g(erman)/b(elgian)/r(ussian) [default is e(nglish)]-> ",0);
    lang = waiting_loop();
    switch (lang)
      {
      case 'r':
      case 'R':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output("You really thought you could get russian  \n",0);
	    ok = 1;
	    return(ok);
	  }	
      case 'i':
      case 'I':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output("  I was joking   \n",0);
	    ok = 1;
	    return(ok);
	  }
      case 'g':
      case 'G':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output("  I don't understand  \n",0);
	    ok = 1;
	    return(ok);
	  }
      case 'b':
      case 'B':
	format_output("Are you sure? y/n [default is n]-> ",0);
	inst = waiting_loop();
	if (inst == 'n' || inst == 'N')
	  return(0);
	else
	  {
	    format_output(" Are you (w)alloon ou (f)lemish ?   \n",0);
	    inst = waiting_loop();
	    if (inst == 'f' || inst == 'F')
	      {
		format_output("Sorry, i never learnt flemish\n",0);
		ok = 1;
		return(ok);
	      }
	    else
	      {
		print_instructions_fr();
		ok = 1;
		return(ok);
	      }
	    print_instructions_fr();
	    ok = 1;
	    return(ok);
	  }
      case 'f':
      case 'F':
	print_instructions_fr();
	break;
      case 'e':
      case 'E':
	print_instructions_gb();
	break;
      default:
	print_instructions_gb();
	break;
      }
    ok = 1;
    return(ok);
}
