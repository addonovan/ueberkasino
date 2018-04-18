#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Text_Display.H>
#include <iostream>
#include <sstream>
#include <network.hpp>
#include <player.hpp>
//using namespace UberCasino;

Fl_Window startWindow(30, 30, 800, 600, "Über Kasino");
std::string purse = "200";
std::string betAmount = "0";
Fl_Text_Buffer *tbbuff = new Fl_Text_Buffer();
Fl_Text_Buffer *tmbuff = new Fl_Text_Buffer();
int betAmountG = 0;
int purseG = 0;
UberCasino::Player player;



/*================================================== H E L P   M E N U ==================================================
=======================================================================================================================*/

void howButton_callback(Fl_Widget*, void* a)
{
	(void)(a);
	Fl_Text_Display::Style_Table_Entry stable[] = {
		{	FL_BOLD,		FL_HELVETICA,	18,	0u},
		{	FL_ITALIC,		FL_HELVETICA, 	18, 0u},
		{	FL_BLACK,		FL_HELVETICA,	18, 0u},
	};

	Fl_Window howWindow(30, 30, 800, 600, "How To");	
	howWindow.color(0x00500000);

	Fl_Box *box = new Fl_Box(300, 10, 200, 50, "How to Play");
	box->box(FL_NO_BOX);
	box->labelfont(FL_BOLD+FL_HELVETICA);
	box->labelsize(20);

	Fl_Text_Display *help = new Fl_Text_Display(20, 60, 760, 520);
	Fl_Text_Buffer *tbuff = new Fl_Text_Buffer();
	Fl_Text_Buffer *sbuff = new Fl_Text_Buffer();
	help->buffer(tbuff);
	int stable_size = sizeof(stable)/sizeof(stable[0]);
	help->highlight_data(sbuff, stable, stable_size, 'A', 0, 0);

	tbuff->text("Blackjack starts with players making bets.\n"
				"Dealer deals 2 cards to the players face up\nand two to himself (1 card face up, the other face down).\n\n"

				"Blackjack card values: Numerical cards count their face value in blackjack.\n"
				"Face cards count as 10 and the ace can count as either 1 or 11.\n"
				"The total of any hand is the sum of the card values in the hand.\n\n"

				"Players must decide whether to hit, stand, double down, or split.\n"
				"Hit: Take another card from the dealer.\n"
				"Stand: Keep your hand as it is.\n"
				"Double Down: Take only one more card from the dealer and double the orignal bet.\n"
				"Split: Split your orignal hand into two new hands.\n"
				"Can only split when the orignal hand contains two cards of the same value.\n\n"

				"The dealer acts last and must hit on 16 or less and stand on 17 through 21.\n"
				"Players win when their hand totals higher than dealer’s hand,\nor they have 21 or less when the dealer busts\n");

	sbuff->text("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\nCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n\n"

				"AAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n\n"

				"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"AAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"AAAAAACCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"AAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"AAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n\n"

				"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n"
				"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\nCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n");

	howWindow.end();
	howWindow.show();
	Fl::run();
}

/*================================================== G A M E   S C R E E N ==================================================
===========================================================================================================================*/
void bet1_callback(Fl_Widget*, void* v)
{
	(void)(v);
	std::stringstream betChange(betAmount);

	betChange >> betAmountG;
	betAmountG += 1;

	std::stringstream betAmount;
	betAmount << betAmountG;
	::betAmount = betAmount.str();
	tbbuff->text(::betAmount.c_str());


	std::stringstream walletChange(purse);

	walletChange >> purseG;	
	purseG -= 1;

	std::stringstream purse;
	purse << purseG;
	::purse = purse.str();
	tmbuff->text(::purse.c_str());
}

void bet5_callback(Fl_Widget*, void* v)
{
	(void)(v);
	std::stringstream betChange(betAmount);

	betChange >> betAmountG;
	betAmountG += 5;

	std::stringstream betAmount;
	betAmount << betAmountG;
	::betAmount = betAmount.str();
	tbbuff->text(::betAmount.c_str());


	std::stringstream walletChange(purse);

	walletChange >> purseG;	
	purseG -= 5;

	std::stringstream purse;
	purse << purseG;
	::purse = purse.str();
	tmbuff->text(::purse.c_str());	
}

