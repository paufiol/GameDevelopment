#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
	
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;
	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

	p2SString Location("maps/"); 
	Location += tilesets[0].img_source;
	SDL_Texture* texture = App->tex->Load(Location.GetString());
	
	App->render->Blit(texture, 0, 0);
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());
	pugi::xml_node map_node;

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		LoadMap(map_file.child("map"));
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	LoadTileset(map_file.child("map"));

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
		LOG("Succesfully parsed map XML file: %s", file_name);
		LOG("width: %u height: %u", map.width, map.height);
		LOG("tile_width: %u tile_height: %u", map.tilewidth, map.tileheight);
		for (int i = 0; i < array_size; i++) {
			LOG("Tileset %d----", i);
			LOG("name: %s firstgid: %d", tilesets[i].name, tilesets[i].firstgid);
			LOG("tile_width: %u tile_height: %u", tilesets[i].width, tilesets[i].height);
			LOG("spacing: %u margin: %u", tilesets[i].spacing, tilesets[i].margin);
		}
	}

	map_loaded = ret;

	return ret;
}

bool j1Map::LoadTileset(pugi::xml_node& node) {
	bool ret = true;
	
	
	for (pugi::xml_node tileset = node.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"), array_size++) {}
	tilesets = new Tileset[array_size];
	
	int i = 0;
	for (pugi::xml_node tileset = node.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"), i++) {

		tilesets[i].firstgid = tileset.attribute("firstgid").as_uint();
		tilesets[i].name = tileset.attribute("name").as_string();
		tilesets[i].width = tileset.attribute("tilewidth").as_uint();
		tilesets[i].height = tileset.attribute("tileheight").as_uint();
		tilesets[i].spacing = tileset.attribute("spacing").as_uint();
		tilesets[i].margin = tileset.attribute("margin").as_uint();
		tilesets[i].img_source = tileset.child("image").attribute("source").as_string();

	}

	return ret;
}

bool j1Map::LoadMap(pugi::xml_node& node) {
	bool ret = true;

	map.version = node.attribute("version").as_float();
	map.width = node.attribute("width").as_uint();
	map.height = node.attribute("height").as_uint();
	map.tilewidth = node.attribute("tilewidth").as_uint();
	map.tileheight = node.attribute("tileheight").as_uint();
	map.nextobject = node.attribute("nextobjectid").as_uint();

	if		(node.attribute("orientation").as_string() == "orthogonal")	map.orientation = Orientation::ORTHOGONAL;
	else if (node.attribute("orientation").as_string() == "isometric")	map.orientation = Orientation::ISOMETRIC;
	else if (node.attribute("orientation").as_string() == "staggered")	map.orientation = Orientation::STAGGERED;
	else if (node.attribute("orientation").as_string() == "hexagonal")	map.orientation = Orientation::HEXAGONAL;
	else ret = false;

	if		(node.attribute("orientation").as_string() == "right-down")	map.renderorder = RenderOrder::RIGHT_DOWN;
	else if (node.attribute("orientation").as_string() == "right-up")		map.renderorder = RenderOrder::RIGHT_UP;
	else if (node.attribute("orientation").as_string() == "left-down")	map.renderorder = RenderOrder::LEFT_DOWN;
	else if (node.attribute("orientation").as_string() == "left-up")		map.renderorder = RenderOrder::LEFT_UP;
	else ret = false;

	return ret;
}

