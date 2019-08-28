#include "Plain.h"
using namespace mtm;
Plain::Plain(const std::string& name):
        Area(name)
{
    if (name==""){
        throw AreaInvalidArguments();
    }
}
void Plain::groupArrive(const string &group_name, const string &clan,
                        map<string,Clan> &clan_map) {
    Area::groupArrive(group_name,clan,clan_map);
    map<string, Clan>::iterator it = clan_map.find(clan);// find clan
    Clan addedClan = it->second;
    GroupPointer addedGroup = addedClan.getGroup(group_name);//find group
    vector<GroupPointer>::const_iterator iter = groups.begin();
    const int thirdOfClan = addedClan.getSize() / 3;
    sortVector();
    if (thirdOfClan > (*addedGroup).getSize()) {
        while (iter != groups.end()) {
            string tempClan = (*(*iter)).getClan();
            if (tempClan == clan) {
                if ((*(*iter)).unite(*addedGroup, thirdOfClan)) {
                    return;
                }
            }
            iter++;
        }
    }
    if (thirdOfClan < (*addedGroup).getSize() &&
            (*addedGroup).getSize()>= 10 ){
        string new_name = divided_name(clan_map,group_name);
        Group divided = (*addedGroup).divide(new_name);
        clan_map.at(clan).addGroup(divided);
        GroupPointer temp(new Group(divided));
        this->groups.push_back(temp);
    }
}


//nothing special happens when group leaves, can use default from area