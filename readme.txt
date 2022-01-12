This is a project I worked on in a course. 
My goal was to produce code that runs as efficiently as possible.

I have marked the parts in code which I have done by myself.
I implemented functions and data structure for the program in "datastructures" files.
The UI files were given to me in advance, so I haven't done them myself.
The functions and data structures I implement are in files: datastructures(hh/cc) 
I haven't touched following files at all: "mainprogram.(hh/cc), and mainwindow.(hh/cc/ui)".
 
Below is an explanation for how this program works:

The topic of this programming project is a program which records information about
towns (name, coordinates, and collected tax revenue), and towns can be printed out in different
orders, and minimum and maximum queries can be made. Towns can
also be removed. The program will contain commands for asking about the taxation relationships of
the towns, as well as each town's own net tax revenue.

Example of taxastion in this code:
Town x (tax 20) has two vassals, v1 (tax 10) and v2 (tax 5), which do not have vassals of
their own. Additionally town x has a master town m. In this case, town v1's total net tax is 9
(because 10 % is paid as tax to x), town v2's total net tax is 5 (because 10 % of 5 is rounded down to
zero). Town x's total net tax is 19 (20 + 1 from v1 (and 0 from v2) = 21, from which 10 % (rounded
down to 2) is paid to m, which makes 19 in total for x's total net tax).


A road always goes directly between two towns, and it can be travelled in either
direction. The length of a road is the same as the distance (euclidean) between the towns rounded down to an integer


A route is a series of roads, which are “connected” so that the next road starts from
the town where the previous one ends. The length of a route is the sum of the lengths of the
roads it contains. A route cannot directly return using the same road that was used to arrive
to a town.


A route has a cycle, if while travelling the route you arrive again to a town through
which the route has already passed


When the program is run, it waits for commands explained below. The commands, whose
explanation mentions a member function, call the respective member function of the Datastructure
class. 
If the program is given a file as a command line parameter, the program executes commands from
that file and then quits.



Commands of the code explained:


//

town_count
unsigned int town_count();

Returns the number of towns currently in the data
structure.

//

bool add_town(TownID id,
std::string const& name, Coord
coord, int tax);

Adds a town to the data structure with the given unique
id, name, coordinates, and tax. New added towns are
initially not vassals of any town. If there already is a town
with the given id, nothing is done and false is returned,
otherwise true is returned.

//

Name get_town_name(TownID id);

Returns the name of the town with the given ID, or
NO_NAME if such a town doesn't exist.  (Command print_town
calls all three get_ operations.)

//

Coord get_town_coordinates(TownID
id);

Returns the coordinates of the town with given ID, or
NO_COORD, if such town doesn't exist.
//

int get_town_tax(TownID id);

Returns the tax of the town with given ID, or
NO_VALUE if such town doesn't exist. 

//

std::vector<TownID> all_towns();

Returns a list (vector) of the towns in any (arbitrary)
order.
//

std::vector<TownID>
find_towns(Name const& name);

Returns towns with the given name, or an empty vector, if
no such towns exist. The order of IDs in the return value
can be arbitrary. 

//

bool change_town_name(TownID id,
Name const& newname);

Changes the name of the town with the given ID. If such a
town doesn't exist, returns false, otherwise true.

//

std::vector<TownID>
towns_alphabetically();

Returns the towns in alphabetical order.

//

std::vector<TownID>
towns_distance_increasing();

Returns the towns in increasing order of distance from the
origin (0,0). 

//

TownID min_distance();

Returns the town nearest to origin (0,0). If there are
several such towns with the same distance, returns one of
them. If no towns exist, NO_TOWNID is returned.

//

TownID max_distance();

Returns the town furthest away from origin (0,0). If there
are several such towns with the same distance, returns one
of them. If no towns exist, NO_TOWNID is returned.

//

bool add_vassalship(TownID
vassalid, TownID masterid);

Adds a vassal relationship between towns. A vassal town
can only have one master town. You can assume that
vassal relationships do not form cycles (i.e., a town
cannot directly or indirectly be its own vassal). If either of
the towns do not exist, or the vassal to be added already
has a master, nothing is done and false is returned.
Otherwise true is returned.

