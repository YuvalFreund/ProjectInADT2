#include "Group.h"
using std::ostream;
using std::string;
using namespace mtm;
int ceiling (double value){
    if (value-(int)value==0){
        return value;
    }
    return (int)value+1;
}
int min (int a,int b){
    if (a < b){
        return a;
    }
    return b;
}

Group::Group(const std::string& name, const std::string& clan, int children,
      int adults, int tools, int food, int morale) :
    name(name), clan(clan), children(children), adults(adults),
            tools(tools) , food(food) ,morale(morale) {
   if (tools < 0 || adults < 0 || food < 0 || morale <0
           || name.length()==0  || children < 0 || morale>100 ||
           (adults==0 &&children==0)){
       throw GroupInvalidArgs();
   }
}


Group::Group(const std::string& name, int children, int adults):
    name(name),children(children),adults(adults),
    tools(adults*4),food(adults*3 + 2*children),
    morale(70){
    if(adults<0 || children < 0 || name.length()==0||
            (children==0 && adults==0)){
        throw GroupInvalidArgs();
    }
}
Group::Group() {
}
/**
 * Copy constructor
 * @param other The group to copy
 */
Group::Group(const Group& other) = default;//we can use default


/** Destructor
 */
Group::~Group()= default;//we can use default
/**
 * Get the name of the group
 * @return The name of the group
 */
const std::string& Group::getName() const{
    return this->name;
}

/**
 * Get the amount of people (children + adults) in the group.
 * @return  Amount of people in the group
 */
int Group::getSize() const{
    return (this->adults + this->children);
}
/**
   * Get the power of the group
   * @return  power of people in the group
   */
int Group::getPower() const{
    double Power =((this->adults*10)+(this->children*3))*
            ((10*this->tools) + (this->food))*morale;
    return (int) (Power/100);
}
/**
 * @return The name of the clan that the group belongs to.
 */
const std::string& Group::getClan() const{
    return this->clan;
}
/**
 * Change the clan of the group.
 * If the group had a different clan before, reduce morale by 10%.
 * If the group's clan was the same as the given one, do nothing.
 * Otherwise, increase morale by 10%. (floor in both cases)
 *
 * floor: 0.5 -> 0, 1.5 -> 1 etc...
 * @param clan The name of the new clan that the groups will belong to.
 */
void Group::changeClan(const std::string& clan) {
    if(clan==""){
        this->clan = "";
        return;
    }
    if (this->clan == "" && clan.length()!=0) {
        double  new_morale = this->morale *1.1;
        if (new_morale>100){
            new_morale=100;
        }
        this->morale = (int) new_morale;
        this->clan=clan;
    }
    if (this->clan == clan) {
        return;
    }
    if (this->clan != clan){
        double new_morale = this->morale*0.9;
        this->morale = (int) new_morale;
        this->clan=clan;
    }
}

/**
 * Compare two groups. according to power (defined here), and name.
 *
 * Power: ((10*number_of_adults + 3 * number_of_children) *
 * (10 * number_of_tools + number_of_food)*morale)/100 (floor)
 *
 * @param rhs
 * @return true, if power(this) < power(rhs), or if they're equal and
 *  this group's name is smaller (lexicographic) than rhs's name.
 *  false otherwise.
 */

bool Group::operator<(const Group& rhs) const{
    int power_rhs = rhs.getPower();
    int power_this = this->getPower();
    if (power_this < power_rhs) {
        return true;
    }
    if (power_this==power_rhs){
        if (rhs.name.std::string::compare(this->name)>0){
            return true;
        }
    }
    return false;
}
/**
 * Compare two groups. according to power, and name.
 * @param rhs
 * @return true, if power(this) > power(rhs), or if they're equal and
 *  this group's name is bigger (lexicographic) than rhs's name.
 *  false otherwise.
 */
bool Group::operator>(const Group& rhs) const{
    int  power_rhs = rhs.getPower();
    int power_this = this->getPower();
    if (power_this>power_rhs) {
        return true;
    }
    if (power_this==power_rhs){
        if (rhs.name.::string::compare(this->name) <0 ){
            return true;
        }
    }
    return false;
}

/**
 * Compare two groups. according to power, and name.
 * @param rhs
 * @return true, if power(this) < power(rhs), or if they're equal and
 *  this group's name is not bigger (lexicographic) than rhs's name.
 *  false otherwise.
 */
bool Group::operator<=(const Group& rhs) const{
    int  power_rhs = rhs.getPower();
    int power_this = this->getPower();
    if (power_this<power_rhs) {
        return true;
    }
    if (power_rhs==power_this) {
        if (rhs.name.::string::compare(this->name) >=0 ) {
            return true;
        }
    }
    return false;
}

