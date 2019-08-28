#include "Mountain.h"
using namespace mtm;

using std::ostream;
Mountain::Mountain(const std::string& name):
        Area(name), controlGr(NULL)
{
    if (name==""){
        throw AreaInvalidArguments();
    }
}
void Mountain::groupArrive(const string &group_name, const string &clan,
                           map<string,Clan> &clan_map) {
    Area::groupArrive(group_name, clan, clan_map);
    if (groups.size() == 1) {
        controlGr = (*(groups.begin()));
        return;
    }
    map<string, Clan>::iterator it = clan_map.find(clan);// find clan
    Clan addedClan = it->second;
    GroupPointer addedGroup = addedClan.getGroup(group_name);//find group
    const string controlClan = (*controlGr).getClan();
    if (clan == controlClan) {
        if ((*(controlGr)) < (*(addedGroup))) {
            controlGr = addedGroup;
        }
    }
    if (clan != controlClan) {
        ((*(controlGr)).fight(*(addedGroup)));

        if (((*(controlGr)) < (*(addedGroup)))) {
            controlGr = addedGroup;
        }
    }
}

void Mountain::groupLeave(const std::string& group_name) {
    Area::groupLeave(group_name);
    if (groups.size() == 0) {
        controlGr = nullptr;
        return;
    }
    if (group_name == (*controlGr).getName()) {// leaving group is control
        const string controlClan = (*controlGr).getClan();
        sortVector();
        vector<GroupPointer>::const_iterator iter = groups.begin();
        while (iter != groups.end()) {
            string tempClan = (*(*iter)).getClan();
            if (tempClan == controlClan) {
                controlGr = (*iter);
                break;
            }
            iter++;
        }
        if (iter == groups.end()) {
            controlGr = (*groups.begin());
        }
    }
}