//

std::vector<TownID> get_town_vassals(TownID id);

Returns the IDs of the towns that are immediate vassals of
the given town (i.e., vassals of vassals are not included),
or a vector with a single element NO_TOWNID, if no
town with the given ID exists. The order of IDs can be
arbitrary. 

//

taxer_path(TownID id);

Returns a list of towns to which the town pays taxes either
directly or indirectly. The return vector first contains the
town, then its master, the master of the master, etc. as long
as there are masters. If the ID does not correspond to any
town, a vector with a single element NO_TOWNID is
returned.

//

bool remove_town(TownID id);

Removes a town with the given id. If a town with the
given id does not exist, does nothing and returns false,
otherwise returns true. If the town to be removed has
vassal towns and a master town, the vassals of the
removed town become vassals of the master of the
removed town. If the town to be removed has no master,
after removal its vassals are also without a master.

//

std::vector<TownID>
towns_nearest(Coord coord);

Returns a list (vector) of the towns in increasing order of
distance from the given coordinate (x,y) (nearest first).

//

std::vector<TownID>
longest_vassal_path(TownID id);

Returns the longest possible chain of vassals, starting
from the given town. The return vector first contains the
town, then its vassal, the vassal of the vassal, etc., so that
the chain has as many towns as possible (if there are
several vassal chains with equally many towns, any such
chain may be returned). If the ID does not correspond to
any town, a vector with a single element NO_TOWNID is
returned.

//

int total_net_tax(TownID id);

Returns the town's total net tax.
If the ID does not correspond to any
town, NO_VALUE is returned.

//

void clear_all(); 

Clears out the data structure, i.e. removes all towns
and roads (after this town_count returns 0 and
all_roads returns an empty list).

//

void clear_roads()

Clears out all roads, but doesn’t touch towns or
vassalships.

//

std::vector<std::pair<TownID,
TownID>> all_roads()

Returns a list (vector) of the ways in any (arbitrary)
order (the main routine sorts them based on their ID).
Each road is in the list only once and expressed as a
pair of town ids, so that the smaller valued id is first in
the pair.

//

bool add_road(TownID town1,
TownID town2)

Adds a road between given towns. If either town
doesn't exist, or a road already exists between towns,
nothing is done and false is returned, otherwise
true.

//

std::vector<TownID>
get_roads_from(TownID id)

Returns in arbitrary order a list of towns to which a
direct road goes from the given town. If there's no town
with the given ID, a single element NO_TOWNID is
returned.

//

std::vector<TownID>
any_route(TownID fromid, TownID
toid)

eturns any (arbitrary) route between the given towns.
The returned vector first has the starting town. Then
come the rest of the towns along the route and finally
the destination town. If no route can be found between
the towns, an empty vector is returned. If either of the
ids does not correspond to a town, one element
{NO_TOWNID} is returned.

//

bool remove_road(TownID town1,
TownID town2)

Removes a road between given towns. If either town
doesn't exist, or a road does not exists between towns,
nothing is done and false is returned, otherwise
true.

//

std::vector<TownID>
least_towns_route(TownID fromid,
TownID toid)

Returns a route between the given crossroads so that it
contains the minimum number of towns. If several
routes exist with as few towns, any of them can be
returned. The returned vector first has the starting
town. Then come the rest of the towns along the route
and finally the destination town. If no route can be
found between the towns, an empty vector is returned.
If either of the ids does not correspond to a town, one
element {NO_TOWNID} is returned.

//

std::vector<TownID>
road_cycle_route(TownID startid)

Returns a route starting from the given town so that has
a cycle, i.e. the route returns to a town already passed
on the route. The returned vector first has the starting
town. Then come the rest of the towns along the route
and finally the town reached again (causing the cycle).
If no cyclic route can be found from the point, an
empty vector is returned. If the id does not correspond
to a town, one element {NO_TOWNID} is returned.
A route that immediately travels back the same
road it used to arrive to a town doesn’t count as a
cycle.

//


