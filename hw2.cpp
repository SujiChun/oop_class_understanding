#include <iostream>
using namespace std;

class Enemy {
private:
	int id;
	string type;
	int distance;
	int energy;
public:
	Enemy(int enemyId, string t, int d, int e);
	~Enemy();
	int getId() const { return id; }
	int getEnergy() const {return energy;}
	string getType() const { return type; }
	int getDistance() const { return distance; }
	bool IsDefeated() const { return energy <= 0; }
	void TakeDamage(int dmg);
};
Enemy::Enemy(int enemyId, string t, int d, int e) : id(enemyId), type(t), distance(d), energy(e) {
	cout << "[Constructor] Enemy " << id << " of type " << type << " created with distance: " << distance << " and energy: " << energy << endl;
}
Enemy::~Enemy() {
    cout << "[Destructor] Enemy " << id << " destroyed." << endl;
}
void Enemy::TakeDamage(int dmg){
    this->energy -= dmg;
    if (this->energy < 0) {
		this->energy = 0;
    }
}

class IAttackStrategy {
private:
    string weapon;
    int damage;
public:
    IAttackStrategy(string w, int dmg);
    ~IAttackStrategy();
    string getWeapon() const { return weapon; }
    void Attack(int dalgooId, Enemy& enemy);
};
IAttackStrategy::IAttackStrategy(string w, int dmg) : weapon(w), damage(dmg) {
    cout << "[Constructor] Attack Strategy created with weapon: " << weapon << " and damage: " << damage << endl;
}
IAttackStrategy::~IAttackStrategy() {
    cout << "[Destructor] IAttackStrategy destroyed." << endl;
}
void IAttackStrategy::Attack(int dalgooId, Enemy& enemy) {
    cout << "[Attack] Dalgoo" << dalgooId << " attacks Enemy " << enemy.getId() << " with " << weapon << " causing " << damage << " damage." << endl;
	enemy.TakeDamage(damage);
}

class Dalgoo {
private:
	IAttackStrategy* attackStrategy;
	static int totalAttacks;
	int id;
public:
	Dalgoo(int instanceId);
	~Dalgoo();
	void SetAttackStrategy(IAttackStrategy* strategy);
	void PerformAttack(Enemy& enemy);
    static int GetTotalAttacks() { return totalAttacks; };
};
Dalgoo::Dalgoo(int instanceId) : id(instanceId), attackStrategy(nullptr){
	totalAttacks = 0;
    cout << "[Constructor] Dalgoo instance " << id << " created." << endl;
}
Dalgoo::~Dalgoo() {
    cout << "[Destructor] Dalgoo instance " << id << " destroyed." << endl;
}
void Dalgoo::SetAttackStrategy(IAttackStrategy* strategy) {
    this->attackStrategy = strategy;
    cout << "[SetAttackStrategy] Dalgoo" << id << " sets attack strategy to" << strategy->getWeapon() << endl;
}
void Dalgoo::PerformAttack(Enemy& enemy) {
    totalAttacks = 0;
	cout << "[PerformAttack] Dalgoo" << id << " performs an attack: " << endl;
    if (attackStrategy) {
        attackStrategy->Attack(id, enemy);
        totalAttacks++;
    }
    else {
        cout << "[Error] Dalgoo" << id << " has no attack strategy set" << endl;
        return;
    }
    if (enemy.IsDefeated()) {
        cout << "[PerformAttack] Enemy " << enemy.getId() << " has been defeated!" << endl;
	}
    else {
        cout << "[PerformAttack] Enemy " << enemy.getId() << "'s remaining energy: " << enemy.getEnergy() << endl;
    }
}

