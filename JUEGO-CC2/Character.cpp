#include "Character.h"

int Character::characterCount = 0;

Character::Character(std::string n, float d, float as, float spd, int l, sf::Vector2f p, sf::Vector2f s) : Unit(n, p, s, spd)
{
    damage = d;
    attackSpeed = as;
    setLevel(l);
    attackDelay = sf::Time::Zero;
    id = ++characterCount;
    setMaxShield(20);
}

Character::Character() {}

void Character::update(sf::Time elapsed) {
    regenerate(elapsed);
    attackDelay -= elapsed;
    move();
}

void Character::attack(std::vector<std::unique_ptr<Projectile>>& projectiles,
    sf::Vector2f mousePos,
    sf::Time elapsed)
{
    // Change direction character is looking in x direction
    float xDir = getCenter().x - mousePos.x;
    if ((xDir > 0 && !left) || (xDir < 0 && left)) {
        look();
    }

    if (attackDelay - elapsed >= sf::Time::Zero) {
        return;
    }

    // Determine attack based on class
    if (getClass() == ARCHER) {
        float attackDamage = (std::rand() % (int)(damage * 0.2 + 1)) + damage - damage * 0.1;
        Arrow arrow(getCenter(), mousePos, attackDamage, true);
        projectiles.push_back(std::make_unique<Arrow>(arrow));
    }
    else if (getClass() == ELEMAGE) {
        float attackDamage = (std::rand() % (int)(damage * 0.2 + 1)) + damage - damage * 0.1;
        FireBall fireBall(getCenter(), mousePos, attackDamage, true);
        projectiles.push_back(std::make_unique<FireBall>(fireBall));
    }
    else {
        SwordSwing swordSwing(getCenter(), mousePos, damage, true);
        projectiles.push_back(std::make_unique<SwordSwing>(swordSwing));
    }

    attackDelay = sf::seconds(0.3) / attackSpeed;
}

void Character::regenerate(sf::Time elapsed) {
    addHealth(healthRegen * elapsed.asSeconds());
    addMana(manaRegen * elapsed.asSeconds());
}

bool Character::isDead() {
    return health <= 0;
}

void Character::setLevel(int n) {
    while (level < n) levelUp();
}

void Character::levelUp() {
    addMaxHealth(10);
    addHealth(10);
    addMaxMana(10);
    addMana(10);
    speed += 2;
    damage += 1;
    level++;
    healthRegen += 0.2;
    manaRegen += 0.2;
}

void Character::setHealth(float n) {
    health = (n > maxHealth) ? maxHealth : n;
}

void Character::addHealth(float n) {
    setHealth(health + n);
}

void Character::removeHealth(float n, DamageType damageType, std::vector<ParticleSystem>& particleSystem) {
    float dmgAmount = n * damageMultiplier[damageType];
    if (shield > 0) {
        removeShield(dmgAmount);
        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(hitbox.left, hitbox.top), Utils::toString(dmgAmount, 1), 1, sf::Color(20, 20, 20), 30);
    }
    else {
        setHealth(health - dmgAmount);
        particleSystem[ParticlesGame::PARTICLES_WORLD].addTextEmitter(sf::Vector2f(hitbox.left, hitbox.top), Utils::toString(dmgAmount, 1), 1, sf::Color(DamageTypeColors[damageType]), 36);
    }
}

void Character::setMaxHealth(float n) {
    maxHealth = (n <= 0) ? 1 : n;
}

void Character::addMaxHealth(float n) {
    setMaxHealth(maxHealth + n);
}

void Character::setHealthRegen(float n) {
    healthRegen = n;
}

void Character::setMana(float n) {
    if (n < 0)              mana = 0;
    else if (n > maxMana)   mana = maxMana;
    else                    mana = n;
}

void Character::addMana(float n) {
    setMana(mana + n);
}

void Character::removeMana(float n) {
    setMana(mana - n);
}

void Character::setMaxMana(float n) {
    maxMana = (n <= 0) ? 1 : n;
}

void Character::addMaxMana(float n) {
    setMaxMana(maxMana + n);
}

void Character::setManaRegen(float n) {
    manaRegen = n;
}

void Character::setShield(float n) {
    if (n < 0)              shield = 0;
    else if (n > maxShield) shield = maxShield;
    else                    shield = n;
}

void Character::addShield(float n) {
    setShield(getShield() + n);
}

void Character::removeShield(float n) {
    setShield(getShield() - n);
}

void Character::setMaxShield(float n) {
    maxShield = (n < 0) ? 0 : n;
}

int Character::getLevel() const {
    return level;
}
float Character::getHealth() const {
    return health;
}
float Character::getMaxHealth() const {
    return maxHealth;
}
float Character::getHealthRegen() const {
    return healthRegen;
}
float Character::getMana() const {
    return mana;
}
float Character::getMaxMana() const {
    return maxMana;
}
float Character::getManaRegen() const {
    return manaRegen;
}
float Character::getShield() const {
    return shield;
}
float Character::getMaxShield() const {
    return maxShield;
}
int Character::getId() const {
    return id;
}
int Character::getClass() const {
    return playerClass;
}
