#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum UI_Type {
	UI_BUTTON,
	UI_TEXT,
	UI_IMAGE,
	UI_UNKNOWN
};



class UI_elem {
public:
	UI_elem(SDL_Rect Rect, UI_Type Type) : type(Type), rect(Rect), hovered(false), interactable(true) {};
	
	iPoint position;
	bool interactable;
	UI_elem* parent;

	inline SDL_Rect GetRect() {
		return rect;
	}

private:
	
	SDL_Rect rect;
	UI_Type  type;
	bool hovered;

};

class UI_Text : public UI_elem {
public:
	UI_Text(SDL_Rect Rect, const char* Text) : UI_elem(Rect, UI_TEXT), text(Text) {};

	const char* text;
};

class UI_Image : public UI_elem {
public:
	UI_Image(SDL_Rect Rect) : UI_elem(Rect, UI_IMAGE) {};
};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	UI_elem* CreateUIelement(SDL_Rect rect, UI_Type type);
	
	UI_Image* CreateImage(SDL_Rect rect);
	UI_Text* CreateText(SDL_Rect rect, const char* text);
	
	bool deleteUIelement(UI_elem* elem);




	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UI_elem*> UI_List;
};

#endif // __j1GUI_H__