class EnemyManager {
private:
	Enemy** enemies;
	int enemiesCount = 0;
	int capacity = 0;
public:
	EnemyManager();
	~EnemyManager();
	int GetTotalEnemyCount() const { return enemiesCount; }
    void ResizeArray(int newCapacity);
	void AddEnemy(Enemy* enemy);
	Enemy* GetEnemy(int enemyIdx);
	void DisplayAllEnemies();
	bool AreAllEnemiesDefeated();
};
EnemyManager::EnemyManager() : enemies(nullptr), enemiesCount(0), capacity(0) {
    cout << "[Constructor] EnemyManager created." << endl;
}
EnemyManager::~EnemyManager() {
    for (int i = 0; i < enemiesCount; i++) {
        delete enemies[i];
    }
    delete[] enemies;
    cout << "[Destructor] EnemyManager destroyed." << endl;
}
void EnemyManager::ResizeArray(int newCapacity) {
    Enemy** newEnemies =new Enemy * [newCapacity];
    for (int i = 0; i < enemiesCount; i++) {
        newEnemies[i] = enemies[i];
    }
    delete[] enemies;
    enemies = newEnemies;
    capacity = newCapacity;
}
void EnemyManager::AddEnemy(Enemy* enemy) {
    int newCapacity;
    if (enemiesCount == capacity) {
        if (capacity == 0) {
            newCapacity = 2;
        }
        else {
            newCapacity = capacity * 2;
        }
        ResizeArray(newCapacity);
    }
    enemies[enemiesCount] = enemy;
    enemiesCount++;
    cout << "[AddEnemy] Enemy " << enemy->getId() << " added of type" << enemy->getType() << endl;
}
Enemy* EnemyManager::GetEnemy(int enemyIdx) {
    int id = -1;
    for (int i = 0; i < enemiesCount; i++) {
        if (enemies[i]->getId() == enemyIdx ) {
            id = i;
            break;
        }
	}
    if (id == -1) {
        cout << "[Error] Enemy with ID " << enemyIdx << " not found." << endl;
        return nullptr;
	}
    return enemies [id];
}
void EnemyManager::DisplayAllEnemies() {
    cout << "[DisplayAllEnemies] Enemy Energy Levels:" << endl;
    for (int i = 0; i < enemiesCount; i++) {
        cout << i+1<< ") Enemy " << enemies[i]->getId() << " (" << enemies[i]->getType()
            << ") - Distance: " << enemies[i]->getDistance()
            << "/ Energy: " << enemies[i]->getEnergy()
            << " " << (enemies[i]->IsDefeated() ? "[Defeated]" : "") << endl;
    }
}
bool EnemyManager::AreAllEnemiesDefeated() {
    for (int i = 0; i < enemiesCount; i++) {
        if (!enemies[i]->IsDefeated()) {
            return false;
        }
    }
    return true;
}


int main() {
    cout << "===== Part 1: Constructor =====" << endl;
    Dalgoo dalgoo1(1), dalgoo2(2);
    Enemy* enemy1 = new Enemy(1, "Guardian", 10, 20);
    Enemy* enemy2 = new Enemy(2, "Ghost", 15, 20);
    Enemy* enemy3 = new Enemy(3, "Dragon Boss", 5, 50);
    EnemyManager enemyManager;

    cout << "\n===== Part 2: Initializing Dalgoo's AttackStrategy =====" <<
        endl;
    IAttackStrategy bungeobbang("Bungeobbang", 10);
    dalgoo1.SetAttackStrategy(&bungeobbang);
    dalgoo2.SetAttackStrategy(&bungeobbang);

    cout << "\n===== Part 3: Initializing EnemyManager =====" << endl;
    enemyManager.AddEnemy(enemy1);
    enemyManager.AddEnemy(enemy2);
    enemyManager.AddEnemy(enemy3);
    enemyManager.DisplayAllEnemies();

    cout << "\n===== Part 4: Dalgoo 1 Attack Enemy 1 =====" << endl;
    Enemy* selectedEnemy = enemyManager.GetEnemy(0); // Get Enemy 1 
    for (int i = 0; i < 2; i++) {
        dalgoo1.PerformAttack(*selectedEnemy);
    }
    enemyManager.DisplayAllEnemies();

    cout << "\n===== Part 5: Dalgoo 2 Attack Enemy 2 =====" << endl;
    selectedEnemy = enemyManager.GetEnemy(1); // Get Enemy 2 
    for (int i = 0; i < 2; i++) {
        dalgoo2.PerformAttack(*selectedEnemy);
    }
    enemyManager.DisplayAllEnemies();

    cout << "\n===== Part 6: Dalgoo 1 Attack Enemy 3 =====" << endl;
    selectedEnemy = enemyManager.GetEnemy(2); // Get Enemy 3 
    for (int i = 0; i < 5; i++) {
        dalgoo1.PerformAttack(*selectedEnemy);
    }
    enemyManager.DisplayAllEnemies();

    cout << "\n===== Part 7: Check if all enemies are defeated =====" << endl;
    if (enemyManager.AreAllEnemiesDefeated()) {
        cout << "All enemies have been defeated!" << endl;
    }
    else {
        cout << "There are still enemies remaining." << endl;
    }
    cout << "Total attacks performed: " << Dalgoo::GetTotalAttacks() << endl;

    cout << "\n===== Part 8: Destructor =====" << endl;
    return 0;
}
