
#ifndef HW4_RIVER_H
#define HW4_RIVER_H
#include "Area.h"
#include <string>
#include <map>
#include "Clan.h"
#include "Group.h"
#include <vector>
#include <memory>
using std::string;
using std::shared_ptr;
using std::map;
using std::vector;
namespace mtm {
    class River : public Area {
    public:
        /**
          * Constructor
          * @param name The name of the River
          * @throws AreaInvalidArguments If the name is empty
          */

        explicit River(const std::string &name);

        ~River()= default;
/**
             * Get a group into the River.
             * @param group_name The name of the group that get into the River.
             * @param clan The name of the clan that the group belongs to.
             * @param clan_map The map of clans that contains the clan of the group
             * @throws AreaClanNotFoundInMap If there is no clan with the given
             * name in the map.
             * @throws AreaGroupNotInClan If there is no group with the given name
             * in the clan with the given name in the map.
             * @throws AreaGroupAlreadyIn If group with same name already in the
             *  River.
             *
             * Assert that the map does contain the clan that the group belongs to.
             */
        void groupArrive(const string &group_name, const string &clan,
                         map<string, Clan> &clan_map) override;
    };
}


#endif //HW4_RIVER_H