/**
 * Compare two groups. according to power, and name.
 * @param rhs
 * @return true, if power(this) > power(rhs), or if they're equal and
 *  this group's name is not smaller (lexicographic) than rhs's name.
 *  false otherwise.
 */
bool Group::operator>=(const Group& rhs) const{
    int  power_rhs = rhs.getPower();
    int power_this = this->getPower();
    if (power_this>power_rhs) {
        return true;
    }
    if (power_rhs==power_this) {
        if (rhs.name.::string::compare(this->name) <=0 ) {
            return true;
        }
    }
    return false;
}
void Group::setEmpty(){
    this->food=0;
    this->morale=0;
    this->adults=0;
    this->tools=0;
    this->children=0;
    this->name="";
    this->clan="";
}

/**
 * Compare two groups. according to power, and name.
 * @param rhs
 * @return true, if power(this) == power(rhs), and this group's name is
 * equal to rhs's name.
 * false otherwise.
 */
bool Group::operator==(const Group& rhs) const{
    int  power_rhs = rhs.getPower();
    int power_this = this->getPower();
    if (power_this==power_rhs) {
        if (rhs.name == this->name) {
            return true;
        }
    }
    return false;
}

/**
 * Compare two groups. according to power, and name.
 * @param rhs
 * @return true, if power(this) != power(rhs), and this group's name
 * isn't equal to rhs's name.
 * false otherwise.
 */
bool Group::operator!=(const Group& rhs) const{
    int  power_rhs = rhs.getPower();
    int power_this = this->getPower();
    if (power_this!=power_rhs) {
        if (rhs.name != this->name) {
            return true;
        }
    }
    return false;
}

/**
 * Try to unite two groups, this group, and given group.
 * Will succeed only if the two groups are not the same group,
 * belong to the same clan, both have at least 70 morale, and they
 * don't surpass together a given amount of people.
 * Should the union succeed, this group will change according to:
 * - name = name of the more powerful group
 * - clan = old clan
 * - children = sum of the children in the two groups
 * - adults = sum of the adults in the two groups
 * - tools = sum of the tools in the two groups
 * - food = sum of the food in the two groups
 * - morale = average of the morales, counting the amount of people
 * (floor)
 *
 * The other group will become empty.
 * @param other The group to unite with.
 * @param max_amount If the two groups have more people combined then
 *  max_amount, then the union fails.
 * @return True if Unite was successful, false otherwise.
 */
bool Group::unite(Group& other, int max_amount){
    if (this==&other || this->morale < 70 || other.morale < 70
        || (this->getClan() != other.getClan())
            ||(this->getSize() + other.getSize()) >max_amount) {
        return false;
    }
    //unite will succeed
    if (*this<other) {
        name = other.getName();
    }
    double new_morale= (this->morale*this->getSize()+
                        other.morale*other.getSize());
    this->children+=other.children;
    this->adults+= other.adults;
    this->tools+=other.tools;
    this-> food+=other.food;
    this-> morale = (int) (new_morale/this->getSize());
    other.setEmpty();
    return true;
}

/**
 * Divide the group.
 *
 * After the division this group will have the same
 *  name, clan, morale. And ceiling of half of children , adults ,
 *  tools, food
 *
 * The other group will have a new name, same clan, same morale,
 *  and floor of half of children , adults, tools, food.
 *
 * Ceiling: 0.5 -> 1, 1.5 -> 2 etc...
 *
 * floor: 0.5 -> 0, 1.5 -> 1 etc...
 * @param name The name of the new group.
 * @return The new group, that divided from this group.
 * @throws GroupInvalidArgs If name is empty.
 * @throws GroupCantDivide If the divided group Would be empty (can
 * only happen of this group has no more than 1 child and 1 adult).
 */
Group Group::divide(const std::string& name) {
    if (name.length()==0) {
        throw GroupInvalidArgs();
    }
    if (adults<2 && children<2) {
        throw GroupCantDivide();
    }
    int floor_children= this->children/2;
    int floor_food= this->food/2;
    int floor_adults= this->adults/2;
    int floor_tools= this->tools/2;
    Group divided(name,this->clan,floor_children,floor_adults,floor_tools,
    floor_food,this->morale);
    this->adults -= floor_adults;
    this->food -= floor_food;
    this->children -= floor_children;
    this->tools -= floor_tools;
    return divided;
}


