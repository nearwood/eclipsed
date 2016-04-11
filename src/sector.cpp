#include "sector.h"

Sector::Sector():
id(-1),
ring(-1),
ln(nullptr),
lne(nullptr),
lse(nullptr),
ls(nullptr),
lsw(nullptr),
lnw(nullptr),
n(nullptr),
ne(nullptr),
se(nullptr),
s(nullptr),
sw(nullptr),
nw(nullptr)
{
	
}

Sector::Sector(Sector& other):
//planets(other.planets),
ancientSpawn(other.ancientSpawn),
ancientBonus(other.ancientBonus),
startSector(other.startSector),
id(other.id),
ring(other.ring),
eco(other.eco),
min(other.min),
sci(other.sci),
aeco(other.aeco),
amin(other.amin),
asci(other.asci),
influence(other.influence),
ships(other.ships),
ln(other.ln),
lne(other.lne),
lse(other.lse),
ls(other.ls),
lsw(other.lsw),
lnw(other.lnw),
n(other.n),
ne(other.ne),
se(other.se),
s(other.s),
sw(other.sw),
nw(other.nw)
{
	
}
