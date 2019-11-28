#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum UI_Type {
	UI_BUTTON,
	UI_TEXT,
	UI_UNKNOWN
};



class UI_elem {
public:
	UI_elem(SDL_Rect Rect, UI_Type Type)  {};
	
	SDL_Rect rect;
	UI_Type  type;
};

class UI_button : public UI_elem {
public:
	UI_button(SDL_Rect Rect, UI_Type Type) : UI_elem(Rect, Type) {};
};

class UI_text : public UI_elem {
public:
	UI_text(SDL_Rect Rect, UI_Type Type) : UI_elem(Rect, Type) {};
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

	// TODO 2: Create the factory methods
	// Gui creation functions
	UI_elem* CreateUIelement(SDL_Rect rect, UI_Type type);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UI_elem*>* UI_List;
};

#endif // __j1GUI_H__