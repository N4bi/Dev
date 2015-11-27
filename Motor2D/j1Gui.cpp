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
	p2List_item<GUImanager*>* gui_element = GUIelement_list.getFirst();
	while (gui_element != NULL)
	{
		gui_element->data->Draw();
		gui_element = gui_element->next;
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	p2List_item<GUImanager*>* gui_elements = GUIelement_list.getFirst();
	while (gui_elements != NULL)
	{
		delete gui_elements->data;
		gui_elements = gui_elements->next;
	}

	GUIelement_list.clear();

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------


const GUIlabel* j1Gui::CreateLabel(const char* label_text, iPoint pos)
{
	GUIlabel* label = new GUIlabel();
	label->pos = pos;
	
	label->label_text = label_text;
	label->label_tx = App->font->Print(label_text);
	GUIelement_list.add(label);

	return label;
}
const GUIimage* j1Gui::CreateImage(SDL_Texture* texture, iPoint pos, SDL_Rect& rect)
{
	GUIimage* image_ret = new GUIimage();
	if (texture != NULL)
	{
		image_ret->image = texture;
	}
	else
	{
		image_ret->image = (SDL_Texture*)App->gui->GetAtlas();
	}

	image_ret->pos = pos;
	image_ret->rect = rect;
	GUIelement_list.add(image_ret);

	return image_ret;
}


bool GUIlabel::Draw()
{
	App->render->Blit(label_tx, pos.x, pos.y);
	return true;
}

bool GUIimage::Draw()
{
	App->render->Blit(image, pos.x, pos.y, &rect);
	return true;
}





