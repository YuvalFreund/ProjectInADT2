#ifndef HW4_PLAIN_H
#define HW4_PLAIN_H
#include "Area.h"
#include <string>
#include <map>
#include <sstream>
#include "Clan.h"
#include "Group.h"
#include <vector>
#include <memory>
using std::string;
using std::shared_ptr;
using std::map;
using std::vector;
namespace mtm {
    class Plain : public Area {
    public:
        /**
          * Constructor
          * @param name The name of the River
          * @throws AreaInvalidArguments If the name is empty
          */
        explicit Plain(const std::string &name);

        ~Plain()= default;
        string divided_name( map<string, Clan> &clan_map,
                             const string &group) {
            int place = 2;
            string nameGroup = group;
            std::stringstream tempGroup;
            do {
                tempGroup.str("");
                tempGroup.clear();
                tempGroup << nameGroup << "_" << place++;
            } while(nameAppears(clan_map, tempGroup.str()));
            return tempGroup.str();
        }
        bool nameAppears(map<string, Clan> &clan_map,
                         string tempGroup) {
            map<string, Clan>::const_iterator iter = clan_map.begin();
            while (iter != clan_map.end()) {
                Clan addedClan = iter->second;
                if (addedClan.doesContain(tempGroup)) {
                    return true;
                }
                iter++;
            }
            return false;
        }
            /**
            * Get a group into the Plain.
            * @param group_name The name of the group that get into the Plain.
            * @param clan The name of the clan that the group belongs to.
            * @param clan_map The map of clans that contains the clan of the group
            * @throws AreaClanNotFoundInMap If there is no clan with the given
            * name in the map.
            * @throws AreaGroupNotInClan If there is no group with the given name
            * in the clan with the given name in the map.
            * @throws AreaGroupAlreadyIn If group with same name already in the
            *  Plain .
            *
            * Assert that the map does contain the clan that the group belongs to.
            */
            void groupArrive(const string &group_name, const string &clan,
                             map<string, Clan> &clan_map) override;
    };
}
#endif //HW4_PLAIN_H
