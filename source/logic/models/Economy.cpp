#include "../models/Economy.h"

/** multiplies gold with the profit multiplier and adds the result to the gold amount the player has
 *@param enemiesDefeated a list of enemies that were previously defeated in case they drop different
 *amounts of gold
 */
void Economy::earnGold(std::vector<Enemy*> enemiesDefeated) {
    for (Enemy* enemy: enemiesDefeated) {
        goldAmount+=enemy->reward*profitMultiplier; //ask to create a reward or price attribute
    }
}

/** @returns the goldAmount, useful for displaying */
int Economy::getGoldAmount() {
    return goldAmount;
}

/** buys a tower and subtracts its price from the goldAmount
 * @param towerToBuy is the tower to be purchased
 * @returns true if the tower was bought successfully
 * @returns false if the tower was not bought
 */
bool Economy::buyTower(Tower* towerToBuy) {

    if (goldAmount>=towerToBuy->price) {
        goldAmount-= towerToBuy->price;
        return true;
    }
    //handle purchase failure here
    return false;

}


