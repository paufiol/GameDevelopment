#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<UI_elem*>* UIter = UI_List.start;

	while (UIter != NULL)
	{
		App->render->Blit(atlas, UIter->data->position.x, UIter->data->position.y, UIter->data->);


		UIIter = UIIter->next;
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

UI_elem* j1Gui::CreateUIelement(SDL_Rect rect, UI_Type type)
{
	UI_elem* ret;

	switch (type) {
		case UI_TEXT:
			ret = (UI_elem*) new UI_Text(rect, "");
			break;
		case UI_IMAGE:
			ret = (UI_elem*) new UI_Image(rect);
			break;
		
		case UI_UNKNOWN:
			LOG("Something went wrong, UI_UNKWNOWN");
			break;
	}

	UI_List.add(ret);

	return ret;
}

UI_Image* j1Gui::CreateImage(SDL_Rect rect) {

	UI_Image* ret = new UI_Image(rect);
	
	UI_List.add(ret);

	return ret;
};

UI_Text* j1Gui::CreateText(SDL_Rect rect, const char* text) {
	
	UI_Text* ret = new UI_Text(rect, text);

	UI_List.add(ret);

	return ret;
};

bool j1Gui::deleteUIelement(UI_elem* elem) {
	return UI_List.del(UI_List.At(UI_List.find(elem)));
}

// class Gui ---------------------------------------------------

