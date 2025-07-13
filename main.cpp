#include "gui/desktop/view.h"

/** @mainpage SNAKE
 *
 * Snake is a genre of action video games where the player maneuvers the end of a growing line, 
 * often themed as a snake. The player must keep the snake from colliding with both other 
 * obstacles and itself, which gets harder as the snake lengthens.
 * The genre originated in the 1976 competitive arcade video game Blockade from Gremlin 
 * Industries where the goal is to survive longer than the other player. Blockade and the 
 * initial wave of clones that followed were purely abstract and did not use snake terminology. 
 * The concept evolved into a single-player variant where a line with a head and tail gets 
 * longer with each piece of food eaten—often apples or eggs—increasing the likelihood of 
 * self-collision. The simplicity and low technical requirements of snake games have resulted 
 * in hundreds of versions, some of which have the word snake or worm in the title. The 1982 
 * Tron arcade video game, based on the film, includes snake gameplay for the single-player 
 * Light Cycles segment, and some later snake games borrow the theme.
 * After a version simply called Snake was preloaded on Nokia mobile phones in 1998, there 
 * was a resurgence of interest in snake games
 */

/** @brief Entrypoint
 *
 * Main fuction that starts snake game.
 *
 * Desktop interface is to be initialized, datafile to be opened and
 * main structure of the game to be created here.
 * 
 * @param argc argument count of command line arguments are passed to main().
 * 
 * @param argv argument vector which stores command line arguments are passed to main().
 *
 * @return specific output values, errors codes executable program.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    s21::MainWindow view(nullptr);

    view.show();

    return a.exec();
}
