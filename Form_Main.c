#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#pragma region ENUMS
enum Dice {
	DiceM3,
	DiceM2,
	DiceM1,
	DiceP1,
	DiceP2,
	DiceP3,
};
enum Nut { NUT1, NUT2, };
enum LuckyCard
{
	Place1,
	Place2,
	Place3,
	Place4,
};
enum Pages
{
	StartGame,
	Form_continue,
	FristMenu,
	buttons_continueANDnew_Form,
	Template_Form,
	Guide_Form,
	AboutUs_Form,
	Setting_Form,
	Board_Form,
	appointment_Form,//TAiin Nobat
};
enum GuideForms {P1,P2,P3,P4,P5};

#pragma endregion
#pragma region STRUCTS
#pragma endregion
void must_init(bool check, const char* description)
{
	if (check) return;
	printf("couldn't initialize %s\n", description);
	exit(1);
}
int main()
{

	//Setting
#pragma region create Window

	al_init();
	must_init(al_init(), "Allegro");
	must_init(al_init_primitives_addon(), "primitives");
	must_init(al_init_image_addon(), "Image Load");
	must_init(al_install_keyboard(), "Key Board");
	must_init(al_install_mouse(), "Mouse");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	ALLEGRO_VERTEX_DECL* vertex;

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	ALLEGRO_DISPLAY* disp = al_create_display(1300, 810);
	must_init(disp, "Window");

	ALLEGRO_FONT* font = al_create_builtin_font();
	must_init(font, "Font Package");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_mouse_event_source());

#pragma endregion

	bool sw = true;
	bool done = false;
	enum Pages pages_sw=Board_Form;

	//Objects
 #pragma region Images of Board Form
	ALLEGRO_EVENT event;

	ALLEGRO_BITMAP* Board_PIC = al_load_bitmap("Images/MIMBOARD.png");

	ALLEGRO_BITMAP* Dice_PIC[6];
	Dice_PIC[DiceP3] = al_load_bitmap("Images/Dice/TAS_puls3.png");
	Dice_PIC[DiceP2] = al_load_bitmap("Images/Dice/TAS_puls2.png");
	Dice_PIC[DiceP1] = al_load_bitmap("Images/Dice/TAS_puls1.png");
	Dice_PIC[DiceM3] = al_load_bitmap("Images/Dice/TAS_mine3.png");
	Dice_PIC[DiceM2] = al_load_bitmap("Images/Dice/TAS_mine2.png");
	Dice_PIC[DiceM1] = al_load_bitmap("Images/Dice/TAS_mine1.png");

	ALLEGRO_BITMAP* NutsP1_PIC[2];
	NutsP1_PIC[NUT1] = al_load_bitmap("Images/MOHRE1.png");
	NutsP1_PIC[NUT2] = al_load_bitmap("Images/MOHRE1.png");

	ALLEGRO_BITMAP* NutsP2_PIC[2];
	NutsP2_PIC[NUT1] = al_load_bitmap("Images/MOHRE2.png");
	NutsP2_PIC[NUT2] = al_load_bitmap("Images/MOHRE2.png");

	ALLEGRO_BITMAP* lucky_CardP1_PIC[4];
	lucky_CardP1_PIC[Place1] = al_load_bitmap("Images/BLOCK_cart.png");
	lucky_CardP1_PIC[Place2] = al_load_bitmap("Images/BLOCK_cart.png");
	lucky_CardP1_PIC[Place3] = al_load_bitmap("Images/BLOCK_cart.png");
	lucky_CardP1_PIC[Place4] = al_load_bitmap("Images/BLOCK_cart.png");

	ALLEGRO_BITMAP* lucky_CardP2_PIC[4];
	lucky_CardP2_PIC[Place1] = al_load_bitmap("Images/BLOCK_cart.png");
	lucky_CardP2_PIC[Place2] = al_load_bitmap("Images/BLOCK_cart.png");
	lucky_CardP2_PIC[Place3] = al_load_bitmap("Images/BLOCK_cart.png");
	lucky_CardP2_PIC[Place4] = al_load_bitmap("Images/BLOCK_cart.png");

	ALLEGRO_BITMAP* Place_Start_Nuts_P1[2];
	Place_Start_Nuts_P1[Place1] = al_load_bitmap("Images/BLOCK_player1.png");
	Place_Start_Nuts_P1[Place2] = al_load_bitmap("Images/BLOCK_player1.png");

	ALLEGRO_BITMAP* Place_Start_Nuts_P2[2];
	Place_Start_Nuts_P2[Place1] = al_load_bitmap("Images/BLOCK_player2.png");
	Place_Start_Nuts_P2[Place2] = al_load_bitmap("Images/BLOCK_player2.png");

	//ALLEGRO_BITMAP* ProgressP1 = al_load_bitmap("Images/MIMBOARD.png");
	//ALLEGRO_BITMAP* ProgressP2 = al_load_bitmap("Images/MIMBOARD.png");

	ALLEGRO_BITMAP* RefreshIcon = al_load_bitmap("Images/RESTART.png");

	ALLEGRO_BITMAP* GuideIcon = al_load_bitmap("Images/Qestion.png");

	ALLEGRO_BITMAP* Menu_InTheBoard_Icon = al_load_bitmap("Images/Menuintheboard.png");

	ALLEGRO_BITMAP* MenuFramePic = al_load_bitmap("Images/BLOCK_STOP_menu.png");

	ALLEGRO_BITMAP* CaractersP1_PIC = al_load_bitmap("Images/Caracters/superMan.png");

	ALLEGRO_BITMAP* CaractersP2_PIC = al_load_bitmap("Images/Caracters/strongMan.png");