/**
 * This group fights an opponent group. The bigger group according to
 *  the relational operators is the winner. If both groups are equal,
 *  the groups will not fight.
 *
 * Fights effects on the loser group:
 * - Losing third of each of the children and adult population (ceiling)
 * - Losing Half of the tools, and half of the food (ceiling)
 * - Morale decreases by 20%. (ceiling)
 * For example: if a group that had 5 adults and 3 tools lost and 50
 * morale, it will have 3 adults, 1 tool, and 40 morale after the fight.
 *
 * Fights effects on the winner group:
 * - Losing a quarter of the adults (floor) and no children.
 * - Losing a quarter of the tools (floor).
 * - gaining half of the food the loser group lost in the fight. (floor)
 *      The gain is equal to ceiling(loser.food / 2) / 2, even if the
 *      loser group lost all of it's people.
 * - Morale increases by 20%. (ceiling)
 * @param opponent The group to fight with.
 * @return WON if this group won, LOST if this group lost, and DRAW
 * in case the 2 groups are equal.
 * @throws GroupCantFightWithItself if opponent is the same as this
 * @throws GroupCantFightEmptyGroup if this group, or the other group
 *  is empty (i.e no people).
 */
void Group::makeFight(Group& winner, Group& loser){
    double winner_adults =  winner.adults/4;
    winner.adults-=ceil(winner_adults);
    double winner_tools =  winner.tools/4;
    winner.tools-=ceil(winner_tools);
    double winner_morale= winner.morale*1.2;
    if (winner_morale> 100){
        winner_morale=100;
    }
    winner.morale = ceiling(winner_morale);
    loser.food -= ceil((double)loser.food/2);
    winner.food += ceil(loser.food);
    double loser_morale= loser.morale*0.2;
    loser.morale -= ceiling(loser_morale);
    loser.tools= loser.tools/2;
    loser.adults= loser.adults*2/3;
    loser.children = loser.children*2/3;
    if(loser.getSize()==0){
        loser.setEmpty();
    }
}
FIGHT_RESULT Group::fight(Group& opponent) {
    if (this == &opponent) {
        throw GroupCantFightWithItself();
    }
    if(getSize()==0 || opponent.getSize()==0) {
        throw GroupCantFightEmptyGroup();
    }
    if (*this==opponent){
        return DRAW; // There is a tie
    }
    if(*this>opponent){
        makeFight(*this,opponent);
        return WON;
    }
    makeFight(opponent,*this);
    return LOST;
}

/**
 * Try to do a trade between the two groups.
 * Each groups tries make its tools and food equal.
 * To do that, each group offers |group's tools - group's food| / 2
 * (ceiling) of the resource it has more of.
 * If the other group offers the other resource, a trade is made.
 * In the trade, each group gives the average of the offers [(offer1 +
 * offer2)/2 (ceiling)], from the resource it has more of. A group
 * can't give more tools or food than it has, and the two groups
 * always trade the same amount of resources.
 *
 * If one of the groups has the same amount of tools as amount of
 * food, or if both has more tools than food, or vice versa,
 * the trade would not be made.
 * @param other Group to trade with.
 * @return true if a trade was made, false otherwise.
 * @throws GroupCantTradeWithItself if other is the same as this
 */
void Group::make_trade(Group& other,int average){
    if(food > tools){///this is trading food, we know that other has more tools
        average = min(food,average);
        average = min(other.tools,average);///now we have the lowest value for trading
        food-=average;
        other.tools-=average;
        tools+=average;
        other.food+=average;
    }
    else{
        average = min(tools,average);
        average = min(other.food,average);///now we have the lowest value for trading
        food+=average;
        other.tools+=average;
        tools-=average;
        other.food-=average;
    }
}
bool Group::trade(Group& other) {
    if(this == &other){
        throw GroupCantTradeWithItself();
    }
    if (food == tools || other.tools == other.food ||
        (food < tools && other.food < other.tools) ||
        (food > tools && other.food > other.tools)) {
        return false;///trade fails
    }
    ///trade succeeds, now trading
    double average = 0;
    if(food>tools){
        average = ceil((ceil((food-tools)/2)+ceil(other.tools-other.food)/2));
    }
    else{
        average = ceil((ceil((tools-food)/2)+ceil(other.food-other.tools)/2)/2);
    }
    make_trade(other,average);
    return true;
}


/**
 * Print the data of a given group. Output form:
 *      Group's name: [group's name]
 *      Group's clan: [group's clan]
 *      Group's children: [group's children]
 *      Group's adults: [group's adults]
 *      Group's tools: [group's tools]
 *      Group's food: [group's food]
 *      Group's morale: [group's morale]
 *
 * @param os the output stream
 * @param group The group to print
 * @return the output stream
 */
    std::ostream& mtm::operator<<(std::ostream& os, const Group& group){
    if (group.getSize()==0){
        return os;
    }
    os<< "Group's name: "<<group.getName()<<std::endl;
    os<< "Group's clan: "<<group.getClan()<<std::endl;
    os<< "Group's children: "<<group.children<<std::endl;
    os<< "Group's adults: "<<group.adults<<std::endl;
    os<< "Group's tools: "<<group.tools<<std::endl;
    os<< "Group's food: "<<group.food<<std::endl;
    os<< "Group's morale: "<<group.morale<<std::endl;
    return os;
}


