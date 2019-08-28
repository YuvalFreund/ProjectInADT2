#include "World.h"

using namespace mtm;


/**
         * Add a new clan to the world.
         * @param new_clan The name of the new clan
         * @throws WorldInvalidArgument If new_clan is empty
         * @throws WorldClanNameIsTaken If there is or was a clan with the
         *  given name.
         */
void World::addClan(const string& new_clan){
    try{
        Clan inserted(new_clan);
        std::pair<std::map<string,Clan>::iterator,bool> ret;
        ret = this->clan_map.insert(std::pair<string,Clan>(new_clan,inserted));
        if(!ret.second){
            //if the value wasn't inserted because there was another clan with the same name
            throw WorldClanNameIsTaken();
        }
    }catch(ClanEmptyName &e) {
        throw WorldInvalidArgument();
    }
}

/**
 * Add a new area to the world.
 * @param area_name The name of the area
 * @param type The type of the area (PLAIN, MOUNTAIN, RIVER)
 * @throws WorldInvalidArgument If area_name is empty
 * @throws WorldAreaNameIsTaken If there is already an area with the
 *  given name.
 */
void World::addArea(const string& area_name, AreaType type){
    if(area_name.empty()){
        throw WorldInvalidArgument();
    }
    if(check_area_exists(area_name)){
        throw WorldAreaNameIsTaken();
    }
    switch(type){
        case PLAIN:{
            AreaPtr inserted(new Plain(area_name));
            this->area_map.insert(std::pair<string,AreaPtr>(area_name,
                                                               inserted));
            break;
        }
        case MOUNTAIN:{
            AreaPtr inserted(new Mountain(area_name));
            this->area_map.insert(std::pair<std::string,AreaPtr>(area_name,
                                                               inserted));
            break;
        }
        case RIVER:{
            AreaPtr inserted(new River(area_name));
            this->area_map.insert(std::pair<std::string,AreaPtr>(area_name,
                                                               inserted));
            break;
        }
    }
}


/**
 * Add a new group to the world, with given size, clan, and starting
 *  area (the group "arrives" to the area).
 *  The group should have 77 morale when entering the area.
 * @param group_name The name of the new group
 * @param clan_name The name of the clan of the group.
 * @param num_children Number of children in the group.
 * @param num_adults Number of the adults in the group.
 * @param area_name The name of the area the group starts in (arrives
 *  to it first)
 * @throws WorldInvalidArgument If group_name is empty, or at least
 * one of num_children and num_adults is negative, or both are 0.
 * @throws WorldGroupNameIsTaken If there is already a group with the
 *  given name in the world.
 * @throws WorldClanNotFound If there is no clan with the given name
 *  in the world.
 * @throws WorldAreaNotFound If there is no area with the given name
 *  in the world.
 */
void World::addGroup(const string& group_name, const string& clan_name, int
num_children, int num_adults, const string& area_name) {
    if (group_name.empty() || num_children < 0 || num_adults < 0 ||
        (num_adults == 0 && num_children == 0)) {
        throw WorldInvalidArgument();
    }
    if (check_group_exists(group_name)) {
        throw WorldGroupNameIsTaken();
    }
    if (!check_clan_exists(clan_name)) {
        throw WorldClanNotFound();
    }
    if (!check_area_exists(area_name)) {
        throw WorldAreaNotFound();
    }
    Group new_group(group_name, num_children, num_adults);
    new_group.changeClan(clan_name);
    clan_map.at(clan_name).addGroup(new_group);
    ////need to change morale to 77!!!!
    (*(area_map.at(area_name))).groupArrive(group_name, clan_name, clan_map);
}


/**
 * Make an area reachable from another area.
 * (make 'to' reachable from 'from')
 * @param from The name of the area that the other area will be
 * reachable from.
 * @param to The name of the area that should be reachable from the
 * other area.
 * @throws WorldAreaNotFound If at least one of the areas isn't in
 *  the world.
 */
void World::makeReachable(const string& from, const string& to){
    if(!check_area_exists(from) || !check_area_exists(to)){
        throw WorldAreaNotFound();
    }
    (*(area_map.at(from))).addReachableArea(to);
}

/**
 * Move a group to destination area.
 * @param group_name The name of the group that should move
 * @param destination The name of the area the group should move to.
 * @throws WorldGroupNotFound If there is no group with the given
 *  name in the world.
 * @throws WorldAreaNotFound If there is no area with the given name
 *  in the world.
 * @throws WorldGroupAlreadyInArea If the group is already in the
 *  destination area.
 * @throws WorldAreaNotReachable If the destination area isn't
 *  reachable from the area the group is currently in.
 */
