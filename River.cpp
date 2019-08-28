#include "River.h"

using namespace mtm;
River::River(const std::string& name):
        Area(name)
{
    if (name==""){
        throw AreaInvalidArguments();
    }
}
void River::groupArrive(const string &group_name, const string &clan,
                        map<string,Clan> &clan_map) {
    Area::groupArrive(group_name, clan, clan_map);
    //if (groups.size() == 1) {
   //     return;
  //  }
    sortVector();
    map<string, Clan>::iterator it = clan_map.find(clan);// find clan
    Clan check = it->second;
    GroupPointer addedGroup = check.getGroup(group_name);//find group
    string tempClan;
    vector<GroupPointer>::const_iterator iter = groups.begin();
    while (iter != groups.end()) {
        if (clan_map.at(clan).isFriend(clan_map.at((*(*iter)).getClan()))){
            if ((*iter)!=addedGroup) {
                if ((*(*iter)).trade(*addedGroup)) {
                    return;//trade succeeded
                }
            }
        }
        iter++;
    }
}