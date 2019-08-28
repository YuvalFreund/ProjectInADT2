#include "Clan.h"
using std::string;
using namespace mtm;

  /**
   * A clan of multiple groups. Groups can join a clan, and clans can be
   * friends to other clans.
   * Groups with no people can't join a clan, and a group that had
   * lost all of its people, will be removed from the clan.
   */

/**
 * Constructor
 * @param name The name of the new clan, can't be empty
 * @throws ClanEmptyName if name is empty.
 */
Clan::Clan(const std::string& name):
    name(name), groups(), friends()
{
    if (name.length()==0){
        throw ClanEmptyName();
    }
}

/**
 * Copy constructor.
 */
Clan::Clan(const Clan& other) = default;

/**
 * Get the name of the clan
 * @return The name of the clan
  */
const std::string& Clan::getName() const{
     return this->name;
}

/**
 * Destructor
 */
Clan::~Clan()= default;

/**
 * Add a group (copy of it) to the clan
 * @param group The group to add to the clan
 * @throws ClanGroupIsEmpty if the group has no people (empty)
 * @throws ClanGroupNameAlreadyTaken if there is already a group
 * with the same name in the clan.
 */
void Clan::addGroup(const Group& group){
    if(group.getSize()==0){
        throw ClanGroupIsEmpty();
    }
    for(MtmSet<GroupPointer>::const_iterator iter=groups.begin()
            ;iter!=groups.end();iter++) {
        if ((*iter)->getName()== group.getName()) {
            throw ClanGroupNameAlreadyTaken();
        }
    }
    GroupPointer temp_group(new Group(group));
    temp_group->changeClan(this->getName());
    this->groups.insert(temp_group);
}

/**
 * Get a group from the clan, with a given name
 * @param group_name The name of the group to return
 * @return A reference to the group with the given name
 * @throws ClanGroupNotFound if there is no group in the clan with the
 * given name.
 */
const GroupPointer& Clan::getGroup(const std::string& group_name) const{
    for(MtmSet<GroupPointer>::const_iterator iter=groups.begin()
            ;iter!=groups.end();iter++){
        if((*iter)->getName()==group_name) {
            return *iter;
        };
    }
    throw ClanGroupNotFound();
}

bool Clan::doesContain(const std::string& group_name) const{
    for(MtmSet<GroupPointer>::const_iterator iter=groups.begin();
        iter!=groups.end();iter++){
        if((*iter)->getName()==group_name)
            return true;
    }
    return false;
}

/**
 * The function returns the amount of people in the clan.
 * A person belongs to the clan, if he belongs to a group, that
 * belongs to the clan.
 * @return The amount of people in the clan.
 */
int Clan::getSize() const{
    int total=0;
    for(MtmSet<GroupPointer>::const_iterator iter=groups.begin();
        iter!=groups.end();iter++){
            total+=(*iter)->getSize();
   }
    return total;
}
/**
 * Make two clans unite, to form a new clan, with a new name. All the
 * groups of each clan will change their clan.
 * The friends of the new clan are all the friends of either one of
 * the old 2 clans.
 * The new clan will replace this clan, and the other clan (received
 * by an argument) will become empty (i.e no groups).
 *
 * If One of the exception is thrown, both clan shouldn't change.
 * @param other The clan to unite with
 * @param new_name The name of the new clan. If the name is of one of
 *  the uniting clans (assume to clan A), that means the other clan,
 *  joined clan A, and the groups of the clan A, don't change their
 *  clan.
 * @return A reference to the new clan (this).
 * @throws ClanEmptyName new_name is empty.
 * @throws ClanCantUnite If other is the same clan as this or if
 *  there is a group in one of the clans, that has the same name as a
 *  group in the other clan.
 */
Clan& Clan::unite(Clan& other, const std::string& new_name) {
    if (new_name == "") {
        throw ClanEmptyName();//check if name is empty
    }
    if (this == &other) {
        throw ClanCantUnite();//check if not the same clan
    }
    for(MtmSet<GroupPointer>::const_iterator iter=groups.begin();
        iter!=groups.end();iter++) {
        if (other.doesContain((*iter)->getName())) {
            throw ClanCantUnite(); //
        }
    }
    name =new_name;
    for(MtmSet<GroupPointer>::const_iterator iter=groups.begin();
        iter!=groups.end(); iter++){
        (*(*iter)).changeClan(new_name);
    }
    for(MtmSet<GroupPointer>::const_iterator iter=other.groups.begin();
        iter!=other.groups.end(); iter++){
        this->addGroup(*(*iter));
    }
    for(MtmSet<string>::iterator iter=other.friends.begin();
        iter!=other.friends.end();++iter){
        this->friends.insert(*iter);
    }
    other.groups.clear();//clear the other groups
    return *this;
}
/**
 * Make this clan, and a given clan, friends. If the two clans already
 * were friends, does nothing.
 * Assume that every clan has a unique name. (In copied clans, you
 * can assume one of the copies will not be used again).
 * @param other The clan to become a friend with.
 */
void Clan::makeFriend(Clan& other){
    this->friends.insert(other.name);
    other.friends.insert(this->name);
}

/**
 * Check if a given clan is a friend of this clan.
 * Every clan is a friend of itself.
 * @param other The clan to check if is a friend.
 * @return true, if the given clan is a friend of this clan, false
 *  otherwise.
 */
bool Clan::isFriend(const Clan& other) const{
    if (this==&other){
        return true;
    }
    return this->friends.contains(other.getName());
}

/**
 * Print The clan name, and it groups, sorted by groups comparison
 * operators, from strongest to weakest. In the next Format:
 *
 * Clan's name: [name]
 *     [1'st group name]
 *     [2'nd group name]
 *     [3'rd group name]
 *             *
 *             *
 *             *
 *
 * @param os The output stream
 * @param clan The clan to print
 * @return A reference to the output stream
 */
std::ostream& mtm::operator<<(std::ostream& os, const Clan& clan){
    os << "Clan's name: " << clan.getName() << std::endl;
    os << "Clan's groups:" << std::endl;
    list<Group> printing;
    for(MtmSet<GroupPointer>::const_iterator iter = clan.groups.begin();
        iter != clan.groups.end(); iter++){
        printing.push_back((*(*iter)));
    }
    printing.sort();
    printing.reverse();
    for(std::list<Group>::iterator iter= printing.begin();
        iter !=printing.end(); iter++){
        os<<(*iter).getName()<<std::endl;
    }
    return os;
}