#pragma endregion


	//current Window
	al_start_timer(timer);
	while (1)
	{
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			sw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}
		if (done)break;

		if (sw && al_is_event_queue_empty(queue))
		{
			switch (pages_sw)
			{
			case StartGame:
#pragma region codes for StartGame

#pragma endregion
				break;
			case Form_continue:
				break;
			case FristMenu:
				break;
			case buttons_continueANDnew_Form:
				break;
			case Template_Form:
				break;
			case Guide_Form:
				break;
			case AboutUs_Form:
				break;
			case Setting_Form:
				break;
			case Board_Form:
#pragma region codes for board page
				al_clear_to_color(al_map_rgb(240, 240, 240));
				//Menu Frame-------------------------------
				al_draw_bitmap(MenuFramePic, 25, -12, 0);
				al_draw_bitmap(Menu_InTheBoard_Icon, 35, -5, 0);
				al_draw_bitmap(RefreshIcon, 105, -5, 0);
				al_draw_bitmap(GuideIcon, 170, -5, 0);
				//-----------------------------------------

				//Board Frame------------------------------
				al_draw_bitmap(lucky_CardP1_PIC[Place1], 340, 286, 0);
				al_draw_bitmap(lucky_CardP1_PIC[Place2], 340, 391, 0);
				al_draw_bitmap(lucky_CardP1_PIC[Place3], 340, 496, 0);
				al_draw_bitmap(lucky_CardP1_PIC[Place4], 340, 601, 0);

				al_draw_bitmap(lucky_CardP2_PIC[Place1], 936, 100, 0);
				al_draw_bitmap(lucky_CardP2_PIC[Place2], 936, 205, 0);
				al_draw_bitmap(lucky_CardP2_PIC[Place3], 936, 310, 0);
				al_draw_bitmap(lucky_CardP2_PIC[Place4], 936, 415, 0);

				al_draw_bitmap(Place_Start_Nuts_P1[Place1], 350, 692, 0);
				al_draw_bitmap(Place_Start_Nuts_P1[Place2], 455, 692, 0);

				al_draw_bitmap(Place_Start_Nuts_P2[Place1], 850, 80, 0);
				al_draw_bitmap(Place_Start_Nuts_P2[Place2], 745, 80, 0);

				al_draw_bitmap(Board_PIC, 350, 100, 0);
				//-----------------------------------------

				//Dice-------------------------------------
				al_draw_bitmap(Dice_PIC[DiceP3], 615, 366, 0);
				//-----------------------------------------

				//Nuts-------------------------------------
				al_draw_bitmap(NutsP1_PIC[NUT1], 365, 730, 0);
				al_draw_bitmap(NutsP1_PIC[NUT2], 470, 730, 0);
				al_draw_bitmap(NutsP2_PIC[NUT1], 760, 5, 0);
				al_draw_bitmap(NutsP2_PIC[NUT2], 865, 5, 0);
				//-----------------------------------------

				//Caracters--------------------------------
				al_draw_bitmap(CaractersP1_PIC, 10, 290, 0);
				al_draw_bitmap(CaractersP2_PIC, 1090, 100, 0);
				//-----------------------------------------
#pragma endregion
				break;
			case appointment_Form:
				break;

			default:
				break;
			}


			//Build Window-----------------------------
			al_flip_display();
			//-----------------------------------------
			sw = false;

		}
	}
#pragma region Destroying
	al_destroy_bitmap(Board_PIC);
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
#pragma endregion




	return 0;
}