void bet10_callback(Fl_Widget*, void* v)
{
	(void)(v);
	std::stringstream betChange(betAmount);

	betChange >> betAmountG;
	betAmountG += 10;

	std::stringstream betAmount;
	betAmount << betAmountG;
	::betAmount = betAmount.str();
	tbbuff->text(::betAmount.c_str());


	std::stringstream walletChange(purse);

	walletChange >> purseG;	
	purseG -= 10;

	std::stringstream purse;
	purse << purseG;
	::purse = purse.str();
	tmbuff->text(::purse.c_str());	
}

void bet50_callback(Fl_Widget*, void* v)
{
	(void)(v);
	std::stringstream betChange(betAmount);

	betChange >> betAmountG;
	betAmountG += 50;

	std::stringstream betAmount;
	betAmount << betAmountG;
	::betAmount = betAmount.str();
	tbbuff->text(::betAmount.c_str());


	std::stringstream walletChange(purse);

	walletChange >> purseG;	
	purseG -= 50;

	std::stringstream purse;
	purse << purseG;
	::purse = purse.str();
	tmbuff->text(::purse.c_str());	
}

void clear_callback(Fl_Widget*, void* v)
{
	(void)(v);
	std::stringstream walletChange(purse);
	std::stringstream betChange(betAmount);

	walletChange >> purseG;
	betChange >> betAmountG;	
	purseG = purseG + betAmountG;

	std::stringstream purse;
	purse << purseG;
	::purse = purse.str();
	tmbuff->text(::purse.c_str());


	betAmountG = 0;

	std::stringstream betAmount;
	betAmount << betAmountG;
	::betAmount = betAmount.str();
	tbbuff->text(::betAmount.c_str());
}

void hit_callback(Fl_Widget*, void* v)
{
	std::cout << "I hit\n";
	(void)(v);
}

void stand_callback(Fl_Widget*, void* v)
{
	std::cout << "I stand\n";
	(void)(v);
}

void dbldown_callback(Fl_Widget*, void* v)
{
	std::cout << "I double down\n";
	(void)(v);
}

