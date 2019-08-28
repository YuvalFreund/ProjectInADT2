
#ifndef HW4_MOUNTAIN_H
#define HW4_MOUNTAIN_H
#include "Area.h"
#include "Group.h"
#include "Clan.h"
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <memory>
using std::string;
using std::shared_ptr;
using std::map;
using std::vector;
namespace mtm {
    class Mountain : public Area {
        GroupPointer controlGr; //group that controls the mountain
    public:
        ~Mountain()= default;
        /**
          * Constructor
          * @param name The name of the Mountain
          * @throws AreaInvalidArguments If the name is empty
          */
        explicit Mountain(const std::string &name);

        /**
             * Get a group into the Mountain.
             * @param group_name The name of the group that get into the Mountain.
             * @param clan The name of the clan that the group belongs to.
             * @param clan_map The map of clans that contains the clan of the group
             * @throws AreaClanNotFoundInMap If there is no clan with the given
             * name in the map.
             * @throws AreaGroupNotInClan If there is no group with the given name
             * in the clan with the given name in the map.
             * @throws AreaGroupAlreadyIn If group with same name already in the
             *  Mountain.
             *
             * Assert that the map does contain the clan that the group belongs to.
             */
        void groupArrive(const string &group_name, const string &clan,
                         map<string, Clan> &clan_map) override ;


        /**
        * Get a group out of the Mountain.
        * @param group_name The name of the leaving group.
        * @throws AreaGroupNotFound If there is no group in the Mountain with the
        *  same name;
        */
         void groupLeave(const std::string& group_name) override;
    };
}
#endif //HW4_MOUNTAIN_H
