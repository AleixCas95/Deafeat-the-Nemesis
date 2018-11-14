#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if (CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::Find(const iPoint& point) const
{
	p2List_item<PathNode>* item = list.start;
	while (item)
	{
		if (item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::GetNodeLowestScore() const
{
	p2List_item<PathNode>* ret = NULL;
	//??
	int min = 65535;

	p2List_item<PathNode>* item = list.end;
	while (item)
	{
		if (item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	iPoint cell;
	uint before = list_to_fill.list.count();

	// north
	cell.create(pos.x, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// south
	cell.create(pos.x, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// east
	cell.create(pos.x + 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	return list_to_fill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	//??
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{

	//if the origin or the place where the entity is is not walkable, return -1
	if (IsWalkable(destination) == false || IsWalkable(origin) == false) return -1;

	//open son los posibles caminos que puedo tomar
	//close es el camino que he hecho hasta ahora
	PathList open, close;

	//nodo es el punto donde empieza el pathfinding (le pasamos coste,distancia,posicion, padre(nullptr))
	PathNode originTile(0, origin.DistanceNoSqrt(destination), origin, nullptr);

	open.list.add(originTile);

	//if openlist is not empty
	while (open.list.count() > 0) 
	{
		//en el camino que hay que hace le añades el node que tenga menos coste
		close.list.add(open.GetNodeLowestScore()->data);
		//haces delete del node de menos coste porque necesitas nodes nuevos(no puedes volver al mismo))
		open.list.del(open.GetNodeLowestScore());

		//Si el ultimo nodo que hay en la close(que es el camino recorrido) es el destino ya no hay mas que buscar
		if (close.list.end->data.pos == destination) 
		{
			p2List_item<PathNode>* iterator = close.list.end;
			//empieza en el destino hasta que llega al origen
			for (; iterator->data.parent != nullptr; iterator = close.Find(iterator->data.parent->pos))
			{
				//añade el paso en la lista last_path
				last_path.PushBack(iterator->data.pos);

				//si es el primer paso, empieza
				if (iterator->data.parent == nullptr)
				{
					last_path.PushBack(close.list.start->data.pos);
				}

				last_path.Flip();
				return last_path.Count();
			}
		}
		//si no estamos en el destino
		else
		{
			PathList neighbours;

			//estamos asignando a neighbours cuales son los vecinos caminables
			close.list.end->data.FindWalkableAdjacents(neighbours);

			p2List_item<PathNode>* iterator = neighbours.list.start;
			for (iterator; iterator != nullptr; iterator = iterator->next)
			{
				if (close.Find(iterator->data.pos))
				{
					//si el vecino esta en la close list te lo saltas
					continue;
				}
				//si el vecino es caminable c
				else if (open.Find(iterator->data.pos))
				{
					PathNode tmp = open.Find(iterator->data.pos)->data;
					iterator->data.CalculateF(destination);
					//comparacion de costes
					if (tmp.g > iterator->data.g) 
					{
						tmp.parent = iterator->data.parent;
					}
				}
				else
				{
					//si no es el destino y no esta en la open list, lo metemos en ella
					iterator->data.CalculateF(destination);
					open.list.add(iterator->data);
				}
			}
			neighbours.list.clear();

		}
		
	}
	open.list.clear();
	close.list.clear();

	return last_path.Count();
}