void playButton_callback(Fl_Widget*, void* a)
{
	(void)(a);

	/***************************************** S T Y L E   T A B L E ****************************************
	********************************************************************************************************/
	Fl_Text_Display::Style_Table_Entry stable[] = {
		{	FL_BOLD,		FL_HELVETICA,	18,	0u},
		{	FL_ITALIC,		FL_HELVETICA, 	18,	0u},
		{	FL_BLACK,		FL_HELVETICA,	18, 0u},
		{	FL_BLACK,		FL_HELVETICA,	34,	0u},
		{	FL_BLACK,		FL_HELVETICA,	12,	0u},
	};


	Fl_Window playWindow(30, 30, 800, 600, "Black Jack");
	playWindow.color(0x00500000);

	Fl_Box *box = new Fl_Box(250, 5, 300, 100, "Black Jack!");
	box->box(FL_NO_BOX);
	box->labelfont(FL_BOLD+FL_HELVETICA);
	box->labelsize(30);
	box->labeltype(FL_SHADOW_LABEL);

	/***************************************** P L A Y E R   A C T I O N S ****************************************
	**************************************************************************************************************/
	Fl_Button *hitButton = new Fl_Button(600, 470, 60, 60, "HIT");
	hitButton->box(FL_OVAL_BOX);
	hitButton->color(FL_BLACK);
	hitButton->labelcolor(FL_LIGHT1);
	hitButton->labelfont(FL_BOLD);
	hitButton->callback(hit_callback);	

	Fl_Button *standButton = new Fl_Button(650, 420, 60, 60, "STAND");
	standButton->box(FL_OVAL_BOX);
	standButton->color(FL_BLACK);
	standButton->labelcolor(FL_LIGHT1);
	standButton->labelfont(FL_BOLD);
	standButton->callback(stand_callback);		

	Fl_Button *dbldownButton = new Fl_Button(700, 470, 60, 60, "DBL\nDOWN");
	dbldownButton->box(FL_OVAL_BOX);
	dbldownButton->color(FL_BLACK);
	dbldownButton->labelcolor(FL_LIGHT1);
	dbldownButton->labelfont(FL_BOLD);
	dbldownButton->callback(dbldown_callback);	

	/***************************************** P L A Y I N G   S T Y L E S ****************************************
	**************************************************************************************************************/
	Fl_Box *playingBox = new Fl_Box(540, 70, 300, 100, "Playing Styles");
	playingBox->box(FL_NO_BOX);
	playingBox->labelfont(FL_BOLD+FL_HELVETICA);
	playingBox->labelsize(20);

	Fl_Round_Button *manualButton = new Fl_Round_Button(625, 150, 20, 20, "Manual");
	manualButton->type(FL_RADIO_BUTTON);
	manualButton->color(FL_BLACK);
	manualButton->labelcolor(FL_BLACK);
	manualButton->labelfont(FL_BOLD);

	Fl_Round_Button *conservativeButton = new Fl_Round_Button(625, 175, 20, 20, "Conservative");
	conservativeButton->type(FL_RADIO_BUTTON);
	conservativeButton->color(FL_BLACK);
	conservativeButton->labelcolor(FL_BLACK);
	conservativeButton->labelfont(FL_BOLD);

	Fl_Round_Button *recklessButton = new Fl_Round_Button(625, 200, 20, 20, "Reckless");
	recklessButton->type(FL_RADIO_BUTTON);
	recklessButton->color(FL_BLACK);
	recklessButton->labelcolor(FL_BLACK);
	recklessButton->labelfont(FL_BOLD);

	Fl_Round_Button *traditionalButton = new Fl_Round_Button(625, 225, 20, 20, "Traditional");
	traditionalButton->type(FL_RADIO_BUTTON);
	traditionalButton->color(FL_BLACK);
	traditionalButton->labelcolor(FL_BLACK);
	traditionalButton->labelfont(FL_BOLD);	

	Fl_Round_Button *countingButton = new Fl_Round_Button(625, 250, 20, 20, "Card Counting");
	countingButton->type(FL_RADIO_BUTTON);
	countingButton->color(FL_BLACK);
	countingButton->labelcolor(FL_BLACK);
	countingButton->labelfont(FL_BOLD);

	/***************************************** M O N E Y   D I S P L A Y S ****************************************
	**************************************************************************************************************/
	Fl_Text_Display *money = new Fl_Text_Display(600, 300, 160, 50);
	Fl_Text_Buffer *smbuff = new Fl_Text_Buffer();
	money->buffer(tmbuff);
	int stable_sizeM = sizeof(stable)/sizeof(stable[0]);
	money->highlight_data(smbuff, stable, stable_sizeM, 'A', 0, 0);

	std::cout << purse << std::endl;
	tmbuff->text(purse.c_str());
	smbuff->text("DDDDDDD");

	Fl_Text_Display *bet = new Fl_Text_Display(315, 255, 160, 50);
	Fl_Text_Buffer *sbbuff = new Fl_Text_Buffer();
	bet->buffer(tbbuff);
	int stable_sizeB = sizeof(stable)/sizeof(stable[0]);
	bet->highlight_data(sbbuff, stable, stable_sizeB, 'A', 0, 0);

	tbbuff->text(betAmount.c_str());
	sbbuff->text("DDDDDDD");	

	/***************************************** B E T   I N C R E M E N T S ****************************************
	**************************************************************************************************************/
	Fl_Button *bet1button = new Fl_Button(295, 315, 45, 30, "$1");
	bet1button->box(FL_SHADOW_BOX);
	bet1button->color(FL_LIGHT1);
	bet1button->labelcolor(FL_BLACK);
	bet1button->labelfont(FL_BOLD);
	bet1button->callback(bet1_callback);

	Fl_Button *bet5button = new Fl_Button(345, 315, 45, 30, "$5");
	bet5button->box(FL_SHADOW_BOX);
	bet5button->color(FL_LIGHT1);
	bet5button->labelcolor(FL_BLACK);
	bet5button->labelfont(FL_BOLD);
	bet5button->callback(bet5_callback);

	Fl_Button *bet10button = new Fl_Button(395, 315, 45, 30, "$10");
	bet10button->box(FL_SHADOW_BOX);
	bet10button->color(FL_LIGHT1);
	bet10button->labelcolor(FL_BLACK);
	bet10button->labelfont(FL_BOLD);
	bet10button->callback(bet10_callback);

	Fl_Button *bet50button = new Fl_Button(445, 315, 45, 30, "$50");
	bet50button->box(FL_SHADOW_BOX);
	bet50button->color(FL_LIGHT1);
	bet50button->labelcolor(FL_BLACK);
	bet50button->labelfont(FL_BOLD);	
	bet50button->callback(bet50_callback);

	Fl_Button *betClear = new Fl_Button(345, 355, 90, 45, "CLEAR BET");
	betClear->box(FL_SHADOW_BOX);
	betClear->color(FL_LIGHT1);
	betClear->labelcolor(FL_BLACK);
	betClear->labelfont(FL_BOLD);
	betClear->callback(clear_callback);


	/***************************************** P L A Y E R   &   D E A L E R ****************************************
	****************************************************************************************************************/

		/*+++++++++++++++++++++++++++++++ D E A L E R +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		Fl_Text_Display *dispDealer = new Fl_Text_Display(315, 133, 175, 65);
		Fl_Text_Buffer *tdbuff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sdbuff = new Fl_Text_Buffer();
		dispDealer->buffer(tdbuff);
		int stable_sizeD = sizeof(stable)/sizeof(stable[0]);
		dispDealer->highlight_data(sdbuff, stable, stable_sizeD, 'A', 0, 0);

		std::string dealercards = "";
		tdbuff->text(dealercards.c_str());
		sdbuff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");

		/*+++++++++++++++++++++++++++++++ P L A Y E R +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/	
		Fl_Text_Display *dispPlayer = new Fl_Text_Display(315, 453, 175, 65);
		Fl_Text_Buffer *tppbuff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sppbuff = new Fl_Text_Buffer();
		dispPlayer->buffer(tppbuff);
		int stable_sizeP = sizeof(stable)/sizeof(stable[0]);
		dispPlayer->highlight_data(sppbuff, stable, stable_sizeP, 'A', 0, 0);

		std::string playerpcards = "";
		tppbuff->text(playerpcards.c_str());
		sppbuff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");

	/***************************************** O T H E R   P L A Y E R S ****************************************
	************************************************************************************************************/

		/*+++++++++++++++++++++++++++++++ P L A Y E R   1 +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		Fl_Text_Display *dispPlayer1 = new Fl_Text_Display(40, 43, 175, 65);
		Fl_Text_Buffer *tp1buff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sp1buff = new Fl_Text_Buffer();
		dispPlayer1->buffer(tp1buff);
		int stable_sizeP1 = sizeof(stable)/sizeof(stable[0]);
		dispPlayer1->highlight_data(sp1buff, stable, stable_sizeP1, 'A', 0, 0);

		std::string player1cards = "";
		tp1buff->text(player1cards.c_str());
		sp1buff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");

		/*+++++++++++++++++++++++++++++++ P L A Y E R   2 +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		Fl_Text_Display *dispPlayer2 = new Fl_Text_Display(40, 133, 175, 65);
		Fl_Text_Buffer *tp2buff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sp2buff = new Fl_Text_Buffer();
		dispPlayer2->buffer(tp2buff);
		int stable_sizeP2 = sizeof(stable)/sizeof(stable[0]);
		dispPlayer2->highlight_data(sp2buff, stable, stable_sizeP2, 'A', 0, 0);

		std::string player2cards = "";
		tp2buff->text(player2cards.c_str());
		sp2buff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");	

		/*+++++++++++++++++++++++++++++++ P L A Y E R   3 +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		Fl_Text_Display *dispPlayer3 = new Fl_Text_Display(40, 223, 175, 65);
		Fl_Text_Buffer *tp3buff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sp3buff = new Fl_Text_Buffer();
		dispPlayer3->buffer(tp3buff);
		int stable_sizeP3 = sizeof(stable)/sizeof(stable[0]);
		dispPlayer3->highlight_data(sp3buff, stable, stable_sizeP3, 'A', 0, 0);

		std::string player3cards = "";
		tp3buff->text(player3cards.c_str());
		sp3buff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");	

		/*+++++++++++++++++++++++++++++++ P L A Y E R   4 +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		Fl_Text_Display *dispPlayer4 = new Fl_Text_Display(40, 313, 175, 65);
		Fl_Text_Buffer *tp4buff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sp4buff = new Fl_Text_Buffer();
		dispPlayer4->buffer(tp4buff);
		int stable_sizeP4 = sizeof(stable)/sizeof(stable[0]);
		dispPlayer4->highlight_data(sp4buff, stable, stable_sizeP4, 'A', 0, 0);

		std::string player4cards = "";
		tp4buff->text(player4cards.c_str());
		sp4buff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");		

		/*+++++++++++++++++++++++++++++++ P L A Y E R   5 +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		Fl_Text_Display *dispPlayer5 = new Fl_Text_Display(40, 403, 175, 65);
		Fl_Text_Buffer *tp5buff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sp5buff = new Fl_Text_Buffer();
		dispPlayer5->buffer(tp5buff);
		int stable_sizeP5 = sizeof(stable)/sizeof(stable[0]);
		dispPlayer5->highlight_data(sp5buff, stable, stable_sizeP5, 'A', 0, 0);

		std::string player5cards = "";
		tp5buff->text(player5cards.c_str());
		sp5buff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");		

		/*+++++++++++++++++++++++++++++++ P L A Y E R   6 +++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		Fl_Text_Display *dispPlayer6 = new Fl_Text_Display(40, 493, 175, 65);
		Fl_Text_Buffer *tp6buff = new Fl_Text_Buffer();
		Fl_Text_Buffer *sp6buff = new Fl_Text_Buffer();
		dispPlayer6->buffer(tp6buff);
		int stable_sizeP6 = sizeof(stable)/sizeof(stable[0]);
		dispPlayer6->highlight_data(sp6buff, stable, stable_sizeP6, 'A', 0, 0);

		std::string player6cards = "";
		tp6buff->text(player6cards.c_str());
		sp6buff->text("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");			


	playWindow.end();
	playWindow.show();
	Fl::run();	
	Network::get().on_game_update([&](Game game){
		(void)(game);
	});
}


/*================================================== E X I T ==================================================
=============================================================================================================*/
void exitButton_callback(Fl_Widget*, void* a)
{
	(void)(a);
	startWindow.hide();
}


/*================================================== M A I N   W I N D O W ==================================================
===========================================================================================================================*/
int main()
{
	startWindow.color(0x00500000);

	Fl_Box *box = new Fl_Box(250, 60, 300, 100, "Über Kasino!");
	box->box(FL_NO_BOX);
	box->labelfont(FL_BOLD+FL_ITALIC+FL_HELVETICA);
	box->labelsize(90);
	box->labeltype(FL_SHADOW_LABEL);


	Fl_Button *howButton = new Fl_Button(125, 300, 100, 100, "How To");
	howButton->box(FL_DIAMOND_UP_BOX);
	howButton->color(FL_BLACK);
	howButton->labelcolor(FL_LIGHT1);
	howButton->labelfont(FL_BOLD);

	howButton->callback(howButton_callback);

	Fl_Button *playButton = new Fl_Button(350, 300, 100, 100, "Play");
	playButton->box(FL_DIAMOND_UP_BOX);
	playButton->color(FL_DARK_RED);
	playButton->labelcolor(FL_BLACK);
	playButton->labelfont(FL_BOLD);

	playButton->callback(playButton_callback);

	Fl_Button *exitButton = new Fl_Button(575, 300, 100, 100, "Exit");
	exitButton->box(FL_DIAMOND_UP_BOX);
	exitButton->color(FL_BLACK);
	exitButton->labelcolor(FL_LIGHT1);
	exitButton->labelfont(FL_BOLD);

	exitButton->callback(exitButton_callback);

	startWindow.end();
	startWindow.show();

	return Fl::run();

}