void World::moveGroup(const string& group_name, const string& destination){
    if(!check_group_exists(group_name)){
        throw WorldGroupNotFound();
    }
    if(!check_area_exists(destination)){
        throw WorldAreaNotFound();
    }
    if((*(area_map.at(destination))).getGroupsNames().contains(group_name)){
        ///if the group is in the set of groups in the area
        throw WorldGroupAlreadyInArea();
    }
    std::map<string,AreaPtr>::iterator iter1;
    for(iter1 = area_map.begin();iter1 != area_map.end();++iter1){
        ///searching for the group in the areas
        if((*(iter1->second)).getGroupsNames().contains(group_name)){
            break;///we found where the group is
        }
    }
    if(!(*(iter1->second)).isReachable(destination)){
       throw WorldAreaNotReachable();
    }
    std::map<string,Clan>::iterator iter2;
    for(iter2 = clan_map.begin();iter2 != clan_map.end();++iter2){
        ///searching for the group in the areas
        if(iter2->second.doesContain(group_name)){
            break;///we found where the group is
        }
    }
    (*(area_map.at((*(iter1->second)).getName(*(iter1->second))))).
            groupLeave(group_name);
    (*(area_map.at(destination))).groupArrive(group_name,iter2->second.getName(),
                                              clan_map);
}

/**
 * Make two clans friends.
 * @param clan1 The name of one of the clans to become friends.
 * @param clan2 The name of the other clan to become friends with.
 * @throws WorldClanNotFound If at least one of the clans isn't in
 * the world.
 */
void World::makeFriends(const string& clan1, const string& clan2){
    if(!check_clan_exists(clan1) || !check_clan_exists(clan2)){
        throw WorldClanNotFound();
    }
    clan_map.at(clan1).makeFriend(clan_map.at(clan2));
}


/**
 * Unite two clans to a new clan with a new name.
 * @param clan1 The name of one of the clan that need to unite.
 * @param clan2 The name of the second clan that need to unite.
 * @param new_name The name of the new clan.
 * @throws WorldInvalidArgument If new_name is empty.
 * @throws WorldClanNameIsTaken If new_name was already used for a
 * clan that is not clan1 or clan2.
 * @throws WorldClanNotFound If clan1 or clan2 are not in the world.
 */
void World::uniteClans(const string& clan1, const string& clan2, const
string& new_name){
    if(new_name.empty()){
        throw WorldInvalidArgument();
    }
    if(check_clan_exists(new_name)){
        throw WorldClanNameIsTaken();
    }
    if(!check_clan_exists(clan1) || !check_clan_exists(clan2)){
        throw WorldClanNotFound();
    }
    clan_map.at(clan1).unite(clan_map.at(clan2),new_name);
    ///now clan1 has the new name and is the united clan, we need to remove clan2
    Clan temp_clan = clan_map.at(clan1) ;
    clan_map.erase(clan1);
    clan_map.erase(clan2);
    clan_map.insert(std::pair<string,Clan>(new_name,temp_clan));
    ///should we do something with the friend??
}

/**
 * Print a group to the ostream, using the group output function (<<).
 * Add to it another line (after the last one of a regular print) of
 * the form:
 *      Group's current area: [area name]
 * That print the area which the group is in.
 * @param os The ostream to print into.
 * @param group_name The name of the group to print.
 * @throws WorldGroupNotFound If there is no group in the world with
 *  the given name.
 */
void World::printGroup(std::ostream& os, const string& group_name) const{
    if(!check_group_exists(group_name)){
        throw WorldGroupNotFound();
    }
    std::map<string,Clan>::const_iterator iter2;
    for(iter2 = clan_map.begin();iter2 != clan_map.end();++iter2){
        ///searching for the group in the areas
        if(iter2->second.doesContain(group_name)){
            Group printing(*(*iter2).second.getGroup(group_name));
            os<<printing;
            break;///we found where the group is
        }
    }
    std::map<string,AreaPtr>::const_iterator iter1;
    for(iter1 = area_map.begin();iter1 != area_map.end();++iter1){
        if((*(iter1->second)).getGroupsNames().contains(group_name)){
            os<<"Group's current area: "<<iter1->first<<endl;
        }
    }


}
/**
 * Print a clan to the ostream, using the clan output function.
 * @param os The ostream to print into.
 * @param clan_name The name of the clan to print.
 * @throws WorldClanNotFound If there is no clan with the given name
 *  in the world.
 */
void World::printClan(std::ostream& os, const string& clan_name) const{
    if(!check_clan_exists(clan_name)){
        throw WorldClanNotFound();
    }
    os << clan_map.at(clan_name);
}

/**
    * checks if a group is in the world
    * if exists - true, if not - false
        */
bool World::check_area_exists(const string& area_name){
    auto iter1 = area_map.find(area_name);
    if(iter1 == area_map.end()){
        return false;
    }
    return true;
}

/**
 * checks if a group is in the world
 */
bool World::check_clan_exists(const string& clan_name){
    auto iter1 = clan_map.find(clan_name);
    if(iter1 == clan_map.end()){
        return false;
    }
    return true;
}
const bool World::check_clan_exists(const string& clan_name)const {
    auto iter1 = clan_map.find(clan_name);
    if(iter1 == clan_map.end()){
        return false;
    }
    return true;
}
/**
 * checks if a group is in the world
 */
bool World::check_group_exists(const string& group_name){
    for(auto iter1 = clan_map.begin();iter1!=clan_map.end();++iter1){
        if(iter1->second.doesContain(group_name)){
            return true;
        }
    }
    return false;
}
const bool World::check_group_exists(const string& group_name)const{
    for(auto iter1 = clan_map.begin();iter1!=clan_map.end();++iter1){
        if(iter1->second.doesContain(group_name)){
            return true;
        }
    }
    return false;
}
