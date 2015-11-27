#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

enum GUI_TYPE
{
	GUI_LABEL,
	GUI_BUTTON,
	GUI_IMAGE,
	GUI_INPUT_BOX,
};

class GUImanager
{
public:

	iPoint			pos;
	GUI_TYPE		type;

	virtual bool Update(){ return true; };
	virtual bool Draw(){ return true; };
};

class GUIlabel : public GUImanager
{
public:
	const char*			label_text;
	SDL_Texture*		label_tx;

	GUIlabel(){ pos.SetToZero(); type = GUI_LABEL;	label_text = NULL;	label_tx = NULL; };

	GUIlabel(const char* label_text);
	~GUIlabel();

	bool Draw();
};

class GUIimage :public GUImanager
{
public:
	SDL_Texture*	image;
	SDL_Rect		rect;

	GUIimage(){ pos.SetToZero(); type = GUI_IMAGE; image = NULL; rect = { 0, 0, 0, 0 }; };
	GUIimage(SDL_Texture* image);
	GUIimage(SDL_Texture* image, SDL_Rect rect);
	~GUIimage();

	bool Draw();
};

class GUIbutton : public GUImanager
{
public:
	int width, height;
	bool clicked;

	GUIbutton(){ pos.SetToZero(); type = GUI_BUTTON; width = 0; height = 0; clicked = false; };
	GUIbutton(int width, int height);
	~GUIbutton();

	bool Update(){ return true; };
	bool Draw(){ return true; };
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
	const GUIlabel* CreateLabel(const char* label_text, iPoint pos);
	const GUIimage* CreateImage(SDL_Texture* image, iPoint pos, SDL_Rect& rect);
	const GUIbutton* CreateButton(int width, int height, iPoint pos, bool clicked);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<GUImanager*> GUIelement_list;
};

#endif // __j1GUI_H__